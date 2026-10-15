// GOW-Port: esperados contrastados con GSRendererSW original y GLSL, sin juego.
#include "MiniTest.h"
#include "runtime/gs/gs_cpu_backend.h"
#include <vector>
namespace {
void check(TestCase& test,bool negative,bool clamp) {
    std::vector<uint8_t> vram(4u<<20,0x35);GSCpuBackend backend;
    backend.Initialize(vram.data(),uint32_t(vram.size()));
    const uint32_t dest=negative?0u:0x00204050u;
    const uint32_t source=negative?0x00804020u:0x00f0dcc8u;
    const uint32_t expected=negative?(clamp?0u:0x0080c0e0u):(clamp?0x00ffffffu:0x00101c18u);
    backend.WriteVram(GS_PSM_CT32,0,1,2,3,dest|0x73000000u);
    backend.WriteVram(GS_PSM_Z32,104*32,1,2,3,0x12345678u);
    GSPrimitiveBatch b{};b.vertexCount=2;b.state.prim.type=GS_PRIM_SPRITE;
    b.state.prim.abe=true;b.state.colclamp=clamp?1:0;
    auto& c=b.state.context;c.frame={0,1,GS_PSM_CT32,0};c.scissor={0,63,0,63};
    c.zbuf={104,GS_PSM_Z32,false};c.test=0;
    c.alpha=(uint64_t(128)<<32)|(negative?0xa2u:0x68u);
    for(unsigned i=0;i<2;++i){auto&v=b.vertices[i];v.x=float(2+i);v.y=float(3+i);
        v.r=uint8_t(source);v.g=uint8_t(source>>8);v.b=uint8_t(source>>16);v.a=128;v.z=50;}
    backend.Submit(b);
    test.Equals(backend.ReadVram(GS_PSM_CT32,0,1,2,3),expected|0x80000000u,
        "COLCLAMP selecciona wrap/clamp del RGB de ALPHA sin modificar alpha fuente");
    test.Equals(backend.ReadVram(GS_PSM_Z32,104*32,1,2,3),0x12345678u,
        "La corrección de RGB no altera Z con ZTE deshabilitado");
    test.Equals(backend.ReadVram(GS_PSM_CT32,0,1,3,3),0x35353535u,"Conserva vecino fuera del sprite");
}
}
void register_gs_cpu_colclamp_tests(){
    MiniTest::Case("GS CPU COLCLAMP",[](TestCase& test){
        test.Run("Mezcla negativa envuelta",[](TestCase& t){check(t,true,false);});
        test.Run("Mezcla negativa saturada",[](TestCase& t){check(t,true,true);});
        test.Run("Desbordamiento envuelto",[](TestCase& t){check(t,false,false);});
        test.Run("Desbordamiento saturado",[](TestCase& t){check(t,false,true);});
    });
}
