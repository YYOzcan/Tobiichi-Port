// GOW-Port: comprobar FINISH opcional y la barrera de lectura sin GPU ni datos del juego.
#include "runtime/gs/gs_frontend.h"
#include "runtime/gs/gs_threaded_backend.h"
#include "runtime/ps2_memory.h"
#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <mutex>
#include <string_view>
#include <vector>

namespace {
    using namespace std::chrono_literals;
    void option(const char *name, const char *value) {
#ifdef _WIN32
        _putenv_s(name,value);
#else
        setenv(name,value,1);
#endif
    }
    struct Recording {
        std::promise<void> entered,release;
        std::shared_future<void> gate=release.get_future().share();
        std::mutex mutex;
        std::vector<int> events;
        void event(int value) { std::lock_guard lock(mutex); events.push_back(value); }
    };
    class Target final : public GSRasterBackend {
        Recording &r;
    public:
        explicit Target(Recording &recording):r(recording) {}
        void Initialize(uint8_t *,uint32_t) override {}
        void Reset() override {}
        void Submit(const GSPrimitiveBatch &b) override { r.event(int(b.state.context.frame.fbp)); }
        void LoadClut(const GSTex0Reg &,const GSTexClutReg &) override {}
        void BeginTransfer(const GSTransferCommand &) override {}
        void UploadImage(const uint8_t *,uint32_t) override {}
        void Flush() override {}
        void TextureFlush() override {}
        void Sync(GSSyncReason reason) override {
            if(reason==GSSyncReason::Finish) {
                r.entered.set_value();
                r.gate.wait();
                r.event(3);
            }
        }
        PresentationFrame Present(const GSPresentationRequest &) override { return {}; }
        bool ClearFramebuffer(const GSContext &,uint32_t) override { return true; }
        uint32_t ConsumeLocalToHostBytes(uint8_t *,uint32_t) override { return 0; }
        uint32_t ReadVram(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t) const override {
            r.event(4); return 42;
        }
        void WriteVram(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t) override {}
        void SnapshotVram(std::vector<uint8_t> &out) const override { out.clear(); }
        GSTransferSnapshot GetTransferSnapshot() const override { return {}; }
    };
}

int main(int argc,char **argv) {
    if(argc!=2 || (std::string_view(argv[1])!="default" && std::string_view(argv[1])!="async")) return 2;
    const bool async=std::string_view(argv[1])=="async";
    // Procesos separados: el runtime lee esta opción una sola vez.
    option("GOW_GS_FINISH_ASINCRONO",async?"1":"0");
    option("PS2X_GS_GPU","0"); option("PS2X_GS_THREAD","0");
    Recording recording;
    auto entered=recording.entered.get_future();
    GSRegisters registers;
    std::vector<uint8_t> vram(PS2_GS_VRAM_SIZE);
    GS gs; gs.init(vram.data(),uint32_t(vram.size()),&registers);
    auto backend=std::make_unique<GSThreadedBackend>(std::make_unique<Target>(recording));
    auto *raw=backend.get(); gs.setRasterBackend(std::move(backend));
    registers.csr.store(0);
    GSPrimitiveBatch draw{};
    draw.vertexCount=1; draw.state.prim.type=GS_PRIM_POINT;
    draw.state.context.frame.fbp=1; raw->Submit(draw);
    draw.state.context.frame.fbp=2; raw->Submit(draw);
    auto finish=std::async(std::launch::async,[&] { gs.writeRegister(GS_REG_FINISH,0); });
    bool valid=true;
    if(async && finish.wait_for(5s)!=std::future_status::ready) {
        std::cerr<<"FINISH opcional no devuelve antes del backend\n"; valid=false;
    }
    if(!async && entered.wait_for(5s)!=std::future_status::ready) {
        std::cerr<<"FINISH default no llegó al backend\n"; valid=false;
    }
    // En modo async, la lectura publica el bloque abierto y fuerza su ejecución.
    // En modo default, FINISH ya publicó el bloque. Ambos deben esperar al gate.
    auto read=std::async(std::launch::async,[&] { return raw->ReadVram(0,0,1,0,0); });
    if(entered.wait_for(5s)!=std::future_status::ready) {
        std::cerr<<"FINISH no llegó al hilo del GS\n"; valid=false;
    }
    const bool returned=finish.wait_for(0s)==std::future_status::ready;
    const bool signaled=(registers.csr.load()&2)!=0;
    if(returned!=async || signaled!=async) {
        std::cerr<<"Retorno/bit FINISH no respetan el modo seleccionado\n"; valid=false;
    }
    if(read.wait_for(0s)==std::future_status::ready) {
        std::cerr<<"La lectura de VRAM adelantó el FINISH pendiente\n"; valid=false;
    }
    // Liberar siempre antes de recoger futures y destruir la cola, incluso si falla.
    recording.release.set_value();
    finish.get();
    if(read.get()!=42 || (registers.csr.load()&2)==0) valid=false;
    raw->Flush();
    { std::lock_guard lock(recording.mutex);
      if(recording.events!=std::vector<int>({1,2,3,4})) {
          std::cerr<<"Se alteró el orden dibujos -> FINISH -> lectura\n"; valid=false;
      }
    }
    if(valid) std::cout<<"FINISH "<<argv[1]<<": retorno, CSR, orden y lectura sincronizada: OK\n";
    return valid?0:1;
}
