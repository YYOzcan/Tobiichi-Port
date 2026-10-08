// GOW-Port: captura/repetición sintética; no depende del juego ni de OpenGL.
#include "../src/gow_gs_replay.h"
#include "runtime/gs/gs_cpu_backend.h"

static bool optionsTest()
{
    using namespace gow_gs_replay;
    CaptureOptions options; const char *error=nullptr;
    if(!captureOptions(nullptr,nullptr,nullptr,options,error) || error ||
       options.after!=150 || options.seconds!=3 || options.atTextureFlush) return false;
    if(!captureOptions("470.5","2.25","1",options,error) || error ||
       options.after!=470.5 || options.seconds!=2.25 || !options.atTextureFlush) return false;
    if(!captureOptions("0","0.1","0",options,error) || options.after!=0 ||
       options.seconds!=0.1 || options.atTextureFlush) return false;
    if(!captureOptions("3600","60",nullptr,options,error)) return false;
    // GOW-Port: una opción inválida no aplica parcialmente las demás.
    const char *badNumbers[]={"", "nan", "inf", "1x", "1,5", "-1", "3601", "1e999", " 1"};
    for(const auto *text:badNumbers) {
        options={17,9,true};
        if(captureOptions(text,"2","0",options,error) || !error ||
           options.after!=17 || options.seconds!=9 || !options.atTextureFlush) return false;
    }
    for(const auto *text:{"0","0.09","60.1","nan","1s"})
        if(captureOptions("1",text,"1",options,error) || !error) return false;
    for(const auto *text:{"","true","2","01"})
        if(captureOptions("1","2",text,options,error) || !error) return false;
    return true;
}

static bool textureFlushBoundaryTest(std::filesystem::path path,const GSPrimitiveBatch &sprite)
{
    using namespace gow_gs_replay;
    path += ".texflush";
    std::vector<uint8_t> vram(PS2_GS_VRAM_SIZE);
    PS2Memory memory; if(!memory.initialize()) return false;
    Backend capture(std::make_unique<GSCpuBackend>(),&memory,path,0,3600,true);
    capture.Initialize(vram.data(),uint32_t(vram.size()));
    // Un TEXFLUSH del menú se envía, pero no abre una captura de partida.
    capture.TextureFlush(); if(capture.finish()) return false;
    const uint32_t gameState=11; std::memcpy(memory.getRDRAM()+0x29E560u,&gameState,4);
    // Caché antigua que difiere de VRAM: no se debe invalidar al instalar el wrapper.
    GSBackendState stale; if(!capture.ExportState(stale)) return false;
    stale.cachePageBase=8192; stale.cacheBytes.fill(0x5a);
    if(!capture.ImportState(stale)) return false;
    capture.Submit(sprite); capture.Present(GSPresentationRequest{});
    GSTransferCommand command{}; command.direction=0; command.bitbltbuf.dbp=4;
    command.bitbltbuf.dbw=1; command.bitbltbuf.dpsm=1; command.trxreg={1,1};
    capture.BeginTransfer(command); const uint8_t prefix[]={0x12,0x34};
    capture.UploadImage(prefix,2);
    GSBackendState before;
    if(!capture.ExportState(before) || before.cachePageBase!=8192 ||
       before.cacheBytes!=stale.cacheBytes || before.upload24.size!=2 ||
       capture.ReadVram(0,0,1,1,1)!=0x80332211u || capture.finish()) return false;
    const auto initialVram=vram;
    capture.TextureFlush(); // El TEXFLUSH real abre la captura con caché invalidada.
    const uint8_t last=0x56; capture.UploadImage(&last,1);
    auto next=sprite; next.vertices[0].r=next.vertices[1].r=0x77;
    capture.Submit(next); capture.TextureFlush();
    if(!capture.finish()) return false;
    const auto closedSize=std::filesystem::file_size(path);
    capture.TextureFlush();
    if(capture.finish() || std::filesystem::file_size(path)!=closedSize) return false;
    // Cerrar Reader antes de borrar el archivo: Windows no permite eliminarlo abierto.
    {
        Reader reader(path); Record record; unsigned draws=0,uploads=0,flushes=0;
        bool initial=false,ended=false; GSCpuBackend replay;
        std::vector<uint8_t> repeated(PS2_GS_VRAM_SIZE);
        replay.Initialize(repeated.data(),uint32_t(repeated.size()));
        const uint32_t originalMxcsr=_mm_getcsr();
        // Restaurar el modo del llamador también si falla una comprobación de replay.
        struct Restore { uint32_t value; ~Restore() { _mm_setcsr(value); } } restore{originalMxcsr};
        while(reader.next(record)) {
            switch(record.op) {
            case Op::Initial: {
                Snapshot state;
                if(initial || !decodeSnapshot(record,state) || state.state.cachePageBase!=UINT32_MAX ||
                   state.state.upload24.size!=2 || state.vram!=initialVram) return false;
                std::memcpy(repeated.data(),state.vram.data(),repeated.size());
                if(!replay.ImportState(state.state)) return false;
                initial=true; break;
            }
            case Op::Mxcsr: { uint32_t csr; if(!pod(record,csr)) return false; _mm_setcsr(csr); break; }
            case Op::Upload: replay.UploadImage(record.data.data(),uint32_t(record.data.size())); ++uploads; break;
            case Op::Submit: { GSPrimitiveBatch batch; if(!pod(record,batch)) return false; replay.Submit(batch); ++draws; break; }
            case Op::TextureFlush: replay.TextureFlush(); ++flushes; break;
            case Op::End: {
                Snapshot state;
                if(!decodeSnapshot(record,state) || state.vram!=vram || repeated!=vram ||
                   state.state.upload24.size || state.state.cachePageBase!=UINT32_MAX) return false;
                ended=true; break;
            }
            default: return false; // Ningún comando anterior a la frontera debe haberse grabado.
            }
        }
        if(!initial || !ended || draws!=1 || uploads!=1 || flushes!=1 || !reader.error.empty()) return false;
    }
    std::filesystem::remove(path);
    // Un TEXFLUSH anterior al plazo se envía al backend pero no inicia la captura.
    path += ".delay";
    {
        Backend delayed(std::make_unique<GSCpuBackend>(),nullptr,path,3600,3,true);
        delayed.Initialize(vram.data(),uint32_t(vram.size()));
        if(!delayed.ImportState(stale)) return false;
        delayed.TextureFlush(); delayed.Submit(sprite);
        GSBackendState state;
        if(!delayed.ExportState(state) || state.cachePageBase!=UINT32_MAX || delayed.finish()) return false;
    }
    if(std::filesystem::file_size(path)!=sizeof(Header)) return false;
    std::filesystem::remove(path);
    return true;
}

#ifdef _WIN32
int wmain(int argc,wchar_t **argv)
#else
int main(int argc,char **argv)
#endif
{
    if(argc!=2) return 2;
    const std::filesystem::path path=argv[1];
    std::vector<uint8_t> vram(PS2_GS_VRAM_SIZE);
    gow_gs_replay::Backend capture(std::make_unique<GSCpuBackend>(),nullptr,path,0,3600);
    capture.Initialize(vram.data(),uint32_t(vram.size()));
    GSTransferCommand command{}; command.direction=0; command.bitbltbuf.dbw=1;
    command.bitbltbuf.dpsm=1; command.trxreg={2,1}; capture.BeginTransfer(command);
    const uint8_t a[]={0x12,0x34},b[]={0x56,0x78,0x9a,0xbc};
    capture.UploadImage(a,2); capture.UploadImage(b,4);
    GSPrimitiveBatch sprite{}; sprite.vertexCount=2; sprite.state.prim.type=GS_PRIM_SPRITE;
    sprite.state.context.frame.fbw=1; sprite.state.context.scissor={0,7,0,7};
    sprite.state.context.zbuf.zmask=true; sprite.state.context.test=1ull<<17; sprite.state.colclamp=1;
    sprite.vertices[0].r=0x11; sprite.vertices[0].g=0x22; sprite.vertices[0].b=0x33; sprite.vertices[0].a=0x80;
    sprite.vertices[1]=sprite.vertices[0]; sprite.vertices[1].x=4; sprite.vertices[1].y=4;
    capture.Submit(sprite); capture.TextureFlush();
    if(capture.ReadVram(0,0,1,1,1)!=0x80332211u || !capture.finish()) return 1;
    gow_gs_replay::Reader reader(path); gow_gs_replay::Record record;
    bool initial=false,ended=false; unsigned uploads=0,draws=0;
    while(reader.next(record)) {
        if(record.op==gow_gs_replay::Op::Initial || record.op==gow_gs_replay::Op::End) {
            gow_gs_replay::Snapshot state; if(!gow_gs_replay::decodeSnapshot(record,state)) return 1;
            if(record.op==gow_gs_replay::Op::Initial) initial=true; else ended=true;
            // El parser rechaza tamaños inconsistentes y bytes CT24 inválidos.
            auto bad=record; bad.data.pop_back(); if(gow_gs_replay::decodeSnapshot(bad,state)) return 1;
            gow_gs_replay::FixedState fixed{}; std::memcpy(&fixed,record.data.data(),sizeof(fixed));
            fixed.upload24.size=3; bad=record; std::memcpy(bad.data.data(),&fixed,sizeof(fixed));
            if(gow_gs_replay::decodeSnapshot(bad,state)) return 1;
        }
        if(record.op==gow_gs_replay::Op::Upload) ++uploads;
        if(record.op==gow_gs_replay::Op::Submit) ++draws;
    }
    if(!initial || !ended || uploads!=2 || draws!=1 || !reader.error.empty()) return 1;
    // Un archivo cortado no se puede certificar como una captura completa.
    auto truncated=path; truncated += ".truncated";
    std::ifstream original(path,std::ios::binary); std::vector<char> raw((std::istreambuf_iterator<char>(original)),{});
    { std::ofstream out(truncated,std::ios::binary); out.write(raw.data(),raw.size()-1); }
    { gow_gs_replay::Reader incomplete(truncated); while(incomplete.next(record)) {}
      if(incomplete.error.empty()) return 1; }
    std::filesystem::remove(truncated);
    if(!optionsTest()) { std::fprintf(stderr,"Opciones de captura: fallo\n"); return 1; }
    if(!textureFlushBoundaryTest(path,sprite)) { std::fprintf(stderr,"Frontera TEXFLUSH: fallo\n"); return 1; }
    std::fprintf(stderr,"Captura sintética, parser, truncamiento, opciones y frontera TEXFLUSH: OK\n");
    return 0;
}
