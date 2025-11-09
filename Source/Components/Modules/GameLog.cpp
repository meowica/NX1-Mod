namespace GameLog
{
#ifdef IS_SINGLEPLAYER
	namespace SP
	{
		Util::Hook::Detour Vehicle_ClearServerDefs_Hook;
		void Vehicle_ClearServerDefs()
		{
			Symbols::SP::Com_Printf(15, "------- Game Initialization -------\n");
			Symbols::SP::Com_Printf(15, "NX1-Mod\n");
			Symbols::SP::Com_Printf(15, "Time: %s\n", Util::String::GetCurrentTime());
			Symbols::SP::Com_Printf(15, "-----------------------------------\n");

			auto Invoke = Vehicle_ClearServerDefs_Hook.Invoke<void(*)()>();
			Invoke();
		}

		void Hooks()
		{
			Vehicle_ClearServerDefs_Hook.Create(0x8256F0F8, Vehicle_ClearServerDefs);
		}

		void ClearHooks()
		{
			Vehicle_ClearServerDefs_Hook.Clear();
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
