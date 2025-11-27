#pragma once

#include "IFxEffectDef.h"

namespace ISurfaceFxTable
{
	struct SurfaceFxEntry
	{
		const IFxEffectDef::FxEffectDef* surfaceEffect[31];
	};

	struct SurfaceFxTable
	{
		const char* name;
		SurfaceFxEntry* table;
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
