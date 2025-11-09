#pragma once

namespace Config
{
	bool ShouldShowIntroMovie();

	bool ShouldShowWatermark();
	bool ShouldShowFPSCounter();

#ifdef IS_MULTIPLAYER
	namespace MP
	{
		void Load();
		void Unload();
	}
#elif IS_SINGLEPLAYER
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}