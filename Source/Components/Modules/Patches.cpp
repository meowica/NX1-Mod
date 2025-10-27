namespace Patches
{
#ifdef MP_MOD
	namespace MP
	{
		Util::Hook::Detour printf_Hook;
		Util::Hook::Detour _printf_Hook;
		void _printf(const char* fmt, ...)
		{
			char buf[256];

			va_list args;
			va_start(args, fmt);
			vsnprintf(buf, sizeof(buf), fmt, args);
			va_end(args);

			Symbols::MP::Com_Printf(0, "printf: %s", buf);
		}		

		Util::Hook::Detour FS_InitFilesystem_Hook;
		void FS_InitFilesystem()
		{
			DWORD start = GetTickCount(); // We could use Sys_Milliseconds here buuut GetTickCount works fine

			Symbols::MP::Com_Printf(0, "Loading modules...\n"); // TODO: figure out why this dont print
			for (int i = 0; i < Loader::g_moduleCount; ++i)
			{
				Symbols::MP::Com_Printf(0, "%d: %s\n", i + 1, Loader::g_modules[i].name);
			}
		
			DWORD end = GetTickCount();
			DWORD duration = end - start;

			Symbols::MP::Com_Printf(0, "Loaded all modules in %lu ms\n\n", duration);

			auto Invoke = FS_InitFilesystem_Hook.Invoke<void(*)()>();
			Invoke();
		}

		Util::Hook::Detour Com_ExecStartupConfigs_Hook;
		void Com_ExecStartupConfigs(int localClientNum, const char* configFile)
		{
			static bool alreadyRanFunction = FALSE;
			if (alreadyRanFunction)
			{
				return;
			}
			alreadyRanFunction = TRUE;

			auto Invoke = Com_ExecStartupConfigs_Hook.Invoke<void(*)(int, const char*)>();
			Invoke(localClientNum, configFile);
		}

		Util::Hook::Detour Com_Init_Hook;
		void Com_Init(const char* p_command_line)
		{
			auto Invoke = Com_Init_Hook.Invoke<void(*)(const char*)>();
			Invoke(p_command_line);

			if (p_command_line && *p_command_line)
			{
				Symbols::MP::Com_Printf(16, "Command Line:\n%s\n\n", p_command_line);
			}
		}

		Util::Hook::Detour getBuildNumber_Hook;
		const char* getBuildNumber()
		{
			return Util::String::Va("NX1-Mod MP");
		}

		Util::Hook::Detour LSP_CheckOngoingTasks_Hook;
		void LSP_CheckOngoingTasks(int PacketsInternal)
		{
			// null stub
		}

		Util::Hook::Detour MAssertVargs_Hook;
		int MAssertVargs(const char* filename, int line, int type, int, const char* fmt, ...)
		{
			// TODO: Implement symbols printing. For that extra cool debug info

			static const char* lastFilename = nullptr;
			static int lastLine = -1;
			static int repeatCount = 0;

			// Check if this is the same assert location as last time
			if (lastFilename && strcmp(lastFilename, filename) == 0 && lastLine == line)
			{
				repeatCount++;
			}
			else
			{
				lastFilename = filename;
				lastLine = line;
				repeatCount = 1;
			}

			char message[1024];

			va_list va;
			va_start(va, fmt);
			vsnprintf_s(message, sizeof(message), fmt, va);
			message[sizeof(message) - 1] = '\0';

			Symbols::MP::Com_Printf(0, "\n");
			Symbols::MP::Com_Printf(0, "****************************************\n");
			Symbols::MP::Com_Printf(0, "*  Assertion Info:\n");
			Symbols::MP::Com_Printf(0, "*  Message:       %s\n", message);
			Symbols::MP::Com_Printf(0, "*  File:          %s\n", filename);
			Symbols::MP::Com_Printf(0, "*  Line:          %d\n", line);
			Symbols::MP::Com_Printf(0, "****************************************\n");

			if (repeatCount >= 2)
			{
				Symbols::MP::Com_Printf(0, "*  Warning:       Same assert triggered multiple times.\n");
				Symbols::MP::Com_Printf(0, "****************************************\n");
				return 0;
			}
			else
			{
				Symbols::MP::Com_Printf(0, "*  Note:          First time this assert occurred.\n");
				Symbols::MP::Com_Printf(0, "****************************************\n");
				return 0;
			}
		}

		Util::Hook::Detour Sys_GetThreadName_Hook;
		void Sys_GetThreadName(DWORD threadId, char *p_destBuffer, unsigned int destBufferSize)
		{
			Util::XBox::DM_THREADINFOEX info;
			info.Size = sizeof(Util::XBox::DM_THREADINFOEX);
			Util::XBox::DmGetThreadInfoEx(threadId, &info);

			const char* name = info.ThreadNameAddress;
			snprintf(p_destBuffer, destBufferSize, "\"%s\", 0x%08x, HW Thread %d", name, threadId, info.CurrentProcessor);
		}

		void Hooks()
		{
			// issue fix: disable Black Box
			Util::Hook::Nop(0x82456AC0, 2); // BB_Init
			Util::Hook::Nop(0x824577C4, 2); // BB_Update

			// disable Anti Cheat
			Util::Hook::Nop(0x82456BE8, 2); // LiveAntiCheat_Init
			Util::Hook::Nop(0x82667F30, 2); // LiveAntiCheat_Pump
			Util::Hook::Nop(0x825A67FC, 2); // LiveAntiCheat_Update
			Util::Hook::Nop(0x825A48B4, 2); // LiveAntiCheat_UserSignedInToLive
			Util::Hook::Nop(0x825A3FCC, 2); // LiveAntiCheat_UserSignedOut
			Util::Hook::Nop(0x82667C44, 2); // LiveAntiCheat_OnChallengesReceived

			// detour printf output to Com_Printf instead
			printf_Hook.Create(printf, _printf);
			_printf_Hook.Create(0x82898D70, _printf); // make sure we grab the games version too

			// print all our loaded modules
			FS_InitFilesystem_Hook.Create(0x8252F740, FS_InitFilesystem);

			// prevent dupe config executions
			Com_ExecStartupConfigs_Hook.Create(0x82453810, Com_ExecStartupConfigs);

			Com_Init_Hook.Create(0x82457EC8, Com_Init);

			// xenia bug fix: fix console input
			Util::Hook::Nop(0x8259F27C, 2);

			// bug fix: remove xray material from the scoreboard
			Util::Hook::Nop(0x82263204, 2);

			// set build version to mine!
			getBuildNumber_Hook.Create(0x82425110, getBuildNumber);

			// dont check any lsp tasks
			LSP_CheckOngoingTasks_Hook.Create(0x82633810, LSP_CheckOngoingTasks);

			// our custom assertion handler
			MAssertVargs_Hook.Create(0x82527570, MAssertVargs);

			// fix thread names appearing as gibberish
			Sys_GetThreadName_Hook.Create(0x82572A88, Sys_GetThreadName);

			// remove autoexec dev
			Util::Hook::Nop(0x822C8A74, 2);
			Util::Hook::Nop(0x82453898, 2);
		}

		void PrintRemovals()
		{
			Util::Hook::Nop(0x8255628C, 2); // dvar set
			Util::Hook::Nop(0x8253C1B8, 2); // missing soundalias
			Util::Hook::Nop(0x82457F60, 2); // cmd line
			Util::Hook::Nop(0x8259AC34, 2); // unknown map add to xlast
			Util::Hook::Nop(0x82456B1C, 2); // start $init
			Util::Hook::Nop(0x82456BC0, 2); // end $init
			Util::Hook::Nop(0x8226E62C, 2); // looking for alias
			Util::Hook::Nop(0x82456A98, 2); // com_init_tbf build version
		}

		void StringEdits()
		{
			Util::Hook::Set<const char*>(0x8202F8D4, "%s MP > "); // uhh just make NX1-Mod look nicer
			Util::Hook::Set<const char*>(0x8202F8E0, "NX1-Mod"); // NX1 MODDING !!!!!!
			Util::Hook::Set<const char*>(0x8202F740, "Build 1866586"); // shorten that string!
			Util::Hook::Set<const char*>(0x8207FDB4, ""); // timestamp in console log
		}

		void DVarEdits()
		{
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
		}

		void ClearHooks()
		{
			printf_Hook.Clear();
			_printf_Hook.Clear();
			FS_InitFilesystem_Hook.Clear();
			Com_ExecStartupConfigs_Hook.Clear();
			Com_Init_Hook.Clear();
			getBuildNumber_Hook.Clear();
			LSP_CheckOngoingTasks_Hook.Clear();
			MAssertVargs_Hook.Clear();
			Sys_GetThreadName_Hook.Clear();
		}

		void Load()
		{
			Hooks();
			PrintRemovals();
			StringEdits();
			DVarEdits();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#elif SP_MOD
	namespace SP
	{
		Util::Hook::Detour printf_Hook;
		Util::Hook::Detour _printf_Hook;
		void _printf(const char* fmt, ...)
		{
			char buf[256];

			va_list args;
			va_start(args, fmt);
			vsnprintf(buf, sizeof(buf), fmt, args);
			va_end(args);

			Symbols::SP::Com_Printf(0, "printf: %s", buf);
		}

		Util::Hook::Detour FS_InitFilesystem_Hook;
		void FS_InitFilesystem()
		{
			DWORD start = GetTickCount(); // We could use Sys_Milliseconds here buuut GetTickCount works fine

			Symbols::SP::Com_Printf(0, "Loading modules...\n"); // TODO: figure out why this dont print
			for (int i = 0; i < Loader::g_moduleCount; ++i)
			{
				Symbols::SP::Com_Printf(0, "%d: %s\n", i + 1, Loader::g_modules[i].name);
			}
		
			DWORD end = GetTickCount();
			DWORD duration = end - start;

			Symbols::SP::Com_Printf(0, "Loaded all modules in %lu ms\n\n", duration);

			auto Invoke = FS_InitFilesystem_Hook.Invoke<void(*)()>();
			Invoke();
		}

		Util::Hook::Detour Com_ExecStartupConfigs_Hook;
		void Com_ExecStartupConfigs(int localClientNum, const char* configFile)
		{
			static bool alreadyRanFunction = FALSE;
			if (alreadyRanFunction)
			{
				return;
			}
			alreadyRanFunction = TRUE;

			auto Invoke = Com_ExecStartupConfigs_Hook.Invoke<void(*)(int, const char*)>();
			Invoke(localClientNum, configFile);
		}

		Util::Hook::Detour Com_Init_Hook;
		void Com_Init(const char* p_command_line)
		{
			auto Invoke = Com_Init_Hook.Invoke<void(*)(const char*)>();
			Invoke(p_command_line);

			if (p_command_line && *p_command_line)
			{
				Symbols::SP::Com_Printf(16, "Command Line:\n%s\n\n", p_command_line);
			}
		}

		Util::Hook::Detour getBuildNumber_Hook;
		const char* getBuildNumber()
		{
			return Util::String::Va("NX1-Mod SP");
		}

		Util::Hook::Detour LSP_CheckOngoingTasks_Hook;
		void LSP_CheckOngoingTasks(int PacketsInternal)
		{
			// null stub
		}

		Util::Hook::Detour MAssertVargs_Hook;
		int MAssertVargs(const char* filename, int line, int type, int, const char* fmt, ...)
		{
			// TODO: Implement symbols printing. For that extra cool debug info

			static const char* lastFilename = nullptr;
			static int lastLine = -1;
			static int repeatCount = 0;

			// Check if this is the same assert location as last time
			if (lastFilename && strcmp(lastFilename, filename) == 0 && lastLine == line)
			{
				repeatCount++;
			}
			else
			{
				lastFilename = filename;
				lastLine = line;
				repeatCount = 1;
			}

			char message[1024];

			va_list va;
			va_start(va, fmt);
			vsnprintf_s(message, sizeof(message), fmt, va);
			message[sizeof(message) - 1] = '\0';

			Symbols::SP::Com_Printf(0, "\n");
			Symbols::SP::Com_Printf(0, "****************************************\n");
			Symbols::SP::Com_Printf(0, "*  Assertion Info:\n");
			Symbols::SP::Com_Printf(0, "*  Message:       %s\n", message);
			Symbols::SP::Com_Printf(0, "*  File:          %s\n", filename);
			Symbols::SP::Com_Printf(0, "*  Line:          %d\n", line);
			Symbols::SP::Com_Printf(0, "****************************************\n");

			if (repeatCount >= 2)
			{
				Symbols::SP::Com_Printf(0, "*  Warning:       Same assert triggered multiple times.\n");
				Symbols::SP::Com_Printf(0, "****************************************\n");
				return 0;
			}
			else
			{
				Symbols::SP::Com_Printf(0, "*  Note:          First time this assert occurred.\n");
				Symbols::SP::Com_Printf(0, "****************************************\n");
				return 0;
			}
		}

		Util::Hook::Detour Sys_GetThreadName_Hook;
		void Sys_GetThreadName(DWORD threadId, char *p_destBuffer, unsigned int destBufferSize)
		{
			Util::XBox::DM_THREADINFOEX info;
			info.Size = sizeof(Util::XBox::DM_THREADINFOEX);
			Util::XBox::DmGetThreadInfoEx(threadId, &info);

			const char* name = info.ThreadNameAddress;
			snprintf(p_destBuffer, destBufferSize, "\"%s\", 0x%08x, HW Thread %d", name, threadId, info.CurrentProcessor);
		}

		void Hooks()
		{
			// issue fix: disable Black Box
			Util::Hook::Nop(0x8242C930, 2); // BB_Init
			Util::Hook::Nop(0x8242D4F8, 2); // BB_Update

			// disable Anti Cheat
			Util::Hook::Nop(0x8242CA38, 2); // LiveAntiCheat_Init
			Util::Hook::Nop(0x825CD3F8, 2); // LiveAntiCheat_Pump
			Util::Hook::Nop(0x825225D4, 2); // LiveAntiCheat_Update
			Util::Hook::Nop(0x82521740, 2); // LiveAntiCheat_UserSignedInToLive
			Util::Hook::Nop(0x8252119C, 2); // LiveAntiCheat_UserSignedOut
			Util::Hook::Nop(0x825CD10C, 2); // LiveAntiCheat_OnChallengesReceived

			// detour printf output to Com_Printf instead
			printf_Hook.Create(printf, _printf);
			_printf_Hook.Create(0x8277B188, _printf); // make sure we grab the games version too

			// print all our loaded modules
			FS_InitFilesystem_Hook.Create(0x824C34F0, FS_InitFilesystem);

			// prevent dupe config executions
			Com_ExecStartupConfigs_Hook.Create(0x824296C0, Com_ExecStartupConfigs);

			Com_Init_Hook.Create(0x8242DB20, Com_Init);

			// xenia bug fix: fix console input
			Util::Hook::Nop(0x8251E97C, 2);

			// set build version to mine!
			getBuildNumber_Hook.Create(0x82410188, getBuildNumber);

			// dont check any lsp tasks
			LSP_CheckOngoingTasks_Hook.Create(0x825A2C68, LSP_CheckOngoingTasks);

			// our custom assertion handler
			MAssertVargs_Hook.Create(0x824BCD10, MAssertVargs);

			// fix thread names appearing as gibberish
			Sys_GetThreadName_Hook.Create(0x824F41B8, Sys_GetThreadName);

			// remove autoexec dev
			Util::Hook::Nop(0x8222CC84, 2);
			Util::Hook::Nop(0x82429748, 2);
		}

		void PrintRemovals()
		{
			Util::Hook::Nop(0x824D920C, 2); // dvar set
			Util::Hook::Nop(0x824CF6C0, 2); // missing soundalias
			Util::Hook::Nop(0x8242DBB8, 2); // cmd line
			Util::Hook::Nop(0x8251B994, 2); // unknown map add to xlast
			Util::Hook::Nop(0x8242C98C, 2); // start $init
			Util::Hook::Nop(0x8242CA10, 2); // end $init
			Util::Hook::Nop(0x821E32EC, 2); // looking for alias
			Util::Hook::Nop(0x8242C908, 2); // com_init_tbf build version
		}

		void AssertRemovals()
		{
			Util::Hook::Nop(0x824F35F0, 2); // sys mem changed to something no expected
			Util::Hook::Nop(0x824F3D5C, 2); // ^^
			Util::Hook::Nop(0x824F3ABC, 2); // ^^
			Util::Hook::Nop(0x824F3858, 2); // ^^
		}

		void StringEdits()
		{
			Util::Hook::Set<const char*>(0x8201F030, "%s SP > "); // uhh just make NX1-Mod look nicer
			Util::Hook::Set<const char*>(0x8201F03C, "NX1-Mod"); // NX1 MODDING !!!!!!
			Util::Hook::Set<const char*>(0x8201EEC4, "Build 1866586"); // shorten that string!
			Util::Hook::Set<const char*>(0x82076B88, ""); // timestamp in console log
		}

		void DVarEdits()
		{
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
		}

		void ClearHooks()
		{
			FS_InitFilesystem_Hook.Clear();
			Com_ExecStartupConfigs_Hook.Clear();
			getBuildNumber_Hook.Clear();
			LSP_CheckOngoingTasks_Hook.Clear();
			MAssertVargs_Hook.Clear();
			Sys_GetThreadName_Hook.Clear();
		}

		void Load()
		{
			Hooks();
			PrintRemovals();
			AssertRemovals();
			StringEdits();
			DVarEdits();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif
}
