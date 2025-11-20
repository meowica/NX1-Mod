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

#pragma region Invoke Variadic Hack
			template <typename Ret>
			Ret Invoke() const
			{
				return reinterpret_cast<Ret(*)()>(GetTrampolineAddress())();
			}

			template <typename Ret, typename A1>
			Ret Invoke(A1 a1) const
			{
				return reinterpret_cast<Ret(*)(A1)>(GetTrampolineAddress())(a1);
			}

			template <typename Ret, typename A1, typename A2>
			Ret Invoke(A1 a1, A2 a2) const
			{
				return reinterpret_cast<Ret(*)(A1, A2)>(GetTrampolineAddress())(a1, a2);
			}

			template <typename Ret, typename A1, typename A2, typename A3>
			Ret Invoke(A1 a1, A2 a2, A3 a3) const
			{
				return reinterpret_cast<Ret(*)(A1, A2, A3)>(GetTrampolineAddress())(a1, a2, a3);
			}

			template <typename Ret, typename A1, typename A2, typename A3, typename A4>
			Ret Invoke(A1 a1, A2 a2, A3 a3, A4 a4) const
			{
				return reinterpret_cast<Ret(*)(A1, A2, A3, A4)>(GetTrampolineAddress())(a1, a2, a3, a4);
			}

			template <typename Ret, typename A1, typename A2, typename A3, typename A4, typename A5>
			Ret Invoke(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
			{
				return reinterpret_cast<Ret(*)(A1, A2, A3, A4, A5)>(GetTrampolineAddress())(a1, a2, a3, a4, a5);
			}

			template <typename Ret, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
			Ret Invoke(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const
			{
				return reinterpret_cast<Ret(*)(A1, A2, A3, A4, A5, A6)>(GetTrampolineAddress())(a1, a2, a3, a4, a5, a6);
			}

			template <typename Ret, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
			Ret Invoke(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const
			{
				return reinterpret_cast<Ret(*)(A1, A2, A3, A4, A5, A6, A7)>(GetTrampolineAddress())(a1, a2, a3, a4, a5, a6, a7);
			}

			template <typename Ret, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
			Ret Invoke(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const
			{
				return reinterpret_cast<Ret(*)(A1, A2, A3, A4, A5, A6, A7, A8)>(GetTrampolineAddress())(a1, a2, a3, a4, a5, a6, a7, a8);
			}

			// add more if you have more then 8 types
#pragma endregion

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

			// TODO: This needs major fixing, this doesn't work as intended
			// The CPU still uses the old instructions for some reasons, which makes some patches not get set sometimes. FIX SOON
			
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
