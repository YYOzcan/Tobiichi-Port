// SPDX-FileCopyrightText: 2002-2026 PCSX2 Dev Team
// SPDX-License-Identifier: GPL-3.0+

#include "Common.h"

#include <float.h>

#include "R5900.h"
#include "R5900OpcodeTables.h"
#include "eeref_internal.h"



static __fi bool _add64_Overflow( s64 x, s64 y, s64 &ret )
{
	const s64 result = x + y;

	// Let's all give gigaherz a big round of applause for finding this gem,
	// which apparently works, and generates compact/fast x86 code too (the
	// other method below is like 5-10 times slower).

	if( ((~(x^y))&(x^result)) < 0 ) {
		cpuException(0x30, cpuRegs.branch);		// fixme: is 0x30 right for overflow??
		return true;
	}

	// the not-as-fast style!
	//if( ((x >= 0) && (y >= 0) && (result <  0)) ||
	//	((x <  0) && (y <  0) && (result >= 0)) )
	//	cpuException(0x30, cpuRegs.branch);

	ret = result;
	return false;
}

static __fi bool _add32_Overflow( s32 x, s32 y, s64 &ret )
{
	GPR_reg64 result;  result.SD[0] = (s64)x + y;

	// This 32bit method can rely on the MIPS documented method of checking for
	// overflow, whichs imply compares bit 32 (rightmost bit of the upper word),
	// against bit 31 (leftmost of the lower word).

	// If bit32 != bit31 then we have an overflow.
	if( (result.UL[0]>>31) != (result.UL[1] & 1) ) {
		cpuException(0x30, cpuRegs.branch);
		return true;
	}

	ret = result.SD[0];

	return false;
}


const R5900::OPCODE& R5900::GetCurrentInstruction()
{
	const OPCODE* opcode = &R5900::OpcodeTables::tbl_Standard[_Opcode_];

	while( opcode->getsubclass != NULL )
		opcode = &opcode->getsubclass(cpuRegs.code);

	return *opcode;
}

const R5900::OPCODE& R5900::GetInstruction(u32 op)
{
	const OPCODE* opcode = &R5900::OpcodeTables::tbl_Standard[op >> 26];

	while( opcode->getsubclass != NULL )
		opcode = &opcode->getsubclass(op);

	return *opcode;
}

namespace R5900 {
namespace Interpreter {
namespace OpcodeImpl {

void COP2()
{
	//std::string disOut;
	//disR5900Fasm(disOut, cpuRegs.code, cpuRegs.pc);

	//VU0_LOG("%s", disOut.c_str());
	eeref::cop2(cpuRegs.code);
}

void Unknown() {
	CPU_LOG("%8.8lx: Unknown opcode called", cpuRegs.pc);
}

void MMI_Unknown() { Console.Warning("Unknown MMI opcode called"); }
void COP0_Unknown() { Console.Warning("Unknown COP0 opcode called"); }
void COP1_Unknown() { Console.Warning("Unknown FPU/COP1 opcode called"); }



/*********************************************************
* Arithmetic with immediate operand                      *
* Format:  OP rt, rs, immediate                          *
*********************************************************/

// Implementation Notes:
//  * It is important that instructions perform overflow checks prior to shortcutting on
//    the zero register (when it is used as a destination).  Overflow exceptions are still
//    handled even though the result is discarded.

// Rt = Rs + Im signed [exception on overflow]
void ADDI()
{
	s64 result;
	bool overflow = _add32_Overflow( cpuRegs.GPR.r[_Rs_].SD[0], _Imm_, result );
	if (overflow || !_Rt_) return;
	cpuRegs.GPR.r[_Rt_].SD[0] = result;
}

// Rt = Rs + Im signed !!! [overflow ignored]
// This instruction is effectively identical to ADDI.  It is not a true unsigned operation,
// but rather it is a signed operation that ignores overflows.
void ADDIU()
{
	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].UD[0] = u64(s64(s32(cpuRegs.GPR.r[_Rs_].UL[0] + u32(s32(_Imm_)))));
}

// Rt = Rs + Im [exception on overflow]
// This is the full 64 bit version of ADDI.  Overflow occurs at 64 bits instead
// of at 32 bits.
void DADDI()
{
	s64 result;
	bool overflow = _add64_Overflow( cpuRegs.GPR.r[_Rs_].SD[0], _Imm_, result );
	if (overflow || !_Rt_) return;
	cpuRegs.GPR.r[_Rt_].SD[0] = result;
}

// Rt = Rs + Im [overflow ignored]
// This instruction is effectively identical to DADDI.  It is not a true unsigned operation,
// but rather it is a signed operation that ignores overflows.
void DADDIU()
{
	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0] + u64(s64(_Imm_));
}
void ANDI() 	{ if (!_Rt_) return; cpuRegs.GPR.r[_Rt_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0] & (u64)_ImmU_; } // Rt = Rs And Im (zero-extended)
void ORI() 	    { if (!_Rt_) return; cpuRegs.GPR.r[_Rt_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0] | (u64)_ImmU_; } // Rt = Rs Or  Im (zero-extended)
void XORI() 	{ if (!_Rt_) return; cpuRegs.GPR.r[_Rt_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0] ^ (u64)_ImmU_; } // Rt = Rs Xor Im (zero-extended)
void SLTI()     { if (!_Rt_) return; cpuRegs.GPR.r[_Rt_].UD[0] = (cpuRegs.GPR.r[_Rs_].SD[0] < (s64)(_Imm_)) ? 1 : 0; } // Rt = Rs < Im (signed)
void SLTIU()    { if (!_Rt_) return; cpuRegs.GPR.r[_Rt_].UD[0] = (cpuRegs.GPR.r[_Rs_].UD[0] < (u64)(_Imm_)) ? 1 : 0; } // Rt = Rs < Im (unsigned)

/*********************************************************
* Register arithmetic                                    *
* Format:  OP rd, rs, rt                                 *
*********************************************************/

// Rd = Rs + Rt		(Exception on Integer Overflow)
void ADD()
{
	s64 result;
	bool overflow = _add32_Overflow( cpuRegs.GPR.r[_Rs_].SD[0], cpuRegs.GPR.r[_Rt_].SD[0], result );
	if (overflow || !_Rd_) return;
	cpuRegs.GPR.r[_Rd_].SD[0] = result;
}

void DADD()
{
	s64 result;
	bool overflow = _add64_Overflow( cpuRegs.GPR.r[_Rs_].SD[0], cpuRegs.GPR.r[_Rt_].SD[0], result );
	if (overflow || !_Rd_) return;
	cpuRegs.GPR.r[_Rd_].SD[0] = result;
}

// Rd = Rs - Rt		(Exception on Integer Overflow)
void SUB()
{
	s64 result;
	bool overflow = _add32_Overflow( cpuRegs.GPR.r[_Rs_].SD[0], -cpuRegs.GPR.r[_Rt_].SD[0], result );
	if (overflow || !_Rd_) return;
	cpuRegs.GPR.r[_Rd_].SD[0] = result;
}

// Rd = Rs - Rt		(Exception on Integer Overflow)
void DSUB()
{
	s64 result;
	bool overflow = _add64_Overflow( cpuRegs.GPR.r[_Rs_].SD[0], -cpuRegs.GPR.r[_Rt_].SD[0], result );
	if (overflow || !_Rd_) return;
	cpuRegs.GPR.r[_Rd_].SD[0] = result;
}

void ADDU() 	{ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = u64(s64(s32(cpuRegs.GPR.r[_Rs_].UL[0]  + cpuRegs.GPR.r[_Rt_].UL[0]))); }	// Rd = Rs + Rt
void DADDU()    { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0]  + cpuRegs.GPR.r[_Rt_].UD[0]; }
void SUBU() 	{ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = u64(s64(s32(cpuRegs.GPR.r[_Rs_].UL[0]  - cpuRegs.GPR.r[_Rt_].UL[0]))); }	// Rd = Rs - Rt
void DSUBU() 	{ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0]  - cpuRegs.GPR.r[_Rt_].UD[0]; }
void AND() 	    { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0]  & cpuRegs.GPR.r[_Rt_].UD[0]; }	// Rd = Rs And Rt
void OR() 	    { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0]  | cpuRegs.GPR.r[_Rt_].UD[0]; }	// Rd = Rs Or  Rt
void XOR() 	    { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0]  ^ cpuRegs.GPR.r[_Rt_].UD[0]; }	// Rd = Rs Xor Rt
void NOR() 	    { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] =~(cpuRegs.GPR.r[_Rs_].UD[0] | cpuRegs.GPR.r[_Rt_].UD[0]); }// Rd = Rs Nor Rt
void SLT()		{ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = (cpuRegs.GPR.r[_Rs_].SD[0] < cpuRegs.GPR.r[_Rt_].SD[0]) ? 1 : 0; }	// Rd = Rs < Rt (signed)
void SLTU()		{ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = (cpuRegs.GPR.r[_Rs_].UD[0] < cpuRegs.GPR.r[_Rt_].UD[0]) ? 1 : 0; }	// Rd = Rs < Rt (unsigned)

/*********************************************************
* Register mult/div & Register trap logic                *
* Format:  OP rs, rt                                     *
*********************************************************/

// Signed division "overflows" on (0x80000000 / -1), here (LO = 0x80000000, HI = 0) is returned by MIPS
// in division by zero on MIPS, it appears that:
// LO gets 1 if rs is negative (and the division is signed) and -1 otherwise.
// HI gets the value of rs.

// Result is stored in HI/LO [no arithmetic exceptions]
void DIV()
{
	if (cpuRegs.GPR.r[_Rs_].UL[0] == 0x80000000 && cpuRegs.GPR.r[_Rt_].UL[0] == 0xffffffff)
	{
		cpuRegs.LO.SD[0] = (s32)0x80000000;
		cpuRegs.HI.SD[0] = (s32)0x0;
	}
    else if (cpuRegs.GPR.r[_Rt_].SL[0] != 0)
    {
        cpuRegs.LO.SD[0] = cpuRegs.GPR.r[_Rs_].SL[0] / cpuRegs.GPR.r[_Rt_].SL[0];
        cpuRegs.HI.SD[0] = cpuRegs.GPR.r[_Rs_].SL[0] % cpuRegs.GPR.r[_Rt_].SL[0];
    }
	else
	{
		cpuRegs.LO.SD[0] = (cpuRegs.GPR.r[_Rs_].SL[0] < 0) ? 1 : -1;
		cpuRegs.HI.SD[0] = cpuRegs.GPR.r[_Rs_].SL[0];
	}
}

// Result is stored in HI/LO [no arithmetic exceptions]
void DIVU()
{
	if (cpuRegs.GPR.r[_Rt_].UL[0] != 0)
	{
		// note: DIVU has no sign extension when assigning back to 64 bits
		// note 2: reference material strongly disagrees. (air)
		cpuRegs.LO.SD[0] = (s32)(cpuRegs.GPR.r[_Rs_].UL[0] / cpuRegs.GPR.r[_Rt_].UL[0]);
		cpuRegs.HI.SD[0] = (s32)(cpuRegs.GPR.r[_Rs_].UL[0] % cpuRegs.GPR.r[_Rt_].UL[0]);
	}
	else
	{
		cpuRegs.LO.SD[0] = -1;
		cpuRegs.HI.SD[0] = cpuRegs.GPR.r[_Rs_].SL[0];
	}
}

// Result is written to both HI/LO and to the _Rd_ (Lo only)
void MULT()
{
	s64 res = (s64)cpuRegs.GPR.r[_Rs_].SL[0] * cpuRegs.GPR.r[_Rt_].SL[0];

	// Sign-extend into 64 bits:
	cpuRegs.LO.SD[0] = (s32)(res & 0xffffffff);
	cpuRegs.HI.SD[0] = (s32)(res >> 32);

	if( _Rd_ ) cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.LO.UD[0];
}

// Result is written to both HI/LO and to the _Rd_ (Lo only)
void MULTU()
{
	u64 res = (u64)cpuRegs.GPR.r[_Rs_].UL[0] * cpuRegs.GPR.r[_Rt_].UL[0];

	// Note: sign-extend into 64 bits even though it's an unsigned mult.
	cpuRegs.LO.SD[0] = (s32)(res & 0xffffffff);
	cpuRegs.HI.SD[0] = (s32)(res >> 32);

	if( _Rd_ ) cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.LO.UD[0];
}

/*********************************************************
* Load higher 16 bits of the first word in GPR with imm  *
* Format:  OP rt, immediate                              *
*********************************************************/
void LUI() {
	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].UD[0] = (s32)(cpuRegs.code << 16);
}

/*********************************************************
* Move from HI/LO to GPR                                 *
* Format:  OP rd                                         *
*********************************************************/
void MFHI() { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.HI.UD[0]; } // Rd = Hi
void MFLO() { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.LO.UD[0]; } // Rd = Lo

/*********************************************************
* Move to GPR to HI/LO & Register jump                   *
* Format:  OP rs                                         *
*********************************************************/
void MTHI() { cpuRegs.HI.UD[0] = cpuRegs.GPR.r[_Rs_].UD[0]; } // Hi = Rs
void MTLO() { cpuRegs.LO.UD[0] = cpuRegs.GPR.r[_Rs_].UD[0]; } // Lo = Rs


/*********************************************************
* Shift arithmetic with constant shift                   *
* Format:  OP rd, rt, sa                                 *
*********************************************************/
void SRA()   { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = (s32)(cpuRegs.GPR.r[_Rt_].SL[0] >> _Sa_); } // Rd = Rt >> sa (arithmetic)
void SRL()   { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = (s32)(cpuRegs.GPR.r[_Rt_].UL[0] >> _Sa_); } // Rd = Rt >> sa (logical) [sign extend!!]
void SLL()   { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = (s32)(cpuRegs.GPR.r[_Rt_].UL[0] << _Sa_); } // Rd = Rt << sa
void DSLL()  { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = (u64)(cpuRegs.GPR.r[_Rt_].UD[0] << _Sa_); }
void DSLL32(){ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = (u64)(cpuRegs.GPR.r[_Rt_].UD[0] << (_Sa_+32));}
void DSRA()  { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = cpuRegs.GPR.r[_Rt_].SD[0] >> _Sa_; }
void DSRA32(){ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = cpuRegs.GPR.r[_Rt_].SD[0] >> (_Sa_+32);}
void DSRL()  { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rt_].UD[0] >> _Sa_; }
void DSRL32(){ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rt_].UD[0] >> (_Sa_+32);}

/*********************************************************
* Shift arithmetic with variant register shift           *
* Format:  OP rd, rt, rs                                 *
*********************************************************/
void SLLV() { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = (s32)(cpuRegs.GPR.r[_Rt_].UL[0] << (cpuRegs.GPR.r[_Rs_].UL[0] &0x1f));} // Rd = Rt << rs
void SRAV() { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = (s32)(cpuRegs.GPR.r[_Rt_].SL[0] >> (cpuRegs.GPR.r[_Rs_].UL[0] &0x1f));} // Rd = Rt >> rs (arithmetic)
void SRLV() { if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = (s32)(cpuRegs.GPR.r[_Rt_].UL[0] >> (cpuRegs.GPR.r[_Rs_].UL[0] &0x1f));} // Rd = Rt >> rs (logical)
void DSLLV(){ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = (u64)(cpuRegs.GPR.r[_Rt_].UD[0] << (cpuRegs.GPR.r[_Rs_].UL[0] &0x3f));}
void DSRAV(){ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].SD[0] = (s64)(cpuRegs.GPR.r[_Rt_].SD[0] >> (cpuRegs.GPR.r[_Rs_].UL[0] &0x3f));}
void DSRLV(){ if (!_Rd_) return; cpuRegs.GPR.r[_Rd_].UD[0] = (u64)(cpuRegs.GPR.r[_Rt_].UD[0] >> (cpuRegs.GPR.r[_Rs_].UL[0] &0x3f));}

/*********************************************************
* Load and store for GPR                                 *
* Format:  OP rt, offset(base)                           *
*********************************************************/

// Implementation Notes Regarding Memory Operations:
//  * It it 'correct' to do all loads into temp variables, even if the destination GPR
//    is the zero reg (which nullifies the result).  The memory needs to be accessed
//    regardless so that hardware registers behave as expected (some clear on read) and
//    so that TLB Misses are handled as expected as well.
//
//  * Low/High varieties of instructions, such as LWL/LWH, do *not* raise Address Error
//    exceptions, since the lower bits of the address are used to determine the portions
//    of the address/register operations.

__noinline static void RaiseAddressError(u32 addr, bool store)
{
	eeref::stop(store ? "address error (store)" : "address error (load)");
}

void LB()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	s8 temp = memRead8(addr);

	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].SD[0] = temp;

	// Force event test on EE counter read to improve read + interrupt syncing. Namely ESPN Games.
	if ((addr & 0xFFFFE000) == 0x10000000)
	{
		intUpdateCPUCycles();
		intEventTest();
	}
}

void LBU()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u8 temp = memRead8(addr);

	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].UD[0] = temp;

	// Force event test on EE counter read to improve read + interrupt syncing. Namely ESPN Games.
	if ((addr & 0xFFFFE000) == 0x10000000)
	{
		intUpdateCPUCycles();
		intEventTest();
	}
}

void LH()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;

	if (addr & 1) [[unlikely]]
		RaiseAddressError(addr, false);

	s16 temp = memRead16(addr);

	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].SD[0] = temp;

	// Force event test on EE counter read to improve read + interrupt syncing. Namely ESPN Games.
	if ((addr & 0xFFFFE000) == 0x10000000)
	{
		intUpdateCPUCycles();
		intEventTest();
	}
}

void LHU()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;

	if (addr & 1) [[unlikely]]
		RaiseAddressError(addr, false);

	u16 temp = memRead16(addr);

	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].UD[0] = temp;

	// Force event test on EE counter read to improve read + interrupt syncing. Namely ESPN Games.
	if ((addr & 0xFFFFE000) == 0x10000000)
	{
		intUpdateCPUCycles();
		intEventTest();
	}
}

void LW()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;

	if (addr & 3) [[unlikely]]
		RaiseAddressError(addr, false);

	u32 temp = memRead32(addr);

	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].SD[0] = (s32)temp;

	// Force event test on EE counter read to improve read + interrupt syncing. Namely ESPN Games.
	if ((addr & 0xFFFFE000) == 0x10000000)
	{
		intUpdateCPUCycles();
		intEventTest();
	}
}

void LWU()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;

	if (addr & 3) [[unlikely]]
		RaiseAddressError(addr, false);

	u32 temp = memRead32(addr);

	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].UD[0] = temp;
}

static const u32 LWL_MASK[4] = { 0xffffff, 0x0000ffff, 0x000000ff, 0x00000000 };
static const u32 LWR_MASK[4] = { 0x000000, 0xff000000, 0xffff0000, 0xffffff00 };
static const u8 LWL_SHIFT[4] = { 24, 16, 8, 0 };
static const u8 LWR_SHIFT[4] = { 0, 8, 16, 24 };

void LWL()
{
	s32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u32 shift = addr & 3;

	u32 mem = memRead32(addr & ~3);

	if (!_Rt_) return;

	// ensure the compiler does correct sign extension into 64 bits by using s32
	cpuRegs.GPR.r[_Rt_].SD[0] =	(s32)((cpuRegs.GPR.r[_Rt_].UL[0] & LWL_MASK[shift]) |
								(mem << LWL_SHIFT[shift]));

	/*
	Mem = 1234.  Reg = abcd
	(result is always sign extended into the upper 32 bits of the Rt)

	0   4bcd   (mem << 24) | (reg & 0x00ffffff)
	1   34cd   (mem << 16) | (reg & 0x0000ffff)
	2   234d   (mem <<  8) | (reg & 0x000000ff)
	3   1234   (mem      ) | (reg & 0x00000000)
	*/
}

void LWR()
{
	s32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u32 shift = addr & 3;

	u32 mem = memRead32(addr & ~3);

	if (!_Rt_) return;

	// Use unsigned math here, and conditionally sign extend below, when needed.
	mem = (cpuRegs.GPR.r[_Rt_].UL[0] & LWR_MASK[shift]) | (mem >> LWR_SHIFT[shift]);

	if( shift == 0 )
	{
		// This special case requires sign extension into the full 64 bit dest.
		cpuRegs.GPR.r[_Rt_].SD[0] =	(s32)mem;
	}
	else
	{
		// This case sets the lower 32 bits of the target register.  Upper
		// 32 bits are always preserved.
		cpuRegs.GPR.r[_Rt_].UL[0] =	mem;
	}

	/*
	Mem = 1234.  Reg = abcd

	0   1234   (mem      ) | (reg & 0x00000000)	[sign extend into upper 32 bits!]
	1   a123   (mem >>  8) | (reg & 0xff000000)
	2   ab12   (mem >> 16) | (reg & 0xffff0000)
	3   abc1   (mem >> 24) | (reg & 0xffffff00)
	*/
}

// dummy variable used as a destination address for writes to the zero register, so
// that the zero register always stays zero.
alignas(16) static GPR_reg m_dummy_gpr_zero;

// Returns the x86 address of the requested GPR, which is safe for writing. (includes
// special handling for returning a dummy var for GPR0(zero), so that it's value is
// always preserved)
static GPR_reg* gpr_GetWritePtr( uint gpr )
{
	return (( gpr == 0 ) ? &m_dummy_gpr_zero : &cpuRegs.GPR.r[gpr]);
}

void LD()
{
    s32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;

	if (addr & 7) [[unlikely]]
		RaiseAddressError(addr, false);

	cpuRegs.GPR.r[_Rt_].UD[0] = memRead64(addr);
}

static const u64 LDL_MASK[8] =
{	0x00ffffffffffffffULL, 0x0000ffffffffffffULL, 0x000000ffffffffffULL, 0x00000000ffffffffULL,
	0x0000000000ffffffULL, 0x000000000000ffffULL, 0x00000000000000ffULL, 0x0000000000000000ULL
};
static const u64 LDR_MASK[8] =
{	0x0000000000000000ULL, 0xff00000000000000ULL, 0xffff000000000000ULL, 0xffffff0000000000ULL,
	0xffffffff00000000ULL, 0xffffffffff000000ULL, 0xffffffffffff0000ULL, 0xffffffffffffff00ULL
};

static const u8 LDR_SHIFT[8] = { 0, 8, 16, 24, 32, 40, 48, 56 };
static const u8 LDL_SHIFT[8] = { 56, 48, 40, 32, 24, 16, 8, 0 };


void LDL()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u32 shift = addr & 7;

	u64 mem = memRead64(addr & ~7);

	if( !_Rt_ ) return;
	cpuRegs.GPR.r[_Rt_].UD[0] =	(cpuRegs.GPR.r[_Rt_].UD[0] & LDL_MASK[shift]) |
								(mem << LDL_SHIFT[shift]);
}

void LDR()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u32 shift = addr & 7;

	u64 mem = memRead64(addr & ~7);

	if (!_Rt_) return;
	cpuRegs.GPR.r[_Rt_].UD[0] =	(cpuRegs.GPR.r[_Rt_].UD[0] & LDR_MASK[shift]) |
								(mem >> LDR_SHIFT[shift]);
}

void LQ()
{
	// MIPS Note: LQ and SQ are special and "silently" align memory addresses, thus
	// an address error due to unaligned access isn't possible like it is on other loads/stores.

	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	memRead128(addr & ~0xf, (u128*)gpr_GetWritePtr(_Rt_));
}

void SB()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	memWrite8(addr, cpuRegs.GPR.r[_Rt_].UC[0]);
}

void SH()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;

	if (addr & 1) [[unlikely]]
		RaiseAddressError(addr, true);

	memWrite16(addr, cpuRegs.GPR.r[_Rt_].US[0]);
}

void SW()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;

	if (addr & 3) [[unlikely]]
		RaiseAddressError(addr, true);

  memWrite32(addr, cpuRegs.GPR.r[_Rt_].UL[0]);
}

static const u32 SWL_MASK[4] = { 0xffffff00, 0xffff0000, 0xff000000, 0x00000000 };
static const u32 SWR_MASK[4] = { 0x00000000, 0x000000ff, 0x0000ffff, 0x00ffffff };

static const u8 SWR_SHIFT[4] = { 0, 8, 16, 24 };
static const u8 SWL_SHIFT[4] = { 24, 16, 8, 0 };

void SWL()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u32 shift = addr & 3;
	u32 mem = memRead32( addr & ~3 );

	memWrite32( addr & ~3,
		(cpuRegs.GPR.r[_Rt_].UL[0] >> SWL_SHIFT[shift]) |
		(mem & SWL_MASK[shift])
	);

	/*
	Mem = 1234.  Reg = abcd

	0   123a   (reg >> 24) | (mem & 0xffffff00)
	1   12ab   (reg >> 16) | (mem & 0xffff0000)
	2   1abc   (reg >>  8) | (mem & 0xff000000)
	3   abcd   (reg      ) | (mem & 0x00000000)
	*/
}

void SWR() {
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u32 shift = addr & 3;
	u32 mem = memRead32(addr & ~3);

	memWrite32( addr & ~3,
		(cpuRegs.GPR.r[_Rt_].UL[0] << SWR_SHIFT[shift]) |
		(mem & SWR_MASK[shift])
	);

	/*
	Mem = 1234.  Reg = abcd

	0   abcd   (reg      ) | (mem & 0x00000000)
	1   bcd4   (reg <<  8) | (mem & 0x000000ff)
	2   cd34   (reg << 16) | (mem & 0x0000ffff)
	3   d234   (reg << 24) | (mem & 0x00ffffff)
	*/
}

void SD()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;

	if (addr & 7) [[unlikely]]
		RaiseAddressError(addr, true);

    memWrite64(addr,cpuRegs.GPR.r[_Rt_].UD[0]);
}

static const u64 SDL_MASK[8] =
{	0xffffffffffffff00ULL, 0xffffffffffff0000ULL, 0xffffffffff000000ULL, 0xffffffff00000000ULL,
	0xffffff0000000000ULL, 0xffff000000000000ULL, 0xff00000000000000ULL, 0x0000000000000000ULL
};
static const u64 SDR_MASK[8] =
{	0x0000000000000000ULL, 0x00000000000000ffULL, 0x000000000000ffffULL, 0x0000000000ffffffULL,
	0x00000000ffffffffULL, 0x000000ffffffffffULL, 0x0000ffffffffffffULL, 0x00ffffffffffffffULL
};

static const u8 SDL_SHIFT[8] = { 56, 48, 40, 32, 24, 16, 8, 0 };
static const u8 SDR_SHIFT[8] = { 0, 8, 16, 24, 32, 40, 48, 56 };

void SDL()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u32 shift = addr & 7;
	u64 mem = memRead64(addr & ~7);
	mem = (cpuRegs.GPR.r[_Rt_].UD[0] >> SDL_SHIFT[shift]) |
		  (mem & SDL_MASK[shift]);
	memWrite64(addr & ~7, mem);
}


void SDR()
{
	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	u32 shift = addr & 7;
	u64 mem = memRead64(addr & ~7);
	mem = (cpuRegs.GPR.r[_Rt_].UD[0] << SDR_SHIFT[shift]) |
		  (mem & SDR_MASK[shift]);
	memWrite64(addr & ~7, mem );
}

void SQ()
{
	// MIPS Note: LQ and SQ are special and "silently" align memory addresses, thus
	// an address error due to unaligned access isn't possible like it is on other loads/stores.

	u32 addr = cpuRegs.GPR.r[_Rs_].UL[0] + _Imm_;
	memWrite128(addr & ~0xf, cpuRegs.GPR.r[_Rt_].UQ);
}

/*********************************************************
* Conditional Move                                       *
* Format:  OP rd, rs, rt                                 *
*********************************************************/

void MOVZ() {
	if (!_Rd_) return;
	if (cpuRegs.GPR.r[_Rt_].UD[0] == 0) {
		cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0];
	}
}
void MOVN() {
	if (!_Rd_) return;
	if (cpuRegs.GPR.r[_Rt_].UD[0] != 0) {
		cpuRegs.GPR.r[_Rd_].UD[0] = cpuRegs.GPR.r[_Rs_].UD[0];
	}
}

/*********************************************************
* Special purpose instructions                           *
* Format:  OP                                            *
*********************************************************/


// This function is the only one that uses Sifcmd.h in Pcsx2.
void SYSCALL() { eeref::stop("syscall"); }

void BREAK() { eeref::stop("break"); }

void MFSA() {
	if (!_Rd_) return;
	cpuRegs.GPR.r[_Rd_].UD[0] = (u64)cpuRegs.sa;
}

void MTSA() {
	cpuRegs.sa = (u32)cpuRegs.GPR.r[_Rs_].UD[0];
}

// SNY supports three basic modes, two which synchronize memory accesses (related
// to the cache) and one which synchronizes the instruction pipeline (effectively
// a stall in either case).  Our emulation model does not track EE-side pipeline
// status or stalls, nor does it implement the CACHE.  Thus SYNC need do nothing.
void SYNC()
{
}

// Used to prefetch data into the EE's cache, or schedule a dirty write-back.
// CACHE is not emulated at this time (nor is there any need to emulate it), so
// this function does nothing in the context of our emulator.
void PREF()
{
}

static void trap(u16 code=0)
{
	cpuRegs.pc -= 4;
	Console.Warning("Trap exception at 0x%08x", cpuRegs.pc);
	cpuException(0x34, cpuRegs.branch);
}

/*********************************************************
* Register trap                                          *
* Format:  OP rs, rt                                     *
*********************************************************/
void TGE()  { if (cpuRegs.GPR.r[_Rs_].SD[0] >= cpuRegs.GPR.r[_Rt_].SD[0]) trap(_TrapCode_); }
void TGEU() { if (cpuRegs.GPR.r[_Rs_].UD[0] >= cpuRegs.GPR.r[_Rt_].UD[0]) trap(_TrapCode_); }
void TLT()  { if (cpuRegs.GPR.r[_Rs_].SD[0] <  cpuRegs.GPR.r[_Rt_].SD[0]) trap(_TrapCode_); }
void TLTU() { if (cpuRegs.GPR.r[_Rs_].UD[0] <  cpuRegs.GPR.r[_Rt_].UD[0]) trap(_TrapCode_); }
void TEQ()  { if (cpuRegs.GPR.r[_Rs_].SD[0] == cpuRegs.GPR.r[_Rt_].SD[0]) trap(_TrapCode_); }
void TNE()  { if (cpuRegs.GPR.r[_Rs_].SD[0] != cpuRegs.GPR.r[_Rt_].SD[0]) trap(_TrapCode_); }

/*********************************************************
* Trap with immediate operand                            *
* Format:  OP rs, rt                                     *
*********************************************************/
void TGEI()  { if (cpuRegs.GPR.r[_Rs_].SD[0] >= _Imm_) trap(); }
void TLTI()  { if (cpuRegs.GPR.r[_Rs_].SD[0] <  _Imm_) trap(); }
void TEQI()  { if (cpuRegs.GPR.r[_Rs_].SD[0] == _Imm_) trap(); }
void TNEI()  { if (cpuRegs.GPR.r[_Rs_].SD[0] != _Imm_) trap(); }
void TGEIU() { if (cpuRegs.GPR.r[_Rs_].UD[0] >= (u64)_Imm_) trap(); }
void TLTIU() { if (cpuRegs.GPR.r[_Rs_].UD[0] <  (u64)_Imm_) trap(); }

/*********************************************************
* Sa intructions                                         *
* Format:  OP rs, rt                                     *
*********************************************************/

void MTSAB() {
	cpuRegs.sa = ((cpuRegs.GPR.r[_Rs_].UL[0] & 0xF) ^ (_Imm_ & 0xF));
}

void MTSAH() {
	cpuRegs.sa = ((cpuRegs.GPR.r[_Rs_].UL[0] & 0x7) ^ (_Imm_ & 0x7)) << 1;
}

} }	} // end namespace R5900::Interpreter::OpcodeImpl
