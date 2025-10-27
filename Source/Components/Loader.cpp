namespace Loader
{
	Module g_modules[MAX_MODULES];
	int g_moduleCount = 0;

	void RegisterModule(const char* name, void (*load)(), void (*unload)())
	{
		// Check for duplicates
		for (int i = 0; i < g_moduleCount; ++i)
		{
			if (strcmp(g_modules[i].name, name) == 0)
				return; // Already registered
		}

		if (g_moduleCount < MAX_MODULES)
		{
			g_modules[g_moduleCount].name = name;
			g_modules[g_moduleCount].load = load;
			g_modules[g_moduleCount].unload = unload;
			g_moduleCount++;
		}
	}

	void LoadAllModules()
	{
		for (int i = 0; i < g_moduleCount; ++i)
		{
			if (g_modules[i].load)
				g_modules[i].load();
		}
	}

	void UnloadAllModules()
	{
		for (int i = g_moduleCount - 1; i >= 0; --i)
		{
			if (g_modules[i].unload)
				g_modules[i].unload();
		}

		g_moduleCount = 0;
	}

	void RegisterModules()
	{
		REGISTER_MODULE(Patches); // we want this to be first

		REGISTER_MODULE(CustomCommands); // yeah.. this would be nice to have pretty early

		REGISTER_MODULE(DevGui);
		REGISTER_MODULE(Drawing);
		REGISTER_MODULE(InternalConsole);
		REGISTER_MODULE(Intro);

	#ifdef SP_MOD
		REGISTER_MODULE(GameLog);
	#endif
	}
}