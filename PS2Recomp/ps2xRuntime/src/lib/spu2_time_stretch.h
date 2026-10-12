#ifndef PS2_SPU2_TIME_STRETCH_H
#define PS2_SPU2_TIME_STRETCH_H

// GOW-Port: estirado temporal (WSOLA) de la salida del SPU2 hacia el audio del host.
//
// El SPU2 produce muestras al ritmo del reloj emulado del IOP. Si el juego va más lento que el tiempo
// real, llegan menos de 48.000 tramas por segundo y la salida se quedaba sin datos: el callback rellenaba
// con silencio y el sonido salía a trozos. Este bloque mantiene un colchón (kTargetFrames) y consume la
// entrada a un ritmo ("tempo") igual a la tasa medida de llegada, corregida por el nivel del colchón.
// Con tempo < 1 alarga el sonido sin cambiar el tono: segmentos de kSequence tramas que se solapan
// kOverlap tramas, buscando en una ventana de kSeek tramas el desplazamiento que mejor continúa la
// forma de onda anterior (como SoundTouch/PCSX2). Con el juego a tiempo real el tempo queda en ~1 y el
// segmento elegido es la continuación natural.
//
// Un solo hilo (el callback de audio del host) llama a push() y pull().

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace ps2_audio
{
    class TimeStretch
    {
    public:
        static constexpr size_t kSequence = 1920;     // 40 ms a 48 kHz
        static constexpr size_t kOverlap = 384;       // 8 ms
        static constexpr size_t kSeek = 720;          // 15 ms (±7,5 ms)
        static constexpr size_t kTargetFrames = 4800; // 100 ms de colchón mínimo
        static constexpr size_t kMaxTargetFrames = 14400; // 300 ms si la entrada llega a ráfagas largas
        static constexpr size_t kMaxFrames = 48000;   // 1 s: lo que sobre se descarta
        static constexpr double kMinTempo = 0.1;
        static constexpr double kMaxTempo = 2.0;

        void reset()
        {
            m_in.clear();
            m_pos = 0.0;
            m_tail.assign(kOverlap * 2u, 0.0f);
            m_haveTail = false;
            m_natural = 0;
            m_out.clear();
            m_outRead = 0;
            m_rate = 1.0;
            m_tempo = 1.0;
            m_primed = false;
            m_pushed = 0;
            m_target = static_cast<double>(kTargetFrames);
        }

        TimeStretch() { reset(); }

        void push(const int16_t *stereo, size_t frames)
        {
            m_in.reserve(m_in.size() + frames * 2u);
            for (size_t i = 0; i < frames * 2u; ++i)
                m_in.push_back(static_cast<float>(stereo[i]));
            m_pushed += frames;
        }

        // Escribe exactamente 'frames' tramas estéreo. Devuelve cuántas proceden de datos (el resto es silencio).
        size_t pull(int16_t *stereo, size_t frames)
        {
            if (frames == 0u)
                return 0u;

            // Tasa de llegada (tramas de entrada por trama de salida), suavizada en ~20 llamadas.
            const double arrived = static_cast<double>(m_pushed) / static_cast<double>(frames);
            m_pushed = 0;
            m_rate += 0.05 * (arrived - m_rate);

            if (inputFrames() > kMaxFrames)
            {
                // Demasiado retraso (la emulación fue más rápida o el host se paró): saltar al colchón.
                m_pos = static_cast<double>(m_in.size() / 2u - target());
                m_haveTail = false;
            }

            // El colchón crece al quedarse sin datos (starve) y vuelve despacio (~40 s) al mínimo.
            m_target -= (m_target - static_cast<double>(kTargetFrames)) * 0.0005;

            if (!m_primed)
            {
                if (inputFrames() < target())
                {
                    std::fill(stereo, stereo + frames * 2u, int16_t{0});
                    return 0u;
                }
                m_primed = true;
            }

            const double fill = static_cast<double>(inputFrames() + pendingOutput());
            const double error = (fill - m_target) / m_target;
            // GOW-Port: zona muerta. Con el juego a tiempo real la entrada llega a ráfagas (cada VBlank o dos) y la
            // tasa por llamada oscila: el tempo saltaba entre ~0,82 y ~1,28 cada 20 ms y cada segmento de 40 ms
            // repetía o saltaba hasta un 25 % (el sonido "en bucle"/entrecortado). Si el colchón está en su margen y
            // la llegada ronda el tiempo real, tempo exactamente 1: el segmento siguiente empieza donde acaba la
            // cola del anterior y la búsqueda elige ese desplazamiento (salida idéntica a la entrada). Fuera del
            // margen, o con la emulación claramente lenta, el estirado de siempre.
            // Cerca del tiempo real y sin riesgo de vaciado, la corrección del colchón es suave (±5 %): la emulación
            // va ~1-2 % rápida y el colchón sube despacio; antes, al pasar el margen, el tempo saltaba a ~1,7.
            const bool realTime = std::abs(m_rate - 1.0) < 0.25;
            if (realTime && fill > 0.5 * m_target && fill < 2.5 * m_target)
                m_tempo = 1.0;
            else if (realTime && fill > 0.25 * m_target)
                m_tempo = std::clamp(1.0 + 0.05 * error, 0.95, 1.05);
            else
                m_tempo = std::clamp(m_rate * (1.0 + 0.5 * error), kMinTempo, kMaxTempo);

            size_t produced = 0;
            while (produced < frames)
            {
                if (m_outRead >= m_out.size() / 2u)
                {
                    m_out.clear();
                    m_outRead = 0;
                    produceSegment(); // sin datos deja, como mucho, la salida suave de la cola
                    if (m_out.empty())
                        break;
                }
                const size_t n = std::min(frames - produced, m_out.size() / 2u - m_outRead);
                for (size_t i = 0; i < n * 2u; ++i)
                    stereo[produced * 2u + i] = toSample(m_out[m_outRead * 2u + i]);
                m_outRead += n;
                produced += n;
            }
            std::fill(stereo + produced * 2u, stereo + frames * 2u, int16_t{0});
            compact();
            return produced;
        }

        [[nodiscard]] double tempo() const { return m_tempo; }
        [[nodiscard]] unsigned starves() const { return m_starves; } // GOW-Port: GOW_AUDIO_DIAG
        [[nodiscard]] size_t target() const { return static_cast<size_t>(m_target); }
        [[nodiscard]] size_t inputFrames() const
        {
            const size_t total = m_in.size() / 2u;
            const size_t pos = static_cast<size_t>(m_pos);
            return total > pos ? total - pos : 0u;
        }

    private:
        [[nodiscard]] size_t pendingOutput() const { return m_out.size() / 2u - m_outRead; }

        static int16_t toSample(float value)
        {
            return static_cast<int16_t>(std::clamp(std::lround(value), -32768L, 32767L));
        }

        [[nodiscard]] float mono(size_t frame) const { return m_in[frame * 2u] + m_in[frame * 2u + 1u]; }

        // Desplazamiento (respecto a 'base') cuyo comienzo mejor continúa la cola del segmento anterior.
        [[nodiscard]] long bestOffset(size_t base, long lo, long hi) const
        {
            auto score = [&](long offset) {
                const size_t start = static_cast<size_t>(static_cast<long>(base) + offset);
                double dot = 0.0, energy = 1e-9;
                for (size_t i = 0; i < kOverlap; i += 2u)
                {
                    const double x = mono(start + i);
                    dot += static_cast<double>(m_tail[i * 2u] + m_tail[i * 2u + 1u]) * x;
                    energy += x * x;
                }
                return dot / std::sqrt(energy);
            };
            long best = 0;
            double bestScore = -1e300;
            for (long offset = lo; offset < hi; offset += 4) // búsqueda gruesa
            {
                const double s = score(offset);
                if (s > bestScore) { bestScore = s; best = offset; }
            }
            const long fineLo = std::max(lo, best - 3), fineHi = std::min(hi, best + 4);
            for (long offset = fineLo; offset < fineHi; ++offset) // y fina
            {
                const double s = score(offset);
                if (s > bestScore) { bestScore = s; best = offset; }
            }
            return best;
        }

        // Añade a m_out kSequence - kOverlap tramas. Devuelve false si no hay entrada suficiente.
        bool produceSegment()
        {
            const size_t total = m_in.size() / 2u;
            const size_t base = static_cast<size_t>(m_pos);
            constexpr long half = static_cast<long>(kSeek / 2u);
            const long lo = m_haveTail ? -std::min<long>(half, static_cast<long>(base)) : 0;
            const long hi = m_haveTail ? half : 1;
            if (base + static_cast<size_t>(std::max(hi, 0L)) + kSequence > total)
            {
                starve();
                return false;
            }
            // GOW-Port: con tempo 1 la continuación natural del segmento anterior (sin búsqueda): copia exacta.
            const long natural = static_cast<long>(m_natural) - static_cast<long>(base);
            const long offset = !m_haveTail ? 0
                              : (m_tempo == 1.0 && natural >= lo && natural < hi) ? natural
                                                                                  : bestOffset(base, lo, hi);
            const size_t start = static_cast<size_t>(static_cast<long>(base) + offset);
            m_natural = start + (kSequence - kOverlap);

            m_out.resize((kSequence - kOverlap) * 2u);
            for (size_t i = 0; i < kOverlap; ++i)
            {
                const float w = (static_cast<float>(i) + 0.5f) / static_cast<float>(kOverlap);
                for (size_t c = 0; c < 2u; ++c)
                {
                    const float x = m_in[(start + i) * 2u + c];
                    m_out[i * 2u + c] = m_haveTail ? m_tail[i * 2u + c] * (1.0f - w) + x * w : x * w; // sin cola: entrada suave
                }
            }
            std::copy(m_in.begin() + static_cast<std::ptrdiff_t>((start + kOverlap) * 2u),
                      m_in.begin() + static_cast<std::ptrdiff_t>((start + kSequence - kOverlap) * 2u),
                      m_out.begin() + static_cast<std::ptrdiff_t>(kOverlap * 2u));
            std::copy(m_in.begin() + static_cast<std::ptrdiff_t>((start + kSequence - kOverlap) * 2u),
                      m_in.begin() + static_cast<std::ptrdiff_t>((start + kSequence) * 2u), m_tail.begin());
            m_haveTail = true;
            m_pos += static_cast<double>(kSequence - kOverlap) * m_tempo;
            return true;
        }

        // Sin datos ni estirando: salida suave de la cola y nuevo colchón antes de volver a sonar.
        void starve()
        {
            if (m_haveTail)
            {
                m_out.resize(kOverlap * 2u);
                for (size_t i = 0; i < kOverlap; ++i)
                {
                    const float w = 1.0f - (static_cast<float>(i) + 0.5f) / static_cast<float>(kOverlap);
                    m_out[i * 2u] = m_tail[i * 2u] * w;
                    m_out[i * 2u + 1u] = m_tail[i * 2u + 1u] * w;
                }
                m_outRead = 0;
            }
            m_haveTail = false;
            if (m_primed)
            {
                ++m_starves;
                m_target = std::min(m_target * 1.5, static_cast<double>(kMaxTargetFrames));
            }
            m_primed = false;
        }

        void compact()
        {
            const size_t keep = kSeek; // historia para la búsqueda hacia atrás
            const size_t pos = static_cast<size_t>(m_pos);
            if (pos < 48000u + keep)
                return;
            const size_t drop = pos - keep;
            m_in.erase(m_in.begin(), m_in.begin() + static_cast<std::ptrdiff_t>(drop * 2u));
            m_pos -= static_cast<double>(drop);
            m_natural = m_natural > drop ? m_natural - drop : 0u;
        }

        std::vector<float> m_in;  // entrada estéreo intercalada
        double m_pos = 0.0;       // trama de lectura en m_in (fraccionaria)
        std::vector<float> m_tail; // últimas kOverlap tramas del segmento anterior
        bool m_haveTail = false;
        size_t m_natural = 0; // GOW-Port: trama de entrada que continúa el último segmento
        std::vector<float> m_out; // salida lista, estéreo intercalada
        size_t m_outRead = 0;
        double m_rate = 1.0;
        double m_tempo = 1.0;
        bool m_primed = false;
        size_t m_pushed = 0;
        double m_target = static_cast<double>(kTargetFrames);
        unsigned m_starves = 0;
    };
}

#endif
