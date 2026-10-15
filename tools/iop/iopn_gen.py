"""Ahead-of-time compiler for the game's IRX modules (IOP, R3000A) -> C++ (ps2xIOP/src/native).

usage: python -I tools/iop/iopn_gen.py <dump dir> <out dir>

<dump dir> comes from a run with PS2X_IOP_DUMP_MODULES=<dump dir>: <name>.bin = the module's code as relocated at its load
address, modules.txt = "<name> <base hex> <text size hex> <fnv hash hex>" per load. The runtime uses a generated module
only when the module is loaded again at the same base with the same bytes.

Every instruction is emitted as specialised C++ with exactly the semantics of iopExecute (ps2xIOP core/iop_cpu_exec.h):
operands are read before the pending load of the previous instruction is committed, the commit skips a register the
instruction itself wrote, loads (and MFC0) become the new pending load, LWL/LWR merge with a pending value of the same
register, exceptions go through iopRaiseException (which drops the pending load). A branch is evaluated, its delay slot
is emitted inline right after it, then the code jumps to the target or falls through. cpu.pc is only stored when control
leaves straight-line code.

Code is split in chunks (one C++ function each, the optimiser does not cope with one function per module); a chunk
switches over all its addresses for dynamic entries (a delay slot entered that way runs as an ordinary instruction).
The module function returns to the IOP dispatcher at import stubs (jr ra; addiu $0,$0,n: the HLE kernel serves them),
on exceptions, when the target is outside the module, and when the instruction budget is used (checked at every
control transfer).
"""
import os
import struct
import sys

CHUNK = 512  # instructions per C++ function


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def fields(w):
    return w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31, w & 63, w & 0xFFFF


def is_branch(w):
    op, rs, rt, rd, sa, fn, imm = fields(w)
    if op == 0:
        return fn in (0x08, 0x09)
    if op == 1:
        return rt in (0x00, 0x01, 0x10, 0x11)
    return op in (0x02, 0x03, 0x04, 0x05, 0x06, 0x07)


def g(r):
    return '0u' if r == 0 else f'cpu.gpr[{r}]'


def commit(written):
    """commit the pending load of the previous instruction (unless this instruction wrote that register)"""
    if written:
        return [f'    if (cpu.pendingLoad) {{ if (cpu.pendingLoadReg != {written}u) cpu.gpr[cpu.pendingLoadReg] = cpu.pendingLoadValue; cpu.pendingLoad = false; }}']
    return ['    if (cpu.pendingLoad) { cpu.gpr[cpu.pendingLoadReg] = cpu.pendingLoadValue; cpu.pendingLoad = false; }']


def raise_(code, pc, delay, addr=None):
    a = f', {addr}' if addr else ''
    return f'{{ iopRaiseException(cpu, {code}u, {pc}, {"true" if delay else "false"}{a}); stop = true; return n; }}'


def emit(w, a, delay):
    """C++ for one non-branch instruction at physical address a; delay = it runs in a branch delay slot"""
    op, rs, rt, rd, sa, fn, imm = fields(w)
    simm = sext16(imm)
    pc = f'seg | 0x{a:x}u'
    L = ['    ++n;']

    def write(reg, expr):
        if reg == 0:
            L.extend(commit(0))
        else:
            L.append(f'    {{ const uint32_t v = {expr};')
            L.extend(['  ' + c for c in commit(reg)])
            L.append(f'      cpu.gpr[{reg}] = v; }}')

    def load(reg, expr, pre=None):
        L.append('    {')
        if pre:
            L.extend('      ' + p for p in pre)
        L.append(f'      const uint32_t v = {expr};')
        L.extend(['  ' + c for c in commit(0)])
        if reg:
            L.append(f'      cpu.pendingLoad = true; cpu.pendingLoadReg = {reg}u; cpu.pendingLoadValue = v;')
        L.append('    }')

    def other(stmts):
        L.extend('    ' + s for s in stmts)
        L.extend(commit(0))

    ea = f'{g(rs)} + 0x{simm & 0xFFFFFFFF:x}u'
    if op == 0:
        if fn == 0x00: write(rd, f'{g(rt)} << {sa}u')
        elif fn == 0x02: write(rd, f'{g(rt)} >> {sa}u')
        elif fn == 0x03: write(rd, f'static_cast<uint32_t>(static_cast<int32_t>({g(rt)}) >> {sa})')
        elif fn == 0x04: write(rd, f'{g(rt)} << ({g(rs)} & 31u)')
        elif fn == 0x06: write(rd, f'{g(rt)} >> ({g(rs)} & 31u)')
        elif fn == 0x07: write(rd, f'static_cast<uint32_t>(static_cast<int32_t>({g(rt)}) >> ({g(rs)} & 31u))')
        elif fn == 0x0C: L.append('    ' + raise_(8, pc, delay))
        elif fn == 0x0D: L.append('    ' + raise_(9, pc, delay))
        elif fn == 0x10: write(rd, 'cpu.hi')
        elif fn == 0x11: other([f'cpu.hi = {g(rs)};'])
        elif fn == 0x12: write(rd, 'cpu.lo')
        elif fn == 0x13: other([f'cpu.lo = {g(rs)};'])
        elif fn == 0x18: other([f'{{ const int64_t r = static_cast<int64_t>(static_cast<int32_t>({g(rs)})) * static_cast<int64_t>(static_cast<int32_t>({g(rt)})); cpu.lo = static_cast<uint32_t>(r); cpu.hi = static_cast<uint32_t>(static_cast<uint64_t>(r) >> 32u); }}'])
        elif fn == 0x19: other([f'{{ const uint64_t r = static_cast<uint64_t>({g(rs)}) * {g(rt)}; cpu.lo = static_cast<uint32_t>(r); cpu.hi = static_cast<uint32_t>(r >> 32u); }}'])
        elif fn == 0x1A: other([f'iopDiv(cpu, {g(rs)}, {g(rt)});'])
        elif fn == 0x1B: other([f'iopDivu(cpu, {g(rs)}, {g(rt)});'])
        elif fn in (0x20, 0x22):
            sign = '+' if fn == 0x20 else '-'
            L.append(f'    {{ const int64_t r = static_cast<int64_t>(static_cast<int32_t>({g(rs)})) {sign} static_cast<int32_t>({g(rt)});')
            L.append(f'      if (r > 0x7FFFFFFFll || r < -0x80000000ll) ' + raise_(12, pc, delay) + ' }')
            write(rd, f'{g(rs)} {sign} {g(rt)}')
        elif fn == 0x21: write(rd, f'{g(rs)} + {g(rt)}')
        elif fn == 0x23: write(rd, f'{g(rs)} - {g(rt)}')
        elif fn == 0x24: write(rd, f'{g(rs)} & {g(rt)}')
        elif fn == 0x25: write(rd, f'{g(rs)} | {g(rt)}')
        elif fn == 0x26: write(rd, f'{g(rs)} ^ {g(rt)}')
        elif fn == 0x27: write(rd, f'~({g(rs)} | {g(rt)})')
        elif fn == 0x2A: write(rd, f'static_cast<int32_t>({g(rs)}) < static_cast<int32_t>({g(rt)}) ? 1u : 0u')
        elif fn == 0x2B: write(rd, f'{g(rs)} < {g(rt)} ? 1u : 0u')
        else: L.append('    ' + raise_(10, pc, delay))
    elif op == 0x01:
        L.append('    ' + raise_(10, pc, delay))  # branches are handled by the caller; other REGIMM codes are invalid
    elif op == 0x08:
        L.append(f'    {{ const int64_t r = static_cast<int64_t>(static_cast<int32_t>({g(rs)})) + ({simm});')
        L.append(f'      if (r > 0x7FFFFFFFll || r < -0x80000000ll) ' + raise_(12, pc, delay) + ' }')
        write(rt, f'{g(rs)} + 0x{simm & 0xFFFFFFFF:x}u')
    elif op == 0x09: write(rt, f'{g(rs)} + 0x{simm & 0xFFFFFFFF:x}u')
    elif op == 0x0A: write(rt, f'static_cast<int32_t>({g(rs)}) < {simm} ? 1u : 0u')
    elif op == 0x0B: write(rt, f'{g(rs)} < 0x{simm & 0xFFFFFFFF:x}u ? 1u : 0u')
    elif op == 0x0C: write(rt, f'{g(rs)} & 0x{imm:x}u')
    elif op == 0x0D: write(rt, f'{g(rs)} | 0x{imm:x}u')
    elif op == 0x0E: write(rt, f'{g(rs)} ^ 0x{imm:x}u')
    elif op == 0x0F: write(rt, f'0x{(imm << 16) & 0xFFFFFFFF:x}u')
    elif op == 0x10:
        if rs == 0x00: load(rt, f'cpu.cop0[{rd}]')
        elif rs == 0x04: other([f'cpu.cop0[{rd}] = {g(rt)};'])
        elif rs == 0x10 and fn == 0x10: other(['{ const uint32_t s = cpu.cop0[12]; cpu.cop0[12] = (s & ~0x0Fu) | ((s >> 2u) & 0x0Fu); }'])
        else: L.append('    ' + raise_(10, pc, delay))
    elif op in (0x20, 0x24):
        load(rt, 'static_cast<uint32_t>(static_cast<int32_t>(static_cast<int8_t>(memory.load8(addr))))' if op == 0x20 else 'memory.load8(addr)',
             [f'const uint32_t addr = {ea};'])
    elif op in (0x21, 0x25):
        load(rt, 'static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(memory.load16(addr))))' if op == 0x21 else 'memory.load16(addr)',
             [f'const uint32_t addr = {ea};', 'if (addr & 1u) ' + raise_(4, pc, delay, 'addr')])
    elif op == 0x23:
        load(rt, 'memory.load32(addr)', [f'const uint32_t addr = {ea};', 'if (addr & 3u) ' + raise_(4, pc, delay, 'addr')])
    elif op in (0x22, 0x26):
        old = f'(cpu.pendingLoad && cpu.pendingLoadReg == {rt}u ? cpu.pendingLoadValue : {g(rt)})'
        if op == 0x22:
            expr = f'({old} & kLwlMask[addr & 3u]) | (memory.load32(addr & ~3u) << kLwlShift[addr & 3u])'
        else:
            expr = f'({old} & kLwrMask[addr & 3u]) | (memory.load32(addr & ~3u) >> kLwrShift[addr & 3u])'
        load(rt, expr, [f'const uint32_t addr = {ea};'])
    elif op == 0x28:
        other([f'memory.store8({ea}, static_cast<uint8_t>({g(rt)}));'])
    elif op == 0x29:
        L.append(f'    {{ const uint32_t addr = {ea}; if (addr & 1u) ' + raise_(5, pc, delay, 'addr') + f' memory.store16(addr, static_cast<uint16_t>({g(rt)})); }}')
        L.extend(commit(0))
    elif op == 0x2B:
        L.append(f'    {{ const uint32_t addr = {ea}; if (addr & 3u) ' + raise_(5, pc, delay, 'addr') + f' memory.store32(addr, {g(rt)}); }}')
        L.extend(commit(0))
    elif op == 0x2A:
        other([f'iopSwl(memory, {ea}, {g(rt)});'])
    elif op == 0x2E:
        other([f'iopSwr(memory, {ea}, {g(rt)});'])
    else:
        L.append('    ' + raise_(10, pc, delay))
    return L


def emit_branch(w, a):
    """evaluates the branch at a: sets locals tk (taken) and tg (target), writes the link register"""
    op, rs, rt, rd, sa, fn, imm = fields(w)
    link = f'seg | 0x{a + 8:x}u'
    L = ['    ++n;']
    if op == 0 and fn == 0x08:
        L.append(f'    tk = true; tg = {g(rs)};')
        L.extend(commit(0))
    elif op == 0 and fn == 0x09:
        r = rd if rd else 31
        L.append(f'    cpu.gpr[{r}] = {link}; tk = true; tg = {g(rs)};')
        L.extend(commit(r))
    elif op == 0x01:
        cond = f'static_cast<int32_t>({g(rs)}) < 0' if rt in (0x00, 0x10) else f'static_cast<int32_t>({g(rs)}) >= 0'
        if rt in (0x10, 0x11):
            L.append(f'    cpu.gpr[31] = {link};')
        L.append(f'    tk = {cond}; tg = seg | 0x{(a + 4 + (sext16(imm) << 2)) & 0x1FFFFFFF:x}u;')
        L.extend(commit(31 if rt in (0x10, 0x11) else 0))
    elif op in (0x02, 0x03):
        t = ((a + 4) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)
        if op == 0x03:
            L.append(f'    cpu.gpr[31] = {link};')
        L.append(f'    tk = true; tg = (seg & 0xF0000000u) | 0x{t & 0x0FFFFFFF:x}u;')
        L.extend(commit(31 if op == 0x03 else 0))
    else:
        cond = {0x04: f'{g(rs)} == {g(rt)}', 0x05: f'{g(rs)} != {g(rt)}',
                0x06: f'static_cast<int32_t>({g(rs)}) <= 0', 0x07: f'static_cast<int32_t>({g(rs)}) > 0'}[op]
        L.append(f'    tk = {cond}; tg = seg | 0x{(a + 4 + (sext16(imm) << 2)) & 0x1FFFFFFF:x}u;')
        L.extend(commit(0))
    return L


def static_target(w, a):
    op, rs, rt, rd, sa, fn, imm = fields(w)
    if op == 0:
        return None
    if op in (0x02, 0x03):
        return ((a + 4) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)
    return (a + 4 + (sext16(imm) << 2)) & 0x1FFFFFFF


def load_overrides():
    """tools/iop/native_overrides.txt: `<module ident> <offset hex> <name>` = IRX functions replaced by native C++
    (ps2xIOP/src/native/iop_native_overrides.cpp); the compiled code hands control to the dispatcher there."""
    path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'native_overrides.txt')
    result = {}
    if os.path.exists(path):
        for line in open(path):
            parts = line.split('#')[0].split()
            if len(parts) >= 2:
                result.setdefault(parts[0], set()).add(int(parts[1], 16))
    return result


OVERRIDES = load_overrides()


def gen_module(name, base, words, out):
    n = len(words)
    stub = [False] * n
    for i in range(n - 1):
        if words[i] == 0x03E00008 and (words[i + 1] & 0xFFFF0000) == 0x24000000:
            stub[i] = True
    module = name.rsplit('_', 1)[0]  # ident without the base suffix
    for offset in OVERRIDES.get(module, ()):
        if offset % 4 == 0 and offset // 4 < n:
            stub[offset // 4] = True     # native override: hand over like an import stub
    fn = f'iopn_{name}'
    chunks = (n + CHUNK - 1) // CHUNK
    L = [f'// generated by tools/iop/iopn_gen.py from {name} (base 0x{base:x}, {n} words) - do not edit',
         '#include "native/iop_native_support.h"', '', 'namespace ps2x::iop::detail', '{', 'namespace', '{']
    for c in range(chunks):
        lo, hi = c * CHUNK, min(n, (c + 1) * CHUNK)
        clo, chi = base + lo * 4, base + hi * 4

        def go(addr):
            """transfer to addr (cpu.pc already holds it)"""
            if clo <= addr < chi:
                return f'goto L{(addr - base) // 4:x};'
            return 'return n;'

        def is_delay(i):
            return i > 0 and is_branch(words[i - 1]) and not stub[i - 1]

        L.append(f'uint32_t chunk{c}(IopCpuState &cpu, IopMemory &memory, uint32_t budget, const uint32_t seg, bool &stop)')
        L.append('{')
        L.append('    uint32_t n = 0;')
        L.append('    bool tk = false;')
        L.append('    uint32_t tg = 0;')
        L.append('    (void)tk; (void)tg;')
        L.append('dispatch:')
        L.append('    if (n >= budget) { stop = true; return n; }')
        L.append(f'    switch ((cpu.pc & 0x1FFFFFFFu) - 0x{clo:x}u)')
        L.append('    {')
        for i in range(lo, hi):
            L.append(f'    case 0x{(i - lo) * 4:x}u: goto {"D" if is_delay(i) else "L"}{i:x};')
        L.append('    default: return n;')
        L.append('    }')
        for i in range(lo, hi):
            w = words[i]
            a = base + i * 4
            if is_delay(i):
                # entered directly (not after its branch): an ordinary instruction
                L.append(f'D{i:x}:')
                L.extend(emit(w, a, False))
                L.append(f'    cpu.pc = seg | 0x{a + 4:x}u;')
                L.append(f'    {go(a + 4) if i + 1 < hi else "return n;"}')
                continue
            L.append(f'L{i:x}:')
            if stub[i]:
                L.append(f'    cpu.pc = seg | 0x{a:x}u; stop = true; return n;')
                continue
            if is_branch(w):
                L.extend(emit_branch(w, a))
                if i + 1 < n:
                    d = words[i + 1]
                    if is_branch(d):  # branch in a delay slot: hand over to the interpreter
                        L.append(f'    cpu.pc = seg | 0x{a:x}u; stop = true; return n - 1;')
                        continue
                    L.extend(emit(d, a + 4, True))
                L.append('    if (tk) {')
                L.append('        cpu.pc = tg;')
                L.append('        if (n >= budget) { stop = true; return n; }')
                t = static_target(w, a)
                if t is not None:
                    L.append(f'        {go(t)}')
                else:
                    L.append('        goto dispatch;')
                L.append('    }')
                L.append(f'    cpu.pc = seg | 0x{a + 8:x}u;')
                L.append('    if (n >= budget) { stop = true; return n; }')
                L.append(f'    {go(a + 8) if i + 2 < hi else "return n;"}')
                continue
            L.extend(emit(w, a, False))
            if i + 1 == hi:
                L.append(f'    cpu.pc = seg | 0x{a + 4:x}u;')
                L.append('    return n;')
        L.append('}')
        L.append('')
    L.append('using Chunk = uint32_t (*)(IopCpuState &, IopMemory &, uint32_t, uint32_t, bool &);')
    L.append('const Chunk kChunks[] = {' + ', '.join(f'chunk{c}' for c in range(chunks)) + '};')
    L.append('}')
    L.append('')
    L.append(f'uint32_t {fn}(IopCpuState &cpu, IopMemory &memory, uint32_t budget)')
    L.append('{')
    L.append('    const uint32_t seg = cpu.pc & 0xE0000000u;')
    L.append('    cpu.exception = false;')
    L.append('    cpu.yielded = false;')
    L.append('    uint32_t n = 0;')
    L.append('    while (n < budget)')
    L.append('    {')
    L.append(f'        const uint32_t offset = (cpu.pc & 0x1FFFFFFFu) - 0x{base:x}u;')
    L.append(f'        if (offset >= 0x{n * 4:x}u || (offset & 3u) != 0u || (cpu.pc & 0xE0000000u) != seg)')
    L.append('            return n;')
    L.append('        bool stop = false;')
    L.append(f'        const uint32_t ran = kChunks[offset / {CHUNK * 4}u](cpu, memory, budget - n, seg, stop);')
    L.append('        n += ran;')
    L.append('        if (stop || ran == 0u)')
    L.append('            return n;')
    L.append('    }')
    L.append('    return n;')
    L.append('}')
    L.append('}')
    out.write('\n'.join(L) + '\n')
    return fn


def main():
    dump, outdir = sys.argv[1], sys.argv[2]
    os.makedirs(outdir, exist_ok=True)
    seen = {}
    for line in open(os.path.join(dump, 'modules.txt')):
        parts = line.split()
        if len(parts) != 4:
            continue
        name, base, size, h = parts[0], int(parts[1], 16), int(parts[2], 16), int(parts[3], 16)
        seen[(name, base)] = (size, h)   # the last load of a module at a base wins
    entries = []
    for (name, base), (size, h) in sorted(seen.items()):
        data = open(os.path.join(dump, name + '.bin'), 'rb').read()
        if len(data) != size:
            print(f'skip {name}: dump has {len(data)} bytes, list says {size}')
            continue
        words = list(struct.unpack(f'<{size // 4}I', data[:size // 4 * 4]))
        ident = f'{name}_{base:x}'
        with open(os.path.join(outdir, f'iopn_{ident}.cpp'), 'w', newline='\n') as f:
            fn = gen_module(ident, base, words, f)
        entries.append((name, base, size, h, fn))
        print(f'{name}: base 0x{base:x}, {len(words)} instructions')
    with open(os.path.join(outdir, 'iopn_registry.cpp'), 'w', newline='\n') as f:
        f.write('// generated by tools/iop/iopn_gen.py - do not edit\n#include "native/iop_native.h"\n\n')
        f.write('namespace ps2x::iop::detail\n{\n')
        for e in entries:
            f.write(f'uint32_t {e[4]}(IopCpuState &, IopMemory &, uint32_t);\n')
        f.write('\nnamespace\n{\nconst IopNativeModule kModules[] = {\n')
        for name, base, size, h, fn in entries:
            f.write(f'    {{"{name}", 0x{base:x}u, 0x{size:x}u, 0x{h:x}ull, &{fn}}},\n')
        if not entries:
            f.write('    {nullptr, 0u, 0u, 0ull, nullptr},\n')
        f.write('};\n}\n\n')
        f.write('const IopNativeModule *iopNativeModules(size_t &count)\n{\n')
        f.write(f'    count = {len(entries)};\n    return kModules;\n}}\n}}\n')


if __name__ == '__main__':
    main()
