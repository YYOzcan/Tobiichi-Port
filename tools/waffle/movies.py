"""Movie regression check: play every movie of the disc through the game's own player and judge picture and sound.

usage: python -I tools/movies.py [--only A01MP05,SEMO02] [--batch 12] [--out port/movies] [--exe <runner>] [--keep-pcm]
       python -I tools/movies.py --new-game 300   (the movies a new game plays itself: intro, ship A01MP05)
       python -I tools/movies.py --reanalyse <run dir>   (judge a finished run again from its logs and kept PCM)

The movie names come from disc-usa/GODOFWAR.TOC (every *.PSS; the game itself picks .PSS or .PSW). Each batch is one
session of the real runner: GOW_MOVIE_OVERRIDE=<list> makes the intro play the first movie, then the title menu starts
the next one each time the player is idle again (gow_overrides.cpp gowDiagBonusMovie), so later movies play after
earlier ones, as in the game. Sound is recorded (GOW_AUDIO_PCM, s16le stereo 48 kHz) with the output muted
(GOW_AUDIO=0: the stream runs at volume 0, paced as when heard). Per movie the report gives:
  pictures, pictures per second (30 expected), audio seconds vs picture seconds, A/V drift over the movie, silent
  one-second windows, clipped samples, smoothness (first difference / RMS: music and speech 0.01-0.9, noise >= 1.2),
  repeated 512-frame blocks (stuck or re-sent buffers), dropped output frames (GOW_AUDIO_STATS) and runtime errors.
Report: <out>/<stamp>/report.md and report.json; logs per batch.
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

import numpy as np

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXE = os.path.join(ROOT, 'ext', 'PS2Recomp-kl', 'out', 'build-kl', 'ps2xRuntime', 'Release', 'ps2EntryRunner.exe')
ELF = os.path.join(ROOT, 'disc-usa', 'SCUS_973.99')
TOC = os.path.join(ROOT, 'disc-usa', 'GODOFWAR.TOC')
CARD = os.path.join(ROOT, 'ref', 'saves', 'Mcd002.ps2')
RATE = 48000
BYTES_PER_SECOND = 0.69e6  # PSS streams: ~0.69 MB per second of movie (BONUS03: 566 MB, 812 s)

ENV = {
    'PS2X_GS_WORKER': '1', 'GOW_GS_FINISH_ASINCRONO': '1', 'GOW_PAD_TEST': '1', 'GOW_PERF_DIAG': '1',
    'GOW_DELTA_DIAG': '1', 'GOW_MPEG_DIAG': '1', 'GOW_AUDIO_STATS': '1', 'GOW_AUDIO': '0',
    'GOW_PAD_GUION': '99999:select',  # the default test presses would start a new game
    'GOW_BONUS_MOVIE_DELAY': '8',
}
# a movie load: forced by GOW_MOVIE_OVERRIDE or the game's own (GOW_MPEG_DIAG)
LOAD_LINE = r'\[gow-fmv\] (?:override \d+/\d+ \S+ -> |load )(\S+)'
ERRORS = r'No exact recompiled|Unhandled|access violation|Access violation|did not return|missing-target'


def movie_list():
    toc = open(TOC, 'rb').read()
    names = {}
    for i in range(0, len(toc) - 23, 24):
        name = toc[i:i + 12].split(b'\0')[0].decode('ascii', 'replace')
        size = struct.unpack_from('<I', toc, i + 16)[0]
        if name.upper().endswith('.PSS'):
            names.setdefault(name[:-4].upper(), size)
    return names


def run_batch(movies, sizes, outdir, index, args):
    log_path = os.path.join(outdir, f'batch{index}.log')
    pcm_path = os.path.join(outdir, f'batch{index}.pcm')
    card = os.path.join(outdir, f'card{index}.ps2')
    with open(CARD, 'rb') as src, open(card, 'wb') as dst:
        dst.write(src.read())
    env = dict(os.environ, **ENV)
    # the title menu requests a bonus movie (any: the load override replaces its name), also for a single movie
    env.update({'GOW_MOVIE_OVERRIDE': ','.join(movies), 'GOW_BONUS_MOVIE': '24', 'GOW_AUDIO_PCM': pcm_path, 'GOW_MC0': card})
    budget = 120 + sum(sizes[m] / BYTES_PER_SECOND + 30 for m in movies)
    exe_dir = os.path.dirname(args.exe)
    with open(log_path, 'wb') as log:
        proc = subprocess.Popen([args.exe, ELF], cwd=exe_dir, env=env, stdout=log, stderr=subprocess.STDOUT)
    start, ended_at = time.time(), None
    while proc.poll() is None and time.time() - start < budget:
        time.sleep(2)
        text = open(log_path, encoding='utf-8', errors='replace').read()
        overrides = text.count('[gow-fmv] override ')
        last = text.rfind('[gow-fmv] override ')
        # the last movie ended: its player went back to idle after the last override
        if overrides >= len(movies) and re.search(r'menu sees movie state \d+ -> 0', text[last:]):
            ended_at = ended_at or time.time()
            if time.time() - ended_at > 4:
                break
        # the intro slot is the only movie: it ends before the menu hook watches
        if len(movies) == 1 and overrides and 'menu sees' not in text and re.search(r'\[MPEG:sync\]', text[last:]) \
                and time.time() - start > 60 + sizes[movies[0]] / BYTES_PER_SECOND:
            break
    if proc.poll() is None:
        proc.kill()
        proc.wait()
    return log_path, pcm_path, time.time() - start


def pcm_checks(pcm, p0, p1):
    n = len(pcm) // 4
    p0, p1 = max(0, min(p0, n)), max(0, min(p1, n))
    res = {'silent_s': 0, 'clipped': 0, 'smooth_max': 0.0, 'repeats': 0, 'rms_mean': 0.0}
    if p1 - p0 < RATE:
        return res
    stereo = np.frombuffer(pcm, dtype='<i2', count=(p1 - p0) * 2, offset=p0 * 4).reshape(-1, 2)
    left = stereo[:, 0].astype(np.float64)
    seconds = len(left) // RATE
    windows = left[:seconds * RATE].reshape(seconds, RATE)
    rms = np.sqrt(np.mean(windows ** 2, axis=1))
    loud = rms >= 30
    res['silent_s'] = int(np.count_nonzero(~loud))
    if loud.any():
        diff = np.sqrt(np.mean(np.diff(windows[loud], axis=1) ** 2, axis=1))
        res['smooth_max'] = float(np.max(diff / rms[loud]))
    res['rms_mean'] = float(np.mean(rms))
    res['clipped'] = int(np.count_nonzero((stereo >= 32767) | (stereo <= -32768)))
    # repeated blocks: a non-silent 512-frame block equal to one of the 8 before it
    blocks = stereo[:len(stereo) // 512 * 512].reshape(-1, 512 * 2)
    loud_blocks = np.max(np.abs(blocks[:, :128]), axis=1) > 64
    repeated = np.zeros(len(blocks), dtype=bool)
    for back in range(1, 9):
        repeated[back:] |= np.all(blocks[back:] == blocks[:-back], axis=1)
    res['repeats'] = int(np.count_nonzero(repeated & loud_blocks))
    return res


def new_game_script(seconds=150):
    """Pad script of a new game (title -> New Game -> Hero -> the ship) that fights its way around the deck, turning
    the stick every 1.6 s (agent/newgame2's "cycle" fight plan); it plays the intro and reaches the trigger of the
    ship's first movie (A01MP05, about 80 gameplay seconds in)."""
    keys, t, n = ['5:start', '14:x', '20:x', '26:x', '32:x'], 3.0, 0
    cycle = ('lup', 'lright', 'ldown', 'lleft')
    while t < seconds:
        keys.append(f'g{t:.1f}:{cycle[n % 4]}*0.3')
        keys += [f'g{t + 0.35 * i:.2f}:cuadrado*0.15' for i in range(3)]
        keys.append(f'g{t + 1.05:.2f}:triangulo*0.15')
        t += 1.6
        n += 1
    return ','.join(keys), t


def run_new_game(outdir, args, seconds=300):
    """The in-game path: the movies a new game plays itself, entered from gameplay (sound state, IOP clock and
    memory as the game leaves them), recorded and judged like the forced ones."""
    log_path, pcm_path = os.path.join(outdir, 'batch0.log'), os.path.join(outdir, 'batch0.pcm')
    card = os.path.join(outdir, 'card0.ps2')
    with open(CARD, 'rb') as src, open(card, 'wb') as dst:
        dst.write(src.read())
    script, _ = new_game_script(seconds - 60)
    env = dict(os.environ, **ENV)
    # with a GOW_MOVIE_OVERRIDE list (e.g. ',A01MP02' style tests: Semo01,A01MP02 replaces the ship's preload) the
    # title menu must not start movies itself
    env['GOW_BONUS_MOVIE_DELAY'] = os.environ.get('GOW_BONUS_MOVIE_DELAY', '99999')
    env.update({'GOW_PAD_GUION': script, 'GOW_GOD_MODE': '1', 'GOW_PLAYER_TRACE': '1', 'GOW_AUDIO_PCM': pcm_path,
                'GOW_MC0': card})
    with open(log_path, 'wb') as log:
        proc = subprocess.Popen([args.exe, ELF], cwd=os.path.dirname(args.exe), env=env, stdout=log,
                                stderr=subprocess.STDOUT)
    start = time.time()
    while proc.poll() is None and time.time() - start < seconds:
        time.sleep(2)
    if proc.poll() is None:
        proc.kill()
        proc.wait()
    text = open(log_path, encoding='utf-8', errors='replace').read()
    movies = [m.group(1) for m in re.finditer(LOAD_LINE, text)]
    rows = analyse(movies, log_path, pcm_path)
    for row in rows:
        row['batch'] = 0
    return rows


def analyse(movies, log_path, pcm_path):
    text = open(log_path, encoding='utf-8', errors='replace').read()
    pcm = open(pcm_path, 'rb').read() if os.path.exists(pcm_path) else b''
    starts = [m.start() for m in re.finditer(LOAD_LINE, text)]
    out = []
    for i, movie in enumerate(movies):
        row = {'movie': movie, 'result': 'bad', 'reasons': []}
        out.append(row)
        if i >= len(starts):
            row['reasons'].append('not played')
            continue
        seg = text[starts[i]:starts[i + 1] if i + 1 < len(starts) else len(text)]
        sync_re = r'\[MPEG:sync\] frame=(\d+) pts=(\d+) wall_ms=([0-9.]+) audio_played=\d+ audio_produced=(\d+)'
        sync = [(int(f), int(p), float(w), int(a)) for f, p, w, a in re.findall(sync_re, seg)]
        sync = [s for s in sync if s[0] >= 30 and s[1] < (1 << 33)]  # pictures without a PTS print -1 (unsigned)
        errors = len(re.findall(ERRORS, seg))
        # output statistics only while the movie plays (a preloaded movie's segment also holds gameplay)
        marks = [m.start() for m in re.finditer(sync_re, seg) if int(m.group(1)) >= 30 and int(m.group(2)) < (1 << 33)]
        playing = seg[marks[0]:seg.find('\n[audio-stats]', marks[-1]) + 200] if marks else seg
        stats = re.findall(r'\[audio-stats\] requested=\d+ missing=(\d+) dropped=(\d+)', playing)
        row['missing'] = sum(int(a) for a, _ in stats)
        row['dropped'] = sum(int(b) for _, b in stats)
        row['errors'] = errors
        if len(sync) < 2:
            row['reasons'].append('no pictures')
            continue
        (f0, t0, w0, a0), (f1, t1, w1, a1) = sync[0], sync[-1]
        pic_s = (t1 - t0) / 90000.0
        row['pictures'] = f1
        row['fps'] = (f1 - f0) / max(1e-6, (w1 - w0) / 1000.0)
        row['audio_s'] = (a1 - a0) / RATE
        row['picture_s'] = pic_s
        lag = [(a - a0) / RATE - (t - t0) / 90000.0 for _, t, _, a in sync]
        row['drift'] = max(lag) - min(lag)
        row.update(pcm_checks(pcm, a0, a1))
        if not 29.0 <= row['fps'] <= 31.0:
            row['reasons'].append(f"{row['fps']:.1f} pictures/s")
        if abs(row['audio_s'] - pic_s) > 0.5:
            row['reasons'].append(f"audio {row['audio_s']:.1f} s for {pic_s:.1f} s of pictures")
        if row['drift'] > 0.25:
            row['reasons'].append(f"A/V drift {row['drift']:.2f} s")
        if row['rms_mean'] < 100:
            row['reasons'].append('no sound')
        elif row['silent_s'] > max(5, pic_s * 0.25):
            row['reasons'].append(f"{row['silent_s']} silent seconds")
        if row['smooth_max'] >= 1.2:
            row['reasons'].append(f"noise (diff/rms {row['smooth_max']:.2f})")
        # more than 0.5 % of the samples at full scale: a movie whose mask leaves music playing (A01MP05) clips a
        # little by design, a wrong gain on the movie track clips far more
        if row['clipped'] > pic_s * RATE * 2 * 0.005:
            row['reasons'].append(f"{row['clipped']} clipped samples")
        if row['repeats'] > 2:
            row['reasons'].append(f"{row['repeats']} repeated blocks")
        if row['dropped'] or row['missing'] > RATE // 10:
            row['reasons'].append(f"output dropped {row['dropped']} / missing {row['missing']} frames")
        if errors:
            row['reasons'].append(f'{errors} runtime errors')
        # a movie started from the title menu must end: its player goes back to idle
        if 'menu sees movie state' in seg and not re.search(r'menu sees movie state 11 -> 0', seg):
            row['reasons'].append(f"never ended (last picture {row['pictures']})")
        if not row['reasons']:
            row['result'] = 'ok'
    return out


def reanalyse(outdir):
    rows = []
    for name in sorted(f for f in os.listdir(outdir) if re.fullmatch(r'batch\d+\.log', f)):
        index = int(name[5:-4])
        text = open(os.path.join(outdir, name), encoding='utf-8', errors='replace').read()
        movies = [m.group(1) for m in re.finditer(LOAD_LINE, text)]
        for row in analyse(movies, os.path.join(outdir, name), os.path.join(outdir, f'batch{index}.pcm')):
            row['batch'] = index
            rows.append(row)
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--only', help='comma list of movie names (default: every movie on the disc)')
    ap.add_argument('--batch', type=int, default=12, help='movies per session')
    ap.add_argument('--out', default=os.path.join(ROOT, 'port', 'movies'))
    ap.add_argument('--exe', default=EXE)
    ap.add_argument('--keep-pcm', action='store_true')
    ap.add_argument('--new-game', type=int, metavar='SECONDS', help='play a new game for SECONDS and judge the movies it plays from its own triggers (intro, ship)')
    ap.add_argument('--reanalyse', help='run directory to judge again (needs --keep-pcm for the sound checks)')
    args = ap.parse_args()
    args.exe = os.path.abspath(args.exe)
    if args.reanalyse:
        return report(os.path.abspath(args.reanalyse), reanalyse(os.path.abspath(args.reanalyse)))
    if args.new_game:
        outdir = os.path.join(os.path.abspath(args.out), datetime.datetime.now().strftime('%Y%m%d_%H%M%S'))
        os.makedirs(outdir, exist_ok=True)
        rows = run_new_game(outdir, args, args.new_game)
        for row in rows:
            print(f"  {row['movie']:10s} {row['result']:3s} {'; '.join(row['reasons'])}", flush=True)
        return report(outdir, rows)
    sizes = movie_list()
    movies = [m.upper() for m in args.only.split(',')] if args.only else sorted(sizes)
    for m in movies:
        sizes.setdefault(m, 50e6)
    outdir = os.path.join(os.path.abspath(args.out), datetime.datetime.now().strftime('%Y%m%d_%H%M%S'))
    os.makedirs(outdir, exist_ok=True)
    rows = []
    for index, k in enumerate(range(0, len(movies), args.batch)):
        batch = movies[k:k + args.batch]
        print(f'batch {index}: {",".join(batch)}', flush=True)
        log_path, pcm_path, secs = run_batch(batch, sizes, outdir, index, args)
        for row in analyse(batch, log_path, pcm_path):
            row['batch'] = index
            rows.append(row)
            print(f"  {row['movie']:10s} {row['result']:3s} {'; '.join(row['reasons'])}", flush=True)
        if not args.keep_pcm and os.path.exists(pcm_path):
            os.remove(pcm_path)
    return report(outdir, rows)


def report(outdir, rows):
    lines = ['# Movie check ' + os.path.basename(outdir), '',
             '| movie | batch | pictures | pictures/s | picture s | audio s | A/V drift s | mean RMS | silent s | '
             'diff/rms max | clipped | repeats | dropped | result |', '|' + '---|' * 14]
    for r in rows:
        lines.append('| {movie} | {batch} | {p} | {fps} | {ps} | {aus} | {dr} | {rms} | {sil} | {sm} | {cl} | {rep} | {dro} | {res} |'.format(
            movie=r['movie'], batch=r['batch'], p=r.get('pictures', '-'), fps=f"{r['fps']:.2f}" if 'fps' in r else '-',
            ps=f"{r['picture_s']:.1f}" if 'picture_s' in r else '-', aus=f"{r['audio_s']:.1f}" if 'audio_s' in r else '-',
            dr=f"{r['drift']:.2f}" if 'drift' in r else '-', rms=f"{r['rms_mean']:.0f}" if 'rms_mean' in r else '-',
            sil=r.get('silent_s', '-'), sm=f"{r['smooth_max']:.2f}" if 'smooth_max' in r else '-',
            cl=r.get('clipped', '-'), rep=r.get('repeats', '-'), dro=r.get('dropped', '-'),
            res=r['result'] + (': ' + '; '.join(r['reasons']) if r['reasons'] else '')))
    bad = [r['movie'] for r in rows if r['result'] != 'ok']
    lines += ['', f'{len(rows) - len(bad)} of {len(rows)} movies ok' + (f'; bad: {", ".join(bad)}' if bad else '')]
    open(os.path.join(outdir, 'report.md'), 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
    json.dump(rows, open(os.path.join(outdir, 'report.json'), 'w'), indent=1)
    print('\n'.join(lines[-1:]))
    print('report:', os.path.join(outdir, 'report.md'))
    return 1 if bad else 0




if __name__ == '__main__':
    sys.exit(main())
