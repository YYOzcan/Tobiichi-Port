// GOW-Port: ZTE=0 dibuja sin prueba ni escritura Z, contrastado con DX11 original.
#include "MiniTest.h"
#include "runtime/gs/gs_cpu_backend.h"
#include "runtime/gs/gs_gpu_backend.h"
#include "runtime/gs/gs_threaded_backend.h"
#include "runtime/gs/gs_swizzle.h"
#include <chrono>
#include <cstdlib>
#include <memory>
#include <thread>
#include <vector>

namespace {
constexpr uint32_t background=0x80302010u, source=0x804020f0u;
std::vector<GSPrimitiveBatch> draws(){
    std::vector<GSPrimitiveBatch> result;
    for(unsigned enabled=0;enabled<2;++enabled)for(unsigned method=0;method<4;++method)
        for(unsigned masked=0;masked<2;++masked){
            GSPrimitiveBatch b{};const unsigned x=4+unsigned(result.size())*3;
            b.vertexCount=2;b.state.prim.type=GS_PRIM_SPRITE;b.state.colclamp=1;
            auto& c=b.state.context;c.frame={0,1,GS_PSM_CT32,0};
            c.zbuf={104,GS_PSM_Z32,masked!=0};c.scissor={0,63,0,63};
            c.test=(uint64_t(enabled)<<16)|(uint64_t(method)<<17);
            for(unsigned i=0;i<2;++i){auto& v=b.vertices[i];v.x=float(x+i);v.y=float(1+i);v.z=50;
                v.r=uint8_t(source);v.g=uint8_t(source>>8);v.b=uint8_t(source>>16);v.a=0x80;}
            result.push_back(b);
        }
    return result;
}
void exercise(TestCase& test,GSRasterBackend& backend,const std::vector<GSPrimitiveBatch>& batches){
    for(unsigned i=0;i<batches.size();++i){
        backend.WriteVram(GS_PSM_CT32,0,1,4+i*3,1,background);
        backend.WriteVram(GS_PSM_Z32,104*32,1,4+i*3,1,100);
    }
    for(const auto& b:batches)backend.Submit(b);
    std::vector<uint8_t> snapshot;backend.SnapshotVram(snapshot);
    for(unsigned i=0;i<batches.size();++i){
        const auto& c=batches[i].state.context;
        const bool enabled=(c.test&0x10000u)!=0;const auto method=(c.test>>17)&3;
        const uint32_t rgb=!enabled || method==1?source:background;
        const uint32_t z=enabled && method==1 && !c.zbuf.zmask?50u:100u;
        test.Equals(backend.ReadVram(GS_PSM_CT32,0,1,4+i*3,1),rgb,
                    "Color/alpha: ZTE apagado ignora cualquier ZTST; encendido conserva su prueba");
        test.Equals(backend.ReadVram(GS_PSM_Z32,104*32,1,4+i*3,1),z,
                    "ZTE apagado conserva Z incluso con ZMSK=0; habilitado respeta ZMSK y ZTST");
        test.Equals(backend.ReadVram(GS_PSM_CT32,0,1,5+i*3,1),0x35353535u,
                    "No altera el pixel vecino fuera del sprite");
    }
}
void gpuCheck(TestCase& test,bool hardware){
    std::vector<uint8_t> vram(GSSwizzle::kMemorySize,0x35);
    auto owned=std::make_unique<GSGpuBackend>();auto* gpu=owned.get();
    gpu->SetHardwareRasterAllowed(hardware);GSThreadedBackend backend(std::move(owned));
    backend.Initialize(vram.data(),uint32_t(vram.size()));
    if(dynamic_cast<GSGpuBackend*>(&backend.Inner())!=gpu || !gpu->IsReady()){
        test.Fail("OpenGL requerido, sin fallback CPU");return;
    }
    const auto batches=draws();bool observed=false;
    const auto deadline=std::chrono::steady_clock::now()+std::chrono::seconds(20);
    do{
        const auto before=gpu->GetStats();exercise(test,backend,batches);const auto after=gpu->GetStats();
        observed=hardware?(after.tiles==before.tiles && after.prims-before.prims==batches.size()):after.tiles>before.tiles;
        if(!observed)std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }while(hardware && !observed && std::chrono::steady_clock::now()<deadline);
    test.IsTrue(observed,hardware?"Hardware efectivo, sin compute":"Compute efectivo, sin fallback CPU");
}
}
void register_gs_zte_tests(){
    MiniTest::Case("GS habilitacion de profundidad",[](TestCase& test){
        test.Run("CPU ZTE/ZTST/ZMSK y alpha",[](TestCase& test){
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize,0x35);GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size()));exercise(test,backend,draws());
        });
        if(const char* enabled=std::getenv("GOW_GS_GPU_TEST");enabled && enabled[0]=='1'){
            test.Run("OpenGL compute ZTE/ZTST/ZMSK",[](TestCase& test){gpuCheck(test,false);});
            test.Run("OpenGL hardware ZTE/ZTST/ZMSK",[](TestCase& test){gpuCheck(test,true);});
        }
    });
}
