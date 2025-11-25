#pragma once

#include "IMapEnts.h"

namespace IAddonMapEnts
{
	struct AddonMapEnts
	{
		const char* name;
		char* entityString;
		int numEntityChars;
		IMapEnts::MapTriggers trigger;
	};

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
