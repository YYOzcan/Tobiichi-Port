// GOW-Port: XYZF escribe el atributo FOG, incluso si no dibuja. XYZ conserva ese atributo.
#include "MiniTest.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/gs/gs_cpu_backend.h"
#include <array>
#include <memory>
#include <vector>

namespace {
uint64_t xyz(unsigned x){return uint64_t(x*16)|(16ull<<16)|(1ull<<32);}
struct Fixture {
    std::vector<uint8_t> vram=std::vector<uint8_t>(4u<<20);
    GS gs;
    Fixture(){gs.setRasterBackend(std::make_unique<GSCpuBackend>());gs.init(vram.data(),uint32_t(vram.size()));setup();}
    void setup(){
        for(auto reg:{GS_REG_FRAME_1,GS_REG_FRAME_2})gs.writeRegister(reg,1ull<<16);
        for(auto reg:{GS_REG_ZBUF_1,GS_REG_ZBUF_2})gs.writeRegister(reg,1ull<<32);
        for(auto reg:{GS_REG_SCISSOR_1,GS_REG_SCISSOR_2})gs.writeRegister(reg,(63ull<<16)|(63ull<<48));
        for(auto reg:{GS_REG_TEST_1,GS_REG_TEST_2})gs.writeRegister(reg,(1ull<<16)|(1ull<<17)); // ALWAYS.
        gs.writeRegister(GS_REG_PRMODECONT,1);gs.writeRegister(GS_REG_COLCLAMP,1);
        gs.writeRegister(GS_REG_PRIM,1ull<<5); // POINT, FGE, contexto 0.
        gs.writeRegister(GS_REG_RGBAQ,0x3f800000804020f0ull);gs.writeRegister(GS_REG_FOGCOL,0xc86432);
    }
    uint32_t color(unsigned x){return gs.ReadVram(GS_PSM_CT32,0,1,x,1);}
    uint32_t explicitFog(uint8_t fog,unsigned x){
        gs.writeRegister(GS_REG_FOG,uint64_t(fog)<<56);gs.writeRegister(GS_REG_XYZ2,xyz(x));return color(x);
    }
    bool send(unsigned format,bool skip,bool adc,uint8_t fog,GifPathId path){
        const uint8_t descriptor=skip?0x0c:0x04;
        const uint64_t regular=xyz(1)|(uint64_t(fog)<<56);
        if(format==3){gs.writeRegister(descriptor,regular);return true;}
        std::array<uint64_t,4> p{1|(1ull<<15)|(1ull<<60),descriptor,
            16|(16ull<<32),(1ull<<4)|(uint64_t(fog)<<36)|(adc?(1ull<<47):0)};
        if(format==1){p[1]=0xe;p[2]=regular;p[3]=descriptor;}
        else if(format==2){p[0]|=1ull<<58;p[2]=regular;p[3]=0;}
        if(format==4)return gs.processNativePackedGIFPacket(reinterpret_cast<const uint8_t*>(p.data()),sizeof(p),path);
        gs.processGIFPacket(reinterpret_cast<const uint8_t*>(p.data()),sizeof(p),path);return true;
    }
};
void check(TestCase& t,unsigned format,bool skip,bool adc,GifPathId path){
    Fixture fixture;
    const uint32_t expected=fixture.explicitFog(201,3),previous=fixture.explicitFog(13,5);
    t.IsTrue(expected!=0 && expected!=previous,"La niebla explícita cambia un píxel realmente dibujado");
    t.IsTrue(fixture.send(format,skip,adc,201,path),"La ruta solicitada acepta el paquete completo");
    fixture.gs.writeRegister(GS_REG_XYZ2,xyz(2));
    t.Equals(fixture.color(2),expected,"XYZ posterior usa FOG del XYZF, no el FOG anterior");
    const auto replaced=fixture.explicitFog(77,6);fixture.gs.writeRegister(GS_REG_XYZ2,xyz(7));
    t.IsTrue(replaced!=expected,"FOG posterior cambia la niebla del control");
    t.Equals(fixture.color(7),replaced,"XYZ conserva el FOG explícito posterior");
}
}
void register_gs_fog_latch_tests(){
    MiniTest::Case("GS atributo FOG retenido",[](TestCase& tc){
        const char* names[]={"XYZF2/3 PACKED","XYZF2/3 A+D","XYZF2/3 REGLIST","XYZF2/3 escritura directa","XYZF2/3 PACKED nativo"};
        for(unsigned format=0;format<5;++format)tc.Run(names[format],[format](TestCase& t){
            for(auto path:{GifPathId::Path1,GifPathId::Path2,GifPathId::Path3})
                for(bool skip:{false,true})check(t,format,skip,false,path);
        });
        tc.Run("ADC, contexto global y reset",[](TestCase& t){
            for(unsigned format:{0u,4u})check(t,format,false,true,GifPathId::Path1);
            Fixture fixture;const auto expected=fixture.explicitFog(201,3);fixture.explicitFog(13,5);
            fixture.send(0,true,false,201,GifPathId::Path1);
            fixture.gs.writeRegister(GS_REG_PRIM,(1ull<<5)|(1ull<<9));
            fixture.gs.writeRegister(GS_REG_XYZ2,xyz(2));
            t.Equals(fixture.color(2),expected,"FOG es global y sobrevive al cambio de contexto");
            fixture.gs.reset();fixture.setup();fixture.gs.writeRegister(GS_REG_XYZ2,xyz(6));
            const auto resetColor=fixture.color(6);
            t.Equals(resetColor,fixture.explicitFog(0,7),"Reset vuelve al atributo FOG inicial");
        });
    });
}
