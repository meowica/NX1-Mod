// Thanks to Lil Poop for originally working on this and for the idea.

namespace IniConfig
{
	bool ShowIntroMovie = true;

	bool ShowWatermark = true;
	bool ShowFPSCounter = false;

	bool EnableMapEntsLoader = true;
	bool EnableRawFileLoader = true;

	bool EnablePhysPresetDumper = false;
	bool EnableMapEntsDumper = false;
	bool EnableLocalizeEntryDumper = false;
	bool EnableRawFileDumper = false;
	bool EnableStringTableDumper = false;
	bool EnableLeaderboardDefDumper = false;

	Util::INI g_Config;

	void LoadAndReadConfig()
	{
		std::string filePath = Util::String::VA("game:\\" BASE_FOLDER "\\" INI_CONFIG);
		if (!g_Config.Load(filePath))
		{
			auto win = Util::XBox::XShowMessageBox(
				0,
				L"Error - Missing Config",
				Util::String::VAW("Failed to load '%s'.\nNX1-Mod needs this config file to run.\n\nPlease add it to the NX1-Mod folder and try again.\n", INI_CONFIG));
			return;
		}

		ShowIntroMovie = g_Config.GetBoolean("Intro", "ShowIntroMovie", ShowIntroMovie);

		ShowWatermark  = g_Config.GetBoolean("Drawing", "ShowWatermark",  ShowWatermark);
		ShowFPSCounter = g_Config.GetBoolean("Drawing", "ShowFPSCounter", ShowFPSCounter);

		EnableMapEntsLoader = g_Config.GetBoolean("Asset Loaders", "EnableMapEntsLoader", EnableMapEntsLoader);
		EnableRawFileLoader = g_Config.GetBoolean("Asset Loaders", "EnableRawFileLoader", EnableRawFileLoader);

		EnablePhysPresetDumper = g_Config.GetBoolean("Asset Dumpers", "EnablePhysPresetDumper", EnablePhysPresetDumper);
		EnableMapEntsDumper = g_Config.GetBoolean("Asset Dumpers", "EnableMapEntsDumper", EnableMapEntsDumper);
		EnableLocalizeEntryDumper = g_Config.GetBoolean("Asset Dumpers", "EnableLocalizeEntryDumper", EnableLocalizeEntryDumper);
		EnableRawFileDumper = g_Config.GetBoolean("Asset Dumpers", "EnableRawFileDumper", EnableRawFileDumper);
		EnableStringTableDumper = g_Config.GetBoolean("Asset Dumpers", "EnableStringTableDumper", EnableStringTableDumper);
		EnableLeaderboardDefDumper = g_Config.GetBoolean("Asset Dumpers", "EnableLeaderboardDefDumper", EnableLeaderboardDefDumper);
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
