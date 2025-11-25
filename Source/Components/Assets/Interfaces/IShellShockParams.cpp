#include "IShellShockParams.h"

namespace IShellShockParams
{
	enum ShockViewTypes
	{
		SHELLSHOCK_VIEWTYPE_BLURRED,
		SHELLSHOCK_VIEWTYPE_FLASHED,
		SHELLSHOCK_VIEWTYPE_NONE,
	};

	struct ShellShockParams
	{
		const char* p_name;
		int screenBlendBlurredFadeTime;
		int screenBlendBlurredEffectTime;
		int screenBlendFlashWhiteFadeTime;
		int screenBlendFlashShotFadeTime;
		ShockViewTypes screenBlendType;
		int viewFadeTime;
		float viewKickRate;
		float viewKickRadius;
		bool lookControlAffect;
		int lookControlFadeTime;
		float lookControlMouseSensitivity;
		float lookControlMaxPitchSpeed;
		float lookControlMaxYawSpeed;
		bool movementAffect;
		const char* volumeSettingName;
		bool soundAffect;
		const char* soundLoop;
		const char* soundEnd;
		const char* soundEndAbort;
		int soundFadeInTime;
		int soundFadeOutTime;
		float soundDrylevel;
		float soundWetlevel;
		char* soundRoomtype;
		int soundModEndDelay;
		int soundLoopFadeTime;
		int soundLoopEndDelay;
	};

	static std::string JsonEscape(const char* string)
	{
		if (!string)
			return "";

		std::string input = string;
		std::string out;
		out.reserve(input.size() + 8);

		for (size_t i = 0; i < input.size(); i++)
		{
			char c = input[i];
			switch (c)
			{
			case '\\':
				out += "\\\\";
				break;
			case '"':
				out += "\\\"";
				break;
			case '\n':
				out += "\\n";
				break;
			case '\r':
				out += "\\r";
				break;
			case '\t':
				out += "\\t";
				break;
			default:
				if ((unsigned char)c < 0x20)
				{
					char buf[8];
					sprintf(buf, "\\u%04x", c);
					out += buf;
				}
				else
				{
					out += c;
				}
			}
		}
		return out;
	}

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
			oss << "  \"name\": \"" << JsonEscape(shellShockParams->p_name) << "\",\n";
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
			oss << "    \"volumeSettingName\": \"" << JsonEscape(shellShockParams->volumeSettingName) << "\",\n";
			oss << "    \"affect\": " << ((shellShockParams->soundAffect) ? "true" : "false") << ",\n";
			oss << "    \"soundLoop\": \"" << JsonEscape(shellShockParams->soundLoop) << "\",\n";
			oss << "    \"soundEnd\": \"" << JsonEscape(shellShockParams->soundEnd) << "\",\n";
			oss << "    \"soundEndAbort\": \"" << JsonEscape(shellShockParams->soundEndAbort) << "\",\n";
			oss << "    \"fadeInTime\": " << shellShockParams->soundFadeInTime << ",\n";
			oss << "    \"fadeOutTime\": " << shellShockParams->soundFadeOutTime << ",\n";
			oss << "    \"dry\": " << shellShockParams->soundDrylevel << ",\n";
			oss << "    \"wet\": " << shellShockParams->soundWetlevel << ",\n";
			oss << "    \"roomType\": \"" << JsonEscape(shellShockParams->soundRoomtype) << "\",\n";
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
			oss << "  \"name\": \"" << JsonEscape(shellShockParams->p_name) << "\",\n";
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
			oss << "    \"volumeSettingName\": \"" << JsonEscape(shellShockParams->volumeSettingName) << "\",\n";
			oss << "    \"affect\": " << ((shellShockParams->soundAffect) ? "true" : "false") << ",\n";
			oss << "    \"soundLoop\": \"" << JsonEscape(shellShockParams->soundLoop) << "\",\n";
			oss << "    \"soundEnd\": \"" << JsonEscape(shellShockParams->soundEnd) << "\",\n";
			oss << "    \"soundEndAbort\": \"" << JsonEscape(shellShockParams->soundEndAbort) << "\",\n";
			oss << "    \"fadeInTime\": " << shellShockParams->soundFadeInTime << ",\n";
			oss << "    \"fadeOutTime\": " << shellShockParams->soundFadeOutTime << ",\n";
			oss << "    \"dry\": " << shellShockParams->soundDrylevel << ",\n";
			oss << "    \"wet\": " << shellShockParams->soundWetlevel << ",\n";
			oss << "    \"roomType\": \"" << JsonEscape(shellShockParams->soundRoomtype) << "\",\n";
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
