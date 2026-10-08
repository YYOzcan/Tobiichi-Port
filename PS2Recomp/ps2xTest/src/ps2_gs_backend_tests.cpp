// GOW-Port: regresiones de la adaptación OpenGL/cola de SotC ac9efa0.
#include "MiniTest.h"
#include "runtime/gs/gs_cpu_backend.h"
#include "runtime/gs/gs_gpu_backend.h"
#include "runtime/gs/gs_threaded_backend.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/gs/gs_swizzle.h"
#include "runtime/gs/ps2_gs_memory.h"
#include "runtime/ps2_memory.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <thread>
#include <vector>
#include <xmmintrin.h>

namespace
{
    // GOW-Port: el GS recibe datos, no debe heredar el redondeo SSE del EE/VU.
    void cpuRoundingIndependent(TestCase &t, bool threaded)
    {
        struct Restore { unsigned csr=_mm_getcsr(); ~Restore(){_mm_setcsr(csr);} } restore;
        auto render=[&](unsigned mode,unsigned fixture) {
            _mm_setcsr(restore.csr & ~_MM_ROUND_MASK);
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize);
            std::unique_ptr<GSRasterBackend> backend=std::make_unique<GSCpuBackend>();
            if(threaded) backend=std::make_unique<GSThreadedBackend>(std::move(backend));
            backend->Initialize(vram.data(),uint32_t(vram.size()));
            GSPrimitiveBatch b{}; b.vertexCount=3; b.state.prim.type=GS_PRIM_TRIANGLE;
            b.state.context.frame.fbw=1; b.state.context.scissor={0,63,0,63};
            b.state.context.zbuf.zmask=true; b.state.context.test=1ull<<17; b.state.colclamp=1;
            b.vertices[0].x=20;b.vertices[0].y=20;b.vertices[1].x=37;b.vertices[1].y=20;b.vertices[2].x=20;b.vertices[2].y=39;
            for(auto &v:b.vertices) {v.a=128;v.r=128;v.g=128;v.b=128;v.z=7;}
            if(fixture==0) {
                b.state.prim.iip=true;b.vertices[0].r=0;b.vertices[1].r=17;b.vertices[2].r=19;
            } else {
                b.state.prim.tme=true;b.state.prim.fst=fixture==1;
                auto &tex=b.state.context.tex0;tex.tbp0=256;tex.tbw=1;tex.tw=6;tex.th=6;tex.tfx=1;tex.tcc=1;
                for(unsigned y=0;y<64;++y) for(unsigned x=0;x<64;++x)
                    backend->WriteVram(0,256,1,x,y,0x80000000u|(x*3u)|((y*3u)<<8)|(((x+y)*2u)<<16));
                b.vertices[1].u=272;b.vertices[2].v=304;
                const float q[]={1.5f,2.0f,1.0f};
                for(unsigned i=0;i<3;++i) {
                    b.vertices[i].q=q[i];b.vertices[i].s=q[i]*(i==1?.75f:.25f);b.vertices[i].t=q[i]*(i==2?.75f:.25f);
                }
            }
            const unsigned before=(_mm_getcsr() & ~_MM_ROUND_MASK) | mode;
            _mm_setcsr(before);backend->Submit(b);backend->Sync(GSSyncReason::Finish);
            const unsigned control=_MM_ROUND_MASK|_MM_MASK_MASK|_MM_FLUSH_ZERO_MASK|0x40u;
            t.IsTrue((_mm_getcsr()&control)==(before&control),"Submit conserva redondeo, mascaras y FTZ/DAZ del llamador");
            _mm_setcsr(restore.csr & ~_MM_ROUND_MASK);
            std::vector<uint8_t> out;backend->SnapshotVram(out);return out;
        };
        for(unsigned fixture=0;fixture<3;++fixture) {
            const auto expected=render(_MM_ROUND_NEAREST,fixture);
            for(unsigned mode:{_MM_ROUND_NEAREST,_MM_ROUND_TOWARD_ZERO,_MM_ROUND_UP,_MM_ROUND_DOWN})
                t.IsTrue(render(mode,fixture)==expected,"Gradiente/UV/STQ conserva VRAM con cualquier redondeo SSE del productor");
        }
    }

    // GOW-Port: conservar los bits de profundidad al convertir areas grandes en pesos.
    void gpuTrianglePrecision(TestCase &t, bool hardware)
    {
        struct Restore {unsigned csr=_mm_getcsr();~Restore(){_mm_setcsr(csr);}} restore;
        _mm_setcsr(restore.csr & ~_MM_ROUND_MASK);
        std::vector<uint8_t> cpuVram(GSSwizzle::kMemorySize), gpuVram(cpuVram.size());
        GSCpuBackend cpu; cpu.Initialize(cpuVram.data(),uint32_t(cpuVram.size()));
        auto gpu=std::make_unique<GSGpuBackend>();auto *raw=gpu.get();raw->SetHardwareRasterAllowed(hardware);
        GSThreadedBackend gl(std::move(gpu));gl.Initialize(gpuVram.data(),uint32_t(gpuVram.size()));
        if(dynamic_cast<GSGpuBackend*>(&gl.Inner())!=raw || !raw->IsReady()){t.Fail("OpenGL requerido");return;}
        const std::vector<uint8_t> zeros(64u*64u*4u);
        for(unsigned extent:{3071u,4095u}) for(unsigned offset:{0u,256u})
        for(uint8_t psm:{uint8_t(GS_PSM_Z32),uint8_t(GS_PSM_Z24)}) {
            GSPrimitiveBatch b{}; b.vertexCount=3;b.state.prim.type=GS_PRIM_TRIANGLE;
            auto &c=b.state.context;c.frame.fbw=1;c.scissor={0,63,0,63};
            c.xyoffset={uint16_t(offset*16u),uint16_t(offset*16u)};
            c.zbuf.zbp=32;c.zbuf.psm=psm;c.test=1ull<<17;b.state.colclamp=1;
            b.vertices[1].x=float(extent);b.vertices[2].y=float(extent);
            for(auto &v:b.vertices){v.r=128;v.g=128;v.b=128;v.a=128;v.z=7;}
            b.vertices[1].z=4294967295.0;b.vertices[2].z=2147483647.0;
            GSTransferCommand clear{};clear.direction=0;clear.bitbltbuf.dbp=32u*32u;
            clear.bitbltbuf.dbw=1;clear.bitbltbuf.dpsm=GS_PSM_Z32;clear.trxreg={64,64};
            auto render=[&](GSRasterBackend &backend){
                backend.ClearFramebuffer(c,0);backend.BeginTransfer(clear);backend.UploadImage(zeros.data(),uint32_t(zeros.size()));
                backend.Submit(b);backend.Sync(GSSyncReason::DebugReadback);
                std::vector<uint8_t> out;backend.SnapshotVram(out);return out;
            };
            const auto expected=render(cpu);
            for(unsigned mode:{_MM_ROUND_NEAREST,_MM_ROUND_TOWARD_ZERO,_MM_ROUND_UP,_MM_ROUND_DOWN}) {
                const unsigned before=(restore.csr & ~_MM_ROUND_MASK)|mode;_mm_setcsr(before);
                const auto actual=render(gl);
                const unsigned control=_MM_ROUND_MASK|_MM_MASK_MASK|_MM_FLUSH_ZERO_MASK|0x40u;
                t.IsTrue((_mm_getcsr()&control)==(before&control),"OpenGL conserva los controles SSE del productor");
                _mm_setcsr(restore.csr & ~_MM_ROUND_MASK);
                t.IsTrue(actual==expected,"Z32/Z24 coincide con CPU para areas grandes, XYOFFSET y los cuatro modos SSE");
            }
        }
    }

    struct Recording
    {
        std::vector<int> events;
        std::vector<GSPrimitiveBatch> draws;
        std::vector<uint8_t> uploaded;
        std::thread::id owner, destroyer;
    };
    class Recorder final : public GSRasterBackend
    {
        Recording &r;
    public:
        explicit Recorder(Recording &record) : r(record) {}
        ~Recorder() override { r.destroyer = std::this_thread::get_id(); }
        void Initialize(uint8_t *, uint32_t) override { r.owner = std::this_thread::get_id(); }
        void Reset() override { r.events.push_back(8); }
        void Submit(const GSPrimitiveBatch &b) override { r.events.push_back(3); r.draws.push_back(b); }
        void LoadClut(const GSTex0Reg &, const GSTexClutReg &) override { r.events.push_back(4); }
        void BeginTransfer(const GSTransferCommand &) override { r.events.push_back(1); }
        void UploadImage(const uint8_t *p, uint32_t n) override { r.events.push_back(2); if(n) r.uploaded.insert(r.uploaded.end(),p,p+n); }
        void Flush() override { r.events.push_back(5); }
        void TextureFlush() override { r.events.push_back(6); }
        void Sync(GSSyncReason) override { r.events.push_back(7); }
        PresentationFrame Present(const GSPresentationRequest &) override { r.events.push_back(9); return {}; }
        bool ClearFramebuffer(const GSContext &, uint32_t) override { return true; }
        uint32_t ConsumeLocalToHostBytes(uint8_t *,uint32_t) override { return 0; }
        uint32_t ReadVram(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t) const override { return static_cast<uint32_t>(r.draws.size()); }
        void WriteVram(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t) override {}
        void SnapshotVram(std::vector<uint8_t> &out) const override { out = r.uploaded; }
        GSTransferSnapshot GetTransferSnapshot() const override { return {}; }
    };
    // GOW-Port: un pixel de 24 bits puede atravesar el limite de un quadword IMAGE.
    void transfer24Fragments(TestCase &t, GSRasterBackend &backend)
    {
        uint8_t bytes[48]; for(uint32_t i=0;i<48u;++i) bytes[i]=uint8_t(i+1u);
        for(const uint8_t format : {uint8_t(GS_PSM_CT24),uint8_t(GS_PSM_Z24)})
        {
            GSTransferCommand cmd{}; cmd.direction=0; cmd.bitbltbuf.dbp=96; cmd.bitbltbuf.dbw=1;
            cmd.bitbltbuf.dpsm=format; cmd.trxreg={16,1};
            const uint32_t rawFormat=format==GS_PSM_CT24 ? GS_PSM_CT32 : GS_PSM_Z32;
            auto clear=[&] {for(uint32_t x=0;x<16u;++x) backend.WriteVram(rawFormat,96,1,x,0,0xa5000000u);};
            clear(); backend.BeginTransfer(cmd); backend.UploadImage(bytes,48);
            std::vector<uint8_t> expected; backend.SnapshotVram(expected);
            for(uint32_t x=0;x<16u;++x) {
                const uint32_t i=x*3u,value=0xa5000000u|bytes[i]|(uint32_t(bytes[i+1u])<<8)|(uint32_t(bytes[i+2u])<<16);
                t.Equals(backend.ReadVram(rawFormat,96,1,x,0),value,"CT24/Z24 conserva el byte alto de VRAM");
            }
            for(uint32_t cut=0;cut<=48u;++cut)
            {
                clear(); backend.BeginTransfer(cmd);
                backend.UploadImage(bytes,cut); backend.UploadImage(bytes+cut,48u-cut);
                std::vector<uint8_t> actual; backend.SnapshotVram(actual);
                const auto s=backend.GetTransferSnapshot();
                if(actual!=expected || s.direction!=3u || s.copiedPixels!=16u) {
                    t.Fail("Pixel perdido entre cargas: PSM="+std::to_string(format)+" corte="+std::to_string(cut)+
                           " copiados="+std::to_string(s.copiedPixels)); return;
                }
            }
            for(const uint32_t chunk : {1u,16u})
            {
                clear(); backend.BeginTransfer(cmd);
                for(uint32_t offset=0;offset<48u;offset+=chunk) backend.UploadImage(bytes+offset,chunk);
                std::vector<uint8_t> actual; backend.SnapshotVram(actual);
                t.IsTrue(actual==expected && backend.GetTransferSnapshot().copiedPixels==16u,
                         "Cargas repetidas de un byte o un quadword conservan todos los pixels");
            }
        }
    }
    void transfer24Reset(TestCase &t, GSRasterBackend &backend)
    {
        for(const bool reset : {false,true}) for(const uint32_t partial : {1u,2u})
        {
            GSTransferCommand cmd{}; cmd.direction=0; cmd.bitbltbuf.dbp=96; cmd.bitbltbuf.dbw=1;
            cmd.bitbltbuf.dpsm=GS_PSM_CT24; cmd.trxreg={1,1};
            const uint8_t old[]={0x11,0x22},fresh[]={0x33,0x44,0x55};
            backend.BeginTransfer(cmd); backend.UploadImage(old,partial);
            if(reset) backend.Reset();
            backend.BeginTransfer(cmd); backend.UploadImage(fresh,3);
            t.Equals(backend.ReadVram(GS_PSM_CT24,96,1,0,0),0x554433u,
                     "Reset y nueva transferencia descartan bytes de la carga anterior");
        }
    }
    GSPrimitiveBatch sprite()
    {
        GSPrimitiveBatch b{};
        b.vertexCount = 2;
        b.state.prim.type = GS_PRIM_SPRITE;
        b.state.context.frame.fbw = 1;
        b.state.context.scissor = {0,63,0,63};
        b.state.context.zbuf.zbp = 32;
        b.state.context.zbuf.zmask = true;
        b.state.context.test = 1ull << 17; // ZTST=ALWAYS, igual que las pruebas GS existentes.
        b.state.colclamp = 1;
        b.vertices[0].x = 4; b.vertices[0].y = 6;
        b.vertices[1].x = 12; b.vertices[1].y = 14;
        for(auto &v : b.vertices) { v.r = 25; v.g = 51; v.b = 99; v.a = 128; v.z = 7; }
        return b;
    }
    // GOW-Port: manual GS 2.4.4/3.2.9: centro entero y lados superior/izquierdo incluidos.
    void triangleSampling(TestCase &t, GSRasterBackend &backend, unsigned fixture)
    {
        auto draw=sprite(); draw.vertexCount=3; draw.state.prim.type=GS_PRIM_TRIANGLE;
        draw.vertices[0].x=20;draw.vertices[0].y=20;
        draw.vertices[1].x=36;draw.vertices[1].y=20;
        draw.vertices[2].x=20;draw.vertices[2].y=36;
        if(fixture==0u) {
            backend.ClearFramebuffer(draw.state.context,0);
            draw.state.prim.iip=true; draw.vertices[0].r=128;draw.vertices[1].g=128;draw.vertices[2].b=128;
            backend.Submit(draw);
            t.Equals(backend.ReadVram(0,0,1,24,24),0x806a464cu,
                     "Pesos GS en (24,24): 1/2,1/4,1/4; no desplazar medio pixel");
        } else if(fixture==1u) {
            for(const uint16_t offset : {uint16_t(4),uint16_t(12)}) {
                backend.ClearFramebuffer(draw.state.context,0x80332211u);
                draw.state.context.xyoffset.ofx=offset; draw.state.context.xyoffset.ofy=offset;
                for(unsigned i=0;i<3u;++i) {draw.vertices[i].x=(i==1u ? 36.5f:20.5f);draw.vertices[i].y=(i==2u ? 36.5f:20.5f);}
                backend.Submit(draw); const uint32_t start=offset==4u ? 21u:20u;
                t.Equals(backend.ReadVram(0,0,1,start-1u,start-1u),0x80332211u,"Conservar XYOFFSET fraccional y excluir el centro exterior");
                t.Equals(backend.ReadVram(0,0,1,start,start),0x80633319u,"Incluir el primer centro entero dentro del triangulo");
            }
        } else {
            draw.state.prim.abe=true; draw.state.context.alpha=(1ull<<2)|(1ull<<6);
            for(auto &v : draw.vertices) {v.r=128;v.g=128;v.b=128;v.a=64;}
            for(const bool reverse : {false,true}) {
                backend.ClearFramebuffer(draw.state.context,0);
                auto first=draw,second=draw;
                second.vertices[0].x=36;second.vertices[0].y=20;
                second.vertices[1].x=36;second.vertices[1].y=36;
                second.vertices[2].x=20;second.vertices[2].y=36;
                if(reverse) {std::swap(first.vertices[0],first.vertices[2]);std::swap(second.vertices[0],second.vertices[2]);}
                backend.Submit(first);backend.Submit(second);
                for(uint32_t y=20;y<36u;++y) for(uint32_t x=20;x<36u;++x)
                    if(backend.ReadVram(0,0,1,x,y)!=0x40404040u) {
                        t.Fail("Lado compartido se dibuja exactamente una vez, sin huecos: x="+std::to_string(x)+" y="+std::to_string(y));return;
                    }
            }
        }
    }
    // GOW-Port: GS 3.2.9 y ejes firmados de sotc-port ac9efa070638ad3b3accd284de6f898d5ab271d1.
    void spriteSampling(TestCase &t, GSRasterBackend &backend, unsigned fixture)
    {
        auto draw=sprite();
        draw.vertices[0].x=20;draw.vertices[0].y=20;
        draw.vertices[1].x=28;draw.vertices[1].y=28;
        if(fixture==0u) {
            for(const uint16_t extra : {uint16_t(0),uint16_t(16)}) {
                draw.state.context.xyoffset.ofx=4+extra;draw.state.context.xyoffset.ofy=12+extra;
                draw.vertices[0].x=20.5f;draw.vertices[0].y=20.5f;
                draw.vertices[1].x=28.5f;draw.vertices[1].y=28.5f;
                for(const bool reverse : {false,true}) {
                    backend.ClearFramebuffer(draw.state.context,0x80332211u);
                    auto submitted=draw;
                    if(reverse) std::swap(submitted.vertices[0],submitted.vertices[1]);
                    backend.Submit(submitted);
                    const uint32_t firstX=extra ? 20u:21u,firstY=extra ? 19u:20u;
                    for(uint32_t y=18;y<=30u;++y) for(uint32_t x=18;x<=30u;++x) {
                        const uint32_t expected=x>=firstX&&x<firstX+8u&&y>=firstY&&y<firstY+8u ? 0x80633319u:0x80332211u;
                        if(backend.ReadVram(0,0,1,x,y)!=expected) {
                            t.Fail("Cobertura fraccional de sprite: x="+std::to_string(x)+" y="+std::to_string(y));return;
                        }
                    }
                }
            }
        } else if(fixture==1u) {
            for(unsigned axis=0;axis<2u;++axis) {
                backend.ClearFramebuffer(draw.state.context,0x80332211u);
                std::vector<uint8_t> before,after;backend.SnapshotVram(before);
                auto empty=draw;
                if(axis==0u) empty.vertices[1].x=empty.vertices[0].x;
                else empty.vertices[1].y=empty.vertices[0].y;
                backend.Submit(empty);backend.SnapshotVram(after);
                t.IsTrue(before==after,"Ancho o alto cero no modifica VRAM");
            }
        } else {
            draw.state.prim.tme=true;draw.state.prim.fst=true;
            draw.state.context.tex0.tbp0=256;draw.state.context.tex0.tbw=1;
            draw.state.context.tex0.tfx=1;draw.state.context.tex0.tcc=1;
            draw.state.textureWidth=8;draw.state.textureHeight=8;
            for(uint32_t y=0;y<8u;++y) for(uint32_t x=0;x<8u;++x)
                backend.WriteVram(0,256,1,x,y,0x80000000u|x*29u|((y*29u)<<8));
            if(fixture==2u) {
                draw.state.context.tex1=(1ull<<5)|(1ull<<6);
                draw.state.linearFilter=true;
                for(auto &v:draw.vertices) {v.u=12;v.v=12;v.s=0.75f/8;v.t=0.75f/8;v.q=1;}
                for(const bool fst : {true,false}) {
                    draw.state.prim.fst=fst;
                    backend.ClearFramebuffer(draw.state.context,0x80332211u);backend.Submit(draw);
                    t.Equals(backend.ReadVram(0,0,1,24,24),0x80000707u,
                             "UV=0.75: pesos lineales 3/4 y 1/4 conservan la fraccion");
                }
            } else {
                draw.vertices[1].u=128;draw.vertices[1].v=128;
                for(unsigned reverse=0;reverse<4u;++reverse) {
                    backend.ClearFramebuffer(draw.state.context,0x80332211u);
                    auto submitted=draw;
                    if(reverse&1u) {std::swap(submitted.vertices[0].x,submitted.vertices[1].x);std::swap(submitted.vertices[0].u,submitted.vertices[1].u);}
                    if(reverse&2u) {std::swap(submitted.vertices[0].y,submitted.vertices[1].y);std::swap(submitted.vertices[0].v,submitted.vertices[1].v);}
                    // El scissor recorta la cobertura, no el origen de interpolacion.
                    submitted.state.context.scissor={22,26,21,25};
                    backend.Submit(submitted);
                    for(uint32_t y=20;y<28u;++y) for(uint32_t x=20;x<28u;++x) {
                        const uint32_t expected=x>=22u&&x<=26u&&y>=21u&&y<=25u
                                                   ? 0x80000000u|((x-20u)*29u)|(((y-20u)*29u)<<8):0x80332211u;
                        if(backend.ReadVram(0,0,1,x,y)!=expected) {
                            t.Fail("Sprite invertido/recortado conserva texels: x="+std::to_string(x)+" y="+std::to_string(y));return;
                        }
                    }
                }
            }
        }
    }

    // GOW-Port: atributos constantes no cambian con pesos baricentricos redondeados.
    void triangleConstants(TestCase &t,GSRasterBackend &backend,bool fog)
    {
        auto draw=sprite();draw.vertexCount=3;draw.state.prim.type=GS_PRIM_TRIANGLE;
        draw.state.prim.iip=!fog;draw.state.prim.fge=fog;
        // Alpha 128 debe pasar GEQUAL 128 en todo el triangulo, sin huecos de alpha 127.
        if(!fog)draw.state.context.test|=1ull|(5ull<<1)|(128ull<<4);
        draw.vertices[0].x=20;draw.vertices[0].y=20;
        draw.vertices[1].x=37;draw.vertices[1].y=20;
        draw.vertices[2].x=20;draw.vertices[2].y=39;
        for(auto &v:draw.vertices){v.r=255;v.g=127;v.b=63;v.a=128;v.fog=255;v.z=7;}
        auto point=draw;point.vertexCount=1;point.state.prim.type=GS_PRIM_POINT;
        point.vertices[0].x=24;point.vertices[0].y=24;
        backend.ClearFramebuffer(draw.state.context,0x80332211u);backend.Submit(point);
        const uint32_t expected=backend.ReadVram(0,0,1,24,24);
        if(!fog)t.Equals(expected,0x803f7fffu,"Control sin interpolacion conserva RGBA exacto");
        for(const bool reverse : {false,true}) {
            backend.ClearFramebuffer(draw.state.context,0x80332211u);
            auto submitted=draw;if(reverse)std::swap(submitted.vertices[0],submitted.vertices[2]);
            backend.Submit(submitted);
            for(uint32_t y=20;y<39u;++y)for(uint32_t x=20;x<37u;++x){
                if((x-20u)*19u+(y-20u)*17u>=323u)continue;
                const uint32_t actual=backend.ReadVram(0,0,1,x,y);
                if(actual!=expected){
                    t.Fail(std::string(fog?"FOG constante":"RGBA constante")+" difiere del control: x="+
                           std::to_string(x)+" y="+std::to_string(y)+" valor="+std::to_string(actual));return;
                }
            }
        }
    }

    // GOW-Port: UV/STQ constantes deben seleccionar el mismo texel que un sprite 1x1.
    void triangleTextureConstants(TestCase &t,GSRasterBackend &backend,bool fst)
    {
        auto draw=sprite();draw.vertexCount=3;draw.state.prim.type=GS_PRIM_TRIANGLE;
        draw.state.prim.tme=true;draw.state.prim.fst=fst;
        draw.state.context.tex0.tbp0=256;draw.state.context.tex0.tbw=1;
        draw.state.context.tex0.tfx=1;draw.state.context.tex0.tcc=1;
        draw.state.textureWidth=8;draw.state.textureHeight=8;
        draw.vertices[0].x=20;draw.vertices[0].y=20;
        draw.vertices[1].x=37;draw.vertices[1].y=20;
        draw.vertices[2].x=20;draw.vertices[2].y=39;
        for(auto &v:draw.vertices){v.u=32;v.v=48;v.q=1.5f;v.s=.375f;v.t=.5625f;}
        for(uint32_t y=0;y<8u;++y)for(uint32_t x=0;x<8u;++x)
            backend.WriteVram(0,256,1,x,y,0x80000000u|(x*29u)|((y*29u)<<8));
        for(const bool linear:{false,true})for(const bool reverse:{false,true}){
            auto submitted=draw;submitted.state.linearFilter=linear;
            submitted.state.context.tex1=linear?((1ull<<5)|(1ull<<6)):0;
            if(reverse)std::swap(submitted.vertices[0],submitted.vertices[2]);
            auto control=submitted;control.vertexCount=2;control.state.prim.type=GS_PRIM_SPRITE;
            control.vertices[0].x=24;control.vertices[0].y=24;
            control.vertices[1].x=25;control.vertices[1].y=25;
            backend.ClearFramebuffer(draw.state.context,0x80332211u);backend.Submit(control);
            const uint32_t expected=backend.ReadVram(0,0,1,24,24);
            t.Equals(expected,linear?0x8000492cu:0x8000573au,"Control texturizado exacto");
            backend.ClearFramebuffer(draw.state.context,0x80332211u);backend.Submit(submitted);
            for(uint32_t y=20;y<39u;++y)for(uint32_t x=20;x<37u;++x){
                if((x-20u)*19u+(y-20u)*17u>=323u)continue;
                if(backend.ReadVram(0,0,1,x,y)!=expected){
                    t.Fail(std::string(fst?"UV":"STQ")+" constante selecciona otro texel: x="+
                           std::to_string(x)+" y="+std::to_string(y));return;
                }
            }
        }
        // Conservar gradientes descendentes y Q variable; centros lejos de fronteras de texel.
        auto gradient=draw;
        gradient.vertices[0].u=116;gradient.vertices[0].v=20;
        gradient.vertices[1].u=20;gradient.vertices[1].v=20;
        gradient.vertices[2].u=116;gradient.vertices[2].v=100;
        for(unsigned i=0;i<3u;++i){auto &v=gradient.vertices[i];v.q=float(i+1u);
            v.s=float(v.u)*v.q/128.0f;v.t=float(v.v)*v.q/128.0f;}
        backend.ClearFramebuffer(draw.state.context,0x80332211u);backend.Submit(gradient);
        t.Equals(backend.ReadVram(0,0,1,24,24),fst?0x80003a91u:0x80005791u,
                 "Gradiente mantiene UV firmadas y division por Q despues de interpolar");
    }


    void transferRoundtrip(TestCase &t, GSRasterBackend &b)
    {
        GSTransferCommand c{};
        c.direction = 0; c.bitbltbuf.dbp = 96; c.bitbltbuf.dbw = 1;
        c.trxreg = {3,2}; c.trxpos.dsax = 63; c.trxpos.dsay = 31;
        const uint32_t pixels[] = {0x80112233,0x80445566,0x80778899,0x80aabbcc,0x80123456,0x80654321};
        b.BeginTransfer(c);
        b.UploadImage(reinterpret_cast<const uint8_t *>(pixels), 8);
        b.UploadImage(reinterpret_cast<const uint8_t *>(pixels)+8, sizeof(pixels)-8);
        // Cruza páginas y paquetes sin alterar el orden de bytes.
        t.Equals(b.ReadVram(0,96,1,65,32),pixels[5],"Último píxel de la subida partida");
        c.direction = 1; c.bitbltbuf.sbp = 96; c.bitbltbuf.sbw = 1;
        c.trxpos.ssax = 63; c.trxpos.ssay = 31;
        b.BeginTransfer(c);
        uint8_t result[sizeof(pixels)]{};
        t.Equals(b.ConsumeLocalToHostBytes(result,5),5u,"Primera lectura parcial");
        t.Equals(b.ConsumeLocalToHostBytes(result+5,sizeof(result)-5),sizeof(result)-5,"Segunda lectura parcial");
        t.IsTrue(std::memcmp(result,pixels,sizeof(pixels))==0,"Transferencia host/local/host exacta");
    }
    void gpuComparison(TestCase &t, bool hardware)
    {
        std::vector<uint8_t> cpuRam(GSSwizzle::kMemorySize), gpuRam(GSSwizzle::kMemorySize);
        GSCpuBackend cpu;
        cpu.Initialize(cpuRam.data(),static_cast<uint32_t>(cpuRam.size()));
        auto gpu = std::make_unique<GSGpuBackend>();
        gpu->SetHardwareRasterAllowed(hardware);
        auto *raw = gpu.get();
        GSThreadedBackend threaded(std::move(gpu));
        threaded.Initialize(gpuRam.data(),static_cast<uint32_t>(gpuRam.size()));
        // No contar el fallback CPU como validación de OpenGL.
        if (dynamic_cast<GSGpuBackend *>(&threaded.Inner()) != raw) { t.Fail("OpenGL no pudo inicializarse"); return; }
        t.IsTrue(raw->IsReady(),"Contexto y shaders OpenGL disponibles");
        transferRoundtrip(t,threaded);
        transferRoundtrip(t,cpu);
        auto draw = sprite();
        for(auto *b : {static_cast<GSRasterBackend *>(&cpu),static_cast<GSRasterBackend *>(&threaded)})
        {
            t.IsTrue(b->ClearFramebuffer(draw.state.context,0x80332211),"Clear CT32");
            b->Submit(draw);
            b->Sync(GSSyncReason::Finish);
            const auto color=b->ReadVram(0,0,1,5,7);
            t.Equals(color,0x80633319u,"Color sintético del sprite: "+std::to_string(color));
            // Imagen local a local, seguida de dibujo con máscara de canal.
            GSTransferCommand copy{};
            copy.direction=2; copy.bitbltbuf.sbw=1; copy.bitbltbuf.dbw=1; copy.bitbltbuf.dbp=192;
            copy.trxreg={16,16};
            b->BeginTransfer(copy);
        }
        std::vector<uint8_t> expected, actual;
        cpu.SnapshotVram(expected); threaded.SnapshotVram(actual);
        t.IsTrue(expected == actual,"VRAM completa CPU/OpenGL: clear, sprite, transferencias");
        for(auto *backend : {static_cast<GSRasterBackend *>(&cpu),static_cast<GSRasterBackend *>(&threaded)})
        {
            auto tri=sprite(); tri.vertexCount=3; tri.state.prim.type=GS_PRIM_TRIANGLE;
            tri.vertices[0].x=20; tri.vertices[0].y=20;
            tri.vertices[1].x=36; tri.vertices[1].y=20;
            tri.vertices[2].x=20; tri.vertices[2].y=36;
            backend->Submit(tri);
            t.Equals(backend->ReadVram(0,0,1,24,24),0x80633319u,"Interior del triángulo plano");
            t.Equals(backend->ReadVram(0,0,1,40,40),0x80332211u,"Exterior del triángulo plano");
            auto tex=sprite(); tex.state.prim.tme=true; tex.state.prim.fst=true;
            tex.state.context.tex0.tbp0=256; tex.state.context.tex0.tbw=1;
            tex.state.context.tex0.tfx=1; tex.state.context.tex0.tcc=1; // DECAL RGBA
            tex.state.textureWidth=2; tex.state.textureHeight=2;
            tex.vertices[0].x=40; tex.vertices[0].y=20;
            tex.vertices[1].x=42; tex.vertices[1].y=22;
            tex.vertices[1].u=32; tex.vertices[1].v=32;
            for(uint32_t y=0;y<2;++y) for(uint32_t x=0;x<2;++x)
                backend->WriteVram(0,256,1,x,y,0x80112233u+x+y*2);
            backend->Submit(tex);
            t.Equals(backend->ReadVram(0,0,1,41,21),0x80112236u,"Sprite texturado CT32 1:1");
        }
        // CRTC básico sin la heurística específica de GoW del renderer CPU.
        GSPresentationRequest req{}; req.pmode=1; req.dispfb1=1ull<<9;
        req.display1=(63ull<<32)|(63ull<<44);
        auto a=cpu.Present(req), b=threaded.Present(req);
        t.Equals(b.width,a.width,"Ancho de presentación");
        t.Equals(b.height,a.height,"Alto de presentación");
        const size_t shown=static_cast<size_t>(640u)*a.height*4u;
        // El CPU reserva hasta la altura máxima; comparar todas las filas presentadas.
        if(a.pixels.size()<shown || b.pixels.size()<shown || !std::equal(a.pixels.begin(),a.pixels.begin()+shown,b.pixels.begin()))
        {
            size_t i=0; while(i<a.pixels.size() && i<b.pixels.size() && a.pixels[i]==b.pixels[i]) ++i;
            t.Fail("Presentación diferente en byte "+std::to_string(i)+": CPU="+std::to_string(i<a.pixels.size()?a.pixels[i]:-1)+", GPU="+std::to_string(i<b.pixels.size()?b.pixels[i]:-1));
        }
        // GOW-Port: fuente de textura en bloques de 256 B, distinta del CRTC en páginas.
        // Base no alineada a 8 KB, otro stride y origen CRTC no nulo: no convertir por división.
        req.dispfb1=32ull|(1ull<<9)|(7ull<<32)|(9ull<<43);
        req.hasPreferredSource=true; req.preferredDestFbp=32;
        req.preferredSource={1057,2,GS_PSM_CT32,0};
        auto comparePresentation=[&](const char *message) {
            const auto ref=cpu.Present(req), got=threaded.Present(req);
            t.Equals(got.usedPreferred,ref.usedPreferred,"Selección de fuente");
            t.Equals(got.displayFbp,ref.displayFbp,"Destino en páginas");
            t.Equals(got.sourceFbp,ref.sourceFbp,"Fuente sin perder bits del bloque");
            t.Equals(got.width,ref.width,"Ancho de fuente preferida");
            t.Equals(got.height,ref.height,"Alto de fuente preferida");
            const size_t bytes=static_cast<size_t>(640)*ref.height*4;
            t.IsTrue(ref.pixels.size()>=bytes && got.pixels.size()>=bytes &&
                     std::equal(ref.pixels.begin(),ref.pixels.begin()+bytes,got.pixels.begin()),message);
            return got;
        };
        GSContext display{}; display.frame={32,1,GS_PSM_CT32,0}; display.scissor={0,63,0,63};
        for(auto *backend : {static_cast<GSRasterBackend *>(&cpu),static_cast<GSRasterBackend *>(&threaded)})
            backend->ClearFramebuffer(display,0x80332211);
        for(const auto psm : {GS_PSM_CT32,GS_PSM_CT24,GS_PSM_CT16,GS_PSM_CT16S})
        {
            req.preferredSource.psm=psm;
            std::vector<uint8_t> pixels;
            for(uint32_t y=0;y<64;++y) for(uint32_t x=0;x<64;++x)
            {
                const uint32_t color=(psm==GS_PSM_CT16 || psm==GS_PSM_CT16S)
                    ? 0x8000u|(x&31u)|((y&31u)<<5u)|(((x+y)&31u)<<10u)
                    : 0x80000000u|(x*3u)|((y*3u)<<8u)|(((x+y)&127u)<<16u);
                const unsigned count=psm==GS_PSM_CT24?3u:(psm==GS_PSM_CT32?4u:2u);
                for(unsigned i=0;i<count;++i) pixels.push_back(static_cast<uint8_t>(color>>(i*8u)));
            }
            GSTransferCommand upload{}; upload.direction=0; upload.bitbltbuf.dbp=1057;
            upload.bitbltbuf.dbw=2; upload.bitbltbuf.dpsm=psm; upload.trxreg={64,64};
            for(auto *backend : {static_cast<GSRasterBackend *>(&cpu),static_cast<GSRasterBackend *>(&threaded)})
            {
                backend->BeginTransfer(upload);
                backend->UploadImage(pixels.data(),static_cast<uint32_t>(pixels.size()));
            }
            auto first=comparePresentation("Píxeles CPU/OpenGL de la fuente preferida");
            for(auto *backend : {static_cast<GSRasterBackend *>(&cpu),static_cast<GSRasterBackend *>(&threaded)})
                // Color sin alfa también debe verse con un único circuito activo.
                backend->WriteVram(psm,1057,2,0,0,0x00001234u);
            auto next=comparePresentation("Se presenta la actualización posterior de la fuente");
            t.IsTrue(first.pixels!=next.pixels,"La presentación cambia con la fuente");
        }
        req.preferredSource.psm=GS_PSM_CT32;
        req.preferredDestFbp=31; comparePresentation("Destino distinto mantiene CRTC");
        req.preferredDestFbp=32; req.hasPreferredSource=false;
        comparePresentation("Sin fuente preferida mantiene CRTC");
        req.hasPreferredSource=true; req.preferredSource.psm=GS_PSM_T8;
        comparePresentation("Formato de framebuffer no soportado mantiene CRTC");
        req.preferredSource.psm=GS_PSM_CT32; req.pmode=3;
        req.dispfb2=req.dispfb1; req.display2=req.display1;
        comparePresentation("Dos circuitos conservan la composición CRTC");
        // GOW-Port: modo de campos entrelazados usado por GoW (SMODE2=0x401).
        // La misma VRAM debe producir campos par e impar distintos, iguales al CPU.
        req.hasPreferredSource=false; req.pmode=0x8023; req.smode2=0x401;
        req.dispfb2=32ull|(1ull<<9)|(1ull<<15);
        req.dispfb1=req.dispfb2|(1ull<<43);
        req.display1=(63ull<<32)|(64ull<<44); req.display2=(63ull<<32)|(65ull<<44);
        std::vector<uint8_t> fieldPixels;
        for(uint32_t y=0;y<66;++y) for(uint32_t x=0;x<64;++x)
        {fieldPixels.push_back(static_cast<uint8_t>(x*3));fieldPixels.push_back(static_cast<uint8_t>(y*3));fieldPixels.push_back(static_cast<uint8_t>((x+y)*2));}
        GSTransferCommand fieldUpload{}; fieldUpload.direction=0; fieldUpload.bitbltbuf.dbp=1024;
        fieldUpload.bitbltbuf.dbw=1; fieldUpload.bitbltbuf.dpsm=GS_PSM_CT24; fieldUpload.trxreg={64,66};
        for(auto *backend : {static_cast<GSRasterBackend *>(&cpu),static_cast<GSRasterBackend *>(&threaded)})
        {backend->BeginTransfer(fieldUpload);backend->UploadImage(fieldPixels.data(),static_cast<uint32_t>(fieldPixels.size()));}
        req.vsyncTick=0; const auto even=comparePresentation("Campo par coincide con el CPU");
        req.vsyncTick=1; const auto odd=comparePresentation("Campo impar coincide con el CPU");
        t.IsTrue(even.pixels!=odd.pixels,"Se alternan los campos sin cambiar VRAM");
        req.smode2=0; req.vsyncTick=2; const auto progressive=comparePresentation("Modo progresivo coincide con el CPU");
        req.vsyncTick=3; const auto same=comparePresentation("Modo progresivo no depende de la paridad");
        t.IsTrue(progressive.pixels==same.pixels,"Sin entrelazado no se fuerza alternancia");
        // GOW-Port: temporización completa observada en GoW, con patrón sintético sin assets.
        req.pmode=0x8023; req.smode2=0x401;
        req.dispfb1=0x800000090d0ull; req.dispfb2=0x90d0ull;
        req.display1=0x1be9ff0203227cull; req.display2=0x1bf9ff0203227cull;
        fieldPixels.clear();
        for(uint32_t y=0;y<448;++y) for(uint32_t x=0;x<512;++x)
        {fieldPixels.push_back(static_cast<uint8_t>(x));fieldPixels.push_back(static_cast<uint8_t>(y*3));fieldPixels.push_back(static_cast<uint8_t>(x+y));}
        fieldUpload.bitbltbuf.dbp=0xd0u*32u; fieldUpload.bitbltbuf.dbw=8; fieldUpload.trxreg={512,448};
        for(auto *backend : {static_cast<GSRasterBackend *>(&cpu),static_cast<GSRasterBackend *>(&threaded)})
        {backend->BeginTransfer(fieldUpload);backend->UploadImage(fieldPixels.data(),static_cast<uint32_t>(fieldPixels.size()));}
        req.vsyncTick=0; const auto realEven=comparePresentation("Temporización GoW: campo par exacto");
        req.vsyncTick=1; const auto realOdd=comparePresentation("Temporización GoW: campo impar exacto");
        t.IsTrue(realEven.pixels!=realOdd.pixels,"Temporización GoW alterna sus campos");
    }
}

void register_ps2_gs_backend_tests()
{
    MiniTest::Case("GOW GS backends", [](TestCase &t) {
        t.Run("CPU drawing is independent of caller SSE rounding",[](TestCase &t) {cpuRoundingIndependent(t,false);});
        t.Run("Threaded CPU drawing is independent of producer SSE rounding",[](TestCase &t) {cpuRoundingIndependent(t,true);});

        // GOW-Port: PACKED XYZ conserva Z32 incluso por encima de la precision float.
        t.Run("PACKED XYZ2 writes every depth bit through native and fragmented paths",[](TestCase &t){
            for(bool native:{false,true}) for(uint32_t z:{0x01000001u,0x80000001u,0xffffff01u,0xffffffffu})
            for(uint32_t cut=0;cut<=(native?0u:32u);++cut) {
                std::vector<uint8_t> bytes(GSSwizzle::kMemorySize);GS gs;gs.init(bytes.data(),uint32_t(bytes.size()));
                gs.setRasterBackend(std::make_unique<GSCpuBackend>());
                gs.writeRegister(GS_REG_FRAME_1,1ull<<16);gs.writeRegister(GS_REG_SCISSOR_1,63ull<<16|63ull<<48);
                gs.writeRegister(GS_REG_ZBUF_1,32);gs.writeRegister(GS_REG_TEST_1,1ull<<17);gs.writeRegister(GS_REG_RGBAQ,0x80332211u);
                const uint64_t packet[]={1ull|(1ull<<15)|(1ull<<46)|(1ull<<60),5ull,0x0000001000000010ull,z};
                const auto *data=reinterpret_cast<const uint8_t*>(packet);
                if(native) t.IsTrue(gs.processNativePackedGIFPacket(data,sizeof(packet)),"Ruta nativa consume PACKED");
                else {gs.processGIFPacket(data,cut);gs.processGIFPacket(data+cut,uint32_t(sizeof(packet))-cut);}
                t.Equals(gs.ReadVram(GS_PSM_Z32,32u*32u,1,1,1),z,"El pixel conserva Z32 sin redondeo intermedio a float");
                t.Equals(gs.ReadVram(GS_PSM_CT32,0,1,1,1),0x80332211u,"El punto sigue dibujandose");
            }
        });
        t.Run("PACKED XYZ3 and XYZ2 ADC retain queued depth without a premature draw",[](TestCase &t){
            for(bool native:{false,true}) for(bool xyz3:{false,true}) {
                std::vector<uint8_t> bytes(GSSwizzle::kMemorySize);GS gs;gs.init(bytes.data(),uint32_t(bytes.size()));
                Recording records;gs.setRasterBackend(std::make_unique<Recorder>(records));
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
                const uint64_t depths[]={0xffffffffull,0x80000001ull,0x01000001ull};
                for(uint32_t i=0;i<3u;++i) {
                    const bool suppressed=i<2u;
                    const uint64_t reg=suppressed&&xyz3 ? 0xDull:5ull;
                    const uint64_t adc=suppressed&&!xyz3 ? 1ull<<47:0ull;
                    const uint64_t packet[]={1ull|(1ull<<15)|(1ull<<60),reg,
                                             uint64_t(i*16u)|(uint64_t(i*32u)<<32),depths[i]|adc};
                    const auto *data=reinterpret_cast<const uint8_t*>(packet);
                    if(native)t.IsTrue(gs.processNativePackedGIFPacket(data,sizeof(packet)),"Ruta nativa consume XYZ3/ADC");
                    else gs.processGIFPacket(data,sizeof(packet));
                    t.Equals(records.draws.size(),size_t(i==2u?1u:0u),"Solo el ultimo vertice lanza el triangulo");
                }
                if(records.draws.size()!=1u){t.Fail("Falta el triangulo control");continue;}
                for(uint32_t i=0;i<3u;++i)
                    t.IsTrue(records.draws[0].vertices[i].z==double(depths[i]),"La cola conserva Z32 en XYZ3 y XYZ2 ADC");
            }
        });
        // GOW-Port: exportación CPU adaptada de SotC ac9efa0 para repetir comandos GS.
        t.Run("CPU and threaded CPU restore an incomplete CT24 transfer",[](TestCase &t) {
            for(bool threaded:{false,true}) {
                std::vector<uint8_t> vram(GSSwizzle::kMemorySize),otherVram(vram.size());
                std::unique_ptr<GSRasterBackend> source=std::make_unique<GSCpuBackend>();
                if(threaded) source=std::make_unique<GSThreadedBackend>(std::move(source));
                source->Initialize(vram.data(),uint32_t(vram.size()));
                auto *access=dynamic_cast<GSBackendStateAccess*>(source.get());
                GSBackendState saved;
                if(!access || !access->ExportState(saved)) {t.Fail("CPU debe exportar estado además de VRAM");return;}
                GSTransferCommand transfer{}; transfer.direction=0;
                transfer.bitbltbuf.dbw=1; transfer.bitbltbuf.dpsm=1; transfer.trxreg={2,1};
                source->BeginTransfer(transfer); const uint8_t first[]={0x12,0x34}; source->UploadImage(first,2);
                t.IsTrue(access->ExportState(saved),"Exportar pixel CT24 incompleto");
                t.IsTrue(saved.upload24.size==2,"Conservar ambos bytes pendientes");
                source->SnapshotVram(otherVram);
                GSCpuBackend destination; destination.Initialize(otherVram.data(),uint32_t(otherVram.size()));
                auto *restored=dynamic_cast<GSBackendStateAccess*>(static_cast<GSRasterBackend*>(&destination));
                if(!restored || !restored->ImportState(saved)) {t.Fail("CPU debe importar la transferencia");return;}
                const uint8_t tail[]={0x56,0x78,0x9a,0xbc};
                source->UploadImage(tail,4); destination.UploadImage(tail,4);
                t.IsTrue(destination.ReadVram(0,0,1,0,0)==0x00563412u &&
                         destination.ReadVram(0,0,1,1,0)==0x00bc9a78u,"Pixels exactos tras reanudar");
                std::vector<uint8_t> expected,actual; source->SnapshotVram(expected); destination.SnapshotVram(actual);
                t.IsTrue(expected==actual,"La VRAM completa coincide tras reanudar");
            }
        });
        t.Run("CPU state restores CLUT texture cache and pending readback",[](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend cpu;
            cpu.Initialize(vram.data(),uint32_t(vram.size()));
            auto *access=dynamic_cast<GSBackendStateAccess*>(static_cast<GSRasterBackend*>(&cpu));
            if(!access) {t.Fail("Falta acceso al estado CPU");return;}
            GSBackendState initial; for(unsigned i=0;i<512;++i) initial.clut[i]=uint16_t(i*67u);
            initial.clutCbp={256u,512u}; initial.cachePageBase=256u*256u; // TBP0 en bloques de 256 B.
            const uint32_t cached=0x80654321u; std::memcpy(initial.cacheBytes.data(),&cached,4);
            initial.localToHost={1,2,3,4,5}; initial.localToHostReadPos=1;
            t.IsTrue(access->ImportState(initial),"Importar estado CPU completo");
            GSBackendState roundtrip; t.IsTrue(access->ExportState(roundtrip),"Exportar sin pérdidas");
            t.IsTrue(initial.clut==roundtrip.clut && initial.clutCbp==roundtrip.clutCbp &&
                     initial.cachePageBase==roundtrip.cachePageBase && initial.cacheBytes==roundtrip.cacheBytes,
                     "Paleta y página cacheada exactas");
            uint8_t bytes[2]{}; t.IsTrue(cpu.ConsumeLocalToHostBytes(bytes,2)==2 && bytes[0]==2 && bytes[1]==3,
                                      "Readback continúa en el cursor exportado");
            GSPrimitiveBatch sprite{}; sprite.vertexCount=2; sprite.state.prim.type=GS_PRIM_SPRITE;
            sprite.state.prim.tme=true; sprite.state.prim.fst=true; sprite.state.context.frame.fbw=1;
            sprite.state.context.tex0.tbp0=256; sprite.state.context.tex0.tbw=1;
            sprite.state.context.tex0.tfx=1; sprite.state.context.tex0.tcc=1;
            sprite.state.context.scissor={0,1,0,1}; sprite.state.context.zbuf.zmask=true;
            sprite.state.context.test=1ull<<17; sprite.state.colclamp=1;
            sprite.vertices[1].x=1; sprite.vertices[1].y=1; cpu.Submit(sprite);
            t.IsTrue(cpu.ReadVram(0,0,1,0,0)==cached,"La muestra conserva el texel cacheado del origen");
        });
        t.Run("CPU rejects invalid snapshots without changing its state",[](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend cpu;
            cpu.Initialize(vram.data(),uint32_t(vram.size()));
            auto *access=dynamic_cast<GSBackendStateAccess*>(static_cast<GSRasterBackend*>(&cpu));
            if(!access) {t.Fail("Falta acceso al estado CPU");return;}
            GSBackendState original; original.clut[5]=123; original.localToHost={4,8};
            t.IsTrue(access->ImportState(original),"Estado inicial válido");
            for(unsigned fixture=0;fixture<4;++fixture) {
                auto invalid=original; invalid.clut[5]=999;
                if(fixture==0) invalid.upload24.size=3;
                if(fixture==1) invalid.cachePageBase=1;
                if(fixture==2) invalid.cachePageBase=GSSwizzle::kMemorySize;
                if(fixture==3) invalid.localToHostReadPos=3;
                t.IsTrue(!access->ImportState(invalid),"Rechazar snapshot inválido");
                GSBackendState actual; access->ExportState(actual);
                t.IsTrue(actual.clut==original.clut && actual.localToHost==original.localToHost &&
                         actual.upload24.size==0 && actual.cachePageBase==UINT32_MAX,
                         "Un rechazo no modifica el estado anterior");
            }
        });
        // GOW-Port: continuidad GIF entre envios, incluidos cortes dentro de etiquetas y registros.
        t.Run("PACKED GIF resumes A+D registers across every byte split", [](TestCase &t) {
            const uint64_t packet[]={2ull|(1ull<<15)|(1ull<<46)|(uint64_t(GS_PRIM_SPRITE)<<47)|(1ull<<60),0xeull,
                                     7ull,GS_REG_COLCLAMP,1ull,GS_REG_DTHE};
            const auto *bytes=reinterpret_cast<const uint8_t *>(packet);
            bool complete=true;
            for(uint32_t cut=0;cut<=sizeof(packet);++cut)
            {
                std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
                gs.processGIFPacket(bytes,cut); gs.processGIFPacket(bytes+cut,uint32_t(sizeof(packet))-cut);
                const auto s=gs.getDebugSnapshot();
                complete &= s.colclamp==7u && s.dthe==1u && s.prim.type==GS_PRIM_SPRITE;
            }
            t.IsTrue(complete,"A+D y PRE conservan su significado para todos los cortes, sin nuevas etiquetas ficticias");
        });
        t.Run("PACKED GIF resumes register cursor and ST Q across fragments", [](TestCase &t) {
            const uint64_t packet[]={1ull|(1ull<<15)|(1ull<<46)|(3ull<<60),0x512ull,
                0x402000003fc00000ull,0x40000000ull,
                0x0000002200000011ull,0x0000008000000033ull,
                0x0000001000000010ull,1ull};
            const auto *bytes=reinterpret_cast<const uint8_t *>(packet);
            bool complete=true;
            for(uint32_t cut=0;cut<=sizeof(packet);++cut)
            {
                Recording r; std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
                gs.setRasterBackend(std::make_unique<Recorder>(r));
                gs.processGIFPacket(bytes,cut); gs.processGIFPacket(bytes+cut,uint32_t(sizeof(packet))-cut);
                complete &= r.draws.size()==1u;
                if(r.draws.size()==1u)
                {
                    const auto &v=r.draws[0].vertices[0];
                    complete &= v.s==1.5f && v.t==2.5f && v.q==2.0f && v.r==0x11u && v.g==0x22u && v.b==0x33u;
                }
            }
            t.IsTrue(complete,"El cursor ST/RGBAQ/XYZ y Q sobreviven sin repetir PRE ni reiniciar Q");
        });
        t.Run("REGLIST GIF preserves odd padding and the following tag across fragments", [](TestCase &t) {
            const uint64_t packet[]={1ull|(1ull<<15)|(uint64_t(GIF_FMT_REGLIST)<<58)|(3ull<<60),0x760ull,
                uint64_t(GS_PRIM_TRIANGLE),11ull,22ull,0xffffffffffffffffull,
                1ull|(1ull<<15)|(1ull<<60),0xeull,7ull,GS_REG_COLCLAMP};
            const auto *bytes=reinterpret_cast<const uint8_t *>(packet);
            bool complete=true;
            for(uint32_t cut=0;cut<=sizeof(packet);++cut)
            {
                std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
                gs.processGIFPacket(bytes,cut); gs.processGIFPacket(bytes+cut,uint32_t(sizeof(packet))-cut);
                const auto s=gs.getDebugSnapshot();
                complete &= s.prim.type==GS_PRIM_TRIANGLE && s.ctx[0].tex0.tbp0==11u && s.ctx[1].tex0.tbp0==22u && s.colclamp==7u;
            }
            t.IsTrue(complete,"Los tres registros, su padding de ocho bytes y la etiqueta siguiente permanecen separados");
        });
        t.Run("IMAGE GIF preserves payload bytes and the following tag across fragments", [](TestCase &t) {
            const uint64_t packet[]={2ull|(1ull<<15)|(uint64_t(GIF_FMT_IMAGE)<<58),0ull,
                0x8044556680112233ull,0x80aabbcc80778899ull,0x8033221180665544ull,0x8099887780ccbbaaull,
                1ull|(1ull<<15)|(1ull<<60),0xeull,7ull,GS_REG_COLCLAMP};
            const auto *bytes=reinterpret_cast<const uint8_t *>(packet);
            bool complete=true;
            for(uint32_t cut=0;cut<=sizeof(packet);++cut)
            {
                Recording r; std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
                gs.setRasterBackend(std::make_unique<Recorder>(r));
                gs.writeRegister(GS_REG_BITBLTBUF,(96ull<<32)|(1ull<<48));
                gs.writeRegister(GS_REG_TRXREG,8ull|(1ull<<32)); gs.writeRegister(GS_REG_TRXDIR,0);
                gs.processGIFPacket(bytes,cut); gs.processGIFPacket(bytes+cut,uint32_t(sizeof(packet))-cut);
                complete &= r.uploaded.size()==32u && gs.getDebugSnapshot().colclamp==7u;
                if(r.uploaded.size()==32u) complete &= std::memcmp(r.uploaded.data(),bytes+16u,32u)==0;
            }
            t.IsTrue(complete,"IMAGE no interpreta el siguiente fragmento de pixeles como otra etiqueta");
        });
        // GOW-Port: FLG=3 se transfiere como IMAGE2, sin tratar sus pixels como etiquetas.
        t.Run("IMAGE2 retains bytes PRE and the following tag across all fragments", [](TestCase &t) {
            const uint64_t packet[]={2ull|(1ull<<15)|(1ull<<46)|(uint64_t(GS_PRIM_SPRITE)<<47)|(3ull<<58),0ull,
                0x8044556680112233ull,0x80aabbcc80778899ull,0x8033221180665544ull,0x8099887780ccbbaaull,
                1ull|(1ull<<15)|(1ull<<60),0xeull,7ull,GS_REG_COLCLAMP};
            const auto *bytes=reinterpret_cast<const uint8_t *>(packet);
            bool complete=true;
            for(uint32_t cut=0;cut<=sizeof(packet);++cut)
            {
                Recording r; std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
                gs.setRasterBackend(std::make_unique<Recorder>(r));
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
                gs.writeRegister(GS_REG_BITBLTBUF,(96ull<<32)|(1ull<<48));
                gs.writeRegister(GS_REG_TRXREG,8ull|(1ull<<32)); gs.writeRegister(GS_REG_TRXDIR,0);
                gs.processGIFPacket(bytes,cut,GifPathId::Path3);
                gs.processGIFPacket(bytes+cut,uint32_t(sizeof(packet))-cut,GifPathId::Path3);
                const auto s=gs.getDebugSnapshot();
                complete &= r.uploaded.size()==32u && s.colclamp==7u && s.prim.type==GS_PRIM_TRIANGLE &&
                            !gs.hasPendingGIFPacket(GifPathId::Path3);
                if(r.uploaded.size()==32u) complete &= std::memcmp(r.uploaded.data(),bytes+16u,32u)==0;
            }
            t.IsTrue(complete,"IMAGE2 conserva pixels, ignora PRE y llega a la etiqueta siguiente en todos los cortes");
        });
        t.Run("native IMAGE2 upload preserves CPU pixels and setup PRE", [](TestCase &t) {
            for(const bool recorder : {false,true})
            {
                Recording r; std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
                if(recorder) gs.setRasterBackend(std::make_unique<Recorder>(r));
                const uint64_t packet[]={4ull|(1ull<<60)|(1ull<<46)|(uint64_t(GS_PRIM_SPRITE)<<47),0xeull,
                    (96ull<<32)|(1ull<<48),GS_REG_BITBLTBUF,
                    0ull,GS_REG_TRXPOS,4ull|(1ull<<32),GS_REG_TRXREG,0ull,GS_REG_TRXDIR,
                    1ull|(1ull<<15)|(1ull<<46)|(3ull<<58),0ull,
                    0x8044556680112233ull,0x80aabbcc80778899ull};
                gs.processGIFPacket(reinterpret_cast<const uint8_t *>(packet),sizeof(packet),GifPathId::Path3);
                t.Equals(gs.nativeImageUploadCount(),uint64_t(1),"IMAGE2 usa el atajo completo validado");
                t.Equals(gs.getDebugSnapshot().prim.type,uint8_t(GS_PRIM_SPRITE),"PRE del setup aplica; PRE de IMAGE2 no");
                if(recorder)
                    t.IsTrue(r.uploaded.size()==16u && std::memcmp(r.uploaded.data(),packet+12,16)==0,
                             "El backend recibe los pixels originales");
                else
                    for(uint32_t x=0;x<4u;++x)
                        t.Equals(GSMem::ReadCT32(vram.data(),96u,1u,x,0u),reinterpret_cast<const uint32_t *>(packet+12)[x],
                                 "El renderer CPU conserva cada pixel IMAGE2");
            }
        });
        t.Run("native DMA IMAGE chain preserves GIF tag PRE Q and pixels", [](TestCase &t) {
            for(const uint64_t format : {2ull,3ull}) for(const bool pre : {false,true})
            {
                PS2Memory mem; t.IsTrue(mem.initialize(),"Memoria para cadena DMA");
                Recording r; GS gs; gs.init(mem.getGSVRAM(),uint32_t(PS2_GS_VRAM_SIZE));
                gs.setRasterBackend(std::make_unique<Recorder>(r));
                constexpr uint32_t address=0x28000u,pixels=0x29000u;
                const uint64_t chain[]={5ull|(1ull<<28),0ull,
                    4ull|(1ull<<60)|(pre ? (1ull<<46)|(uint64_t(GS_PRIM_SPRITE)<<47) : 0ull),0xeull,
                    (96ull<<32)|(1ull<<48),GS_REG_BITBLTBUF,
                    0ull,GS_REG_TRXPOS,4ull|(1ull<<32),GS_REG_TRXREG,0ull,GS_REG_TRXDIR,
                    1ull|(1ull<<28),0ull,
                    1ull|(format<<58)|(1ull<<46),0ull,
                    1ull|(3ull<<28)|(uint64_t(pixels)<<32),0ull,
                    7ull<<28,0ull};
                std::memcpy(mem.getRDRAM()+address,chain,sizeof(chain));
                for(uint32_t i=0;i<16u;++i) mem.getRDRAM()[pixels+i]=uint8_t(0x40u+i);
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
                gs.writeRegister(GS_REG_RGBAQ,0x4000000080112233ull); // Q=2 antes de la etiqueta.
                t.IsTrue(mem.tryProcessNativeGifImageUploadChain(gs,address,0x105u),"Cadena IMAGE/IMAGE2 validada usa el atajo");
                t.Equals(gs.nativeImageUploadCount(),1ull,"Una sola subida nativa");
                t.Equals(gs.getDebugSnapshot().prim.type,uint8_t(pre ? GS_PRIM_SPRITE : GS_PRIM_TRIANGLE),
                         "Solo PRE de la etiqueta PACKED del setup afecta a PRIM");
                t.IsTrue(r.uploaded.size()==16u && std::memcmp(r.uploaded.data(),mem.getRDRAM()+pixels,16u)==0,
                         "El atajo conserva los bytes de los pixels");
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_POINT);
                gs.writeRegister(GS_REG_XYZ2,0x00100010ull);
                t.Equals(r.draws.size(),size_t(1),"Punto posterior para observar Q sin otra GIFtag");
                if(!r.draws.empty()) {
                    t.Equals(r.draws[0].vertices[0].q,1.0f,"El atajo DMA reinicia Q por las etiquetas no vacias");
                    t.Equals(r.draws[0].vertices[0].r,uint8_t(0x33u),"Reiniciar Q no cambia el color previo");
                }
            }
        });
        t.Run("rejected native DMA IMAGE chain does not apply its setup tag", [](TestCase &t) {
            PS2Memory mem; t.IsTrue(mem.initialize(),"Memoria para cadena DMA rechazada");
            Recording r; GS gs; gs.init(mem.getGSVRAM(),uint32_t(PS2_GS_VRAM_SIZE));
            gs.setRasterBackend(std::make_unique<Recorder>(r));
            constexpr uint32_t address=0x28000u,pixels=0x29000u;
            const uint64_t chain[]={5ull|(1ull<<28),0ull,
                4ull|(1ull<<60)|(1ull<<46)|(uint64_t(GS_PRIM_SPRITE)<<47),0xeull,
                (96ull<<32)|(1ull<<48),GS_REG_BITBLTBUF,
                0ull,GS_REG_TRXPOS,4ull|(1ull<<32),GS_REG_TRXREG,0ull,GS_REG_TRXDIR,
                1ull|(1ull<<28),0ull,1ull|(2ull<<58),0ull,
                1ull|(3ull<<28)|(uint64_t(pixels)<<32),0ull,
                2ull<<28,0ull}; // terminal NEXT invalido para el atajo canonico
            std::memcpy(mem.getRDRAM()+address,chain,sizeof(chain));
            gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
            gs.writeRegister(GS_REG_RGBAQ,0x4000000080112233ull);
            t.IsTrue(!mem.tryProcessNativeGifImageUploadChain(gs,address,0x105u),"Validar toda la cadena antes de alterar GS");
            t.Equals(gs.nativeImageUploadCount(),0ull,"Rechazo no cuenta una subida");
            t.IsTrue(r.uploaded.empty(),"Rechazo no sube pixels");
            t.Equals(gs.getDebugSnapshot().prim.type,uint8_t(GS_PRIM_TRIANGLE),"PRE queda intacto tras el rechazo");
            gs.writeRegister(GS_REG_PRIM,GS_PRIM_POINT); gs.writeRegister(GS_REG_XYZ2,0x00100010ull);
            t.Equals(r.draws.size(),size_t(1),"Punto posterior al rechazo");
            if(!r.draws.empty()) t.Equals(r.draws[0].vertices[0].q,2.0f,"Q queda intacto tras el rechazo");
        });
        t.Run("GS reset discards partial GIF input before the next packet", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
            const uint64_t partial[]={2ull|(1ull<<60),0xeull,5ull,GS_REG_COLCLAMP};
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(partial),sizeof(partial));
            t.IsTrue(gs.hasPendingGIFPacket(GifPathId::Path1),"La etiqueta conserva su segundo registro pendiente");
            gs.reset();
            t.IsTrue(!gs.hasPendingGIFPacket(GifPathId::Path1),"Reset limpia el cursor");
            const uint64_t next[]={1ull|(1ull<<15)|(1ull<<60),0xeull,1ull,GS_REG_DTHE};
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(next),sizeof(next));
            t.Equals(gs.getDebugSnapshot().dthe,1ull,"Reset elimina la etiqueta incompleta anterior");
        });
        t.Run("GIF preserves independent PACKED and REGLIST cursors on interleaved paths", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
            const uint64_t path2[]={2ull|(1ull<<60),0xeull,7ull,GS_REG_COLCLAMP};
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(path2),sizeof(path2),GifPathId::Path2);
            const uint64_t path3[]={1ull|(uint64_t(GIF_FMT_REGLIST)<<58)|(3ull<<60),0x760ull,uint64_t(GS_PRIM_TRIANGLE)};
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(path3),sizeof(path3),GifPathId::Path3);
            const uint64_t path1[]={1ull|(1ull<<15)|(1ull<<60),0xeull,2ull,GS_REG_DTHE};
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(path1),sizeof(path1),GifPathId::Path1);
            const uint64_t end2[]={1ull,GS_REG_DTHE},end3[]={11ull,22ull,0xffffffffffffffffull};
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(end2),sizeof(end2),GifPathId::Path2);
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(end3),sizeof(end3),GifPathId::Path3);
            const auto s=gs.getDebugSnapshot();
            t.IsTrue(s.colclamp==7u && s.dthe==1u && s.ctx[0].tex0.tbp0==11u && s.ctx[1].tex0.tbp0==22u,
                     "Los registros globales se aplican en orden, sin compartir el cursor del parser");
            for(const auto path : {GifPathId::Path1,GifPathId::Path2,GifPathId::Path3})
                t.IsTrue(!gs.hasPendingGIFPacket(path),"Los tres PATH terminan sus etiquetas");
        });
        t.Run("native PACKED shortcut cannot bypass a pending GIF tag on its path", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
            const uint64_t partial[]={2ull|(1ull<<60),0xeull,7ull,GS_REG_COLCLAMP};
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(partial),sizeof(partial),GifPathId::Path3);
            const uint64_t packet[]={1ull|(1ull<<15)|(1ull<<60),0xeull,1ull,GS_REG_DTHE};
            t.IsTrue(!gs.processNativePackedGIFPacket(reinterpret_cast<const uint8_t *>(packet),sizeof(packet),GifPathId::Path3),
                     "El atajo devuelve false sin consumir el fragmento ni alterar registros");
            t.Equals(gs.nativePackedGIFPacketCount(),uint64_t(0),"No contar un atajo rechazado");
            t.IsTrue(gs.processNativePackedGIFPacket(reinterpret_cast<const uint8_t *>(packet),sizeof(packet),GifPathId::Path1),
                     "Otro PATH completo puede usar el atajo");
            const uint64_t end[]={2ull,GS_REG_DTHE};
            gs.processGIFPacket(reinterpret_cast<const uint8_t *>(end),sizeof(end),GifPathId::Path3);
            t.Equals(gs.getDebugSnapshot().dthe,2ull,"La continuacion real PATH3 sigue intacta");
            t.IsTrue(gs.processNativePackedGIFPacket(reinterpret_cast<const uint8_t *>(packet),sizeof(packet),GifPathId::Path3),
                     "El mismo PATH puede usar el atajo despues de completar su etiqueta");
            t.Equals(gs.getDebugSnapshot().dthe,1ull,"El paquete nativo posterior se procesa");
        });
        t.Run("GIF NREG zero retains all sixteen register slots across fragments", [](TestCase &t) {
            std::vector<uint64_t> packet={1ull|(1ull<<15),0xefffffffffffffffull};
            for(unsigned i=0;i<15u;++i) {packet.push_back(0u);packet.push_back(0u);}
            packet.push_back(7u);packet.push_back(GS_REG_COLCLAMP);
            const auto *bytes=reinterpret_cast<const uint8_t *>(packet.data());
            const uint32_t size=uint32_t(packet.size()*8u);
            bool complete=true;
            for(uint32_t cut=0;cut<=size;++cut)
            {
                std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GS gs; gs.init(vram.data(),uint32_t(vram.size()));
                gs.processGIFPacket(bytes,cut);gs.processGIFPacket(bytes+cut,size-cut);
                complete &= gs.getDebugSnapshot().colclamp==7u && !gs.hasPendingGIFPacket(GifPathId::Path1);
            }
            t.IsTrue(complete,"NREG=0 significa dieciseis, incluido el ultimo A+D");
        });
        // GOW-Port: etiquetas vacias y PRE no deben cambiar la geometria que sigue.
        t.Run("empty GIFtags ignore PRE in generic and native PACKED paths", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize);
            GS gs; gs.init(vram.data(),static_cast<uint32_t>(vram.size()));
            for(const bool native : {false,true}) for(uint64_t format=0;format<4;++format)
            {
                if(native && format!=GIF_FMT_PACKED) continue;
                gs.writeRegister(GS_REG_PRIM,static_cast<uint64_t>(GS_PRIM_TRIANGLE)|(1ull<<9));
                const uint64_t tag[]={(1ull<<15)|(1ull<<46)|
                    (static_cast<uint64_t>(GS_PRIM_SPRITE)<<47)|(format<<58)|(15ull<<60),0ull};
                if(native) t.IsTrue(gs.processNativePackedGIFPacket(reinterpret_cast<const uint8_t *>(tag),sizeof(tag)),"Etiqueta PACKED vacia valida");
                else gs.processGIFPacket(reinterpret_cast<const uint8_t *>(tag),sizeof(tag));
                const auto state=gs.getDebugSnapshot();
                t.Equals(state.prim.type,static_cast<uint8_t>(GS_PRIM_TRIANGLE),"NLOOP=0 conserva la topologia");
                t.IsTrue(state.prim.ctxt,"NLOOP=0 conserva el contexto");
            }
        });
        t.Run("empty GIFtags preserve pending triangle vertices and Q", [](TestCase &t) {
            for(const bool native : {false,true}) for(const bool pre : {false,true})
            {
                Recording r;
                std::vector<uint8_t> vram(GSSwizzle::kMemorySize);
                GS gs; gs.init(vram.data(),static_cast<uint32_t>(vram.size()));
                gs.setRasterBackend(std::make_unique<Recorder>(r));
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
                gs.writeRegister(GS_REG_RGBAQ,0x4000000080112233ull); // Q=2.
                gs.writeRegister(GS_REG_XYZ2,0x00100010ull);
                gs.writeRegister(GS_REG_XYZ2,0x00100040ull);
                // PRE=0 aisla Q; PRE=1 con el mismo PRIM detecta el descarte de vertices.
                const uint64_t empty[]={(1ull<<15)|(pre ? (1ull<<46)|(static_cast<uint64_t>(GS_PRIM_TRIANGLE)<<47) : 0ull),0ull};
                if(native) t.IsTrue(gs.processNativePackedGIFPacket(reinterpret_cast<const uint8_t *>(empty),sizeof(empty)),"Etiqueta PACKED vacia valida");
                else gs.processGIFPacket(reinterpret_cast<const uint8_t *>(empty),sizeof(empty));
                gs.writeRegister(GS_REG_XYZ2,0x00400010ull);
                t.Equals(r.draws.size(),size_t(1),"La etiqueta vacia conserva los dos vertices previos");
                if(!r.draws.empty()) for(int i=0;i<3;++i)
                    t.Equals(r.draws[0].vertices[i].q,2.0f,"NLOOP=0 no reinicia Q");

                // Una etiqueta no vacia sigue reiniciando Q aunque su unico registro sea NOP.
                gs.writeRegister(GS_REG_RGBAQ,0x4000000080112233ull);
                const uint64_t nonempty[]={1ull|(1ull<<15)|(1ull<<60),0xfull,0ull,0ull};
                if(native) t.IsTrue(gs.processNativePackedGIFPacket(reinterpret_cast<const uint8_t *>(nonempty),sizeof(nonempty)),"PACKED no vacio valido");
                else gs.processGIFPacket(reinterpret_cast<const uint8_t *>(nonempty),sizeof(nonempty));
                gs.writeRegister(GS_REG_XYZ2,0x00100010ull);
                gs.writeRegister(GS_REG_XYZ2,0x00100040ull);
                gs.writeRegister(GS_REG_XYZ2,0x00400010ull);
                t.Equals(r.draws.size(),size_t(2),"El siguiente triangulo tambien llega al backend");
                if(r.draws.size()==2) for(int i=0;i<3;++i)
                    t.Equals(r.draws[1].vertices[i].q,1.0f,"Una etiqueta no vacia reinicia Q");
            }
        });
        t.Run("GIFtag PRE applies only to nonempty PACKED packets", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize);
            GS gs; gs.init(vram.data(),static_cast<uint32_t>(vram.size()));
            for(const uint64_t format : {uint64_t(GIF_FMT_REGLIST),uint64_t(GIF_FMT_IMAGE)})
            {
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
                const uint64_t tag[]={1ull|(1ull<<15)|(1ull<<46)|
                    (static_cast<uint64_t>(GS_PRIM_SPRITE)<<47)|(format<<58)|(2ull<<60),0xffull,0ull,0ull};
                gs.processGIFPacket(reinterpret_cast<const uint8_t *>(tag),sizeof(tag));
                t.Equals(gs.getDebugSnapshot().prim.type,static_cast<uint8_t>(GS_PRIM_TRIANGLE),"REGLIST e IMAGE ignoran PRE");
            }
            for(const bool native : {false,true})
            {
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
                const uint64_t packed[]={1ull|(1ull<<15)|(1ull<<46)|
                    (static_cast<uint64_t>(GS_PRIM_SPRITE)<<47)|(1ull<<60),0xfull,0ull,0ull};
                if(native) t.IsTrue(gs.processNativePackedGIFPacket(reinterpret_cast<const uint8_t *>(packed),sizeof(packed)),"PACKED con PRE valido");
                else gs.processGIFPacket(reinterpret_cast<const uint8_t *>(packed),sizeof(packed));
                t.Equals(gs.getDebugSnapshot().prim.type,static_cast<uint8_t>(GS_PRIM_SPRITE),"PACKED no vacio aplica PRE");
            }
        });
        t.Run("native IMAGE upload honors setup PRE and resets Q without IMAGE PRE", [](TestCase &t) {
            for(const bool pre : {false,true})
            {
                Recording r;
                std::vector<uint8_t> vram(GSSwizzle::kMemorySize);
                GS gs; gs.init(vram.data(),static_cast<uint32_t>(vram.size()));
                gs.setRasterBackend(std::make_unique<Recorder>(r));
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_TRIANGLE);
                gs.writeRegister(GS_REG_RGBAQ,0x4000000080112233ull);
                const uint64_t packet[]={4ull|(1ull<<60)|
                    (pre ? (1ull<<46)|(static_cast<uint64_t>(GS_PRIM_SPRITE)<<47) : 0ull),0xeull,
                    (96ull<<32)|(1ull<<48),GS_REG_BITBLTBUF,
                    0ull,GS_REG_TRXPOS,4ull|(1ull<<32),GS_REG_TRXREG,0ull,GS_REG_TRXDIR,
                    1ull|(1ull<<15)|(1ull<<46)|(uint64_t(GIF_FMT_IMAGE)<<58),0ull,
                    0x8044556680112233ull,0x80aabbcc80778899ull};
                gs.processGIFPacket(reinterpret_cast<const uint8_t *>(packet),sizeof(packet));
                t.Equals(gs.nativeImageUploadCount(),uint64_t(1),"Se ejercita la subida IMAGE nativa");
                t.Equals(gs.getDebugSnapshot().prim.type,static_cast<uint8_t>(pre ? GS_PRIM_SPRITE : GS_PRIM_TRIANGLE),"Solo PRE del setup PACKED cambia PRIM");
                t.Equals(r.uploaded.size(),size_t(16),"La subida conserva los cuatro pixeles");
                if(r.uploaded.size()==16) t.IsTrue(std::memcmp(r.uploaded.data(),packet+12,16)==0,"Los bytes de IMAGE no cambian");
                gs.writeRegister(GS_REG_PRIM,GS_PRIM_POINT);
                gs.writeRegister(GS_REG_XYZ2,0x00100010ull);
                t.Equals(r.draws.size(),size_t(1),"El siguiente punto llega al backend");
                if(!r.draws.empty()) t.Equals(r.draws[0].vertices[0].q,1.0f,"Las etiquetas no vacias reinician Q tambien en el atajo IMAGE");
            }
        });
        t.Run("queue owns upload and draw payloads; Flush is a barrier", [](TestCase &t) {
            Recording r;
            GSThreadedBackend b(std::make_unique<Recorder>(r)); b.Initialize(nullptr,0);
            std::vector<uint8_t> data{1,2,3,4}; auto draw=sprite();
            b.BeginTransfer({}); b.UploadImage(data.data(),4); b.Submit(draw); b.TextureFlush();
            data.assign(4,99); draw.vertices[0].r=255; b.Flush();
            t.IsTrue(r.events == std::vector<int>({1,2,3,6,5}),"Orden upload/dibujo/flush");
            t.IsTrue(r.uploaded == std::vector<uint8_t>({1,2,3,4}),"Datos propios de la cola");
            if(!r.draws.empty()) t.Equals(r.draws[0].vertices[0].r,25,"Vértices copiados antes del retorno");
            t.IsTrue(r.owner != std::this_thread::get_id(),"Backend inicializado en el hilo GS");
        });
        t.Run("FINISH and readback wait for the last compact draw state", [](TestCase &t) {
            Recording r; GSThreadedBackend b(std::make_unique<Recorder>(r)); b.Initialize(nullptr,0);
            auto draw=sprite(); b.Submit(draw); b.Submit(draw);
            draw.state.context.frame.fbp=11; b.Submit(draw);
            b.Sync(GSSyncReason::Finish);
            t.Equals(r.draws.size(),size_t(3),"FINISH completó los dibujos anteriores");
            if(!r.events.empty()) t.Equals(r.events.back(),7,"FINISH llegó al backend");
            if(!r.draws.empty()) t.Equals(r.draws.back().state.context.frame.fbp,11u,"Cambio de estado compacto");
            b.Submit(draw); t.Equals(b.ReadVram(0,0,1,0,0),4u,"Lectura completa el bloque abierto");
        });
        t.Run("destruction drains bounded queue and destroys on its owner", [](TestCase &t) {
            Recording r;
            { GSThreadedBackend b(std::make_unique<Recorder>(r)); b.Initialize(nullptr,0);
              auto draw=sprite();
              for(int i=0;i<4000;++i) { draw.vertices[0].x=static_cast<float>(i); b.Submit(draw); }
            }
            t.Equals(r.draws.size(),size_t(4000),"No se descartó el último bloque");
            if(!r.draws.empty()) t.Equals(r.draws.back().vertices[0].x,3999.0f,"Orden entre bloques");
            t.IsTrue(r.owner == r.destroyer,"Contexto destruido en el hilo propietario");
        });
        t.Run("threaded CPU preserves transfers and immediate CPU VRAM", [](TestCase &t) {
            std::vector<uint8_t> a(GSSwizzle::kMemorySize),b(GSSwizzle::kMemorySize);
            GSCpuBackend cpu; cpu.Initialize(a.data(),static_cast<uint32_t>(a.size()));
            GSThreadedBackend thread(std::make_unique<GSCpuBackend>()); thread.Initialize(b.data(),static_cast<uint32_t>(b.size()));
            transferRoundtrip(t,cpu); transferRoundtrip(t,thread);
            auto draw=sprite(); cpu.Submit(draw); thread.Submit(draw);
            std::vector<uint8_t> actual; thread.SnapshotVram(actual);
            t.IsTrue(a == actual,"Cola CPU reproduce la VRAM de la ruta directa");
        });
        t.Run("CPU CT24 and Z24 retain pixels across every upload byte cut", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); transfer24Fragments(t,backend);
        });
        t.Run("CPU reset and new transfer discard partial CT24 pixels", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); transfer24Reset(t,backend);
        });
        t.Run("CPU triangle colors sample at the GS integer pixel center", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); triangleSampling(t,backend,0);
        });
        t.Run("CPU triangles retain fractional XYOFFSET and coverage", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); triangleSampling(t,backend,1);
        });
        t.Run("CPU shared triangle edges draw exactly once for both windings", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); triangleSampling(t,backend,2);
        });
        t.Run("CPU sprites preserve fractional XYOFFSET and coverage", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); spriteSampling(t,backend,0);
        });
        t.Run("CPU sprites with zero width or height do not draw", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); spriteSampling(t,backend,1);
        });
        t.Run("CPU sprite linear filtering preserves UV fractional bits", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); spriteSampling(t,backend,2);
        });
        t.Run("CPU sprite texture axes preserve reversed and clipped texels", [](TestCase &t) {
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize); GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size())); spriteSampling(t,backend,3);
        });
        t.Run("CPU Gouraud triangles preserve constant RGBA",[](TestCase &t){
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize);GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size()));triangleConstants(t,backend,false);
        });
        t.Run("CPU triangles preserve constant FOG against a non-interpolated control",[](TestCase &t){
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize);GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size()));triangleConstants(t,backend,true);
        });
        t.Run("CPU triangles preserve constant UV texture coordinates",[](TestCase &t){
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize);GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size()));triangleTextureConstants(t,backend,true);
        });
        t.Run("CPU triangles preserve constant homogeneous STQ coordinates",[](TestCase &t){
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize);GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size()));triangleTextureConstants(t,backend,false);
        });
        t.Run("GPU swizzle matches existing GS memory for all 13 formats", [](TestCase &t) {
            GSMem::InitLookupTables();
            const uint32_t formats[]={0,1,2,10,19,20,27,36,44,48,49,50,58};
            using Writer=void(*)(uint8_t*,uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
            using Reader=uint32_t(*)(uint8_t*,uint32_t,uint32_t,uint32_t,uint32_t);
            const Writer writes[]={GSMem::WriteCT32,GSMem::WriteCT24,GSMem::WriteCT16,GSMem::WriteCT16S,GSMem::WriteP8,GSMem::WriteP4,GSMem::WriteP8H,GSMem::WriteP4HL,GSMem::WriteP4HH,GSMem::WriteZ32,GSMem::WriteZ24,GSMem::WriteZ16,GSMem::WriteZ16S};
            const Reader reads[]={GSMem::ReadCT32,GSMem::ReadCT24,GSMem::ReadCT16,GSMem::ReadCT16S,GSMem::ReadP8,GSMem::ReadP4,GSMem::ReadP8H,GSMem::ReadP4HL,GSMem::ReadP4HH,GSMem::ReadZ32,GSMem::ReadZ24,GSMem::ReadZ16,GSMem::ReadZ16S};
            std::vector<uint8_t> a(GSSwizzle::kMemorySize), b(a.size());
            for(size_t i=0;i<13;++i) for(auto base:{0u,31u,16383u}) for(auto x:{0u,31u,63u,127u,2047u}) for(auto y:{0u,31u,63u,129u,2047u})
            {
                auto psm=formats[i];
                std::fill(a.begin(),a.end(),0xa5); b=a;
                const auto &f=GSSwizzle::GetFormat(psm); auto loc=GSSwizzle::Locate(f,base,8,x,y);
                GSSwizzle::StoreAt(f,a.data()+loc.byte,loc.shift,0x87654321);
                writes[i](b.data(),base,8,x,y,0x87654321);
                if(a != b) { t.Fail("Dirección/máscara diferentes para PSM="+std::to_string(psm)); return; }
                t.Equals(GSSwizzle::LoadAt(f,a.data()+loc.byte,loc.shift),reads[i](b.data(),base,8,x,y),"Lectura del formato");
            }
        });
        // GOW-Port: pruebas nativas opcionales; CI sin GPU prueba la cola y el fallback.
        const char *gpu=std::getenv("GOW_GS_GPU_TEST");
        if(gpu && *gpu && *gpu!='0')
        {
            t.Run("OpenGL triangle depth keeps large-area precision independently of SSE",[](TestCase &t){
                gpuTrianglePrecision(t,false);gpuTrianglePrecision(t,true);
            });
            t.Run("OpenGL compute agrees with synthetic CPU fixture",[](TestCase &t){gpuComparison(t,false);});
            t.Run("OpenGL hardware or compute fallback agrees with CPU fixture",[](TestCase &t){gpuComparison(t,true);});
            t.Run("OpenGL CT24 and Z24 retain pixels across every upload byte cut",[](TestCase &t){
                std::vector<uint8_t> vram(GSSwizzle::kMemorySize); auto gpu=std::make_unique<GSGpuBackend>(); auto *raw=gpu.get();
                GSThreadedBackend backend(std::move(gpu)); backend.Initialize(vram.data(),uint32_t(vram.size()));
                if(dynamic_cast<GSGpuBackend *>(&backend.Inner())!=raw || !raw->IsReady()) {t.Fail("OpenGL requerido");return;}
                transfer24Fragments(t,backend); transfer24Reset(t,backend);
            });
            t.Run("OpenGL state handoff preserves a partial CT24 pixel",[](TestCase &t){
                std::vector<uint8_t> vram(GSSwizzle::kMemorySize); auto gpu=std::make_unique<GSGpuBackend>(); auto *raw=gpu.get();
                GSThreadedBackend backend(std::move(gpu)); backend.Initialize(vram.data(),uint32_t(vram.size()));
                if(dynamic_cast<GSGpuBackend *>(&backend.Inner())!=raw || !raw->IsReady()) {t.Fail("OpenGL requerido");return;}
                GSTransferCommand cmd{}; cmd.direction=0; cmd.bitbltbuf.dbp=96; cmd.bitbltbuf.dbw=1;
                cmd.bitbltbuf.dpsm=GS_PSM_CT24; cmd.trxreg={1,1};
                const uint8_t pixel[]={0x33,0x44,0x55};
                for(const uint32_t partial : {1u,2u}) {
                    backend.BeginTransfer(cmd); backend.UploadImage(pixel,partial); GSBackendState state;
                    t.IsTrue(backend.ExportState(state),"Exportar el estado pendiente"); backend.Reset();
                    t.IsTrue(backend.ImportState(state),"Restaurar el estado pendiente");
                    backend.UploadImage(pixel+partial,3u-partial);
                    t.Equals(backend.ReadVram(GS_PSM_CT24,96,1,0,0),0x554433u,"Importar conserva los bytes del pixel incompleto");
                    t.Equals(backend.GetTransferSnapshot().direction,3u,"La transferencia importada termina");
                }
            });
            t.Run("OpenGL compute and hardware follow GS sprite sampling rules",[](TestCase &t){
                for(const bool hardware : {false,true}) {
                    std::vector<uint8_t> vram(GSSwizzle::kMemorySize); auto gpu=std::make_unique<GSGpuBackend>(); auto *raw=gpu.get();
                    raw->SetHardwareRasterAllowed(hardware); GSThreadedBackend backend(std::move(gpu));
                    backend.Initialize(vram.data(),uint32_t(vram.size()));
                    if(dynamic_cast<GSGpuBackend *>(&backend.Inner())!=raw || !raw->IsReady()) {t.Fail("OpenGL requerido");return;}
                    for(unsigned fixture=0;fixture<4u;++fixture) spriteSampling(t,backend,fixture);
                }
            });
            t.Run("OpenGL compute and hardware preserve constant triangle RGBA and FOG",[](TestCase &t){
                for(const bool hardware:{false,true}){
                    std::vector<uint8_t> vram(GSSwizzle::kMemorySize);auto gpu=std::make_unique<GSGpuBackend>();auto *raw=gpu.get();
                    raw->SetHardwareRasterAllowed(hardware);GSThreadedBackend backend(std::move(gpu));backend.Initialize(vram.data(),uint32_t(vram.size()));
                    if(dynamic_cast<GSGpuBackend *>(&backend.Inner())!=raw||!raw->IsReady()){t.Fail("OpenGL requerido");return;}
                    triangleConstants(t,backend,false);triangleConstants(t,backend,true);
                }
            });
            t.Run("OpenGL compute and hardware preserve constant triangle UV and STQ",[](TestCase &t){
                for(const bool hardware:{false,true}){
                    std::vector<uint8_t> vram(GSSwizzle::kMemorySize);auto gpu=std::make_unique<GSGpuBackend>();auto *raw=gpu.get();
                    raw->SetHardwareRasterAllowed(hardware);GSThreadedBackend backend(std::move(gpu));backend.Initialize(vram.data(),uint32_t(vram.size()));
                    if(dynamic_cast<GSGpuBackend *>(&backend.Inner())!=raw||!raw->IsReady()){t.Fail("OpenGL requerido");return;}
                    triangleTextureConstants(t,backend,true);triangleTextureConstants(t,backend,false);
                }
            });
            t.Run("OpenGL compute and hardware follow GS triangle sampling rules",[](TestCase &t){
                for(const bool hardware : {false,true}) {
                    std::vector<uint8_t> vram(GSSwizzle::kMemorySize); auto gpu=std::make_unique<GSGpuBackend>(); auto *raw=gpu.get();
                    raw->SetHardwareRasterAllowed(hardware); GSThreadedBackend backend(std::move(gpu));
                    backend.Initialize(vram.data(),uint32_t(vram.size()));
                    if(dynamic_cast<GSGpuBackend *>(&backend.Inner())!=raw || !raw->IsReady()) {t.Fail("OpenGL requerido");return;}
                    for(unsigned fixture=0;fixture<3u;++fixture) triangleSampling(t,backend,fixture);
                }
            });
        }
    });
}
