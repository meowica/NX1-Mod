namespace Maps
{
#ifdef IS_MP
	namespace MP
	{
		Util::Hook::Detour Com_GetBspFilename_Hook;
		void Com_GetBspFilename(char* filename, unsigned int size, const char* p_mapname)
		{
			// TODO: Maybe let's just intercept the Com_sprintf so we don't have to reimplement this all?

			const char* baseName = p_mapname;

			bool isAddonMap = false;

			if (Symbols::MP::I_strnicmp(p_mapname, "so_", 3) == 0)
			{
				if (strchr(p_mapname + 3, '_'))
				{
					isAddonMap = true;
				}
			}

			if (isAddonMap)
			{
				baseName = Symbols::MP::Com_GetBaseMapName(p_mapname);
			}

			bool isMP = (strncmp(p_mapname, "mp_", 3) == 0);

			if (isMP)
			{
				Symbols::MP::Com_sprintf(filename, size, "maps/mp/%s.d3dbsp", p_mapname);
			}
			else
			{
				Symbols::MP::Com_sprintf(filename, size, "maps/%s.d3dbsp", p_mapname);
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
		void Com_GetBspFilename(char* filename, unsigned int size, const char* p_mapname)
		{
			// TODO: Maybe let's just intercept the Com_sprintf so we don't have to reimplement this all?

			const char* baseName = p_mapname;

			bool isAddonMap = false;

			if (Symbols::SP::I_strnicmp(p_mapname, "so_", 3) == 0)
			{
				if (strchr(p_mapname + 3, '_'))
					isAddonMap = true;
			}

			if (isAddonMap)
				baseName = Symbols::SP::Com_GetBaseMapName(p_mapname);

			bool isMP = (strncmp(p_mapname, "mp_", 3) == 0);

			if (isMP)
			{
				Symbols::SP::Com_sprintf(filename, size, "maps/mp/%s.d3dbsp", p_mapname);
			}
			else
			{
				Symbols::SP::Com_sprintf(filename, size, "maps/%s.d3dbsp", p_mapname);
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
