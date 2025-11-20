#pragma once

namespace ILeaderboardDef
{
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
