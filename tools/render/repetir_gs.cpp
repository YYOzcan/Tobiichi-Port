// GOW-Port: repetir una captura local del mismo ABI sin archivos del juego.
#include "gow_gs_replay.h"
#include "gs_frame_pixels.h"
#include "runtime/gs/gs_cpu_backend.h"
#include "runtime/gs/gs_gpu_backend.h"
#include <algorithm>
#include <charconv>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <thread>

namespace replay=gow_gs_replay;
namespace {
    bool apply(GSRasterBackend &b,const replay::Record &r,PresentationFrame &frame) {
        using replay::Op;
        GSPrimitiveBatch batch{}; replay::Clut clut{}; GSTransferCommand transfer{};
        replay::Clear clear{}; replay::Pixel pixel{}; GSPresentationRequest present{};
        GSSyncReason sync{}; uint32_t csr=0;
        switch(r.op) {
        case Op::Submit: if(!replay::pod(r,batch) || batch.vertexCount>3) return false; b.Submit(batch); break;
        case Op::Clut: if(!replay::pod(r,clut)) return false; b.LoadClut(clut.tex0,clut.texclut); break;
        case Op::Transfer: if(!replay::pod(r,transfer)) return false; b.BeginTransfer(transfer); break;
        case Op::Upload: b.UploadImage(r.data.data(),uint32_t(r.data.size())); break;
        case Op::TextureFlush: if(!r.data.empty()) return false; b.TextureFlush(); break;
        case Op::Flush: if(!r.data.empty()) return false; b.Flush(); break;
        case Op::Reset: if(!r.data.empty()) return false; b.Reset(); break;
        case Op::Sync: if(!replay::pod(r,sync) || sync>GSSyncReason::Reset) return false; b.Sync(sync); break;
        case Op::Present: if(!replay::pod(r,present)) return false; frame=b.Present(present); break;
        case Op::Clear: if(!replay::pod(r,clear)) return false; if(uint32_t(b.ClearFramebuffer(clear.context,clear.rgba))!=clear.result) return false; break;
        case Op::Write: if(!replay::pod(r,pixel)) return false; b.WriteVram(pixel.psm,pixel.base,pixel.bw,pixel.x,pixel.y,pixel.value); break;
        case Op::Read: if(!replay::pod(r,pixel)) return false; if(b.ReadVram(pixel.psm,pixel.base,pixel.bw,pixel.x,pixel.y)!=pixel.value) return false; break;
        case Op::Mxcsr: if(!replay::pod(r,csr) || (csr&0xffff0000u)) return false; _mm_setcsr(csr); break;
        case Op::Consume: {
            if(r.data.size()<4) return false;
            uint32_t n=0; std::memcpy(&n,r.data.data(),4); if(n>replay::kRecordLimit) return false;
            std::vector<uint8_t> data(n); const auto count=b.ConsumeLocalToHostBytes(data.data(),n);
            if(count!=r.data.size()-4 || std::memcmp(data.data(),r.data.data()+4,count)) return false; break;
        }
        default: return false;
        }
        return true;
    }
    size_t differences(const std::vector<uint8_t> &a,const std::vector<uint8_t> &b,size_t &first) {
        first=SIZE_MAX; if(a.size()!=b.size()) return SIZE_MAX;
        if(a==b) return 0; // La biblioteca compara bloques; evita recorrer cada byte idéntico.
        size_t n=0; for(size_t i=0;i<a.size();++i) if(a[i]!=b[i]) { if(first==SIZE_MAX) first=i; ++n; } return n;
    }
    bool ppm(const std::filesystem::path &path,const PresentationFrame &f) {
        if(!f) return true;
        if(GowRenderTool::writePpm(path,f,GowRenderTool::PixelLayout::HostRows640)) return true;
        std::cerr<<"No se pudo exportar PPM visible: "<<path.string()<<'\n';
        return false;
    }
    // Comparar campos semánticos: los structs de la captura contienen padding del ABI.
    const char *stateDifference(const GSBackendState &a,const GSBackendState &b,bool gpuAbsentCache=false) {
        if(a.clut!=b.clut || a.clutCbp!=b.clutCbp) return "CLUT";
        if(gpuAbsentCache) {
            if(b.cachePageBase!=UINT32_MAX ||
               std::any_of(b.cacheBytes.begin(),b.cacheBytes.end(),[](uint8_t v){return v!=0;})) return "cache GPU";
        } else if(a.cachePageBase!=b.cachePageBase || a.cacheBytes!=b.cacheBytes) return "pagina de cache";
        const auto transfer=[](const GSTransferCommand &v) {
            return std::tie(v.bitbltbuf.sbp,v.bitbltbuf.sbw,v.bitbltbuf.spsm,v.bitbltbuf.dbp,v.bitbltbuf.dbw,v.bitbltbuf.dpsm,
                            v.trxpos.ssax,v.trxpos.ssay,v.trxpos.dsax,v.trxpos.dsay,v.trxpos.dir,v.trxreg.rrw,v.trxreg.rrh,v.direction);
        };
        const auto progress=[](const GSTransferSnapshot &v) {
            return std::tie(v.x,v.y,v.totalPixels,v.copiedPixels,v.direction,v.localToHostPendingBytes);
        };
        if(transfer(a.transfer)!=transfer(b.transfer)) return "transferencia";
        if(progress(a.transferState)!=progress(b.transferState)) return "progreso de transferencia";
        if(a.upload24.size!=b.upload24.size || a.upload24.bytes!=b.upload24.bytes) return "pixel CT24 pendiente";
        if(a.localToHost!=b.localToHost || a.localToHostReadPos!=b.localToHostReadPos) return "lectura localToHost";
        return nullptr;
    }
    struct Options {
        std::filesystem::path capture,output=".";
        std::string mode;
        bool lockstep=false,snapshotFeedback=false,syncCheckpoints=false;
        uint32_t repetitions=1,pauseMs=0,lastRecord=0;
        bool gpuMode() const { return mode!="cpu"; }
        bool multiple() const { return repetitions>1; }
        std::filesystem::path image(uint32_t pass,const std::string &name) const {
            return output/(multiple()?"replay_pasada_"+std::to_string(pass)+"_"+name+".ppm":"replay_"+name+".ppm");
        }
    };
    template<class Char> bool parse(int argc,Char **argv,Options &options) {
        if(argc<3) return false;
        options.capture=std::filesystem::path(argv[1]); options.mode=std::filesystem::path(argv[2]).string();
        if(options.mode!="cpu" && options.mode!="compute" && options.mode!="hardware") return false;
        bool directory=false,repetitions=false;
        for(int i=3;i<argc;++i) {
            const std::filesystem::path argument(argv[i]);
            if(argument==std::filesystem::path("--lockstep")) { if(options.lockstep) return false; options.lockstep=true; }
            else if(argument==std::filesystem::path("--checkpoints-sync")) {
                if(options.syncCheckpoints) return false;
                options.syncCheckpoints=true;
            }
            else if(argument==std::filesystem::path("--snapshot-feedback")) {
                if(options.snapshotFeedback) return false;
                options.snapshotFeedback=true;
            }
            else if(argument==std::filesystem::path("--pausa-ms")) {
                if(options.pauseMs || ++i==argc) return false;
                const auto encoded=std::filesystem::path(argv[i]).u8string();
                const std::string value(encoded.begin(),encoded.end());
                uint32_t count=0;const auto result=std::from_chars(value.data(),value.data()+value.size(),count);
                if(result.ec!=std::errc{} || result.ptr!=value.data()+value.size() || count==0 || count>1000) return false;
                options.pauseMs=count;
            }
            else if(argument==std::filesystem::path("--hasta-registro")) {
                if(options.lastRecord || ++i==argc) return false;
                const auto encoded=std::filesystem::path(argv[i]).u8string();
                const std::string value(encoded.begin(),encoded.end());
                uint32_t count=0; const auto result=std::from_chars(value.data(),value.data()+value.size(),count);
                if(result.ec!=std::errc{} || result.ptr!=value.data()+value.size() || count==0) return false;
                options.lastRecord=count;
            }
            else if(argument==std::filesystem::path("--repeticiones")) {
                if(repetitions || ++i==argc) return false;
                const std::filesystem::path number(argv[i]);
                const auto &native=number.native();
                if(native.empty() || std::any_of(native.begin(),native.end(),[](auto c){return c<'0' || c>'9';})) return false;
                const std::string value=number.string();
                uint32_t count=0; const auto result=std::from_chars(value.data(),value.data()+value.size(),count);
                if(result.ec!=std::errc{} || result.ptr!=value.data()+value.size() || count==0) return false;
                options.repetitions=count; repetitions=true;
            } else {
                if(argument.empty() || argument.native().front()=='-' || directory) return false;
                options.output=argument; directory=true;
            }
        }
        return (!options.snapshotFeedback || options.gpuMode()) &&
               (!(options.pauseMs || options.syncCheckpoints) || options.multiple());
    }
    bool restoreInitial(GSRasterBackend &backend,std::vector<uint8_t> &vram,
                        const replay::Snapshot &initial,bool gpuMode,GSGpuBackend *gpu=nullptr) {
        // Terminar la pasada anterior ANTES de sobrescribir el vector estable y reinicializar.
        backend.Sync(GSSyncReason::Finish);
        std::copy(initial.vram.begin(),initial.vram.end(),vram.begin());
        backend.Initialize(vram.data(),uint32_t(vram.size()));
        // Initialize puede destruir la GPU al sustituirla por CPU; comprobar Inner primero.
        if(gpu && (dynamic_cast<GSGpuBackend*>(&static_cast<GSThreadedBackend&>(backend).Inner())!=gpu || !gpu->IsReady())) {
            std::cerr<<"OpenGL no disponible: fallback no cuenta como comparación\n"; return false;
        }
        auto *access=dynamic_cast<GSBackendStateAccess*>(&backend);
        GSBackendState restored;
        if(!access || !access->ImportState(initial.state) || !access->ExportState(restored)) {
            std::cerr<<"No se pudo restaurar/exportar el estado inicial\n"; return false;
        }
        if(const char *field=stateDifference(initial.state,restored,gpuMode)) {
            std::cerr<<"Restauración inicial distinta: "<<field<<'\n'; return false;
        }
        backend.Sync(GSSyncReason::DebugReadback);
        std::vector<uint8_t> restoredVram; backend.SnapshotVram(restoredVram);
        if(restoredVram!=initial.vram) { std::cerr<<"Restauración inicial de VRAM distinta\n"; return false; }
        return true;
    }
    // Se conserva cada imagen VISIBLE, sin filas de reserva ni padding del backend.
    struct VisibleFrame {
        uint32_t width=0,height=0;
        std::vector<uint8_t> pixels;
    };
    struct PassResult {
        struct Checkpoint { size_t record=0,draws=0; replay::Op op{}; uint64_t hash=0; };
        std::vector<uint8_t> vram;
        GSBackendState state;
        std::vector<VisibleFrame> frames;
        std::vector<Checkpoint> checkpoints;
        GSGpuBackend::Stats stats{};
        bool parity=true;
    };
    // GOW-Port: huellas acotadas para localizar variación ANTES del estado final.
    // No guardar una copia de 4 MiB por control. End y cuadros conservan comparación exacta.
    bool checkpoint(PassResult &result,size_t index,size_t draws,replay::Op op,const std::vector<uint8_t> &vram) {
        if(vram.size()!=PS2_GS_VRAM_SIZE || result.checkpoints.size()>=4096) {
            std::cerr<<"VRAM inválida o límite de 4096 controles sincronizados excedido\n"; return false;
        }
        uint64_t hash=14695981039346656037ull;
        for(const auto byte:vram) { hash^=byte; hash*=1099511628211ull; }
        result.checkpoints.push_back({index,draws,op,hash}); return true;
    }
    // GOW-Port: recortar solo en una frontera registrada. TEXFLUSH no drena GPU.
    bool validatePrefix(const std::filesystem::path &path,uint32_t last) {
        replay::Reader reader(path); replay::Record record;
        if(!reader.next(record) || record.op!=replay::Op::Initial) return false;
        size_t index=0;
        while(reader.next(record)) {
            ++index;
            if(index==last) {
                if(record.op==replay::Op::Flush || record.op==replay::Op::Sync ||
                   record.op==replay::Op::Present || record.op==replay::Op::End) return true;
                std::cerr<<"--hasta-registro requiere Flush, Sync, Present o End; registro="<<last<<'\n';
                return false;
            }
            if(record.op==replay::Op::End) break;
        }
        std::cerr<<"--hasta-registro excede la captura o el prefijo está incompleto: "<<reader.error<<'\n';
        return false;
    }
    bool validateCheckpoints(const std::filesystem::path &path,uint32_t last=0) {
        replay::Reader reader(path); replay::Record record; size_t count=0,index=0; bool ended=false;
        while(reader.next(record)) {
            if(record.op!=replay::Op::Initial) ++index;
            if(record.op==replay::Op::Flush || record.op==replay::Op::Sync ||
               record.op==replay::Op::Present || record.op==replay::Op::End) {
                if(++count>4096) { std::cerr<<"Límite de 4096 controles sincronizados excedido\n"; return false; }
            }
            ended=record.op==replay::Op::End;
            if(last && index==last) { ended=true; break; }
        }
        if(!reader.error.empty() || !ended) { std::cerr<<"Captura incompleta: "<<reader.error<<'\n'; return false; }
        return true;
    }
    GSGpuBackend::Stats statsDelta(const GSGpuBackend::Stats &a,const GSGpuBackend::Stats &b) {
        return {b.prims-a.prims,b.batches-a.batches,b.tiles-a.tiles,b.clutLoads-a.clutLoads,
                b.flushTarget-a.flushTarget,b.flushTexture-a.flushTexture,b.flushOther-a.flushOther};
    }
    void printStats(const GSGpuBackend::Stats &s,const std::string &mode) {
        std::cout<<"OpenGL DELTA batches="<<s.batches<<" prims="<<s.prims<<" tiles="<<s.tiles
                 <<" clutLoads="<<s.clutLoads<<" flushTarget="<<s.flushTarget
                 <<" flushTexture="<<s.flushTexture<<" flushOther="<<s.flushOther<<'\n';
        if(mode=="hardware") std::cout<<"hardware solicitado; ";
        else std::cout<<"compute solicitado; ";
        std::cout<<(s.prims==0?"sin primitivas":s.tiles==0?"sin tiles compute observados":"ruta mixta/compute")<<'\n';
    }
    void reportFirst(const replay::Record &record,size_t index,size_t draws,size_t n,size_t first) {
        std::cout<<"Primera divergencia: registro="<<index<<" op="<<unsigned(record.op)<<" draws="<<draws<<" bytes="<<n<<" first="<<first<<std::endl;
        if(record.op!=replay::Op::Submit) return;
        GSPrimitiveBatch batch{}; replay::pod(record,batch); const auto &s=batch.state;
        std::cout<<std::setprecision(17)<<"prim="<<unsigned(s.prim.type)<<" tme="<<s.prim.tme<<" fst="<<s.prim.fst<<" psm="<<unsigned(s.context.tex0.psm)
                 <<" frame="<<s.context.frame.fbp<<" test="<<std::hex<<s.context.test<<" alpha="<<s.context.alpha<<std::dec<<'\n';
        const auto &tex=s.context.tex0; const auto &frame=s.context.frame; const auto &z=s.context.zbuf;
        std::cout<<"textura tbp="<<tex.tbp0<<" tbw="<<unsigned(tex.tbw)<<" dimensiones="<<s.textureWidth<<','<<s.textureHeight
                 <<" linear="<<s.linearFilter<<" tfx="<<unsigned(tex.tfx)<<" tcc="<<unsigned(tex.tcc)
                 <<" clamp="<<std::hex<<s.context.clamp<<" tex1="<<s.context.tex1<<std::dec
                 <<" texa="<<unsigned(s.texa.ta0)<<','<<s.texa.aem<<','<<unsigned(s.texa.ta1)<<'\n';
        std::cout<<"destino fbp="<<frame.fbp<<" fbw="<<frame.fbw<<" psm="<<unsigned(frame.psm)
                 <<" mask="<<std::hex<<frame.fbmsk<<std::dec<<" zbp="<<z.zbp<<" zpsm="<<unsigned(z.psm)
                 <<" zmask="<<z.zmask<<" scissor="<<s.context.scissor.x0<<','<<s.context.scissor.x1
                 <<','<<s.context.scissor.y0<<','<<s.context.scissor.y1<<'\n';
        for(unsigned i=0;i<batch.vertexCount;++i) { const auto &v=batch.vertices[i];
            std::cout<<"v"<<i<<" xy="<<v.x<<','<<v.y<<" z="<<v.z<<" stq="<<v.s<<','<<v.t<<','<<v.q<<" uv="<<v.u<<','<<v.v<<'\n'; }
    }
    int runPass(const Options &options,uint32_t pass,const replay::Snapshot &initial,
                GSCpuBackend &reference,GSRasterBackend &candidate,GSGpuBackend *gpu,PassResult &result) {
        replay::Reader reader(options.capture); replay::Record record;
        replay::Snapshot check;
        if(!reader.next(record) || record.op!=replay::Op::Initial || !replay::decodeSnapshot(record,check) ||
           check.vram!=initial.vram || stateDifference(initial.state,check.state)) {
            std::cerr<<"Estado inicial inválido o captura modificada entre pasadas\n"; return 2;
        }
        const auto before=gpu?gpu->GetStats():GSGpuBackend::Stats{};
        PresentationFrame a,b;
        size_t index=0,draws=0,firstMismatch=SIZE_MAX,frameMismatch=0,visibleBytes=0;
        bool ended=false,stateMismatch=false;
        std::vector<uint8_t> actualA,actualB;
        const auto finish=[&](const replay::Snapshot *captured,replay::Op op) {
            reference.Sync(GSSyncReason::DebugReadback); reference.SnapshotVram(actualA);
            size_t first=0;
            if(captured) {
                const auto n=differences(captured->vram,actualA,first);
                std::cout<<"CPU vs captura final: bytes="<<n<<" first="<<first<<'\n';
                if(n) return 3;
            } else std::cout<<"Prefijo hasta registro="<<index<<"; el End original no se compara\n";
            GSBackendState state;
            if(!reference.ExportState(state)) return 3;
            if(captured) if(const char *field=stateDifference(captured->state,state)) {
                std::cerr<<"El estado CPU final no reproduce la captura: "<<field<<'\n'; return 3;
            }
            candidate.Sync(GSSyncReason::Finish); candidate.Sync(GSSyncReason::DebugReadback); candidate.SnapshotVram(actualB);
            const auto m=differences(actualA,actualB,first);
            std::cout<<"CPU vs "<<options.mode<<(captured?" final: bytes=":" prefijo: bytes=")<<m<<" first="<<first<<'\n';
            if(m && firstMismatch==SIZE_MAX) firstMismatch=index;
            auto *access=dynamic_cast<GSBackendStateAccess*>(&candidate);
            if(!access || !access->ExportState(result.state)) return 3;
            if(const char *field=stateDifference(state,result.state,options.gpuMode())) {
                stateMismatch=true; std::cout<<"CPU vs "<<options.mode
                    <<(captured?" estado final distinto: ":" estado del prefijo distinto: ")<<field<<'\n';
            }
            if(captured && options.syncCheckpoints && !checkpoint(result,index,draws,op,actualB)) return 2;
            result.vram=std::move(actualB); ended=true;
            return 0;
        };
        while(reader.next(record)) {
            ++index;
            if(record.op==replay::Op::End) {
                replay::Snapshot final; if(!replay::decodeSnapshot(record,final)) return 2;
                const int code=finish(&final,record.op); if(code) return code;
                break;
            }
            if(record.op==replay::Op::Initial || !apply(reference,record,a) || !apply(candidate,record,b)) {
                std::cerr<<"Fallo en registro "<<index<<" op="<<unsigned(record.op)<<'\n'; return 3;
            }
            if(record.op==replay::Op::Submit) ++draws;
            if(record.op==replay::Op::Present) {
                std::vector<uint8_t> visibleA,visibleB;
                if(!GowRenderTool::normalize(a,visibleA,GowRenderTool::PixelLayout::HostRows640) ||
                   !GowRenderTool::normalize(b,visibleB,GowRenderTool::PixelLayout::HostRows640)) {
                    std::cerr<<"Layout de presentación inválido en registro "<<index<<'\n'; return 3;
                }
                size_t first=0; const auto n=differences(visibleA,visibleB,first);
                if(n || a.width!=b.width || a.height!=b.height) {
                    ++frameMismatch;
                    if(frameMismatch==1 && (!ppm(options.image(pass,"cpu"),a) || !ppm(options.image(pass,"candidate"),b))) return 2;
                }
                if(options.multiple()) {
                    // Acotar el historial exacto sin cargar cientos de cuadros o el volcado entero.
                    visibleBytes+=visibleB.size();
                    if(visibleBytes>replay::kLimit) {
                        std::cerr<<"Las imágenes visibles de una pasada exceden el límite de estabilidad (64 MiB)\n"; return 2;
                    }
                    result.frames.push_back({b.width,b.height,std::move(visibleB)});
                }
            }
            // Estos comandos ya drenan el lote en los backends. TEXFLUSH no lo hace
            // en GPU: excluirlo para no introducir cortes de lote nuevos en esta sonda.
            if(options.syncCheckpoints && (record.op==replay::Op::Flush || record.op==replay::Op::Sync ||
                                          record.op==replay::Op::Present)) {
                candidate.Sync(GSSyncReason::DebugReadback); candidate.SnapshotVram(actualB);
                if(!checkpoint(result,index,draws,record.op,actualB)) return 2;
            }
            if(options.lockstep && firstMismatch==SIZE_MAX && (record.op==replay::Op::Submit || record.op==replay::Op::Upload || record.op==replay::Op::Transfer ||
                            record.op==replay::Op::Clear || record.op==replay::Op::Write || record.op==replay::Op::Reset)) {
                reference.Sync(GSSyncReason::DebugReadback); reference.SnapshotVram(actualA);
                candidate.Sync(GSSyncReason::DebugReadback); candidate.SnapshotVram(actualB);
                size_t first=0; const auto n=differences(actualA,actualB,first);
                if(n) { firstMismatch=index; reportFirst(record,index,draws,n,first); }
            }
            if(options.lastRecord && index==options.lastRecord) {
                const int code=finish(nullptr,record.op); if(code) return code;
                break;
            }
        }
        if(!reader.error.empty() || !ended) { std::cerr<<"Captura incompleta: "<<reader.error<<'\n'; return 2; }
        if(!ppm(options.image(pass,"last_cpu"),a) || !ppm(options.image(pass,"last_candidate"),b)) return 2;
        std::cout<<"registros="<<index<<" draws="<<draws<<" framesDistintos="<<frameMismatch
                 <<(options.lockstep?" primeraDivergencia=":" primerControlVRAMDistinto=")<<firstMismatch<<'\n';
        result.parity=firstMismatch==SIZE_MAX && frameMismatch==0 && !stateMismatch;
        if(gpu) {
            const auto stats=gpu->GetStats(); result.stats=statsDelta(before,stats);
            if(options.multiple()) printStats(result.stats,options.mode);
            else std::cout<<"OpenGL batches="<<stats.batches<<" prims="<<stats.prims<<" tiles="<<stats.tiles<<'\n';
        }
        return result.parity?0:1;
    }
    bool comparePasses(uint32_t pass,const PassResult &previous,const PassResult &current,bool gpuMode) {
        size_t first=0; const auto bytes=differences(previous.vram,current.vram,first);
        const char *field=stateDifference(previous.state,current.state);
        bool equalCheckpoints=previous.checkpoints.size()==current.checkpoints.size();
        const size_t checkpointCount=std::min(previous.checkpoints.size(),current.checkpoints.size());
        size_t changedCheckpoints=0;
        for(size_t i=0;i<checkpointCount;++i) {
            const auto &a=previous.checkpoints[i],&b=current.checkpoints[i];
            if(a.record!=b.record || a.op!=b.op || a.draws!=b.draws || a.hash!=b.hash) {
                if(!changedCheckpoints) std::cout<<"Primer control variable: registro="<<b.record
                    <<" op="<<unsigned(b.op)<<" draws="<<b.draws<<" pasada="<<pass-1<<"->"<<pass
                    <<" huella="<<std::hex<<a.hash<<"->"<<b.hash<<std::dec<<'\n';
                ++changedCheckpoints; equalCheckpoints=false;
            }
        }
        if(!previous.checkpoints.empty() || !current.checkpoints.empty())
            std::cout<<"Controles sincronizados: previos="<<previous.checkpoints.size()
                     <<" actuales="<<current.checkpoints.size()<<" distintos="<<changedCheckpoints<<'\n';
        const size_t common=std::min(previous.frames.size(),current.frames.size());
        size_t frames=std::max(previous.frames.size(),current.frames.size())-common;
        for(size_t i=0;i<common;++i) {
            const auto &a=previous.frames[i],&b=current.frames[i];
            size_t pixelFirst=0;
            const size_t pixelBytes=differences(a.pixels,b.pixels,pixelFirst);
            const bool dimensionsMatch=a.width==b.width && a.height==b.height;
            frames+=!dimensionsMatch || pixelBytes!=0;
            std::cout<<"Candidato cuadro="<<i+1<<" pasada="<<pass-1<<"->"<<pass
                     <<" bytes="<<pixelBytes<<" first="<<pixelFirst
                     <<" dimensionesIguales="<<dimensionsMatch<<'\n';
        }
        const bool equalRaster=previous.stats.prims==current.stats.prims && previous.stats.tiles==current.stats.tiles;
        std::cout<<"Candidato pasada "<<pass-1<<" vs "<<pass<<": bytes="<<bytes<<" first="<<first
                 <<" estado="<<(field?field:"igual")<<" framesDistintos="<<frames
                 <<" framesPrevios="<<previous.frames.size()<<" framesActuales="<<current.frames.size()<<'\n';
        if(gpuMode) {
            std::cout<<(equalRaster?"Contadores de raster iguales":"Contadores de raster distintos")
                     <<": prims="<<previous.stats.prims<<"->"<<current.stats.prims<<" tiles="<<previous.stats.tiles<<"->"<<current.stats.tiles<<'\n';
            if(!equalRaster && (bytes || field || frames || !equalCheckpoints))
                std::cout<<"El resultado distinto entre pasadas no certifica inestabilidad de una misma ruta de raster\n";
        }
        return bytes==0 && field==nullptr && frames==0 && equalCheckpoints;
    }
    int run(const Options &options) {
        std::error_code outputError;
        std::filesystem::create_directories(options.output,outputError);
        if(outputError || !std::filesystem::is_directory(options.output,outputError)) {
            std::cerr<<"Directorio de salida inválido: "<<options.output.string()<<'\n'; return 2;
        }
        replay::Reader reader(options.capture); replay::Record record; replay::Snapshot initial;
        if(!reader.next(record) || record.op!=replay::Op::Initial) { std::cerr<<reader.error<<"; falta estado inicial\n"; return 2; }
        if(!replay::decodeSnapshot(record,initial)) { std::cerr<<"Estado inicial inválido\n"; return 2; }
        // Rechazar exceso de readbacks antes de crear el backend o repetir dibujos.
        if(options.lastRecord && !validatePrefix(options.capture,options.lastRecord)) return 2;
        if(options.syncCheckpoints && !validateCheckpoints(options.capture,options.lastRecord)) return 2;
        if(initial.state.cachePageBase!=UINT32_MAX) {
            const auto base=initial.state.cachePageBase; const auto size=initial.state.cacheBytes.size();
            if(base%size || uint64_t(base)+size>initial.vram.size()) return 2;
            size_t stale=0; for(size_t i=0;i<size;++i) stale+=initial.state.cacheBytes[i]!=initial.vram[base+i];
            std::cout<<"Cache inicial: base="<<base<<" bytesDistintosDeVRAM="<<stale<<'\n';
            if(options.gpuMode() && stale) { std::cerr<<"Capturar después de TEXFLUSH: la página CPU inicial contiene texels anteriores\n"; return 2; }
        }
        // Crear los backends UNA vez. Los vectores viven más y nunca se redimensionan.
        auto referenceVram=initial.vram,candidateVram=initial.vram;
        GSCpuBackend reference;
        std::unique_ptr<GSRasterBackend> candidate; GSGpuBackend *gpu=nullptr;
        if(options.gpuMode()) {
            auto backend=std::make_unique<GSGpuBackend>(); gpu=backend.get();
            backend->SetFeedbackSnapshotEnabled(options.snapshotFeedback);
            backend->SetHardwareRasterAllowed(options.mode=="hardware"); candidate=std::make_unique<GSThreadedBackend>(std::move(backend));
        } else candidate=std::make_unique<GSCpuBackend>();
        if(options.snapshotFeedback)
            std::cout<<"Feedback experimental: fuente congelada por Submit; no emula la cache PS2 de 8 KiB\n";
        if(options.pauseMs)
            std::cout<<"Pausa de diagnostico entre pasadas: "<<options.pauseMs<<" ms\n";
        if(options.syncCheckpoints)
            std::cout<<"Controles de variación en Flush/Sync/Present/End: añaden readback, no miden FPS\n";
        if(options.lastRecord)
            std::cout<<"Tramo limitado a registro "<<options.lastRecord<<" (Initial=0); no valida el resto de la captura\n";
        struct Restore { unsigned csr=_mm_getcsr(); ~Restore(){_mm_setcsr(csr);} } restore;
        PassResult previous; bool differencesSeen=false;
        for(uint32_t iteration=0;iteration<options.repetitions;++iteration) {
            // GOW-Port: dar tiempo al compilador de shaders conservando el mismo backend.
            if(iteration && options.pauseMs) std::this_thread::sleep_for(std::chrono::milliseconds(options.pauseMs));
            const uint32_t pass=iteration+1;
            _mm_setcsr(restore.csr);
            if(!restoreInitial(reference,referenceVram,initial,false) ||
               !restoreInitial(*candidate,candidateVram,initial,options.gpuMode(),gpu)) return 2;
            if(options.multiple()) std::cout<<"Pasada "<<pass<<'/'<<options.repetitions<<"; restauración inicial exacta (cache GPU ausente esperada="<<options.gpuMode()<<")\n";
            PassResult current; const int code=runPass(options,pass,initial,reference,*candidate,gpu,current);
            if(code>=2) return code;
            differencesSeen|=code!=0;
            if(options.multiple()) {
                std::cout<<"Paridad CPU vs "<<options.mode<<" pasada="<<pass<<": "<<(current.parity?"igual":"distinta")<<'\n';
                if(iteration) differencesSeen|=!comparePasses(pass,previous,current,options.gpuMode());
                previous=std::move(current);
            }
        }
        return differencesSeen?1:0;
    }
}

#ifdef _WIN32
int wmain(int argc,wchar_t **argv) {
#else
int main(int argc,char **argv) {
#endif
    Options options;
    if(!parse(argc,argv,options)) {
        std::cerr<<"Uso: repetir_gs captura.bin cpu|compute|hardware [--lockstep] [--snapshot-feedback] [--repeticiones N] [--pausa-ms M] [--checkpoints-sync] [--hasta-registro R] [directorio]\n"
                 <<"N/R positivos; R en Flush/Sync/Present/End (Initial=0); M=1..1000 requiere varias pasadas; no se admiten opciones desconocidas ni duplicadas\n"; return 2;
    }
    return run(options);
}
