bool isUnloading = false;

void StartupThread()
{
	// TODO: add memory address validation
	while (Util::XBox::XGetCurrentTitleId() != TITLE_ID)
	{
		Sleep(50); // avoid CPU load
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
	isUnloading = true;

	if (Util::XBox::XGetCurrentTitleId() == TITLE_ID)
	{
		Loader::UnloadAllModules(); // keys: does this even do anything??
	}

	Sleep(200);
}

BOOL APIENTRY DllMain(
	HANDLE handle,
	DWORD reason,
	LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		OnAttachProcess();
	case DLL_PROCESS_DETACH:
		OnDetachProcess();
	}

	return TRUE;
}
