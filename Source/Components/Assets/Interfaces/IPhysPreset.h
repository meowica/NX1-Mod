#pragma once

namespace IPhysPreset
{
	struct sndPhysicsParams
	{
		float soundPitchLow;
		float soundPitchHigh;
		float soundVolLow;
		float soundVolHigh;
		float soundImpactRangeLow;
		float soundImpactRangeHigh;
	};

	struct PhysPreset
	{
		const char* name;
		int type;
		float mass;
		float bounce;
		float friction;
		float bulletForceScale;
		float explosiveForceScale;
		const char* sndAliasPrefix;
		sndPhysicsParams sndParams;
		float piecesSpreadFraction;
		float piecesUpwardVelocity;
		bool tempDefaultToCylinder;
		bool perSurfaceSndAlias;
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
