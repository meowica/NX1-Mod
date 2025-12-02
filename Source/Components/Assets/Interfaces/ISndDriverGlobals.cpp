#include "ISndDriverGlobals.h"

namespace ISndDriverGlobals
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_SndDriverGlobals(const SndDriverGlobals* sndDriverGlobals)
		{
			if (!sndDriverGlobals)
				return;

			std::string assetName = sndDriverGlobals->p_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\soundaliases\\" + assetName + ".json";

			std::ostringstream oss;
			oss << std::fixed << std::setprecision(4);
			oss << "{\n";
			const ReverbPresetList& reverbList = sndDriverGlobals->platformGlobals.reverbPresets;
			oss << "  \"ReverbPresets\": [\n";
			for (int i = 0; i < reverbList.numReverbPresets; ++i)
			{
				const ReverbPreset& preset = reverbList.p_reverbPresets[i];
				oss << "    {\n";
				oss << "      \"Name\": \"" << reverbList.pp_reverbPresetNames[i] << "\",\n";
				const XAUDIO2FX_REVERB_I3DL2_PARAMETERS& r = preset.reverbSettings;
				oss << "      \"WetDryMix\": " << r.WetDryMix << ",\n";
				oss << "      \"Room\": " << r.Room << ",\n";
				oss << "      \"RoomHF\": " << r.RoomHF << ",\n";
				oss << "      \"RoomRolloffFactor\": " << r.RoomRolloffFactor << ",\n";
				oss << "      \"DecayTime\": " << r.DecayTime << ",\n";
				oss << "      \"DecayHFRatio\": " << r.DecayHFRatio << ",\n";
				oss << "      \"Reflections\": " << r.Reflections << ",\n";
				oss << "      \"ReflectionsDelay\": " << r.ReflectionsDelay << ",\n";
				oss << "      \"Reverb\": " << r.Reverb << ",\n";
				oss << "      \"ReverbDelay\": " << r.ReverbDelay << ",\n";
				oss << "      \"Diffusion\": " << r.Diffusion << ",\n";
				oss << "      \"Density\": " << r.Density << ",\n";
				oss << "      \"HFReference\": " << r.HFReference << "\n";
				oss << "    }" << (i + 1 < (reverbList.numReverbPresets) ? "," : "") << "\n";
			}
			oss << "  ],\n";
			const ADSRSettingList& adsrList = sndDriverGlobals->adsrSettingsList;
			oss << "  \"ADSRSettings\": [\n";
			for (int i = 0; i < adsrList.numSettings; ++i)
			{
				const ADSRSetting& s = adsrList.p_adsrSettings[i];
				oss << "    {\n";
				oss << "      \"HashName\": " << s.hashName << ",\n";
				oss << "      \"AttackLength\": " << s.attackLength << ",\n";
				oss << "      \"DecayLength\": " << s.decayLength << ",\n";
				oss << "      \"ReleaseLength\": " << s.releaseLength << ",\n";
				oss << "      \"SustainLevel\": " << s.sustainLevel << ",\n";
				oss << "      \"SustainLength\": " << s.sustainLength << ",\n";
				oss << "      \"AttackFunction\": " << (int)s.attackFunction << ",\n";
				oss << "      \"DecayFunction\": " << (int)s.decayFunction << ",\n";
				oss << "      \"ReleaseFunction\": " << (int)s.releaseFunction << "\n";
				oss << "    }" << (i + 1 < adsrList.numSettings ? "," : "") << "\n";
			}
			oss << "  ],\n";
			const WeaponAreaMappingList& wam = sndDriverGlobals->weaponAreaMappingList;
			oss << "  \"WeaponAreaMappings\": [\n";
			for (int i = 0; i < wam.numWeapons; ++i)
			{
				const WeaponAreaMappingEntry& entry = wam.p_weaponAreaMappings[i];
				oss << "    {\n";
				oss << "      \"PlayerADSRIndex\": " << entry.plrAdsrIndex << ",\n";
				oss << "      \"NPCADSRIndex\": " << entry.npcAdsrIndex << ",\n";
				oss << "      \"NPCVerbIndex\": " << entry.npcVerbIndex << "\n";
				oss << "    }" << (i + 1 < wam.numWeapons ? "," : "") << "\n";
			}
			oss << "  ],\n";
			oss << "  \"AreaMappings\": [\n";
			for (int i = 0; i < wam.numAreas; ++i)
			{
				const AreaMappingEntry& area = wam.p_areaMappingNames[i];
				oss << "    {\n";
				oss << "      \"AreaName\": \"" << area.areaName << "\",\n";
				oss << "      \"ReverbName\": \"" << area.reverbName << "\",\n";
				oss << "      \"ReverbWet\": " << area.reverbWet << ",\n";
				oss << "      \"ReverbDry\": " << area.reverbDry << ",\n";
				oss << "      \"ReverbFadeTime\": " << area.reverbFadeTime << "\n";
				oss << "    }" << (i + 1 < wam.numAreas ? "," : "") << "\n";
			}
			oss << "  ],\n";
			oss << "  \"ReverbNames\": [\n";
			for (int i = 0; i < wam.numReverbNames; ++i)
			{
				oss << "    \"" << wam.p_reverbNames[i].name << "\"";
				if (i + 1 < wam.numReverbNames) oss << ",";
				oss << "\n";
			}
			oss << "  ],\n";
			const OcclusionTableList& otl = sndDriverGlobals->occlusionTableList;
			oss << "  \"OcclusionTables\": [\n";
			for (int i = 0; i < otl.numOcclusionTables; ++i)
			{
				const SOcclusionTable& table = otl.p_occlusionTables[i];
				oss << "    {\n";
				oss << "      \"HashName\": " << table.hashName << ",\n";
				oss << "      \"Entries\": [\n";
				for (int j = 0; j < table.numEntries; ++j)
				{
					const SOcclusionTableEntry& e = table.p_entries[j];
					oss << "        {\"Value\": " << e.occlusionValue << ", \"Freq\": " << e.freq << "}";
					if (j + 1 < table.numEntries) oss << ",";
					oss << "\n";
				}
				oss << "      ]\n";
				oss << "    }" << (i + 1 < otl.numOcclusionTables ? "," : "") << "\n";
			}
			oss << "  ],\n";
			const SndEntChannelInfoList& ecl = sndDriverGlobals->entChannelInfoList;
			oss << "  \"EntChannelInfoList\": [\n";
			for (int i = 0; i < ecl.numEntChannels; ++i)
			{
				const snd_entchannel_info_t& c = ecl.p_entChannelList[i];
				oss << "    {\n";
				oss << "      \"Name\": \"" << c.name << "\",\n";
				oss << "      \"Priority\": " << c.priority << ",\n";
				oss << "      \"Type3D\": " << c.type3d << ",\n";
				oss << "      \"IsRestricted\": " << (c.isRestricted ? "true" : "false") << ",\n";
				oss << "      \"IsPausable\": " << (c.isPausable ? "true" : "false") << ",\n";
				oss << "      \"MaxVoices\": " << c.maxVoices << ",\n";
				oss << "      \"VoiceCount\": " << c.voiceCount << ",\n";
				oss << "      \"Volume\": " << c.volume << ",\n";
				oss << "      \"Flags\": " << c.flags << "\n";
				oss << "    }" << (i + 1 < ecl.numEntChannels ? "," : "") << "\n";
			}
			oss << "  ]\n";
			oss << "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), oss.str().c_str(), (int)oss.str().length());
		}

		Util::Hook::Detour Load_SndDriverGlobalsPtr_Hook;
		void Load_SndDriverGlobalsPtr(bool atStreamStart)
		{
			auto varSndDriverGlobalsPtr = *reinterpret_cast<SndDriverGlobals***>(0x82CE6AE8);

			Load_SndDriverGlobalsPtr_Hook.Invoke<void>(atStreamStart);

			if (varSndDriverGlobalsPtr && *varSndDriverGlobalsPtr)
			{
				if (IniConfig::EnableSndDriverGlobalsDumper)
					Dump_SndDriverGlobals(*varSndDriverGlobalsPtr);
				//if (IniConfig::EnableSndDriverGlobalsLoader)
				//	Load_SndDriverGlobals(*varSndDriverGlobalsPtr);
			}
		}

		void Load()
		{
			Load_SndDriverGlobalsPtr_Hook.Create(0x822FAC30, Load_SndDriverGlobalsPtr);
		}

		void Unload()
		{
			Load_SndDriverGlobalsPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_SndDriverGlobals(const SndDriverGlobals* sndDriverGlobals)
		{
			if (!sndDriverGlobals)
				return;

			std::string assetName = sndDriverGlobals->p_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\soundaliases\\" + assetName + ".json";

			std::ostringstream oss;
			oss << std::fixed << std::setprecision(4);
			oss << "{\n";
			const ReverbPresetList& reverbList = sndDriverGlobals->platformGlobals.reverbPresets;
			oss << "  \"ReverbPresets\": [\n";
			for (int i = 0; i < reverbList.numReverbPresets; ++i)
			{
				const ReverbPreset& preset = reverbList.p_reverbPresets[i];
				oss << "    {\n";
				oss << "      \"Name\": \"" << reverbList.pp_reverbPresetNames[i] << "\",\n";
				const XAUDIO2FX_REVERB_I3DL2_PARAMETERS& r = preset.reverbSettings;
				oss << "      \"WetDryMix\": " << r.WetDryMix << ",\n";
				oss << "      \"Room\": " << r.Room << ",\n";
				oss << "      \"RoomHF\": " << r.RoomHF << ",\n";
				oss << "      \"RoomRolloffFactor\": " << r.RoomRolloffFactor << ",\n";
				oss << "      \"DecayTime\": " << r.DecayTime << ",\n";
				oss << "      \"DecayHFRatio\": " << r.DecayHFRatio << ",\n";
				oss << "      \"Reflections\": " << r.Reflections << ",\n";
				oss << "      \"ReflectionsDelay\": " << r.ReflectionsDelay << ",\n";
				oss << "      \"Reverb\": " << r.Reverb << ",\n";
				oss << "      \"ReverbDelay\": " << r.ReverbDelay << ",\n";
				oss << "      \"Diffusion\": " << r.Diffusion << ",\n";
				oss << "      \"Density\": " << r.Density << ",\n";
				oss << "      \"HFReference\": " << r.HFReference << "\n";
				oss << "    }" << (i + 1 < (reverbList.numReverbPresets) ? "," : "") << "\n";
			}
			oss << "  ],\n";
			const ADSRSettingList& adsrList = sndDriverGlobals->adsrSettingsList;
			oss << "  \"ADSRSettings\": [\n";
			for (int i = 0; i < adsrList.numSettings; ++i)
			{
				const ADSRSetting& s = adsrList.p_adsrSettings[i];
				oss << "    {\n";
				oss << "      \"HashName\": " << s.hashName << ",\n";
				oss << "      \"AttackLength\": " << s.attackLength << ",\n";
				oss << "      \"DecayLength\": " << s.decayLength << ",\n";
				oss << "      \"ReleaseLength\": " << s.releaseLength << ",\n";
				oss << "      \"SustainLevel\": " << s.sustainLevel << ",\n";
				oss << "      \"SustainLength\": " << s.sustainLength << ",\n";
				oss << "      \"AttackFunction\": " << (int)s.attackFunction << ",\n";
				oss << "      \"DecayFunction\": " << (int)s.decayFunction << ",\n";
				oss << "      \"ReleaseFunction\": " << (int)s.releaseFunction << "\n";
				oss << "    }" << (i + 1 < adsrList.numSettings ? "," : "") << "\n";
			}
			oss << "  ],\n";
			const WeaponAreaMappingList& wam = sndDriverGlobals->weaponAreaMappingList;
			oss << "  \"WeaponAreaMappings\": [\n";
			for (int i = 0; i < wam.numWeapons; ++i)
			{
				const WeaponAreaMappingEntry& entry = wam.p_weaponAreaMappings[i];
				oss << "    {\n";
				oss << "      \"PlayerADSRIndex\": " << entry.plrAdsrIndex << ",\n";
				oss << "      \"NPCADSRIndex\": " << entry.npcAdsrIndex << ",\n";
				oss << "      \"NPCVerbIndex\": " << entry.npcVerbIndex << "\n";
				oss << "    }" << (i + 1 < wam.numWeapons ? "," : "") << "\n";
			}
			oss << "  ],\n";
			oss << "  \"AreaMappings\": [\n";
			for (int i = 0; i < wam.numAreas; ++i)
			{
				const AreaMappingEntry& area = wam.p_areaMappingNames[i];
				oss << "    {\n";
				oss << "      \"AreaName\": \"" << area.areaName << "\",\n";
				oss << "      \"ReverbName\": \"" << area.reverbName << "\",\n";
				oss << "      \"ReverbWet\": " << area.reverbWet << ",\n";
				oss << "      \"ReverbDry\": " << area.reverbDry << ",\n";
				oss << "      \"ReverbFadeTime\": " << area.reverbFadeTime << "\n";
				oss << "    }" << (i + 1 < wam.numAreas ? "," : "") << "\n";
			}
			oss << "  ],\n";
			oss << "  \"ReverbNames\": [\n";
			for (int i = 0; i < wam.numReverbNames; ++i)
			{
				oss << "    \"" << wam.p_reverbNames[i].name << "\"";
				if (i + 1 < wam.numReverbNames) oss << ",";
				oss << "\n";
			}
			oss << "  ],\n";
			const OcclusionTableList& otl = sndDriverGlobals->occlusionTableList;
			oss << "  \"OcclusionTables\": [\n";
			for (int i = 0; i < otl.numOcclusionTables; ++i)
			{
				const SOcclusionTable& table = otl.p_occlusionTables[i];
				oss << "    {\n";
				oss << "      \"HashName\": " << table.hashName << ",\n";
				oss << "      \"Entries\": [\n";
				for (int j = 0; j < table.numEntries; ++j)
				{
					const SOcclusionTableEntry& e = table.p_entries[j];
					oss << "        {\"Value\": " << e.occlusionValue << ", \"Freq\": " << e.freq << "}";
					if (j + 1 < table.numEntries) oss << ",";
					oss << "\n";
				}
				oss << "      ]\n";
				oss << "    }" << (i + 1 < otl.numOcclusionTables ? "," : "") << "\n";
			}
			oss << "  ],\n";
			const SndEntChannelInfoList& ecl = sndDriverGlobals->entChannelInfoList;
			oss << "  \"EntChannelInfoList\": [\n";
			for (int i = 0; i < ecl.numEntChannels; ++i)
			{
				const snd_entchannel_info_t& c = ecl.p_entChannelList[i];
				oss << "    {\n";
				oss << "      \"Name\": \"" << c.name << "\",\n";
				oss << "      \"Priority\": " << c.priority << ",\n";
				oss << "      \"Type3D\": " << c.type3d << ",\n";
				oss << "      \"IsRestricted\": " << (c.isRestricted ? "true" : "false") << ",\n";
				oss << "      \"IsPausable\": " << (c.isPausable ? "true" : "false") << ",\n";
				oss << "      \"MaxVoices\": " << c.maxVoices << ",\n";
				oss << "      \"VoiceCount\": " << c.voiceCount << ",\n";
				oss << "      \"Volume\": " << c.volume << ",\n";
				oss << "      \"Flags\": " << c.flags << "\n";
				oss << "    }" << (i + 1 < ecl.numEntChannels ? "," : "") << "\n";
			}
			oss << "  ]\n";
			oss << "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), oss.str().c_str(), (int)oss.str().length());
		}

		Util::Hook::Detour Load_SndDriverGlobalsPtr_Hook;
		void Load_SndDriverGlobalsPtr(bool atStreamStart)
		{
			auto varSndDriverGlobalsPtr = *reinterpret_cast<SndDriverGlobals***>(0x82C6E4E8);

			Load_SndDriverGlobalsPtr_Hook.Invoke<void>(atStreamStart);

			if (varSndDriverGlobalsPtr && *varSndDriverGlobalsPtr)
			{
				if (IniConfig::EnableSndDriverGlobalsDumper)
					Dump_SndDriverGlobals(*varSndDriverGlobalsPtr);
				//if (IniConfig::EnableSndDriverGlobalsLoader)
				//	Load_SndDriverGlobals(*varSndDriverGlobalsPtr);
			}
		}

		void Load()
		{
			Load_SndDriverGlobalsPtr_Hook.Create(0x82244858, Load_SndDriverGlobalsPtr);
		}

		void Unload()
		{
			Load_SndDriverGlobalsPtr_Hook.Clear();
		}
	}
#endif
}
