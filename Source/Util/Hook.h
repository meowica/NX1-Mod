#pragma once

#include "PPC.h"

// mostly taken from: https://gist.github.com/iMoD1998/4aa48d5c990535767a3fc3251efc0348

namespace Util
{
	class Hook
	{
	public:
		class Detour
		{
		public:
			Detour();
			Detour(void* place, void* target);
			Detour(size_t place, void* target);
			~Detour();

			bool Create(void* place, void* target);
			bool Create(size_t place, void* target);
			bool Clear();

			void* GetTrampolineAddress() const { return trampolineAddress_; }

			static BYTE trampolineBuffer[200 * 20];
			static SIZE_T trampolineSize;

			template<typename T>
			T Invoke() const
			{
				return T(this->trampolineAddress_);
			}

		private:
			void* place_;
			void* target_;
			unsigned char originalInstructions_[32];
			size_t originalLength_;
			void* trampolineAddress_;

			static size_t CopyInstruction(UINT32* dest, const UINT32* src);
			static size_t RelocateBranch(UINT32* dest, const UINT32* src);

			static size_t WriteFarBranch(void* dest, const void* target, bool linked, bool preserveReg);
			static size_t WriteFarBranchEx(void* dest, const void* target, bool linked, bool preserveReg, UINT32 options, BYTE crBit, BYTE regIndex);
		};

		static void Nop(void* place, size_t length);
		static void Nop(DWORD place, size_t length);

		template <typename T>
		static void Set(void* place, const T& value)
		{
			memcpy(place, &value, sizeof(T));
			
			DCBF(place);
			DCBST(place);
			SYNC();
		}

		template <>
		static void Set<const char*>(void* place, const char* const &value)
		{
			strcpy(reinterpret_cast<char*>(place), value);
			
			DCBF(place);
			DCBST(place);
			SYNC();
		}

		template <typename T>
		static void Set(DWORD place, const T& value)
		{
			Set(reinterpret_cast<void*>(place), value);
		}

	private:
	};
}
