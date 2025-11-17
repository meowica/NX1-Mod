namespace InternalConsole
{
#ifdef IS_MP
	namespace MP
	{
		Util::Hook::Detour Con_DrawConsole_Hook;
		void Con_DrawConsole(int localClientNum)
		{
			Symbols::MP::Con_CheckResize(Symbols::MP::scrPlaceFullUnsafe);

			if (Symbols::MP::Key_IsCatcherActive(localClientNum, KEYCATCH_CONSOLE))
				Symbols::MP::Con_DrawSolidConsole(localClientNum);
		}

		void Load()
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

		void Unload()
		{
			Con_DrawConsole_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		Util::Hook::Detour Con_DrawConsole_Hook;
		void Con_DrawConsole(int localClientNum)
		{
			Symbols::SP::Con_CheckResize(Symbols::SP::scrPlaceFull);

			if (Symbols::SP::Key_IsCatcherActive(localClientNum, KEYCATCH_CONSOLE))
				Symbols::SP::Con_DrawSolidConsole(localClientNum);
		}

		void Load()
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

		void Unload()
		{
			Con_DrawConsole_Hook.Clear();
		}
	}
#endif
}
