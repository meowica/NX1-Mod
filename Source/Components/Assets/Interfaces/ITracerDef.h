#pragma once

#include "IMaterial.h"

namespace ITracerDef
{
	struct TracerDef
	{
		const char* name;
		IMaterial::Material* material;
		unsigned int drawInterval;
		float speed;
		float beamLength;
		float beamWidth;
		float screwRadius;
		float screwDist;
		unsigned int m_screwRadius_top_begin_expanding_overtime;
		unsigned int m_screwRadius_bottom_begin_expanding_overtime;
		float m_screwRadius_top_expanding_overtime;
		float m_screwRadius_bottom_expanding_overtime;
		unsigned int m_fadeout_top_begin;
		unsigned int m_fadeout_top_duration;
		unsigned int m_fadeout_bottom_begin;
		unsigned int m_fadeout_bottom_duration;
		float colors[5][4];
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
