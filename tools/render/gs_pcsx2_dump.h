// GOW-Port: formato GS dump/freeze v8 de PCSX2; serialización propia para el patrón procedural.
// Referencia de formato: PCSX2 v2.8.2, GSState.cpp, GSRegs.h y GSDump.cpp (GPL-3.0+).
// No contiene estado, comandos ni texels del juego. No serializa un GS arbitrario.
#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <span>
#include <vector>

namespace gow_gs_reference
{
    class Bytes {
    public:
        std::vector<uint8_t> data;
        void byte(uint8_t value) { data.push_back(value); }
        void word(uint32_t value) { for(unsigned i=0;i<4;++i) byte(uint8_t(value>>(i*8))); }
        void reg(uint64_t value) { for(unsigned i=0;i<8;++i) byte(uint8_t(value>>(i*8))); }
        void raw(std::span<const uint8_t> value) { data.insert(data.end(),value.begin(),value.end()); }
        void zero(size_t count) { data.resize(data.size()+count); }
    };

    // Estado inicial mínimo de los patrones procedurales: sin transferencias ni GIF pendientes.
    inline bool patternDump(const std::filesystem::path &path,std::span<const uint8_t> seed,
                            const std::array<uint64_t,12> &contextRegisters,const Bytes &commands)
    {
        if(seed.size()!=4u*1024u*1024u || commands.data.empty() || commands.data.size()%16 ||
           commands.data.size()/16>0x7fff) return false;
        constexpr uint64_t display=(511ull<<32)|(447ull<<44);
        Bytes state;state.word(8);
        for(uint64_t value:std::array<uint64_t,15>{0,1,0,0,0,0,0,0,1,0,0,3,0,0,0}) state.reg(value);
        for(unsigned context=0;context<2;++context)
            for(uint64_t value:contextRegisters) state.reg(value);
        state.reg(0x3f80000080808080ull);state.reg(0); // RGBAQ y ST.
        state.word(0);state.word(0);state.reg(0); // GSVertex guarda UV/FOG en 32 bits, XYZ en 64.
        state.reg(0);state.word(0);state.word(0); // Registro obsoleto y cursor de transferencia.
        state.raw(seed);state.zero(80);state.word(0x3f800000u); // Cuatro GIFPath vacíos y Q.
        if(state.data.size()!=seed.size()+448) return false;

        Bytes registers;registers.zero(0x2000);
        auto privileged=[&](size_t offset,uint64_t value) {
            for(unsigned i=0;i<8;++i) registers.data[offset+i]=uint8_t(value>>(i*8));
        };
        privileged(0,1);privileged(0x10,0x20006000);privileged(0x70,8ull<<9);
        privileged(0x80,display);privileged(0x1000,0x55190000);

        Bytes packet;packet.reg(commands.data.size()/16|(1ull<<15)|(1ull<<60));packet.reg(0xE);packet.raw(commands.data);
        Bytes dump;dump.word(0);dump.word(uint32_t(state.data.size()));dump.raw(state.data);dump.raw(registers.data);
        dump.byte(0);dump.byte(3);dump.word(uint32_t(packet.data.size()));dump.raw(packet.data);
        for(unsigned field=0;field<2;++field) {dump.byte(3);dump.raw(registers.data);dump.byte(1);dump.byte(uint8_t(field));}
        std::ofstream output(path,std::ios::binary);output.write(reinterpret_cast<const char*>(dump.data.data()),dump.data.size());
        output.close();return bool(output);
    }

    // GOW-Port: separar invalidación de caché de un corte de lote por cambio de estado.
    enum class FeedbackBoundary { None, Texflush, Scissor };
    inline bool feedbackDump(const std::filesystem::path &path,std::span<const uint8_t> seed,bool disjoint,bool linear,
                             FeedbackBoundary boundary=FeedbackBoundary::None)
    {
        constexpr uint64_t frame=(8ull<<16)|(0xff000000ull<<32);
        constexpr uint64_t zbuf=104ull|(1ull<<24)|(1ull<<32);
        constexpr uint64_t scissor=(511ull<<16)|(447ull<<48);
        const uint64_t tex0=(disjoint?8192ull:0ull)|(8ull<<14)|(10ull<<26)|(10ull<<30)|(1ull<<34);
        const uint64_t tex1=linear?0x60ull:0ull;
        Bytes commands;
        auto ad=[&](uint8_t address,uint64_t value) { commands.reg(value);commands.reg(address); };
        ad(0x1a,1);ad(0x18,0);ad(0x40,scissor);ad(0x4c,frame);ad(0x4e,zbuf);
        ad(0x47,0x31001);ad(0x06,tex0);ad(0x14,tex1);ad(0x08,5);ad(0x46,1);
        ad(0x45,0);ad(0x49,0);ad(0x00,6|16|256);ad(0x01,0x3f80000080808080ull);
        for(unsigned slice=0;slice<2;++slice) {
            if(slice==1 && boundary==FeedbackBoundary::Texflush) ad(0x3f,0);
            if(slice==1 && boundary==FeedbackBoundary::Scissor) ad(0x40,scissor-(1ull<<16));
            const uint64_t x0=slice*32*16,x1=(slice+1)*32*16,y1=416*16;
            ad(0x03,x0);ad(0x05,x0|(7ull<<32));
            ad(0x03,x1|(y1<<16));ad(0x05,x1|(y1<<16)|(7ull<<32));
        }
        ad(0x61,0);
        return patternDump(path,seed,{0,tex0,tex1,5,0,0,scissor,0,0x31001,0,frame,zbuf},commands);
    }

    enum class GridCase {Bilinear,Negative,Boundary,BilinearStq};
    inline float gridCoordinate(GridCase fixture,unsigned index)
    {
        constexpr std::array<float,16> limits={-2.0f,-1.75f,-1.0f,-0.75f,-0.25f,-1.0f/16,-1.0f/256,
            -1.0f/65536,-1.0f/131072,-1.0f/1048576,0,1.0f/1048576,1.0f/16,0.25f,0.75f,1.0f};
        // GOW-Port: STQ bilinear convierte a 16.16 antes de restar medio texel.
        constexpr float e=1.0f/131072;
        constexpr std::array<float,16> bilinearStq={-2-e,-1-e,-0.5f-e,-0.25f-e,-0.0625f-e,
            -e,-2*e,0,e,0.0625f-e,0.0625f+e,0.5f-e,0.5f,0.5f+e,1-e,1+e};
        if(fixture==GridCase::BilinearStq) return bilinearStq.at(index);
        return fixture==GridCase::Boundary?limits.at(index):float(int(index)-8)/4.0f;
    }
    inline bool gridDump(const std::filesystem::path &path,std::span<const uint8_t> seed,GridCase fixture)
    {
        const bool fst=fixture==GridCase::Bilinear;
        const bool linear=fst || fixture==GridCase::BilinearStq;
        constexpr uint64_t frame=8ull<<16,zbuf=104ull|(1ull<<24)|(1ull<<32),scissor=(15ull<<16)|(15ull<<48);
        const uint64_t exponent=fst?1:2,tex1=linear?0x60:0,clamp=fst?5:0;
        const uint64_t tex0=8192ull|(8ull<<14)|(exponent<<26)|(exponent<<30)|(1ull<<34)|(1ull<<35);
        Bytes commands;
        auto ad=[&](uint8_t address,uint64_t value) {commands.reg(value);commands.reg(address);};
        ad(0x1a,1);ad(0x18,0);ad(0x40,scissor);ad(0x4c,frame);ad(0x4e,zbuf);
        ad(0x47,0x30000);ad(0x06,tex0);ad(0x14,tex1);ad(0x08,clamp);ad(0x46,1);
        ad(0x45,0);ad(0x49,0);ad(0x00,6|16|(fst?256:0));ad(0x01,0x3f80000080808080ull);
        for(unsigned y=0;y<16;++y) for(unsigned x=0;x<16;++x) {
            const uint64_t coordinate=fst?(8ull+x)|((8ull+y)<<16):
                uint64_t(std::bit_cast<uint32_t>(gridCoordinate(fixture,x)/4.0f))|
                (uint64_t(std::bit_cast<uint32_t>(gridCoordinate(fixture,y)/4.0f))<<32);
            ad(fst?0x03:0x02,coordinate);ad(0x05,x*16ull|((y*16ull)<<16)|(7ull<<32));
            ad(fst?0x03:0x02,coordinate);ad(0x05,(x+1)*16ull|(((y+1)*16ull)<<16)|(7ull<<32));
        }
        ad(0x61,0);
        return patternDump(path,seed,{0,tex0,tex1,clamp,0,0,scissor,0,0x30000,0,frame,zbuf},commands);
    }
}
