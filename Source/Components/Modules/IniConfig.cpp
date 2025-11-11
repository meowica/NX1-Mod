// We could use an external lib for this, but i think this is better... for now atleast
// We're also pretty limited as this is in C++03-11
//
// Credits:
// - Lil Poop - idea + inital work
// - Wemino - for https://github.com/Wemino/EchoPatch, I used a few things from this patch

namespace IniConfig
{
	// =============================
	// Ini Variables
	// =============================

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

		// read our keys
		ShowIntroMovie = iniFile.GetBool("Intro", "ShowIntroMovie", ShowIntroMovie);
		ShowWatermark   = iniFile.GetBool("Drawing", "ShowWatermark", ShowWatermark);
		ShowFPSCounter  = iniFile.GetBool("Drawing", "ShowFPSCounter", ShowFPSCounter);
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