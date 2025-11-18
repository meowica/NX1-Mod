#pragma once

namespace IPhysPreset
{
#ifdef IS_MP
	namespace MP
	{
		void Dump();
		void Load();
		void Unload();
	}
#elif IS_SP
	namespace SP
	{
		void Dump();
		void Load();
		void Unload();
	}
#endif
}
