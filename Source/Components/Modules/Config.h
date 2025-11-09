#pragma once

namespace Config
{
	bool ShouldShowIntroMovie();

	bool ShouldShowWatermark();
	bool ShouldShowFPSCounter();

#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		void Load();
		void Unload();
	}
#elif IS_SINGLEPLAYER
	namespace Singleplayer
	{
		void Load();
		void Unload();
	}
#endif
}