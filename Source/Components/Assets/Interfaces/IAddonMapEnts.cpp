#include "IAddonMapEnts.h"

namespace IAddonMapEnts
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_AddonEnts(const AddonMapEnts* addonMapEnts)
		{
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

		void Dump_AddonTriggers(const AddonMapEnts* addonMapEnts)
		{
			if (!addonMapEnts)
				return;

			std::string assetName = addonMapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".triggers";

			const IMapEnts::MapTriggers& trig = addonMapEnts->trigger;

			std::ostringstream oss;
			oss << "# TRIGGER MODELS (count = " << trig.count << ")\n";
			for (unsigned i = 0; i < trig.count; ++i)
			{
				const IMapEnts::TriggerModel& m = trig.models[i];
				oss << "model[" << i << "]\n";
				oss << "  contents: " << m.contents << "\n";
				oss << "  hullCount: " << m.hullCount << "\n";
				oss << "  firstHull: " << m.firstHull << "\n\n";
			}
			oss << "# TRIGGER HULLS (count = " << trig.hullCount << ")\n";
			for (unsigned i = 0; i < trig.hullCount; ++i)
			{
				const IMapEnts::TriggerHull& h = trig.hulls[i];
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
				const IMapEnts::TriggerSlab& s = trig.slabs[i];
				oss << "slab[" << i << "]\n";
				oss << "  dir: " << s.dir[0] << " " << s.dir[1] << " " << s.dir[2] << "\n";
				oss << "  midPoint: " << s.midPoint << "\n";
				oss << "  halfSize: " << s.halfSize << "\n\n";
			}

			const std::string out = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), out.data(), out.size());
		}

		void Dump_AddonMapEnts(const AddonMapEnts* addonMapEnts)
		{
			Dump_AddonEnts(addonMapEnts);
			Dump_AddonTriggers(addonMapEnts);
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
		void Dump_AddonEnts(const AddonMapEnts* addonMapEnts)
		{
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

		void Dump_AddonTriggers(const AddonMapEnts* addonMapEnts)
		{
			if (!addonMapEnts)
				return;

			std::string assetName = addonMapEnts->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\";
			outPath += assetName;
			outPath += ".triggers";

			const IMapEnts::MapTriggers& trig = addonMapEnts->trigger;

			std::ostringstream oss;
			oss << "# TRIGGER MODELS (count = " << trig.count << ")\n";
			for (unsigned i = 0; i < trig.count; ++i)
			{
				const IMapEnts::TriggerModel& m = trig.models[i];
				oss << "model[" << i << "]\n";
				oss << "  contents: " << m.contents << "\n";
				oss << "  hullCount: " << m.hullCount << "\n";
				oss << "  firstHull: " << m.firstHull << "\n\n";
			}
			oss << "# TRIGGER HULLS (count = " << trig.hullCount << ")\n";
			for (unsigned i = 0; i < trig.hullCount; ++i)
			{
				const IMapEnts::TriggerHull& h = trig.hulls[i];
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
				const IMapEnts::TriggerSlab& s = trig.slabs[i];
				oss << "slab[" << i << "]\n";
				oss << "  dir: " << s.dir[0] << " " << s.dir[1] << " " << s.dir[2] << "\n";
				oss << "  midPoint: " << s.midPoint << "\n";
				oss << "  halfSize: " << s.halfSize << "\n\n";
			}

			const std::string out = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), out.data(), out.size());
		}

		void Dump_AddonMapEnts(const AddonMapEnts* addonMapEnts)
		{
			Dump_AddonEnts(addonMapEnts);
			Dump_AddonTriggers(addonMapEnts);
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
