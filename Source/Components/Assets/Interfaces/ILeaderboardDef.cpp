#include "ILeaderboardDef.h"

namespace ILeaderboardDef
{
	const char* LbColTypeNames[7] =
	{
		"NUMBER",
		"TIME",
		"LEVELXP",
		"PRESTIGE",
		"BIGNUMBER",
		"PERCENT",
		"TIME_FULL"
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

			std::ostringstream oss;
			oss << "name,type,default,min,max\n";

			for (int i = 0; i < leaderboardDef->columnCount; ++i)
			{
				const LbColumnDef& lbCol = leaderboardDef->columns[i];

				const char* lbColType = "UNKNOWN";
				if (lbCol.type >= 0 && lbCol.type < 7)
					lbColType = LbColTypeNames[lbCol.type];

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

				oss << (lbCol.name) << ","
					<< lbColType << ","
					<< std::fixed << std::setprecision(7)
					<< defaultVal << ","
					<< std::setprecision(1)
					<< minVal << ","
					<< maxVal << "\n";
			}

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

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\leaderboards\\" + assetName + ".csv";

			std::ostringstream oss;
			oss << "name,type,default,min,max\n";

			for (int i = 0; i < leaderboardDef->columnCount; ++i)
			{
				const LbColumnDef& lbCol = leaderboardDef->columns[i];

				const char* lbColType = "UNKNOWN";
				if (lbCol.type >= 0 && lbCol.type < 7)
					lbColType = LbColTypeNames[lbCol.type];

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

				oss << (lbCol.name) << ","
					<< lbColType << ","
					<< std::fixed << std::setprecision(7)
					<< defaultVal << ","
					<< std::setprecision(1)
					<< minVal << ","
					<< maxVal << "\n";
			}

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
