namespace
{
	volatile bool isUnloading = false;

	void StartupThread()
	{
		while (Util::XBox::XGetCurrentTitleId() != TITLE_ID)
			Sleep((Util::XBox::IsInXenia()) ? 50 : 75); // Avoid CPU load

		// On Xenia, this delays the plugin loading which prevents
		// some things from being registered, on real hardware it's fine
		// So we're keeping it only on real hardware
		if (!Util::XBox::IsInXenia())
			Sleep(200); // Sleep a tiny bit

		// Register our modules now
		Loader::RegisterModules();
		Loader::LoadAllModules();
	}

	VOID OnAttachProcess()
	{
		HANDLE threadHandle;
		DWORD threadID;
	
		ExCreateThread(&threadHandle, NULL, &threadID, XapiThreadStartup, LPTHREAD_START_ROUTINE(StartupThread), NULL, 0x2 | CREATE_SUSPENDED);
		if (threadHandle != INVALID_HANDLE_VALUE)
		{
			XSetThreadProcessor(threadHandle, 4);
			ResumeThread(threadHandle);
		}
	}

	VOID OnDetachProcess()
	{
		// Xenia doesn't need this, besides this will NEVER execute in Xenia
		// but if it does somehow, don't run it
		if (Util::XBox::IsInXenia())
			return;

		isUnloading = true;

		if (Util::XBox::XGetCurrentTitleId() == TITLE_ID)
		{
			Loader::UnloadAllModules();
		}

		Sleep(200);
	}
}

BOOL WINAPI DllMain(HANDLE hInst, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		OnAttachProcess();
		break;
	case DLL_PROCESS_DETACH:
		OnDetachProcess();
		break;
	}
	return TRUE;
}
