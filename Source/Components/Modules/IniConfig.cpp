// We could use an external lib for this, but I think this is better... for now atleast
// We're also pretty limited as this is in C++03-11
//
// Credits:
// - Lil Poop - Idea + inital work

namespace IniConfig
{
	// Intro
	static bool ShowIntroMovie = true;

	// Drawing
	static bool ShowWatermark = true;
	static bool ShowFPSCounter = false;

	static void ReadConfig()
	{
		const char* g_configPath = Util::String::VA("game:\\" BASE_FOLDER "\\NX1-Mod.ini");

		Util::Ini iniFile;
		if (!iniFile.Load(g_configPath))
			return;

		// read the keys

		// Intro
		ShowIntroMovie = iniFile.GetBool("Intro", "ShowIntroMovie", ShowIntroMovie);

		// Drawing
		ShowWatermark  = iniFile.GetBool("Drawing", "ShowWatermark",  ShowWatermark);
		ShowFPSCounter = iniFile.GetBool("Drawing", "ShowFPSCounter", ShowFPSCounter);
	}

	bool ShouldShowIntroMovie()
	{
		return ShowIntroMovie;
	}

	bool ShouldShowWatermark()
	{
		return ShowWatermark;
	}

	bool ShouldShowFPSCounter()
	{
		return ShowFPSCounter;
	}

#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		void Load()
		{
			ReadConfig();
		}

		void Unload()
		{
			// nothing
		}
	}
#elif IS_SINGLEPLAYER
	namespace Singleplayer
	{
		void Load()
		{
			ReadConfig();
		}

		void Unload()
		{
			// nothing
		}
	}
#endif
}