#pragma once

// mostly taken from: https://gist.github.com/iMoD1998/4aa48d5c990535767a3fc3251efc0348

#define MASK_N_BITS(N)					((1 << (N)) - 1)

#define PPC_HI(X)						(((X) >> 16) & 0xFFFF)
#define PPC_LO(X)						((X) & 0xFFFF)

// PowerPC most significant bit is addressed as bit 0.
#define PPC_BIT32(N)					(31 - (N))

// Opcode is bits 0-5.
// Allowing for op codes ranging from 0-63.
#define PPC_OPCODE(OP)					((OP) << 26)
#define PPC_OPCODE_ADDI					PPC_OPCODE(14)
#define PPC_OPCODE_ADDIS				PPC_OPCODE(15)
#define PPC_OPCODE_BC					PPC_OPCODE(16)
#define PPC_OPCODE_B					PPC_OPCODE(18)
#define PPC_OPCODE_BCCTR				PPC_OPCODE(19)
#define PPC_OPCODE_ORI					PPC_OPCODE(24)
#define PPC_OPCODE_EXTENDED				PPC_OPCODE(31)
#define PPC_OPCODE_LWZ					PPC_OPCODE(32)
#define PPC_OPCODE_STW					PPC_OPCODE(36)
#define PPC_OPCODE_LD					PPC_OPCODE(58)
#define PPC_OPCODE_STD					PPC_OPCODE(62)
#define PPC_OPCODE_MASK					PPC_OPCODE(63)

#define PPC_EXOPCODE(OP)				((OP) << 1)
#define PPC_EXOPCODE_BCCTR				PPC_EXOPCODE(528)
#define PPC_EXOPCODE_MTSPR				PPC_EXOPCODE(467)

// SPR field is encoded as two 5-bit fields.
#define PPC_SPR(SPR)					((UINT32)(((SPR) & 0x1F) << 5 | (((SPR) >> 5) & 0x1F)))

// rD - Destination register.
// rS - Source register.
// rA/rB - Register inputs.
// SPR - Special purpose register.
// UIMM/SIMM - Unsigned/signed immediate.
#define PPC_ADDI(rD, rA, SIMM)			((UINT32)(PPC_OPCODE_ADDI | ((rD) << PPC_BIT32(10)) | ((rA) << PPC_BIT32(15)) | (SIMM)))
#define PPC_ADDIS(rD, rA, SIMM)			((UINT32)(PPC_OPCODE_ADDIS | ((rD) << PPC_BIT32(10)) | ((rA) << PPC_BIT32(15)) | (SIMM)))
#define PPC_LIS(rD, SIMM)				PPC_ADDIS((rD), 0, (SIMM))
#define PPC_LI(rD, SIMM)				PPC_ADDI((rD), 0, (SIMM))
#define PPC_MTSPR(SPR, rS)				((UINT32)(PPC_OPCODE_EXTENDED | ((rS) << PPC_BIT32(10)) | (PPC_SPR(SPR) << PPC_BIT32(20)) | PPC_EXOPCODE_MTSPR))
#define PPC_MTCTR(rS)					PPC_MTSPR(9, (rS))
#define PPC_ORI(rS, rA, UIMM)			((UINT32)(PPC_OPCODE_ORI | ((rS) << PPC_BIT32(10)) | ((rA) << PPC_BIT32(15)) | (UIMM)))
#define PPC_BCCTR(BO, BI, LK)			((UINT32)(PPC_OPCODE_BCCTR | ((BO) << PPC_BIT32(10)) | ((BI) << PPC_BIT32(15)) | ((LK) & 1) | PPC_EXOPCODE_BCCTR))
#define PPC_STD(rS, DS, rA)				((UINT32)(PPC_OPCODE_STD | ((rS) << PPC_BIT32(10)) | ((rA) << PPC_BIT32(15)) | ((INT16)(DS) & 0xFFFF)))
#define PPC_LD(rS, DS, rA)				((UINT32)(PPC_OPCODE_LD | ((rS) << PPC_BIT32(10)) | ((rA) << PPC_BIT32(15)) | ((INT16)(DS) & 0xFFFF)))

#define PPC_BRANCH_LINKED				(1)
#define PPC_BRANCH_ABSOLUTE				(2)
#define PPC_BRANCH_OPTIONS_ALWAYS		(20)

#define DCBF(ptr)						__dcbf(0, ptr)
#define DCBST(ptr)						__dcbst(0, ptr)
#define SYNC()							__sync()
