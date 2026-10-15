// Shim for PCSX2's Gif_Unit.h: XGKICK hands PATH1 data to the bridge, which forwards complete packets to our GS.
#pragma once
#include "Common.h"

enum GIF_PATH
{
    GIF_PATH_1 = 0,
    GIF_PATH_2,
    GIF_PATH_3,
};
enum GIF_TRANSFER_TYPE
{
    GIF_TRANS_XGKICK = 1,
};

struct Pcsx2GifUnitShim
{
    // Size of the GIF tag at offset (tag + data) | EOP << 31, as PCSX2 returns for the VU1 interpreter.
    u32 GetGSPacketSize(GIF_PATH pathIdx, u8 *mem, u32 offset = 0, u32 size = ~0u, bool flush = false);
    u32 TransferGSPacketData(GIF_TRANSFER_TYPE type, u8 *mem, u32 size, bool aligned = false);
    struct
    {
    } gifPath[3];
};
extern Pcsx2GifUnitShim gifUnit;
