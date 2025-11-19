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

			Symbols::MP::Com_Printf(0, "Dumping '%s' of type '%s'...\n", assetName, "PhysPreset");

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
				if (IniConfig::EnablePhysPresetDumper)
				{
					Dump_PhysPreset(*varPhysPresetPtr);
				}
				
				//if (IniConfig::EnablePhysPresetLoader)
				//{
				//	Load_PhysPreset(*varPhysPresetPtr);
				//}
			}
		}

		void Load()
		{
			Load_PhysPresetPtr_Hook.Create(0x82306FD8, Load_PhysPresetPtr);
		}

		void Unload()
		{
			Load_PhysPresetPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_PhysPreset(const PhysPreset* physPreset)
		{
			if (!physPreset)
				return;

			std::string assetName = physPreset->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			Symbols::SP::Com_Printf(0, "Dumping '%s' of type '%s'...\n", assetName, "PhysPreset");

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
			auto varPhysPresetPtr = *reinterpret_cast<PhysPreset***>(0x82C6E7E0);

			auto Invoke = Load_PhysPresetPtr_Hook.Invoke<void(*)(bool)>();
			Invoke(atStreamStart);

			if (varPhysPresetPtr && *varPhysPresetPtr)
			{
				if (IniConfig::EnablePhysPresetDumper)
				{
					Dump_PhysPreset(*varPhysPresetPtr);
				}
				
				//if (IniConfig::EnablePhysPresetLoader)
				//{
				//	Load_PhysPreset(*varPhysPresetPtr);
				//}
			}
		}

		void Load()
		{
			Load_PhysPresetPtr_Hook.Create(0x82250C00, Load_PhysPresetPtr);
		}

		void Unload()
		{
			Load_PhysPresetPtr_Hook.Clear();
		}
	}
#endif
}
