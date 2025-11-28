#include "ILaserDef.h"

namespace ILaserDef
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_LaserDef(const LaserDef* laserDef)
		{
			if (!laserDef)
				return;

			std::string assetName = laserDef->mp_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\laser\\" + assetName;

			std::ostringstream oss;
			oss << "LASER"
				<< "\\material\\" << laserDef->m_material->info.name
				<< "\\src_width\\" << laserDef->m_src_width
				<< "\\segment\\" << laserDef->m_segment
				<< "\\texture_animation\\" << laserDef->m_texture_animation
				<< "\\src_color_r\\" << laserDef->m_src_red
				<< "\\src_color_g\\" << laserDef->m_src_green
				<< "\\src_color_b\\" << laserDef->m_src_blue
				<< "\\src_color_a\\" << laserDef->m_src_alpha
				<< "\\dst_color_r\\" << laserDef->m_dst_red
				<< "\\dst_color_g\\" << laserDef->m_dst_green
				<< "\\dst_color_b\\" << laserDef->m_dst_blue
				<< "\\dst_color_a\\" << laserDef->m_dst_alpha
				<< "\\uv_layout\\" << laserDef->m_uv
				<< "\\shape\\" << laserDef->m_shape
				<< "\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_LaserDefPtr_Hook;
		void Load_LaserDefPtr(bool atStreamStart)
		{
			auto varLaserDefPtr = *reinterpret_cast<LaserDef***>(0x82CE6448);

			Load_LaserDefPtr_Hook.Invoke<void>(atStreamStart);

			if (varLaserDefPtr && *varLaserDefPtr)
			{
				if (IniConfig::EnableLaserDefDumper)
					Dump_LaserDef(*varLaserDefPtr);
				//if (IniConfig::EnableLaserDefLoader)
				//	Load_LaserDef(*varLaserDefPtr);
			}
		}

		void Load()
		{
			Load_LaserDefPtr_Hook.Create(0x823170A0, Load_LaserDefPtr);
		}

		void Unload()
		{
			Load_LaserDefPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_LaserDef(const LaserDef* laserDef)
		{
			if (!laserDef)
				return;

			std::string assetName = laserDef->mp_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\laser\\" + assetName;

			std::ostringstream oss;
			oss << "LASER"
				<< "\\material\\" << laserDef->m_material->info.name
				<< "\\src_width\\" << laserDef->m_src_width
				<< "\\segment\\" << laserDef->m_segment
				<< "\\texture_animation\\" << laserDef->m_texture_animation
				<< "\\src_color_r\\" << laserDef->m_src_red
				<< "\\src_color_g\\" << laserDef->m_src_green
				<< "\\src_color_b\\" << laserDef->m_src_blue
				<< "\\src_color_a\\" << laserDef->m_src_alpha
				<< "\\dst_color_r\\" << laserDef->m_dst_red
				<< "\\dst_color_g\\" << laserDef->m_dst_green
				<< "\\dst_color_b\\" << laserDef->m_dst_blue
				<< "\\dst_color_a\\" << laserDef->m_dst_alpha
				<< "\\uv_layout\\" << laserDef->m_uv
				<< "\\shape\\" << laserDef->m_shape
				<< "\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_LaserDefPtr_Hook;
		void Load_LaserDefPtr(bool atStreamStart)
		{
			auto varLaserDefPtr = *reinterpret_cast<LaserDef***>(0x82C6DE48);

			Load_LaserDefPtr_Hook.Invoke<void>(atStreamStart);

			if (varLaserDefPtr && *varLaserDefPtr)
			{
				if (IniConfig::EnableLaserDefDumper)
					Dump_LaserDef(*varLaserDefPtr);
				//if (IniConfig::EnableLaserDefLoader)
				//	Load_LaserDef(*varLaserDefPtr);
			}
		}

		void Load()
		{
			Load_LaserDefPtr_Hook.Create(0x82260CC8, Load_LaserDefPtr);
		}

		void Unload()
		{
			Load_LaserDefPtr_Hook.Clear();
		}
	}
#endif
}
