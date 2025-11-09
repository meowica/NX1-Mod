#pragma once

namespace GameLog
{
#ifdef IS_SINGLEPLAYER
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
