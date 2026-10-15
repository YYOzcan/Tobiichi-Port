// GOW-Port: TA0/TA1/AEM de 48 celdas contrastadas con GSRendererSW original.
#include "MiniTest.h"
#include "runtime/gs/gs_cpu_backend.h"
#include "runtime/gs/gs_gpu_backend.h"
#include "runtime/gs/gs_threaded_backend.h"
#include "runtime/gs/gs_swizzle.h"
#include <array>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <thread>
#include <vector>

namespace {
struct Pattern {bool zero,high,aem;uint8_t ta0,ta1,alpha24,alpha16;};
// GOW-Port: último patrón reproduce TA0=TA1=0 del pase Z16 del juego.
constexpr Pattern patterns[] = {
    {false,false,false,37,201,37,37}, {false,true,false,37,201,37,201},
    {true,false,true,37,201,0,0}, {true,true,true,37,201,0,201},
    {true,false,false,149,53,149,149}, {false,false,true,149,53,149,149},
    {false,true,true,149,53,149,53}, {false,true,false,0,0,0,0}
};
constexpr uint8_t formats[]={GS_PSM_CT24,GS_PSM_Z24,GS_PSM_CT16,GS_PSM_Z16,GS_PSM_CT16S,GS_PSM_Z16S};
bool sixteen(unsigned row){return row>=2;}
uint32_t raw(unsigned row,unsigned col){
    const auto&p=patterns[col];uint32_t value=p.zero?0u:(sixteen(row)?0x1234u:0x123456u);
    return value | ((sixteen(row)&&p.high)?0x8000u:0u);
}
uint32_t expected(unsigned row,unsigned col){
    const auto&p=patterns[col];uint32_t value=raw(row,col),rgb=value&0xffffffu;
    if(sixteen(row)) rgb=((value&31u)<<3)|(((value>>5)&31u)<<11)|(((value>>10)&31u)<<19);
    return rgb | (uint32_t(sixteen(row)?p.alpha16:p.alpha24)<<24);
}
void seed(std::vector<uint8_t>&vram){
    GSCpuBackend writer;writer.Initialize(vram.data(),uint32_t(vram.size()));
    for(unsigned row=0;row<6;++row)for(unsigned col=0;col<8;++col)
        writer.WriteVram(formats[row],8000+(row*8+col)*32,1,0,0,raw(row,col));
}
std::vector<GSPrimitiveBatch> draws(unsigned first=0,unsigned rows=6){
    std::vector<GSPrimitiveBatch> result;
    for(unsigned row=first;row<first+rows;++row)for(unsigned col=0;col<8;++col){
        const auto&p=patterns[col];GSPrimitiveBatch batch{};batch.vertexCount=2;
        auto&s=batch.state;auto&ctx=s.context;s.prim.type=GS_PRIM_SPRITE;
        s.prim.tme=true;s.prim.fst=true;s.colclamp=1;s.texa={p.ta0,p.aem,p.ta1};
        ctx.frame={0,1,GS_PSM_CT32,0};ctx.scissor={0,63,0,63};ctx.zbuf={104,GS_PSM_Z24,true};
        ctx.test=0;ctx.tex0.tbp0=8000+(row*8+col)*32;ctx.tex0.tbw=1;
        ctx.tex0.psm=formats[row];ctx.tex0.tfx=1;ctx.tex0.tcc=1;
        s.textureWidth=s.textureHeight=1;
        for(unsigned i=0;i<2;++i){auto&v=batch.vertices[i];v.x=float(col*8+1+i);v.y=float(row*8+1+i);
            v.z=1;v.r=v.g=v.b=v.a=128;v.u=v.v=uint16_t(i*16);}
        result.push_back(batch);
    }
    return result;
}
void check(TestCase&t,GSRasterBackend&b,unsigned first=0,unsigned rows=6){
    for(unsigned row=first;row<first+rows;++row)for(unsigned col=0;col<8;++col){
        t.Equals(b.ReadVram(GS_PSM_CT32,0,1,col*8+1,row*8+1),expected(row,col),
            "RGBA de textura usa TEXA también en alias depth; RGB conservado");
        t.Equals(b.ReadVram(GS_PSM_CT32,0,1,col*8+2,row*8+1),0x35353535u,
            "Vecino no cubierto conserva su RGBA");
    }
}
void cpu(TestCase&t,unsigned first){
    std::vector<uint8_t> vram(GSSwizzle::kMemorySize,0x35);seed(vram);GSCpuBackend b;
    b.Initialize(vram.data(),uint32_t(vram.size()));for(const auto&batch:draws(first,2))b.Submit(batch);check(t,b,first,2);
}
void gpu(TestCase&t,bool hardware){
    std::vector<uint8_t> vram(GSSwizzle::kMemorySize,0x35);seed(vram);
    auto inner=std::make_unique<GSGpuBackend>();auto*actual=inner.get();actual->SetHardwareRasterAllowed(hardware);
    GSThreadedBackend b(std::move(inner));b.Initialize(vram.data(),uint32_t(vram.size()));
    if(dynamic_cast<GSGpuBackend*>(&b.Inner())!=actual||!actual->IsReady()){t.Fail("OpenGL efectivo requerido, sin fallback CPU");return;}
    const auto batches=draws();bool observed=false;
    const auto deadline=std::chrono::steady_clock::now()+std::chrono::seconds(20);
    do{
        const auto before=actual->GetStats();for(const auto&batch:batches)b.Submit(batch);
        std::vector<uint8_t>snapshot;b.SnapshotVram(snapshot);const auto after=actual->GetStats();check(t,b);
        observed=hardware?(after.tiles==before.tiles&&after.prims-before.prims==batches.size()):after.tiles>before.tiles;
        if(!observed)std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }while(hardware&&!observed&&std::chrono::steady_clock::now()<deadline);
    t.IsTrue(observed,hardware?"Hardware observado sin tiles compute":"Compute observado");
}
}
void register_gs_texa_depth_tests(){
    MiniTest::Case("GS TEXA en texturas depth",[](TestCase&t){
        t.Run("CPU CT24/Z24 TA0/AEM",[](TestCase&t){cpu(t,0);});
        t.Run("CPU CT16/Z16 TA0/TA1/AEM",[](TestCase&t){cpu(t,2);});
        t.Run("CPU CT16S/Z16S TA0/TA1/AEM",[](TestCase&t){cpu(t,4);});
        if(const char*enabled=std::getenv("GOW_GS_GPU_TEST");enabled&&enabled[0]=='1'){
            t.Run("OpenGL compute TEXA externo",[](TestCase&t){gpu(t,false);});
            t.Run("OpenGL hardware TEXA externo",[](TestCase&t){gpu(t,true);});
        }
    });
}
