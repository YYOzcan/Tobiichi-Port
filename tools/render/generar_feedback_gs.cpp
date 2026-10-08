// GOW-Port: genera capturas procedurales GS, sin archivos ni texels del juego.
#include "gow_gs_replay.h"
#include "runtime/gs/gs_cpu_backend.h"
#include "runtime/gs/gs_swizzle.h"
#include "gs_pcsx2_dump.h"
#include <algorithm>
#include <cstring>
#include <iostream>

#ifdef _WIN32
int wmain(int argc,wchar_t **argv)
#else
int main(int argc,char **argv)
#endif
{
    bool pcsx2=false,separations=false,hasOutput=false;
    auto output=std::filesystem::path("logs");
    for(int i=1;i<argc;++i) {
        const auto argument=std::filesystem::path(argv[i]);
        if(argument=="--pcsx2" && !pcsx2) pcsx2=true;
        else if(argument=="--separaciones" && !separations) separations=true;
        else if(!hasOutput && !argument.native().empty() && argument.native()[0]!='-') {output=argument;hasOutput=true;}
        else {std::cerr<<"Uso: generar_feedback_gs [directorio=logs] [--pcsx2] [--separaciones]\n";return 2;}
    }
    std::error_code error;
    std::filesystem::create_directories(output,error);
    if(error || !std::filesystem::is_directory(output,error)) return 2;
    constexpr unsigned sourceBytes=1u<<20,disjointBytes=2u<<20;
    constexpr unsigned width=64,height=416,pitch=8;
    const auto &format=GSSwizzle::GetFormat(GS_PSM_CT32);
    std::vector<uint8_t> seed(PS2_GS_VRAM_SIZE);
    for(unsigned y=0;y<height;++y) for(unsigned x=0;x<width;++x) {
        const uint32_t color=0x80000000u | ((x*37u+y*13u+x*y*3u)&255u) |
            (((x*11u+y*29u)&255u)<<8u) | (((x*x*5u+y*47u)&255u)<<16u);
        const auto location=GSSwizzle::Locate(format,0,pitch,x,y);
        if(location.byte+4>sourceBytes) return 2;
        std::memcpy(seed.data()+location.byte,&color,4);
    }
    for(unsigned separation=0;separation<(separations?3u:1u);++separation)
    for(unsigned variant=0;variant<3;++variant) {
        const auto boundary=static_cast<gow_gs_reference::FeedbackBoundary>(separation);
        const char *suffix=separation==1?"_texflush":separation==2?"_scissor":"";
        const bool disjoint=variant==1,linear=variant!=2;
        const char *name=disjoint?"disjoint":linear?"self":"nearest";
        auto vram=seed;
        if(disjoint) {
            std::memcpy(vram.data()+disjointBytes,vram.data(),sourceBytes);
            unsigned checks=0;
            // Verificar también los vecinos bilineales y el remapeo de negativos por CLAMP.
            for(int rawY=-1;rawY<=int(height);++rawY) for(int rawX=-1;rawX<=int(width);++rawX) {
                const unsigned x=unsigned(std::max(rawX,0)),y=unsigned(std::max(rawY,0));
                const auto from=GSSwizzle::Locate(format,0,pitch,x,y);
                const auto to=GSSwizzle::Locate(format,disjointBytes/256u,pitch,x,y);
                if(from.byte+4>sourceBytes || to.byte!=from.byte+disjointBytes ||
                   to.byte+4>vram.size() || std::memcmp(vram.data()+from.byte,vram.data()+to.byte,4)) return 2;
                ++checks;
            }
            std::cout<<"Vecinos copiados y verificados="<<checks<<'\n';
        }
        const auto base=std::string("feedback_gs_")+name+suffix;
        const auto path=output/(base+".bin");
        if(pcsx2 && !gow_gs_reference::feedbackDump(output/(base+".gs"),vram,disjoint,linear,boundary)) return 2;
        gow_gs_replay::Backend capture(std::make_unique<GSCpuBackend>(),nullptr,path,0,3600);
        capture.Initialize(vram.data(),uint32_t(vram.size()));
        for(unsigned slice=0;slice<2;++slice) {
            if(slice==1 && boundary==gow_gs_reference::FeedbackBoundary::Texflush) capture.TextureFlush();
            GSPrimitiveBatch batch{}; batch.vertexCount=2; batch.state.prim.type=GS_PRIM_SPRITE;
            batch.state.prim.tme=true; batch.state.prim.fst=true; batch.state.linearFilter=linear;
            batch.state.textureWidth=1024; batch.state.textureHeight=1024; batch.state.colclamp=1;
            auto &context=batch.state.context;
            context.frame.fbw=pitch; context.frame.psm=GS_PSM_CT32; context.frame.fbmsk=0xff000000u;
            context.scissor={0,511,0,447}; context.zbuf.zbp=104;
            // 510 sigue fuera de x=0..63: cambia el estado, no la cobertura.
            if(slice==1 && boundary==gow_gs_reference::FeedbackBoundary::Scissor) context.scissor.x1=510;
            context.zbuf.psm=GS_PSM_Z24; context.zbuf.zmask=true;
            context.test=0x31001; context.clamp=5; context.tex1=linear?0x60:0;
            context.tex0.psm=GS_PSM_CT32; context.tex0.tbw=pitch;
            context.tex0.tw=context.tex0.th=10; context.tex0.tcc=1; context.tex0.tfx=0;
            context.tex0.tbp0=disjoint?disjointBytes/256u:0;
            for(auto &vertex:batch.vertices) {vertex.r=vertex.g=vertex.b=vertex.a=128;vertex.z=7;}
            batch.vertices[0].x=slice*32; batch.vertices[0].u=slice*32*16;
            batch.vertices[1].x=(slice+1)*32; batch.vertices[1].y=height;
            batch.vertices[1].u=(slice+1)*32*16; batch.vertices[1].v=height*16;
            capture.Submit(batch);
        }
        GSPresentationRequest request{}; request.pmode=1; request.dispfb1=8ull<<9;
        request.display1=(511ull<<32)|(447ull<<44);
        const auto image=capture.Present(request);
        if(image.width!=512 || image.height!=448 || !capture.finish()) return 2;
        std::cout<<"Captura procedural="<<path.string()<<" imagen="<<image.width<<'x'<<image.height<<'\n';
    }
    return 0;
}
