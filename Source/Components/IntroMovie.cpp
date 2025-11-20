namespace IntroMovie
{
#ifdef IS_MP
	namespace MP
	{
		Util::Hook::Detour SV_InitServerThread_Hook;
		void SV_InitServerThread()
		{
			SV_InitServerThread_Hook.Invoke<void>();

			auto playIntro = Symbols::MP::Dvar_FindVar("intro");
			if (!IniConfig::ShowIntroMovie || !playIntro->current.enabled)
				return;

			Symbols::MP::Cbuf_AddText(0, "autocinematic title\n");
		}

		void Load()
		{
			SV_InitServerThread_Hook.Create(0x824DEB90, SV_InitServerThread);
		}

		void Unload()
		{
			SV_InitServerThread_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		Util::Hook::Detour COM_PlayIntroMovies_Hook;
		void COM_PlayIntroMovies()
		{
			auto playIntro = Symbols::SP::Dvar_FindVar("intro");
			if (!IniConfig::ShowIntroMovie || !playIntro->current.enabled)
				return;

			Symbols::SP::Cbuf_AddText(0, "autocinematic title\n");
		}

		void Load()
		{
			COM_PlayIntroMovies_Hook.Create(0x82428EF0, COM_PlayIntroMovies);
		}

		void Unload()
		{
			COM_PlayIntroMovies_Hook.Clear();
		}
	}
#endif
}
