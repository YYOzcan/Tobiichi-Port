// GOW-Port: colores de referencia obtenidos con el shader DX11 original de PCSX2.
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
struct Sample { uint32_t input, fogColor, expected; uint8_t fog; bool enabled; };
// GOW-Port: dos sprites con nieblas distintas en un lote evitan el clear FOG=255
// de PCSX2. Se conservan RGB medidos; alpha 0x80 corresponde al framebuffer, no al PCRTC.
constexpr Sample samples[] = {
    {0x804020f0,0xc86432,0x804020f0,0,false},
    {0x804020f0,0xc86432,0x80c86432,0,true},
    {0x804020f0,0xc86432,0x80c76332,1,true},
    {0x804020f0,0xc86432,0x809f4f6b,77,true},
    {0x804020f0,0xc86432,0x80844291,128,true},
    {0x804020f0,0xc86432,0x805d2ec7,201,true},
    {0x804020f0,0xc86432,0x804020ef,255,true},
    {0x8080ff00,0x8000ff,0x8080ff00,0,false},
    {0x8080ff00,0x8000ff,0x808000ff,0,true},
    {0x8080ff00,0x8000ff,0x808000fe,1,true},
    {0x8080ff00,0x8000ff,0x80804cb2,77,true},
    {0x8080ff00,0x8000ff,0x80807f7f,128,true},
    {0x8080ff00,0x8000ff,0x8080c836,201,true},
    {0x8080ff00,0x8000ff,0x8080fe00,255,true}
};
std::vector<GSPrimitiveBatch> draws(){
    std::vector<GSPrimitiveBatch> output;
    for(unsigned i=0;i<std::size(samples);++i){
        const auto& sample=samples[i];GSPrimitiveBatch batch{};
        batch.vertexCount=2;batch.state.prim.type=GS_PRIM_SPRITE;
        batch.state.prim.fge=sample.enabled;batch.state.colclamp=1;
        auto& context=batch.state.context;
        context.frame={0,1,GS_PSM_CT32,0};context.scissor={0,63,0,63};
        context.zbuf={104,GS_PSM_Z32,true};context.test=0x30000;
        batch.state.fogR=uint8_t(sample.fogColor);
        batch.state.fogG=uint8_t(sample.fogColor>>8);batch.state.fogB=uint8_t(sample.fogColor>>16);
        for(unsigned v=0;v<2;++v){
            auto& vertex=batch.vertices[v];vertex.x=float(4+i*2+v);vertex.y=float(1+v);vertex.z=1;
            vertex.r=uint8_t(sample.input);vertex.g=uint8_t(sample.input>>8);
            vertex.b=uint8_t(sample.input>>16);vertex.a=uint8_t(sample.input>>24);vertex.fog=sample.fog;
        }
        output.push_back(batch);
    }
    return output;
}
void checkPixels(TestCase& test,GSRasterBackend& backend){
    for(unsigned i=0;i<std::size(samples);++i){
        test.Equals(backend.ReadVram(GS_PSM_CT32,0,1,4+i*2,1),samples[i].expected,
                    "RGB de referencia y alpha conservado, sin usar CPU como oráculo GPU");
        test.Equals(backend.ReadVram(GS_PSM_CT32,0,1,5+i*2,1),0x35353535u,
                    "Píxel vecino no cubierto conserva el fondo");
    }
}
void gpuCheck(TestCase& test,bool hardware){
    std::vector<uint8_t> vram(GSSwizzle::kMemorySize,0x35);
    auto gpu=std::make_unique<GSGpuBackend>();auto* raw=gpu.get();
    raw->SetHardwareRasterAllowed(hardware);GSThreadedBackend backend(std::move(gpu));
    backend.Initialize(vram.data(),uint32_t(vram.size()));
    if(dynamic_cast<GSGpuBackend*>(&backend.Inner())!=raw || !raw->IsReady()){
        test.Fail("OpenGL requerido, sin fallback CPU");return;
    }
    const auto batches=draws();bool observed=false;
    const auto deadline=std::chrono::steady_clock::now()+std::chrono::seconds(20);
    do{
        const auto before=raw->GetStats();
        for(const auto& batch:batches)backend.Submit(batch);
        std::vector<uint8_t> snapshot;backend.SnapshotVram(snapshot);
        const auto after=raw->GetStats();checkPixels(test,backend);
        observed=hardware?(after.tiles==before.tiles && after.prims-before.prims==batches.size())
                         :after.tiles>before.tiles;
        if(!observed)std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }while(hardware && !observed && std::chrono::steady_clock::now()<deadline);
    test.IsTrue(observed,hardware?"Hardware efectivo, sin tiles compute":"Compute efectivo, sin fallback CPU");
}
}
void register_gs_fog_math_tests(){
    MiniTest::Case("GS precisión de niebla",[](TestCase& test){
        test.Run("CPU RGB externo, extremos y alpha",[](TestCase& test){
            std::vector<uint8_t> vram(GSSwizzle::kMemorySize,0x35);GSCpuBackend backend;
            backend.Initialize(vram.data(),uint32_t(vram.size()));
            for(const auto& batch:draws())backend.Submit(batch);
            checkPixels(test,backend);
        });
        if(const char* enabled=std::getenv("GOW_GS_GPU_TEST");enabled && enabled[0]=='1'){
            test.Run("OpenGL compute RGB externo",[](TestCase& test){gpuCheck(test,false);});
            test.Run("OpenGL hardware RGB externo",[](TestCase& test){gpuCheck(test,true);});
        }
    });
}
