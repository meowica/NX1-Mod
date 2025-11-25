#include "IMapEnts.h"

namespace IMapEnts
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_Ents(const MapEnts* mapEnts)
		{
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

		void Dump_Triggers(const MapEnts* mapEnts)
		{
			if (!mapEnts)
				return;

			std::string assetName = mapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".triggers";

			const MapTriggers& trig = mapEnts->trigger;

			std::ostringstream oss;
			oss << "# TRIGGER MODELS (count = " << trig.count << ")\n";
			for (unsigned i = 0; i < trig.count; ++i)
			{
				const TriggerModel& m = trig.models[i];
				oss << "model[" << i << "]\n";
				oss << "  contents: " << m.contents << "\n";
				oss << "  hullCount: " << m.hullCount << "\n";
				oss << "  firstHull: " << m.firstHull << "\n\n";
			}
			oss << "# TRIGGER HULLS (count = " << trig.hullCount << ")\n";
			for (unsigned i = 0; i < trig.hullCount; ++i)
			{
				const TriggerHull& h = trig.hulls[i];
				oss << "hull[" << i << "]\n";
				oss << "  bounds.midPoint: " << h.bounds.midPoint[0] << " " << h.bounds.midPoint[1] << " " << h.bounds.midPoint[2] << "\n";
				oss << "  bounds.halfSize: " << h.bounds.halfSize[0] << " " << h.bounds.halfSize[1] << " " << h.bounds.halfSize[2] << "\n";
				oss << "  contents: " << h.contents << "\n";
				oss << "  slabCount: " << h.slabCount << "\n";
				oss << "  firstSlab: " << h.firstSlab << "\n\n";
			}
			oss << "# TRIGGER SLABS (count = " << trig.slabCount << ")\n";
			for (unsigned i = 0; i < trig.slabCount; ++i)
			{
				const TriggerSlab& s = trig.slabs[i];
				oss << "slab[" << i << "]\n";
				oss << "  dir: " << s.dir[0] << " " << s.dir[1] << " " << s.dir[2] << "\n";
				oss << "  midPoint: " << s.midPoint << "\n";
				oss << "  halfSize: " << s.halfSize << "\n\n";
			}

			const std::string out = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), out.data(), out.size());
		}

		void Dump_Stages(const MapEnts* mapEnts)
		{
			if (!mapEnts)
				return;

			std::string assetName = mapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".stages";

			std::ostringstream oss;
			oss << "# STAGES (count = " << (int)mapEnts->stageCount << ")\n\n";
			for (unsigned i = 0; i < mapEnts->stageCount; ++i)
			{
				const Stage& s = mapEnts->stages[i];

				oss << "stage[" << i << "]\n";
				oss << "  name: " << s.name << "\n";
				oss << "  origin: " << s.origin[0] << " " << s.origin[1] << " " << s.origin[2] << "\n";
				oss << "  triggerIndex: " << s.triggerIndex << "\n";
				oss << "  sunPrimaryLightIndex: " << (int)s.sunPrimaryLightIndex << "\n\n";
			}

			const std::string out = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), out.data(), out.size());
		}

		void Dump_MapEnts(const MapEnts* mapEnts)
		{
			Dump_Ents(mapEnts);
			Dump_Triggers(mapEnts);
			Dump_Stages(mapEnts);
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
		void Dump_Ents(const MapEnts* mapEnts)
		{
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

		void Dump_Triggers(const MapEnts* mapEnts)
		{
			if (!mapEnts)
				return;

			std::string assetName = mapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".triggers";

			const MapTriggers& trig = mapEnts->trigger;

			std::ostringstream oss;
			oss << "# TRIGGER MODELS (count = " << trig.count << ")\n";
			for (unsigned i = 0; i < trig.count; ++i)
			{
				const TriggerModel& m = trig.models[i];
				oss << "model[" << i << "]\n";
				oss << "  contents: " << m.contents << "\n";
				oss << "  hullCount: " << m.hullCount << "\n";
				oss << "  firstHull: " << m.firstHull << "\n\n";
			}
			oss << "# TRIGGER HULLS (count = " << trig.hullCount << ")\n";
			for (unsigned i = 0; i < trig.hullCount; ++i)
			{
				const TriggerHull& h = trig.hulls[i];
				oss << "hull[" << i << "]\n";
				oss << "  bounds.midPoint: " << h.bounds.midPoint[0] << " " << h.bounds.midPoint[1] << " " << h.bounds.midPoint[2] << "\n";
				oss << "  bounds.halfSize: " << h.bounds.halfSize[0] << " " << h.bounds.halfSize[1] << " " << h.bounds.halfSize[2] << "\n";
				oss << "  contents: " << h.contents << "\n";
				oss << "  slabCount: " << h.slabCount << "\n";
				oss << "  firstSlab: " << h.firstSlab << "\n\n";
			}
			oss << "# TRIGGER SLABS (count = " << trig.slabCount << ")\n";
			for (unsigned i = 0; i < trig.slabCount; ++i)
			{
				const TriggerSlab& s = trig.slabs[i];
				oss << "slab[" << i << "]\n";
				oss << "  dir: " << s.dir[0] << " " << s.dir[1] << " " << s.dir[2] << "\n";
				oss << "  midPoint: " << s.midPoint << "\n";
				oss << "  halfSize: " << s.halfSize << "\n\n";
			}

			const std::string out = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), out.data(), out.size());
		}

		void Dump_Stages(const MapEnts* mapEnts)
		{
			if (!mapEnts)
				return;

			std::string assetName = mapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".stages";

			std::ostringstream oss;
			oss << "# STAGES (count = " << (int)mapEnts->stageCount << ")\n\n";
			for (unsigned i = 0; i < mapEnts->stageCount; ++i)
			{
				const Stage& s = mapEnts->stages[i];

				oss << "stage[" << i << "]\n";
				oss << "  name: " << s.name << "\n";
				oss << "  origin: " << s.origin[0] << " " << s.origin[1] << " " << s.origin[2] << "\n";
				oss << "  triggerIndex: " << s.triggerIndex << "\n";
				oss << "  sunPrimaryLightIndex: " << (int)s.sunPrimaryLightIndex << "\n\n";
			}

			const std::string out = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), out.data(), out.size());
		}

		void Dump_MapEnts(const MapEnts* mapEnts)
		{
			Dump_Ents(mapEnts);
			Dump_Triggers(mapEnts);
			Dump_Stages(mapEnts);
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
