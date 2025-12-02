// Thanks to Lil Poop for originally working on this and for the idea.

namespace IniConfig
{
	bool ShowIntroMovie = true;

	bool ShowWatermark = true;
	bool ShowFPSCounter = false;

	bool EnableMapEntsLoader = true;
	bool EnableRawFileLoader = true;
	bool EnableAddonMapEntsLoader = true;

	bool EnablePhysPresetDumper = false;
	bool EnableSndVfCurveDumper = false;
	bool EnableClipMapDumper = false;
	bool EnableComWorldDumper = false;
	bool EnableGameWorldSpDumper = false;
	bool EnableGameWorldMpDumper = false;
	bool EnableMapEntsDumper = false;
	bool EnableFxWorldDumper = false;
	bool EnableGfxWorldDumper = false;
	bool EnableGfxLightDefDumper = false;
	bool EnableFontHandleDumper = false;
	bool EnableMenuListDumper = false;
	bool EnableLocalizeEntryDumper = false;
	bool EnableSndDriverGlobalsDumper = false;
	bool EnableRawFileDumper = false;
	bool EnableStringTableDumper = false;
	bool EnableLeaderboardDefDumper = false;
	bool EnableStructuredDataDefSetDumper = false;
	bool EnableTracerDefDumper = false;
	bool EnableLaserDefDumper = false;
	bool EnableAddonMapEntsDumper = false;
	bool EnableShellShockParamDumper = false;
	bool EnableAudioVolumeSettingDumper = false;
	bool EnableRadVerbPresetDumper = false;
	bool EnableFogDefDumper = false;

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
		EnableAddonMapEntsLoader = g_Config.GetBoolean("Asset Loaders", "EnableAddonMapEntsLoader", EnableAddonMapEntsLoader);

		EnablePhysPresetDumper = g_Config.GetBoolean("Asset Dumpers", "EnablePhysPresetDumper", EnablePhysPresetDumper);
		EnableSndVfCurveDumper = g_Config.GetBoolean("Asset Dumpers", "EnableSndVfCurveDumper", EnableSndVfCurveDumper);
		EnableClipMapDumper = g_Config.GetBoolean("Asset Dumpers", "EnableClipMapDumper", EnableClipMapDumper);
		EnableComWorldDumper = g_Config.GetBoolean("Asset Dumpers", "EnableComWorldDumper", EnableComWorldDumper);
		EnableGameWorldSpDumper = g_Config.GetBoolean("Asset Dumpers", "EnableGameWorldSpDumper", EnableGameWorldSpDumper);
		EnableGameWorldMpDumper = g_Config.GetBoolean("Asset Dumpers", "EnableGameWorldMpDumper", EnableGameWorldMpDumper);
		EnableMapEntsDumper = g_Config.GetBoolean("Asset Dumpers", "EnableMapEntsDumper", EnableMapEntsDumper);
		EnableFxWorldDumper = g_Config.GetBoolean("Asset Dumpers", "EnableFxWorldDumper", EnableFxWorldDumper);
		EnableGfxWorldDumper = g_Config.GetBoolean("Asset Dumpers", "EnableGfxWorldDumper", EnableGfxWorldDumper);
		EnableGfxLightDefDumper = g_Config.GetBoolean("Asset Dumpers", "EnableGfxLightDefDumper", EnableGfxLightDefDumper);
		EnableFontHandleDumper = g_Config.GetBoolean("Asset Dumpers", "EnableFontHandleDumper", EnableFontHandleDumper);
		EnableMenuListDumper = g_Config.GetBoolean("Asset Dumpers", "EnableMenuListDumper", EnableMenuListDumper);
		EnableLocalizeEntryDumper = g_Config.GetBoolean("Asset Dumpers", "EnableLocalizeEntryDumper", EnableLocalizeEntryDumper);
		EnableSndDriverGlobalsDumper = g_Config.GetBoolean("Asset Dumpers", "EnableSndDriverGlobalsDumper", EnableSndDriverGlobalsDumper);
		EnableRawFileDumper = g_Config.GetBoolean("Asset Dumpers", "EnableRawFileDumper", EnableRawFileDumper);
		EnableStringTableDumper = g_Config.GetBoolean("Asset Dumpers", "EnableStringTableDumper", EnableStringTableDumper);
		EnableLeaderboardDefDumper = g_Config.GetBoolean("Asset Dumpers", "EnableLeaderboardDefDumper", EnableLeaderboardDefDumper);
		EnableStructuredDataDefSetDumper = g_Config.GetBoolean("Asset Dumpers", "EnableStructuredDataDefSetDumper", EnableStructuredDataDefSetDumper);
		EnableTracerDefDumper = g_Config.GetBoolean("Asset Dumpers", "EnableTracerDefDumper", EnableTracerDefDumper);
		EnableLaserDefDumper = g_Config.GetBoolean("Asset Dumpers", "EnableLaserDefDumper", EnableLaserDefDumper);
		EnableAddonMapEntsDumper = g_Config.GetBoolean("Asset Dumpers", "EnableAddonMapEntsDumper", EnableAddonMapEntsDumper);
		EnableShellShockParamDumper = g_Config.GetBoolean("Asset Dumpers", "EnableShellShockParamDumper", EnableShellShockParamDumper);
		EnableAudioVolumeSettingDumper = g_Config.GetBoolean("Asset Dumpers", "EnableAudioVolumeSettingDumper", EnableAudioVolumeSettingDumper);
		EnableRadVerbPresetDumper = g_Config.GetBoolean("Asset Dumpers", "EnableRadVerbPresetDumper", EnableRadVerbPresetDumper);
		EnableFogDefDumper = g_Config.GetBoolean("Asset Dumpers", "EnableFogDefDumper", EnableFogDefDumper);
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
