#include "IMapEnts.h"

namespace IMapEnts
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_MapEnts(const MapEnts* mapEnts)
		{
			// TODO: maybe dump triggers and stages too?

			if (!mapEnts)
				return;

			std::string assetName = mapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".ents";

			std::string cleaned;
			cleaned.reserve(mapEnts->numEntityChars);

			const char* src = mapEnts->entityString;
			for (int i = 0; i < mapEnts->numEntityChars; ++i)
			{
				if (src[i] != '\0')
					cleaned.push_back(src[i]);
			}

			Util::FileSystem::WriteFile(outPath.c_str(), cleaned.data(), cleaned.size());
		}

		void Load_MapEnts(MapEnts* mapEnts)
		{
			// TODO: maybe load triggers and stages too?

			if (!mapEnts)
				return;

			std::string assetName = mapEnts->name;
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
				mapEnts->entityString = newMemory;

				Symbols::MP::Com_Printf(0, "map ents '%s' has been overriden with '%s'.\n", mapEnts->name, inPath.c_str());
			}
			else
			{
				Symbols::MP::Com_Printf(0, "Failed to allocate memory for entityString replacement!\n");
			}
		}

		Util::Hook::Detour Load_MapEntsPtr_Hook;
		void Load_MapEntsPtr(bool atStreamStart)
		{
			auto varMapEntsPtr = *reinterpret_cast<MapEnts***>(0x82CE6DF8);

			Load_MapEntsPtr_Hook.Invoke<void>(atStreamStart);

			if (varMapEntsPtr && *varMapEntsPtr)
			{
				if (IniConfig::EnableMapEntsDumper)
					Dump_MapEnts(*varMapEntsPtr);
				if (IniConfig::EnableMapEntsLoader)
					Load_MapEnts(*varMapEntsPtr);
			}
		}

		void Load()
		{
			Load_MapEntsPtr_Hook.Create(0x823102C8, Load_MapEntsPtr);
		}

		void Unload()
		{
			Load_MapEntsPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_MapEnts(const MapEnts* mapEnts)
		{
			// TODO: maybe dump triggers and stages too?

			if (!mapEnts)
				return;

			std::string assetName = mapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".ents";

			std::string cleaned;
			cleaned.reserve(mapEnts->numEntityChars);

			const char* src = mapEnts->entityString;
			for (int i = 0; i < mapEnts->numEntityChars; ++i)
			{
				if (src[i] != '\0')
					cleaned.push_back(src[i]);
			}

			Util::FileSystem::WriteFile(outPath.c_str(), cleaned.data(), cleaned.size());
		}

		void Load_MapEnts(MapEnts* mapEnts)
		{
			// TODO: maybe load triggers and stages too?

			if (!mapEnts)
				return;

			std::string assetName = mapEnts->name;
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
				mapEnts->entityString = newMemory;

				Symbols::SP::Com_Printf(0, "map ents '%s' has been overriden with '%s'.\n", mapEnts->name, inPath.c_str());
			}
			else
			{
				Symbols::SP::Com_Printf(0, "Failed to allocate memory for entityString replacement!\n");
			}
		}

		Util::Hook::Detour Load_MapEntsPtr_Hook;
		void Load_MapEntsPtr(bool atStreamStart)
		{
			auto varMapEntsPtr = *reinterpret_cast<MapEnts***>(0x82C6E7F8);

			Load_MapEntsPtr_Hook.Invoke<void>(atStreamStart);

			if (varMapEntsPtr && *varMapEntsPtr)
			{
				if (IniConfig::EnableMapEntsDumper)
					Dump_MapEnts(*varMapEntsPtr);
				if (IniConfig::EnableMapEntsLoader)
					Load_MapEnts(*varMapEntsPtr);
			}
		}

		void Load()
		{
			Load_MapEntsPtr_Hook.Create(0x82259EF0, Load_MapEntsPtr);
		}

		void Unload()
		{
			Load_MapEntsPtr_Hook.Clear();
		}
	}
#endif
}
