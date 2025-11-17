namespace Maps
{
#ifdef IS_MP
	namespace MP
	{
		Util::Hook::Detour Com_GetBspFilename_Hook;
		void Com_GetBspFilename(char* filename, int size, const char* mapname)
		{
			// TODO: add addon_map shit

			bool isMP = (strncmp(mapname, "mp_", 3) == 0);

			if (isMP)
			{
				sprintf_s(filename, size, "maps/mp/%s.d3dbsp", mapname);
			}
			else
			{
				sprintf_s(filename, size, "maps/%s.d3dbsp", mapname);
			}
		}

		void Load()
		{
			Com_GetBspFilename_Hook.Create(0x82530268, Com_GetBspFilename);
		}

		void Unload()
		{
			Com_GetBspFilename_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		Util::Hook::Detour Com_GetBspFilename_Hook;
		void Com_GetBspFilename(char* filename, int size, const char* mapname)
		{
			// TODO: add addon_map shit

			bool isMP = (strncmp(mapname, "mp_", 3) == 0);

			if (isMP)
			{
				sprintf_s(filename, size, "maps/mp/%s.d3dbsp", mapname);
			}
			else
			{
				sprintf_s(filename, size, "maps/%s.d3dbsp", mapname);
			}
		}

		void Load()
		{
			Com_GetBspFilename_Hook.Create(0x824C3FC0, Com_GetBspFilename);
		}

		void Unload()
		{
			Com_GetBspFilename_Hook.Clear();
		}
	}
#endif
}
