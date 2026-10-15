"""Native VU1 block generator.

usage: python -I tools/vu1/vu1n_gen.py <out dir> <micro-memory dir or .bin files...> [--heads heads.txt] [--parts N]

Reads the captured 16 KB VU1 micro-memories (GOW_VU1_CAPTURA), splits them into basic blocks (same rule as
VU1Interpreter's nativeExtent in ps2_vu1_native.inl) and writes straight-line C++ for each distinct (pc, words) block:
immediate semantics, no cycle model, MAC flags only where they can be observed. Output: vu1n_part<k>.cpp. The exact engine
(ps2_vu1_core.cpp) remains the fallback for every block that is not here and the oracle for GOW_VU1N_VERIFY.
heads.txt (optional): extra entry pcs (hex, one per line), e.g. misses logged by GOW_VU1N_DIAG.
"""
import os
import struct
import sys

BRANCH_OPS = {0x20, 0x21, 0x24, 0x25, 0x28, 0x29, 0x2C, 0x2D, 0x2E, 0x2F}
REV4 = [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
CODE_SIZE = 16384


def fnv_block(pc, words):
    h = 1469598103934665603
    for w in [pc] + list(words):
        for i in range(4):
            h = ((h ^ ((w >> (i * 8)) & 0xFF)) * 1099511628211) & 0xFFFFFFFFFFFFFFFF
    return h


def sx(v, bits):
    v &= (1 << bits) - 1
    return v - (1 << bits) if v & (1 << (bits - 1)) else v


def is_branch(l, u):
    return not (u >> 31) and (l >> 25) in BRANCH_OPS


def extent(code, pc):
    """Pairs (lower, upper) of the block starting at pc, same rule as nativeExtent()."""
    out = []
    p = pc
    while p + 8 <= CODE_SIZE and len(out) < 64:
        l, u = struct.unpack_from('<II', code, p)
        if l == 0 and u == 0:
            break
        out.append((l, u))
        if (u >> 28) & 1 or (u >> 27) & 1:
            break
        if is_branch(l, u) or (u >> 30) & 1:
            if p + 16 <= CODE_SIZE:
                dl, du = struct.unpack_from('<II', code, p + 8)
                if not (dl == 0 and du == 0):
                    out.append((dl, du))
            break
        p += 8
    return out


def heads_of(code, extra_heads):
    heads = set(extra_heads)
    pairs = []
    for i in range(CODE_SIZE // 8):
        l, u = struct.unpack_from('<II', code, i * 8)
        pairs.append((l, u))
    for i, (l, u) in enumerate(pairs):
        if l == 0 and u == 0:
            continue
        pc = i * 8
        if i == 0 or pairs[i - 1] == (0, 0):
            heads.add(pc)
        if is_branch(l, u):
            op = l >> 25
            if op not in (0x24, 0x25):
                heads.add((pc + 8 + sx(l, 11) * 8) & 0x3FFF)
            heads.add((pc + 16) & 0x3FFF)
        if (u >> 30) & 1:
            heads.add((pc + 16) & 0x3FFF)
        if (u >> 28) & 1 or (u >> 27) & 1:
            heads.add((pc + 8) & 0x3FFF)
    return heads


# ---------------------------------------------------------------------------------------------------------------------
# upper (FMAC) decode

def classify(u):
    """(kind, source, toAcc, bc) like vu1c::classify, plus special kinds."""
    op = u & 0x3F
    if op < 0x3C:
        c = op
        if c <= 0x03: return ('add', 'bc', False, c & 3)
        if c <= 0x07: return ('sub', 'bc', False, c & 3)
        if c <= 0x0B: return ('madd', 'bc', False, c & 3)
        if c <= 0x0F: return ('msub', 'bc', False, c & 3)
        if c <= 0x13: return ('max', 'bc', False, c & 3)
        if c <= 0x17: return ('mini', 'bc', False, c & 3)
        if c <= 0x1B: return ('mul', 'bc', False, c & 3)
        table = {0x1C: ('mul', 'q'), 0x1D: ('max', 'i'), 0x1E: ('mul', 'i'), 0x1F: ('mini', 'i'),
                 0x20: ('add', 'q'), 0x21: ('madd', 'q'), 0x22: ('add', 'i'), 0x23: ('madd', 'i'),
                 0x24: ('sub', 'q'), 0x25: ('msub', 'q'), 0x26: ('sub', 'i'), 0x27: ('msub', 'i'),
                 0x28: ('add', 'v'), 0x29: ('madd', 'v'), 0x2A: ('mul', 'v'), 0x2B: ('max', 'v'),
                 0x2C: ('sub', 'v'), 0x2D: ('msub', 'v'), 0x2E: ('opmsub', 'v'), 0x2F: ('mini', 'v')}
        if c in table:
            return (table[c][0], table[c][1], False, 0)
        return ('other', 'v', False, 0)
    sp = (u & 3) | ((u >> 4) & 0x7C)
    if sp <= 0x03: return ('add', 'bc', True, sp & 3)
    if sp <= 0x07: return ('sub', 'bc', True, sp & 3)
    if sp <= 0x0B: return ('madd', 'bc', True, sp & 3)
    if sp <= 0x0F: return ('msub', 'bc', True, sp & 3)
    if 0x10 <= sp <= 0x13: return ('itof', (0, 4, 12, 15)[sp & 3], False, 0)
    if 0x14 <= sp <= 0x17: return ('ftoi', (0, 4, 12, 15)[sp & 3], False, 0)
    if 0x18 <= sp <= 0x1B: return ('mul', 'bc', True, sp & 3)
    sp_table = {0x1C: ('mul', 'q'), 0x1E: ('mul', 'i'), 0x20: ('add', 'q'), 0x21: ('madd', 'q'), 0x22: ('add', 'i'),
                0x23: ('madd', 'i'), 0x24: ('sub', 'q'), 0x25: ('msub', 'q'), 0x26: ('sub', 'i'), 0x27: ('msub', 'i'),
                0x28: ('add', 'v'), 0x29: ('madd', 'v'), 0x2A: ('mul', 'v'), 0x2C: ('sub', 'v'), 0x2D: ('msub', 'v'),
                0x2E: ('opmula', 'v')}
    if sp == 0x1D: return ('abs', None, False, 0)
    if sp == 0x1F: return ('clip', None, False, 0)
    if sp in (0x2F, 0x30): return ('nop', None, False, 0)
    if sp in sp_table:
        return (sp_table[sp][0], sp_table[sp][1], True, 0)
    return ('other', 'v', False, 0)


def upper_info(u):
    """(writes_vf set, reads_vf set, writes_mac, reads_q)"""
    kind, src, toacc, bc = classify(u)
    dest = (u >> 21) & 0xF
    ft, fs, fd = (u >> 16) & 31, (u >> 11) & 31, (u >> 6) & 31
    w, r = set(), set()
    if kind == 'nop' or dest == 0 and kind not in ('clip',):
        return w, r, False, False
    if kind in ('add', 'sub', 'madd', 'msub', 'mul', 'max', 'mini'):
        r.add(fs)
        if src in ('bc', 'v'):
            r.add(ft)
        if not toacc:
            w.add(fd)
    elif kind in ('itof', 'ftoi', 'abs'):
        r.add(fs)
        w.add(ft)
    elif kind == 'clip':
        r.update((fs, ft))
    elif kind in ('opmsub', 'opmula', 'other'):
        r.update((fs, ft))
        if not toacc:
            w.add(fd)
    writes_mac = kind in ('add', 'sub', 'madd', 'msub', 'mul') and dest != 0
    reads_q = src == 'q'
    return {x for x in w if x}, r, writes_mac, reads_q


def emit_upper(u, pc, idx, mac_var, clip_var, prev_clip, clean=frozenset()):
    kind, src, toacc, bc = classify(u)
    dest = (u >> 21) & 0xF
    ft, fs, fd = (u >> 16) & 31, (u >> 11) & 31, (u >> 6) & 31
    m = REV4[dest]
    L = []
    if kind == 'nop':
        return L
    if kind == 'clip':
        return [f"const uint32_t {clip_var} = vu1n::clipVal(s, {fs}, {ft}, {prev_clip});"]
    if dest == 0:
        return L
    if kind == 'itof':
        return [f"vu1n::itof<{src}, {m}>(s, {fs}, {ft});"] if ft else L
    if kind == 'ftoi':
        return [f"vu1n::ftoi<{src}, {m}>(s, {fs}, {ft});"] if ft else L
    if kind == 'abs':
        return [f"vu1n::absOp<{m}>(s, {fs}, {ft});"] if ft else L
    if kind in ('opmsub', 'opmula', 'other'):
        return [f"VU1NativeAccess::callUpper(n, {pc}u, 0x{u:08x}u);"]
    def opnd(r):
        return f"vu1n::ld(s, {r})" if r == 0 or r in clean else f"vu1n::ldn(s, {r})"
    a = opnd(fs)
    if src == 'bc':
        b = f"vu1n::bc<{bc}>({opnd(ft)})"
    elif src == 'q':
        b = "_mm_set1_ps(s.q)"
    elif src == 'i':
        b = "_mm_set1_ps(s.i)"
    else:
        b = opnd(ft)
    acc = "vu1n::ldAcc(s)"
    if kind == 'add':
        r = f"_mm_add_ps({a}, {b})"
    elif kind == 'sub':
        r = f"_mm_sub_ps({a}, {b})"
    elif kind == 'mul':
        r = f"_mm_mul_ps({a}, {b})"
    elif kind == 'madd':
        r = f"vu1n::madd<false>({acc}, {a}, {b})"
    elif kind == 'msub':
        r = f"vu1n::madd<true>({acc}, {a}, {b})"
    elif kind == 'max':
        r = f"_mm_max_ps({a}, {b})"
    else:
        r = f"_mm_min_ps({a}, {b})"
    target = "s.acc" if toacc else f"s.vf[{fd}]"
    out = [f"__m128 r{idx} = {r};"]
    if kind in ('add', 'sub', 'mul', 'madd', 'msub') and mac_var:
        out.append(f"const uint32_t {mac_var} = vu1n::macVal<{m}>(r{idx});")
        out.append(f"const __m128 q{idx} = r{idx};  // unclamped: flags computed later if it outlives the block")
    if kind not in ('max', 'min', 'mini'):
        out.append(f"r{idx} = vu1n::clampv(r{idx});")
    if toacc or fd:
        out.append(f"vu1n::stf<{m}>({target}, r{idx});")
    return out


# ---------------------------------------------------------------------------------------------------------------------
# lower decode

def lower_fields(l):
    return dict(dest=(l >> 21) & 0xF, ft=(l >> 16) & 31, fs=(l >> 11) & 31, vid=(l >> 6) & 31,
                imm11=sx(l, 11), imm15=(l & 0x7FF) | ((l >> 10) & 0x7800), imm24=l & 0xFFFFFF)


def lower_special(l):
    return ((l & 3) | ((l >> 4) & 0x7C)) if (l & 0x3F) >= 0x3C else None


def lower_info(l):
    """Describe a lower instruction.

    returns dict: vfw set, vfr set, reads_mac, reads_clip, writes_q, vi_delay_reg (reg whose write delays a following
    branch read), native (bool), branch (kind or None), vi_reads set"""
    op = l >> 25
    f = lower_fields(l)
    info = dict(vfw=set(), vfr=set(), reads_mac=False, reads_clip=False, writes_q=False, delay=0, native=True,
                branch=None, calls_out=False, vi_reads=set())
    if l == 0 or l == 0x8000033C:
        return info
    ft, fs, vid = f['ft'], f['fs'], f['vid']
    if op == 0x00:
        info['vfw'] = {ft}
        info['vi_reads'] = {fs}
    elif op == 0x01:
        info['vfr'] = {fs}
        info['vi_reads'] = {ft}
    elif op in (0x04, 0x05):
        info['vi_reads'] = {fs, ft} if op == 0x05 else {fs}
    elif op in (0x08, 0x09):
        info['delay'] = ft
        info['vi_reads'] = {fs}
    elif op in (0x10, 0x11, 0x12, 0x13, 0x1C):
        info['reads_clip'] = op != 0x11
    elif op in (0x18, 0x1A, 0x1B):
        info['reads_mac'] = True
        info['vi_reads'] = {fs}
    elif op in BRANCH_OPS:
        info['branch'] = op
        info['vi_reads'] = {fs, ft} if op in (0x28, 0x29) else ({fs} if op in (0x24, 0x25, 0x2C, 0x2D, 0x2E, 0x2F) else set())
    elif op == 0x40:
        fn = l & 0x3F
        if fn in (0x30, 0x31, 0x34, 0x35):
            info['delay'] = vid
            info['vi_reads'] = {fs, ft}
        elif fn == 0x32:
            info['delay'] = ft
            info['vi_reads'] = {fs}
        elif fn >= 0x3C:
            sp = lower_special(l)
            if sp in (0x30, 0x31):
                info['vfw'] = {ft}
                info['vfr'] = {fs}
            elif sp in (0x34, 0x36):
                info['vfw'] = {ft}
                info['delay'] = fs
                info['vi_reads'] = {fs}
            elif sp in (0x35, 0x37):
                info['vfr'] = {fs}
                info['delay'] = ft
                info['vi_reads'] = {ft}
            elif sp == 0x38:
                info['vfr'] = {fs, ft}
                info['writes_q'] = True
            elif sp == 0x39:
                info['vfr'] = {ft}
                info['writes_q'] = True
            elif sp == 0x3A:
                info['vfr'] = {fs, ft}
                info['writes_q'] = True
            elif sp == 0x3B:
                pass
            elif sp == 0x3C:
                info['vfr'] = {fs}
                info['delay'] = ft
            elif sp == 0x3D:
                info['vfw'] = {ft}
                info['vi_reads'] = {fs}
            elif sp in (0x3E, 0x3F):
                info['vi_reads'] = {fs, ft}
            elif sp == 0x64:
                info['vfw'] = {ft}
            elif sp in (0x68, 0x69, 0x6C):
                info['vi_reads'] = {fs} if sp == 0x6C else set()
            else:
                info['native'] = False
                info['calls_out'] = True
                info['vfr'] = {fs, ft}
                info['vfw'] = {ft}
        else:
            info['native'] = False
            info['calls_out'] = True
    else:
        info['native'] = False
        info['calls_out'] = True
        info['vfr'] = {fs, ft}
        info['vfw'] = {ft}
    info['vfw'] = {x for x in info['vfw'] if x}
    return info


def dest_comp(dest):
    return 0 if dest & 8 else 1 if dest & 4 else 2 if dest & 2 else 3


def emit_lower(l, pc, upper, bkp, mac_expr, clip_expr, clip_var):
    """Lines for a non-branch lower op. bkp: dict reg->variable name for branch backups (unused here)."""
    op = l >> 25
    f = lower_fields(l)
    dest, ft, fs, vid, imm11 = f['dest'], f['ft'], f['fs'], f['vid'], f['imm11']
    m = REV4[dest]
    if l == 0 or l == 0x8000033C:
        return []
    L = []
    def vi_set(reg, expr):
        return [f"s.vi[{reg}] = {expr};"] if reg else []
    if op == 0x00:
        if ft:
            L.append(f"{{ uint32_t a = vu1n::qaddr(n, s.vi[{fs}] + {imm11}); vu1n::stf<{m}>(s.vf[{ft}], vu1n::ldq(n, a)); }}")
        return L
    if op == 0x01:
        return [f"{{ uint32_t a = vu1n::qaddr(n, s.vi[{ft}] + {imm11}); vu1n::stq<{m}>(n, a, vu1n::ld(s, {fs})); }}"]
    if op == 0x04:
        return vi_set(ft, f"vu1n::ldWord(n, vu1n::qaddr(n, s.vi[{fs}] + {imm11}), {dest_comp(dest)})")
    if op == 0x05:
        return [f"vu1n::stWords(n, vu1n::qaddr(n, s.vi[{fs}] + {imm11}), s.vi[{ft}], {dest});"]
    if op == 0x08:
        return vi_set(ft, f"vu1n::sx16(s.vi[{fs}] + {f['imm15']})")
    if op == 0x09:
        return vi_set(ft, f"vu1n::sx16(s.vi[{fs}] - {f['imm15']})")
    if op == 0x10:
        return vi_set(1, f"(({clip_expr} & 0xFFFFFFu) == 0x{f['imm24']:x}u) ? 1 : 0")
    if op == 0x11:
        return [f"const uint32_t {clip_var} = 0x{f['imm24']:x}u;"]
    if op == 0x12:
        return vi_set(1, f"(({clip_expr} & 0x{f['imm24']:x}u) != 0u) ? 1 : 0")
    if op == 0x13:
        return vi_set(1, f"(({clip_expr} | 0x{f['imm24']:x}u) == 0xFFFFFFu) ? 1 : 0")
    if op == 0x18:
        return vi_set(ft, f"(({mac_expr} & 0xFFFFu) == (uint32_t)(uint16_t)s.vi[{fs}]) ? 1 : 0")
    if op == 0x1A:
        return vi_set(ft, f"(int32_t)({mac_expr} & (uint32_t)(uint16_t)s.vi[{fs}])")
    if op == 0x1B:
        return vi_set(ft, f"(int32_t)({mac_expr} | (uint32_t)(uint16_t)s.vi[{fs}])")
    if op == 0x1C:
        return vi_set(ft, f"(int32_t)({clip_expr} & 0x0FFFu)")
    if op == 0x40:
        fn = l & 0x3F
        if fn == 0x30:
            return vi_set(vid, f"vu1n::sx16(s.vi[{fs}] + s.vi[{ft}])")
        if fn == 0x31:
            return vi_set(vid, f"vu1n::sx16(s.vi[{fs}] - s.vi[{ft}])")
        if fn == 0x32:
            return vi_set(ft, f"vu1n::sx16(s.vi[{fs}] + {sx((l >> 6) & 0x1F, 5)})")
        if fn == 0x34:
            return vi_set(vid, f"s.vi[{fs}] & s.vi[{ft}]")
        if fn == 0x35:
            return vi_set(vid, f"s.vi[{fs}] | s.vi[{ft}]")
        sp = lower_special(l)
        if sp == 0x30:
            return [f"vu1n::stf<{m}>(s.vf[{ft}], vu1n::ld(s, {fs}));"] if ft else []
        if sp == 0x31:
            return [f"{{ __m128 v = vu1n::ld(s, {fs}); vu1n::stf<{m}>(s.vf[{ft}], _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 3, 2, 1))); }}"] if ft else []
        if sp == 0x34:  # LQI
            out = []
            if ft:
                out.append(f"{{ uint32_t a = vu1n::qaddr(n, (uint16_t)s.vi[{fs}]); vu1n::stf<{m}>(s.vf[{ft}], vu1n::ldq(n, a)); }}")
            else:
                pass
            if fs:
                out.append(f"s.vi[{fs}] = vu1n::sx16(s.vi[{fs}] + 1);")
            return out
        if sp == 0x35:  # SQI
            out = [f"{{ uint32_t a = vu1n::qaddr(n, (uint16_t)s.vi[{ft}]); vu1n::stq<{m}>(n, a, vu1n::ld(s, {fs})); }}"]
            if ft:
                out.append(f"s.vi[{ft}] = vu1n::sx16(s.vi[{ft}] + 1);")
            return out
        if sp == 0x36:  # LQD
            out = []
            if fs:
                out.append(f"s.vi[{fs}] = vu1n::sx16(s.vi[{fs}] - 1);")
            if ft:
                out.append(f"{{ uint32_t a = vu1n::qaddr(n, (uint16_t)s.vi[{fs}]); vu1n::stf<{m}>(s.vf[{ft}], vu1n::ldq(n, a)); }}")
            return out
        if sp == 0x37:  # SQD
            out = []
            if ft:
                out.append(f"s.vi[{ft}] = vu1n::sx16(s.vi[{ft}] - 1);")
            out.append(f"{{ uint32_t a = vu1n::qaddr(n, (uint16_t)s.vi[{ft}]); vu1n::stq<{m}>(n, a, vu1n::ld(s, {fs})); }}")
            return out
        fsf, ftf = (l >> 21) & 3, (l >> 23) & 3
        if sp == 0x38:
            return [f"vu1n::divOp(s, {fs}, {fsf}, {ft}, {ftf});"]
        if sp == 0x39:
            return [f"vu1n::sqrtOp(s, {ft}, {ftf});"]
        if sp == 0x3A:
            return [f"vu1n::rsqrtOp(s, {fs}, {fsf}, {ft}, {ftf});"]
        if sp == 0x3B:
            return []
        if sp == 0x3C:
            return vi_set(ft, f"vu1n::compBits(s, {fs}, {fsf})")
        if sp == 0x3D:
            return [f"vu1n::stf<{m}>(s.vf[{ft}], vu1n::fromInt(vu1n::sx16(s.vi[{fs}])));"] if ft else []
        if sp == 0x3E:
            return vi_set(ft, f"vu1n::ldWord(n, vu1n::qaddr(n, (uint16_t)s.vi[{fs}]), {dest_comp(dest)})")
        if sp == 0x3F:
            return [f"vu1n::stWords(n, vu1n::qaddr(n, (uint16_t)s.vi[{fs}]), s.vi[{ft}], {dest});"]
        if sp == 0x64:
            return [f"vu1n::stf<{m}>(s.vf[{ft}], _mm_set1_ps(s.p));"] if ft else []
        if sp == 0x68:
            return vi_set(ft, "(int32_t)(s.top & 0x3FFu)")
        if sp == 0x69:
            return vi_set(ft, "(int32_t)(s.itop & 0x3FFu)")
        if sp == 0x6C:
            return [f"VU1NativeAccess::xgkick(n, (uint32_t)(uint16_t)s.vi[{fs}]);"]
    return [f"VU1NativeAccess::callLower(n, {pc}u, 0x{l:08x}u, 0x{upper:08x}u);"]


def gen_block(pc0, pairs, tail_out=None):
    """tail_out: list that receives the block's VU1TailDesc (mac pairs, mac masks, clip pairs) when it has one.
    C++ body for a block, or None if the block uses something the native backend does not support."""
    n = len(pairs)
    infos = [lower_info(l) if not (u >> 31) else lower_info(0) for (l, u) in pairs]
    uinfo = [upper_info(u) for (l, u) in pairs]
    # structural checks
    for i, (l, u) in enumerate(pairs):
        br = is_branch(l, u)
        if br:
            if i != n - 2:
                return None            # branch must be the second to last pair (delay slot last)
            if (u >> 30) & 1 or (u >> 28) & 1 or (u >> 27) & 1:
                return None
            if is_branch(*pairs[n - 1]):
                return None            # branch in a delay slot
    last_is_branch_block = n >= 2 and is_branch(*pairs[n - 2])
    if n >= 1 and is_branch(*pairs[n - 1]) and not last_is_branch_block:
        return None                     # branch without delay slot
    # Flag model of the exact engine: an FMAC / CLIP / FCSET issued at pair j becomes visible to flag readers 4 cycles later
    # (kFmacLatency, on the exact engine's stall-model cycles n.cyc, computed at block entry from the pipeline state the
    # previous block left). Flags older than the block come from the exact engine's
    # flag pipeline as visible at the reader's issue cycle (VU1NativeAccess::macAt / clipAt): writers of the previous block
    # (or of exact-stepped pairs) that are still in flight stay invisible until their latency has passed. At a block exit the
    # writers that can still become visible are queued in that pipeline (pushMac / pushClip) instead of being committed:
    # committing the newest one at once let a loop read the flags of its last pair too early (the shadow-volume culling loop
    # at 0x3C38 tests with FMEQ the sign of the MSUB issued exactly 4 pairs earlier, across the loop branch).
    FLAT = 4
    mac_w = [i for i in range(n) if uinfo[i][2]]
    clip_w = [i for i in range(n) if classify(pairs[i][1])[0] == 'clip' or (not (pairs[i][1] >> 31) and (pairs[i][0] >> 25) == 0x11)]
    for i in clip_w:
        if classify(pairs[i][1])[0] == 'clip' and not (pairs[i][1] >> 31) and (pairs[i][0] >> 25) == 0x11:
            return None

    def visible(i, writers, prefix, entry):
        """Newest earlier writer already committed when pair i issues: pair distance >= 4 always, nearer ones only when the
        exact engine's stall model (n.cyc) pushed pair i far enough."""
        expr = entry
        for j in [j for j in writers if j < i]:        # oldest -> newest; the newest candidate is tested first
            if i - j >= FLAT:
                expr = f"{prefix}{j}"
            else:
                expr = f"((n.cyc[{i}] - n.cyc[{j}] >= {FLAT}) ? {prefix}{j} : {expr})"
        return expr

    def mac_src(i):
        return visible(i, mac_w, "m", f"VU1NativeAccess::macAt(n, n.cyc[{i}])")

    def clip_src(i):
        return visible(i, clip_w, "c", f"VU1NativeAccess::clipAt(n, n.cyc[{i}])")

    def clip_prev(i):
        c = [j for j in clip_w if j < i]
        return f"c{c[-1]}" if c else "VU1NativeAccess::clipChain(n)"

    def flush_final(i):
        """Block end: the newest MAC / clip writer is queued with the block's tail record (n.tail); the older writers that
        can still be the visible one after the exit (successor in the last three pairs) are only stored there, the reader
        decides (VU1FlagRing::tailVisible)."""
        out, desc = [], {"m": [], "c": []}
        for writers, prefix in ((mac_w, "m"), (clip_w, "c")):
            w = [j for j in writers if j <= i]
            older = [j for k, j in enumerate(w[:-1]) if i - w[k + 1] < FLAT - 1]
            desc[prefix] = older
            for k, j in enumerate(older):
                out.append(f"n.tail->q[{k}] = q{j};" if prefix == "m" else f"n.tail->c[{k}] = c{j};")
        has_tail = bool(desc["m"] or desc["c"])
        tail = "n.tail" if has_tail else "nullptr"
        if mac_w and mac_w[-1] <= i:
            j = mac_w[-1]
            out.append(f"VU1NativeAccess::pushMacRaw(n, n.cyc[{j}], q{j}, {REV4[(pairs[j][1] >> 21) & 0xF]}u, {tail});")
        if clip_w and clip_w[-1] <= i:
            j = clip_w[-1]
            out.append(f"VU1NativeAccess::pushClipTail(n, n.cyc[{j}], c{j}, {tail});")
        if has_tail and tail_out is not None:
            tail_out.append((desc["m"], [REV4[(pairs[j][1] >> 21) & 0xF] for j in desc["m"]], desc["c"]))
        return out

    def flush(i):
        """Block exit after pair i (D/T halt): queue every writer that can still be the visible one at or after the exit
        (the last one, and older ones whose successor is not visible yet when the block ends)."""
        out = []
        end = f"n.cyc[{i}] + 1u"
        for writers, prefix, push in ((mac_w, "m", "pushMac"), (clip_w, "c", "pushClip")):
            w = [j for j in writers if j <= i]
            for k, j in enumerate(w):
                if prefix == "m":  # MAC flags of a writer read after the block: computed by the reader (VU1FlagRing)
                    call = f"VU1NativeAccess::pushMacRaw(n, n.cyc[{j}], q{j}, {REV4[(pairs[j][1] >> 21) & 0xF]}u, nullptr);"
                else:
                    call = f"VU1NativeAccess::{push}(n, n.cyc[{j}], {prefix}{j});"
                if k == len(w) - 1:
                    out.append(call)
                elif i - w[k + 1] < FLAT - 1:
                    # visible after the exit only if its successor is not yet: issue-cycle gaps are at least the pair
                    # distance (stalls only widen them), so writers followed by one 3+ pairs before the end never are
                    out.append(f"if (n.cyc[{w[k + 1]}] + {FLAT}u > {end}) {call}")
        return out

    lines = []
    clean_regs = set()          # vf registers known to hold normalised (finite) values: FMAC results of this block
    for i, (l, u) in enumerate(pairs):
        pc = pc0 + 8 * i
        clean_i = frozenset(clean_regs - infos[i]['vfw'])
        li, (uw, ur, umac, uq) = infos[i], uinfo[i]
        iBit = bool(u >> 31)
        lower_first = False
        both = False
        if not iBit:
            h1 = bool(uw & li['vfr'])            # upper writes what lower reads (lower must read old)
            h2 = bool(li['vfw'] & ur)            # lower writes what upper reads (upper must read old)
            h3 = li['writes_q'] and uq           # lower writes Q, upper reads old Q
            if (h1 and (h2 or h3)):
                return None
            lower_first = h1
        # backup of VI for a branch in the next pair
        backup = []
        if i + 1 < n and li['delay']:
            nl, nu = pairs[i + 1]
            if is_branch(nl, nu):
                nf = lower_fields(nl)
                regs = lower_info(nl)['vi_reads']
                if li['delay'] in regs:
                    backup.append(f"const int32_t vib{i + 1} = s.vi[{li['delay']}];")
        lines.append(f"// pair {i} pc=0x{pc:04x} lower={l:08x} upper={u:08x}")
        lines.extend(backup)
        if is_branch(l, u):
            op = l >> 25
            f = lower_fields(l)
            ft, fs, imm = f['ft'], f['fs'], f['imm11']
            prev_backup = None
            def rd(reg):
                if i > 0 and infos[i - 1]['delay'] == reg and reg != 0:
                    return f"vib{i}"
                return f"s.vi[{reg}]"
            tgt = (pc + 8 + imm * 8) & 0x3FFF
            if op == 0x20:
                lines.append("bool taken = true;")
                lines.append(f"uint32_t target = {tgt}u;")
            elif op == 0x21:
                if ft:
                    lines.append(f"s.vi[{ft}] = {(pc + 16) // 8};")
                lines.append("bool taken = true;")
                lines.append(f"uint32_t target = {tgt}u;")
            elif op == 0x24:
                lines.append("bool taken = true;")
                lines.append(f"uint32_t target = (((uint32_t)(uint16_t)s.vi[{fs}]) * 8u) & 0x3FFFu;")
            elif op == 0x25:
                lines.append(f"uint32_t target = (((uint32_t)(uint16_t)s.vi[{fs}]) * 8u) & 0x3FFFu;")
                if ft:
                    lines.append(f"s.vi[{ft}] = {(pc + 16) // 8};")
                lines.append("bool taken = true;")
            else:
                cmp = {0x28: "==", 0x29: "!="}.get(op)
                if cmp:
                    cond = f"(int16_t){rd(fs)} {cmp} (int16_t){rd(ft)}"
                else:
                    cmp = {0x2C: "< 0", 0x2D: "> 0", 0x2E: "<= 0", 0x2F: ">= 0"}[op]
                    cond = f"(int16_t){rd(fs)} {cmp}"
                lines.append(f"bool taken = {cond};")
                lines.append(f"uint32_t target = {tgt}u;")
            # upper still executes in the branch pair
            lines.extend(emit_upper(u, pc, i, f"m{i}" if i in mac_w else None, f"c{i}", clip_prev(i), clean_i))
            continue
        # ordinary pair
        up = emit_upper(u, pc, i, f"m{i}" if i in mac_w else None, f"c{i}", clip_prev(i), clean_i)
        lo = [] if iBit else emit_lower(l, pc, u, None, mac_src(i), clip_src(i), f"c{i}")
        if iBit:
            lines.extend(up)
            lines.append(f"s.i = vu1n::qnorm(*(const float *)&(const uint32_t &)(0x{l:08x}u)); // I register")
            # (the line above is replaced below to avoid UB)
            lines[-1] = f"{{ const uint32_t bits = 0x{l:08x}u; float imm; std::memcpy(&imm, &bits, 4); s.i = vu1n::qnorm(imm); }}"
        elif lower_first:
            lines.extend(lo)
            lines.extend(up)
        else:
            lines.extend(up)
            lines.extend(lo)
        clean_regs = set(clean_i)
        kind_u = classify(u)[0]
        if kind_u in ('add', 'sub', 'mul', 'madd', 'msub', 'max', 'mini') and ((u >> 21) & 0xF) == 0xF and not classify(u)[2]:
            clean_regs |= {x for x in uw}
        # D/T halt bits
        if (u >> 28) & 1:
            lines.append("if (s.dBitEnabled) { " + " ".join(flush(i)) + f" s.stoppedByD = true; return kVu1nEnded | {(pc + 8) & 0x3FFF}u; }}")
        if (u >> 27) & 1:
            lines.append("if (s.tBitEnabled) { " + " ".join(flush(i)) + f" s.stoppedByT = true; return kVu1nEnded | {(pc + 8) & 0x3FFF}u; }}")
    end_pc = (pc0 + 8 * n) & 0x3FFF
    ebit = any((u >> 30) & 1 for (l, u) in pairs)
    lines.extend(flush_final(n - 1))
    if last_is_branch_block:
        lines.append(f"return taken ? target : {end_pc}u;")
    elif ebit:
        lines.append(f"return kVu1nEnded | {end_pc}u;")
    else:
        lines.append(f"return {end_pc}u;")
    return lines


def main():
    args = sys.argv[1:]
    heads_file = None
    parts = 6
    files = []
    out = args[0]
    i = 1
    while i < len(args):
        if args[i] == '--heads':
            heads_file = args[i + 1]
            i += 2
        elif args[i] == '--parts':
            parts = int(args[i + 1])
            i += 2
        else:
            files.append(args[i])
            i += 1
    inputs = []
    for a in files:
        if os.path.isdir(a):
            inputs += sorted(os.path.join(a, f) for f in os.listdir(a) if f.endswith('.bin'))
        else:
            inputs.append(a)
    extra = set()
    if heads_file and os.path.exists(heads_file):
        for line in open(heads_file):
            line = line.strip()
            if line:
                extra.add(int(line, 16) & 0x3FF8)
    blocks = {}
    unsupported = 0
    for f in inputs:
        code = open(f, 'rb').read()
        if len(code) != CODE_SIZE:
            continue
        for pc in sorted(heads_of(code, extra)):
            pairs = extent(code, pc)
            if not pairs:
                continue
            words = [w for pr in pairs for w in pr]
            key = fnv_block(pc, words)
            if key in blocks:
                continue
            tail = []
            body = gen_block(pc, pairs, tail)
            blocks[key] = (pc, len(pairs), body, tail[0] if tail else None)
            if body is None:
                unsupported += 1
    os.makedirs(out, exist_ok=True)
    texts = [[] for _ in range(parts)]
    regs = [[] for _ in range(parts)]
    count = 0
    for key, (pc, npairs, body, tail) in sorted(blocks.items()):
        if body is None:
            continue
        name = f"b{pc:04x}_{key & 0xFFFFFFFF:08x}"
        part = count % parts
        count += 1
        t = []
        if tail:
            mp, mm, cp = (list(x) + [0] * (3 - len(x)) for x in tail)
            t.append(f"static const VU1TailDesc {name}_tail = {{{len(tail[0])}, {len(tail[2])}, {{{mp[0]}, {mp[1]}, {mp[2]}}}, "
                     f"{{{mm[0]}, {mm[1]}, {mm[2]}}}, {{{cp[0]}, {cp[1]}, {cp[2]}}}}};")
        t += [f"static uint32_t {name}(VU1NativeCtx &n)", "{", "    VU1State &s = *n.s;"]
        t += ["    " + ln for ln in body]
        t += ["}", ""]
        texts[part].append("\n".join(t))
        # bit 16: the block reads flags written before it; only such blocks need exact entry timing (see runNative)
        reads_entry = any("macAt(" in ln or "clipAt(" in ln for ln in body)
        regs[part].append(f"    vu1nRegisterBlock(0x{key:016x}ull, {name}, {npairs | (0x10000 if reads_entry else 0)}u, "
                          f"{'&' + name + '_tail' if tail else 'nullptr'});")
    header = ('// Generated by tools/vu1/vu1n_gen.py from the game\'s VU1 microcode. Do not publish.\n'
              '#include "runtime/ps2_vu1_native.h"\n#include <cmath>\n\n'
              '#if defined(_MSC_VER)\n#pragma float_control(precise, on, push)\n#pragma fp_contract(off)\n#endif\n\n')
    footer = '\n#if defined(_MSC_VER)\n#pragma float_control(pop)\n#endif\n'
    for k in range(parts):
        body = header + "\n".join(texts[k]) + "\nnamespace\n{\n    const bool g_registered = []\n    {\n" + "\n".join(regs[k]) + "\n        return true;\n    }();\n}\n" + footer
        path = os.path.join(out, f"vu1n_part{k}.cpp")
        old = open(path, encoding='utf-8').read() if os.path.exists(path) else None
        if old != body:
            open(path, 'w', encoding='utf-8').write(body)
    print(f"[vu1n_gen] {len(inputs)} images, {len(blocks)} distinct blocks, {count} generated, {unsupported} unsupported")


if __name__ == '__main__':
    main()
