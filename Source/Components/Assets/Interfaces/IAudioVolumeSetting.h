#pragma once

namespace IAudioVolumeSetting
{
	struct AudioVolumeSetting
	{
		const char* p_name;
		float soundChannelVolumes[64];
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
