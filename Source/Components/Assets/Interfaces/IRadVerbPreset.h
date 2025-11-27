#pragma once

namespace IRadVerbPreset
{
	struct RadVerbPreset
	{
		const char* p_name;
		float earlyTime;
		float lateTime;
		float earlyGain;
		float lateGain;
		float lateGainProx;
		float returnGain;
		float earlyLpf;
		float lateLpf;
		float inputLpf;
		float dampLpf;
		float wallReflect;
		float dryGain;
		float earlySize;
		float lateSize;
		float diffusion;
		float rearLevel;
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
