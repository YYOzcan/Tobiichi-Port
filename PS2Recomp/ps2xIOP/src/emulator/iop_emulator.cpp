#include "iop_emulator.h"
#include "imports/iop_cdvd.h"
#include "core/iop_cpu.h"
#include "imports/iop_heaplib.h"
#include "imports/iop_imports.h"
#include "imports/iop_intrman.h"
#include "imports/iop_ioman.h"
#include "core/iop_kernel.h"
#include "imports/iop_loadcore.h"
#include "core/iop_memory.h"
#include "services/iop_module_loader.h"
#include "services/iop_rpc.h"
#include "imports/iop_stdio.h"
#include "imports/iop_sysclib.h"
#include "imports/iop_sysmem.h"
#include "imports/iop_timrman.h"
#include "imports/iop_vblank.h"
#include "iop_emulator_const.h"

#include <algorithm>
#include <filesystem>
#include <cstdlib>
#include <cctype>
#include <map>
#include <optional>
#include <span>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace ps2x::iop::detail
{
    namespace
    {
        constexpr uint32_t kRamSize = IopMemory::RamSize;
        constexpr uint32_t kKernelHeapBase = IopMemory::HeapBase;
        constexpr uint32_t kKernelHeapLimit = IopMemory::HeapLimit;
        constexpr uint32_t kCallStackBase = kKernelHeapLimit;
        constexpr uint32_t kCallStackLimit = 0x001FFF00u;
        constexpr uint32_t kCallStackSize = 0x2000u;
        constexpr uint32_t kCallStackCapacity = (kCallStackLimit - kCallStackBase) / kCallStackSize;
        constexpr uint64_t kCdvdCompletionCycles = 128u;

        uint32_t physicalAddress(uint32_t address)
        {
            return IopMemory::physicalAddress(address);
        }

        int32_t sign16(uint32_t value)
        {
            return static_cast<int16_t>(value & 0xFFFFu);
        }

        bool iequals(std::string_view lhs, std::string_view rhs)
        {
            if (lhs.size() != rhs.size())
                return false;
            for (size_t i = 0; i < lhs.size(); ++i)
            {
                if (std::tolower(static_cast<unsigned char>(lhs[i])) !=
                    std::tolower(static_cast<unsigned char>(rhs[i])))
                    return false;
            }
            return true;
        }

    }

    class IopEmulator::Impl final : public IopGuestExecutor
    {
    public:
        using CpuState = IopCpuState;

        struct Module
        {
            int id = 0;
            std::string path;
            std::string name;
            uint32_t base = 0;
            uint32_t size = 0;
            uint32_t entry = 0;
            uint32_t gp = 0;
            bool resident = false;
        };

        struct GuestCallback
        {
            uint32_t function = 0;
            uint32_t gp = 0;
        };

        static constexpr uint64_t kSifDmaCompletionCycles = 2000u; // GOW-Port
        struct ScheduledGuestCallback
        {
            uint32_t function = 0u;
            uint32_t gp = 0u;
            uint32_t argument = 0u;
        };

        explicit Impl(IopHost &hostRef)
            : host(hostRef),
              sysmem(host, memory),
              kernel(memory),
              cdvd(host, memory, kernel),
              vblank(kernel),
              rpc(host, memory, kernel),
              sysclib(memory),
              stdio(host, memory),
              heaplib(memory),
              intrman(memory),
              timrman(),
              ioman(memory),
              cpuCore(memory),
              imports(memory),
              loadcore(memory, imports)
        {
            reset();
            kernel.setOutsideThreadWait([this](const std::function<bool()> &ready) { return waitOutsideThread(ready); });
            // GOW-Port: memory card del SIO2. Puerto 1: GOW_MC0 o Mcd001.ps2 junto al ELF (formato de PCSX2);
            // puerto 2: solo con GOW_MC1. GOW_MC0=0 deja el puerto 1 vacio.
            memory.sio2().setCardPathProvider([this](uint32_t port) -> std::string
            {
                const char *setting = std::getenv(port == 0u ? "GOW_MC0" : "GOW_MC1");
                if (setting != nullptr)
                    return setting[0] == '0' && setting[1] == '\0' ? std::string() : std::string(setting);
                if (port != 0u)
                    return {};
                const std::string directory = host.hostPath(HostPathKind::ElfDirectory);
                return directory.empty() ? std::string("Mcd001.ps2") : (std::filesystem::path(directory) / "Mcd001.ps2").string();
            });
        }

        void reset()
        {
            memory.reset();
            kernel.reset();
            modules.clear();
            imports.reset();
            rpc.reset();
            cdvd.reset();
            intrman.reset();
            timrman.reset();
            ioman.reset();
            pendingDmaInterrupts.clear();
            pendingGuestCallbacks.clear();
            nextModuleId = 1;
            moduleCursor = kModuleLoadBase;
            totalCycles = 0;
            totalInstructions = 0;
            eeCycleCarry = 0;
            activeCpu = nullptr;
            lastError.clear();
            servicingDmaInterrupts = false;
            servicingGuestCallbacks = false;
            callDepth = 0u;
            secrMcCommandHandler = {};
            secrMcDevIdHandler = {};
            checkKelfPathCallback = {};
        }

        uint8_t read8(uint32_t address) const
        {
            return memory.read8(address);
        }

        uint16_t read16(uint32_t address) const
        {
            return memory.read16(address);
        }

        uint32_t read32(uint32_t address) const
        {
            return memory.read32(address);
        }

        void write8(uint32_t address, uint8_t value)
        {
            memory.write8(address, value);
            schedulePendingDma();
        }

        void write16(uint32_t address, uint16_t value)
        {
            memory.write16(address, value);
            schedulePendingDma();
        }

        void write32(uint32_t address, uint32_t value)
        {
            memory.write32(address, value);
            schedulePendingDma();
        }

        void schedulePendingDma()
        {
            if (!memory.hasDmaStart()) // GOW-Port: comprobacion barata en cada instruccion
                return;
            if (const auto dma = memory.takeDmaStart())
                pendingDmaInterrupts[dma->irq] = totalCycles + dma->delayCycles;
        }

        bool readRam(uint32_t address, void *destination, size_t size) const
        {
            return memory.readRam(address, destination, size);
        }

        bool writeRam(uint32_t address, const void *source, size_t size)
        {
            return memory.writeRam(address, source, size);
        }

        bool zeroRam(uint32_t address, size_t size)
        {
            return memory.zeroRam(address, size);
        }

        bool isHardwareAddress(uint32_t phys) const
        {
            return memory.isHardwareAddress(phys);
        }

        uint32_t allocate(uint32_t size, uint32_t alignment = 16u, std::optional<uint32_t> fixed = std::nullopt)
        {
            return memory.allocate(size, alignment, fixed);
        }

        bool freeAllocation(uint32_t address)
        {
            return memory.freeAllocation(address);
        }

        void log(LogLevel level, std::string_view text)
        {
            host.log(level, text);
        }

        bool checkInterrupt(CpuState &cpu)
        {
            const uint32_t status = cpu.cop0[12];
            if ((status & 1u) == 0u)
                return false;
            if ((status & 0x2u) != 0u)
                return false;
            const bool pending = memory.interruptControl() != 0u && (memory.interruptStatus() & memory.interruptMask()) != 0u;
            if (!pending)
                return false;
            cpu.cop0[13] |= 0x400u;
            cpuCore.raiseException(cpu, 0u, cpu.pc, false);
            return true;
        }

        enum class ImportDisposition
        {
            Handled,
            JumpToGuest,
            Missing,
        };

        ImportDisposition dispatchImport(const IopImportCall &call, CpuState &cpu)
        {
            const uint32_t a0 = cpu.gpr[4];
            auto setV0 = [&](uint32_t value)
            {
                cpu.gpr[2] = value;
            };

            // GOW-Port: traza opcional de llamadas a importaciones (PS2X_IOP_TRACE=<numero de llamadas>).
            static const long traceLimit = []
            {
                const char *v = std::getenv("PS2X_IOP_TRACE");
                return v ? std::strtol(v, nullptr, 10) : 0L;
            }();
            // PS2X_IOP_TRACE_EVERY=<n>: muestreo, una de cada n llamadas (para ver progreso sin frenar).
            static const long traceEvery = []
            {
                const char *v = std::getenv("PS2X_IOP_TRACE_EVERY");
                return v ? std::strtol(v, nullptr, 10) : 0L;
            }();
            // PS2X_IOP_TRACE_NOCLIB=1: no trazar sysclib (memcpy/strncmp...), que es la mayor parte del volumen.
            static const bool traceNoClib = std::getenv("PS2X_IOP_TRACE_NOCLIB") != nullptr;
            static long traceCount = 0;
            static long callCount = 0;
            ++callCount;
            const bool traceSkip = traceNoClib && iequals(call.library, "sysclib");
            // PS2X_IOP_TRACE_FROM=<n>: la traza de PS2X_IOP_TRACE empieza en la llamada n.
            static const long traceFrom = []
            {
                const char *v = std::getenv("PS2X_IOP_TRACE_FROM");
                return v ? std::strtol(v, nullptr, 10) : 0L;
            }();
            if (!traceSkip && ((callCount >= traceFrom && traceCount < traceLimit) || (traceEvery > 0 && callCount % traceEvery == 0)))
            {
                ++traceCount;
                std::ostringstream trace;
                trace << "[IOP:trace] #" << std::dec << callCount << " " << call.library << ':' << std::dec << call.ordinal << std::hex
                      << " a0=0x" << cpu.gpr[4] << " a1=0x" << cpu.gpr[5] << " a2=0x" << cpu.gpr[6]
                      << " a3=0x" << cpu.gpr[7] << " ra=0x" << cpu.gpr[31];
                log(LogLevel::Info, trace.str());
            }

            if (iequals(call.library, "sysmem") && sysmem.dispatchImport(call.ordinal, cpu))
                return ImportDisposition::Handled;

            if (iequals(call.library, "cdvdman") && cdvd.dispatchImport(call.ordinal, cpu))
            {
                if (const auto callback = cdvd.takeCompletionCallback())
                {
                    pendingGuestCallbacks.emplace(
                        totalCycles + kCdvdCompletionCycles,
                        ScheduledGuestCallback{
                            callback->address,
                            callback->gp,
                            callback->reason,
                        });
                }
                return ImportDisposition::Handled;
            }

            if (iequals(call.library, "loadcore") && loadcore.dispatchImport(call.ordinal, cpu))
                return ImportDisposition::Handled;

            if (iequals(call.library, "thbase") || iequals(call.library, "threadman"))
            {
                return kernel.dispatchThreadImport(call.ordinal, cpu, totalCycles)
                           ? ImportDisposition::Handled
                           : ImportDisposition::Missing;
            }
            if (iequals(call.library, "thsemap"))
            {
                return kernel.dispatchSemaphoreImport(call.ordinal, cpu)
                           ? ImportDisposition::Handled
                           : ImportDisposition::Missing;
            }
            if (iequals(call.library, "thevent"))
            {
                return kernel.dispatchEventImport(call.ordinal, cpu)
                           ? ImportDisposition::Handled
                           : ImportDisposition::Missing;
            }
            if (iequals(call.library, "sifcmd"))
            {
                return rpc.dispatchSifCmdImport(call.ordinal, cpu)
                           ? ImportDisposition::Handled
                           : ImportDisposition::Missing;
            }
            if (iequals(call.library, "intrman") && intrman.dispatchImport(call.ordinal, cpu, *this))
                return ImportDisposition::Handled;
            if (iequals(call.library, "secrman"))
            {
                switch (call.ordinal)
                {
                case 4: // SecrSetMcCommandHandler
                    secrMcCommandHandler = {a0, cpu.gpr[28]};
                    setV0(0);
                    return ImportDisposition::Handled;
                case 5: // SecrSetMcDevIDHandler
                    secrMcDevIdHandler = {a0, cpu.gpr[28]};
                    setV0(0);
                    return ImportDisposition::Handled;
                case 6: // SecrAuthCard: GOW-Port: la memory card emulada no lleva MagicGate, se da por autenticada
                    setV0(memory.sio2Enabled() ? 1u : 0u);
                    return ImportDisposition::Handled;
                case 7: // SecrResetAuthCard
                    setV0(0);
                    return ImportDisposition::Handled;
                default:
                    break;
                }
            }
            if (iequals(call.library, "modload") && call.ordinal == 13u)
            {
                checkKelfPathCallback = {a0, cpu.gpr[28]};
                setV0(0);
                return ImportDisposition::Handled;
            }
            if (iequals(call.library, "ioman") && ioman.dispatchImport(call.ordinal, cpu, *this))
                return ImportDisposition::Handled;
            if (iequals(call.library, "sifman"))
            {
                const bool handled = rpc.dispatchSifManImport(call.ordinal, cpu);
                // GOW-Port: dbcman envía al EE con sceSifSetDmaIntr y espera su callback de fin de DMA.
                IopRpcBridge::DmaCompletionCallback callback{};
                if (rpc.takeDmaCompletionCallback(callback))
                    pendingGuestCallbacks.emplace(totalCycles + kSifDmaCompletionCycles,
                                                  ScheduledGuestCallback{callback.function, callback.gp, callback.argument});
                return handled ? ImportDisposition::Handled : ImportDisposition::Missing;
            }
            if (iequals(call.library, "vblank") && vblank.dispatchImport(call.ordinal, cpu, totalCycles))
                return ImportDisposition::Handled;
            if (iequals(call.library, "timrman") && timrman.dispatchImport(call.ordinal, cpu, totalCycles))
                return ImportDisposition::Handled;
            if (iequals(call.library, "dmacman"))
            {
                // GOW-Port: sio2man programa los DMA 11 y 12 del SIO2 con sceSetSliceDMA/sceStartDMA.
                const uint32_t channel = a0;
                const bool sio2Channel = memory.sio2Enabled() && (channel == 11u || channel == 12u);
                const uint32_t channelBase = 0x1F801500u + (channel - 7u) * 0x10u;
                if (sio2Channel && call.ordinal == 28u) // sceSetSliceDMA(canal, direccion, palabras, bloques, sentido)
                {
                    const uint32_t direction = memory.read32(cpu.gpr[29] + 16u);
                    write32(channelBase, cpu.gpr[5] & 0xFFFFFFu);
                    write32(channelBase + 4u, (cpu.gpr[6] & 0xFFFFu) | (cpu.gpr[7] << 16u));
                    write32(channelBase + 8u, (direction & 1u) | 0x200u | (direction == 0u ? 0x40000000u : 0u));
                    setV0(1);
                    return ImportDisposition::Handled;
                }
                if (sio2Channel && call.ordinal == 32u) // sceStartDMA(canal)
                {
                    write32(channelBase + 8u, memory.read32(channelBase + 8u) | 0x01000000u);
                    setV0(0);
                    return ImportDisposition::Handled;
                }
                setV0(0);
                return ImportDisposition::Handled;
            }
            if (iequals(call.library, "stdio") && stdio.dispatchImport(call.ordinal, cpu))
                return ImportDisposition::Handled;
            if (iequals(call.library, "sysclib"))
            {
                return sysclib.dispatchImport(call.ordinal, cpu)
                           ? ImportDisposition::Handled
                           : ImportDisposition::Missing;
            }
            if (iequals(call.library, "heaplib") && heaplib.dispatchImport(call.ordinal, cpu))
                return ImportDisposition::Handled;

            const uint32_t target = imports.resolve(call.library, call.ordinal, call.version);
            if (target != 0u)
            {
                cpu.pc = target;
                cpu.branchPending = false;
                return ImportDisposition::JumpToGuest;
            }

            std::ostringstream out;
            out << "[IOP] unhandled import " << call.library << ':' << call.ordinal
                << " version=0x" << std::hex << call.version << " pc=0x" << cpu.pc;
            log(LogLevel::Warning, out.str());
            setV0(0);
            return ImportDisposition::Missing;
        }

        bool step(CpuState &cpu)
        {
            if (cpu.stopped)
                return false;
            if (cpu.pc == kThreadReturnSentinel || cpu.pc == kCallReturnSentinel)
            {
                cpu.stopped = true;
                return false;
            }
            if (physicalAddress(cpu.pc) >= kRamSize)
            {
                std::ostringstream out;
                out << "[IOP] execution outside RAM pc=0x" << std::hex << cpu.pc;
                log(LogLevel::Error, out.str());
                cpu.stopped = true;
                return false;
            }
            if (checkInterrupt(cpu))
                return true;

            // GOW-Port: los stubs de importacion empiezan por "jr ra"; solo esas direcciones se buscan en las tablas.
            const auto import = memory.fetch32(cpu.pc) == 0x03E00008u ? imports.decode(cpu.pc) : std::nullopt;
            if (import)
            {
                const ImportDisposition disposition = dispatchImport(*import, cpu);
                ++totalInstructions;
                ++totalCycles;
                if (disposition == ImportDisposition::JumpToGuest)
                    return true;
                cpu.pc = cpu.gpr[31];
                cpu.branchPending = false;
                return !cpu.stopped;
            }

            // GOW-Port: muestreo del PC del IOP (PS2X_IOP_PC_EVERY=<instrucciones>), leido una vez al crear el IOP.
            if (pcEvery != 0ULL && totalInstructions % pcEvery == 0ULL)
            {
                std::ostringstream out;
                out << "[IOP:pc] instr=" << std::dec << totalInstructions << std::hex << " pc=0x" << cpu.pc
                    << " ra=0x" << cpu.gpr[31] << " sp=0x" << cpu.gpr[29] << " v0=0x" << cpu.gpr[2]
                    << " a0=0x" << cpu.gpr[4];
                log(LogLevel::Info, out.str());
            }

            const bool running = cpuCore.executeInstruction(cpu);
            schedulePendingDma();
            ++totalInstructions;
            ++totalCycles;
            return running;
        }

        uint32_t runCpu(CpuState &cpu, uint32_t instructionBudget)
        {
            CpuState *previous = activeCpu;
            activeCpu = &cpu;
            const uint64_t start = totalInstructions;
            while (!cpu.stopped && !cpu.yielded && totalInstructions - start < instructionBudget)
            {
                if (!step(cpu))
                    break;
                if (!servicingDmaInterrupts && !pendingDmaInterrupts.empty())
                    servicePendingDmaInterrupts();
                if (!servicingGuestCallbacks && !pendingGuestCallbacks.empty())
                    servicePendingGuestCallbacks();
            }
            activeCpu = previous;
            return static_cast<uint32_t>(totalInstructions - start);
        }

        uint32_t callFunction(uint32_t address,
                              uint32_t a0,
                              uint32_t a1,
                              uint32_t a2,
                              uint32_t a3,
                              uint32_t gp,
                              uint32_t budget = kMaxCallInstructions)
        {
            struct CallDepthGuard
            {
                uint32_t &depth;
                ~CallDepthGuard() { --depth; }
            };

            const uint32_t depth = callDepth++;
            const CallDepthGuard depthGuard{callDepth};
            CpuState cpu{};
            cpu.pc = address;
            cpu.gpr[4] = a0;
            cpu.gpr[5] = a1;
            cpu.gpr[6] = a2;
            cpu.gpr[7] = a3;
            cpu.gpr[28] = gp;
            if (depth < kCallStackCapacity)
            {
                const uint32_t stackTop = kCallStackLimit - depth * kCallStackSize;
                cpu.gpr[29] = stackTop - 32u;
            }
            else if (activeCpu && activeCpu->gpr[29] > kCallStackBase + kStackGuardBytes)
            {
                // Extremely deep re-entrancy borrows unused space below the
                // suspended caller's live frame. Stack growth remains away
                // from the caller, so its saved registers stay intact.
                cpu.gpr[29] = (activeCpu->gpr[29] - kStackGuardBytes) & ~15u;
            }
            else
            {
                cpu.gpr[29] = kCallStackBase - 32u;
            }
            cpu.gpr[31] = kCallReturnSentinel;
            runCpu(cpu, budget);
            if (!cpu.stopped && !cpu.yielded)
            {
                // GOW-Port: avisar en vez de abandonar la llamada en silencio.
                std::ostringstream out;
                out << "[IOP] guest call 0x" << std::hex << address << " exceeded its budget of " << std::dec << budget
                    << " instructions (pc=0x" << std::hex << cpu.pc << ")";
                log(LogLevel::Warning, out.str());
            }
            return cpu.gpr[2];
        }

        void runReadyThreads(uint64_t maxCycles) override
        {
            // Solo desde fuera de la ejecucion del IOP (una RPC del EE), y sin reentrar.
            if (activeCpu != nullptr || settlingThreads)
                return;
            settlingThreads = true;
            const uint64_t start = totalCycles;
            while (kernel.hasReadyThread() && totalCycles - start < maxCycles)
                runCycles(kDefaultSlice * 16u);
            settlingThreads = false;
        }
        bool settlingThreads = false;

        // GOW-Port: una espera sin hilo actual (p. ej. WaitSema en un servidor RPC) deja correr a los hilos del IOP,
        // como haria el IOP real al bloquear al hilo RPC, hasta que la condicion se cumple o pasa kMaxOutsideWaitCycles.
        bool waitOutsideThread(const std::function<bool()> &ready)
        {
            if (ready())
                return true;
            if (waitingOutsideThread)
                return false;
            waitingOutsideThread = true;
            const uint64_t start = totalCycles;
            while (!ready() && totalCycles - start < kMaxOutsideWaitCycles)
                runCycles(kDefaultSlice);
            waitingOutsideThread = false;
            const bool satisfied = ready();
            if (!satisfied)
                log(LogLevel::Warning, "[IOP] wait outside a thread timed out");
            return satisfied;
        }
        bool waitingOutsideThread = false;
        static constexpr uint64_t kMaxOutsideWaitCycles = 36864000u; // ~1 s de reloj del IOP
        const unsigned long long pcEvery = []
        {
            const char *v = std::getenv("PS2X_IOP_PC_EVERY");
            return v ? std::strtoull(v, nullptr, 10) : 0ULL;
        }();

        uint32_t executeGuestFunction(uint32_t address,
                                      uint32_t a0,
                                      uint32_t a1,
                                      uint32_t a2,
                                      uint32_t a3,
                                      uint32_t gp) override
        {
            return callFunction(address, a0, a1, a2, a3, gp);
        }

        uint32_t executeGuestFunctionWithBudget(uint32_t address,
                                                uint32_t a0,
                                                uint32_t a1,
                                                uint32_t a2,
                                                uint32_t a3,
                                                uint32_t gp,
                                                uint32_t instructionBudget) override
        {
            return callFunction(address, a0, a1, a2, a3, gp, instructionBudget);
        }

        // Not that good to use exception handling for control flow but will do for now
        void servicePendingDmaInterrupts()
        {
            if (servicingDmaInterrupts || pendingDmaInterrupts.empty())
                return;

            servicingDmaInterrupts = true;

            std::vector<int> completed;
            for (auto it = pendingDmaInterrupts.begin(); it != pendingDmaInterrupts.end();)
            {
                if (it->second > totalCycles)
                {
                    ++it;
                    continue;
                }
                completed.push_back(it->first);
                it = pendingDmaInterrupts.erase(it);
            }
            try
            {
                for (const int irq : completed)
                    (void)intrman.dispatchInterrupt(irq, *this);
            }
            catch (...)
            {
                servicingDmaInterrupts = false;
                throw;
            }
            servicingDmaInterrupts = false;
        }

        // GOW-Port: el SPU2 genera una muestra cada 768 ciclos del IOP; su IRQ (IRQA alcanzada) es la interrupcion 9.
        void serviceSpu2()
        {
            // GOW_SPU2_IRQ=0 desactiva la entrega de la IRQ (para comparar si el juego cambia de comportamiento).
            static const bool irqEnabled = []
            {
                const char *value = std::getenv("GOW_SPU2_IRQ");
                return value == nullptr || value[0] != '0';
            }();
            Spu2 &spu = memory.spu2();
            spu.advanceTo(totalCycles);
            if (!spu.takeInterrupt() || !irqEnabled || servicingSpu2Interrupt)
                return;
            servicingSpu2Interrupt = true;
            try
            {
                (void)intrman.dispatchInterrupt(Spu2::IopInterrupt, *this);
            }
            catch (...)
            {
                servicingSpu2Interrupt = false;
                throw;
            }
            servicingSpu2Interrupt = false;
        }

        void servicePendingGuestCallbacks()
        {
            if (servicingGuestCallbacks || pendingGuestCallbacks.empty())
                return;

            std::vector<ScheduledGuestCallback> callbacks;
            for (auto it = pendingGuestCallbacks.begin(); it != pendingGuestCallbacks.end();)
            {
                if (it->first > totalCycles)
                    break;
                callbacks.push_back(it->second);
                it = pendingGuestCallbacks.erase(it);
            }
            if (callbacks.empty())
                return;

            servicingGuestCallbacks = true;
            try
            {
                for (const ScheduledGuestCallback &callback : callbacks)
                {
                    if (callback.function != 0u)
                    {
                        (void)callFunction(callback.function,
                                           callback.argument,
                                           0u,
                                           0u,
                                           0u,
                                           callback.gp,
                                           100000u);
                    }
                }
            }
            catch (...)
            {
                servicingGuestCallbacks = false;
                throw;
            }
            servicingGuestCallbacks = false;
        }

        void runCycles(uint64_t cycles) noexcept
        {
            try
            {
                const uint64_t target = totalCycles + cycles;
                while (totalCycles < target)
                {
                    serviceSpu2();
                    servicePendingDmaInterrupts();
                    servicePendingGuestCallbacks();
                    timrman.serviceDue(totalCycles, *this);
                    IopThread *next = kernel.beginNextReady(totalCycles);
                    if (!next)
                    {
                        // GOW-Port: con PS2X_IOP_PC_EVERY, avisar de vez en cuando si el IOP esta ocioso.
                        static unsigned long long idleCount = 0ULL;
                        static const bool idleTrace = std::getenv("PS2X_IOP_PC_EVERY") != nullptr;
                        if (idleTrace && (++idleCount % 200000ULL) == 1ULL)
                        {
                            std::ostringstream out;
                            out << "[IOP:idle] sin hilos listos (veces=" << idleCount << ") instr=" << totalInstructions;
                            log(LogLevel::Info, out.str());
                        }
                        uint64_t nextWake = kernel.nextWakeCycle(target);
                        for (const auto &[irq, completionCycle] : pendingDmaInterrupts)
                            nextWake = std::min(nextWake, completionCycle);
                        if (!pendingGuestCallbacks.empty())
                            nextWake = std::min(nextWake, pendingGuestCallbacks.begin()->first);
                        nextWake = timrman.nextEventCycle(nextWake);
                        totalCycles = std::max(totalCycles + 1u, std::min(target, nextWake));
                        continue;
                    }
                    const uint64_t before = totalCycles;
                    runCpu(next->cpu, static_cast<uint32_t>(std::min<uint64_t>(kDefaultSlice, target - totalCycles)));
                    kernel.endTimeslice(*next, kThreadReturnSentinel);
                    if (totalCycles == before)
                        ++totalCycles;
                }
                serviceSpu2(); // GOW-Port: al dia tambien tras saltar ciclos ociosos hasta el final
            }
            catch (...)
            {
                // Runtime scheduling must never throw through EeScheduler::accountCycles().
            }
        }

        ModuleLoadResult loadImage(std::string path, std::span<const uint8_t> image, const void *arguments, uint32_t argumentSize)
        {
            ModuleLoadResult result{true, -1, -1};
            const IopImageLoadResult loaded = IopModuleLoader::load(image, memory, moduleCursor);
            moduleCursor = loaded.nextModuleCursor;
            if (!loaded)
            {
                if (loaded.error == IopImageLoadError::InvalidElf)
                    log(LogLevel::Error, "[IOP] rejected invalid/non-MIPS IRX ELF");
                else if (loaded.error == IopImageLoadError::ArenaExhausted)
                    log(LogLevel::Error, "[IOP] module arena exhausted");
                return result;
            }
            if (!loaded.relocationsComplete)
                log(LogLevel::Warning, "[IOP] one or more IRX relocations were unsupported");

            Module module;
            module.id = nextModuleId++;
            module.path = std::move(path);
            const size_t slash = module.path.find_last_of("/\\:");
            module.name = slash == std::string::npos ? module.path : module.path.substr(slash + 1u);
            module.base = loaded.base;
            module.size = loaded.size;
            module.entry = loaded.entry;
            module.gp = loaded.gp;

            // GOW-Port: como el loadcore real, el modulo arranca con start(argc, argv): argv[0] es la ruta del
            // modulo y los argumentos vienen separados por '\0' ("rpc_priority=64\0..."). Antes se pasaba
            // (tamano en bytes, puntero al texto) y 989snd leia el texto como punteros ("989snd Error: cause 7").
            std::vector<std::string> argStrings;
            argStrings.push_back(module.path);
            if (arguments && argumentSize)
            {
                const char *text = static_cast<const char *>(arguments);
                size_t begin = 0u;
                for (size_t i = 0u; i <= argumentSize; ++i)
                {
                    if (i == argumentSize || text[i] == '\0')
                    {
                        if (i > begin)
                            argStrings.emplace_back(text + begin, i - begin);
                        begin = i + 1u;
                    }
                }
            }
            uint32_t stringBytes = 0u;
            for (const std::string &value : argStrings)
                stringBytes += static_cast<uint32_t>(value.size()) + 1u;
            const uint32_t pointerBytes = static_cast<uint32_t>(argStrings.size() + 1u) * 4u;
            const uint32_t args = allocate(pointerBytes + stringBytes, 16u);
            const uint32_t argc = static_cast<uint32_t>(argStrings.size());
            if (args)
            {
                uint32_t cursor = args + pointerBytes;
                for (size_t i = 0u; i < argStrings.size(); ++i)
                {
                    memory.write32(args + static_cast<uint32_t>(i) * 4u, cursor);
                    writeRam(cursor, argStrings[i].data(), static_cast<uint32_t>(argStrings[i].size()));
                    write8(cursor + static_cast<uint32_t>(argStrings[i].size()), 0u);
                    cursor += static_cast<uint32_t>(argStrings[i].size()) + 1u;
                }
                memory.write32(args + pointerBytes - 4u, 0u);
            }
            const uint32_t startResult = callFunction(module.entry, args ? argc : 0u, args, 0u, 0u, module.gp);
            if (args)
                freeAllocation(args);
            module.resident = startResult == 0u || startResult == 2u;
            result.moduleId = module.id;
            result.startResult = static_cast<int32_t>(startResult);
            modules[module.id] = std::move(module);

            std::ostringstream out;
            out << "[IOP] loaded IRX id=" << result.moduleId
                << " entry=0x" << std::hex << modules[result.moduleId].entry
                << " base=0x" << modules[result.moduleId].base
                << " start=" << std::dec << result.startResult;
            log(LogLevel::Info, out.str());
            return result;
        }

        ModuleLoadResult loadModule(std::string_view path, const void *arguments, uint32_t argumentSize)
        {
            std::vector<uint8_t> image;
            if (!IopModuleLoader::readWholeHostFile(host, path, image))
            {
                log(LogLevel::Warning, std::string("[IOP] failed to open IRX '") + std::string(path) + "'");
                return {true, -1, -1};
            }
            return loadImage(std::string(path), image, arguments, argumentSize);
        }

        ModuleLoadResult loadModuleBuffer(uint32_t guestAddress, const void *arguments, uint32_t argumentSize)
        {
            std::vector<uint8_t> image;
            if (!IopModuleLoader::readElfFromGuest(host, guestAddress, image))
                return {true, -1, -1};
            std::ostringstream tag;
            tag << "buffer@0x" << std::hex << guestAddress;
            return loadImage(tag.str(), image, arguments, argumentSize);
        }

        bool stopModule(int32_t moduleId, int32_t *result)
        {
            auto it = modules.find(moduleId);
            if (it == modules.end())
                return false;
            // A removable IRX normally exposes a stop entry through module metadata. We do not guess it; terminate owned execution and release the image cleanly.
            kernel.terminateThreadsInRange(it->second.base, it->second.size);
            rpc.removeServersInRange(it->second.base, it->second.size);
            imports.eraseRange(it->second.base, it->second.size);
            modules.erase(it);
            kernel.cleanupDeadThreads();
            if (result)
                *result = 0;
            return true;
        }

        IopHost &host;
        IopMemory memory;
        IopSysmem sysmem;
        IopKernel kernel;
        IopCdvd cdvd;
        IopVblank vblank;
        IopRpcBridge rpc;
        IopSysclib sysclib;
        IopStdio stdio;
        IopHeaplib heaplib;
        IopIntrman intrman;
        IopTimrman timrman;
        IopIoman ioman;
        IopCpuCore cpuCore;
        IopImportRegistry imports;
        IopLoadcore loadcore;
        std::map<int, Module> modules;
        std::map<int, uint64_t> pendingDmaInterrupts;
        bool servicingSpu2Interrupt = false;
        std::multimap<uint64_t, ScheduledGuestCallback> pendingGuestCallbacks;
        uint32_t nextModuleId = 1;
        uint32_t moduleCursor = kModuleLoadBase;
        uint64_t totalCycles = 0;
        uint64_t totalInstructions = 0;
        uint64_t eeCycleCarry = 0;
        CpuState *activeCpu = nullptr;
        std::string lastError;
        bool servicingDmaInterrupts = false;
        bool servicingGuestCallbacks = false;
        uint32_t callDepth = 0u;
        GuestCallback secrMcCommandHandler;
        GuestCallback secrMcDevIdHandler;
        GuestCallback checkKelfPathCallback;
    };

    IopEmulator::IopEmulator(IopHost &host)
        : m_impl(std::make_unique<Impl>(host))
    {
    }

    IopEmulator::~IopEmulator() = default;

    void IopEmulator::reset()
    {
        m_impl->reset();
    }

    ModuleLoadResult IopEmulator::loadModule(std::string_view path, const void *arguments, uint32_t argumentSize)
    {
        return m_impl->loadModule(path, arguments, argumentSize);
    }

    ModuleLoadResult IopEmulator::loadModuleBuffer(uint32_t guestAddress, const void *arguments, uint32_t argumentSize)
    {
        return m_impl->loadModuleBuffer(guestAddress, arguments, argumentSize);
    }

    bool IopEmulator::stopModule(int32_t moduleId, int32_t *result)
    {
        return m_impl->stopModule(moduleId, result);
    }

    void IopEmulator::runEeCycles(uint64_t eeCycles) noexcept
    {
        const uint64_t total = m_impl->eeCycleCarry + eeCycles;
        const uint64_t iopCycles = total / 8u;
        m_impl->eeCycleCarry = total % 8u;
        if (iopCycles)
            m_impl->runCycles(iopCycles);
    }

    RpcResult IopEmulator::handleRpc(const RpcRequest &request)
    {
        return m_impl->rpc.handleRpc(request, *m_impl);
    }

    bool IopEmulator::hasRpcServer(uint32_t sid) const noexcept
    {
        return m_impl->rpc.hasServer(sid);
    }

    void IopEmulator::onSifTransfer(const SifTransfer &transfer)
    {
        m_impl->rpc.onSifTransfer(transfer);
    }

    uint32_t IopEmulator::allocateMemory(uint32_t size, uint32_t alignment)
    {
        return m_impl->memory.allocate(size, alignment);
    }

    bool IopEmulator::freeMemory(uint32_t address)
    {
        return m_impl->memory.freeAllocation(address);
    }

    bool IopEmulator::readMemory(uint32_t address, void *destination, size_t size) const
    {
        return isMemoryRange(address, size) &&
               m_impl->memory.readRam(address, destination, size);
    }

    bool IopEmulator::writeMemory(uint32_t address, const void *source, size_t size)
    {
        return isMemoryRange(address, size) &&
               m_impl->memory.writeRam(address, source, size);
    }

    bool IopEmulator::zeroMemory(uint32_t address, size_t size)
    {
        return isMemoryRange(address, size) &&
               m_impl->memory.zeroRam(address, size);
    }

    bool IopEmulator::isMemoryRange(uint32_t address, size_t size) const
    {
        const bool physicalSegment = address < IopMemory::RamSize;
        const bool cachedSegment = address >= 0x80000000u && address < 0x80200000u;
        const bool uncachedSegment = address >= 0xA0000000u && address < 0xA0200000u;
        if (!physicalSegment && !cachedSegment && !uncachedSegment)
            return false;
        const uint32_t physical = IopMemory::physicalAddress(address);
        return physical <= IopMemory::RamSize && size <= IopMemory::RamSize - physical;
    }

    size_t IopEmulator::drainAudio(int16_t *stereo, size_t maxFrames, size_t maxLatencyFrames)
    {
        return m_impl->memory.spu2().drainOutput(stereo, maxFrames, maxLatencyFrames);
    }

    uint64_t IopEmulator::cycles() const noexcept
    {
        return m_impl->totalCycles;
    }

    uint64_t IopEmulator::instructions() const noexcept
    {
        return m_impl->totalInstructions;
    }

    uint32_t IopEmulator::loadedModuleCount() const noexcept
    {
        return static_cast<uint32_t>(m_impl->modules.size());
    }

    uint32_t IopEmulator::threadCount() const noexcept
    {
        return static_cast<uint32_t>(m_impl->kernel.threadCount());
    }

    uint32_t IopEmulator::rpcServerCount() const noexcept
    {
        return static_cast<uint32_t>(m_impl->rpc.serverCount());
    }

}
