#pragma once

#include "IFxEffectDef.h"

namespace IFxImpactTable
{
	struct FxImpactEntry
	{
		const IFxEffectDef::FxEffectDef* nonflesh[31];
		const IFxEffectDef::FxEffectDef* flesh[4];
	};

	struct FxImpactTable
	{
		const char* name;
		FxImpactEntry* table;
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
