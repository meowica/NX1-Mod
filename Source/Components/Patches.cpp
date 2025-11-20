namespace Patches
{
#ifdef IS_MP
	namespace MP
	{
		Util::Hook::Detour Com_ExecStartupConfigs_Hook;
		void Com_ExecStartupConfigs(int localClientNum, const char* configFile)
		{
			static bool alreadyRanFunction = false;
			if (alreadyRanFunction)
				return;

			alreadyRanFunction = true;

			Com_ExecStartupConfigs_Hook.Invoke<void>(localClientNum, configFile);
		}

		Util::Hook::Detour Sys_GetThreadName_Hook;
		void Sys_GetThreadName(DWORD threadId, char* p_destBuffer, unsigned int destBufferSize)
		{
			Util::XBox::DM_THREADINFOEX info;

			info.Size = sizeof(Util::XBox::DM_THREADINFOEX);
			Util::XBox::DmGetThreadInfoEx(threadId, &info);

			const char* name = info.ThreadNameAddress;
			snprintf(p_destBuffer, destBufferSize, "\"%s\", 0x%08x, HW Thread %d", name, threadId, info.CurrentProcessor);
		}

		void Load()
		{
			// issue fix: disable Black Box
			Util::Hook::Nop(0x82456AC0, 2); // BB_Init
			Util::Hook::Nop(0x824577C4, 2); // BB_Update

			// xenia bug fix: fix console input
			Util::Hook::Nop(0x8259F27C, 2);

			// bug fix: remove xray material from the scoreboard
			Util::Hook::Nop(0x82263204, 2);

			// prevent dupe config executions
			Com_ExecStartupConfigs_Hook.Create(0x82453810, Com_ExecStartupConfigs);

			// fix thread names appearing as gibberish
			Sys_GetThreadName_Hook.Create(0x82572A88, Sys_GetThreadName);

			// remove autoexec dev
			Util::Hook::Nop(0x822C8A74, 2);
			Util::Hook::Nop(0x82453898, 2);

			// allow unsigned fast files to load
			Util::Hook::Set(0x82453098, 0x38800001); // fastfile_allowNoAuth

			// unlock fps
			Util::Hook::Set(0x82812054, 0x38800000); // r_vsync
			Util::Hook::Set(0x82453010, 0x38800000); // com_maxfps

			// kill com_statmon, it looks ugly
			Util::Hook::Set(0x828139CC, 0x38800000); // com_statmon
			Util::Hook::Set(0x82453138, 0x38800000);

			// kill view pos
			Util::Hook::Set(0x82241314, 0xFC400090); // cg_drawViewpos

			// kill loc errors
			Util::Hook::Set(0x824EFF5C, 0xFC400090); // loc_warningsAsErrors

			// disable this by default cause of our new fps counter
			Util::Hook::Set(0x822412F0, 0x38800000); // cg_drawFPS

			// string changes
			Util::Hook::Set<const char*>(0x8202F8D4, "%s MP > ");
			Util::Hook::Set<const char*>(0x8202F8E0, "NX1-Mod");
			Util::Hook::Set<const char*>(0x8202F740, "Build 1866586");
			Util::Hook::Set<const char*>(0x8207FDB4, ""); // timestamp in console log
			Util::Hook::Set<const char*>(0x820A0EC0, "NX1-Host"); // default host name
			Util::Hook::Set<const char*>(0x82067238, "NX1"); // game name
		}

		void Unload()
		{
			Com_ExecStartupConfigs_Hook.Clear();
			Sys_GetThreadName_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		Util::Hook::Detour Com_ExecStartupConfigs_Hook;
		void Com_ExecStartupConfigs(int localClientNum, const char* configFile)
		{
			static bool alreadyRanFunction = false;
			if (alreadyRanFunction)
				return;

			alreadyRanFunction = true;

			Com_ExecStartupConfigs_Hook.Invoke<void>(localClientNum, configFile);
		}

		Util::Hook::Detour Sys_GetThreadName_Hook;
		void Sys_GetThreadName(DWORD threadId, char* p_destBuffer, unsigned int destBufferSize)
		{
			Util::XBox::DM_THREADINFOEX info;

			info.Size = sizeof(Util::XBox::DM_THREADINFOEX);
			Util::XBox::DmGetThreadInfoEx(threadId, &info);

			const char* name = info.ThreadNameAddress;
			snprintf(p_destBuffer, destBufferSize, "\"%s\", 0x%08x, HW Thread %d", name, threadId, info.CurrentProcessor);
		}

		void Load()
		{
			// issue fix: disable Black Box
			Util::Hook::Nop(0x8242C930, 2); // BB_Init
			Util::Hook::Nop(0x8242D4F8, 2); // BB_Update

			// xenia bug fix: fix console input
			Util::Hook::Nop(0x8251E97C, 2);

			// prevent dupe config executions
			Com_ExecStartupConfigs_Hook.Create(0x824296C0, Com_ExecStartupConfigs);

			// fix thread names appearing as gibberish
			Sys_GetThreadName_Hook.Create(0x824F41B8, Sys_GetThreadName);

			// remove autoexec dev
			Util::Hook::Nop(0x8222CC84, 2);
			Util::Hook::Nop(0x82429748, 2);

			// remove "sys mem changed to something not expected" assert
			Util::Hook::Nop(0x824F35F0, 2);
			Util::Hook::Nop(0x824F3D5C, 2);
			Util::Hook::Nop(0x824F3ABC, 2);
			Util::Hook::Nop(0x824F3858, 2);

			// skip main_lockout menu
			Util::Hook::Set(0x8242CDB8, 0x38800001); // ui_skipMainLockout

			// unlock fps
			Util::Hook::Set(0x827014DC, 0x38800000); // r_vsync 0
			Util::Hook::Set(0x82428FD0, 0x38800000); // com_maxfps 0

			// kill stat mon, it looks ugly
			Util::Hook::Set(0x82702E54, 0x38800000); // com_statmon
			Util::Hook::Set(0x824290F8, 0x38800000); // com_statmon

			// kill view pos
			Util::Hook::Set(0x821BB110, 0xFC400090); // cg_drawViewpos

			// kill loc errors
			Util::Hook::Set(0x82496DFC, 0xFC400090); // loc_warningsAsErrors

			// disable this by default cause of our new fps counter
			Util::Hook::Set(0x821BB0F8, 0x38800000); // cg_drawFPS

			// string changes
			Util::Hook::Set<const char*>(0x8201F030, "%s SP > ");
			Util::Hook::Set<const char*>(0x8201F03C, "NX1-Mod");
			Util::Hook::Set<const char*>(0x8201EEC4, "Build 1866586");
			Util::Hook::Set<const char*>(0x82076B88, ""); // timestamp in console log
		}

		void Unload()
		{
			Com_ExecStartupConfigs_Hook.Clear();
			Sys_GetThreadName_Hook.Clear();
		}
	}
#endif
}
