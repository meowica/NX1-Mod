namespace DevGui
{
#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		Util::Hook::Detour DevGui_GetScreenXPad_Hook;
		int DevGui_GetScreenXPad()
		{
			return 0;
		}

		Util::Hook::Detour DevGui_GetScreenYPad_Hook;
		int DevGui_GetScreenYPad()
		{
			return 0;
		}

		void Hooks()
		{
			// change the safe area to match pc
			DevGui_GetScreenXPad_Hook.Create(0x82353A68, DevGui_GetScreenXPad);
			DevGui_GetScreenYPad_Hook.Create(0x82353AD0, DevGui_GetScreenYPad);
		}

		void ClearHooks()
		{
			DevGui_GetScreenXPad_Hook.Clear();
			DevGui_GetScreenYPad_Hook.Clear();
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
		Util::Hook::Detour DevGui_GetScreenXPad_Hook;
		int DevGui_GetScreenXPad()
		{
			return 0;
		}

		Util::Hook::Detour DevGui_GetScreenYPad_Hook;
		int DevGui_GetScreenYPad()
		{
			return 0;
		}

		void Hooks()
		{
			// change the safe area to match pc
			DevGui_GetScreenXPad_Hook.Create(0x8229D748, DevGui_GetScreenXPad);
			DevGui_GetScreenYPad_Hook.Create(0x8229D7B0, DevGui_GetScreenYPad);
		}

		void ClearHooks()
		{
			DevGui_GetScreenXPad_Hook.Clear();
			DevGui_GetScreenYPad_Hook.Clear();
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
