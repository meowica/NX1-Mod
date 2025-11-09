#pragma once

namespace GameLog
{
#ifdef IS_SINGLEPLAYER
	namespace Singleplayer
	{
		void Load();
		void Unload();
	}
#endif
}
