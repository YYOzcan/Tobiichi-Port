// GOW-Port: el dump procedural de PCSX2 debe reproducir la captura CPU a través de GIF PATH3.
#include "../src/gow_gs_replay.h"
#include "runtime/gs/gs_cpu_backend.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <span>
#include <string_view>

namespace {
    struct DumpReader {
        std::vector<uint8_t> data;
        size_t offset=0;
        bool good=true;
        std::span<const uint8_t> take(size_t count) {
            if(!good || count>data.size()-offset) {good=false;return {};}
            const auto result=std::span<const uint8_t>(data).subspan(offset,count);
            offset+=count;return result;
        }
        uint32_t number(unsigned bytes) {
            const auto value=take(bytes); uint32_t result=0;
            for(unsigned i=0;i<value.size();++i) result|=uint32_t(value[i])<<(i*8);
            return result;
        }
    };

    void storeWord(std::span<uint8_t> bytes,size_t offset,uint64_t value,unsigned count=8) {
        for(unsigned i=0;i<count;++i) bytes[offset+i]=uint8_t(value>>(i*8));
    }

    bool checkBytes(std::span<const uint8_t> actual,std::span<const uint8_t> expected,
                    const char *variant,const char *section,size_t base=0) {
        if(actual.size()!=expected.size()) {
            std::cerr<<variant<<": "<<section<<" tamaño="<<actual.size()
                     <<" esperado="<<expected.size()<<'\n';return false;
        }
        for(size_t i=0;i<expected.size();++i) if(actual[i]!=expected[i]) {
            std::cerr<<variant<<": "<<section<<" byte="<<base+i
                     <<" valor="<<unsigned(actual[i])<<" esperado="<<unsigned(expected[i])<<'\n';
            return false;
        }
        return true;
    }

    // GOW-Port: contrato independiente del exportador para el freeze v8 procedural.
    // Ambos contextos preceden a VRAM (offset 364); las cuatro colas GIF vacías
    // y Q=1 siguen a VRAM. Validar todo evita aceptar registros que GIF sobrescribe.
    bool checkFrozen(std::span<const uint8_t> frozen,std::span<const uint8_t> vram,const char *variant) {
        if(frozen.size()!=PS2_GS_VRAM_SIZE+448 || vram.size()!=PS2_GS_VRAM_SIZE) return false;
        const std::string_view fixture(variant);
        const bool feedback=!fixture.starts_with("oraculo_");
        const bool fst=fixture=="oraculo_bilinear";
        const bool linear=feedback?!fixture.starts_with("nearest"):fst || fixture=="oraculo_bilinear_stq";
        const uint64_t exponent=feedback?10:fst?1:2;
        const uint64_t tex0=(feedback&&!fixture.starts_with("disjoint")?0ull:8192ull)|
            (8ull<<14)|(exponent<<26)|(exponent<<30)|(1ull<<34)|(feedback?0ull:1ull<<35);
        const uint64_t tex1=linear?0x60:0,clamp=feedback||fst?5:0;
        const uint64_t scissor=feedback?(511ull<<16)|(447ull<<48):(15ull<<16)|(15ull<<48);
        const uint64_t test=feedback?0x31001:0x30000;
        const uint64_t frame=(8ull<<16)|(feedback?0xff000000ull<<32:0ull);
        constexpr uint64_t zbuf=104ull|(1ull<<24)|(1ull<<32);
        const std::array<uint64_t,12> context={0,tex0,tex1,clamp,0,0,scissor,0, test,0,frame,zbuf};
        constexpr std::array<uint64_t,15> global={0,1,0,0,0,0,0,0,1,0,0,3,0,0,0};
        std::array<uint8_t,364> prefix{};
        storeWord(prefix,0,8,4);
        for(size_t i=0;i<global.size();++i) storeWord(prefix,4+i*8,global[i]);
        for(size_t c=0;c<2;++c) for(size_t i=0;i<context.size();++i)
            storeWord(prefix,124+(c*context.size()+i)*8,context[i]);
        storeWord(prefix,316,0x3f80000080808080ull); // RGBAQ; vértice/cursor/registro obsoleto a cero.
        std::array<uint8_t,84> suffix{};
        storeWord(suffix,80,0x3f800000u,4);
        return checkBytes(frozen.first(prefix.size()),prefix,variant,"freeze inicial") &&
            checkBytes(frozen.subspan(prefix.size(),vram.size()),vram,variant,"VRAM inicial",prefix.size()) &&
            checkBytes(frozen.last(suffix.size()),suffix,variant,"colas GIF/Q",prefix.size()+vram.size());
    }

    std::array<uint8_t,8192> expectedRegisters() {
        // GOW-Port: bloque privilegiado completo del patrón 512x448, no solo
        // igualdad entre sus tres copias. PMODE=0 también conserva el End VRAM.
        std::array<uint8_t,8192> registers{};
        storeWord(registers,0,1); // PMODE: circuito de lectura 1 habilitado.
        storeWord(registers,0x10,0x20006000); // SMODE1.
        storeWord(registers,0x70,8ull<<9); // DISPFB1: CT32, base cero, pitch 512.
        storeWord(registers,0x80,(511ull<<32)|(447ull<<44)); // DISPLAY1: 512x448.
        storeWord(registers,0x1000,0x55190000); // CSR del patrón.
        return registers;
    }

    bool verify(const std::filesystem::path &directory,const char *variant) {
        const auto name=std::string("feedback_gs_")+variant;
        const bool feedback=!std::string(variant).starts_with("oraculo_");
        const bool texflush=std::string(variant).ends_with("_texflush");
        const bool scissor=std::string(variant).ends_with("_scissor");
        gow_gs_replay::Reader capture(directory/(name+".bin"));
        gow_gs_replay::Record record; gow_gs_replay::Snapshot initial,expected;
        bool hasInitial=false,hasEnd=false;
        unsigned submissions=0,invalidations=0;
        while(capture.next(record)) {
            if(record.op==gow_gs_replay::Op::Initial) hasInitial=gow_gs_replay::decodeSnapshot(record,initial);
            if(record.op==gow_gs_replay::Op::End) hasEnd=gow_gs_replay::decodeSnapshot(record,expected);
            if(feedback && record.op==gow_gs_replay::Op::Submit) {
                GSPrimitiveBatch batch{};
                if(!gow_gs_replay::pod(record,batch) || batch.vertexCount!=2 || submissions>=2 ||
                   batch.state.context.scissor.x1!=(scissor && submissions==1?510:511) ||
                   batch.vertices[1].x>64 || batch.vertices[1].y!=416) return false;
                ++submissions;
            }
            if(record.op==gow_gs_replay::Op::TextureFlush) {
                if(submissions!=1 || !record.data.empty()) return false;
                ++invalidations;
            }
        }
        if(!hasInitial || !hasEnd || !capture.error.empty() ||
           initial.vram.size()!=PS2_GS_VRAM_SIZE || expected.vram.size()!=PS2_GS_VRAM_SIZE) return false;
        if(feedback && (submissions!=2 || invalidations!=unsigned(texflush))) return false;
        std::ifstream input(directory/(name+".gs"),std::ios::binary|std::ios::ate);
        if(!input || input.tellg()<0 || input.tellg()>5*1024*1024) return false;
        DumpReader dump;dump.data.resize(size_t(input.tellg()));input.seekg(0);
        if(!input.read(reinterpret_cast<char*>(dump.data.data()),dump.data.size())) return false;
        if(dump.number(4)!=0 || dump.number(4)!=PS2_GS_VRAM_SIZE+448) return false;
        const auto frozen=dump.take(PS2_GS_VRAM_SIZE+448);
        if(!dump.good || !checkFrozen(frozen,initial.vram,variant)) return false;
        const auto registers=dump.take(8192);
        const auto wantedRegisters=expectedRegisters();
        if(!dump.good || !checkBytes(registers,wantedRegisters,variant,"registros privilegiados iniciales")) return false;
        if(dump.number(1)!=0 || dump.number(1)!=3) return false;
        const auto packetSize=dump.number(4);
        if(!packetSize || packetSize%16 || packetSize>1024*1024) return false;
        const auto packet=dump.take(packetSize);
        // GOW-Port: comprobar la separación incluso si no altera el End CPU de este patrón.
        // La equivalencia de imágenes por sí sola no detectaría un TEXFLUSH perdido.
        if(feedback) {
            if(packet.size()<16) return false;
            auto word=[&](size_t offset) {
                uint64_t value=0;
                for(unsigned i=0;i<8;++i) value|=uint64_t(packet[offset+i])<<(i*8);
                return value;
            };
            const uint64_t expectedTag=(packet.size()/16-1)|(1ull<<15)|(1ull<<60);
            if(word(0)!=expectedTag || word(8)!=0xe) return false;
            unsigned gifInvalidations=0,scissors=0,vertices=0;
            for(size_t offset=16;offset<packet.size();offset+=16) {
                const auto address=word(offset+8),value=word(offset);
                if(address==0x05) ++vertices;
                if(address==0x3f) {
                    if(value || vertices!=2) return false;
                    ++gifInvalidations;
                }
                if(address==0x40) {
                    const uint64_t expectedScissor=(uint64_t(scissor && scissors==1?510:511)<<16)|(447ull<<48);
                    if(value!=expectedScissor || (scissors==1 && vertices!=2)) return false;
                    ++scissors;
                }
            }
            if(vertices!=4 || gifInvalidations!=unsigned(texflush) || scissors!=(scissor?2u:1u)) return false;
        }
        for(unsigned field=0;field<2;++field) {
            if(dump.number(1)!=3) return false;
            const auto repeated=dump.take(8192);
            if(!dump.good || !checkBytes(repeated,wantedRegisters,variant,
                   field?"registros privilegiados campo 1":"registros privilegiados campo 0") ||
               dump.number(1)!=1 || dump.number(1)!=field) return false;
        }
        if(!dump.good || dump.offset!=dump.data.size()) return false;
        auto vram=initial.vram;
        GS gs;gs.setRasterBackend(std::make_unique<GSCpuBackend>());
        gs.init(vram.data(),uint32_t(vram.size()));
        std::copy(initial.vram.begin(),initial.vram.end(),vram.begin());
        gs.processGIFPacket(packet.data(),packetSize,GifPathId::Path3);
        size_t different=0;
        for(size_t i=0;i<vram.size();++i) different+=vram[i]!=expected.vram[i];
        const bool pending=gs.hasPendingGIFPacket(GifPathId::Path3);
        std::cout<<variant<<": GS freeze inicial exacto; GIF vs End CPU bytes="<<different
                 <<" pending="<<pending<<'\n';
        return different==0 && !pending;
    }
}

#ifdef _WIN32
int wmain(int argc,wchar_t **argv)
#else
int main(int argc,char **argv)
#endif
{
    if(argc!=2 && argc!=3) return 2;
    if(argc==3 && std::filesystem::path(argv[2])=="--oraculos") {
        for(const char *variant:{"oraculo_bilinear","oraculo_negativos","oraculo_limites","oraculo_bilinear_stq"})
            if(!verify(std::filesystem::path(argv[1]),variant)) return 1;
    } else if(argc==3 && std::filesystem::path(argv[2])=="--separaciones") {
        for(const char *variant:{"self","disjoint","nearest","self_texflush","disjoint_texflush","nearest_texflush",
                                "self_scissor","disjoint_scissor","nearest_scissor"})
            if(!verify(std::filesystem::path(argv[1]),variant)) return 1;
    } else if(argc==3) {
        return 2;
    } else for(const char *variant:{"self","disjoint","nearest"})
        if(!verify(std::filesystem::path(argv[1]),variant)) return 1;
    return 0;
}
