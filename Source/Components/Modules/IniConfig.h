#pragma once

namespace IniConfig
{
	bool ShouldShowIntroMovie();

	bool ShouldShowWatermark();
	bool ShouldShowFPSCounter();

	bool ShouldEnableMapEntsLoader();

#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		void Load();
		void Unload();
	}
#endif // IS_MULTIPLAYER

#ifdef IS_SINGLEPLAYER
	namespace Singleplayer
	{
		void Load();
		void Unload();
	}
#endif // IS_SINGLEPLAYER
}