// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#pragma once

#include <algorithm>
#include <cmath>

struct GSSpriteAxis
{
    int first = 0;
    int last = -1;
    float origin = 0.0f;
    float scale = 1.0f;
};

inline GSSpriteAxis gsSpriteAxis(float p0, float p1, float offset)
{
    GSSpriteAxis axis;
    axis.origin = p0 - offset;
    const float end = p1 - offset;
    const float extent = end - axis.origin;
    axis.first = static_cast<int>(std::ceil(std::min(axis.origin, end)));
    axis.last = static_cast<int>(std::ceil(std::max(axis.origin, end))) - 1;
    axis.scale = extent != 0.0f ? 1.0f / extent : 0.0f;
    return axis;
}

inline float gsSpriteParameter(const GSSpriteAxis &axis, int pixel)
{
    return (static_cast<float>(pixel) - axis.origin) * axis.scale;
}
