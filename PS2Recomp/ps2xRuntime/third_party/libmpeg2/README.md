# libmpeg2 0.5.1 (vendored)

MPEG-2 video decoder by Michel Lespinasse and Aaron Holtzman, from mpeg2dec 0.5.1
(Debian `mpeg2dec_0.5.1.orig.tar.gz`). GPL version 2 or later (COPYING); the runtime is GPL-3.0.

Only the decoder core is kept (no CPU-specific acceleration, no output/convert helpers). `config.h` is written for
this project: plain C paths on every platform. Used by `src/lib/Kernel/Stubs/MPEG.cpp` to decode the game's FMV.
