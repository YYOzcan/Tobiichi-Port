"""Zone regression check: load every save slot of a memory card, walk around, capture frames and judge the run.

usage: python -I tools/zones.py [--slots 1,2,3,4] [--card <Mcd.ps2>] [--secs 200] [--diff] [--baseline <report dir>] [--out <dir>]

For each slot (= one zone of the user's save card) the real runner is started with the play configuration and a pad
script (load the slot, wait for gameplay, walk in the four directions, wait). Slot 0 is a NEW GAME instead (title ->
New Game -> Hero -> the Aegean Sea ship), walking and attacking. Per zone it records:
  * reached gameplay (state 11) and how long that took,
  * game fps (guest_flip_hz of the last windows) against the 25 fps floor,
  * game speed (GOW_DELTA_DIAG [gow-speed]: game seconds per wall second, 1.00 = real time; warning outside 0.9-1.1),
  * runtime errors in the log (missing recompiled functions, cut VIF packets, unhandled VIFcodes, access violations...),
  * the captured frames (PNG), flagging blank/black ones and, with --baseline, large changes against an earlier report,
  * with --diff: the EE differential tester (PS2X_EE_DIFF=all) against PCSX2's interpreter, listing functions whose
    memory differs by more than rounding noise (stack garbage and rand callers excluded).
Writes <out>/<timestamp>/report.md, one folder per zone with log + captures + contact sheet. Exit code 1 if a zone fails.
Add more zones by giving --card a card that holds more saves (the slot picker is walked with the stick/D-pad).
"""
import argparse
import datetime
import json
import os
import re
import struct
import subprocess
import sys
import time
import zlib

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE_DIR = os.path.join(ROOT, 'ext', 'PS2Recomp-kl', 'out', 'build-kl', 'ps2xRuntime', 'Release')
EXE = os.path.join(EXE_DIR, 'ps2EntryRunner.exe')
ISO = os.path.join(ROOT, 'iso-usa', 'God of War (USA).iso')
ELF = os.path.join(ROOT, 'disc-usa', 'SCUS_973.99')
DEFAULT_CARD = os.path.join(ROOT, 'ref', 'saves', 'Mcd002.ps2')

PLAY_ENV = {
    'PS2X_GS_WORKER': '1', 'GOW_GS_FINISH_ASINCRONO': '1', 'GOW_SKIP_FMV': '1',
    'GOW_PAD_TEST': '1', 'GOW_PERF_DIAG': '1', 'GOW_PERF_FRAME_PC': '0x001837B8', 'GOW_FAST_BOOT': '1',
    'GOW_DELTA_DIAG': '1',
}
ERROR_PATTERNS = [
    (r'No exact recompiled function', 'missing recompiled function'),
    (r'\[vif1\] (UNPACK|STMASK|STROW|STCOL|MPG) cut|MPG overruns', 'cut VIF1 packet'),
    (r'\[vif1\] unhandled VIFcode', 'unhandled VIFcode'),
    (r'chain on 0x[0-9a-f]+ stopped after', 'runaway DMA chain'),
    (r'Unhandled|unhandled exception|access violation|Access violation', 'exception'),
    (r'\[dma\] SPR .* not handled', 'unhandled SPR DMA mode'),
    (r'gs-gpu\].*(failed|error)', 'GPU backend error'),
]


def read_png(path):
    data = open(path, 'rb').read()
    i, w, h, idat = 8, 0, 0, b''
    while i < len(data):
        n = struct.unpack('>I', data[i:i + 4])[0]
        kind = data[i + 4:i + 8]
        if kind == b'IHDR':
            w, h = struct.unpack('>II', data[i + 8:i + 16])
        elif kind == b'IDAT':
            idat += data[i + 8:i + 8 + n]
        i += 12 + n
    raw = zlib.decompress(idat)
    stride = w * 3
    rows, prev = [], bytearray(stride)
    p = 0
    for _ in range(h):
        f = raw[p]
        line = bytearray(raw[p + 1:p + 1 + stride])
        p += 1 + stride
        if f == 1:
            for x in range(3, stride):
                line[x] = (line[x] + line[x - 3]) & 255
        elif f == 2:
            for x in range(stride):
                line[x] = (line[x] + prev[x]) & 255
        elif f == 3:
            for x in range(stride):
                left = line[x - 3] if x >= 3 else 0
                line[x] = (line[x] + ((left + prev[x]) >> 1)) & 255
        elif f == 4:
            for x in range(stride):
                a = line[x - 3] if x >= 3 else 0
                b = prev[x]
                c = prev[x - 3] if x >= 3 else 0
                pa, pb, pc = abs(b - c), abs(a - c), abs(a + b - 2 * c)
                pr = a if pa <= pb and pa <= pc else (b if pb <= pc else c)
                line[x] = (line[x] + pr) & 255
        rows.append(line)
        prev = line
    return w, h, rows


def luminance_stats(path):
    w, h, rows = read_png(path)
    step = 7
    vals = [sum(r[x:x + 3]) / 3.0 for r in rows[::step] for x in range(0, w * 3 - 2, 3 * step)]
    mean = sum(vals) / len(vals)
    var = sum((v - mean) ** 2 for v in vals) / len(vals)
    return mean, var ** 0.5


def image_distance(a, b):
    wa, ha, ra = read_png(a)
    wb, hb, rb = read_png(b)
    if (wa, ha) != (wb, hb):
        return 255.0
    tot = n = 0
    for y in range(0, ha, 5):
        la, lb = ra[y], rb[y]
        for x in range(0, wa * 3, 15):
            tot += abs(la[x] - lb[x])
            n += 1
    return tot / n


def pad_script(slot, walk):
    if slot == 0:
        # New game: title -> New Game -> difficulty (Hero) -> the Aegean Sea ship; walk and attack (square) so
        # Kratos fights the first enemies instead of dying.
        keys = ['5:start', '14:x', '20:x', '26:x', '32:x']
        t0 = 8
        for direction in walk:
            keys.append(f'g{t0:g}:{direction}*3')
            keys += [f'g{t0 + 0.5 + 0.5 * i:g}:cuadrado*0.2' for i in range(8)]
            t0 += 5
        return ','.join(keys), t0
    keys = ['5:start', '16:abajo', '24:x']
    t = 85.0
    for _ in range(slot - 1):
        keys.append(f'{t:g}:derecha*0.3')
        t += 1.5
    keys.append(f'{t + 4:g}:x')
    t0 = 8
    for direction in walk:
        keys.append(f'g{t0:g}:{direction}*3')
        t0 += 5
    return ','.join(keys), t0


def run_zone(slot, args, outdir):
    zone = os.path.join(outdir, f'zone_slot{slot}')
    os.makedirs(zone, exist_ok=True)
    walk = ['ldown', 'lright', 'lup', 'lleft']
    script, last = pad_script(slot, walk)
    caps = ','.join(f'g{t:g}' for t in [5, 7] + [8 + 5 * i + 2.2 for i in range(len(walk))])
    env = dict(os.environ, **PLAY_ENV)
    env.update({'GOW_MC0': args.card_copy, 'GOW_PAD_GUION': script, 'GOW_PAD_CAPTURAS': caps})
    env.pop('GOW_ISO', None)
    if args.iso:
        env['GOW_ISO'] = ISO  # default: the extracted files next to the ELF (docs/disc.md)
    if args.silent:
        env['GOW_AUDIO'] = '0'  # --silent mutes the run (sound is on by default, user 2026-10-12)
    if args.diff:
        env.update({'PS2X_EE_DIFF': 'all', 'PS2X_EE_DIFF_MAX': '12', 'PS2X_EE_DIFF_LINES': '300',
                    'PS2X_EE_DIFF_START': str(args.diff_start)})
    for f in os.listdir(EXE_DIR):
        if f.startswith('gow_pad_test_') and f.endswith('.ppm'):
            os.remove(os.path.join(EXE_DIR, f))
    log_path = os.path.join(zone, 'log.txt')
    start = time.time()
    with open(log_path, 'wb') as log:
        proc = subprocess.Popen([EXE, ELF], cwd=EXE_DIR, env=env, stdout=log, stderr=subprocess.STDOUT)
        while time.time() - start < args.secs and proc.poll() is None:
            time.sleep(1)
        died = proc.poll() is not None
        code = proc.returncode
        if not died:
            subprocess.run(['taskkill', '/PID', str(proc.pid), '/F'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    text = open(log_path, encoding='utf-8', errors='replace').read()
    res = {'slot': slot, 'died_early': died, 'exit_code': code, 'failures': [], 'warnings': []}
    m = re.search(r'gameplay start at ([0-9.]+) s', text)
    res['gameplay_start_s'] = float(m.group(1)) if m else None
    if not m:
        res['failures'].append('never reached gameplay')
    if died:
        res['failures'].append(f'process exited early (code {code})')
    fps = [float(x) for x in re.findall(r'guest_flip_hz=([0-9.]+)', text)]
    tail = fps[-4:]
    res['fps_last'] = tail
    if tail and min(tail) < args.min_fps:
        res['failures'].append(f'fps {min(tail):.1f} below {args.min_fps}')
    # game speed (GOW_DELTA_DIAG): game seconds per wall second over the last 20 one-second windows
    speed = [float(x) for x in re.findall(r'\[gow-speed\] .*?speed=([0-9.]+)', text)][-20:]
    res['game_speed'] = [sum(speed) / len(speed), min(speed), max(speed)] if speed else None
    if speed and not 0.9 <= res['game_speed'][0] <= 1.1:
        res['warnings'].append(f"game speed {res['game_speed'][0]:.2f}x real time")
    for pattern, label in ERROR_PATTERNS:
        n = len(re.findall(pattern, text))
        if n:
            res['failures'].append(f'{label} x{n}')
    # captures
    pngs = []
    for f in sorted(os.listdir(EXE_DIR)):
        if f.startswith('gow_pad_test_') and f.endswith('.ppm'):
            dst = os.path.join(zone, f.replace('.ppm', '.png'))
            subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools', 'ppm2png.py'), os.path.join(EXE_DIR, f), dst],
                           check=False)
            if os.path.exists(dst):
                pngs.append(dst)
            else:  # e.g. a capture still being written when the runner was stopped
                res['warnings'].append(f'capture {f} not converted')
    res['captures'] = len(pngs)
    blank = 0
    for p in pngs:
        if not os.path.exists(p):
            continue
        mean, sd = luminance_stats(p)
        if sd < 3.0 or mean < 4.0:
            blank += 1
    if pngs and blank == len(pngs):
        res['failures'].append('all captures blank')
    elif blank:
        res['warnings'].append(f'{blank} blank capture(s)')
    if not pngs:
        res['failures'].append('no captures')
    if args.baseline:
        base = os.path.join(args.baseline, f'zone_slot{slot}')
        big = []
        for p in pngs:
            q = os.path.join(base, os.path.basename(p))
            if os.path.exists(q):
                d = image_distance(p, q)
                if d > args.image_tol:
                    big.append(f'{os.path.basename(p)}={d:.0f}')
        if big:
            res['warnings'].append('changed vs baseline: ' + ', '.join(big))
    if len(pngs) > 1:
        subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools', 'sheet.py'), zone, '0', str(len(pngs) - 1),
                        os.path.join(zone, 'sheet.png')], check=False)
    if args.diff:
        res['diff'] = summarize_diff(text)
        if res['diff']['suspects']:
            res['warnings'].append(f"EE diff: {len(res['diff']['suspects'])} function(s) with non-rounding differences")
    return res


def summarize_diff(text):
    fv = lambda x: struct.unpack('f', struct.pack('I', x))[0]
    cur = None
    big = {}
    calls = 0
    for line in text.splitlines():
        m = re.search(r'\[eediff\] ([0-9A-F]{8}) \(ra [0-9A-F]{8}\) call \d+:', line)
        if m:
            cur = m.group(1)
            calls += 1
            continue
        m = re.search(r'\[eediff\]    mem ([0-9A-F]{8}) ref ([0-9A-F]{8}) \([^)]*\) ours ([0-9A-F]{8})', line)
        if not (m and cur):
            continue
        a, r, o = int(m.group(1), 16), int(m.group(2), 16), int(m.group(3), 16)
        if a >= 0x01FE0000:  # stack frames: dead locals
            continue
        er, eo = (r >> 23) & 255, (o >> 23) & 255
        if er and eo and er != 255 and eo != 255:
            d, sc = abs(fv(r) - fv(o)), max(abs(fv(r)), abs(fv(o)), 1e-30)
            if d <= 2e-3 * sc or d < 1e-5:
                continue
        elif (r & 0x7FFFFFFF) < 0x00800000 and (o & 0x7FFFFFFF) < 0x00800000 and abs(r - o) < 8:
            continue
        big[cur] = big.get(cur, 0) + 1
    # rand is stubbed, so its callers differ by construction
    ignore = {'0028C0C8'}
    suspects = {k: v for k, v in big.items() if k not in ignore}
    return {'calls': calls, 'suspects': dict(sorted(suspects.items(), key=lambda kv: -kv[1])[:20])}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--slots', default='1,2,3,4')
    ap.add_argument('--exe', help='runner to test (default: the main build); captures are written next to it')
    ap.add_argument('--card', default=DEFAULT_CARD)
    ap.add_argument('--secs', type=float, default=200)
    ap.add_argument('--silent', action='store_true', help='mute the run (GOW_AUDIO=0); sound is on by default')
    ap.add_argument('--audio', action='store_true', help=argparse.SUPPRESS)  # old flag, sound is the default now
    ap.add_argument('--iso', action='store_true', help='read the original ISO (default: the extracted files in disc-usa/)')
    ap.add_argument('--min-fps', type=float, default=25.0)
    ap.add_argument('--diff', action='store_true', help='also run the EE differential tester (slow)')
    ap.add_argument('--diff-start', type=float, default=125.0)
    ap.add_argument('--baseline', help='earlier report directory to compare captures with')
    ap.add_argument('--image-tol', type=float, default=40.0)
    ap.add_argument('--out', default=os.path.join(ROOT, 'port', 'zones'))
    args = ap.parse_args()
    if args.exe:
        global EXE, EXE_DIR
        EXE = os.path.abspath(args.exe)
        EXE_DIR = os.path.dirname(EXE)
    if args.diff:
        args.secs = max(args.secs, 420)
    stamp = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
    outdir = os.path.join(args.out, stamp)
    os.makedirs(outdir, exist_ok=True)
    args.card_copy = os.path.join(ROOT, 'disc-usa', 'Mcd001.ps2')
    results = []
    for slot in [int(s) for s in args.slots.split(',')]:
        with open(args.card, 'rb') as src, open(args.card_copy, 'wb') as dst:  # fresh card every zone
            dst.write(src.read())
        print(f'zone slot {slot} ...', flush=True)
        res = run_zone(slot, args, outdir)
        results.append(res)
        print('  ', 'FAIL' if res['failures'] else 'ok', res['failures'] or '', res['warnings'] or '', flush=True)
    lines = [f'# Zone check {stamp}', '', '| slot | gameplay start | fps (last windows) | game speed (mean, min-max) | captures | result |', '|---|---|---|---|---|---|']
    for r in results:
        lines.append(f"| {r['slot']} | {r['gameplay_start_s']} | {', '.join('%.1f' % x for x in r['fps_last'])} | "
                     f"{'%.2f (%.2f-%.2f)' % tuple(r['game_speed']) if r['game_speed'] else '-'} | {r['captures']} | "
                     f"{'FAIL: ' + '; '.join(r['failures']) if r['failures'] else 'ok'}{' (' + '; '.join(r['warnings']) + ')' if r['warnings'] else ''} |")
    for r in results:
        if r.get('diff'):
            lines += ['', f"## EE diff slot {r['slot']} ({r['diff']['calls']} compared calls)"]
            lines += [f'- {k}: {v} non-rounding memory differences' for k, v in r['diff']['suspects'].items()] or ['- none']
    open(os.path.join(outdir, 'report.md'), 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
    json.dump(results, open(os.path.join(outdir, 'report.json'), 'w'), indent=1)
    print('\n'.join(lines))
    print('report:', os.path.join(outdir, 'report.md'))
    return 1 if any(r['failures'] for r in results) else 0


if __name__ == '__main__':
    sys.exit(main())
