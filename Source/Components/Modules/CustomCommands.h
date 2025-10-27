#pragma once

namespace CustomCommands
{
#ifdef MP_MOD
	namespace MP
	{
		void Load();
		void Unload();
	}
#elif SP_MOD
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
