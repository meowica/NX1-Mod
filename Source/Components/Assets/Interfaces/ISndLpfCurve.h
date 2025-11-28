#pragma once

#include "ISndAliasList.h"

namespace ISndLpfCurve
{
	struct SndLpfCurve
	{
		const char* p_filename;
		ISndAliasList::SndCurve sndCurve;
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
