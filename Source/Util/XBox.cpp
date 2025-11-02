namespace Util
{
	namespace XBox
	{
		// Borrowed and slightly modified from https://github.com/michaeloliverx/codxe/blob/cbe7ea24ea1ff0378b327bb1a2dada2ba2831216/src/xboxkrnl.cpp#L7
		bool IsInXenia()
		{
			// https://github.com/ClementDreptin/XexUtils/blob/ae8a8b832315678255c00d6a9b967a9136155503/src/Xam_.cpp#L168
			// https://github.com/RBEnhanced/RB3Enhanced/blob/106c4290ee4fc2a91da65f4092a2b881971dc59c/source/xbox360.c#L16

			void* xamFirstExport = ResolveFunction("xam.xex", 1);
			// if Xam is not in the typical memory address space, we're in Xenia
			return (unsigned long)xamFirstExport >> 24 != 0x81;
		}

		// Borrowed and slightly modified from https://github.com/michaeloliverx/codxe/blob/cbe7ea24ea1ff0378b327bb1a2dada2ba2831216/src/xboxkrnl.cpp#L17
		void* ResolveFunction(const char* moduleName, unsigned int ordinal)
		{
			HMODULE moduleHandle = GetModuleHandle(moduleName);
			if (moduleHandle == NULL)
			{
				return NULL;
			}
			return GetProcAddress(moduleHandle, (const char*)ordinal);
		}

		DWORD XGetCurrentTitleId()
		{
			return XamGetCurrentTitleId();
		}

		const char* GetFakeThreadName(uint32_t threadId)
		{
			switch (threadId % 8)
			{
			case 0:
				return "Main";
			case 1:
				return "Render";
			case 2:
				return "Worker0";
			case 3:
				return "Worker1";
			case 4:
				return "Audio";
			case 5:
				return "Network";
			case 6:
				return "Stream";
			case 7:
				return "Comms";
			default:
				return "Unknown";
			}
		}

		int DmGetThreadInfoEx(uint32_t threadId, DM_THREADINFOEX* info)
		{
			if (!info)
				return -1;

			std::memset(info, 0, sizeof(DM_THREADINFOEX));
			info->Size = sizeof(DM_THREADINFOEX);
			info->CurrentProcessor = threadId % 6;
			info->ThreadNameAddress = const_cast<char*>(GetFakeThreadName(threadId));

			info->Priority = 8 + (threadId % 3);
			info->SuspendCount = 0;
			info->StartAddress = 0x82000000 + (threadId * 0x1000);
			info->StackBase = 0x85000000;
			info->StackLimit = 0x84FF0000;
			return S_OK;
		}
	}
}
