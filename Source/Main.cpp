DWORD WINAPI MainThread(LPVOID)
{
	while (Util::XBox::XGetCurrentTitleId() != TITLE_ID)
	{
		Sleep(50);
	}

	Loader::RegisterModules();
	Loader::LoadAllModules();
	return 0;
}

BOOL APIENTRY DllMain(
	HANDLE handle,
	DWORD reason,
	LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE hThread = CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
		if (hThread)
		{
			CloseHandle(hThread);
		}
		break;
	}
	case DLL_PROCESS_DETACH:
		Loader::UnloadAllModules();
		break;
	}

	return TRUE;
}
