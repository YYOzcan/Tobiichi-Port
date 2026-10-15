"""Sampling profiler for the runner (Windows, no debug build needed): suspends every thread of the process periodically,
reads its instruction pointer and attributes it to a function from the linker map file (link with /MAP).

    python tools/sample_prof.py --exe <path to ps2EntryRunner.exe> [--wait 120] [--secs 20] [--top 40]

--wait: seconds to wait for the process (it is found by its executable path) and then before sampling (e.g. to reach the
heavy part of a zone run). Prints per thread the share of samples and the top functions (self time only).
"""
import argparse
import bisect
import collections
import ctypes
import ctypes.wintypes as wt
import os
import re
import sys
import time

k32 = ctypes.WinDLL('kernel32', use_last_error=True)
psapi = ctypes.WinDLL('psapi', use_last_error=True)

TH32CS_SNAPTHREAD = 0x4
PROCESS_QUERY_INFORMATION = 0x0400
PROCESS_VM_READ = 0x0010
THREAD_ACCESS = 0x0002 | 0x0008 | 0x0040  # suspend/resume, get context, query information
CONTEXT_CONTROL = 0x100001


class THREADENTRY32(ctypes.Structure):
    _fields_ = [('dwSize', wt.DWORD), ('cntUsage', wt.DWORD), ('th32ThreadID', wt.DWORD), ('th32OwnerProcessID', wt.DWORD),
                ('tpBasePri', wt.LONG), ('tpDeltaPri', wt.LONG), ('dwFlags', wt.DWORD)]


CONTEXT_SIZE = 1232
RIP_OFFSET = 0xF8
FLAGS_OFFSET = 0x30


def find_pid(exe):
    exe = os.path.normcase(os.path.abspath(exe))
    arr = (wt.DWORD * 4096)()
    needed = wt.DWORD()
    psapi.EnumProcesses(arr, ctypes.sizeof(arr), ctypes.byref(needed))
    for pid in arr[:needed.value // 4]:
        h = k32.OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, False, pid)
        if not h:
            continue
        buf = ctypes.create_unicode_buffer(1024)
        size = wt.DWORD(1024)
        ok = k32.QueryFullProcessImageNameW(h, 0, buf, ctypes.byref(size))
        k32.CloseHandle(h)
        if ok and os.path.normcase(buf.value) == exe:
            return pid
    return None


def module_base(pid):
    h = k32.OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, False, pid)
    mods = (ctypes.c_void_p * 1)()
    needed = wt.DWORD()
    psapi.EnumProcessModulesEx(h, mods, ctypes.sizeof(mods), ctypes.byref(needed), 3)
    k32.CloseHandle(h)
    return mods[0]


def load_map(path):
    """(rva list, name list) of every function symbol in the map."""
    pref = 0x140000000
    syms = []
    pat = re.compile(r'^\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{16})\s+[f ]', re.I)
    with open(path, errors='replace') as f:
        for line in f:
            if 'Preferred load address is' in line:
                pref = int(line.split()[-1], 16)
            m = pat.match(line)
            if m:
                syms.append((int(m.group(2), 16) - pref, m.group(1)))
    syms.sort()
    return [s[0] for s in syms], [s[1] for s in syms]


def threads_of(pid):
    snap = k32.CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0)
    te = THREADENTRY32()
    te.dwSize = ctypes.sizeof(te)
    out = []
    ok = k32.Thread32First(snap, ctypes.byref(te))
    while ok:
        if te.th32OwnerProcessID == pid:
            out.append(te.th32ThreadID)
        ok = k32.Thread32Next(snap, ctypes.byref(te))
    k32.CloseHandle(snap)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--exe', required=True)
    ap.add_argument('--map')
    ap.add_argument('--wait', type=float, default=0)
    ap.add_argument('--secs', type=float, default=20)
    ap.add_argument('--interval', type=float, default=0.001)
    ap.add_argument('--top', type=int, default=40)
    ap.add_argument('--func', help='also print the hottest instruction addresses (RVA) inside functions matching this text')
    a = ap.parse_args()
    mp = a.map or os.path.splitext(a.exe)[0] + '.map'
    rvas, names = load_map(mp)
    t0 = time.time()
    pid = None
    while pid is None and time.time() - t0 < max(a.wait, 1) + 60:
        pid = find_pid(a.exe)
        if pid is None:
            time.sleep(0.5)
    if pid is None:
        sys.exit('process not found')
    rest = a.wait - (time.time() - t0)
    if rest > 0:
        time.sleep(rest)
    base = module_base(pid)
    ctx = ctypes.create_string_buffer(CONTEXT_SIZE + 16)
    addr = (ctypes.addressof(ctx) + 15) & ~15
    handles = {}
    hist = collections.defaultdict(collections.Counter)
    hot = collections.Counter()
    end = time.time() + a.secs
    samples = 0
    tids, refresh = [], 0.0
    while time.time() < end:
        if time.time() >= refresh:  # the thread list changes rarely; a snapshot per round would slow sampling down
            tids, refresh = threads_of(pid), time.time() + 2.0
        for tid in tids:
            h = handles.get(tid)
            if h is None:
                h = handles[tid] = k32.OpenThread(THREAD_ACCESS, False, tid)
            if not h:
                continue
            if k32.SuspendThread(h) == 0xFFFFFFFF:
                continue
            ctypes.c_uint32.from_address(addr + FLAGS_OFFSET).value = CONTEXT_CONTROL
            if k32.GetThreadContext(h, ctypes.c_void_p(addr)):
                rip = ctypes.c_uint64.from_address(addr + RIP_OFFSET).value
                rva = rip - base
                i = bisect.bisect_right(rvas, rva) - 1
                name = names[i] if 0 <= i and 0 <= rva < 0x40000000 else '<outside exe>'
                hist[tid][name] += 1
                if a.func and a.func in name:
                    hot[rva] += 1
            k32.ResumeThread(h)
        samples += 1
        time.sleep(a.interval)
    print(f'{samples} sampling rounds')
    if a.func:
        print(f'hottest addresses in *{a.func}* (RVA, preferred base 0x140000000):')
        for rva, v in hot.most_common(a.top):
            print(f'{v:7d}  0x{rva + 0x140000000:x}')
    for tid, c in sorted(hist.items(), key=lambda kv: -sum(v for k, v in kv[1].items() if k != '<outside exe>')):
        inside = sum(v for k, v in c.items() if k != '<outside exe>')
        if inside < samples * 0.05:
            continue
        print(f'\n== thread {tid}: {sum(c.values())} samples, {inside} in the exe')
        for name, v in c.most_common(a.top):
            print(f'{v:7d} {100.0 * v / sum(c.values()):5.1f}%  {name}')


if __name__ == '__main__':
    main()
