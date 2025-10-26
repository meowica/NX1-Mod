#pragma once

namespace Patches
{
#ifdef MP_MOD
	namespace MP
	{
		void Load();
		void Unload();
	}
#endif

#ifdef SP_MOD
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
