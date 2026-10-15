"""Status map: docs/status-map/data.toml -> docs/status-map/map.svg (README picture) + detail.md (table).

usage: python tools/status_map.py

Two treemaps side by side: the Sony SDK libraries linked into the game (one cell per recompiled function) and the
PS2 hardware components (box area = weight). Colours: ok = green, partial = amber (hatched), pending = grey.
Scores: libraries = share of ok functions (partial counts 1/2), hardware = weighted the same way. The SVG follows the
viewer's light/dark theme.
"""
import math
import os
import tomllib
from xml.sax.saxutils import escape

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DIR = os.path.join(ROOT, 'docs', 'status-map')
W, H = 900, 424
PANEL_Y, PANEL_H = 112, 258
LEFT = (16, 440 - 16)    # x, width
RIGHT = (460, 884 - 460)
SCORE = {'ok': 1.0, 'partial': 0.5, 'pending': 0.0}
EMOJI = {'ok': '✅ ok', 'partial': '🔧 partial', 'pending': '⏳ pending'}

STYLE = """<style>
  .bg { fill: #ffffff; } .line { stroke: #d0d7de; } .t1 { fill: #1f2328; } .t2 { fill: #59636e; }
  .ok { fill: #0ca30c; } .partial { fill: #fab219; } .pending { fill: #c4c8ce; } .gap { stroke: #ffffff; }
  .hatch { stroke: #8a5a00; } .chip { fill: #1f2328; fill-opacity: .8; } .chip-t { fill: #ffffff; }
  .on-ok, .on-partial { fill: #ffffff; } .on-pending { fill: #1f2328; }
  .bk { fill: #59636e; } .bt { fill: #ffffff; }
  @media (prefers-color-scheme: dark) {
    .bg { fill: #0d1117; } .line { stroke: #30363d; } .t1 { fill: #e6edf3; } .t2 { fill: #9198a1; }
    .pending { fill: #4b525c; } .gap { stroke: #0d1117; } .on-pending { fill: #e6edf3; } .bk { fill: #3d444d; }
  }
</style>
<defs><pattern id="hatch" width="6" height="6" patternUnits="userSpaceOnUse" patternTransform="rotate(45)">
<line class="hatch" x1="0" y1="0" x2="0" y2="6" stroke-width="1.5" stroke-opacity=".55"/></pattern></defs>"""


def squarify(sizes, x, y, w, h):
    """Squarified treemap (Bruls et al.): rectangles for `sizes` (sorted large first) inside x,y,w,h, in input order."""
    total = float(sum(sizes))
    if total <= 0:
        return [(x, y, 0, 0) for _ in sizes]
    areas = [s * w * h / total for s in sizes]
    out, i = [], 0
    while i < len(areas):
        short = min(w, h)
        row = [areas[i]]
        i += 1

        def worst(r):
            s = sum(r)
            return max(max(short * short * a / (s * s), s * s / (short * short * a)) for a in r)
        while i < len(areas) and worst(row + [areas[i]]) <= worst(row):
            row.append(areas[i])
            i += 1
        s = sum(row)
        if w >= h:  # column on the left
            cw = s / h
            cy = y
            for a in row:
                out.append((x, cy, cw, a / cw))
                cy += a / cw
            x, w = x + cw, w - cw
        else:       # row on top
            rh = s / w
            cx = x
            for a in row:
                out.append((cx, y, a / rh, rh))
                cx += a / rh
            y, h = y + rh, h - rh
    return out


def ordered(items, size):
    """Items sorted by size (largest first), as squarify expects."""
    return sorted(items, key=size, reverse=True)


def rect(cls, x, y, w, h, extra=''):
    return f'<rect class="{cls}" x="{x:.1f}" y="{y:.1f}" width="{max(w, 0):.1f}" height="{max(h, 0):.1f}"{extra}/>'


def cell(state, x, y, w, h, gap=1.0):
    out = [rect(f'{state} gap', x, y, w, h, f' stroke-width="{gap}"')]
    if state == 'partial':
        out.append(f'<rect fill="url(#hatch)" x="{x:.1f}" y="{y:.1f}" width="{max(w, 0):.1f}" height="{max(h, 0):.1f}"/>')
    return out


def chip(x, y, text):
    w = len(text) * 6.6 + 10
    return [f'<rect class="chip" x="{x + 3:.1f}" y="{y + 3:.1f}" width="{w:.1f}" height="16" rx="3"/>',
            f'<text class="chip-t" x="{x + 8:.1f}" y="{y + 15:.1f}" font-size="11.5">{escape(text)}</text>']


def label(state, x, y, w, h, text):
    """Centered label; vertical when the box is too narrow for horizontal text."""
    tw = len(text) * 7.0
    cx, cy = x + w / 2, y + h / 2
    if tw <= w - 6:
        return [f'<text class="on-{state}" x="{cx:.1f}" y="{cy + 4:.1f}" font-size="12" text-anchor="middle">{escape(text)}</text>']
    if tw <= h - 6:
        return [f'<text class="on-{state}" x="{cx:.1f}" y="{cy:.1f}" font-size="12" text-anchor="middle" dominant-baseline="central" '
                f'transform="rotate(-90 {cx:.1f} {cy:.1f})">{escape(text)}</text>']
    return [f'<text class="on-{state}" x="{cx:.1f}" y="{cy + 3:.1f}" font-size="9.5" text-anchor="middle">{escape(text)}</text>']


def libraries(data):
    merged = {}
    for lib in data['library']:
        m = merged.setdefault(lib['name'], dict(lib, functions=0))
        m['functions'] += lib['functions']
    return list(merged.values())


def lib_score(libs):
    n = sum(lib['functions'] for lib in libs)
    return 100.0 * sum(lib['functions'] * SCORE[lib['state']] for lib in libs) / n, n


def hw_score(groups):
    items = [i for g in groups for i in g['item']]
    return 100.0 * sum(i['weight'] * SCORE[i['state']] for i in items) / sum(i['weight'] for i in items)


def draw_libraries(libs, x0, w0):
    body, chips = [], []
    libs = ordered(libs, lambda lib: lib['functions'])
    for lib, (x, y, w, h) in zip(libs, squarify([lib['functions'] for lib in libs], x0, PANEL_Y, w0, PANEL_H)):
        n = lib['functions']
        tip = f'{lib["name"]}: {n} functions, {lib["state"]}' + (f' - {lib["note"]}' if lib.get('note') else '')
        body.append(f'<g><title>{escape(tip)}</title>')
        # n cells in a grid filling the rectangle (cells of equal size, row by row)
        cols = max(1, round(math.sqrt(n * w / h))) if h > 0 else n
        rows = math.ceil(n / cols)
        cw, ch = w / cols, h / rows
        for k in range(n):
            r, c = divmod(k, cols)
            body += cell(lib['state'], x + c * cw, y + r * ch, cw, ch)
        body.append('</g>')
        if w > 40 and h > 22:
            chips += chip(x, y, lib['name'])
    return body + chips


def draw_hardware(groups, x0, w0):
    body = []
    groups = ordered(groups, lambda g: sum(i['weight'] for i in g['item']))
    sizes = [sum(i['weight'] for i in g['item']) for g in groups]
    for g, (gx, gy, gw, gh) in zip(groups, squarify(sizes, x0, PANEL_Y, w0, PANEL_H)):
        items = ordered(g['item'], lambda i: i['weight'])
        pad = 2
        top = pad  # the group chip overlays the first box
        for it, (x, y, w, h) in zip(items, squarify([i['weight'] for i in items], gx + pad, gy + top, gw - 2 * pad, gh - top - pad)):
            body.append(f'<g><title>{escape(it["name"] + " (" + it["state"] + ")")}</title>')
            body += cell(it['state'], x, y, w, h, 1.5)
            body += label(it['state'], x, y, w, h, it['short'])
            body.append('</g>')
        body += chip(gx, gy, g['group'])
    return body


def badge(x, key, value):
    kw, vw = len(key) * 7 + 22, len(value) * 7.4 + 16
    cls = 'ok' if value == '100%' else 'partial'
    return [f'<rect class="bk" x="{x}" y="56" width="{kw:.0f}" height="22" rx="3"/>',
            f'<text class="bt" x="{x + kw / 2:.1f}" y="71" font-size="12.5" text-anchor="middle">{escape(key)}</text>',
            f'<rect class="{cls}" x="{x + kw:.1f}" y="56" width="{vw:.0f}" height="22" rx="3"/>',
            f'<text class="t1" x="{x + kw + vw / 2:.1f}" y="71" font-size="12.5" text-anchor="middle">{value}</text>'], kw + vw


def svg(data):
    libs = libraries(data)
    ls, n = lib_score(libs)
    hs = hw_score(data['hardware'])
    out = [f'<svg xmlns="http://www.w3.org/2000/svg" width="{W}" height="{H}" viewBox="0 0 {W} {H}" '
           "font-family=\"-apple-system,BlinkMacSystemFont,'Segoe UI',Helvetica,Arial,sans-serif\" role=\"img\">",
           f'<title>Status: libraries* {ls:.1f}%, hardware {hs:.1f}%</title>', STYLE,
           f'<rect class="bg" width="{W}" height="{H}" rx="6"/>',
           '<text class="t1" x="16" y="34" font-size="24" font-weight="600">Status</text>',
           '<line class="line" x1="16" y1="44" x2="884" y2="44" stroke-width="1"/>']
    x = 16
    for key, val in [('libraries*', f'{ls:.1f}%'), ('hardware', f'{hs:.1f}%')]:
        parts, w = badge(x, key, val)
        out += parts
        x += w + 10
    ok_fn = sum(lib['functions'] for lib in libs if lib['state'] == 'ok')
    out.append(f'<text class="t1" x="{LEFT[0]}" y="103" font-size="14">Sony SDK libraries*: {ls:.1f}% ({ok_fn}/{n})</text>')
    out.append(f'<text class="t1" x="{RIGHT[0]}" y="103" font-size="14">PS2 hardware → native: {hs:.1f}%</text>')
    out += draw_libraries(libs, *LEFT)
    out += draw_hardware(data['hardware'], *RIGHT)
    lx = 16
    for state, text in [('ok', 'Native / working'), ('partial', 'Partial'), ('pending', 'Pending')]:
        out.append(rect(state, lx, 383, 12, 12, ' rx="2"'))
        if state == 'partial':
            out.append(f'<rect fill="url(#hatch)" x="{lx}" y="383" width="12" height="12" rx="2"/>')
        out.append(f'<text class="t2" x="{lx + 17}" y="394" font-size="12.5">{text}</text>')
        lx += 17 + len(text) * 7 + 26
    out.append('<text class="t2" x="16" y="414" font-size="11">* Functions of the static Sony libraries linked into '
               'SCUS_973.99 (recompiled output). Hardware: weighted per component.</text>')
    out.append('</svg>')
    return '\n'.join(out) + '\n'


def detail(data):
    libs = libraries(data)
    ls, n = lib_score(libs)
    out = ['# Status detail', '', 'Generated from `data.toml` by `tools/status_map.py`; do not edit by hand.', '',
           f'## Sony SDK libraries ({ls:.1f}%, {n} functions)', '', '| Library | Functions | State | Note |', '|---|---:|---|---|']
    for lib in libs:
        out.append(f'| {lib["name"]} | {lib["functions"]} | {EMOJI[lib["state"]]} | {lib.get("note", "")} |')
    out += ['', f'## PS2 hardware ({hw_score(data["hardware"]):.1f}%)', '', '| Group | Component | Weight | State |',
            '|---|---|---:|---|']
    for g in data['hardware']:
        for i in g['item']:
            out.append(f'| {g["group"]} | {i["name"]} | {i["weight"]} | {EMOJI[i["state"]]} |')
    return '\n'.join(out) + '\n'


def main():
    with open(os.path.join(DIR, 'data.toml'), 'rb') as f:
        data = tomllib.load(f)
    for path, text in [('map.svg', svg(data)), ('detail.md', detail(data))]:
        with open(os.path.join(DIR, path), 'w', encoding='utf-8', newline='\n') as f:
            f.write(text)
    print('wrote', os.path.join(DIR, 'map.svg'), 'and detail.md')


if __name__ == '__main__':
    main()
