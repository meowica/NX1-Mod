namespace IPhysPreset
{
	struct sndPhysicsParams
	{
		float soundPitchLow;
		float soundPitchHigh;
		float soundVolLow;
		float soundVolHigh;
		float soundImpactRangeLow;
		float soundImpactRangeHigh;
	};

	struct PhysPreset
	{
		const char* name;
		int type;
		float mass;
		float bounce;
		float friction;
		float bulletForceScale;
		float explosiveForceScale;
		const char* sndAliasPrefix;
		sndPhysicsParams sndParams;
		float piecesSpreadFraction;
		float piecesUpwardVelocity;
		bool tempDefaultToCylinder;
		bool perSurfaceSndAlias;
	};

#ifdef IS_MP
	namespace MP
	{
		void Dump_PhysPreset(const PhysPreset* physPreset)
		{
			if (!physPreset)
				return;

			std::string assetName = physPreset->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\physic\\" + assetName;
			std::ostringstream oss;

			oss << "PHYSIC"
				<< "\\sndAliasPrefix\\" << physPreset->sndAliasPrefix
				<< "\\mass\\" << physPreset->mass
				<< "\\friction\\" << physPreset->friction
				<< "\\isFrictionInfinity\\0" // always 0
				<< "\\bounce\\" << physPreset->bounce
				<< "\\bulletForceScale\\" << physPreset->bulletForceScale
				<< "\\explosiveForceScale\\" << physPreset->explosiveForceScale
				<< "\\piecesSpreadFraction\\" << physPreset->piecesSpreadFraction
				<< "\\piecesUpwardVelocity\\" << physPreset->piecesUpwardVelocity
				<< "\\tempDefaultToCylinder\\" << ((physPreset->tempDefaultToCylinder) ? 1 : 0)
				<< "\\perSurfaceSndAlias\\" << ((physPreset->perSurfaceSndAlias) ? 1 : 0)
				<< "\n";

			oss << "SND_PARAMS"
				<< "\\soundPitchLow\\" << physPreset->sndParams.soundPitchLow
				<< "\\soundPitchHigh\\" << physPreset->sndParams.soundPitchHigh
				<< "\\soundVolLow\\" << physPreset->sndParams.soundVolLow
				<< "\\soundVolHigh\\" << physPreset->sndParams.soundVolHigh
				<< "\\soundImpactRangeLow\\" << physPreset->sndParams.soundImpactRangeLow
				<< "\\soundImpactRangeHigh\\" << physPreset->sndParams.soundImpactRangeHigh
				<< "\n";

			std::string data = oss.str();
			Util::FileSystem::WriteFileToDisk(outPath.c_str(), data.c_str(), data.size());
		}

		Util::Hook::Detour Load_PhysPresetPtr_Hook;
		void Load_PhysPresetPtr(bool atStreamStart)
		{
			auto varPhysPresetPtr = *reinterpret_cast<PhysPreset***>(0x82CE6DE0);

			auto Invoke = Load_PhysPresetPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			if (varPhysPresetPtr && *varPhysPresetPtr)
			{
				Dump_PhysPreset(*varPhysPresetPtr);
			}
		}

		void Dump()
		{
			Load_PhysPresetPtr_Hook.Create(0x82306FD8, Load_PhysPresetPtr);
		}

		void Load()
		{
			//Load_MapEntsPtr_Hook.Create(0x823102C8, Load_MapEntsPtr);
		}

		void Unload()
		{
			Load_PhysPresetPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
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

				Symbols::SP::Com_Printf(0, "map ents '%s' has been overriden with '%s'.\n", mapEnts->name, rawFilePath.c_str());
			}
			else
			{
				// TODO: change this to be Com_PrintError
				printf("Failed to allocate memory for entityString replacement!\n");
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
