// special modules
#include "Components\IniConfig.h"
#include "Components\Assertion.h"

// regular modules
#include "Components\Assets\AssetHandler.h"
#include "Components\CustomCommands.h"
#include "Components\DevGui.h"
#include "Components\Drawing.h"
#include "Components\InternalConsole.h"
#include "Components\IntroMovie.h"
#include "Components\Log.h"
#include "Components\Maps.h"
#include "Components\Network.h"
#include "Components\Patches.h"

// special components
REGISTER_COMPONENT(IniConfig);
REGISTER_COMPONENT(Assertion);

// regular components
REGISTER_COMPONENT(AssetHandler);
REGISTER_COMPONENT(CustomCommands);
REGISTER_COMPONENT(DevGui);
REGISTER_COMPONENT(Drawing);
REGISTER_COMPONENT(InternalConsole);
REGISTER_COMPONENT(IntroMovie);
REGISTER_COMPONENT(Log);
REGISTER_COMPONENT(Maps);
REGISTER_COMPONENT(Network);
REGISTER_COMPONENT(Patches);

namespace Loader
{
	Component g_components[MAX_COMPONENTS];
	int g_componentCount = 0;

	void RegisterComponent(const char* name, void (*load)(), void (*unload)())
	{
		// check for duplicates
		for (int i = 0; i < g_componentCount; ++i)
		{
			if (strcmp(g_components[i].name, name) == 0)
				return; // already registered
		}

		if (g_componentCount < MAX_COMPONENTS)
		{
			g_components[g_componentCount].name = name;
			g_components[g_componentCount].load = load;
			g_components[g_componentCount].unload = unload;
			g_componentCount++;
		}
	}

	void LoadComponents()
	{
		for (int i = 0; i < g_componentCount; ++i)
		{
			if (g_components[i].load)
				g_components[i].load();
		}
	}

	void UnloadComponents()
	{
		for (int i = g_componentCount - 1; i >= 0; --i)
		{
			if (g_components[i].unload)
				g_components[i].unload();
		}

		g_componentCount = 0;
	}
}
