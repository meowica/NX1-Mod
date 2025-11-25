#pragma once

#include "IMaterial.h"

namespace ILaserDef
{
	enum ELaserUVLayout
	{
		LASER_UV_DEFAULT,
		LASER_UV_BILLBOARD,
		LASER_UV_COUNT,
	};

	enum ELaserShape
	{
		LASER_SHAPE_DEFAULT,
		LASER_SHAPE_BILLBOARD,
		LASER_SHAPE_COUNT,
	};

	struct LaserDef
	{
		const char* mp_name;
		IMaterial::Material* m_material;
		float m_src_width;
		float m_segment;
		float m_texture_animation;
		float m_src_red;
		float m_src_green;
		float m_src_blue;
		float m_src_alpha;
		float m_dst_red;
		float m_dst_green;
		float m_dst_blue;
		float m_dst_alpha;
		ELaserUVLayout m_uv;
		ELaserShape m_shape;
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
