namespace Log
{
#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		Util::Hook::Detour SetupGfxConfig_Hook;
		void SetupGfxConfig(Structs::GfxConfiguration* config)
		{
			Symbols::Multiplayer::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "");
			Symbols::Multiplayer::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "----- Initializing Modules ----\n");

			auto Invoke = SetupGfxConfig_Hook.Invoke<void(*)(Structs::GfxConfiguration*)>();
			Invoke(config);

			for (int i = 0; i < Loader::g_moduleCount; ++i)
			{
				Symbols::Multiplayer::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "> %s\n", Loader::g_modules[i].name);
			}

			Symbols::Multiplayer::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "----- Initialized All Modules ----\n\n");
			Symbols::Multiplayer::Com_Printf(Structs::CON_CHANNEL_CLIENT, "----- Initializing Renderer ----\n");
		}

		Util::Hook::Detour printf_Hook;
		Util::Hook::Detour _printf_Hook;
		void _printf(const char* fmt, ...)
		{
			char buf[256];

			va_list args;
			va_start(args, fmt);
			vsnprintf(buf, sizeof(buf), fmt, args);
			va_end(args);

			Symbols::Multiplayer::Com_Printf(0, "printf: %s", buf);
		}

		void Hooks()
		{
			// print all our loaded modules
			SetupGfxConfig_Hook.Create(0x822AFB20, SetupGfxConfig);

			// detour printf output to Com_Printf instead
			printf_Hook.Create(printf, _printf);
			_printf_Hook.Create(0x82898D70, _printf); // make sure we grab the games version too
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
			Util::Hook::Nop(0x822AFBE0, 2); // renderer init (i reprint it in SetupGfxConfig hook)
		}

		void ClearHooks()
		{
			SetupGfxConfig_Hook.Clear();
			printf_Hook.Clear();
			_printf_Hook.Clear();
		}

		void Load()
		{
			Hooks();
			PrintRemovals();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#elif IS_SINGLEPLAYER
	namespace Singleplayer
	{
		Util::Hook::Detour R_ConfigureRenderer_Hook;
		void R_ConfigureRenderer(Structs::GfxConfiguration* config)
		{
			Symbols::Singleplayer::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "");
			Symbols::Singleplayer::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "----- Initializing Modules ----\n");

			auto Invoke = R_ConfigureRenderer_Hook.Invoke<void(*)(Structs::GfxConfiguration*)>();
			Invoke(config);

			for (int i = 0; i < Loader::g_moduleCount; ++i)
			{
				Symbols::Singleplayer::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "> %s\n", Loader::g_modules[i].name);
			}

			Symbols::Singleplayer::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "----- Initialized All Modules ----\n\n");
			Symbols::Singleplayer::Com_Printf(Structs::CON_CHANNEL_CLIENT, "----- Initializing Renderer ----\n");
		}

		Util::Hook::Detour Vehicle_ClearServerDefs_Hook;
		void Vehicle_ClearServerDefs()
		{
			Symbols::Singleplayer::Com_Printf(15, "------- Game Initialization -------\n");
			Symbols::Singleplayer::Com_Printf(15, "NX1-Mod\n");
			Symbols::Singleplayer::Com_Printf(15, "Time: %s\n", Util::String::GetCurrentTime());
			Symbols::Singleplayer::Com_Printf(15, "-----------------------------------\n");

			auto Invoke = Vehicle_ClearServerDefs_Hook.Invoke<void(*)()>();
			Invoke();
		}

		Util::Hook::Detour printf_Hook;
		Util::Hook::Detour _printf_Hook;
		void _printf(const char* fmt, ...)
		{
			char buf[256];

			va_list args;
			va_start(args, fmt);
			vsnprintf(buf, sizeof(buf), fmt, args);
			va_end(args);

			Symbols::Singleplayer::Com_Printf(0, "printf: %s", buf);
		}

		void Hooks()
		{
			// print all our loaded modules
			R_ConfigureRenderer_Hook.Create(0x82704860, R_ConfigureRenderer);

			// print game init + current time
			Vehicle_ClearServerDefs_Hook.Create(0x8256F0F8, Vehicle_ClearServerDefs);

			// detour printf output to Com_Printf instead
			printf_Hook.Create(printf, _printf);
			_printf_Hook.Create(0x8277B188, _printf); // make sure we grab the games version too
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
			Util::Hook::Nop(0x8221B6F8, 2); // renderer init (i reprint it in R_ConfigureRenderer hook)
		}

		void ClearHooks()
		{
			R_ConfigureRenderer_Hook.Clear();
			Vehicle_ClearServerDefs_Hook.Clear();
			_printf_Hook.Clear();
			printf_Hook.Clear();
		}

		void Load()
		{
			Hooks();
			PrintRemovals();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif
}
