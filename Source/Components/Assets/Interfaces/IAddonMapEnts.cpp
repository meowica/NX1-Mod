namespace IAddonMapEnts
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

	struct AddonMapEnts
	{
		const char* name;
		char* entityString;
		int numEntityChars;
		MapTriggers trigger;
	};

#ifdef IS_MP
	namespace MP
	{
		void Dump_AddonMapEnts(const AddonMapEnts* addonMapEnts)
		{
			// TODO: maybe dump triggers too?

			if (!addonMapEnts)
				return;

			std::string assetName = addonMapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".ents";

			std::string cleaned;
			cleaned.reserve(addonMapEnts->numEntityChars);

			const char* src = addonMapEnts->entityString;
			for (int i = 0; i < addonMapEnts->numEntityChars; ++i)
			{
				if (src[i] != '\0')
					cleaned.push_back(src[i]);
			}

			Util::FileSystem::WriteFile(outPath.c_str(), cleaned.data(), cleaned.size());
		}

		void Load_AddonMapEnts(AddonMapEnts* addonMapEnts)
		{
			// TODO: maybe load triggers too?

			if (!addonMapEnts)
				return;

			std::string assetName = addonMapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string inPath = "game:\\" BASE_FOLDER "\\raw\\";
			inPath += assetName;
			inPath += ".ents";

			if (!Util::FileSystem::FileExists(inPath))
				return;

			std::string newEntityString = Util::FileSystem::ReadFileIntoString(inPath);
			if (newEntityString.empty())
				return;

			const size_t newSize = newEntityString.size() + 1;
			if (char* newMemory = static_cast<char*>(malloc(newSize)))
			{
				memcpy(newMemory, newEntityString.c_str(), newSize); // includes null terminator
				addonMapEnts->entityString = newMemory;

				Symbols::MP::Com_Printf(0, "addon map ents '%s' has been overriden with '%s'.\n", addonMapEnts->name, inPath.c_str());
			}
			else
			{
				Symbols::MP::Com_Printf(0, "Failed to allocate memory for entityString replacement!\n");
			}
		}

		Util::Hook::Detour Load_AddonMapEntsPtr_Hook;
		void Load_AddonMapEntsPtr(bool atStreamStart)
		{
			auto varAddonMapEntsPtr = *reinterpret_cast<AddonMapEnts***>(0x82CE6CD0);

			Load_AddonMapEntsPtr_Hook.Invoke<void>(atStreamStart);

			if (varAddonMapEntsPtr && *varAddonMapEntsPtr)
			{
				if (IniConfig::EnableAddonMapEntsDumper)
					Dump_AddonMapEnts(*varAddonMapEntsPtr);
				if (IniConfig::EnableAddonMapEntsLoader)
					Load_AddonMapEnts(*varAddonMapEntsPtr);
			}
		}

		void Load()
		{
			Load_AddonMapEntsPtr_Hook.Create(0x823108A0, Load_AddonMapEntsPtr);
		}

		void Unload()
		{
			Load_AddonMapEntsPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_AddonMapEnts(const AddonMapEnts* addonMapEnts)
		{
			// TODO: maybe dump triggers too?

			if (!addonMapEnts)
				return;

			std::string assetName = addonMapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".ents";

			std::string cleaned;
			cleaned.reserve(addonMapEnts->numEntityChars);

			const char* src = addonMapEnts->entityString;
			for (int i = 0; i < addonMapEnts->numEntityChars; ++i)
			{
				if (src[i] != '\0')
					cleaned.push_back(src[i]);
			}

			Util::FileSystem::WriteFile(outPath.c_str(), cleaned.data(), cleaned.size());
		}

		void Load_AddonMapEnts(AddonMapEnts* addonMapEnts)
		{
			// TODO: maybe load triggers too?

			if (!addonMapEnts)
				return;

			std::string assetName = addonMapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string inPath = "game:\\" BASE_FOLDER "\\raw\\";
			inPath += assetName;
			inPath += ".ents";

			if (!Util::FileSystem::FileExists(inPath))
				return;

			std::string newEntityString = Util::FileSystem::ReadFileIntoString(inPath);
			if (newEntityString.empty())
				return;

			const size_t newSize = newEntityString.size() + 1;
			if (char* newMemory = static_cast<char*>(malloc(newSize)))
			{
				memcpy(newMemory, newEntityString.c_str(), newSize); // includes null terminator
				addonMapEnts->entityString = newMemory;

				Symbols::SP::Com_Printf(0, "addon map ents '%s' has been overriden with '%s'.\n", addonMapEnts->name, inPath.c_str());
			}
			else
			{
				Symbols::SP::Com_Printf(0, "Failed to allocate memory for entityString replacement!\n");
			}
		}

		Util::Hook::Detour Load_AddonMapEntsPtr_Hook;
		void Load_AddonMapEntsPtr(bool atStreamStart)
		{
			auto varAddonMapEntsPtr = *reinterpret_cast<AddonMapEnts***>(0x82C6E6D0);

			Load_AddonMapEntsPtr_Hook.Invoke<void>(atStreamStart);

			if (varAddonMapEntsPtr && *varAddonMapEntsPtr)
			{
				if (IniConfig::EnableAddonMapEntsDumper)
					Dump_AddonMapEnts(*varAddonMapEntsPtr);
				if (IniConfig::EnableAddonMapEntsLoader)
					Load_AddonMapEnts(*varAddonMapEntsPtr);
			}
		}

		void Load()
		{
			Load_AddonMapEntsPtr_Hook.Create(0x8225A4C8, Load_AddonMapEntsPtr);
		}

		void Unload()
		{
			Load_AddonMapEntsPtr_Hook.Clear();
		}
	}
#endif
}
