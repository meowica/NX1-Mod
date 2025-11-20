namespace Log
{
#ifdef IS_MP
	namespace MP
	{
		Util::Hook::Detour SetupGfxConfig_Hook;
		void SetupGfxConfig(Structs::GfxConfiguration* config)
		{
			Symbols::MP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, ""); // ghost print
			Symbols::MP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "Loading NX1-Mod...\n");
			Symbols::MP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "\n");
			Symbols::MP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "----- Initializing Components ----\n");

			SetupGfxConfig_Hook.Invoke<void>(config);

			for (int i = 0; i < Loader::g_componentCount; ++i)
			{
				Symbols::MP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "> %s\n", Loader::g_components[i].name);
			}

			Symbols::MP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "----- Initialized All Components ----\n\n");
			Symbols::MP::Com_Printf(Structs::CON_CHANNEL_CLIENT, "----- Initializing Renderer ----\n");
		}

		// Borrowed from Rattpak S2MP-Mod: https://github.com/Rattpak/S2MP-Mod/blob/71ebb9646b7fcbbd90292b5dd87599390f9b2742/src/PrintPatches.cpp#L61
		Util::Hook::Detour CM_LoadMap_Hook;
		void CM_LoadMap(const char* name, int* checksum)
		{
			Symbols::MP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "Loading Map: %s\n", name);
			CM_LoadMap_Hook.Invoke<void>(name, checksum);
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

			Symbols::MP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "printf: %s", buf);
		}

		void Load()
		{
			// print all our loaded modules
			SetupGfxConfig_Hook.Create(0x822AFB20, SetupGfxConfig);

			// print the loaded d3dbsp
			CM_LoadMap_Hook.Create(0x82425428, CM_LoadMap);

			// detour printf output to Com_Printf instead
			printf_Hook.Create(printf, _printf);
			_printf_Hook.Create(0x82898D70, _printf); // make sure we grab the games version too

			// remove prints
			Util::Hook::Nop(0x8255628C, 2); // dvar set
			Util::Hook::Nop(0x8253C1B8, 2); // missing soundalias
			Util::Hook::Nop(0x82457F60, 2); // cmd line
			Util::Hook::Nop(0x8259AC34, 2); // unknown map add to xlast
			Util::Hook::Nop(0x82456B1C, 2); // start $init
			Util::Hook::Nop(0x82456BC0, 2); // end $init
			Util::Hook::Nop(0x8226E62C, 2); // looking for alias
			Util::Hook::Nop(0x82456A98, 2); // com_init_tbf build version
			Util::Hook::Nop(0x822AFBE0, 2); // renderer init (i reprint it in SetupGfxConfig hook)
			Util::Hook::Nop(0x825707F8, 2); // loading from disc, not update drive
			Util::Hook::Nop(0x822C27DC, 2); // adding/hiding channel
			Util::Hook::Nop(0x822C280C, 2); // no channels added/hidden
			Util::Hook::Nop(0x82455788, 2); // logfile opened on <date>
		}

		void Unload()
		{
			SetupGfxConfig_Hook.Clear();
			CM_LoadMap_Hook.Clear();
			printf_Hook.Clear();
			_printf_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		Util::Hook::Detour R_ConfigureRenderer_Hook;
		void R_ConfigureRenderer(Structs::GfxConfiguration* config)
		{
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, ""); // ghost print
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "Loading NX1-Mod...\n");
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "\n");
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "----- Initializing Components ----\n");

			R_ConfigureRenderer_Hook.Invoke<void>(config);

			for (int i = 0; i < Loader::g_componentCount; ++i)
			{
				Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "> %s\n", Loader::g_components[i].name);
			}

			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "----- Initialized All Modules ----\n\n");
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_CLIENT, "----- Initializing Renderer ----\n");
		}

		// Borrowed from Rattpak's S2MP-Mod
		// https://github.com/Rattpak/S2MP-Mod/blob/71ebb9646b7fcbbd90292b5dd87599390f9b2742/src/PrintPatches.cpp#L61
		Util::Hook::Detour CM_LoadMap_Hook;
		void CM_LoadMap(const char* name, int* checksum)
		{
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "Loading Map: %s\n", name);
			CM_LoadMap_Hook.Invoke<void>(name, checksum);
		}

		Util::Hook::Detour Vehicle_ClearServerDefs_Hook;
		void Vehicle_ClearServerDefs()
		{
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SERVER, "------- Game Initialization -------\n");
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SERVER, "NX1-Mod\n");
			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SERVER, "-----------------------------------\n");
			Vehicle_ClearServerDefs_Hook.Invoke<void>();
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

			Symbols::SP::Com_Printf(Structs::CON_CHANNEL_SYSTEM, "printf: %s", buf);
		}

		void Load()
		{
			// print all our loaded modules
			R_ConfigureRenderer_Hook.Create(0x82704860, R_ConfigureRenderer);

			// print the loaded d3dbsp
			CM_LoadMap_Hook.Create(0x824104A0, CM_LoadMap);

			// print game name
			Vehicle_ClearServerDefs_Hook.Create(0x8256F0F8, Vehicle_ClearServerDefs);

			// detour printf output to Com_Printf instead
			printf_Hook.Create(printf, _printf);
			_printf_Hook.Create(0x8277B188, _printf); // make sure we grab the games version too

			// remove prints
			Util::Hook::Nop(0x824D920C, 2); // dvar set
			Util::Hook::Nop(0x824CF6C0, 2); // missing soundalias
			Util::Hook::Nop(0x8242DBB8, 2); // cmd line
			Util::Hook::Nop(0x8251B994, 2); // unknown map add to xlast
			Util::Hook::Nop(0x8242C98C, 2); // start $init
			Util::Hook::Nop(0x8242CA10, 2); // end $init
			Util::Hook::Nop(0x821E32EC, 2); // looking for alias
			Util::Hook::Nop(0x8242C908, 2); // com_init_tbf build version
			Util::Hook::Nop(0x8221B6F8, 2); // renderer init (i reprint it in R_ConfigureRenderer hook)
			Util::Hook::Nop(0x82223A64, 2); // adding/hiding channel
			Util::Hook::Nop(0x82223A94, 2); // no channels added/hidden
			Util::Hook::Nop(0x8242B590, 2); // logfile opened on <date>
		}

		void Unload()
		{
			R_ConfigureRenderer_Hook.Clear();
			CM_LoadMap_Hook.Clear();
			Vehicle_ClearServerDefs_Hook.Clear();
			_printf_Hook.Clear();
			printf_Hook.Clear();
		}
	}
#endif
}
