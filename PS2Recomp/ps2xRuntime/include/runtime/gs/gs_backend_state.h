// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#pragma once

#include "runtime/gs/gs_types.h"
#include "runtime/gs/gs_upload24.h" // GOW-Port: exportar tambien el pixel pendiente.

#include <array>
#include <cstdint>
#include <vector>

struct GSBackendState
{
    static constexpr uint32_t kCachePageSize = 8192u;

    std::array<uint16_t, 512> clut{};
    std::array<uint32_t, 2> clutCbp{};
    uint32_t cachePageBase = UINT32_MAX;
    std::array<uint8_t, kCachePageSize> cacheBytes{};
    GSTransferCommand transfer{};
    GSTransferSnapshot transferState{};
    GSUpload24State upload24{};
    std::vector<uint8_t> localToHost;
    uint64_t localToHostReadPos = 0u;
};

class GSBackendStateAccess
{
public:
    virtual ~GSBackendStateAccess() = default;

    virtual bool ExportState(GSBackendState &out) = 0;
    virtual bool ImportState(const GSBackendState &state) = 0;
};
