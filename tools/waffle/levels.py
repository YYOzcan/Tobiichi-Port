"""Level check: warp through every zone of the game with the game's own debug warp and judge each one.

usage: python -I tools/levels.py [--zones all|ATHN01A,PAND04G,...] [--stay 45] [--batch 15] [--exe-dir <dir>]
                                 [--silent] [--out port/levels]

Each batch starts the runner once: NEW GAME (as tools/zones.py slot 0) to reach gameplay on the ship, then GOW_WARP
(gow_overrides.cpp) warps to each zone of the batch in turn (the level scripts' LoadForWarp(zone) + Warp() builtins:
the zone WAD is loaded and Kratos is moved to its warp point) and stays --stay seconds, moving and attacking with
GOW_GOD_MODE on. Per zone it records: arrived or timed out, load time, fps (guest_flip_hz) and game speed while there,
runtime errors ([guest-branch:missing-target], [gow-heapguard], the zones.py error patterns) and two captures.
Writes <out>/<timestamp>/report.md (+ report.json, one log per batch, captures as PNG). Zone names are the WAD
names of GODOFWAR.TOC without ".WAD" (R_* resource WADs are not zones).
"""
import argparse
import datetime
import json
import os
import re
import shutil
import subprocess
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import zones  # noqa: E402  (PLAY_ENV, ERROR_PATTERNS, card and capture helpers)

TOC = os.path.join(ROOT, 'disc-usa', 'GODOFWAR.TOC')


def toc_zones():
    data = open(TOC, 'rb').read()
    seen, out = set(), []
    for i in range(0, len(data) - 23, 24):
        name = data[i:i + 12].split(b'\0')[0].decode('latin1')
        if name.endswith('.WAD') and not name.startswith('R_') and name not in seen:
            seen.add(name)
            out.append(name[:-4])
    return out


def fight_script(total):
    # new game menus (zones.py slot 0), then from gameplay start: move in a square and attack, to the end of the run
    keys = ['5:start', '14:x', '20:x', '26:x', '32:x']
    t = 8.0
    sticks = ['lup', 'lright', 'ldown', 'lleft']
    i = 0
    while t < total:
        keys.append(f'g{t:g}:{sticks[i % 4]}*1.5')
        keys.append(f'g{t + 0.3:g}:cuadrado*0.2')
        keys.append(f'g{t + 0.9:g}:triangulo*0.2')
        keys.append(f'g{t + 1.6:g}:cuadrado*0.2')
        t += 2.0
        i += 1
    return ','.join(keys)


def run_batch(index, batch, args, outdir, exe_dir):
    log_path = os.path.join(outdir, f'batch{index}.log')
    total = 60 + len(batch) * (args.stay + 40)
    env = dict(os.environ, **zones.PLAY_ENV)
    env.update({'GOW_MC0': args.card_copy, 'GOW_PAD_GUION': fight_script(total), 'GOW_PAD_CAPTURAS': 'g4',
                'GOW_WARP': ';'.join(batch), 'GOW_WARP_STAY': str(args.stay), 'GOW_GOD_MODE': '1',
                'GOW_PLAYER_TRACE': '1'})
    env.pop('GOW_ISO', None)
    if args.silent:
        env['GOW_AUDIO'] = '0'
    for f in os.listdir(exe_dir):
        if (f.startswith('gow_warp_') or f.startswith('gow_pad_test_')) and f.endswith('.ppm'):
            os.remove(os.path.join(exe_dir, f))
    start = time.time()
    with open(log_path, 'wb') as log:
        proc = subprocess.Popen([os.path.join(exe_dir, 'ps2EntryRunner.exe'), zones.ELF], cwd=exe_dir, env=env,
                                stdout=log, stderr=subprocess.STDOUT)
        while time.time() - start < total + 120 and proc.poll() is None:
            time.sleep(2)
            text = open(log_path, encoding='utf-8', errors='replace').read()
            if '[gow-warp] done' in text:
                time.sleep(3)
                break
        died = proc.poll() is not None
        if not died:
            subprocess.run(['taskkill', '/PID', str(proc.pid), '/F'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    for f in sorted(os.listdir(exe_dir)):
        if f.startswith('gow_warp_') and f.endswith('.ppm'):
            subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools', 'ppm2png.py'), os.path.join(exe_dir, f),
                            os.path.join(outdir, f.replace('.ppm', '.png'))], check=False)
    return judge(open(log_path, encoding='utf-8', errors='replace').read(), batch, died, args)


def judge(text, batch, died, args):
    results = {z: {'zone': z, 'status': 'not reached', 'failures': [], 'warnings': []} for z in batch}
    current = None
    segment = []

    def close(zone, lines):
        if zone is None:
            return
        r = results[zone]
        seg = '\n'.join(lines)
        fps = [float(x) for x in re.findall(r'guest_flip_hz=([0-9.]+)', seg)]
        r['fps'] = [min(fps), sum(fps) / len(fps)] if fps else None
        if fps and min(fps[1:] or fps) < args.min_fps:
            r['failures'].append(f'fps {min(fps[1:] or fps):.1f} below {args.min_fps}')
        speed = [float(x) for x in re.findall(r'\[gow-speed\] .*?speed=([0-9.]+)', seg)]
        r['speed'] = sum(speed) / len(speed) if speed else None
        if speed and not 0.9 <= r['speed'] <= 1.1:
            r['warnings'].append(f"game speed {r['speed']:.2f}")
        crash = len(re.findall(r'\[guest-branch:missing-target\]', seg))
        if crash:
            r['failures'].append(f'guest crash (missing-target) x{crash}')
        guard = re.findall(r'\[gow-heapguard\][^\n]*', seg)
        if guard:
            r['warnings'].append(f'heap guard x{len(guard)}')
            r['heapguard'] = guard[:5]
        for pattern, label in zones.ERROR_PATTERNS:
            n = len(re.findall(pattern, seg))
            if n:
                r['failures'].append(f'{label} x{n}')
        hp = re.findall(r'\[gow-player\].*? zone=(\S+)', seg)
        r['zones_seen'] = sorted(set(hp))

    for line in text.splitlines():
        m = re.search(r'\[gow-warp\] (request|arrived|timeout) (\S+) at ([0-9.]+) s(?: \(([0-9.]+) s\))?', line)
        if m:
            kind, zone = m.group(1), m.group(2)
            if kind == 'request':
                close(current, segment)
                current, segment = None, []
                if zone in results:
                    results[zone]['status'] = 'requested'
            elif kind == 'arrived' and zone in results:
                results[zone]['status'] = 'ok'
                results[zone]['load_s'] = float(m.group(4)) if m.group(4) else None
                current, segment = zone, []
            elif kind == 'timeout' and zone in results:
                results[zone]['status'] = 'timeout'
                results[zone]['failures'].append('warp timed out: ' + line.split('timeout', 1)[1].strip())
            continue
        if current is not None:
            segment.append(line)
        elif '[guest-branch:missing-target]' in line:
            # a crash while loading a zone: charge it to the zone being requested
            req = [z for z in batch if results[z]['status'] == 'requested']
            if req:
                results[req[-1]]['failures'].append('guest crash while loading')
    close(current, segment)
    for r in results.values():
        if r['status'] in ('not reached', 'requested') and not r['failures']:
            r['failures'].append('process ended before this zone' if died else f"warp {r['status']}")
    return list(results.values())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--zones', default='all')
    ap.add_argument('--stay', type=float, default=30)
    ap.add_argument('--batch', type=int, default=1)
    ap.add_argument('--exe-dir', default=zones.EXE_DIR)
    ap.add_argument('--card', default=zones.DEFAULT_CARD)
    ap.add_argument('--min-fps', type=float, default=25)
    ap.add_argument('--silent', action='store_true')
    ap.add_argument('--out', default=os.path.join(ROOT, 'port', 'levels'))
    args = ap.parse_args()
    names = toc_zones() if args.zones == 'all' else [z.strip().upper() for z in args.zones.split(',') if z.strip()]
    outdir = os.path.join(args.out, datetime.datetime.now().strftime('%Y%m%d_%H%M%S'))
    os.makedirs(outdir, exist_ok=True)
    # the runner writes the card: always a copy, never the user's card
    args.card_copy = os.path.join(outdir, 'card.ps2')
    shutil.copyfile(args.card, args.card_copy)
    results = []
    for i in range(0, len(names), args.batch):
        batch = names[i:i + args.batch]
        print(f'batch {i // args.batch}: {", ".join(batch)}', flush=True)
        results += run_batch(i // args.batch, batch, args, outdir, args.exe_dir)
        shutil.copyfile(args.card, args.card_copy)
    lines = [f'# Level check {os.path.basename(outdir)}', '', '| zone | result | load s | fps min / mean | speed | notes |',
             '|---|---|---|---|---|---|']
    bad = 0
    for r in results:
        ok = r['status'] == 'ok' and not r['failures']
        bad += not ok
        fps = f"{r['fps'][0]:.1f} / {r['fps'][1]:.1f}" if r.get('fps') else '-'
        speed = f"{r['speed']:.2f}" if r.get('speed') else '-'
        load = f"{r['load_s']:.1f}" if r.get('load_s') else '-'
        notes = '; '.join(r['failures'] + r['warnings'])
        lines.append(f"| {r['zone']} | {'ok' if ok else r['status'] if r['status'] != 'ok' else 'FAIL'} | {load} | {fps} | {speed} | {notes} |")
    lines += ['', f'{len(results) - bad} of {len(results)} zones ok.']
    open(os.path.join(outdir, 'report.md'), 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
    json.dump(results, open(os.path.join(outdir, 'report.json'), 'w'), indent=1)
    print('\n'.join(lines))
    print('report:', os.path.join(outdir, 'report.md'))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
