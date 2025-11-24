// for xenia, should be okay on xbox 360
#pragma section(".text")
__declspec(allocate(".text")) BYTE Util::Hook::Detour::trampolineBuffer[200 * 20];
SIZE_T Util::Hook::Detour::trampolineSize = 0;

namespace Util
{
	Hook::Detour::Detour()
		: place_(NULL)
		, target_(NULL)
		, originalLength_(0)
		, trampolineAddress_(NULL)
	{
	}

	Hook::Detour::Detour(void* place, void* target)
		: place_(NULL)
		, target_(NULL)
		, originalLength_(0)
		, trampolineAddress_(NULL)
	{
		this->Create(place, target);
	}

	Hook::Detour::Detour(size_t place, void* target)
		: place_(NULL)
		, target_(NULL)
		, originalLength_(0)
		, trampolineAddress_(NULL)
	{
		this->Create(reinterpret_cast<void*>(place), target);
	}

	Hook::Detour::~Detour()
	{
		Clear();
	}

	bool Hook::Detour::Create(void* place, void* target)
	{
		if (originalLength_ != 0)
			return false;

		place_ = place;
		target_ = target;

		size_t hookSize = WriteFarBranch(NULL, target_, false, false);
		memcpy(originalInstructions_, place_, hookSize);
		originalLength_ = hookSize;

		trampolineAddress_ = &trampolineBuffer[trampolineSize];

		for (size_t i = 0; i < hookSize / 4; ++i)
		{
			UINT32* instrPtr = (UINT32*)((UINT32)place_ + (i * 4));
			trampolineSize += CopyInstruction((UINT32*)&trampolineBuffer[trampolineSize], instrPtr);
		}

		void* afterBranchAddr = (void*)((UINT32)place_ + hookSize);
		trampolineSize += WriteFarBranch(&trampolineBuffer[trampolineSize], afterBranchAddr, false, true);

		WriteFarBranch(place_, target_, false, false);
		return true;
	}

	bool Hook::Detour::Create(const size_t place, void* target)
	{
		return Create(reinterpret_cast<void*>(place), target);
	}

	bool Hook::Detour::Clear()
	{
		if (place_ && originalLength_ != 0)
		{
			memcpy(place_, originalInstructions_, originalLength_);
			originalLength_ = 0;
			place_ = NULL;
			return true;
		}
		return false;
	}

	size_t Hook::Detour::CopyInstruction(UINT32* dest, const UINT32* src)
	{
		UINT32 instr = *src;
		switch (instr & PPC_OPCODE_MASK)
		{
		case PPC_OPCODE_B:
		case PPC_OPCODE_BC:
			return RelocateBranch(dest, src);
		default:
			*dest = instr;
			return 4;
		}
	}

	size_t Hook::Detour::RelocateBranch(UINT32* dest, const UINT32* src)
	{
		UINT32 instr = *src;
		UINT32 instrAddr = (UINT32)src;

		if (instr & PPC_BRANCH_ABSOLUTE)
		{
			*dest = instr;
			return 4;
		}

		INT32 offsetBitSize = 0;
		INT32 offsetBitBase = 0;
		UINT32 options = 0;
		BYTE crBit = 0;

		switch (instr & PPC_OPCODE_MASK)
		{
		case PPC_OPCODE_B:
			offsetBitSize = 24;
			offsetBitBase = 2;
			options = PPC_BRANCH_OPTIONS_ALWAYS;
			crBit = 0;
			break;
		case PPC_OPCODE_BC:
			offsetBitSize = 14;
			offsetBitBase = 2;
			options = (instr >> PPC_BIT32(10)) & MASK_N_BITS(5);
			crBit = (instr >> PPC_BIT32(15)) & MASK_N_BITS(5);
			break;
		}

		INT32 offset = instr & (MASK_N_BITS(offsetBitSize) << offsetBitBase);
		if (offset >> ((offsetBitSize + offsetBitBase) - 1))
			offset |= ~MASK_N_BITS(offsetBitSize + offsetBitBase);

		void* addr = (void*)((INT32)instrAddr + offset);
		return WriteFarBranchEx(dest, addr, (instr & PPC_BRANCH_LINKED) != 0, true, options, crBit, 11);
	}

	size_t Hook::Detour::WriteFarBranch(void* dest, const void* target, bool linked, bool preserveReg)
	{
		return WriteFarBranchEx(dest, target, linked, preserveReg, PPC_BRANCH_OPTIONS_ALWAYS, 0, 11);
	}

	size_t Hook::Detour::WriteFarBranchEx(void* dest, const void* target, bool linked, bool preserveReg, UINT32 options, BYTE crBit, BYTE regIndex)
	{
		UINT32 farAsm[] =
		{
			PPC_LIS(regIndex, PPC_HI((UINT32)target)),
			PPC_ORI(regIndex, regIndex, PPC_LO((UINT32)target)),
			PPC_MTCTR(regIndex),
			PPC_BCCTR(options, crBit, linked)
		};

		UINT32 farAsmPreserve[] =
		{
			PPC_STD(regIndex, -0x30, 1),
			PPC_LIS(regIndex, PPC_HI((UINT32)target)),
			PPC_ORI(regIndex, regIndex, PPC_LO((UINT32)target)),
			PPC_MTCTR(regIndex),
			PPC_LD(regIndex, -0x30, 1),
			PPC_BCCTR(options, crBit, linked)
		};

		const UINT32* asmBlock = (preserveReg) ? farAsmPreserve : farAsm;
		size_t asmSize = (preserveReg) ? sizeof(farAsmPreserve) : sizeof(farAsm);

		if (dest)
			memcpy(dest, asmBlock, asmSize);
		return asmSize;
	}

	void Hook::Nop(void* place, size_t length)
	{
		memset(place, 0x60000000, length);
			
		DCBF(place);
		DCBST(place);
		SYNC();
	}

	void Hook::Nop(DWORD place, size_t length)
	{
		Nop(reinterpret_cast<void*>(place), length);
	}
}
