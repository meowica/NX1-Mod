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
	extern bool EnableMapEntLoader;
	extern bool EnableRawFileLoader;

	// Dumpers
	extern bool EnablePhysPresetDumper;
	extern bool EnableRawFileDumper;
	extern bool EnableStringTableDumper;
	extern bool EnableLeaderboardDefDumper;

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