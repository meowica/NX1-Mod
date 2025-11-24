namespace Util
{
	namespace XBox
	{
		static const char* GetFakeThreadName(DWORD dwThreadId)
		{
			switch (dwThreadId % 8)
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

		HRESULT DmGetThreadInfoEx(DWORD dwThreadId, PDM_THREADINFOEX pdmti)
		{
			if (!pdmti)
				return -1;

			std::memset(pdmti, 0, sizeof(PDM_THREADINFOEX));
			pdmti->Size = sizeof(PDM_THREADINFOEX);

			pdmti->Priority = 12 + (dwThreadId % 4);
			pdmti->SuspendCount = 0;

			pdmti->TlsBase = reinterpret_cast<void*>(0x83000000 + (dwThreadId * 0x100));
			pdmti->StartAddress = reinterpret_cast<void*>(0x82000000 + (dwThreadId * 0x2000));
			pdmti->StackBase = reinterpret_cast<void*>(0x83000000 + (dwThreadId * 0x8000));
			pdmti->StackLimit = reinterpret_cast<void*>(0x82F00000 + (dwThreadId * 0x8000));

			pdmti->StackSlackSpace = 0x2000;

			const char* name = GetFakeThreadName(dwThreadId);
			pdmti->ThreadNameAddress = const_cast<char*>(name);
			pdmti->ThreadNameLength = std::strlen(name);

			pdmti->CurrentProcessor = static_cast<unsigned char>(dwThreadId % 6);

			pdmti->CreateTime.dwLowDateTime = 0xA1B2C3D4;
			pdmti->CreateTime.dwHighDateTime = 0x01234567;

			pdmti->LastError = 0;
			return S_OK;
		}

		DWORD XGetCurrentTitleId()
		{
			return XamGetCurrentTitleId();
		}

		int XShowMessageBox(
			DWORD dwUserIndex,
			const std::wstring& title,
			const std::wstring& text,
			const std::vector<std::wstring>* buttons,
			DWORD focusButton,
			DWORD flags)
		{
			MESSAGEBOX_RESULT result = {};
			XOVERLAPPED overlapped = {};
			overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
			if (!overlapped.hEvent)
				return 0;

			LPCWSTR* pButtonArray = nullptr;
			DWORD cButtons = 0;

			if (buttons && !buttons->empty())
			{
				cButtons = static_cast<DWORD>(buttons->size());
				pButtonArray = new LPCWSTR[cButtons];

				for (DWORD i = 0; i < cButtons; ++i)
					pButtonArray[i] = (*buttons)[i].c_str();
			}

			HRESULT hr = XShowMessageBoxUI(
				dwUserIndex,
				title.c_str(),
				text.c_str(),
				cButtons,
				pButtonArray,
				focusButton,
				flags,
				&result,
				&overlapped);

			if (FAILED(hr))
			{
				if (pButtonArray)
					delete[] pButtonArray;

				CloseHandle(overlapped.hEvent);
				return 0;
			}

			WaitForSingleObject(overlapped.hEvent, INFINITE);

			if (pButtonArray)
				delete[] pButtonArray;

			CloseHandle(overlapped.hEvent);
			return static_cast<int>(result.dwButtonPressed);
		}

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
				return NULL;
			return GetProcAddress(moduleHandle, (const char*)ordinal);
		}
	}
}
