namespace IMapEnts
{
	struct Bounds
	{
		float midPoint[3];
		float halfSize[3];
	};

	struct TriggerModel
	{
		int contents;
		unsigned short hullCount;
		unsigned short firstHull;
	};

	struct TriggerHull
	{
		Bounds bounds;
		int contents;
		unsigned short slabCount;
		unsigned short firstSlab;
	};

	struct TriggerSlab
	{
		float dir[3];
		float midPoint;
		float halfSize;
	};

	struct MapTriggers
	{
		unsigned int count;
		TriggerModel* models;
		unsigned int hullCount;
		TriggerHull* hulls;
		unsigned int slabCount;
		TriggerSlab* slabs;
	};

	struct Stage
	{
		const char* name;
		float origin[3];
		unsigned short triggerIndex;
		unsigned char sunPrimaryLightIndex;
	};

	struct MapEnts
	{
		const char* name;
		char* entityString;
		int numEntityChars;
		MapTriggers trigger;
		Stage* stages;
		unsigned char stageCount;
	};

#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		Util::Hook::Detour Load_MapEntsPtr_Hook;
		void Load_MapEntsPtr(bool atStreamStart)
		{
			// based off this: https://github.com/michaeloliverx/codxe/blob/cbe7ea24ea1ff0378b327bb1a2dada2ba2831216/src/game/iw3/sp/main.cpp#L63

			auto varMapEntsPtr = *reinterpret_cast<MapEnts***>(0x82CE6DF8);

			auto Invoke = Load_MapEntsPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			// Validate pointer before dereferencing
			if (!varMapEntsPtr || !*varMapEntsPtr)
			{
				// TODO: change this to be Com_PrintError
				printf("Load_MapEntsPtr: varMapEntsPtr is NULL!\n");
				return;
			}

			MapEnts* mapEnts = *varMapEntsPtr;

			std::string rawFilePath = "game:\\" BASE_FOLDER "\\raw"; // example: game:/NX1-Mod/raw/maps/mp/mp_nx_pitstop.d3dbsp.ents

			rawFilePath += std::string("\\") + mapEnts->name;
			rawFilePath += ".ents";
			std::replace(rawFilePath.begin(), rawFilePath.end(), '/', '\\');

			if (!Util::FileSystem::FileExists(rawFilePath))
				return;

			std::string newEntityString = Util::FileSystem::ReadFileIntoString(rawFilePath);
			if (newEntityString.empty())
				return;

			// Allocate new memory and copy entity data (+1 for null terminator)
			const size_t newSize = newEntityString.size() + 1;
			if (char* newMemory = static_cast<char*>(malloc(newSize)))
			{
				memcpy(newMemory, newEntityString.c_str(), newSize); // includes null terminator
				mapEnts->entityString = newMemory;

				Symbols::Multiplayer::Com_Printf(0, "map ents '%s' has been overriden with '%s'.\n", mapEnts->name, rawFilePath.c_str());
			}
			else
			{
				// TODO: change this to be Com_PrintError
				printf("Failed to allocate memory for entityString replacement!\n");
			}
		}

		void Hooks()
		{
			Load_MapEntsPtr_Hook.Create(0x823102C8, Load_MapEntsPtr);
		}

		void ClearHooks()
		{
			Load_MapEntsPtr_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#elif IS_SINGLEPLAYER
	namespace Singleplayer
	{
		Util::Hook::Detour Load_MapEntsPtr_Hook;
		void Load_MapEntsPtr(bool atStreamStart)
		{
			// based off this: https://github.com/michaeloliverx/codxe/blob/cbe7ea24ea1ff0378b327bb1a2dada2ba2831216/src/game/iw3/sp/main.cpp#L63

			auto varMapEntsPtr = *reinterpret_cast<MapEnts***>(0x82C6E7F8);

			auto Invoke = Load_MapEntsPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			// Validate pointer before dereferencing
			if (!varMapEntsPtr || !*varMapEntsPtr)
			{
				// TODO: change this to be Com_PrintError
				printf("Load_MapEntsPtr: varMapEntsPtr is NULL!\n");
				return;
			}

			MapEnts* mapEnts = *varMapEntsPtr;

			std::string rawFilePath = "game:\\" BASE_FOLDER "\\raw"; // example: game:/NX1-Mod/raw/maps/nx_border.d3dbsp.ents

			rawFilePath += std::string("\\") + mapEnts->name;
			rawFilePath += ".ents";
			std::replace(rawFilePath.begin(), rawFilePath.end(), '/', '\\');

			if (!Util::FileSystem::FileExists(rawFilePath))
				return;

			std::string newEntityString = Util::FileSystem::ReadFileIntoString(rawFilePath);
			if (newEntityString.empty())
				return;

			// Allocate new memory and copy entity data (+1 for null terminator)
			const size_t newSize = newEntityString.size() + 1;
			if (char* newMemory = static_cast<char*>(malloc(newSize)))
			{
				memcpy(newMemory, newEntityString.c_str(), newSize); // includes null terminator
				mapEnts->entityString = newMemory;

				Symbols::Singleplayer::Com_Printf(0, "map ents '%s' has been overriden with '%s'.\n", mapEnts->name, rawFilePath.c_str());
			}
			else
			{
				// TODO: change this to be Com_PrintError
				printf("Failed to allocate memory for entityString replacement!\n");
			}
		}

		void Hooks()
		{
			Load_MapEntsPtr_Hook.Create(0x82259EF0, Load_MapEntsPtr);
		}

		void ClearHooks()
		{
			Load_MapEntsPtr_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif
}
