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
		void Dump_FogDef(const FogDef* fogDef)
		{
			if (!fogDef)
				return;

			std::string assetName = fogDef->mp_name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\fog\\" + assetName + ".fsi";

			std::ostringstream ss;
			ss << "{\n";
			ss << "  [basedist " << fogDef->m_start_dist << "]\n";
			ss << "  [halfdist " << fogDef->m_halfway_dist << "]\n";
			ss << "  [_fogcolor " << fogDef->m_red << " " << fogDef->m_green << " " << fogDef->m_blue << "]\n";
			ss << "  [fogopacity " << fogDef->m_max_opacity << "]\n";
			ss << "  [transitiontime " << fogDef->m_transition_time << "]\n";
			ss << "  [multipliedblend " << fogDef->m_multiplied_blend << "]\n";
			ss << "  [multipliednear " << fogDef->m_multiplied_near_red << " " << fogDef->m_multiplied_near_green << " " << fogDef->m_multiplied_near_blue << "]\n";
			ss << "  [multipliedfar " << fogDef->m_multiplied_far_red << " " << fogDef->m_multiplied_far_green << " " << fogDef->m_multiplied_far_blue << "]\n";
			ss << "  [_suncolor " << fogDef->m_sun_red << " " << fogDef->m_sun_green << " " << fogDef->m_sun_blue << "]\n";
			ss << "  [sundirection " << fogDef->m_sun_dir[0] << " " << fogDef->m_sun_dir[1] << " " << fogDef->m_sun_dir[2] << "]\n";
			ss << "  [sunbeginfadeangle " << fogDef->m_sun_begin_fade_angle << "]\n";
			ss << "  [sunendfadeangle " << fogDef->m_sun_end_fade_angle << "]\n";
			ss << "  [sunfogscale " << fogDef->m_sun_fog_scale << "]\n";
			ss << "}\n";

			std::string outStr = ss.str();
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

			std::ostringstream ss;
			ss << "{\n";
			ss << "  [basedist " << fogDef->m_start_dist << "]\n";
			ss << "  [halfdist " << fogDef->m_halfway_dist << "]\n";
			ss << "  [_fogcolor " << fogDef->m_red << " " << fogDef->m_green << " " << fogDef->m_blue << "]\n";
			ss << "  [fogopacity " << fogDef->m_max_opacity << "]\n";
			ss << "  [transitiontime " << fogDef->m_transition_time << "]\n";
			ss << "  [multipliedblend " << fogDef->m_multiplied_blend << "]\n";
			ss << "  [multipliednear " << fogDef->m_multiplied_near_red << " " << fogDef->m_multiplied_near_green << " " << fogDef->m_multiplied_near_blue << "]\n";
			ss << "  [multipliedfar " << fogDef->m_multiplied_far_red << " " << fogDef->m_multiplied_far_green << " " << fogDef->m_multiplied_far_blue << "]\n";
			ss << "  [_suncolor " << fogDef->m_sun_red << " " << fogDef->m_sun_green << " " << fogDef->m_sun_blue << "]\n";
			ss << "  [sundirection " << fogDef->m_sun_dir[0] << " " << fogDef->m_sun_dir[1] << " " << fogDef->m_sun_dir[2] << "]\n";
			ss << "  [sunbeginfadeangle " << fogDef->m_sun_begin_fade_angle << "]\n";
			ss << "  [sunendfadeangle " << fogDef->m_sun_end_fade_angle << "]\n";
			ss << "  [sunfogscale " << fogDef->m_sun_fog_scale << "]\n";
			ss << "}\n";

			std::string outStr = ss.str();
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
