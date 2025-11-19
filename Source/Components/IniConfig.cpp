// We could use an external lib for this, but I think this is better... for now atleast
// We're also pretty limited as this is in C++03-11
//
// Credits:
// - Lil Poop - Idea + inital work

namespace IniConfig
{
	// Variables

	// Intro
	static bool ShowIntroMovie = true;

	// Drawing
	static bool ShowWatermark = true;
	static bool ShowFPSCounter = false;

	// Loaders
	static bool EnableMapEntsLoader = true;
	static bool EnableRawFileLoader = true;

	// Dumpers
	static bool EnablePhysPresetDumper = false;
	static bool EnableRawFileDumper = false;

	static void ReadConfig()
	{
		const char* g_configPath = Util::String::VA("game:\\" BASE_FOLDER "\\NX1-Mod.ini");

		Util::INI iFile;
		if (!iFile.Load(g_configPath))
			return;

		// read the keys

		// Intro
		ShowIntroMovie = iFile.GetBool("Intro", "ShowIntroMovie", ShowIntroMovie);

		// Drawing
		ShowWatermark  = iFile.GetBool("Drawing", "ShowWatermark",  ShowWatermark);
		ShowFPSCounter = iFile.GetBool("Drawing", "ShowFPSCounter", ShowFPSCounter);

		// Loaders
		EnableMapEntsLoader = iFile.GetBool("Loaders", "EnableMapEntsLoader", EnableMapEntsLoader);
		EnableRawFileLoader = iFile.GetBool("Loaders", "EnableRawFileLoader", EnableRawFileLoader);

		// Dumpers
		EnablePhysPresetDumper = iFile.GetBool("Dumpers", "EnablePhysPresetDumper", EnablePhysPresetDumper);
		EnableRawFileDumper = iFile.GetBool("Dumpers", "EnableRawFileDumper", EnableRawFileDumper);
	}

	// Intro

	bool ShouldShowIntroMovie()
	{
		return ShowIntroMovie;
	}

	// Drawing

	bool ShouldShowWatermark()
	{
		return ShowWatermark;
	}

	bool ShouldShowFPSCounter()
	{
		return ShowFPSCounter;
	}

	// Loaders

	bool ShouldEnableMapEntsLoader()
	{
		return EnableMapEntsLoader;
	}

	bool ShouldEnableRawFileLoader()
	{
		return EnableRawFileLoader;
	}

	// Dumpers

	bool ShouldEnablePhysPresetDumper()
	{
		return EnablePhysPresetDumper;
	}

	bool ShouldEnableRawFileDumper()
	{
		return EnableRawFileDumper;
	}

#ifdef IS_MP
	namespace MP
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
#elif IS_SP
	namespace SP
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