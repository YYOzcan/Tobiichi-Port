/* GOW-Port: configuration for the vendored libmpeg2 0.5.1: portable C paths only (no CPU-specific acceleration),
   so the same code builds for x64 and AArch64 (Switch). */
#ifndef LIBMPEG2_PORT_CONFIG_H
#define LIBMPEG2_PORT_CONFIG_H
#if defined(__GNUC__) || defined(__clang__)
#define HAVE_BUILTIN_EXPECT 1
#define ATTRIBUTE_ALIGNED_MAX 64
#endif
#if defined(_MSC_VER) && !defined(__cplusplus)
#define inline __inline
#endif
#endif
