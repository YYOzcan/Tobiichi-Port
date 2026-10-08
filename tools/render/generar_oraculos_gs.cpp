// GOW-Port: exporta los cuatro patrones usados como referencia RGBA de PCSX2 software.
// Entradas procedurales; no contiene archivos, texels ni estado del juego.
#include "gow_gs_replay.h"
#include "runtime/gs/gs_cpu_backend.h"
#include "runtime/gs/gs_swizzle.h"
#include "gs_pcsx2_dump.h"
#include <iostream>

#ifdef _WIN32
int wmain(int argc,wchar_t **argv)
#else
int main(int argc,char **argv)
#endif
{
    if(argc>2) return 2;
    const auto output=argc==2?std::filesystem::path(argv[1]):std::filesystem::path("logs/oraculos_gs");
    std::error_code error;std::filesystem::create_directories(output,error);
    if(error || !std::filesystem::is_directory(output,error)) return 2;
    using namespace gow_gs_reference;
    const char *names[]={"bilinear","negativos","limites","bilinear_stq"};
    const GridCase fixtures[]={GridCase::Bilinear,GridCase::Negative,GridCase::Boundary,GridCase::BilinearStq};
    const uint32_t bilinearColors[]={0x01fefe80u,0xff01017fu,0x807f8002u,0x038080fdu};
    const auto &format=GSSwizzle::GetFormat(GS_PSM_CT32);
    for(unsigned fixture=0;fixture<4;++fixture) {
        const bool fst=fixture==0,linear=fst || fixture==3;const unsigned size=fst?2:4;
        std::vector<uint8_t> vram(PS2_GS_VRAM_SIZE);
        for(unsigned y=0;y<size;++y) for(unsigned x=0;x<size;++x) {
            const unsigned i=y*size+x;
            const uint32_t color=fst?bilinearColors[i]:
                (17u*i<<24)|((231u-13u*i)<<16)|((19u+11u*i)<<8)|(7u+15u*i);
            const auto p=GSSwizzle::Locate(format,8192,8,x,y);std::memcpy(vram.data()+p.byte,&color,4);
        }
        const auto name=std::string("feedback_gs_oraculo_")+names[fixture];
        if(!gridDump(output/(name+".gs"),vram,fixtures[fixture])) return 2;
        gow_gs_replay::Backend capture(std::make_unique<GSCpuBackend>(),nullptr,output/(name+".bin"),0,3600);
        capture.Initialize(vram.data(),uint32_t(vram.size()));
        GSPrimitiveBatch batch{};batch.vertexCount=2;batch.state.prim.type=GS_PRIM_SPRITE;
        batch.state.prim.tme=true;batch.state.prim.fst=fst;batch.state.linearFilter=linear;
        batch.state.textureWidth=batch.state.textureHeight=size;batch.state.colclamp=1;
        auto &c=batch.state.context;c.frame.fbw=8;c.scissor={0,15,0,15};
        c.zbuf.zbp=104;c.zbuf.psm=GS_PSM_Z24;c.zbuf.zmask=true;c.test=0x30000;
        c.clamp=fst?5:0;c.tex1=linear?0x60:0;c.tex0.tbp0=8192;c.tex0.tbw=8;
        c.tex0.tw=c.tex0.th=fst?1:2;c.tex0.tcc=1;c.tex0.tfx=1;
        for(unsigned y=0;y<16;++y) for(unsigned x=0;x<16;++x) {
            for(auto &v:batch.vertices) {
                v.r=v.g=v.b=v.a=128;v.z=7;v.u=uint16_t(8+x);v.v=uint16_t(8+y);v.q=1;
                if(!fst) {v.s=gridCoordinate(fixtures[fixture],x)/4;v.t=gridCoordinate(fixtures[fixture],y)/4;}
            }
            batch.vertices[0].x=float(x);batch.vertices[0].y=float(y);
            batch.vertices[1].x=float(x+1);batch.vertices[1].y=float(y+1);capture.Submit(batch);
        }
        GSPresentationRequest request{};request.pmode=1;request.dispfb1=8ull<<9;
        request.display1=(511ull<<32)|(447ull<<44);
        const auto image=capture.Present(request);
        if(image.width!=512 || image.height!=448 || !capture.finish()) return 2;
        std::ofstream rgba(output/(name+".rgba"),std::ios::binary);
        for(unsigned y=0;y<16;++y) for(unsigned x=0;x<16;++x) {
            const auto p=GSSwizzle::Locate(format,0,8,x,y);rgba.write(reinterpret_cast<const char*>(vram.data()+p.byte),4);
        }
        rgba.close();if(!rgba) return 2;
        std::cout<<"Oraculo procedural="<<name<<"; RGBA 16x16 sin datos del juego\n";
    }
    return 0;
}
