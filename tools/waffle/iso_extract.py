"""ISO9660 lister/extractor for PS2 discs (no external deps). Handles dual-layer DVDs: layer 1 has its own
volume descriptor right after layer 0, with extents relative to (that sector - 16).

usage: iso_extract.py ISO [OUTDIR] [--list] [--only NAME,NAME] [--layout]

--layout also writes OUTDIR/.disc_layout (text manifest) and OUTDIR/.disc_meta (every non-zero sector that does
not belong to a file: volume descriptors, UDF structures, directories). With them the runtime serves the extracted
files at their original sector numbers, reproducing the disc exactly for code that reads raw sectors."""
import os, struct, sys

SECTOR = 2048


def read_dir(f, lba, size, path, out, dirs, base=0):
    dirs.append((base + lba, size))
    f.seek((base + lba) * SECTOR)
    data = f.read(size)
    off = 0
    while off < len(data):
        rlen = data[off]
        if rlen == 0:  # records never span sectors
            off = (off // SECTOR + 1) * SECTOR
            continue
        rec = data[off:off + rlen]
        ext_lba = struct.unpack_from('<I', rec, 2)[0]
        ext_len = struct.unpack_from('<I', rec, 10)[0]
        flags = rec[25]
        name = rec[33:33 + rec[32]]
        off += rlen
        if name in (b'\x00', b'\x01'):
            continue
        name = name.decode('ascii', 'replace').split(';')[0]
        full = f'{path}/{name}' if path else name
        if flags & 2:
            read_dir(f, ext_lba, ext_len, full, out, dirs, base)
        else:
            out.append((full, base + ext_lba, ext_len))


def scan(f):
    f.seek(16 * SECTOR)
    pvd = f.read(SECTOR)
    assert pvd[1:6] == b'CD001', 'not ISO9660'
    files, dirs = [], []
    root = pvd[156:156 + 34]
    read_dir(f, struct.unpack_from('<I', root, 2)[0], struct.unpack_from('<I', root, 10)[0], '', files, dirs)
    layer0 = struct.unpack_from('<I', pvd, 80)[0]
    layer1 = 0
    f.seek(layer0 * SECTOR)
    pvd1 = f.read(SECTOR)
    if pvd1[1:6] == b'CD001':
        layer1 = layer0 - 16
        root1 = pvd1[156:156 + 34]
        read_dir(f, struct.unpack_from('<I', root1, 2)[0], struct.unpack_from('<I', root1, 10)[0], '', files,
                 dirs, layer1)
    return files, layer1


def write_layout(f, files, layer1, outdir):
    total = os.fstat(f.fileno()).st_size // SECTOR
    covered = sorted((lba, lba + (size + SECTOR - 1) // SECTOR) for _, lba, size in files)
    meta = []
    lsn = 0
    for start, end in covered + [(total, total)]:
        for s in range(lsn, start):
            f.seek(s * SECTOR)
            data = f.read(SECTOR)
            if any(data):
                meta.append((s, data))
        lsn = max(lsn, end)
    with open(os.path.join(outdir, '.disc_meta'), 'wb') as m:
        for s, data in meta:
            m.write(struct.pack('<I', s) + data)
    with open(os.path.join(outdir, '.disc_layout'), 'w', newline='\n') as m:
        m.write(f'sectors {total}\nlayer1 {layer1}\n')
        for name, lba, size in sorted(files, key=lambda e: e[1]):
            m.write(f'file {lba} {size} {name}\n')
    print(f'layout: {len(files)} files, {len(meta)} metadata sectors, layer1={layer1}')


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    iso = args[0]
    outdir = args[1] if len(args) > 1 else None
    only = None
    if '--only' in sys.argv:
        only = set(sys.argv[sys.argv.index('--only') + 1].upper().split(','))
        args = [a for a in args if a.upper().split(',') != list(only)]
    with open(iso, 'rb') as f:
        files, layer1 = scan(f)
        for name, lba, size in files:
            if '--list' in sys.argv:
                print(f'{lba:8d} {size:12d} {name}')
            if outdir and (only is None or name.upper() in only):
                dst = os.path.join(outdir, *name.split('/'))
                os.makedirs(os.path.dirname(dst) or '.', exist_ok=True)
                f.seek(lba * SECTOR)
                with open(dst, 'wb') as o:
                    left = size
                    while left:
                        chunk = f.read(min(left, 1 << 24))
                        o.write(chunk)
                        left -= len(chunk)
        if outdir and '--layout' in sys.argv:
            write_layout(f, files, layer1, outdir)


if __name__ == '__main__':
    main()
