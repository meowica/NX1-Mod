#pragma once

// special modules
#include "Modules\Config.h"
#include "Modules\Assertion.h"
#include "Modules\Patches.h"
#include "Modules\CustomCommands.h"

// regular modules
#include "Modules\DevGui.h"
#include "Modules\Drawing.h"
#include "Modules\InternalConsole.h"
#include "Modules\Intro.h"
#include "Modules\Network.h"
#ifdef SP_MOD
#include "Modules\GameLog.h"
#endif

namespace Loader
{
	struct Module
	{
		const char* name;
		void (*load)();
		void (*unload)(); // does the plugin EVER call this??
	};

#define MAX_MODULES 256 // big number, nobody should EVER have 256 modules
	extern Module g_modules[MAX_MODULES];
	extern int g_moduleCount;

	void RegisterModule(const char* name, void (*load)(), void (*unload)());
	void LoadAllModules();
	void UnloadAllModules();

	void RegisterModules();
}

#ifdef MP_MOD
	#define MODULE_NAME(name) name::MP
#elif SP_MOD
	#define MODULE_NAME(name) name::SP
#endif

struct ModuleRegistrator
{
	ModuleRegistrator(const char* name, void (*load)(), void (*unload)())
	{
		Loader::RegisterModule(name, load, unload);
	}
};

#define REGISTER_MODULE(name) \
	static ModuleRegistrator _module_##name(#name, MODULE_NAME(name)::Load, MODULE_NAME(name)::Unload)
