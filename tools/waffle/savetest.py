"""Save regression check: load save slot 1, save at the save point it starts on, and check the card.

usage: python -I tools/savetest.py [--out port/savetest] [--secs 150] [--keys "g4:r2,g7:x,g9:x,g11:arriba,g12.5:x,g20:x,g22:x"] (overwrite prompt defaults to No: up, then X)

Runs the runner on a copy of ref/saves/Mcd002.ps2 with a pad script: title menu -> load game -> slot 1 (like zones.py),
then the save keys at gameplay-relative times (default: R2 at the save point, X through the save menus). Captures a
frame every second after gameplay start. Reports how many 528-byte card pages changed and lists the root directory of
the card before/after (docs/memory-card.md format), so a broken write path shows up as corrupt or missing entries.
"""
import argparse
import os
import shutil
import struct
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import zones  # noqa: E402  (paths, play environment)

RAW, DATA = 528, 512


def page(card, p):
    return card[p * RAW:p * RAW + DATA]


def root_dir(card):
    sb = page(card, 0)
    if not sb.startswith(b'Sony PS2 Memory Card Format'):
        return ['(no superblock)']
    ppc = struct.unpack_from('<H', sb, 0x2A)[0]
    alloc, root = struct.unpack_from('<II', sb, 0x34)[0], struct.unpack_from('<I', sb, 0x3C)[0]
    ifc = struct.unpack_from('<I', sb, 0x50)[0]

    def cluster(c):
        return b''.join(page(card, c * ppc + i) for i in range(ppc))

    fat_ptrs = struct.unpack_from('<256I', cluster(ifc))

    def fat(c):
        fc = struct.unpack_from('<256I', cluster(fat_ptrs[c // 256]))
        return fc[c % 256]

    entries, c = [], root
    first = struct.unpack_from('<I', cluster(alloc + root), 4)[0]  # "." length = entry count
    while c != 0x7FFFFFFF and len(entries) < first + 2:
        data = cluster(alloc + c)
        for k in range(2):
            e = data[k * 512:(k + 1) * 512]
            mode, length = struct.unpack_from('<II', e, 0)
            name = e[0x40:0x60].split(b'\0')[0].decode(errors='replace')
            if mode & 0x8000:
                entries.append(f'{name} mode={mode:x} len={length}')
        nxt = fat(c)
        if nxt == 0xFFFFFFFF or not nxt & 0x80000000:
            break
        c = nxt & 0x7FFFFFFF
    return entries


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--out', default=os.path.join(ROOT, 'port', 'savetest'))
    ap.add_argument('--secs', type=float, default=150)
    ap.add_argument('--keys', default='g4:r2,g7:x,g9:x,g11:arriba,g12.5:x,g20:x,g22:x')
    ap.add_argument('--exe')
    ap.add_argument('--silent', action='store_true', help='mute the run (GOW_AUDIO=0); sound is on by default')
    ap.add_argument('--audio', action='store_true', help=argparse.SUPPRESS)  # old flag, sound is the default now
    ap.add_argument('--iso', action='store_true', help='read the original ISO (default: the extracted files in disc-usa/)')
    args = ap.parse_args()
    exe = os.path.abspath(args.exe) if args.exe else zones.EXE
    exe_dir = os.path.dirname(exe)
    args.out = os.path.abspath(args.out)
    os.makedirs(args.out, exist_ok=True)
    card = os.path.join(args.out, 'card.ps2')
    shutil.copyfile(zones.DEFAULT_CARD, card)
    before = open(card, 'rb').read()
    script = '5:start,16:abajo,24:x,89:x,' + args.keys
    caps = ','.join(f'g{t}' for t in range(2, 26, 1))
    env = dict(os.environ, **zones.PLAY_ENV)
    env.update({'GOW_MC0': card, 'GOW_PAD_GUION': script, 'GOW_PAD_CAPTURAS': caps})
    env.pop('GOW_ISO', None)
    if args.iso:
        env['GOW_ISO'] = zones.ISO  # default: the extracted files next to the ELF (docs/disc.md)
    if args.silent:
        env['GOW_AUDIO'] = '0'  # --silent mutes the run (sound is on by default, user 2026-10-12)
    for f in os.listdir(exe_dir):
        if f.startswith('gow_pad_test_') and f.endswith('.ppm'):
            os.remove(os.path.join(exe_dir, f))
    with open(os.path.join(args.out, 'log.txt'), 'wb') as log:
        proc = subprocess.Popen([exe, zones.ELF], cwd=exe_dir, env=env, stdout=log, stderr=subprocess.STDOUT)
        start = time.time()
        while time.time() - start < args.secs and proc.poll() is None:
            time.sleep(1)
        if proc.poll() is None:
            subprocess.run(['taskkill', '/PID', str(proc.pid), '/F'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    for f in sorted(os.listdir(exe_dir)):
        if f.startswith('gow_pad_test_') and f.endswith('.ppm'):
            subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools', 'ppm2png.py'), os.path.join(exe_dir, f),
                            os.path.join(args.out, f[:-4] + '.png')], check=False)
    after = open(card, 'rb').read()
    changed = [p for p in range(len(before) // RAW) if before[p * RAW:(p + 1) * RAW] != after[p * RAW:(p + 1) * RAW]]
    print(f'pages changed: {len(changed)}' + (f' (first {changed[:8]})' if changed else ''))
    print('root before:', root_dir(before))
    print('root after: ', root_dir(after))


if __name__ == '__main__':
    main()
