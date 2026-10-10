// GOW-Port: programa procedural de VU1, sin microcódigo del juego. Se compila con el generador real
// para comparar bloques, pares, fallback por palabras modificadas y cortes/reanudaciones por presupuesto.
#include "runtime/ps2_memory.h"
#include "runtime/ps2_vu1.h"
#include "runtime/gs/gs_frontend.h"
#include <array>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <limits>
#include <random>
#include <vector>
#if defined(_M_X64) || defined(_M_IX86) || defined(__x86_64__) || defined(__i386__)
#include <xmmintrin.h>
#define GOW_DIV_MXCSR 1
#else
#define GOW_DIV_MXCSR 0
#endif

namespace {
constexpr uint32_t nop = 0x2ffu, lowerNop = 0x8000033cu, e = 0x40000000u;
constexpr uint32_t divStart = 128u, divPairs = 14u, divBytes = divPairs * 8u;
constexpr uint32_t zeroStart = 0x1000u; // GOW-Port: VF0/VI0 tras una escritura del programa
constexpr uint32_t upper(uint32_t op, uint32_t dest, uint32_t ft, uint32_t fs, uint32_t fd) {
    return op | (dest<<21) | (ft<<16) | (fs<<11) | (fd<<6);
}
std::vector<uint8_t> program() {
    std::vector<uint8_t> code(PS2_VU1_CODE_SIZE);
    const std::array<std::array<uint32_t,2>,10> pairs{{
        {lowerNop,upper(0x29u,8,2,1,3)}, // MADD.x: producto subnormal, suma normal.
        {lowerNop,nop},
        {lowerNop,upper(0x2au,8,5,5,4)}, // MUL.x pisa MAC, conservando los bits acumulados del producto.
        {(0x08u<<25)|(1u<<16)|7u,nop}, // IADDIU vi1,vi0,7
        {(1u<<25)|(0xfu<<21)|(3u<<11),nop}, // SQ vf3,0(vi0)
        {(0x20u<<25)|2u,nop}, // B: salta a 64 tras la ranura de retardo.
        {(0x08u<<25)|(2u<<16)|3u,nop},
        {(0x08u<<25)|(2u<<16)|9u,nop}, // Se omite.
        {lowerNop,nop|e},
        {lowerNop,nop},
    }};
    std::memcpy(code.data(),pairs.data(),sizeof(pairs));
    // GOW-Port: los 16 selectores de DIV, Q antes/despues de WAITQ y flags D/I.
    for(uint32_t selector=0;selector<16u;++selector) {
        std::array<std::array<uint32_t,2>,divPairs> div{};
        for(auto &pair:div) pair={lowerNop,nop};
        const uint32_t fsf=selector&3u, ftf=selector>>2;
        div[0]={0x800003bcu|(1u<<11)|(2u<<16)|(fsf<<21)|(ftf<<23),upper(0x1cu,15,0,4,3)};
        div[1]={lowerNop,upper(0x1cu,15,0,4,5)};
        div[2]={0x800003bfu,nop}; // WAITQ: espera a Q y a los flags D/I.
        div[3]={lowerNop,upper(0x1cu,15,0,4,6)};
        div[12]={lowerNop,nop|e};
        std::memcpy(code.data()+divStart+selector*divBytes,div.data(),sizeof(div));
    }
    // GOW-Port: LQ escribe VF0 (el hardware lo ignora); el par siguiente debe leer VF0 = (0,0,0,1).
    const std::array<std::array<uint32_t,2>,4> zero{{
        {(0xfu<<21)|1u,nop},                 // LQ.xyzw vf00,1(vi00)
        {lowerNop,upper(0x28u,15,0,0,4)},    // ADD.xyzw vf04,vf00,vf00
        {lowerNop,nop|e},
        {lowerNop,nop},
    }};
    std::memcpy(code.data()+zeroStart,zero.data(),sizeof(zero));
    return code;
}
struct Result {
    VU1State state;
    std::vector<uint8_t> data;
    bool budget=false;
};
Result run(bool compiled, bool queues, unsigned mutation, uint32_t budget, bool resume) {
    PS2Memory mem;
    if(!mem.initialize()) throw "initialize";
    GS gs; gs.init(mem.getGSVRAM(),4u*1024u*1024u,&mem.gs());
    const auto code=program();
    std::memcpy(mem.getVU1Code(),code.data(),code.size());
    if(mutation==1) mem.write32(0x11008004u,upper(0x28u,8,2,1,3)); // ADD: par compilado ya no coincide.
    if(mutation==2) mem.write32(0x11008004u,0x30u); // Reservada: no ejecuta ni avanza.
    VU1Interpreter vu;
    vu.setDirectRegisterWrites(!queues);
    vu.setCompiledProgramsEnabled(compiled);
    vu.state().acc[0]=1.f;
    vu.state().vf[1][0]=std::numeric_limits<float>::min();
    vu.state().vf[2][0]=0.5f;
    vu.state().vf[5][0]=1.f;
    vu.execute(mem.getVU1Code(),PS2_VU1_CODE_SIZE,mem.getVU1Data(),PS2_VU1_DATA_SIZE,gs,&mem,0,0,0,budget);
    if(resume) for(unsigned i=0;i<64 && vu.lastRunHitBudget();++i)
        vu.resume(mem.getVU1Code(),PS2_VU1_CODE_SIZE,mem.getVU1Data(),PS2_VU1_DATA_SIZE,gs,&mem,0,0,64);
    return {vu.state(),{mem.getVU1Data(),mem.getVU1Data()+PS2_VU1_DATA_SIZE},vu.lastRunHitBudget()};
}
bool same(const Result &a,const Result &b) {
    const auto &x=a.state; const auto &y=b.state;
    return std::memcmp(x.vf,y.vf,sizeof(x.vf))==0 && std::memcmp(x.vi,y.vi,sizeof(x.vi))==0 &&
        std::memcmp(x.acc,y.acc,sizeof(x.acc))==0 && std::memcmp(&x.q,&y.q,sizeof(x.q))==0 &&
        std::memcmp(&x.p,&y.p,sizeof(x.p))==0 && std::memcmp(&x.i,&y.i,sizeof(x.i))==0 && x.r==y.r &&
        x.mac==y.mac && x.status==y.status && x.clip==y.clip && x.pc==y.pc && x.cycles==y.cycles &&
        x.ebit==y.ebit && x.branchPending==y.branchPending && x.branchTarget==y.branchTarget &&
        x.branchDelay==y.branchDelay && x.stoppedByD==y.stoppedByD && x.stoppedByT==y.stoppedByT &&
        a.budget==b.budget && a.data==b.data;
}
uint32_t bits(float value) {
    uint32_t out; std::memcpy(&out,&value,sizeof(out)); return out;
}
float fromBits(uint32_t value) {
    float out; std::memcpy(&out,&value,sizeof(out)); return out;
}
Result runDiv(PS2Memory &mem,GS &gs,bool compiled,bool queues,uint32_t selector,
              uint32_t num,uint32_t den,uint32_t budget,bool resume) {
    std::memset(mem.getVU1Data(),0,PS2_VU1_DATA_SIZE);
    VU1Interpreter vu;
    vu.setDirectRegisterWrites(!queues);
    vu.setCompiledProgramsEnabled(compiled);
    auto &s=vu.state();
    for(unsigned c=0;c<4u;++c) {
        s.vf[1][c]=static_cast<float>(2u+c);
        s.vf[2][c]=static_cast<float>(7u+c);
        s.vf[4][c]=1.f;
    }
    s.vf[1][selector&3u]=fromBits(num);
    s.vf[2][selector>>2]=fromBits(den);
    s.q=3.25f;
    s.status=0x30u; // La division normal debe limpiar D/I anteriores.
    vu.execute(mem.getVU1Code(),PS2_VU1_CODE_SIZE,mem.getVU1Data(),PS2_VU1_DATA_SIZE,
               gs,&mem,divStart+selector*divBytes,0,0,budget);
    if(resume) for(unsigned i=0;i<64u && vu.lastRunHitBudget();++i)
        vu.resume(mem.getVU1Code(),PS2_VU1_CODE_SIZE,mem.getVU1Data(),PS2_VU1_DATA_SIZE,gs,&mem,0,0,64u);
    return {vu.state(),{mem.getVU1Data(),mem.getVU1Data()+PS2_VU1_DATA_SIZE},vu.lastRunHitBudget()};
}
bool zeroRegisterCases() {
    PS2Memory mem;
    if(!mem.initialize()) return false;
    GS gs; gs.init(mem.getGSVRAM(),4u*1024u*1024u,&mem.gs());
    const auto code=program();
    std::memcpy(mem.getVU1Code(),code.data(),code.size());
    const auto runZero=[&](bool compiled,bool queues) {
        std::memset(mem.getVU1Data(),0,PS2_VU1_DATA_SIZE);
        const float loaded[4]={3.f,5.f,7.f,9.f};
        std::memcpy(mem.getVU1Data()+16,loaded,sizeof(loaded));
        VU1Interpreter vu;
        vu.setDirectRegisterWrites(!queues);
        vu.setCompiledProgramsEnabled(compiled);
        vu.execute(mem.getVU1Code(),PS2_VU1_CODE_SIZE,mem.getVU1Data(),PS2_VU1_DATA_SIZE,gs,&mem,zeroStart,0,0,65536u);
        return Result{vu.state(),{mem.getVU1Data(),mem.getVU1Data()+PS2_VU1_DATA_SIZE},vu.lastRunHitBudget()};
    };
    for(bool queues:{false,true}) {
        const auto ref=runZero(false,queues);
        const auto got=runZero(true,queues);
        if(!same(ref,got) || got.state.vf[4][3]!=2.f || got.state.vf[0][3]!=1.f) {
            std::fprintf(stderr,"VF0 distinta: colas=%d vf4=%g,%g,%g,%g/%g,%g,%g,%g vf0.w=%g/%g\n",queues,
                ref.state.vf[4][0],ref.state.vf[4][1],ref.state.vf[4][2],ref.state.vf[4][3],
                got.state.vf[4][0],got.state.vf[4][1],got.state.vf[4][2],got.state.vf[4][3],
                ref.state.vf[0][3],got.state.vf[0][3]);
            return false;
        }
    }
    std::printf("VU1 VF0/VI0: 2 casos exactos (escritura a VF0 en un par compilado)\n");
    return true;
}
bool divCases() {
    PS2Memory mem;
    if(!mem.initialize()) return false;
    GS gs; gs.init(mem.getGSVRAM(),4u*1024u*1024u,&mem.gs());
    const auto code=program();
    std::memcpy(mem.getVU1Code(),code.data(),code.size());
#if GOW_DIV_MXCSR
    struct Restore { unsigned value=_mm_getcsr(); ~Restore() { _mm_setcsr(value); } } restore;
    constexpr unsigned modes=2u;
#else
    constexpr unsigned modes=1u;
#endif
    const uint32_t limits[]={0u,0x80000000u,0x00000001u,0x807fffffu,0x3f800000u,0xbf800000u,
        0x00800000u,0x80800000u,0x00800001u,0x40000000u,0x7f7fffffu,0xff7fffffu,
        0x7f800000u,0xff800000u,0x7fc00000u,0xffc00000u,0x7f800001u,0xff800001u};
    unsigned cases=0u;
    const auto check=[&](bool queues,uint32_t selector,uint32_t num,uint32_t den,uint32_t budget,bool resume) {
        const auto ref=runDiv(mem,gs,false,queues,selector,num,den,budget,resume);
        const auto got=runDiv(mem,gs,true,queues,selector,num,den,budget,resume);
        if(!same(ref,got)) {
            std::fprintf(stderr,"DIV distinta: selector=%u num=%08x den=%08x colas=%d presupuesto=%u resume=%d "
                "Q=%08x/%08x status=%x/%x ciclos=%llu/%llu\n",selector,num,den,queues,budget,resume,
                bits(ref.state.q),bits(got.state.q),ref.state.status,got.state.status,
                static_cast<unsigned long long>(ref.state.cycles),static_cast<unsigned long long>(got.state.cycles));
            return false;
        }
        if(budget==65536u || resume) {
            // Exponente cero se normaliza a cero; Inf/NaN a maximo, nunca a cero.
            const bool zeroDen=(den&0x7f800000u)==0u, zeroNum=(num&0x7f800000u)==0u;
            const uint32_t di=zeroDen?(zeroNum?0x10u:0x20u):0u;
            if(got.budget || (got.state.status&0xc30u)!=(di|(di<<6))) {
                std::fprintf(stderr,"DIV incompleta o flags D/I incorrectos: status=%x di=%x budget=%d\n",
                    got.state.status,di,got.budget); return false;
            }
            if(zeroDen && bits(got.state.q)!=(((num^den)&0x80000000u)|0x7f7fffffu)) {
                std::fprintf(stderr,"DIV por cero sin saturacion con signo\n"); return false;
            }
            for(unsigned c=0;c<4u;++c)
                if(bits(got.state.vf[3][c])!=bits(3.25f) || bits(got.state.vf[5][c])!=bits(3.25f) ||
                   bits(got.state.vf[6][c])!=bits(got.state.q)) {
                    std::fprintf(stderr,"DIV: Q visible antes de tiempo o WAITQ sin resultado\n"); return false;
                }
        }
        ++cases; return true;
    };
    for(unsigned mode=0;mode<modes;++mode) {
#if GOW_DIV_MXCSR
        _mm_setcsr((restore.value&~0x8040u)|(mode?0x8040u:0u));
#endif
        for(bool queues:{false,true}) for(uint32_t selector=0;selector<16u;++selector) {
            for(uint32_t num:limits) for(uint32_t den:limits)
                if(!check(queues,selector,num,den,65536u,false)) return false;
            std::mt19937 rng(12345u+selector);
            for(unsigned trial=0;trial<80u;++trial)
                if(!check(queues,selector,static_cast<uint32_t>(rng()),static_cast<uint32_t>(rng()),65536u,false)) return false;
            for(uint32_t num:{0u,0x80000000u,0x3f800000u,0xff7fffffu})
                for(uint32_t den:{0u,0x80000000u,0x40000000u,0x00000001u})
                    for(uint32_t budget:{0u,1u,6u,7u,8u,16u}) for(bool resume:{false,true})
                        if(!check(queues,selector,num,den,budget,resume)) return false;
        }
    }
    std::printf("VU1 DIV: %u casos exactos (16 selectores, limites, D/I, WAITQ, FTZ/DAZ y presupuesto/reanudacion)\n",cases);
    return true;
}
}
int main(int argc,char **argv) {
    if(argc==3 && std::strcmp(argv[1],"--write")==0) {
        const auto code=program(); std::ofstream f(argv[2],std::ios::binary);
        f.write(reinterpret_cast<const char*>(code.data()),code.size());
        f.close(); return f ? 0:2;
    }
    unsigned cases=0;
    for(bool queues:{false,true}) for(unsigned mutation:{0u,1u,2u})
        for(uint32_t budget:{0u,1u,4u,8u,65536u}) for(bool resume:{false,true}) {
            const auto ref=run(false,queues,mutation,budget,resume);
            const auto got=run(true,queues,mutation,budget,resume);
            if(!same(ref,got)) {
                std::fprintf(stderr,"VU1 distinta: colas=%d mutacion=%u presupuesto=%u resume=%d status=%x/%x ciclos=%llu/%llu\n",
                    queues,mutation,budget,resume,ref.state.status,got.state.status,
                    static_cast<unsigned long long>(ref.state.cycles),static_cast<unsigned long long>(got.state.cycles));
                return 1;
            }
            if(!mutation && budget==65536u &&
               (got.state.status!=0x140u || got.state.vi[1]!=7 || got.state.vi[2]!=3 || got.state.vf[3][0]!=1.f ||
                got.budget || got.data.size()<4 || std::memcmp(got.data.data(),&got.state.vf[3][0],4))) {
                uint32_t stored=0; std::memcpy(&stored,got.data.data(),4);
                std::fprintf(stderr,"Referencia VU1 incompleta: status=%x vi1=%d vi2=%d vf3=%g datos=%08x budget=%d\n",
                    got.state.status,got.state.vi[1],got.state.vi[2],got.state.vf[3][0],stored,got.budget); return 1;
            }
            ++cases;
        }
    std::printf("VU1 compilada: %u casos exactos (bloques, palabras modificadas, reservada, colas y presupuesto/reanudacion)\n",cases);
    if(!zeroRegisterCases()) return 1;
    if(!divCases()) return 1;
    return 0;
}
