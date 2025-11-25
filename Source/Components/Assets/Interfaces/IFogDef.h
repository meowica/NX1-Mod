#pragma once

namespace IFogDef
{
	struct FogDef
	{
		const char* mp_name;
		float m_start_dist;
		float m_halfway_dist;
		float m_red;
		float m_green;
		float m_blue;
		float m_max_opacity;
		float m_transition_time;
		float m_multiplied_blend;
		float m_multiplied_near_red;
		float m_multiplied_near_green;
		float m_multiplied_near_blue;
		float m_multiplied_far_red;
		float m_multiplied_far_green;
		float m_multiplied_far_blue;
		float m_sun_red;
		float m_sun_green;
		float m_sun_blue;
		float m_sun_dir[3];
		float m_sun_begin_fade_angle;
		float m_sun_end_fade_angle;
		float m_sun_fog_scale;
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
