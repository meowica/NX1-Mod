#include "IAudioVolumeSetting.h"

namespace IAudioVolumeSetting
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_AudioVolumeSetting(const AudioVolumeSetting* audioVolumeSetting)
		{
			if (!audioVolumeSetting)
				return;

			std::string assetName = audioVolumeSetting->p_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\audio_volume\\" + assetName + ".csv";

			std::ostringstream oss;
			oss << "Channel,Volume\n";

			for (int i = 0; i < 64; ++i)
			{
				oss << i
					<< ","
					<< std::fixed << std::setprecision(6)
					<< audioVolumeSetting->soundChannelVolumes[i]
					<< "\n";
			}

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_AudioVolumeSettingPtr_Hook;
		void Load_AudioVolumeSettingPtr(bool atStreamStart)
		{
			auto varAudioVolumeSettingPtr = *reinterpret_cast<AudioVolumeSetting***>(0x82CE69E4);

			Load_AudioVolumeSettingPtr_Hook.Invoke<void>(atStreamStart);

			if (varAudioVolumeSettingPtr && *varAudioVolumeSettingPtr)
			{
				if (IniConfig::EnableAudioVolumeSettingDumper)
					Dump_AudioVolumeSetting(*varAudioVolumeSettingPtr);
				//if (IniConfig::EnableAudioVolumeSettingLoader)
				//	Load_AudioVolumeSetting(*varAudioVolumeSettingPtr);
			}
		}

		void Load()
		{
			Load_AudioVolumeSettingPtr_Hook.Create(0x82322F80, Load_AudioVolumeSettingPtr);
		}

		void Unload()
		{
			Load_AudioVolumeSettingPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_AudioVolumeSetting(const AudioVolumeSetting* audioVolumeSetting)
		{
			if (!audioVolumeSetting)
				return;

			std::string assetName = audioVolumeSetting->p_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\audio_volume\\" + assetName + ".csv";

			std::ostringstream oss;
			oss << "Channel,Volume\n";

			for (int i = 0; i < 64; ++i)
			{
				oss << i
					<< ","
					<< std::fixed << std::setprecision(6)
					<< audioVolumeSetting->soundChannelVolumes[i]
					<< "\n";
			}

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_AudioVolumeSettingPtr_Hook;
		void Load_AudioVolumeSettingPtr(bool atStreamStart)
		{
			auto varAudioVolumeSettingPtr = *reinterpret_cast<AudioVolumeSetting***>(0x82C6E3E4);

			Load_AudioVolumeSettingPtr_Hook.Invoke<void>(atStreamStart);

			if (varAudioVolumeSettingPtr && *varAudioVolumeSettingPtr)
			{
				if (IniConfig::EnableAudioVolumeSettingDumper)
					Dump_AudioVolumeSetting(*varAudioVolumeSettingPtr);
				//if (IniConfig::EnableAudioVolumeSettingLoader)
				//	Load_AudioVolumeSetting(*varAudioVolumeSettingPtr);
			}
		}

		void Load()
		{
			Load_AudioVolumeSettingPtr_Hook.Create(0x8226CBA8, Load_AudioVolumeSettingPtr);
		}

		void Unload()
		{
			Load_AudioVolumeSettingPtr_Hook.Clear();
		}
	}
#endif
}
