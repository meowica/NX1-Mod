#pragma once

#include "ILoadedSound.h"

namespace ISndAliasList
{
	struct SndCurve
	{
		unsigned short knotCount;
		float knots[16][2];
	};

	struct StreamedSound
	{
		ILoadedSound::StreamFileName filename;
		unsigned int totalMsec;
		unsigned char compressed;
	};

	union SoundFileRef
	{
		ILoadedSound::LoadedSound* loadSnd;
		StreamedSound streamSnd;
	};

	struct SoundFile
	{
		unsigned char type;
		unsigned char exists;
		SoundFileRef ref;
	};

	struct SpeakerLevels
	{
		unsigned int speaker;
		int numLevels;
		float levels[2];
	};

	struct ChannelMap
	{
		int speakerCount;
		SpeakerLevels speakers[6];
	};

	struct SpeakerMap
	{
		bool isDefault;
		const char* p_name;
		ChannelMap channelMaps[2][2];
	};

	struct SndDuckMap
	{
		const char* p_name;
		float duckAmount;
		int attack;
		int sustain;
		int release;
		unsigned long long entChannelMask;
	};

	struct SndAlias
	{
		const char* p_aliasName;
		const char* p_subtitle;
		const char* p_secondaryAliasName;
		const char* p_chainAliasName;
		const char* p_mixerGroup;
		SoundFile* p_soundFile;
		int sequence;
		float volMin;
		float volMax;
		float pitchMin;
		float pitchMax;
		float distMin;
		float distMax;
		float velocityMin;
		int flags;
		float masterSlavePercentage;
		float probability;
		float lfeVol;
		float centerPercentage;
		int startDelay;
		/*SndVfCurve* p_volumeFalloffCurve;*/
		/*SndLpfCurve* p_lpfCurve;*/
		float envelopMin;
		float envelopMax;
		float envelopPercentage;
		SpeakerMap* p_speakerMap;
		short adsrSettingIndex;
		char instanceLimit;
		float reverbSend;
		SndDuckMap* p_duckMap;
	};

	struct SndAliasList
	{
		const char* p_aliasName;
		SndAlias* p_head;
		int count;
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
