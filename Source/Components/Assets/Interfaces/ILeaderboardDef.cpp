#include "ILeaderboardDef.h"

namespace ILeaderboardDef
{
	const char* LbColTypeNames[] =
	{
		"NUMBER",
		"TIME",
		"LEVELXP",
		"PRESTIGE",
		"BIGNUMBER",
		"PERCENT",
		"COUNT"
	};

	const char* LbAggTypeNames[] =
	{
		"MIN",
		"MAX",
		"SUM",
		"LAST",
		"COUNT"
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

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\leaderboards\\" + assetName + ".json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << leaderboardDef->name << "\",\n";
			oss << "  \"id\": " << leaderboardDef->id << ",\n";
			oss << "  \"columnCount\": " << leaderboardDef->columnCount << ",\n";
			oss << "  \"xpColId\": " << leaderboardDef->xpColId << ",\n";
			oss << "  \"prestigeColId\": " << leaderboardDef->prestigeColId << ",\n";
			oss << "  \"columns\": [\n";

			for (int i = 0; i < leaderboardDef->columnCount; ++i)
			{
				const LbColumnDef& lbCol = leaderboardDef->columns[i];

				const char* lbColType = "UNKNOWN";
				if (lbCol.type >= 0 && lbCol.type < LBCOL_TYPE_COUNT)
					lbColType = LbColTypeNames[lbCol.type];

				const char* lbAggType = "UNKNOWN";
				if (lbCol.agg >= 0 && lbCol.agg < LBAGG_TYPE_COUNT)
					lbAggType = LbAggTypeNames[lbCol.agg];

				float defaultVal = 0.0f;
				float minVal = 0.0f;
				float maxVal = 2.0f;

				switch (lbCol.type)
				{
				case LBCOL_TYPE_NUMBER:
				case LBCOL_TYPE_PERCENT:
					defaultVal = static_cast<float>(lbCol.precision) / 10.0f;
					break;
				case LBCOL_TYPE_BIGNUMBER:
				case LBCOL_TYPE_LEVELXP:
					defaultVal = static_cast<float>(lbCol.precision);
					break;
				case LBCOL_TYPE_PRESTIGE:
					defaultVal = 1.0f;
					break;
				default:
					defaultVal = 0.0f;
					break;
				}

				oss << "    {\n";
				oss << "      \"name\": \"" << lbCol.name << "\",\n";
				oss << "      \"id\": " << lbCol.id << ",\n";
				oss << "      \"propertyId\": " << lbCol.propertyId << ",\n";
				oss << "      \"hidden\": " << (lbCol.hidden ? "true" : "false") << ",\n";
				oss << "      \"statName\": \"" << (lbCol.statName ? lbCol.statName : "") << "\",\n";
				oss << "      \"type\": \"" << lbColType << "\",\n";
				oss << "      \"precision\": " << lbCol.precision << ",\n";
				oss << "      \"agg\": \"" << lbAggType << "\",\n";
				oss << "      \"default\": " << std::fixed << std::setprecision(7) << defaultVal << ",\n";
				oss << "      \"min\": " << std::setprecision(1) << minVal << ",\n";
				oss << "      \"max\": " << maxVal << "\n";
				oss << "    }";

				if (i < leaderboardDef->columnCount - 1)
					oss << ",";

				oss << "\n";
			}

			oss << "  ]\n";
			oss << "}\n";

			std::string outStr = oss.str();
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

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\leaderboards\\" + assetName + ".json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << leaderboardDef->name << "\",\n";
			oss << "  \"id\": " << leaderboardDef->id << ",\n";
			oss << "  \"columnCount\": " << leaderboardDef->columnCount << ",\n";
			oss << "  \"xpColId\": " << leaderboardDef->xpColId << ",\n";
			oss << "  \"prestigeColId\": " << leaderboardDef->prestigeColId << ",\n";
			oss << "  \"columns\": [\n";

			for (int i = 0; i < leaderboardDef->columnCount; ++i)
			{
				const LbColumnDef& lbCol = leaderboardDef->columns[i];

				const char* lbColType = "UNKNOWN";
				if (lbCol.type >= 0 && lbCol.type < LBCOL_TYPE_COUNT)
					lbColType = LbColTypeNames[lbCol.type];

				const char* lbAggType = "UNKNOWN";
				if (lbCol.agg >= 0 && lbCol.agg < LBAGG_TYPE_COUNT)
					lbAggType = LbAggTypeNames[lbCol.agg];

				float defaultVal = 0.0f;
				float minVal = 0.0f;
				float maxVal = 2.0f;

				switch (lbCol.type)
				{
				case LBCOL_TYPE_NUMBER:
				case LBCOL_TYPE_PERCENT:
					defaultVal = static_cast<float>(lbCol.precision) / 10.0f;
					break;
				case LBCOL_TYPE_BIGNUMBER:
				case LBCOL_TYPE_LEVELXP:
					defaultVal = static_cast<float>(lbCol.precision);
					break;
				case LBCOL_TYPE_PRESTIGE:
					defaultVal = 1.0f;
					break;
				default:
					defaultVal = 0.0f;
					break;
				}

				oss << "    {\n";
				oss << "      \"name\": \"" << lbCol.name << "\",\n";
				oss << "      \"id\": " << lbCol.id << ",\n";
				oss << "      \"propertyId\": " << lbCol.propertyId << ",\n";
				oss << "      \"hidden\": " << (lbCol.hidden ? "true" : "false") << ",\n";
				oss << "      \"statName\": \"" << (lbCol.statName ? lbCol.statName : "") << "\",\n";
				oss << "      \"type\": \"" << lbColType << "\",\n";
				oss << "      \"precision\": " << lbCol.precision << ",\n";
				oss << "      \"agg\": \"" << lbAggType << "\",\n";
				oss << "      \"default\": " << std::fixed << std::setprecision(7) << defaultVal << ",\n";
				oss << "      \"min\": " << std::setprecision(1) << minVal << ",\n";
				oss << "      \"max\": " << maxVal << "\n";
				oss << "    }";

				if (i < leaderboardDef->columnCount - 1)
					oss << ",";

				oss << "\n";
			}

			oss << "  ]\n";
			oss << "}\n";

			std::string outStr = oss.str();
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
