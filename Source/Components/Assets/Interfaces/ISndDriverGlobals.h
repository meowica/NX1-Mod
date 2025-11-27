#pragma once

namespace ISndDriverGlobals
{
	struct XAUDIO2FX_REVERB_I3DL2_PARAMETERS
	{
		float WetDryMix;
		int Room;
		int RoomHF;
		float RoomRolloffFactor;
		float DecayTime;
		float DecayHFRatio;
		int Reflections;
		float ReflectionsDelay;
		int Reverb;
		float ReverbDelay;
		float Diffusion;
		float Density;
		float HFReference;
	};

	struct ReverbPreset
	{
		XAUDIO2FX_REVERB_I3DL2_PARAMETERS reverbSettings;
	};

	struct ReverbPresetList
	{
		int numReverbPresets;
		ReverbPreset* p_reverbPresets;
		const char** pp_reverbPresetNames;
	};

	struct SndPlatformGlobals
	{
		ReverbPresetList reverbPresets;
	};

	struct ADSRSetting
	{
		unsigned int hashName;
		float attackLength;
		float decayLength;
		float releaseLength;
		float sustainLevel;
		float sustainLength;
		unsigned char attackFunction;
		unsigned char decayFunction;
		unsigned char releaseFunction;
	};

	struct ADSRSettingList
	{
		int numSettings;
		ADSRSetting* p_adsrSettings;
	};

	struct WeaponAreaMappingEntry
	{
		short plrAdsrIndex;
		short npcAdsrIndex;
		short npcVerbIndex;
	};

	struct AreaMappingEntry
	{
		char areaName[16];
		char reverbName[16];
		float reverbWet;
		float reverbDry;
		float reverbFadeTime;
	};

	struct WeaponMappingEntry
	{
		char name[16];
	};

	struct ReverbNameEntry
	{
		char name[32];
	};

	struct WeaponAreaMappingList
	{
		int numWeapons;
		int numAreas;
		int numReverbNames;
		WeaponAreaMappingEntry* p_weaponAreaMappings;
		AreaMappingEntry* p_areaMappingNames;
		WeaponMappingEntry* p_weaponMappingNames;
		ReverbNameEntry* p_reverbNames;
	};

	struct SOcclusionTableEntry
	{
		float occlusionValue;
		float freq;
	};

	struct SOcclusionTable
	{
		unsigned int hashName;
		int numEntries;
		SOcclusionTableEntry* p_entries;
	};

	struct OcclusionTableList
	{
		int numOcclusionTables;
		SOcclusionTable* p_occlusionTables;
	};

	enum EntChan3dType
	{
		ENTCHAN_3DTYPE_2D,
		ENTCHAN_3DTYPE_3D,
		ENTCHAN_3DTYPE_3D_NO_OCCLUSION,
	};

	struct snd_entchannel_info_t
	{
		const char* name;
		int priority;
		EntChan3dType type3d;
		bool isRestricted;
		bool isPausable;
		int maxVoices;
		int voiceCount;
		float volume;
		unsigned int flags;
	};

	struct SndEntChannelInfoList
	{
		int numEntChannels;
		snd_entchannel_info_t* p_entChannelList;
	};

	struct SndDriverGlobals
	{
		const char* p_name;
		SndPlatformGlobals platformGlobals;
		ADSRSettingList adsrSettingsList;
		WeaponAreaMappingList weaponAreaMappingList;
		OcclusionTableList occlusionTableList;
		SndEntChannelInfoList entChannelInfoList;
	};

#ifdef IS_MP
	namespace MP
	{
		void Load();
		void Unload();
	}
#elif IS_SP
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
