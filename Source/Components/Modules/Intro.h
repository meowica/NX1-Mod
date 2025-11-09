#pragma once

namespace Intro
{
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
