#pragma once

namespace IniConfig
{
	bool ShouldShowIntroMovie();

	bool ShouldShowWatermark();
	bool ShouldShowFPSCounter();

	bool ShouldEnableMapEntsLoader();

	bool ShouldEnablePhysPresetDumper();

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