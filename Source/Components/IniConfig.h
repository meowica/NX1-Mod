#pragma once

namespace IniConfig
{
	// Variables

	// Intro
	extern bool ShowIntroMovie;

	// Drawing
	extern bool ShowWatermark;
	extern bool ShowFPSCounter;

	// Loaders
	extern bool EnableMapEntsLoader;
	extern bool EnableRawFileLoader;
	extern bool EnableAddonMapEntsLoader;

	// Dumpers
	extern bool EnablePhysPresetDumper;
	extern bool EnableSndVfCurveDumper;
	extern bool EnableClipMapDumper;
	extern bool EnableComWorldDumper;
	extern bool EnableGameWorldSpDumper;
	extern bool EnableGameWorldMpDumper;
	extern bool EnableMapEntsDumper;
	extern bool EnableFxWorldDumper;
	extern bool EnableGfxWorldDumper;
	extern bool EnableGfxLightDefDumper;
	extern bool EnableFontHandleDumper;
	extern bool EnableMenuListDumper;
	extern bool EnableMenuDefDumper;
	extern bool EnableLocalizeEntryDumper;
	extern bool EnableSndDriverGlobalsDumper;
	extern bool EnableFxEffectDefDumper;
	extern bool EnableRawFileDumper;
	extern bool EnableStringTableDumper;
	extern bool EnableLeaderboardDefDumper;
	extern bool EnableStructuredDataDefSetDumper;
	extern bool EnableTracerDefDumper;
	extern bool EnableLaserDefDumper;
	extern bool EnableAddonMapEntsDumper;
	extern bool EnableShellShockParamDumper;
	extern bool EnableAudioVolumeSettingDumper;
	extern bool EnableRadVerbPresetDumper;
	extern bool EnableFogDefDumper;

#ifdef IS_MP
	namespace MP
	{
		void Load();
		void Unload();
	}
#elif IS_SP
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}