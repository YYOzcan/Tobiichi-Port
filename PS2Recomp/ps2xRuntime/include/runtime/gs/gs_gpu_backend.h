// GOW-Port: adaptado de Taylor N. Albarnaz / LightVelox (GPL-3.0).
// Origen: PS2Recomp sotc-port, ac9efa070638ad3b3accd284de6f898d5ab271d1.
#pragma once

#include "runtime/gs/gs_backend.h"
#include "runtime/gs/gs_backend_state.h"

#include <array>
#include <bitset>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class GSGpuBackend final : public GSRasterBackend, public GSBackendStateAccess
{
public:
    GSGpuBackend();
    ~GSGpuBackend() override;

    void Initialize(uint8_t *vram, uint32_t vramSize) override;
    void Reset() override;
    // GOW-Port: comprobar la inicialización antes de elegir el backend.
    bool IsReady() const;

    void Submit(const GSPrimitiveBatch &batch) override;
    void LoadClut(const GSTex0Reg &tex0, const GSTexClutReg &texclut) override;
    void BeginTransfer(const GSTransferCommand &command) override;
    void UploadImage(const uint8_t *data, uint32_t sizeBytes) override;

    void Flush() override;
    void TextureFlush() override;
    void Sync(GSSyncReason reason) override;
    PresentationFrame Present(const GSPresentationRequest &request) override;

    bool ClearFramebuffer(const GSContext &context, uint32_t rgba) override;
    uint32_t ConsumeLocalToHostBytes(uint8_t *dst, uint32_t maxBytes) override;

    uint32_t ReadVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const override;
    void WriteVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t value) override;
    void SnapshotVram(std::vector<uint8_t> &out) const override;
    GSTransferSnapshot GetTransferSnapshot() const override;

    bool ExportState(GSBackendState &out) override;
    bool ImportState(const GSBackendState &state) override;

    struct Stats
    {
        uint64_t prims = 0;
        uint64_t batches = 0;
        uint64_t tiles = 0;
        uint64_t clutLoads = 0;
        uint64_t flushTarget = 0;
        uint64_t flushTexture = 0;
        uint64_t flushOther = 0;
    };
    const Stats &GetStats() const { return m_stats; }

    static void SetAsyncPresentDefault(bool enabled);
    void SetTexturePageCacheEnabled(bool enabled);
    void SetFastTriangleSetupEnabled(bool enabled);
    void SetHardwareRasterAllowed(bool allowed);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
    Stats m_stats;
};
