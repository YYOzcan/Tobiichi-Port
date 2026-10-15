// COP2 macro-mode dispatch for the EE reference interpreter (tables from PCSX2 R5900OpcodeTables.cpp, GPL-3.0+).
#include "Common.h"
#include "VUmicro.h"

void VADDx(); void VADDy(); void VADDz(); void VADDw(); void VSUBx(); void VSUBy(); void VSUBz(); void VSUBw();
void VMADDx(); void VMADDy(); void VMADDz(); void VMADDw(); void VMSUBx(); void VMSUBy(); void VMSUBz(); void VMSUBw();
void VMAXx(); void VMAXy(); void VMAXz(); void VMAXw(); void VMINIx(); void VMINIy(); void VMINIz(); void VMINIw();
void VMULx(); void VMULy(); void VMULz(); void VMULw(); void VMULq(); void VMAXi(); void VMULi(); void VMINIi();
void VADDq(); void VMADDq(); void VADDi(); void VMADDi(); void VSUBq(); void VMSUBq(); void VSUBi(); void VMSUBi();
void VADD(); void VMADD(); void VMUL(); void VMAX(); void VSUB(); void VMSUB(); void VOPMSUB(); void VMINI();
void VIADD(); void VISUB(); void VIADDI(); void VIAND(); void VIOR();
static void VCALLMS() {}  // VU0 micro mode is not used by the reference runs
static void VCALLMSR() {}
void VADDAx(); void VADDAy(); void VADDAz(); void VADDAw(); void VSUBAx(); void VSUBAy(); void VSUBAz(); void VSUBAw();
void VMADDAx(); void VMADDAy(); void VMADDAz(); void VMADDAw(); void VMSUBAx(); void VMSUBAy(); void VMSUBAz(); void VMSUBAw();
void VITOF0(); void VITOF4(); void VITOF12(); void VITOF15(); void VFTOI0(); void VFTOI4(); void VFTOI12(); void VFTOI15();
void VMULAx(); void VMULAy(); void VMULAz(); void VMULAw(); void VMULAq(); void VABS(); void VMULAi(); void VCLIPw();
void VADDAq(); void VMADDAq(); void VADDAi(); void VMADDAi(); void VSUBAq(); void VMSUBAq(); void VSUBAi(); void VMSUBAi();
void VADDA(); void VMADDA(); void VMULA(); void VSUBA(); void VMSUBA(); void VOPMULA(); void VNOP();
void VMOVE(); void VMR32(); void VLQI(); void VSQI(); void VLQD(); void VSQD();
void VDIV(); void VSQRT(); void VRSQRT(); void VWAITQ(); void VMTIR(); void VMFIR(); void VILWR(); void VISWR();
void VRNEXT(); void VRGET(); void VRINIT(); void VRXOR();

static void COP2_Unknown() {}
static void COP2_SPECIAL2();

static void (*const Int_COP2SPECIAL1PrintTable[64])() =
{
 VADDx,       VADDy,       VADDz,       VADDw,       VSUBx,        VSUBy,        VSUBz,        VSUBw,
 VMADDx,      VMADDy,      VMADDz,      VMADDw,      VMSUBx,       VMSUBy,       VMSUBz,       VMSUBw,
 VMAXx,       VMAXy,       VMAXz,       VMAXw,       VMINIx,       VMINIy,       VMINIz,       VMINIw,
 VMULx,       VMULy,       VMULz,       VMULw,       VMULq,        VMAXi,        VMULi,        VMINIi,
 VADDq,       VMADDq,      VADDi,       VMADDi,      VSUBq,        VMSUBq,       VSUBi,        VMSUBi,
 VADD,        VMADD,       VMUL,        VMAX,        VSUB,         VMSUB,        VOPMSUB,      VMINI,
 VIADD,       VISUB,       VIADDI,      COP2_Unknown,VIAND,        VIOR,         COP2_Unknown, COP2_Unknown,
 VCALLMS,     VCALLMSR,    COP2_Unknown,COP2_Unknown,COP2_SPECIAL2,COP2_SPECIAL2,COP2_SPECIAL2,COP2_SPECIAL2,
};

static void (*const Int_COP2SPECIAL2PrintTable[128])() =
{
 VADDAx      ,VADDAy      ,VADDAz      ,VADDAw      ,VSUBAx      ,VSUBAy      ,VSUBAz      ,VSUBAw,
 VMADDAx     ,VMADDAy     ,VMADDAz     ,VMADDAw     ,VMSUBAx     ,VMSUBAy     ,VMSUBAz     ,VMSUBAw,
 VITOF0      ,VITOF4      ,VITOF12     ,VITOF15     ,VFTOI0      ,VFTOI4      ,VFTOI12     ,VFTOI15,
 VMULAx      ,VMULAy      ,VMULAz      ,VMULAw      ,VMULAq      ,VABS        ,VMULAi      ,VCLIPw,
 VADDAq      ,VMADDAq     ,VADDAi      ,VMADDAi     ,VSUBAq      ,VMSUBAq     ,VSUBAi      ,VMSUBAi,
 VADDA       ,VMADDA      ,VMULA       ,COP2_Unknown,VSUBA       ,VMSUBA      ,VOPMULA     ,VNOP,
 VMOVE       ,VMR32       ,COP2_Unknown,COP2_Unknown,VLQI        ,VSQI        ,VLQD        ,VSQD,
 VDIV        ,VSQRT       ,VRSQRT      ,VWAITQ      ,VMTIR       ,VMFIR       ,VILWR       ,VISWR,
 VRNEXT      ,VRGET       ,VRINIT      ,VRXOR       ,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,
 COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,
 COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,
 COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,
 COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,
 COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,
 COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,
 COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,COP2_Unknown,
};


static void COP2_SPECIAL2()
{
    Int_COP2SPECIAL2PrintTable[(cpuRegs.code & 0x3) | ((cpuRegs.code >> 4) & 0x7c)]();
}

namespace pcsx2vu0
{
    void special(u32 code)
    {
        cpuRegs.code = code;
        Int_COP2SPECIAL1PrintTable[code & 0x3F]();
    }
    u32 *vf(int index) { return vuRegs[0].VF[index].UL; }
    u32 &vi(int index) { return vuRegs[0].VI[index].UL; }
    u32 *acc() { return vuRegs[0].ACC.UL; }
}
