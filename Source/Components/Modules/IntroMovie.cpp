namespace IntroMovie
{
#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		Util::Hook::Detour SV_InitServerThread_Hook;
		void SV_InitServerThread()
		{
			auto Invoke = SV_InitServerThread_Hook.Invoke<void(*)()>();
			Invoke();

			// Why hook here? I hooked here because COM_PlayIntroMovies is inlined and because this is the closest function to it
			// Hooking directly into Com_Init_TBF works fine, but this is more accurate at the intro movie placement

			const auto playIntro = Symbols::Multiplayer::Dvar_FindVar("intro");
			if (!IniConfig::ShouldShowIntroMovie() || !playIntro->current.enabled)
				return;

			Symbols::Multiplayer::Cbuf_AddText(0, "autocinematic title\n");
		}

		void Hooks()
		{
			// play our own intro movie
			SV_InitServerThread_Hook.Create(0x824DEB90, SV_InitServerThread);
		}

		void ClearHooks()
		{
			SV_InitServerThread_Hook.Clear();
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
		Util::Hook::Detour COM_PlayIntroMovies_Hook;
		void COM_PlayIntroMovies()
		{
			const auto playIntro = Symbols::Singleplayer::Dvar_FindVar("intro");
			if (!IniConfig::ShouldShowIntroMovie() || !playIntro->current.enabled)
				return;

			Symbols::Singleplayer::Cbuf_AddText(0, "autocinematic title\n");
		}

		void Hooks()
		{
			// play our own intro movie
			COM_PlayIntroMovies_Hook.Create(0x82428EF0, COM_PlayIntroMovies);
		}

		void ClearHooks()
		{
			COM_PlayIntroMovies_Hook.Clear();
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
