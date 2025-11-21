namespace ILeaderboardDef
{
	const char* ColTypeNames[7] =
	{
		"NUMBER",
		"TIME",
		"LEVELXP",
		"PRESTIGE",
		"BIGNUMBER",
		"PERCENT",
		"TIME_FULL"
	};

	enum LbAggType
	{
		LBAGG_TYPE_MIN,
		LBAGG_TYPE_MAX,
		LBAGG_TYPE_SUM,
		LBAGG_TYPE_LAST,
		LBAGG_TYPE_COUNT,
	};

	enum LbColType
	{
		LBCOL_TYPE_NUMBER,
		LBCOL_TYPE_TIME,
		LBCOL_TYPE_LEVELXP,
		LBCOL_TYPE_PRESTIGE,
		LBCOL_TYPE_BIGNUMBER,
		LBCOL_TYPE_PERCENT,
		LBCOL_TYPE_COUNT,
	};

	struct LbColumnDef
	{
		const char* name;
		int id;
		int propertyId;
		bool hidden;
		const char* statName;
		LbColType type;
		int precision;
		LbAggType agg;
	};

	struct LeaderboardDef
	{
		const char* name;
		int id;
		int columnCount;
		int xpColId;
		int prestigeColId;
		LbColumnDef* columns;
	};

#ifdef IS_MP
	namespace MP
	{
		void Dump_LeaderboardDef(const LeaderboardDef* leaderboardDef)
		{
			if (!leaderboardDef)
				return;

			std::string assetName = leaderboardDef->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');
			std::transform(assetName.begin(), assetName.end(), assetName.begin(), ::tolower);

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\leaderboards\\" + assetName + ".csv";
			std::ostringstream ss;

			ss << "name,type,default,min,max\n";

			for (int i = 0; i < leaderboardDef->columnCount; ++i)
			{
				const LbColumnDef& col = leaderboardDef->columns[i];

				const char* colType = "UNKNOWN";
				if (col.type >= 0 && col.type < 7)
					colType = ColTypeNames[col.type];

				float defaultVal = 0.0f;
				float minVal = 0.0f;
				float maxVal = 2.0f;

				switch (col.type)
				{
				case LBCOL_TYPE_NUMBER:
				case LBCOL_TYPE_PERCENT:
					defaultVal = static_cast<float>(col.precision) / 10.0f;
					break;
				case LBCOL_TYPE_BIGNUMBER:
				case LBCOL_TYPE_LEVELXP:
					defaultVal = static_cast<float>(col.precision);
					break;
				case LBCOL_TYPE_PRESTIGE:
					defaultVal = 1.0f;
					break;
				default:
					defaultVal = 0.0f;
					break;
				}

				ss << (col.name) << ","
					<< colType << ","
					<< std::fixed << std::setprecision(7) << defaultVal << ","
					<< std::setprecision(1) << minVal << ","
					<< maxVal << "\n";
			}

			std::string outStr = ss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_LeaderboardDefPtr_Hook;
		void Load_LeaderboardDefPtr(bool atStreamStart)
		{
			auto varLeaderboardDefPtr = *reinterpret_cast<LeaderboardDef***>(0x82CE6B50);

			Load_LeaderboardDefPtr_Hook.Invoke<void>(atStreamStart);

			if (varLeaderboardDefPtr && *varLeaderboardDefPtr)
			{
				if (IniConfig::EnableLeaderboardDefDumper)
					Dump_LeaderboardDef(*varLeaderboardDefPtr);
				//if (IniConfig::EnableLeaderboardDefLoader)
				//	Load_LeaderboardDef(*varLeaderboardDefPtr);
			}
		}

		void Load()
		{
			Load_LeaderboardDefPtr_Hook.Create(0x8231BBF0, Load_LeaderboardDefPtr);
		}

		void Unload()
		{
			Load_LeaderboardDefPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_LeaderboardDef(const LeaderboardDef* leaderboardDef)
		{
			if (!leaderboardDef)
				return;

			std::string assetName = leaderboardDef->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');
			std::transform(assetName.begin(), assetName.end(), assetName.begin(), ::tolower);

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\leaderboards\\" + assetName + ".csv";
			std::ostringstream ss;

			ss << "name,type,default,min,max\n";

			for (int i = 0; i < leaderboardDef->columnCount; ++i)
			{
				const LbColumnDef& col = leaderboardDef->columns[i];

				const char* colType = "UNKNOWN";
				if (col.type >= 0 && col.type < 7)
					colType = ColTypeNames[col.type];

				float defaultVal = 0.0f;
				float minVal = 0.0f;
				float maxVal = 2.0f;

				switch (col.type)
				{
				case LBCOL_TYPE_NUMBER:
				case LBCOL_TYPE_PERCENT:
					defaultVal = static_cast<float>(col.precision) / 10.0f;
					break;
				case LBCOL_TYPE_BIGNUMBER:
				case LBCOL_TYPE_LEVELXP:
					defaultVal = static_cast<float>(col.precision);
					break;
				case LBCOL_TYPE_PRESTIGE:
					defaultVal = 1.0f;
					break;
				default:
					defaultVal = 0.0f;
					break;
				}

				ss << (col.name) << ","
					<< colType << ","
					<< std::fixed << std::setprecision(7) << defaultVal << ","
					<< std::setprecision(1) << minVal << ","
					<< maxVal << "\n";
			}

			std::string outStr = ss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_LeaderboardDefPtr_Hook;
		void Load_LeaderboardDefPtr(bool atStreamStart)
		{
			auto varLeaderboardDefPtr = *reinterpret_cast<LeaderboardDef***>(0x82C6E550);

			Load_LeaderboardDefPtr_Hook.Invoke<void>(atStreamStart);

			if (varLeaderboardDefPtr && *varLeaderboardDefPtr)
			{
				if (IniConfig::EnableLeaderboardDefDumper)
					Dump_LeaderboardDef(*varLeaderboardDefPtr);
				//if (IniConfig::EnableLeaderboardDefLoader)
				//	Load_LeaderboardDef(*varLeaderboardDefPtr);
			}
		}

		void Load()
		{
			Load_LeaderboardDefPtr_Hook.Create(0x82265818, Load_LeaderboardDefPtr);
		}

		void Unload()
		{
			Load_LeaderboardDefPtr_Hook.Clear();
		}
	}
#endif
}
