#include "IRadVerbPreset.h"

namespace IRadVerbPreset
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_RadVerbPreset(const RadVerbPreset* radVerbPreset)
		{
			if (!radVerbPreset)
				return;

			std::string assetName = radVerbPreset->p_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\rad_verb\\" + assetName + ".csv";

			std::ostringstream oss;
			oss << "name," "earlyTime," "lateTime,"
				"earlyGain,"
				"lateGain,"
				"lateGainProx,"
				"returnGain,"
				"earlyLpf,"
				"lateLpf,"
				"inputLpf,"
				"dampLpf,"
				"wallReflect,"
				"dryGain,"
				"earlySize,"
				"lateSize,"
				"diffusion,"
				"rearLevel\n";
			oss <<
				radVerbPreset->p_name << "," <<
				radVerbPreset->earlyTime << "," <<
				radVerbPreset->lateTime << "," <<
				radVerbPreset->earlyGain << "," <<
				radVerbPreset->lateGain << "," <<
				radVerbPreset->lateGainProx << "," <<
				radVerbPreset->returnGain << "," <<
				radVerbPreset->earlyLpf << "," <<
				radVerbPreset->lateLpf << "," <<
				radVerbPreset->inputLpf << "," <<
				radVerbPreset->dampLpf << "," <<
				radVerbPreset->wallReflect << "," <<
				radVerbPreset->dryGain << "," <<
				radVerbPreset->earlySize << "," <<
				radVerbPreset->lateSize << "," <<
				radVerbPreset->diffusion << "," <<
				radVerbPreset->rearLevel << "\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_RadVerbPresetPtr_Hook;
		void Load_RadVerbPresetPtr(bool atStreamStart)
		{
			auto varRadVerbPresetPtr = *reinterpret_cast<RadVerbPreset***>(0x82CE6370);

			Load_RadVerbPresetPtr_Hook.Invoke<void>(atStreamStart);

			if (varRadVerbPresetPtr && *varRadVerbPresetPtr)
			{
				if (IniConfig::EnableRadVerbPresetDumper)
					Dump_RadVerbPreset(*varRadVerbPresetPtr);
				//if (IniConfig::EnableRadVerbPresetLoader)
				//	Load_RadVerbPreset(*varRadVerbPresetPtr);
			}
		}

		void Load()
		{
			Load_RadVerbPresetPtr_Hook.Create(0x823235C0, Load_RadVerbPresetPtr);
		}

		void Unload()
		{
			Load_RadVerbPresetPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_RadVerbPreset(const RadVerbPreset* radVerbPreset)
		{
			if (!radVerbPreset)
				return;

			std::string assetName = radVerbPreset->p_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\rad_verb\\" + assetName + ".csv";

			std::ostringstream oss;
			oss << "name," "earlyTime," "lateTime,"
				"earlyGain,"
				"lateGain,"
				"lateGainProx,"
				"returnGain,"
				"earlyLpf,"
				"lateLpf,"
				"inputLpf,"
				"dampLpf,"
				"wallReflect,"
				"dryGain,"
				"earlySize,"
				"lateSize,"
				"diffusion,"
				"rearLevel\n";
			oss <<
				radVerbPreset->p_name << "," <<
				radVerbPreset->earlyTime << "," <<
				radVerbPreset->lateTime << "," <<
				radVerbPreset->earlyGain << "," <<
				radVerbPreset->lateGain << "," <<
				radVerbPreset->lateGainProx << "," <<
				radVerbPreset->returnGain << "," <<
				radVerbPreset->earlyLpf << "," <<
				radVerbPreset->lateLpf << "," <<
				radVerbPreset->inputLpf << "," <<
				radVerbPreset->dampLpf << "," <<
				radVerbPreset->wallReflect << "," <<
				radVerbPreset->dryGain << "," <<
				radVerbPreset->earlySize << "," <<
				radVerbPreset->lateSize << "," <<
				radVerbPreset->diffusion << "," <<
				radVerbPreset->rearLevel << "\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_RadVerbPresetPtr_Hook;
		void Load_RadVerbPresetPtr(bool atStreamStart)
		{
			auto varRadVerbPresetPtr = *reinterpret_cast<RadVerbPreset***>(0x82C6DD70);

			Load_RadVerbPresetPtr_Hook.Invoke<void>(atStreamStart);

			if (varRadVerbPresetPtr && *varRadVerbPresetPtr)
			{
				if (IniConfig::EnableRadVerbPresetDumper)
					Dump_RadVerbPreset(*varRadVerbPresetPtr);
				//if (IniConfig::EnableRadVerbPresetLoader)
				//	Load_RadVerbPreset(*varRadVerbPresetPtr);
			}
		}

		void Load()
		{
			Load_RadVerbPresetPtr_Hook.Create(0x8226D1E8, Load_RadVerbPresetPtr);
		}

		void Unload()
		{
			Load_RadVerbPresetPtr_Hook.Clear();
		}
	}
#endif
}
