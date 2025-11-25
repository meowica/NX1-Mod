#pragma once

namespace ILeaderboardDef
{
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
