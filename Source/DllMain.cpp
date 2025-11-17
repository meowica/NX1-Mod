namespace
{
	volatile bool isUnloading = false;

	void StartupThread()
	{
		DWORD expectedTitleId = Util::XBox::XGetCurrentTitleId();

		while (expectedTitleId != TITLE_ID)
			Sleep(50); // avoid CPU load

		if (!Util::XBox::IsInXenia())
			Sleep(200);

		Loader::LoadComponents();
	}

	void OnAttachProcess()
	{
        HANDLE threadHandle = nullptr;
        DWORD threadID = 0;

        DWORD ret = ExCreateThread(
            &threadHandle,
            0,
            &threadID,
            XapiThreadStartup,
            LPTHREAD_START_ROUTINE(StartupThread),
            nullptr,
            0x2 | CREATE_SUSPENDED);

        if (threadHandle)
        {
            XSetThreadProcessor(threadHandle, 4);
            ResumeThread(threadHandle);
        }
	}

	void OnDetachProcess()
	{
		if (Util::XBox::IsInXenia())
			return;

		isUnloading = true;

		DWORD expectedTitleId = Util::XBox::XGetCurrentTitleId();

		if (expectedTitleId == TITLE_ID)
			Loader::UnloadComponents();

		Sleep(200);
	}
}

BOOL WINAPI DllMain(HANDLE hInstance, DWORD dwReason, LPVOID)
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
