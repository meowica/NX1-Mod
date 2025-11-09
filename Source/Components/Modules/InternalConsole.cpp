namespace InternalConsole
{
#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		Util::Hook::Detour Con_DrawConsole_Hook;
		void Con_DrawConsole(int localClientNum)
		{
			Symbols::Multiplayer::Con_CheckResize(Symbols::Multiplayer::scrPlaceFullUnsafe);
			if (Symbols::Multiplayer::Key_IsCatcherActive(localClientNum, KEYCATCH_CONSOLE))
			{
				Symbols::Multiplayer::Con_DrawSolidConsole(localClientNum);
			}
		}

		void Hooks()
		{
			// change the safe area to match pc
			Con_DrawConsole_Hook.Create(0x8229F388, Con_DrawConsole);

			// change output box size
			Util::Hook::Set(0x82013E14, 36.0f);

			// change console font
			Util::Hook::Set<const char*>(0x8203259C, "fonts/fwsmallfont");

			// we dont need this
			Util::Hook::Nop(0x8229D414, 2); // Con_DrawOutputVersion
		}

		void ClearHooks()
		{
			Con_DrawConsole_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#elif IS_SINGLEPLAYER
	namespace Singleplayer
	{
		Util::Hook::Detour Con_DrawConsole_Hook;
		void Con_DrawConsole(int localClientNum)
		{
			Symbols::Singleplayer::Con_CheckResize(Symbols::Singleplayer::scrPlaceFull);
			if (Symbols::Singleplayer::Key_IsCatcherActive(localClientNum, KEYCATCH_CONSOLE))
			{
				Symbols::Singleplayer::Con_DrawSolidConsole(localClientNum);
			}
		}

		void Hooks()
		{
			// change the safe area to match pc
			Con_DrawConsole_Hook.Create(0x8220EA90, Con_DrawConsole);

			// change output box size
			Util::Hook::Set(0x8201DF2C, 36.0f);

			// change console font
			Util::Hook::Set<const char*>(0x820214C0, "fonts/fwsmallfont");

			// we dont need this
			Util::Hook::Nop(0x8220CB80, 2); // Con_DrawOutputVersion
		}

		void ClearHooks()
		{
			Con_DrawConsole_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif
}
