#pragma once

namespace Util
{
	namespace XBox
	{
		bool IsInXenia();

		void* ResolveFunction(const char* moduleName, unsigned int ordinal);

		DWORD XGetCurrentTitleId();

		typedef struct _DM_THREADINFOEX
		{
			unsigned int Size;
			unsigned int SuspendCount;
			unsigned int Priority;

			void* TlsBase;
			void* StartAddress;
			void* StackBase;
			void* StackLimit;

			FILETIME CreateTime;

			unsigned int StackSlackSpace;
			char* ThreadNameAddress;
			unsigned int ThreadNameLength;
			unsigned char CurrentProcessor;
			unsigned int LastError;
		} DM_THREADINFOEX, *PDM_THREADINFOEX;

		HRESULT DmGetThreadInfoEx(DWORD dwThreadId, PDM_THREADINFOEX pdmti);
	}
}
