// Thanks to Lil Poop for originally working on this and for the idea.

namespace IniConfig
{
	bool ShowIntroMovie = true;

	bool ShowWatermark = true;
	bool ShowFPSCounter = false;

	bool EnableMapEntLoader = true;
	bool EnableRawFileLoader = true;

	bool EnablePhysPresetDumper = false;
	bool EnableRawFileDumper = false;

	Util::INI g_Config;

	void LoadAndReadConfig()
	{
		std::string filePath = Util::String::VA("game:\\" BASE_FOLDER "\\" INI_CONFIG);
		if (!g_Config.Load(filePath))
			return;

		ShowIntroMovie = g_Config.GetBoolean("Intro", "ShowIntroMovie", ShowIntroMovie);

		ShowWatermark  = g_Config.GetBoolean("Drawing", "ShowWatermark",  ShowWatermark);
		ShowFPSCounter = g_Config.GetBoolean("Drawing", "ShowFPSCounter", ShowFPSCounter);

		EnableMapEntLoader = g_Config.GetBoolean("Asset Loaders", "EnableMapEntLoader", EnableMapEntLoader);
		EnableRawFileLoader = g_Config.GetBoolean("Asset Loaders", "EnableRawFileLoader", EnableRawFileLoader);

		EnablePhysPresetDumper = g_Config.GetBoolean("Asset Dumpers", "EnablePhysPresetDumper", EnablePhysPresetDumper);
		EnableRawFileDumper = g_Config.GetBoolean("Asset Dumpers", "EnableRawFileDumper", EnableRawFileDumper);
	}

	void UnloadConfig()
	{
		g_Config.Unload();
	}

#ifdef IS_MP
	namespace MP
	{
		void Load()
		{
			LoadAndReadConfig();
		}

		void Unload()
		{
			UnloadConfig();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Load()
		{
			LoadAndReadConfig();
		}

		void Unload()
		{
			UnloadConfig();
		}
	}
#endif
}
