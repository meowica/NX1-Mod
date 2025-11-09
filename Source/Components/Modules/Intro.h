#pragma once

namespace Intro
{
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
