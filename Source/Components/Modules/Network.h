#pragma once

namespace Network
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
