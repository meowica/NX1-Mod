#include "IShellShockParams.h"

namespace IShellShockParams
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_ShellShockParams(const ShellShockParams* shellShockParams)
		{
			if (!shellShockParams)
				return;

			std::string assetName = shellShockParams->p_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\shock\\" + assetName + ".json";

			static const char* kTypeNames[] =
			{
				"blurred",
				"flashed",
				"none"
			};

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << Util::JSON::JsonEscape(shellShockParams->p_name) << "\",\n";
			oss << "  \"screenBlend\": {\n";
			oss << "    \"blurredFadeTime\": " << shellShockParams->screenBlendBlurredFadeTime << ",\n";
			oss << "    \"blurredEffectTime\": " << shellShockParams->screenBlendBlurredEffectTime << ",\n";
			oss << "    \"flashWhiteFadeTime\": " << shellShockParams->screenBlendFlashWhiteFadeTime << ",\n";
			oss << "    \"flashShotFadeTime\": " << shellShockParams->screenBlendFlashShotFadeTime << ",\n";
			oss << "    \"type\": \"" << kTypeNames[shellShockParams->screenBlendType] << "\"\n";
			oss << "  },\n";
			oss << "  \"view\": {\n";
			oss << "    \"fadeTime\": " << shellShockParams->viewFadeTime << ",\n";
			oss << "    \"kickRate\": " << shellShockParams->viewKickRate << ",\n";
			oss << "    \"kickRadius\": " << shellShockParams->viewKickRadius << "\n";
			oss << "  },\n";
			oss << "  \"lookControl\": {\n";
			oss << "    \"affect\": " << ((shellShockParams->lookControlAffect) ? "true" : "false") << ",\n";
			oss << "    \"fadeTime\": " << shellShockParams->lookControlFadeTime << ",\n";
			oss << "    \"mouseSensitivity\": " << shellShockParams->lookControlMouseSensitivity << ",\n";
			oss << "    \"maxPitchSpeed\": " << shellShockParams->lookControlMaxPitchSpeed << ",\n";
			oss << "    \"maxYawSpeed\": " << shellShockParams->lookControlMaxYawSpeed << "\n";
			oss << "  },\n";
			oss << "  \"movement\": {\n";
			oss << "    \"affect\": " << ((shellShockParams->movementAffect) ? "true" : "false") << "\n";
			oss << "  },\n";
			oss << "  \"audio\": {\n";
			oss << "    \"volumeSettingName\": \"" << Util::JSON::JsonEscape(shellShockParams->volumeSettingName) << "\",\n";
			oss << "    \"affect\": " << ((shellShockParams->soundAffect) ? "true" : "false") << ",\n";
			oss << "    \"soundLoop\": \"" << Util::JSON::JsonEscape(shellShockParams->soundLoop) << "\",\n";
			oss << "    \"soundEnd\": \"" << Util::JSON::JsonEscape(shellShockParams->soundEnd) << "\",\n";
			oss << "    \"soundEndAbort\": \"" << Util::JSON::JsonEscape(shellShockParams->soundEndAbort) << "\",\n";
			oss << "    \"fadeInTime\": " << shellShockParams->soundFadeInTime << ",\n";
			oss << "    \"fadeOutTime\": " << shellShockParams->soundFadeOutTime << ",\n";
			oss << "    \"dry\": " << shellShockParams->soundDrylevel << ",\n";
			oss << "    \"wet\": " << shellShockParams->soundWetlevel << ",\n";
			oss << "    \"roomType\": \"" << Util::JSON::JsonEscape(shellShockParams->soundRoomtype) << "\",\n";
			oss << "    \"modEndDelay\": " << shellShockParams->soundModEndDelay << ",\n";
			oss << "    \"loopFadeTime\": " << shellShockParams->soundLoopFadeTime << ",\n";
			oss << "    \"loopEndDelay\": " << shellShockParams->soundLoopEndDelay << "\n";
			oss << "  }\n";
			oss << "}\n";

			std::string json = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), json.c_str(), json.size());
		}

		Util::Hook::Detour Load_ShellShockParamsPtr_Hook;
		void Load_ShellShockParamsPtr(bool atStreamStart)
		{
			auto varShellShockParamsPtr = *reinterpret_cast<ShellShockParams***>(0x82CE6B80);

			Load_ShellShockParamsPtr_Hook.Invoke<void>(atStreamStart);

			if (varShellShockParamsPtr && *varShellShockParamsPtr)
			{
				if (IniConfig::EnableShellShockParamDumper)
					Dump_ShellShockParams(*varShellShockParamsPtr);
				//if (IniConfig::EnableShellShockParamLoader)
				//	Load_ShellShockParam(*varShellShockParamPtr);
			}
		}

		void Load()
		{
			Load_ShellShockParamsPtr_Hook.Create(0x82322998, Load_ShellShockParamsPtr);
		}

		void Unload()
		{
			Load_ShellShockParamsPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_ShellShockParams(const ShellShockParams* shellShockParams)
		{
			if (!shellShockParams)
				return;

			std::string assetName = shellShockParams->p_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\shock\\" + assetName + ".json";

			static const char* kTypeNames[] =
			{
				"blurred",
				"flashed",
				"none"
			};

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << Util::JSON::JsonEscape(shellShockParams->p_name) << "\",\n";
			oss << "  \"screenBlend\": {\n";
			oss << "    \"blurredFadeTime\": " << shellShockParams->screenBlendBlurredFadeTime << ",\n";
			oss << "    \"blurredEffectTime\": " << shellShockParams->screenBlendBlurredEffectTime << ",\n";
			oss << "    \"flashWhiteFadeTime\": " << shellShockParams->screenBlendFlashWhiteFadeTime << ",\n";
			oss << "    \"flashShotFadeTime\": " << shellShockParams->screenBlendFlashShotFadeTime << ",\n";
			oss << "    \"type\": \"" << kTypeNames[shellShockParams->screenBlendType] << "\"\n";
			oss << "  },\n";
			oss << "  \"view\": {\n";
			oss << "    \"fadeTime\": " << shellShockParams->viewFadeTime << ",\n";
			oss << "    \"kickRate\": " << shellShockParams->viewKickRate << ",\n";
			oss << "    \"kickRadius\": " << shellShockParams->viewKickRadius << "\n";
			oss << "  },\n";
			oss << "  \"lookControl\": {\n";
			oss << "    \"affect\": " << ((shellShockParams->lookControlAffect) ? "true" : "false") << ",\n";
			oss << "    \"fadeTime\": " << shellShockParams->lookControlFadeTime << ",\n";
			oss << "    \"mouseSensitivity\": " << shellShockParams->lookControlMouseSensitivity << ",\n";
			oss << "    \"maxPitchSpeed\": " << shellShockParams->lookControlMaxPitchSpeed << ",\n";
			oss << "    \"maxYawSpeed\": " << shellShockParams->lookControlMaxYawSpeed << "\n";
			oss << "  },\n";
			oss << "  \"movement\": {\n";
			oss << "    \"affect\": " << ((shellShockParams->movementAffect) ? "true" : "false") << "\n";
			oss << "  },\n";
			oss << "  \"audio\": {\n";
			oss << "    \"volumeSettingName\": \"" << Util::JSON::JsonEscape(shellShockParams->volumeSettingName) << "\",\n";
			oss << "    \"affect\": " << ((shellShockParams->soundAffect) ? "true" : "false") << ",\n";
			oss << "    \"soundLoop\": \"" << Util::JSON::JsonEscape(shellShockParams->soundLoop) << "\",\n";
			oss << "    \"soundEnd\": \"" << Util::JSON::JsonEscape(shellShockParams->soundEnd) << "\",\n";
			oss << "    \"soundEndAbort\": \"" << Util::JSON::JsonEscape(shellShockParams->soundEndAbort) << "\",\n";
			oss << "    \"fadeInTime\": " << shellShockParams->soundFadeInTime << ",\n";
			oss << "    \"fadeOutTime\": " << shellShockParams->soundFadeOutTime << ",\n";
			oss << "    \"dry\": " << shellShockParams->soundDrylevel << ",\n";
			oss << "    \"wet\": " << shellShockParams->soundWetlevel << ",\n";
			oss << "    \"roomType\": \"" << Util::JSON::JsonEscape(shellShockParams->soundRoomtype) << "\",\n";
			oss << "    \"modEndDelay\": " << shellShockParams->soundModEndDelay << ",\n";
			oss << "    \"loopFadeTime\": " << shellShockParams->soundLoopFadeTime << ",\n";
			oss << "    \"loopEndDelay\": " << shellShockParams->soundLoopEndDelay << "\n";
			oss << "  }\n";
			oss << "}\n";

			std::string json = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), json.c_str(), json.size());
		}

		Util::Hook::Detour Load_ShellShockParamsPtr_Hook;
		void Load_ShellShockParamsPtr(bool atStreamStart)
		{
			auto varShellShockParamsPtr = *reinterpret_cast<ShellShockParams***>(0x82C6E580);

			Load_ShellShockParamsPtr_Hook.Invoke<void>(atStreamStart);

			if (varShellShockParamsPtr && *varShellShockParamsPtr)
			{
				if (IniConfig::EnableShellShockParamDumper)
					Dump_ShellShockParams(*varShellShockParamsPtr);
				//if (IniConfig::EnableShellShockParamLoader)
				//	Load_ShellShockParam(*varShellShockParamPtr);
			}
		}

		void Load()
		{
			Load_ShellShockParamsPtr_Hook.Create(0x8226C5C0, Load_ShellShockParamsPtr);
		}

		void Unload()
		{
			Load_ShellShockParamsPtr_Hook.Clear();
		}
	}
#endif
}
