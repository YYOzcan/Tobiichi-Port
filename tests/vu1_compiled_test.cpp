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
constexpr uint32_t specialStart = 0x1000u;
constexpr uint32_t zeroStart = 0x1200u; // GOW-Port: VF0/VI0 tras una escritura del programa
constexpr uint32_t abnormalStart = 0x1300u; // GOW-Port: FMAC escalar (producto que desborda) y lectura en el mismo bloque
constexpr uint32_t upper(uint32_t op, uint32_t dest, uint32_t ft, uint32_t fs, uint32_t fd) {
    return op | (dest<<21) | (ft<<16) | (fs<<11) | (fd<<6);
}
// Especiales de la unidad superior (ITOF/FTOI 0x10-0x17, ABS 0x1D, CLIP 0x1F).
constexpr uint32_t special(uint32_t code, uint32_t dest, uint32_t ft, uint32_t fs) {
    return (code&3u) | 0x3cu | ((code>>2)<<6) | (fs<<11) | (ft<<16) | (dest<<21);
}
constexpr uint32_t iaddiu(uint32_t it, uint32_t imm) {
    return (0x08u<<25) | (it<<16) | (imm&0x7ffu) | (((imm>>11)&0xfu)<<21);
}
constexpr uint32_t sq(uint32_t dest, uint32_t fs, uint32_t imm) {
    return (1u<<25) | (dest<<21) | (fs<<11) | (imm&0x7ffu); // SQ.dest vfs, imm(vi0)
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
    // GOW-Port: ITOF/FTOI/ABS (con SSE en el código compilado), SQ con DEST parcial, lectores de flags que el
    // código compilado trata en línea (FCAND, FCGET, FMAND, FMEQ) y BAL, JR y JALR.
    constexpr uint32_t base = specialStart/8u;
    const std::array<std::array<uint32_t,2>,30> sp{{
        {iaddiu(4u,0x7fffu),special(0x15u,0xfu,6u,1u)},  // FTOI4 vf6,vf1
        {iaddiu(8u,base+25u),special(0x17u,0xeu,7u,2u)}, // FTOI15.xyz vf7,vf2
        {iaddiu(11u,base+28u),special(0x12u,0xdu,8u,3u)},// ITOF12.xyw vf8,vf3
        {lowerNop,special(0x1du,0xau,9u,1u)},            // ABS.xz vf9,vf1
        {sq(0xeu,6u,2u),special(0x14u,0xfu,10u,2u)},     // FTOI0 vf10,vf2 | SQ.xyz vf6
        {sq(0x5u,7u,3u),special(0x10u,0xfu,11u,3u)},     // ITOF0 vf11,vf3 | SQ.yw vf7
        {sq(0xfu,8u,4u),special(0x13u,0x2u,12u,3u)},     // ITOF15.z vf12,vf3 | SQ vf8
        {sq(0x9u,9u,5u),special(0x11u,0xfu,13u,3u)},     // ITOF4 vf13,vf3 | SQ.xw vf9
        {sq(0xfu,10u,6u),special(0x16u,0x6u,14u,1u)},    // FTOI12.yz vf14,vf1 | SQ vf10
        {sq(0x6u,11u,7u),special(0x1fu,0xeu,2u,1u)},     // CLIPw.xyz vf1,vf2 | SQ.yz vf11
        {(0x12u<<25)|0x3fu,nop},                         // FCAND vi1,0x3f: el CLIP aún no es visible
        {(0x1cu<<25)|(2u<<16),upper(0x2au,0xfu,2u,1u,15u)}, // FCGET vi2 | MUL vf15,vf1,vf2
        {lowerNop,nop},{lowerNop,nop},{lowerNop,nop},
        {(0x1au<<25)|(3u<<16)|(4u<<11),nop},             // FMAND vi3,vi4
        {(0x18u<<25)|(5u<<16)|(4u<<11),nop},             // FMEQ vi5,vi4
        {(0x12u<<25)|0xffffffu,nop},                     // FCAND vi1,0xffffff
        {(0x1cu<<25)|(13u<<16),nop},                     // FCGET vi13
        {(0x21u<<25)|(6u<<16)|2u,nop},                   // BAL vi6,+2: al par 22
        {iaddiu(7u,11u),nop},                            // ranura de retardo
        {iaddiu(7u,99u),nop},                            // se omite
        {(0x24u<<25)|(8u<<11),nop},                      // JR vi8: al par 25
        {iaddiu(9u,5u),nop},                             // ranura de retardo
        {iaddiu(9u,77u),nop},                            // se omite
        {(0x25u<<25)|(10u<<16)|(11u<<11),nop},           // JALR vi10,vi11: al par 28
        {iaddiu(12u,3u),nop},                            // ranura de retardo
        {iaddiu(12u,88u),nop},                           // se omite
        {lowerNop,nop|e},
        {lowerNop,nop},
    }};
    std::memcpy(code.data()+specialStart,sp.data(),sizeof(sp));
    // GOW-Port: LQ escribe VF0 (el hardware lo ignora); el par siguiente debe leer VF0 = (0,0,0,1).
    const std::array<std::array<uint32_t,2>,4> zero{{
        {(0xfu<<21)|1u,nop},                 // LQ.xyzw vf00,1(vi00)
        {lowerNop,upper(0x28u,15,0,0,4)},    // ADD.xyzw vf04,vf00,vf00
        {lowerNop,nop|e},
        {lowerNop,nop},
    }};
    std::memcpy(code.data()+zeroStart,zero.data(),sizeof(zero));
    // GOW-Port: MADD.x con ACC = -max y un producto que desborda en float (ruta escalar; con redondeo hacia cero
    // queda en el máximo); el ADD.x siguiente lee vf3 en el mismo bloque y debe dar lo mismo que el intérprete.
    const std::array<std::array<uint32_t,2>,4> abnormal{{
        {lowerNop,upper(0x29u,8,2,1,3)},     // MADD.x vf03,vf01,vf02
        {lowerNop,upper(0x28u,8,0,3,4)},     // ADD.x vf04,vf03,vf00
        {lowerNop,nop|e},
        {lowerNop,nop},
    }};
    std::memcpy(code.data()+abnormalStart,abnormal.data(),sizeof(abnormal));
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
bool abnormalCases() {
    PS2Memory mem;
    if(!mem.initialize()) return false;
    GS gs; gs.init(mem.getGSVRAM(),4u*1024u*1024u,&mem.gs());
    const auto code=program();
    std::memcpy(mem.getVU1Code(),code.data(),code.size());
    const auto runAbnormal=[&](bool compiled,bool queues) {
        std::memset(mem.getVU1Data(),0,PS2_VU1_DATA_SIZE);
        VU1Interpreter vu;
        vu.setDirectRegisterWrites(!queues);
        vu.setCompiledProgramsEnabled(compiled);
        vu.state().acc[0]=-std::numeric_limits<float>::max();
        vu.state().vf[1][0]=18446744073709551616.f; // 2^64
        vu.state().vf[2][0]=2.767e19f;              // producto ~1,5 * max: desborda en float
        vu.execute(mem.getVU1Code(),PS2_VU1_CODE_SIZE,mem.getVU1Data(),PS2_VU1_DATA_SIZE,gs,&mem,abnormalStart,0,0,65536u);
        return Result{vu.state(),{mem.getVU1Data(),mem.getVU1Data()+PS2_VU1_DATA_SIZE},vu.lastRunHitBudget()};
    };
    for(bool queues:{false,true}) {
        const auto ref=runAbnormal(false,queues);
        const auto got=runAbnormal(true,queues);
        if(!same(ref,got)) {
            std::fprintf(stderr,"FMAC escalar en bloque distinta: colas=%d vf3.x=%08x/%08x vf4.x=%08x/%08x\n",queues,
                bits(ref.state.vf[3][0]),bits(got.state.vf[3][0]),bits(ref.state.vf[4][0]),bits(got.state.vf[4][0]));
            return false;
        }
    }
    std::printf("VU1 FMAC escalar en bloque: 2 casos exactos (producto que desborda y lectura posterior)\n");
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
Result runSpecial(PS2Memory &mem,GS &gs,bool compiled,bool queues,const uint32_t (&v)[12],uint32_t budget,bool resume) {
    std::memset(mem.getVU1Data(),0,PS2_VU1_DATA_SIZE);
    VU1Interpreter vu;
    vu.setDirectRegisterWrites(!queues);
    vu.setCompiledProgramsEnabled(compiled);
    auto &s=vu.state();
    for(unsigned c=0;c<4u;++c) {
        s.vf[1][c]=fromBits(v[c]);
        s.vf[2][c]=fromBits(v[4u+c]);
        s.vf[3][c]=fromBits(v[8u+c]);
    }
    vu.execute(mem.getVU1Code(),PS2_VU1_CODE_SIZE,mem.getVU1Data(),PS2_VU1_DATA_SIZE,gs,&mem,specialStart,0,0,budget);
    if(resume) for(unsigned i=0;i<64u && vu.lastRunHitBudget();++i)
        vu.resume(mem.getVU1Code(),PS2_VU1_CODE_SIZE,mem.getVU1Data(),PS2_VU1_DATA_SIZE,gs,&mem,0,0,64u);
    return {vu.state(),{mem.getVU1Data(),mem.getVU1Data()+PS2_VU1_DATA_SIZE},vu.lastRunHitBudget()};
}
bool specialCases() {
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
    // Cero con signo, subnormales, 1, ±2^31 y vecinos (saturación de FTOI), máximos, Inf, NaN y enteros límite.
    const uint32_t limits[]={0u,0x80000000u,0x00000001u,0x807fffffu,0x00800000u,0x3f800000u,0xbfc00000u,
        0x4effffffu,0x4f000000u,0xceffffffu,0xcf000000u,0xcf000001u,0x46fffe00u,0x7f7fffffu,0xff7fffffu,
        0x7f800000u,0xff800000u,0x7fc00000u,0xffffffffu,0x7fffffffu,0x01000001u,0x00ffffffu};
    constexpr unsigned count=sizeof(limits)/sizeof(limits[0]);
    unsigned cases=0u;
    const auto check=[&](bool queues,const uint32_t (&v)[12],uint32_t budget,bool resume) {
        const auto ref=runSpecial(mem,gs,false,queues,v,budget,resume);
        const auto got=runSpecial(mem,gs,true,queues,v,budget,resume);
        if(!same(ref,got)) {
            std::fprintf(stderr,"Especiales distintos: colas=%d presupuesto=%u resume=%d vf1=%08x vf2=%08x vf3=%08x "
                "mac=%x/%x clip=%x/%x ciclos=%llu/%llu\n",queues,budget,resume,v[0],v[4],v[8],ref.state.mac,got.state.mac,
                ref.state.clip,got.state.clip,static_cast<unsigned long long>(ref.state.cycles),
                static_cast<unsigned long long>(got.state.cycles));
            return false;
        }
        constexpr int link=static_cast<int>(specialStart/8u);
        if(budget==65536u && (got.budget || got.state.vi[7]!=11 || got.state.vi[9]!=5 || got.state.vi[12]!=3 ||
           got.state.vi[6]!=link+21 || got.state.vi[10]!=link+27)) {
            std::fprintf(stderr,"BAL/JR/JALR: vi7=%d vi9=%d vi12=%d vi6=%d vi10=%d\n",got.state.vi[7],got.state.vi[9],
                got.state.vi[12],got.state.vi[6],got.state.vi[10]);
            return false;
        }
        ++cases; return true;
    };
    for(unsigned mode=0;mode<modes;++mode) {
#if GOW_DIV_MXCSR
        _mm_setcsr((restore.value&~0x8040u)|(mode?0x8040u:0u));
#endif
        for(bool queues:{false,true}) {
            for(unsigned i=0;i<count;++i) {
                uint32_t v[12];
                for(unsigned l=0;l<12u;++l) v[l]=limits[(i+l*5u)%count];
                if(!check(queues,v,65536u,false)) return false;
            }
            std::mt19937 rng(777u);
            for(unsigned trial=0;trial<200u;++trial) {
                uint32_t v[12];
                for(unsigned l=0;l<12u;++l) v[l]=trial%2u ? static_cast<uint32_t>(rng()) : limits[rng()%count];
                if(!check(queues,v,65536u,false)) return false;
            }
            for(uint32_t budget:{0u,1u,3u,7u,12u,20u}) for(bool resume:{false,true}) {
                uint32_t v[12];
                for(unsigned l=0;l<12u;++l) v[l]=limits[(budget+l*3u)%count];
                if(!check(queues,v,budget,resume)) return false;
            }
        }
    }
    std::printf("VU1 especiales: %u casos exactos (ITOF/FTOI/ABS, SQ parcial, FCAND/FCGET/FMAND/FMEQ, BAL/JR/JALR)\n",cases);
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
    if(!abnormalCases()) return 1;
    if(!divCases()) return 1;
    if(!specialCases()) return 1;
    return 0;
}
