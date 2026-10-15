"""Summarize PS2X_GS_WORKER_TRACE output: flip intervals and big worker job durations.
usage: python -I tools/gsw_trace.py port/<run>.log"""
import sys
ev = []
for line in open(sys.argv[1], encoding='utf-8', errors='replace'):
    if '[gsw-trace]' in line:
        _, t, a, b = line.split()[:4]
        ev.append((float(t) / 1000.0, a, b))
flips = [t for t, a, b in ev if a == 'enter' and b == '0x1837B8']
iv = [flips[i + 1] - flips[i] for i in range(len(flips) - 1)]
print(f"flips={len(flips)} mean_interval_ms={sum(iv) / max(1, len(iv)):.1f}")
starts = {}
jobs = []
for t, a, b in ev:
    if a == 'job-start':
        starts[b] = t
    elif a == 'job-done' and b in starts and int(b) > 100000:
        jobs.append(t - starts.pop(b))
print(f"big jobs={len(jobs)} mean_ms={sum(jobs) / max(1, len(jobs)):.1f} min={min(jobs, default=0):.1f} max={max(jobs, default=0):.1f}")
waits = []
enter = None
for t, a, b in ev:
    if b == '0x183878':
        if a == 'enter':
            enter = t
        elif enter is not None:
            waits.append(t - enter)
            enter = None
print(f"WaitForDMAComplete mean_ms={sum(waits) / max(1, len(waits)):.1f}")
