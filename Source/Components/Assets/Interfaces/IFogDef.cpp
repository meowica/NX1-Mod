#include "IFogDef.h"

namespace IFogDef
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_FogDef(const FogDef* fogDef)
		{
			if (!fogDef)
				return;

			std::string assetName = fogDef->mp_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\fog\\" + assetName + ".fsi";

			std::ostringstream oss;
			oss << "basedist [ " << fogDef->m_start_dist << " ]\n";
			oss << "halfdist [ " << fogDef->m_halfway_dist << " ]\n";
			oss << "_fogcolor [ " << fogDef->m_red << " " << fogDef->m_green << " " << fogDef->m_blue << " ]\n";
			oss << "fogopacity [ " << fogDef->m_max_opacity << " ]\n";
			oss << "transitiontime [ " << fogDef->m_transition_time << " ]\n";
			oss << "multipliedblend [ " << fogDef->m_multiplied_blend << " ]\n";
			oss << "multipliednear [ " << fogDef->m_multiplied_near_red << " " << fogDef->m_multiplied_near_green << " " << fogDef->m_multiplied_near_blue << " ]\n";
			oss << "multipliedfar [ " << fogDef->m_multiplied_far_red << " " << fogDef->m_multiplied_far_green << " " << fogDef->m_multiplied_far_blue << " ]\n";
			oss << "_suncolor [ " << fogDef->m_sun_red << " " << fogDef->m_sun_green << " " << fogDef->m_sun_blue << " ]\n";
			oss << "sundirection [ " << fogDef->m_sun_dir[0] << " " << fogDef->m_sun_dir[1] << " " << fogDef->m_sun_dir[2] << " ]\n";
			oss << "sunbeginfadeangle [ " << fogDef->m_sun_begin_fade_angle << " ]\n";
			oss << "sunendfadeangle [ " << fogDef->m_sun_end_fade_angle << " ]\n";
			oss << "sunfogscale [ " << fogDef->m_sun_fog_scale << " ]\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_FogDefPtr_Hook;
		void Load_FogDefPtr(bool atStreamStart)
		{
			auto varFogDefPtr = *reinterpret_cast<FogDef***>(0x82CE6524);

			Load_FogDefPtr_Hook.Invoke<void>(atStreamStart);

			if (varFogDefPtr && *varFogDefPtr)
			{
				if (IniConfig::EnableFogDefDumper)
					Dump_FogDef(*varFogDefPtr);
				//if (IniConfig::EnableFogDefLoader)
				//	Load_FogDef(*varFogDefPtr);
			}
		}

		void Load()
		{
			Load_FogDefPtr_Hook.Create(0x8231C200, Load_FogDefPtr);
		}

		void Unload()
		{
			Load_FogDefPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_FogDef(const FogDef* fogDef)
		{
			if (!fogDef)
				return;

			std::string assetName = fogDef->mp_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\fog\\" + assetName + ".fsi";

			std::ostringstream oss;
			oss << "basedist [ " << fogDef->m_start_dist << " ]\n";
			oss << "halfdist [ " << fogDef->m_halfway_dist << " ]\n";
			oss << "_fogcolor [ " << fogDef->m_red << " " << fogDef->m_green << " " << fogDef->m_blue << " ]\n";
			oss << "fogopacity [ " << fogDef->m_max_opacity << " ]\n";
			oss << "transitiontime [ " << fogDef->m_transition_time << " ]\n";
			oss << "multipliedblend [ " << fogDef->m_multiplied_blend << " ]\n";
			oss << "multipliednear [ " << fogDef->m_multiplied_near_red << " " << fogDef->m_multiplied_near_green << " " << fogDef->m_multiplied_near_blue << " ]\n";
			oss << "multipliedfar [ " << fogDef->m_multiplied_far_red << " " << fogDef->m_multiplied_far_green << " " << fogDef->m_multiplied_far_blue << " ]\n";
			oss << "_suncolor [ " << fogDef->m_sun_red << " " << fogDef->m_sun_green << " " << fogDef->m_sun_blue << " ]\n";
			oss << "sundirection [ " << fogDef->m_sun_dir[0] << " " << fogDef->m_sun_dir[1] << " " << fogDef->m_sun_dir[2] << " ]\n";
			oss << "sunbeginfadeangle [ " << fogDef->m_sun_begin_fade_angle << " ]\n";
			oss << "sunendfadeangle [ " << fogDef->m_sun_end_fade_angle << " ]\n";
			oss << "sunfogscale [ " << fogDef->m_sun_fog_scale << " ]\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_FogDefPtr_Hook;
		void Load_FogDefPtr(bool atStreamStart)
		{
			auto varFogDefPtr = *reinterpret_cast<FogDef***>(0x82C6DF24);

			Load_FogDefPtr_Hook.Invoke<void>(atStreamStart);

			if (varFogDefPtr && *varFogDefPtr)
			{
				if (IniConfig::EnableFogDefDumper)
					Dump_FogDef(*varFogDefPtr);
				//if (IniConfig::EnableFogDefLoader)
				//	Load_FogDef(*varFogDefPtr);
			}
		}

		void Load()
		{
			Load_FogDefPtr_Hook.Create(0x82265E28, Load_FogDefPtr);
		}

		void Unload()
		{
			Load_FogDefPtr_Hook.Clear();
		}
	}
#endif
}
