#include "MiniTest.h"
#include "ps2x/iop/ps2_path.h"
#include "../../ps2xIOP/tests/iop_compat_test_support.h"
#include "../../ps2xIOP/src/emulator/core/iop_cpu.h"
#include "../../ps2xIOP/src/emulator/core/iop_kernel.h"
#include "../../ps2xIOP/src/emulator/imports/iop_cdvd.h"
#include "../../ps2xIOP/src/emulator/core/iop_memory.h"
#include "../../ps2xIOP/src/emulator/services/iop_rpc.h"

void register_ps2_iop_tests()
{
    MiniTest::Case("PS2IopSubsystem", [](TestCase &tc)
    {
        tc.Run("PS2 path parsing is shared and normalizes ISO/module names", [](TestCase &t)
        {
            const ps2x::iop::ParsedPs2Path cd = ps2x::iop::parsePs2Path("CDROM0:\\MODULES\\LIBSD.IRX;1");
            t.Equals(cd.device, ps2x::iop::Ps2PathDevice::Cdrom,
                     "device names should be case-insensitive");
            t.Equals(cd.path, std::string("MODULES/LIBSD.IRX"),
                     "separators and ISO version suffixes should normalize once");
            t.Equals(ps2x::iop::ps2PathLeafKey(cd), std::string("libsd"),
                     "module lookup should use a normalized IRX leaf key");

            const ps2x::iop::ParsedPs2Path rom = ps2x::iop::parsePs2Path("rom0:ROMVER");
            t.Equals(rom.device, ps2x::iop::Ps2PathDevice::Rom0,
                     "ROM0 should remain a distinct virtual device");
            t.IsFalse(static_cast<bool>(ps2x::iop::parsePs2Path("unknown0:file.irx")),
                      "unsupported devices must not fall through to cdrom0");
        });

        tc.Run("HLE services activate only after a recognized module load", [](TestCase &t)
        {
            iop_test::Host host;
            ps2x::iop::IopSubsystem subsystem(host);
            t.IsFalse(subsystem.canBindRpc(0x80000701u),
                      "LIBSD RPC must not exist before LIBSD is loaded");

            const ps2x::iop::ModuleLoadResult unknown = subsystem.loadModule("rom0:NOT_A_REAL_MODULE");
            t.IsTrue(unknown.handled, "the module manager should return a real load result");
            t.IsTrue(unknown.moduleId < 0, "unknown ROM modules must fail instead of receiving fake IDs");

            const ps2x::iop::ModuleLoadResult loaded = subsystem.loadModule("rom0:LIBSD");
            t.IsTrue(loaded.moduleId > 0, "a registered no-BIOS HLE module should load");
            t.IsTrue(subsystem.canBindRpc(0x80000701u),
                     "loading LIBSD should activate its HLE RPC endpoint");

            ps2x::iop::RpcRequest request{};
            request.sid = 0x80000701u;
            request.function = 3u;
            t.IsTrue(subsystem.handleRpc(request).handled,
                     "the activated LIBSD service should handle its RPC");
            t.Equals(host.audioCalls, 1u, "the RPC should reach the HLE audio contract");

            int32_t stopResult = -1;
            t.IsTrue(subsystem.stopModule(loaded.moduleId, &stopResult),
                     "an HLE module should have a real stoppable lifecycle");
            t.Equals(stopResult, 0, "stopping an HLE module should report success");
            t.IsFalse(subsystem.canBindRpc(0x80000701u),
                      "stopping LIBSD should deactivate its RPC endpoint");
        });

        // GOW-Port: 989snd toma su candado del tick con WaitSema desde el servidor RPC (sin hilo actual).
        tc.Run("WaitSema outside a thread waits for the semaphore instead of faking success", [](TestCase &t)
        {
            using namespace ps2x::iop::detail;
            IopMemory memory;
            IopKernel kernel(memory);
            kernel.reset();
            constexpr uint32_t kDescriptor = 0x2000u;
            memory.write32(kDescriptor + 0u, 0u);
            memory.write32(kDescriptor + 4u, 0u);
            memory.write32(kDescriptor + 8u, 0u); // ocupado por otro hilo
            memory.write32(kDescriptor + 12u, 1u);
            IopCpuState create{};
            create.gpr[4] = kDescriptor;
            t.IsTrue(kernel.dispatchSemaphoreImport(4u, create), "CreateSema should be handled");
            const uint32_t id = create.gpr[2];

            IopCpuState wait{};
            wait.gpr[4] = id;
            t.IsTrue(kernel.dispatchSemaphoreImport(8u, wait), "WaitSema should be handled");
            t.Equals(static_cast<int32_t>(wait.gpr[2]), -419, "without anyone to release it, WaitSema must not report success");

            uint32_t waits = 0u;
            kernel.setOutsideThreadWait([&](const std::function<bool()> &ready)
            {
                ++waits;
                IopCpuState signal{};
                signal.gpr[4] = id; // el hilo que lo tenia lo libera
                (void)kernel.dispatchSemaphoreImport(6u, signal);
                return ready();
            });
            wait = {};
            wait.gpr[4] = id;
            t.IsTrue(kernel.dispatchSemaphoreImport(8u, wait), "WaitSema should be handled");
            t.Equals(wait.gpr[2], 0u, "WaitSema should succeed once another thread signals");
            t.Equals(waits, 1u, "WaitSema should let other threads run while it waits");
            IopCpuState poll{};
            poll.gpr[4] = id;
            t.IsTrue(kernel.dispatchSemaphoreImport(9u, poll), "PollSema should be handled");
            t.Equals(static_cast<int32_t>(poll.gpr[2]), -419, "the waiter should own the semaphore");
        });

        // GOW-Port: smpd y 989snd cargan los bancos de sonido desde la RAM del EE con sceSifGetOtherData.
        tc.Run("sceSifGetOtherData copies EE memory into IOP RAM", [](TestCase &t)
        {
            using namespace ps2x::iop::detail;
            iop_test::Host host;
            IopMemory memory;
            IopKernel kernel(memory);
            kernel.reset();
            IopRpcBridge rpc(host, memory, kernel);
            rpc.reset();
            constexpr uint32_t kEeSource = 0x1000u;
            constexpr uint32_t kIopDestination = 0x30000u;
            constexpr uint32_t kReceiveData = 0x2800u;
            for (uint32_t i = 0; i < 64u; ++i)
            {
                const uint8_t value = static_cast<uint8_t>(0x40u + i);
                (void)host.writeGuest(kEeSource + i, &value, 1u);
            }
            IopCpuState cpu{};
            cpu.gpr[4] = kReceiveData;
            cpu.gpr[5] = kEeSource;
            cpu.gpr[6] = kIopDestination;
            cpu.gpr[7] = 64u;
            t.IsTrue(rpc.dispatchSifCmdImport(23u, cpu), "sifcmd:23 should be handled");
            t.Equals(cpu.gpr[2], 0u, "sceSifGetOtherData should succeed");
            bool copied = true;
            for (uint32_t i = 0; i < 64u; ++i)
                copied = copied && memory.read8(kIopDestination + i) == static_cast<uint8_t>(0x40u + i);
            t.IsTrue(copied, "the EE bytes should land at the IOP destination");
            t.Equals(memory.read32(kReceiveData + 0x10u), kEeSource, "receive data should record the source");
            t.Equals(memory.read32(kReceiveData + 0x14u), kIopDestination, "receive data should record the destination");
            t.Equals(memory.read32(kReceiveData + 0x18u), 64u, "receive data should record the size");
        });

        // GOW-Port: sio2man espera el fin de cada transferencia de la memory card con WaitEventFlag, y mc2_d
        // la pide desde el servidor RPC de dbcman, sin hilo actual.
        tc.Run("WaitEventFlag outside a thread waits for the flag instead of failing", [](TestCase &t)
        {
            using namespace ps2x::iop::detail;
            IopMemory memory;
            IopKernel kernel(memory);
            kernel.reset();
            constexpr uint32_t kDescriptor = 0x2000u;
            constexpr uint32_t kResult = 0x2040u;
            memory.write32(kDescriptor + 0u, 0u);
            memory.write32(kDescriptor + 4u, 0u);
            memory.write32(kDescriptor + 8u, 0u);
            IopCpuState create{};
            create.gpr[4] = kDescriptor;
            t.IsTrue(kernel.dispatchEventImport(4u, create), "CreateEventFlag should be handled");
            const uint32_t id = create.gpr[2];

            IopCpuState wait{};
            wait.gpr[4] = id;
            wait.gpr[5] = 0x1000u;
            wait.gpr[6] = 0x10u; // WEF_AND | WEF_CLEAR
            wait.gpr[7] = kResult;
            t.IsTrue(kernel.dispatchEventImport(10u, wait), "WaitEventFlag should be handled");
            t.Equals(static_cast<int32_t>(wait.gpr[2]), -418, "without anyone to set it, the wait must fail");

            kernel.setOutsideThreadWait([&](const std::function<bool()> &ready)
            {
                IopCpuState set{};
                set.gpr[4] = id;
                set.gpr[5] = 0x1000u; // la interrupcion del SIO2 marca el fin
                (void)kernel.dispatchEventImport(6u, set);
                return ready();
            });
            wait.gpr[2] = 0xFFFFFFFFu;
            t.IsTrue(kernel.dispatchEventImport(10u, wait), "WaitEventFlag should be handled");
            t.Equals(wait.gpr[2], 0u, "WaitEventFlag should succeed once the flag is set");
            t.Equals(memory.read32(kResult), 0x1000u, "the satisfied bits should be reported");
            IopCpuState poll{};
            poll.gpr[4] = id;
            poll.gpr[5] = 0x1000u;
            t.IsTrue(kernel.dispatchEventImport(11u, poll), "PollEventFlag should be handled");
            t.Equals(static_cast<int32_t>(poll.gpr[2]), -418, "WEF_CLEAR should have cleared the flag");
        });

        // GOW-Port: dbcman contesta al EE con sceSifSetDmaIntr y espera su callback para enviar lo siguiente.
        tc.Run("sceSifSetDmaIntr copies to the EE and queues its completion callback", [](TestCase &t)
        {
            using namespace ps2x::iop::detail;
            iop_test::Host host;
            IopMemory memory;
            IopKernel kernel(memory);
            kernel.reset();
            IopRpcBridge rpc(host, memory, kernel);
            rpc.reset();
            constexpr uint32_t kSource = 0x30000u;
            constexpr uint32_t kDescriptor = 0x30100u;
            constexpr uint32_t kEeDestination = 0x1800u;
            uint8_t payload[32];
            for (uint32_t i = 0; i < 32u; ++i)
                payload[i] = static_cast<uint8_t>(0x60u + i);
            t.IsTrue(memory.writeRam(kSource, payload, sizeof(payload)), "payload should be written");
            const uint32_t descriptor[4] = {kSource, kEeDestination, static_cast<uint32_t>(sizeof(payload)), 0u};
            t.IsTrue(memory.writeRam(kDescriptor, descriptor, sizeof(descriptor)), "descriptor should be written");

            IopCpuState cpu{};
            cpu.gpr[4] = kDescriptor;
            cpu.gpr[5] = 1u;
            cpu.gpr[6] = 0x112F4u; // callback
            cpu.gpr[7] = 0x55u;    // argumento
            cpu.gpr[28] = 0x9000u; // gp
            t.IsTrue(rpc.dispatchSifManImport(32u, cpu), "sifman:32 should be handled");
            t.IsTrue(cpu.gpr[2] != 0u, "sceSifSetDmaIntr should return a DMA id");
            uint8_t copied[32]{};
            t.IsTrue(host.readGuest(kEeDestination, copied, sizeof(copied)), "EE destination should be readable");
            t.IsTrue(std::memcmp(copied, payload, sizeof(payload)) == 0, "the payload should reach EE memory");
            IopRpcBridge::DmaCompletionCallback callback{};
            t.IsTrue(rpc.takeDmaCompletionCallback(callback), "the completion callback should be queued");
            t.Equals(callback.function, 0x112F4u, "callback function");
            t.Equals(callback.argument, 0x55u, "callback argument");
            t.Equals(callback.gp, 0x9000u, "callback gp");
            t.IsFalse(rpc.takeDmaCompletionCallback(callback), "the callback should be taken once");
        });

        // GOW-Port: mc2_d copia las especificaciones de la tarjeta con LWL/LWR seguidas sobre el mismo registro.
        tc.Run("IOP LWR merges with the LWL still in the load delay slot", [](TestCase &t)
        {
            using namespace ps2x::iop::detail;
            IopMemory memory;
            IopCpuCore core(memory);
            constexpr uint32_t kCode = 0x40000u;
            constexpr uint32_t kData = 0x40100u;
            const uint8_t bytes[8] = {0x10u, 0x11u, 0x12u, 0x13u, 0x14u, 0x15u, 0x16u, 0x17u};
            t.IsTrue(memory.writeRam(kData, bytes, sizeof(bytes)), "data should be written");
            const uint32_t code[3] = {
                (0x22u << 26) | (5u << 21) | (8u << 16) | 6u, // lwl t0, 6(a1): palabra sin alinear en kData+3
                (0x26u << 26) | (5u << 21) | (8u << 16) | 3u, // lwr t0, 3(a1)
                0u,                                           // nop
            };
            t.IsTrue(memory.writeRam(kCode, code, sizeof(code)), "code should be written");
            IopCpuState cpu{};
            cpu.pc = kCode;
            cpu.gpr[5] = kData;
            cpu.gpr[8] = 0xAAAAAAAAu;
            for (int i = 0; i < 3; ++i)
                (void)core.executeInstruction(cpu);
            t.Equals(cpu.gpr[8], 0x16151413u, "the unaligned word should be assembled from both halves");
        });

        // GOW-Port: mc2_d pone la fecha de las partidas con sceCdReadClock del IOP.
        tc.Run("IOP sceCdReadClock writes a valid BCD clock", [](TestCase &t)
        {
            using namespace ps2x::iop::detail;
            iop_test::Host host;
            IopMemory memory;
            IopKernel kernel(memory);
            kernel.reset();
            IopCdvd cdvd(host, memory, kernel);
            cdvd.reset();
            constexpr uint32_t kClock = 0x2400u;
            IopCpuState cpu{};
            cpu.gpr[4] = kClock;
            t.IsTrue(cdvd.dispatchImport(24u, cpu), "cdvdman:24 should be handled");
            t.Equals(cpu.gpr[2], 1u, "sceCdReadClock should succeed");
            const auto value = [&](uint32_t offset)
            {
                const uint8_t b = memory.read8(kClock + offset);
                return static_cast<uint32_t>((b >> 4) * 10u + (b & 0xFu));
            };
            t.IsTrue(value(1) < 60u && value(2) < 60u && value(3) < 24u, "time fields should be valid BCD");
            t.IsTrue(value(5) >= 1u && value(5) <= 31u, "day should be valid");
            t.IsTrue(value(6) >= 1u && value(6) <= 12u, "month should be valid");
        });

        tc.Run("unknown SID remains unhandled without a loaded IRX", [](TestCase &t)
        {
            iop_test::Host host;
            ps2x::iop::IopSubsystem subsystem(host);

            ps2x::iop::RpcRequest request{};
            request.sid = 0xDEADC0DEu;
            request.function = 0x99u;
            const ps2x::iop::RpcResult result = subsystem.handleRpc(request);
            t.IsFalse(result.handled, "an unknown SID should not be claimed by the IOP subsystem");
            t.Equals(result.resultAddress, 0u, "an unknown SID should not return a guest result address");
            t.IsFalse(result.signalNowaitCompletion, "an unknown SID should not signal nowait completion");
            t.Equals(result.callbackPolicy, ps2x::iop::CallbackPolicy::RuntimeDefault,
                     "an unknown SID should preserve runtime callback handling");

        });

    });
}
