#pragma once

namespace Config
{
	bool ShouldShowIntroMovie();

	bool ShouldShowWatermark();
	bool ShouldShowFPSCounter();

#ifdef MP_MOD
	namespace MP
	{
		void Load();
		void Unload();
	}
#elif SP_MOD
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}