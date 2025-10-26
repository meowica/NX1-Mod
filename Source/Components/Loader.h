#pragma once

// modules
#ifdef INCLUDE_ASSET_DUMPERS
#include "Modules\Assets\Assets.h"
#endif
#include "Modules\Drawing.h"
#ifdef SP_MOD
#include "Modules\GameLog.h"
#endif
#include "Modules\Patches.h"

namespace Loader
{
	struct Module
	{
		const char* name;
		void (*load)();
		void (*unload)();
	};

#define MAX_MODULES 128 // big number, nobody should EVER have 128 modules
	extern Module g_modules[MAX_MODULES];
	extern int g_moduleCount;

	void RegisterModule(const char* name, void (*load)(), void (*unload)());
	void LoadAllModules();
	void UnloadAllModules();
}

#ifdef SP_MOD
	#define MODULE_NS(name) name::SP
#else
	#define MODULE_NS(name) name::MP
#endif

struct ModuleRegistrator
{
	ModuleRegistrator(const char* name, void (*load)(), void (*unload)())
	{
		Loader::RegisterModule(name, load, unload);
	}
};

#define REGISTER_MODULE(name) \
	static ModuleRegistrator _module_##name(#name, MODULE_NS(name)::Load, MODULE_NS(name)::Unload)
