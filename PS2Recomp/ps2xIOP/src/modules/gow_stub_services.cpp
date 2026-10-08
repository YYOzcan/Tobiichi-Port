// GOW-Port: servicios IOP "mudos" para modulos que God of War carga y que el runtime
// todavia no simula. Aceptan el enlace RPC y responden con un buffer en cero, para que
// el juego no se quede esperando. No reproducen sonido ni guardan nada todavia.
#include "module_factories.h"
#include "rpc_reply.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

namespace ps2x::iop::detail
{
    namespace
    {
        template <size_t NSids, size_t NAliases>
        class SilentService final : public IopService
        {
        public:
            SilentService(IopHost &host, std::string_view name, uint32_t fill,
                          std::array<uint32_t, NSids> sids,
                          std::array<std::string_view, NAliases> aliases)
                : m_host(host), m_name(name), m_fill(fill), m_sids(sids), m_aliases(aliases) {}

            std::string_view name() const override { return m_name; }
            std::span<const uint32_t> sids() const override { return m_sids; }
            std::span<const std::string_view> moduleAliases() const override { return m_aliases; }
            void reset() override { std::lock_guard<std::mutex> l(m_mutex); m_logs = 0; m_calls = 0; }

            RpcResult handleRpc(const RpcRequest &request) override
            {
                RpcResult result;
                result.handled = true;
                result.resultAddress = request.receive.address;
                if (request.receive.address != 0u && request.receive.size != 0u)
                {
                    std::vector<uint32_t> zeros(std::min<uint32_t>(request.receive.size / 4u, 1024u), 0u);
                    // 989snd: la primera y la ultima palabra son marcas de "terminado" (-1);
                    // las del medio son el resultado del comando (0 = OK / handle valido).
                    if (m_fill != 0u && !zeros.empty()) { zeros.front() = m_fill; zeros.back() = m_fill; }
                    (void)writeRpcWords(m_host, request.receive, zeros);
                }
                bool log = false;
                {
                    std::lock_guard<std::mutex> l(m_mutex);
                    ++m_calls;
                    if (m_logs < 24u) { ++m_logs; log = true; }
                }
                if (log)
                {
                    std::ostringstream m;
                    m << "[" << m_name << ":silent] sid=0x" << std::hex << request.sid
                      << " rpc=0x" << request.function << " sendSize=0x" << request.send.size
                      << " recvSize=0x" << request.receive.size;
                    m_host.log(LogLevel::Info, m.str());
                }
                return result;
            }

            void appendDebugMetrics(std::vector<DebugMetric> &metrics) const override
            {
                std::lock_guard<std::mutex> l(m_mutex);
                metrics.push_back({"calls", m_calls, false});
            }

        private:
            IopHost &m_host;
            std::string_view m_name;
            uint32_t m_fill;
            std::array<uint32_t, NSids> m_sids;
            std::array<std::string_view, NAliases> m_aliases;
            mutable std::mutex m_mutex;
            uint32_t m_logs = 0;
            uint64_t m_calls = 0;
        };
    }

    // Motor de sonido 989snd de Sony (989nomid.irx).
    std::unique_ptr<IopService> createGow989SndService(IopHost &host)
    {
        return std::make_unique<SilentService<2, 3>>(host, "989snd", 0xFFFFFFFFu, // el driver marca "comando terminado" escribiendo -1
            std::array<uint32_t, 2>{0x00123456u, 0x00123457u},
            std::array<std::string_view, 3>{"989nomid", "989snd", "989err"});
    }
}
