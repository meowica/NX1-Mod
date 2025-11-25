#pragma once

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
