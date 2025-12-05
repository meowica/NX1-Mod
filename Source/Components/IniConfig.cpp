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
	bool EnableFxEffectDefDumper = false;
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

	Util::INI g_config;

	void LoadConfig()
	{
		std::string filePath = Util::String::VA("game:\\" BASE_FOLDER "\\" PLUGIN_CONFIG);
		if (!g_config.Load(filePath))
		{
			auto win = Util::XBox::XShowMessageBox(
				0,
				L"Error - Missing Plugin Config",
				Util::String::VAW(
					"Failed to load '%s'.\nNX1-Mod needs this config file to run.\n"
					"\nPlease add it to the NX1-Mod folder and try again.\n", PLUGIN_CONFIG));
			return;
		}

		ShowIntroMovie = g_config.GetBoolean("Intro", "ShowIntroMovie", ShowIntroMovie);

		ShowWatermark  = g_config.GetBoolean("Drawing", "ShowWatermark",  ShowWatermark);
		ShowFPSCounter = g_config.GetBoolean("Drawing", "ShowFPSCounter", ShowFPSCounter);

		EnableMapEntsLoader = g_config.GetBoolean("Asset Loaders", "EnableMapEntsLoader", EnableMapEntsLoader);
		EnableRawFileLoader = g_config.GetBoolean("Asset Loaders", "EnableRawFileLoader", EnableRawFileLoader);
		EnableAddonMapEntsLoader = g_config.GetBoolean("Asset Loaders", "EnableAddonMapEntsLoader", EnableAddonMapEntsLoader);

		EnablePhysPresetDumper = g_config.GetBoolean("Asset Dumpers", "EnablePhysPresetDumper", EnablePhysPresetDumper);
		EnableSndVfCurveDumper = g_config.GetBoolean("Asset Dumpers", "EnableSndVfCurveDumper", EnableSndVfCurveDumper);
		EnableClipMapDumper = g_config.GetBoolean("Asset Dumpers", "EnableClipMapDumper", EnableClipMapDumper);
		EnableComWorldDumper = g_config.GetBoolean("Asset Dumpers", "EnableComWorldDumper", EnableComWorldDumper);
		EnableGameWorldSpDumper = g_config.GetBoolean("Asset Dumpers", "EnableGameWorldSpDumper", EnableGameWorldSpDumper);
		EnableGameWorldMpDumper = g_config.GetBoolean("Asset Dumpers", "EnableGameWorldMpDumper", EnableGameWorldMpDumper);
		EnableMapEntsDumper = g_config.GetBoolean("Asset Dumpers", "EnableMapEntsDumper", EnableMapEntsDumper);
		EnableFxWorldDumper = g_config.GetBoolean("Asset Dumpers", "EnableFxWorldDumper", EnableFxWorldDumper);
		EnableGfxWorldDumper = g_config.GetBoolean("Asset Dumpers", "EnableGfxWorldDumper", EnableGfxWorldDumper);
		EnableGfxLightDefDumper = g_config.GetBoolean("Asset Dumpers", "EnableGfxLightDefDumper", EnableGfxLightDefDumper);
		EnableFontHandleDumper = g_config.GetBoolean("Asset Dumpers", "EnableFontHandleDumper", EnableFontHandleDumper);
		EnableMenuListDumper = g_config.GetBoolean("Asset Dumpers", "EnableMenuListDumper", EnableMenuListDumper);
		EnableLocalizeEntryDumper = g_config.GetBoolean("Asset Dumpers", "EnableLocalizeEntryDumper", EnableLocalizeEntryDumper);
		EnableSndDriverGlobalsDumper = g_config.GetBoolean("Asset Dumpers", "EnableSndDriverGlobalsDumper", EnableSndDriverGlobalsDumper);
		EnableFxEffectDefDumper = g_config.GetBoolean("Asset Dumpers", "EnableFxEffectDefDumper", EnableFxEffectDefDumper);
		EnableRawFileDumper = g_config.GetBoolean("Asset Dumpers", "EnableRawFileDumper", EnableRawFileDumper);
		EnableStringTableDumper = g_config.GetBoolean("Asset Dumpers", "EnableStringTableDumper", EnableStringTableDumper);
		EnableLeaderboardDefDumper = g_config.GetBoolean("Asset Dumpers", "EnableLeaderboardDefDumper", EnableLeaderboardDefDumper);
		EnableStructuredDataDefSetDumper = g_config.GetBoolean("Asset Dumpers", "EnableStructuredDataDefSetDumper", EnableStructuredDataDefSetDumper);
		EnableTracerDefDumper = g_config.GetBoolean("Asset Dumpers", "EnableTracerDefDumper", EnableTracerDefDumper);
		EnableLaserDefDumper = g_config.GetBoolean("Asset Dumpers", "EnableLaserDefDumper", EnableLaserDefDumper);
		EnableAddonMapEntsDumper = g_config.GetBoolean("Asset Dumpers", "EnableAddonMapEntsDumper", EnableAddonMapEntsDumper);
		EnableShellShockParamDumper = g_config.GetBoolean("Asset Dumpers", "EnableShellShockParamDumper", EnableShellShockParamDumper);
		EnableAudioVolumeSettingDumper = g_config.GetBoolean("Asset Dumpers", "EnableAudioVolumeSettingDumper", EnableAudioVolumeSettingDumper);
		EnableRadVerbPresetDumper = g_config.GetBoolean("Asset Dumpers", "EnableRadVerbPresetDumper", EnableRadVerbPresetDumper);
		EnableFogDefDumper = g_config.GetBoolean("Asset Dumpers", "EnableFogDefDumper", EnableFogDefDumper);
	}

	void UnloadConfig()
	{
		g_config.Unload();
	}

#ifdef IS_MP
	namespace MP
	{
		void Load()
		{
			LoadConfig();
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
			LoadConfig();
		}

		void Unload()
		{
			UnloadConfig();
		}
	}
#endif
}
