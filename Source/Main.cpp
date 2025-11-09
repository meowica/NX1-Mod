bool isUnloading = false;

void StartupThread()
{
	// TODO: add memory address validation
	while (Util::XBox::XGetCurrentTitleId() != NX1_TITLE_ID)
	{
		// 50 is fine for Xenia, mirror what Heaventh did for Xbox 360
		if (Util::XBox::IsInXenia())
		{
			Sleep(50); // avoid CPU load
		}
		else
		{
			Sleep(75); // avoid CPU load
		}
	}

	// Xenia does not need this
	// From my testing, this only hinders the plugin, making it inject slower which means we miss out on things
	if (!Util::XBox::IsInXenia())
	{
		Sleep(200); // sleep a tiny bit
	}

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
	// but if it does, don't run it
	if (!Util::XBox::IsInXenia())
	{
		isUnloading = true;

		if (Util::XBox::XGetCurrentTitleId() == NX1_TITLE_ID)
		{
			Loader::UnloadAllModules(); // keys: does this even do anything??
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
	case DLL_PROCESS_DETACH:
		OnDetachProcess();
	}
	return TRUE;
}
