// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

struct GSTriangleRaster
{
    int64_t x[3]{};
    int64_t y[3]{};
    int64_t a[3]{};
    int64_t b[3]{};
    int64_t c[3]{};
    int64_t bias[3]{};
    int64_t area = 0;
    double invArea = 0.0;
    int minX = 0;
    int maxX = -1;
    int minY = 0;
    int maxY = -1;
    int winding = 1;
};

inline int64_t gsFloorDiv16(int64_t v)
{
    return v >= 0 ? v / 16 : -((-v + 15) / 16);
}

inline int64_t gsRoundCoordinate(float value, bool fast)
{
    const double scaled = static_cast<double>(value) * 16.0;
    if (fast && scaled >= -1048576.0 && scaled <= 1048576.0)
        return static_cast<int64_t>(scaled < 0.0 ? scaled - 0.5 : scaled + 0.5);
    return std::llround(scaled);
}

inline bool gsTriangleSetup(float x0, float y0, float x1, float y1, float x2, float y2, int ofx, int ofy, GSTriangleRaster &t, bool fast = false)
{
    const float xs[3] = {x0, x1, x2};
    const float ys[3] = {y0, y1, y2};
    for (int i = 0; i < 3; ++i)
    {
        t.x[i] = gsRoundCoordinate(xs[i], fast) - ofx;
        t.y[i] = gsRoundCoordinate(ys[i], fast) - ofy;
    }
    for (int i = 0; i < 3; ++i)
    {
        const int p = (i + 1) % 3;
        const int q = (i + 2) % 3;
        t.a[i] = -(t.y[q] - t.y[p]);
        t.b[i] = t.x[q] - t.x[p];
        t.c[i] = -(t.a[i] * t.x[p] + t.b[i] * t.y[p]);
    }
    t.area = t.a[0] * t.x[0] + t.b[0] * t.y[0] + t.c[0];
    if (t.area == 0)
        return false;
    t.winding = t.area < 0 ? -1 : 1;
    if (t.area < 0)
    {
        t.area = -t.area;
        for (int i = 0; i < 3; ++i)
        {
            t.a[i] = -t.a[i];
            t.b[i] = -t.b[i];
            t.c[i] = -t.c[i];
        }
    }
    for (int i = 0; i < 3; ++i)
        t.bias[i] = (t.a[i] > 0 || (t.a[i] == 0 && t.b[i] > 0)) ? 1 : 0;
    t.invArea = 1.0 / static_cast<double>(t.area);
    const int64_t minX16 = fast ? std::min(t.x[0], std::min(t.x[1], t.x[2])) : std::min({t.x[0], t.x[1], t.x[2]});
    const int64_t maxX16 = fast ? std::max(t.x[0], std::max(t.x[1], t.x[2])) : std::max({t.x[0], t.x[1], t.x[2]});
    const int64_t minY16 = fast ? std::min(t.y[0], std::min(t.y[1], t.y[2])) : std::min({t.y[0], t.y[1], t.y[2]});
    const int64_t maxY16 = fast ? std::max(t.y[0], std::max(t.y[1], t.y[2])) : std::max({t.y[0], t.y[1], t.y[2]});
    t.minX = static_cast<int>(-gsFloorDiv16(-minX16));
    t.maxX = static_cast<int>(gsFloorDiv16(maxX16));
    t.minY = static_cast<int>(-gsFloorDiv16(-minY16));
    t.maxY = static_cast<int>(gsFloorDiv16(maxY16));
    return true;
}

inline int64_t gsTriangleEdge(const GSTriangleRaster &t, int i, int px, int py)
{
    return t.a[i] * (static_cast<int64_t>(px) * 16) + t.b[i] * (static_cast<int64_t>(py) * 16) + t.c[i];
}

inline bool gsTriangleCovers(const GSTriangleRaster &t, const int64_t e[3])
{
    return e[0] + t.bias[0] > 0 && e[1] + t.bias[1] > 0 && e[2] + t.bias[2] > 0;
}

inline float gsTriangleWeight(const GSTriangleRaster &t, int64_t e)
{
    return static_cast<float>(static_cast<double>(e) * t.invArea);
}
