#include "Common.h"
#include "DMA.h"

namespace ps2_stubs
{
    namespace
    {
        struct SceDmaEnv
        {
            uint8_t sts = 0;
            uint8_t std = 0;
            uint8_t mfd = 0;
            uint8_t rele = 0;
            uint32_t pcr = 0;
            uint32_t sqwc = 0;
            uint32_t rbor = 0;
            uint32_t rbsr = 0;
        };

        static_assert(sizeof(SceDmaEnv) == 0x14, "sceDmaEnv must match the guest ABI");

        // GOW-Port: there is no DMA controller (docs/native-port.md, step 2): the environment is kept for sceDmaGetEnv
        // only; the values the game sets (stall control, MFIFO, priorities) have no effect on native transfers.
        std::mutex g_dmaEnvMutex;
        SceDmaEnv g_dmaCurrentEnv;
    }

    void DmaAddr(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        setReturnU32(ctx, getRegU32(ctx, 4));
    }

    void sceDmaCallback(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaCallback", rdram, ctx, runtime);
    }

    void sceDmaDebug(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaDebug", rdram, ctx, runtime);
    }

    void sceDmaGetChan(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t chanArg = getRegU32(ctx, 4);
        const uint32_t channelBase = resolveDmaChannelBase(rdram, chanArg);
        setReturnU32(ctx, channelBase);
    }

    void sceDmaGetEnv(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t envAddr = getRegU32(ctx, 4);
        if (uint8_t *dst = getMemPtr(rdram, envAddr))
        {
            std::lock_guard<std::mutex> lock(g_dmaEnvMutex);
            std::memcpy(dst, &g_dmaCurrentEnv, sizeof(g_dmaCurrentEnv));
        }
        setReturnU32(ctx, envAddr);
    }

    void sceDmaLastSyncTime(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaLastSyncTime", rdram, ctx, runtime);
    }

    void sceDmaPause(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaPause", rdram, ctx, runtime);
    }

    void sceDmaPutEnv(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t envAddr = getRegU32(ctx, 4);
        const uint8_t *src = getConstMemPtr(rdram, envAddr);
        if (!src || !runtime)
        {
            setReturnS32(ctx, -1);
            return;
        }

        SceDmaEnv env{};
        std::memcpy(&env, src, sizeof(env));

        if (env.sts >= 10u)
        {
            setReturnS32(ctx, -1);
            return;
        }
        if (env.std >= 10u)
        {
            setReturnS32(ctx, -2);
            return;
        }
        if (env.mfd >= 10u)
        {
            setReturnS32(ctx, -3);
            return;
        }
        if (env.rele >= 7u)
        {
            setReturnS32(ctx, -4);
            return;
        }

        {
            std::lock_guard<std::mutex> lock(g_dmaEnvMutex);
            g_dmaCurrentEnv = env;
        }

        setReturnS32(ctx, 0);
    }

    void sceDmaPutStallAddr(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        static uint32_t stallAddress = 0u;
        const uint32_t newAddr = getRegU32(ctx, 4);
        const uint32_t oldAddr = stallAddress;
        if (newAddr != 0xFFFFFFFFu)
            stallAddress = newAddr;
        setReturnU32(ctx, oldAddr);
    }

    void sceDmaRecv(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaRecv", rdram, ctx, runtime);
    }

    void sceDmaRecvI(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaRecvI", rdram, ctx, runtime);
    }

    void sceDmaRecvN(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaRecvN", rdram, ctx, runtime);
    }

    void sceDmaReset(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        {
            std::lock_guard<std::mutex> lock(g_dmaEnvMutex);
            g_dmaCurrentEnv = {};
        }

        setReturnS32(ctx, 0);
    }

    void sceDmaRestart(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaRestart", rdram, ctx, runtime);
    }

    void sceDmaSend(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        setReturnS32(ctx, submitDmaSend(rdram, ctx, runtime, false));
    }

    void sceDmaSendI(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        setReturnS32(ctx, submitDmaSend(rdram, ctx, runtime, false));
    }

    void sceDmaSendM(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        setReturnS32(ctx, submitDmaSend(rdram, ctx, runtime, false));
    }

    void sceDmaSendN(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        setReturnS32(ctx, submitDmaSend(rdram, ctx, runtime, true));
    }

    void sceDmaSync(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        setReturnS32(ctx, submitDmaSync(rdram, ctx, runtime));
    }

    void sceDmaSyncN(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        setReturnS32(ctx, submitDmaSync(rdram, ctx, runtime));
    }

    void sceDmaWatch(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        TODO_NAMED("sceDmaWatch", rdram, ctx, runtime);
    }
}
