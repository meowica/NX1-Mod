#ifndef IS_SINGLEPLAYER
#error This file is for Singeplayer only!!
#endif

namespace GameLog
{
#ifdef IS_SINGLEPLAYER
	namespace Singleplayer
	{
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
