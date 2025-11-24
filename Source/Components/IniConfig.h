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

	// Dumpers
	extern bool EnablePhysPresetDumper;
	extern bool EnableMapEntsDumper;
	extern bool EnableFontHandleDumper;
	extern bool EnableMenuListDumper;
	extern bool EnableLocalizeEntryDumper;
	extern bool EnableRawFileDumper;
	extern bool EnableStringTableDumper;
	extern bool EnableLeaderboardDefDumper;
	extern bool EnableAudioVolumeSettingDumper;

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