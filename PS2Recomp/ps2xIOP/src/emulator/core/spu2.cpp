#include "spu2.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <string>
#include <unordered_map>

namespace ps2x::iop::detail
{
    namespace
    {
        constexpr int32_t kAdpcmFilters[5][2] = {{0, 0}, {60, 0}, {115, -52}, {98, -55}, {122, -60}};
        constexpr size_t kMaxBufferedFrames = 48000u * 2u; // 2 s; si nadie consume, se descarta lo mas antiguo

        int16_t clamp16(int32_t value) noexcept
        {
            return static_cast<int16_t>(std::clamp(value, -32768, 32767));
        }

        // GOW-Port: ADMA (AutoDMA, sceSdBlockTrans; God of War lo usa para el sonido de los vídeos). Con el bit del núcleo
        // en ADMAS, su DMA no escribe en la TSA: entrega PCM s16 en bloques de 1 KB (256 muestras izquierdas y luego 256
        // derechas) que el SPU2 toma a 48 kHz como entrada de datos de sonido (volumen BVOL, MMIX bits 7/6 a la mezcla
        // seca). Como en el hardware, cada bloque se lee de la RAM del IOP cuando hace falta, y el DMA termina cuando se
        // ha leído el último (iop_memory.cpp retrasa su interrupción con spu2AdmaRetardo). Lo usa solo el hilo del IOP.
        struct AdmaSegmento
        {
            const uint8_t *origen = nullptr; // siguiente bloque sin leer (RAM del IOP)
            size_t restantes = 0;            // bytes aún sin leer
        };
        struct AdmaNucleo
        {
            // DMA en curso y los que ya han empezado detrás de él. La interrupción de fin llega cuando el SPU2 debería
            // haber leído el último bloque, pero su reloj de muestras va algo por detrás del del IOP: si el siguiente DMA
            // sustituyera al actual, se perdería su último bloque (se oía 1 de cada 8 bloques saltado).
            std::deque<AdmaSegmento> cola;
            std::array<int16_t, 256> izquierda{}, derecha{};
            uint32_t posicion = 256; // 256: hace falta el bloque siguiente
            uint64_t retardo = 0;    // ciclos del IOP hasta leer el último bloque del DMA recién empezado
        };
        struct EstadoAdma
        {
            std::array<AdmaNucleo, 2> nucleos{};
        };
        std::unordered_map<const void *, EstadoAdma> s_adma; // por instancia de Spu2 (las pruebas crean varias)

        int32_t s_admaPico = 0; // diagnóstico: mayor |muestra| ADMA leída en el último segundo

        bool admaPendiente(const AdmaNucleo &a) noexcept
        {
            return a.posicion < 256u || !a.cola.empty();
        }

        // Siguiente muestra estéreo de la entrada ADMA; false si no hay datos (el SPU2 mezcla silencio).
        bool admaTomarMuestra(AdmaNucleo &a, int32_t &izquierda, int32_t &derecha) noexcept
        {
            if (a.posicion >= 256u)
            {
                while (!a.cola.empty() && (a.cola.front().restantes == 0u || a.cola.front().origen == nullptr))
                    a.cola.pop_front();
                if (a.cola.empty())
                    return false;
                AdmaSegmento &segmento = a.cola.front();
                {
                    // GOW-Port: GOW_FMV_DIAG=1: hora del primer bloque ADMA tras una pausa y cada 200 bloques.
                    static const bool diagAv = [] { const char *v = std::getenv("GOW_FMV_DIAG"); return v && v[0] == '1'; }();
                    static uint64_t bloques = 0;
                    static auto ultimo = std::chrono::steady_clock::time_point{};
                    const auto ahora = std::chrono::steady_clock::now();
                    if (diagAv && (ahora - ultimo > std::chrono::milliseconds(500) || ++bloques % 200u == 0u))
                        std::fprintf(stderr, "[fmv-av] bloque ADMA %llu t_ms=%lld%s\n", static_cast<unsigned long long>(bloques),
                                     static_cast<long long>(std::chrono::duration_cast<std::chrono::milliseconds>(
                                                                ahora.time_since_epoch()).count()),
                                     ahora - ultimo > std::chrono::milliseconds(500) ? " (empieza)" : "");
                    ultimo = ahora;
                }
                std::array<uint8_t, 1024> bloque{};
                const size_t n = std::min<size_t>(segmento.restantes, bloque.size());
                std::memcpy(bloque.data(), segmento.origen, n);
                for (uint32_t i = 0; i < 256u; ++i)
                {
                    a.izquierda[i] = static_cast<int16_t>(bloque[i * 2u] | (bloque[i * 2u + 1u] << 8u));
                    a.derecha[i] = static_cast<int16_t>(bloque[512u + i * 2u] | (bloque[512u + i * 2u + 1u] << 8u));
                }
                segmento.origen += n;
                segmento.restantes -= n;
                if (segmento.restantes == 0u)
                    a.cola.pop_front();
                a.posicion = 0;
            }
            izquierda = a.izquierda[a.posicion];
            derecha = a.derecha[a.posicion];
            s_admaPico = std::max({s_admaPico, std::abs(izquierda), std::abs(derecha)});
            ++a.posicion;
            return true;
        }

        // Volumen de voz o de nucleo. Modo fijo (bit 15 = 0): 15 bits con signo. El barrido (bit 15 = 1) aun no se
        // emula: se aplica de inmediato su destino (maximo si sube, 0 si baja).
        int32_t volumeFromRegister(uint16_t value) noexcept
        {
            if ((value & 0x8000u) == 0u)
                return static_cast<int16_t>(value << 1u) >> 1; // -0x4000..0x3FFF
            return (value & 0x2000u) != 0u ? 0 : 0x3FFF;
        }
        static size_t s_outputRead = 0;

        // GOW-Port: suma la entrada ADMA de cada núcleo a su mezcla seca (BVOL; MMIX bit 7 izquierda, bit 6 derecha).
        // leerReg(offset) lee un registro del SPU2 (desplazamiento como en Spu2::reg).
        template <typename LeerReg>
        void mezclarAdma(EstadoAdma *adma, LeerReg &&leerReg, int32_t (&coreOut)[2][2]) noexcept
        {
            if (adma == nullptr)
                return;
            for (uint32_t core = 0; core < 2u; ++core)
            {
                const uint32_t base = core * 0x400u;
                int32_t izquierda = 0, derecha = 0;
                if ((leerReg(base + Spu2::RegAdmas) & (core + 1u)) == 0u ||
                    !admaTomarMuestra(adma->nucleos[core], izquierda, derecha))
                    continue;
                // BVOL no tiene barrido: es un s16 directo (0x7FFF = 1,0), no el formato de 15 bits de las voces.
                const uint16_t mmix = leerReg(base + Spu2::RegMmix);
                const uint32_t bvol = Spu2::RegMvolBase + core * Spu2::RegMvolStride + 0xCu;
                if ((mmix & 0x80u) != 0u)
                    coreOut[core][0] += (izquierda * static_cast<int16_t>(leerReg(bvol))) >> 15;
                if ((mmix & 0x40u) != 0u)
                    coreOut[core][1] += (derecha * static_cast<int16_t>(leerReg(bvol + 2u))) >> 15;
            }
        }

        bool admaActivo(const EstadoAdma *adma) noexcept
        {
            return adma != nullptr && (admaPendiente(adma->nucleos[0]) || admaPendiente(adma->nucleos[1]));
        }

        // GOW-Port: diagnostico opcional. GOW_SPU2_DIAG=1: contadores por segundo de audio emulado (voces activas,
        // ADMA, barridos, NON/PMON, IRQ, KON, fin de bloque); GOW_SPU2_PCM=<archivo>: la mezcla en s16le estereo.
        struct Diag
        {
            bool on = false;
            FILE *pcm = nullptr;
            uint64_t samples = 0;
            unsigned admaDmas[2]{}, admasWrites = 0, sweepVoice = 0, sweepMaster = 0, nonWrites = 0, pmonWrites = 0;
            unsigned irqFired = 0, irqaWrites = 0, keyOn = 0, keyOnActive = 0, lsaLostOnKon = 0, endStop = 0, endLoop = 0;
            unsigned attrWrites = 0, mmixWrites = 0, dmaWords = 0;
            uint16_t lastAttr[2]{}, lastMmix[2]{}, lastAdmas[2]{};
            // Bloques de 8 medias palabras: cuántas veces los ha escrito un DMA y qué escritura se tocó la última vez.
            // Un bloque reescrito varias veces es de streaming; tocarlo otra vez sin reescribirlo = datos viejos.
            std::vector<uint16_t> writeGen, playedGen;
            unsigned staleBlocks = 0, freshBlocks = 0;
            unsigned staleByVoice[2][24]{}, freshByVoice[2][24]{}, onceByVoice[2][24]{}, totalByVoice[2][24]{};
            uint32_t lastBlock[2][24]{};
            uint64_t pitchSum[2][24]{}, pitchSteps[2][24]{};
            unsigned jumpSame[2][24]{}, jumpOther[2][24]{}; // salto de fin de bucle a su propio trozo / a otro
            std::string jumps; // últimos saltos de c1v0 (direcciones), para ver la secuencia
        };
        // GOW-Port: traza de eventos de una voz (GOW_SPU2_TRAZA=<nucleo><voz>, p. ej. 10) para ver el protocolo del driver.
        uint64_t g_sampleClock = 0;
        int g_traceVoice = []
        {
            const char *v = std::getenv("GOW_SPU2_TRAZA");
            return v ? std::atoi(v) : -1;
        }();
        unsigned g_traceLines = 0;
        void trace(uint32_t core, uint32_t voice, const char *fmt, uint32_t a = 0, uint32_t b = 0, uint32_t c = 0)
        {
            if (g_traceVoice != static_cast<int>(core * 10u + voice) || g_traceLines >= 700u)
                return;
            ++g_traceLines;
            std::fprintf(stderr, "[spu2-ev] t=%llu ", static_cast<unsigned long long>(g_sampleClock));
            std::fprintf(stderr, fmt, a, b, c);
            std::fputc('\n', stderr);
        }
        Diag &diag()
        {
            static Diag d = []
            {
                Diag out;
                const char *v = std::getenv("GOW_SPU2_DIAG");
                out.on = v && v[0] == '1';
                if (const char *f = std::getenv("GOW_SPU2_PCM"))
                    out.pcm = std::fopen(f, "wb");
                return out;
            }();
            return d;
        }
    }

    Spu2::Spu2() : m_ram(RamHalfwords)
    {
        reset();
    }

    void Spu2::reset()
    {
        std::fill(m_ram.begin(), m_ram.end(), uint16_t{0});
        m_regs.fill(0);
        for (auto &core : m_voices)
            for (auto &voice : core)
                voice = VoiceState{};
        m_endx.fill(0);
        m_activeVoiceCount = 0;
        {
            std::lock_guard<std::mutex> lock(m_outputMutex);
            m_output.clear();
            s_outputRead = 0;
        }
        m_lastCycle = 0;
        m_interrupt = false;
        s_adma.erase(this); // GOW-Port
        reg(RegStatx) = StatxDmaReady;
        reg(0x400u + RegStatx) = StatxDmaReady;
    }

    uint32_t Spu2::reg32(uint32_t offset) const noexcept
    {
        return ((static_cast<uint32_t>(reg(offset)) & 0xFu) << 16u) | reg(offset + 2u);
    }

    void Spu2::setReg32(uint32_t offset, uint32_t value) noexcept
    {
        value &= RamHalfwords - 1u;
        reg(offset) = static_cast<uint16_t>(value >> 16u);
        reg(offset + 2u) = static_cast<uint16_t>(value);
    }

    void Spu2::writeRam(uint32_t halfwordAddress, uint16_t value) noexcept
    {
        halfwordAddress &= RamHalfwords - 1u;
        m_ram[halfwordAddress] = value;
        checkIrqAddress(halfwordAddress);
    }

    void Spu2::checkIrqAddress(uint32_t halfwordAddress) noexcept
    {
        for (uint32_t core = 0; core < 2u; ++core)
        {
            const uint32_t base = core * 0x400u;
            if ((reg(base + RegAttr) & 0x40u) != 0u && reg32(base + RegIrqa) == halfwordAddress)
            {
                ++diag().irqFired;
                m_interrupt = true;
                reg(0x7C2u) |= static_cast<uint16_t>(4u << core); // SPDIF_IRQINFO
            }
        }
    }

    bool Spu2::takeInterrupt() noexcept
    {
        const bool pending = m_interrupt;
        m_interrupt = false;
        return pending;
    }

    uint16_t Spu2::read16(uint32_t physical) const
    {
        const uint32_t offset = (physical - RegBase) & 0x7FEu;
        if (offset < 0x760u)
        {
            const uint32_t core = offset >= 0x400u ? 1u : 0u;
            const uint32_t local = offset & 0x3FFu;
            if (local < 0x180u)
            {
                const uint32_t index = local >> 4u;
                const uint32_t field = local & 0xFu;
                if (index < VoicesPerCore)
                {
                    const VoiceState &v = m_voices[core][index];
                    if (field == 0xAu)
                        return static_cast<uint16_t>(v.envelope);
                    if (field == 0xCu || field == 0xEu)
                        return static_cast<uint16_t>(volumeFromRegister(reg(voiceReg(core, index, field - 0xCu))) << 1u);
                }
            }
            else if (local >= RegVoiceAddr && local < RegVoiceAddr + VoicesPerCore * 0xCu)
            {
                const uint32_t index = (local - RegVoiceAddr) / 0xCu;
                const uint32_t field = (local - RegVoiceAddr) % 0xCu;
                // GOW-Port: NAX como el hardware: la media palabra que se está leyendo dentro del bloque que suena
                // (nax ya apunta al bloque siguiente mientras quedan muestras del actual); con el bloque terminado, el
                // siguiente (LSA si había marca de fin), pasada la cabecera.
                const VoiceState &voice = m_voices[core][index];
                const uint32_t current = voice.active && voice.decodedIndex < 28u
                                             ? ((voice.nax - 8u + 1u + voice.decodedIndex / 4u) & (RamHalfwords - 1u))
                                             : ((voice.nax + (voice.active ? 1u : 0u)) & (RamHalfwords - 1u));
                if (field == 8u)
                    return static_cast<uint16_t>(current >> 16u);
                if (field == 10u)
                {
                    static unsigned lecturas = 0;
                    if ((++lecturas % 64u) == 0u)
                    {
                        // GOW-Port: GOW_SPU2_TRAZA_SIN_NAX=1 deja en la traza solo KON/KOFF/fin/direcciones.
                        static const bool sinNax = std::getenv("GOW_SPU2_TRAZA_SIN_NAX") != nullptr;
                        if (!sinNax)
                            trace(core, index, "lee NAX=%05x (1 de 64)", current);
                    }
                    return static_cast<uint16_t>(current);
                }
            }
            else if (local == RegEndx)
            {
                if (g_traceVoice >= 0 && static_cast<uint32_t>(g_traceVoice) / 10u == core && (m_endx[core] >> (g_traceVoice % 10)) & 1u)
                    trace(core, static_cast<uint32_t>(g_traceVoice % 10), "lee ENDX (bit puesto)");
                return static_cast<uint16_t>(m_endx[core]);
            }
            else if (local == RegEndx + 2u)
                return static_cast<uint16_t>(m_endx[core] >> 16u);
        }
        return reg(offset);
    }

    void Spu2::write16(uint32_t physical, uint16_t value)
    {
        const uint32_t offset = (physical - RegBase) & 0x7FEu;
        reg(offset) = value;
        if (offset >= 0x760u)
        {
            if (diag().on && offset < 0x760u + 2u * RegMvolStride && (value & 0x8000u) != 0u)
                ++diag().sweepMaster;
            return;
        }

        const uint32_t core = offset >= 0x400u ? 1u : 0u;
        const uint32_t base = core * 0x400u;
        const uint32_t local = offset & 0x3FFu;
        if (diag().on)
        {
            Diag &d = diag();
            if (local < 0x180u && (local & 0xFu) < 4u && (value & 0x8000u) != 0u)
                ++d.sweepVoice;
            if ((local == RegNon || local == RegNon + 2u) && value != 0u)
                ++d.nonWrites;
            if ((local == RegPmon || local == RegPmon + 2u) && value != 0u)
                ++d.pmonWrites;
            if (local == RegIrqa || local == RegIrqa + 2u)
                ++d.irqaWrites;
            if (local == RegAttr) { ++d.attrWrites; d.lastAttr[core] = value; }
            if (local == RegMmix) { ++d.mmixWrites; d.lastMmix[core] = value; }
            if (local == RegAdmas) { if (value != 0u) ++d.admasWrites; d.lastAdmas[core] = value; }
        }
        if (local == RegAdmas && (value & (core + 1u)) == 0u)
            s_adma[this].nucleos[core] = AdmaNucleo{}; // GOW-Port: ADMA detenido, se descarta lo pendiente
        switch (local)
        {
        case RegKon:
            keyOn(core, value, 0u);
            return;
        case RegKon + 2u:
            keyOn(core, value & 0xFFu, 16u);
            return;
        case RegKoff:
            keyOff(core, value, 0u);
            return;
        case RegKoff + 2u:
            keyOff(core, value & 0xFFu, 16u);
            return;
        case RegData:
        {
            uint32_t tsa = reg32(base + RegTsa);
            writeRam(tsa, value);
            setReg32(base + RegTsa, tsa + 1u);
            return;
        }
        case RegEndx:
            m_endx[core] &= 0xFF0000u;
            return;
        case RegEndx + 2u:
            m_endx[core] &= 0x00FFFFu;
            return;
        default:
            break;
        }

        if (local >= RegVoiceAddr && local < RegVoiceAddr + VoicesPerCore * 0xCu)
        {
            const uint32_t index = (local - RegVoiceAddr) / 0xCu;
            const uint32_t field = (local - RegVoiceAddr) % 0xCu;
            VoiceState &v = m_voices[core][index];
            if (field == 4u || field == 6u) // LSAX escrito por el driver: manda sobre la marca del bloque
            {
                v.lsa = reg32(voiceAddrReg(core, index, 4u));
                v.lsaFromRegister = true;
                if (field == 6u)
                    trace(core, index, "LSA=%05x (nax=%05x)", v.lsa, v.nax);
            }
            else if (field == 0u || field == 2u)
            {
                if (field == 2u)
                    trace(core, index, "SSA=%05x (nax=%05x)", reg32(voiceAddrReg(core, index, 0u)), v.nax);
            }
            else if (field == 8u || field == 10u)
            {
                v.nax = reg32(voiceAddrReg(core, index, 8u)) & ~7u;
            }
        }
    }

    bool Spu2::dmaWrite(uint32_t core, const uint8_t *source, size_t bytes)
    {
        const uint32_t base = core * 0x400u;
        diag().dmaWords += static_cast<unsigned>(bytes / 2u);
        if ((reg(base + RegAdmas) & (core + 1u)) != 0u)
        {
            // GOW-Port: ADMA. El SPU2 lee los bloques a su ritmo (admaTomarMuestra). El último bloque del DMA se lee
            // cuando acaba el que suena ahora y los anteriores de este DMA: ahí termina la transferencia.
            ++diag().admaDmas[core];
            AdmaNucleo &a = s_adma[this].nucleos[core];
            const uint64_t quedanEnBloque = a.posicion < 256u ? 256u - a.posicion : 0u;
            uint64_t bloquesAntes = 0u;
            for (const AdmaSegmento &segmento : a.cola)
                bloquesAntes += (segmento.restantes + 1023u) / 1024u;
            const uint64_t bloques = std::max<uint64_t>((bytes + 1023u) / 1024u, 1u);
            if (a.cola.size() >= 4u) // nadie consume (no debería pasar): no acumular sin límite
                a.cola.pop_front();
            a.cola.push_back(AdmaSegmento{source, bytes});
            a.retardo = std::max<uint64_t>((quedanEnBloque + (bloquesAntes + bloques - 1u) * 256u) * CyclesPerSample, 64u);
            return true;
        }
        uint32_t tsa = reg32(base + RegTsa);
        if (diag().on && bytes >= 2u)
        {
            Diag &d = diag();
            if (d.writeGen.empty())
            {
                d.writeGen.assign(RamHalfwords / 8u, 0u);
                d.playedGen.assign(RamHalfwords / 8u, 0u);
            }
            const uint32_t first = tsa / 8u, last = (tsa + static_cast<uint32_t>(bytes / 2u) - 1u) / 8u;
            for (uint32_t b = first; b <= last; ++b)
            {
                uint16_t &g = d.writeGen[b & (RamHalfwords / 8u - 1u)];
                g = static_cast<uint16_t>(g == 0xFFFFu ? 2u : g + 1u);
            }
        }
        for (size_t i = 0; i + 1u < bytes; i += 2u)
            writeRam(tsa++, static_cast<uint16_t>(source[i] | (source[i + 1u] << 8u)));
        setReg32(base + RegTsa, tsa);
        return true;
    }

    bool Spu2::dmaRead(uint32_t core, uint8_t *destination, size_t bytes)
    {
        const uint32_t base = core * 0x400u;
        if ((reg(base + RegAdmas) & (core + 1u)) != 0u)
            return false;
        uint32_t tsa = reg32(base + RegTsa);
        for (size_t i = 0; i + 1u < bytes; i += 2u)
        {
            const uint16_t value = ram(tsa++);
            destination[i] = static_cast<uint8_t>(value);
            destination[i + 1u] = static_cast<uint8_t>(value >> 8u);
        }
        setReg32(base + RegTsa, tsa);
        return true;
    }

    void Spu2::markDmaReady(uint32_t core) noexcept
    {
        reg(core * 0x400u + RegStatx) |= StatxDmaReady;
    }

    void Spu2::keyOn(uint32_t core, uint32_t mask, uint32_t firstVoice)
    {
        for (uint32_t bit = 0; bit < 16u; ++bit)
        {
            if ((mask & (1u << bit)) == 0u || firstVoice + bit >= VoicesPerCore)
                continue;
            const uint32_t index = firstVoice + bit;
            VoiceState &v = m_voices[core][index];
            const uint32_t ssa = reg32(voiceAddrReg(core, index, 0u)) & ~7u;
            if (diag().on)
            {
                ++diag().keyOn;
                if (v.active)
                    ++diag().keyOnActive;
                if (v.lsaFromRegister && v.lsa != ssa)
                    ++diag().lsaLostOnKon;
            }
            // GOW-Port: KON no toca la direccion de bucle (como el hardware y PCSX2, V_Voice::Start): el driver la
            // escribe antes de KON y la marca de inicio de bucle de los datos solo manda mientras no se reescriba.
            // Antes se ponia LSA = SSA y los sonidos con bucle volvian al principio en lugar de a su bucle.
            const uint32_t lsa = v.lsa;
            trace(core, index, "KON ssa=%05x lsa=%05x activa=%u", ssa, lsa, v.active ? 1u : 0u);
            v = VoiceState{};
            v.active = true;
            v.nax = ssa;
            v.lsa = lsa;
            v.phase = VoiceState::Phase::Attack;
            m_endx[core] &= ~(1u << index);
            ++m_activeVoiceCount;
        }
    }

    void Spu2::keyOff(uint32_t core, uint32_t mask, uint32_t firstVoice)
    {
        for (uint32_t bit = 0; bit < 16u; ++bit)
        {
            if ((mask & (1u << bit)) == 0u || firstVoice + bit >= VoicesPerCore)
                continue;
            VoiceState &v = m_voices[core][firstVoice + bit];
            trace(core, firstVoice + bit, "KOFF nax=%05x", v.nax);
            if (v.active)
            {
                v.phase = VoiceState::Phase::Release;
                v.envelopeCounter = 0;
            }
        }
    }

    void Spu2::decodeBlock(uint32_t core, uint32_t index)
    {
        VoiceState &v = m_voices[core][index];

        if (!v.active)
            return;

        const uint32_t block = v.nax & (RamHalfwords - 1u);
        if (diag().on && !diag().writeGen.empty())
        {
            Diag &d = diag();
            const uint32_t b = block / 8u;
            ++d.totalByVoice[core][index];
            d.lastBlock[core][index] = block;
            // playedGen = writeGen + 1 la última vez que se tocó (0 = nunca).
            const bool repeated = d.playedGen[b] == static_cast<uint16_t>(d.writeGen[b] + 1u);
            if (d.writeGen[b] >= 2u)
            {
                if (repeated)
                {
                    ++d.staleBlocks;
                    ++d.staleByVoice[core][index];
                }
                else
                {
                    ++d.freshBlocks;
                    ++d.freshByVoice[core][index];
                }
            }
            else if (repeated)
                ++d.onceByVoice[core][index]; // escrito una vez (o nunca por DMA) y tocado otra vez
            d.playedGen[b] = static_cast<uint16_t>(d.writeGen[b] + 1u);
        }
        const uint16_t header = ram(block);
        uint32_t shift = header & 0xFu;
        if (shift > 12u)
            shift = 9u;
        const uint32_t filter = std::min<uint32_t>((header >> 4u) & 7u, 4u);
        v.blockFlags = static_cast<uint8_t>(header >> 8u);
        if ((v.blockFlags & 4u) != 0u && !v.lsaFromRegister)
            v.lsa = block;

        for (uint32_t word = 1; word < 8u; ++word)
        {
            const uint16_t packed = ram(block + word);
            checkIrqAddress((block + word) & (RamHalfwords - 1u));
            for (uint32_t nibble = 0; nibble < 4u; ++nibble)
            {
                const int32_t raw = static_cast<int16_t>(((packed >> (nibble * 4u)) & 0xFu) << 12u) >> shift;
                const int32_t predicted = (v.hist1 * kAdpcmFilters[filter][0] + v.hist2 * kAdpcmFilters[filter][1] + 32) >> 6;
                const int16_t sample = clamp16(raw + predicted);
                v.hist2 = v.hist1;
                v.hist1 = sample;
                v.decoded[(word - 1u) * 4u + nibble] = sample;
            }
        }
        checkIrqAddress(block);
        v.decodedIndex = 0;
        v.nax = (block + 8u) & (RamHalfwords - 1u);
    }

    void Spu2::stepEnvelope(uint32_t core, uint32_t index)
    {
        VoiceState &v = m_voices[core][index];
        const uint16_t adsr1 = reg(voiceReg(core, index, 6u));
        const uint16_t adsr2 = reg(voiceReg(core, index, 8u));

        uint32_t rate = 0;
        bool exponential = false;
        bool increase = false;
        switch (v.phase)
        {
        case VoiceState::Phase::Attack:
            rate = (adsr1 >> 8u) & 0x7Fu;
            exponential = (adsr1 & 0x8000u) != 0u;
            increase = true;
            break;
        case VoiceState::Phase::Decay:
            rate = ((adsr1 >> 4u) & 0xFu) * 4u;
            exponential = true;
            break;
        case VoiceState::Phase::Sustain:
            rate = (adsr2 >> 6u) & 0x7Fu;
            exponential = (adsr2 & 0x8000u) != 0u;
            increase = (adsr2 & 0x4000u) == 0u;
            break;
        case VoiceState::Phase::Release:
            rate = (adsr2 & 0x1Fu) * 4u;
            exponential = (adsr2 & 0x20u) != 0u;
            break;
        case VoiceState::Phase::Off:
            return;
        }

        // psx-spx "SPU ADSR": ciclos = 1 << max(0, shift - 11); paso = valor << max(0, 11 - shift).
        const int32_t shiftValue = static_cast<int32_t>(rate >> 2u);
        const int32_t stepValue = static_cast<int32_t>(rate & 3u);
        int32_t step = increase ? 7 - stepValue : -8 + stepValue;
        uint32_t cycles = 1u << static_cast<uint32_t>(std::max(0, shiftValue - 11));
        step <<= std::max(0, 11 - shiftValue);
        if (exponential && increase && v.envelope > 0x6000)
            cycles *= 4u;
        // GOW-Port: desplazamiento aritmetico (hacia -infinito) como el hardware y PCSX2 (V_ADSR::Calculate); la
        // division redondeaba hacia cero, el paso se quedaba en 0 por debajo de ~0x1000 en las tasas lentas y la voz
        // seguia sonando (y repitiendo su bucle) al ~12 % para siempre en vez de apagarse.
        if (exponential && !increase)
            step = static_cast<int16_t>((step * v.envelope) >> 15);

        if (++v.envelopeCounter >= cycles)
        {
            v.envelopeCounter = 0;
            v.envelope = std::clamp(v.envelope + step, 0, 0x7FFF);
        }

        switch (v.phase)
        {
        case VoiceState::Phase::Sustain:
            // GOW-Port: el sustain que baja hasta 0 apaga la voz (PCSX2: "stay in sustain until key off or silence").
            if (v.envelope <= 0 && !increase)
            {
                v.phase = VoiceState::Phase::Off;
                v.active = false;
                if (m_activeVoiceCount > 0)
                    --m_activeVoiceCount;
            }
            break;
        case VoiceState::Phase::Attack:
            if (v.envelope >= 0x7FFF)
            {
                v.phase = VoiceState::Phase::Decay;
                v.envelopeCounter = 0;
            }
            break;
        case VoiceState::Phase::Decay:
            if (v.envelope <= static_cast<int32_t>(((adsr1 & 0xFu) + 1u) * 0x800u))
            {
                v.phase = VoiceState::Phase::Sustain;
                v.envelopeCounter = 0;
            }
            break;
        case VoiceState::Phase::Release:
            if (v.envelope <= 0)
            {
                v.envelope = 0;
                v.phase = VoiceState::Phase::Off;
                v.active = false;
                if (m_activeVoiceCount > 0)
                    --m_activeVoiceCount;
            }
            break;
        default:
            break;
        }
    }

    int32_t Spu2::stepVoice(uint32_t core, uint32_t index)
    {
        VoiceState &v = m_voices[core][index];
        if (!v.active)
            return 0;

        // GOW-Port: fin de bloque en cuanto se toca su última muestra (no al pedir el siguiente). Con la marca de fin se
        // salta a LSA; sin "repetir", la voz se apaga. Así NAX nunca apunta al bloque de después de uno con marca de fin
        // (antes valía "bloque + 8" desde que se decodificaba el último bloque): el driver de streaming de God of War
        // lee NAX, veía que la voz había salido de su trozo del búfer doble (0x8020) y paraba y relanzaba la música
        // desde el principio cada ~0,35 s.
        const auto endBlock = [this, &v](uint32_t core, uint32_t index)
        {
            if ((v.blockFlags & 1u) != 0u)
            {
                m_endx[core] |= 1u << index;
                trace(core, index, "FIN bloque=%05x flags=%x -> lsa=%05x", (v.nax - 8u) & (RamHalfwords - 1u), v.blockFlags, v.lsa);
                if (diag().on)
                {
                    Diag &d = diag();
                    ++((v.blockFlags & 2u) == 0u ? d.endStop : d.endLoop);
                    // nax apunta al bloque siguiente al del fin; el trozo actual empieza antes. Si LSA cae a menos de
                    // 0x1000 medias palabras hacia atrás, vuelve a su propio trozo.
                    const uint32_t from = (v.nax - 8u) & (RamHalfwords - 1u);
                    if ((v.blockFlags & 2u) != 0u)
                    {
                        if (v.lsa <= from && from - v.lsa < 0x1000u)
                            ++d.jumpSame[core][index];
                        else
                            ++d.jumpOther[core][index];
                        if (core == 1u && index == 0u && d.jumps.size() < 120u)
                        {
                            char t[24];
                            std::snprintf(t, sizeof(t), " %05x>%05x", from, v.lsa);
                            d.jumps += t;
                        }
                    }
                }
                v.nax = v.lsa;
                if ((v.blockFlags & 2u) == 0u)
                {
                    v.active = false;
                    v.phase = VoiceState::Phase::Off;
                    v.envelope = 0;
                }
            }
            v.blockFlags = 0;
        };

        // Tono 4.12 (0x1000 = 48 kHz). Interpolacion lineal entre las dos ultimas muestras (el hardware usa una
        // gaussiana de 4 puntos).
        v.pitchCounter += std::min<uint32_t>(reg(voiceReg(core, index, 4u)), 0x3FFFu);
        if (diag().on)
        {
            diag().pitchSum[core][index] += std::min<uint32_t>(reg(voiceReg(core, index, 4u)), 0x3FFFu);
            ++diag().pitchSteps[core][index];
        }
        while (v.pitchCounter >= 0x1000u && v.active)
        {
            v.pitchCounter -= 0x1000u;
            if (v.decodedIndex >= 28u)
                decodeBlock(core, index);
            if (!v.active)
                break;
            v.prev[1] = v.prev[0];
            v.prev[0] = v.decoded[v.decodedIndex++];
            if (v.decodedIndex >= 28u)
                endBlock(core, index);
        }
        if (!v.active)
            return 0;

        const int32_t fraction = static_cast<int32_t>(v.pitchCounter & 0xFFFu);
        const int32_t sample = v.prev[1] + (((v.prev[0] - v.prev[1]) * fraction) >> 12);
        stepEnvelope(core, index);
        v.lastOutput = clamp16((sample * v.envelope) >> 15);
        return v.lastOutput;
    }

    void Spu2::step()
    {
        int32_t coreOut[2][2] = {};
        if (m_activeVoiceCount > 0)
        {
            for (uint32_t core = 0; core < 2u; ++core)
            {
                const uint32_t base = core * 0x400u;
                const uint32_t mixLeft = reg(base + RegVmixL) | (static_cast<uint32_t>(reg(base + RegVmixL + 2u)) << 16u);
                const uint32_t mixRight = reg(base + RegVmixR) | (static_cast<uint32_t>(reg(base + RegVmixR + 2u)) << 16u);
                int32_t left = 0;
                int32_t right = 0;
                for (uint32_t index = 0; index < VoicesPerCore; ++index)
                {
                    if (!m_voices[core][index].active)
                        continue;
                    const int32_t sample = stepVoice(core, index);
                    if (sample == 0)
                        continue;
                    const int32_t volLeft = volumeFromRegister(reg(voiceReg(core, index, 0u)));
                    const int32_t volRight = volumeFromRegister(reg(voiceReg(core, index, 2u)));
                    if ((mixLeft & (1u << index)) != 0u)
                        left += (sample * volLeft) >> 14;
                    if ((mixRight & (1u << index)) != 0u)
                        right += (sample * volRight) >> 14;
                }
                coreOut[core][0] = left;
                coreOut[core][1] = right;
            }
        }
        if (const auto it = s_adma.find(this); it != s_adma.end()) // GOW-Port
            mezclarAdma(&it->second, [this](uint32_t offset) { return reg(offset); }, coreOut);

        const auto master = [this](uint32_t core, uint32_t side)
        {
            return volumeFromRegister(reg(RegMvolBase + core * RegMvolStride + side * 2u));
        };
        const int32_t core0L = (coreOut[0][0] * master(0u, 0u)) >> 14;
        const int32_t left = ((core0L + coreOut[1][0]) * master(1u, 0u)) >> 14;
        const int32_t core0R = (coreOut[0][1] * master(0u, 1u)) >> 14;
        const int32_t right = ((core0R + coreOut[1][1]) * master(1u, 1u)) >> 14;

        std::lock_guard<std::mutex> lock(m_outputMutex);
        m_output.push_back(clamp16(left));
        m_output.push_back(clamp16(right));
        const size_t available = m_output.size() - s_outputRead;
        if (available > kMaxBufferedFrames * 2u)
            s_outputRead += (available - kMaxBufferedFrames * 2u) & ~size_t{1};
    }

    void Spu2::advanceTo(uint64_t iopCycle)
    {
        if (iopCycle <= m_lastCycle)
            return;
        const uint64_t samples = (iopCycle - m_lastCycle) / CyclesPerSample;
        if (samples == 0)
            return;

        EstadoAdma *adma = nullptr; // GOW-Port: entrada ADMA
        if (const auto it = s_adma.find(this); it != s_adma.end())
            adma = &it->second;
        if (m_activeVoiceCount == 0 && !admaActivo(adma))
        {
            std::lock_guard<std::mutex> lock(m_outputMutex);
            const size_t needed = static_cast<size_t>(samples * 2u);
            m_output.insert(m_output.end(), needed, int16_t{0});
            const size_t available = m_output.size() - s_outputRead;
            if (available > kMaxBufferedFrames * 2u)
                s_outputRead += (available - kMaxBufferedFrames * 2u) & ~size_t{1};
        }
        else
        {
            std::vector<int16_t> batch;
            batch.reserve(static_cast<size_t>(samples * 2u));
            for (uint64_t s = 0; s < samples; ++s)
            {
                int32_t coreOut[2][2] = {};
                for (uint32_t core = 0; core < 2u; ++core)
                {
                    const uint32_t base = core * 0x400u;
                    const uint32_t mixLeft = reg(base + RegVmixL) | (static_cast<uint32_t>(reg(base + RegVmixL + 2u)) << 16u);
                    const uint32_t mixRight = reg(base + RegVmixR) | (static_cast<uint32_t>(reg(base + RegVmixR + 2u)) << 16u);
                    int32_t left = 0;
                    int32_t right = 0;
                    for (uint32_t index = 0; index < VoicesPerCore; ++index)
                    {
                        if (!m_voices[core][index].active)
                            continue;
                        const int32_t sample = stepVoice(core, index);
                        if (sample == 0)
                            continue;
                        const int32_t volLeft = volumeFromRegister(reg(voiceReg(core, index, 0u)));
                        const int32_t volRight = volumeFromRegister(reg(voiceReg(core, index, 2u)));
                        if ((mixLeft & (1u << index)) != 0u)
                            left += (sample * volLeft) >> 14;
                        if ((mixRight & (1u << index)) != 0u)
                            right += (sample * volRight) >> 14;
                    }
                    coreOut[core][0] = left;
                    coreOut[core][1] = right;
                }
                mezclarAdma(adma, [this](uint32_t offset) { return reg(offset); }, coreOut); // GOW-Port
                const auto master = [this](uint32_t core, uint32_t side)
                {
                    return volumeFromRegister(reg(RegMvolBase + core * RegMvolStride + side * 2u));
                };
                const int32_t core0L = (coreOut[0][0] * master(0u, 0u)) >> 14;
                const int32_t left = ((core0L + coreOut[1][0]) * master(1u, 0u)) >> 14;
                const int32_t core0R = (coreOut[0][1] * master(0u, 1u)) >> 14;
                const int32_t right = ((core0R + coreOut[1][1]) * master(1u, 1u)) >> 14;
                batch.push_back(clamp16(left));
                batch.push_back(clamp16(right));
            }
            std::lock_guard<std::mutex> lock(m_outputMutex);
            m_output.insert(m_output.end(), batch.begin(), batch.end());
            const size_t available = m_output.size() - s_outputRead;
            if (available > kMaxBufferedFrames * 2u)
                s_outputRead += (available - kMaxBufferedFrames * 2u) & ~size_t{1};
        }
        {
            std::lock_guard<std::mutex> lock(m_outputMutex);
            if (s_outputRead >= 8192u)
            {
                m_output.erase(m_output.begin(), m_output.begin() + static_cast<std::ptrdiff_t>(s_outputRead));
                s_outputRead = 0;
            }
        }
        m_lastCycle += samples * CyclesPerSample;
        g_sampleClock += samples;
        Diag &d = diag();
        if (d.pcm)
        {
            std::lock_guard<std::mutex> lock(m_outputMutex);
            const size_t count = static_cast<size_t>(samples * 2u);
            if (m_output.size() >= count)
                std::fwrite(m_output.data() + (m_output.size() - count), sizeof(int16_t), count, d.pcm);
        }
        if (d.on && (d.samples += samples) >= 48000u)
        {
            unsigned active = 0;
            for (const auto &c : m_voices)
                for (const auto &v : c)
                    active += v.active ? 1u : 0u;
            std::fprintf(stderr,
                         "[spu2-diag] voces=%u kon=%u kon_activa=%u lsa_perdida=%u fin_para=%u fin_bucle=%u irq=%u irqa_esc=%u "
                         "adma_dma=%u/%u admas_esc=%u barrido_voz=%u barrido_master=%u non=%u pmon=%u attr=%04x/%04x "
                         "mmix=%04x/%04x admas=%x/%x dma_hw=%u bvol=%04x/%04x,%04x/%04x avol=%04x/%04x,%04x/%04x "
                         "adma_pico=%d\n",
                         active, d.keyOn, d.keyOnActive, d.lsaLostOnKon, d.endStop, d.endLoop, d.irqFired, d.irqaWrites,
                         d.admaDmas[0], d.admaDmas[1], d.admasWrites, d.sweepVoice, d.sweepMaster, d.nonWrites,
                         d.pmonWrites, d.lastAttr[0], d.lastAttr[1], d.lastMmix[0], d.lastMmix[1], d.lastAdmas[0],
                         d.lastAdmas[1], d.dmaWords, reg(RegMvolBase + 0xCu), reg(RegMvolBase + 0xEu),
                         reg(RegMvolBase + RegMvolStride + 0xCu), reg(RegMvolBase + RegMvolStride + 0xEu),
                         reg(RegMvolBase + 0x8u), reg(RegMvolBase + 0xAu), reg(RegMvolBase + RegMvolStride + 0x8u),
                         reg(RegMvolBase + RegMvolStride + 0xAu), s_admaPico);
            s_admaPico = 0;
            // Voces de streaming: las que han tocado más de 300 bloques reescritos en este segundo (nuevos/viejos).
            std::string stale;
            for (uint32_t c = 0; c < 2u; ++c)
                for (uint32_t i = 0; i < 24u; ++i)
                    if (d.freshByVoice[c][i] + d.staleByVoice[c][i] > 300u)
                    {
                        const VoiceState &v = m_voices[c][i];
                        char extra[240];
                        std::snprintf(extra, sizeof(extra), " c%uv%u=%u/%u/%u/%u@%u(media %.0f, pasos %llu)[saltos propio=%u otro=%u]"
                                      "[vol=%04x/%04x env=%d fase=%u vmix=%u/%u]",
                                      c, i, d.totalByVoice[c][i], d.freshByVoice[c][i], d.staleByVoice[c][i], d.onceByVoice[c][i],
                                      reg(voiceReg(c, i, 4u)),
                                      d.pitchSteps[c][i] ? static_cast<double>(d.pitchSum[c][i]) / static_cast<double>(d.pitchSteps[c][i]) : 0.0,
                                      static_cast<unsigned long long>(d.pitchSteps[c][i]), d.jumpSame[c][i], d.jumpOther[c][i],
                                      reg(voiceReg(c, i, 0u)), reg(voiceReg(c, i, 2u)), v.envelope, static_cast<unsigned>(v.phase),
                                      (((reg(c * 0x400u + RegVmixL) | (static_cast<uint32_t>(reg(c * 0x400u + RegVmixL + 2u)) << 16u)) >> i) & 1u),
                                      (((reg(c * 0x400u + RegVmixR) | (static_cast<uint32_t>(reg(c * 0x400u + RegVmixR + 2u)) << 16u)) >> i) & 1u));
                        stale += extra;
                    }
            std::fprintf(stderr, "[spu2-diag] streaming: bloques_nuevos=%u bloques_viejos=%u%s mvol=%04x/%04x,%04x/%04x\n",
                         d.freshBlocks, d.staleBlocks, stale.c_str(), reg(RegMvolBase), reg(RegMvolBase + 2u),
                         reg(RegMvolBase + RegMvolStride), reg(RegMvolBase + RegMvolStride + 2u));
            if (!d.jumps.empty())
                std::fprintf(stderr, "[spu2-diag] saltos c1v0:%s\n", d.jumps.c_str());
            Diag keep = std::move(d);
            d = Diag{};
            d.on = true;
            d.pcm = keep.pcm;
            d.writeGen = std::move(keep.writeGen);
            d.playedGen = std::move(keep.playedGen);
            std::copy(std::begin(keep.lastAttr), std::end(keep.lastAttr), d.lastAttr);
            std::copy(std::begin(keep.lastMmix), std::end(keep.lastMmix), d.lastMmix);
            std::copy(std::begin(keep.lastAdmas), std::end(keep.lastAdmas), d.lastAdmas);
            std::fflush(d.pcm);
        }
    }

    size_t Spu2::pendingFrames() const
    {
        std::lock_guard<std::mutex> lock(m_outputMutex);
        return m_output.size() > s_outputRead ? (m_output.size() - s_outputRead) / 2u : 0u;
    }

    size_t Spu2::drainOutput(int16_t *stereo, size_t maxFrames, size_t maxLatencyFrames)
    {
        std::lock_guard<std::mutex> lock(m_outputMutex);
        if (s_outputRead >= m_output.size())
        {
            m_output.clear();
            s_outputRead = 0;
            return 0;
        }
        size_t available = (m_output.size() - s_outputRead) / 2u;
        if (maxLatencyFrames != SIZE_MAX && available > maxFrames + maxLatencyFrames)
        {
            const size_t drop = available - maxFrames - maxLatencyFrames;
            s_outputRead += drop * 2u;
            available -= drop;
        }
        const size_t frames = std::min(maxFrames, available);
        if (frames > 0)
        {
            std::copy_n(m_output.data() + s_outputRead, frames * 2u, stereo);
            s_outputRead += frames * 2u;
        }
        if (s_outputRead >= m_output.size())
        {
            m_output.clear();
            s_outputRead = 0;
        }
        return frames;
    }

    // GOW-Port: retardo de la interrupción de fin de DMA para un DMA ADMA recién empezado en el núcleo (ciclos del IOP
    // hasta que el SPU2 lea su último bloque). 0 si el DMA no era ADMA. Lo llama IopMemory justo después de dmaWrite.
    uint64_t spu2AdmaRetardo(const Spu2 &spu2, uint32_t core)
    {
        const auto it = s_adma.find(&spu2);
        if (it == s_adma.end() || core > 1u)
            return 0u;
        const uint64_t retardo = it->second.nucleos[core].retardo;
        it->second.nucleos[core].retardo = 0u;
        return retardo;
    }
}
