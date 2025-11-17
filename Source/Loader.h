#pragma once

namespace Loader
{
	struct Component
	{
		const char* name;
		void (*load)();
		void (*unload)();
	};

#define MAX_COMPONENTS 512 // big number, nobody should EVER have 512 components
	extern Component g_components[MAX_COMPONENTS];
	extern int g_componentCount;

	void RegisterComponent(const char* name, void (*load)(), void (*unload)());

	void LoadComponents();
	void UnloadComponents();
}

// TODO: should we add a fallback??
#ifdef IS_MP
	#define COMPONENT_NAME(name) name::MP
#elif IS_SP
	#define COMPONENT_NAME(name) name::SP
#endif

struct ComponentRegistrator
{
	ComponentRegistrator(const char* name, void (*load)(), void (*unload)())
	{
		Loader::RegisterComponent(name, load, unload);
	}
};

#define REGISTER_COMPONENT(name) \
    static ComponentRegistrator componentEntry_##name( \
        #name, \
        COMPONENT_NAME(name)::Load, \
        COMPONENT_NAME(name)::Unload)
