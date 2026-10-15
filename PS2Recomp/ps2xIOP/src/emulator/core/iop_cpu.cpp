#include "iop_cpu.h"
#include "iop_cpu_exec.h"
#include "iop_memory.h"

namespace ps2x::iop::detail
{
    IopCpuCore::IopCpuCore(IopMemory &memory) noexcept
        : m_memory(memory)
    {
    }

    void IopCpuCore::raiseException(IopCpuState &cpu, uint32_t code, uint32_t faultPc, bool delaySlot, std::optional<uint32_t> badAddress) const
    {
        iopRaiseException(cpu, code, faultPc, delaySlot, badAddress);
    }

    bool IopCpuCore::executeInstruction(IopCpuState &cpu)
    {
        const uint32_t pc = cpu.pc;
        return iopExecute(cpu, m_memory, m_memory.fetch32(pc), pc); // GOW-Port: lectura en linea
    }
}
