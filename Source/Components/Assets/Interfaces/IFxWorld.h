#pragma once

#include "IPhysPreset.h"
#include "IMaterial.h"

namespace IFxWorld
{
	union GfxColor
	{
		unsigned int packed;
		unsigned char array[4];
	};

	struct FxGlassDef
	{
		float halfThickness;
		float texVecs[2][2];
		GfxColor color;
		IMaterial::Material* material;
		IMaterial::Material* materialShattered;
		const IPhysPreset::PhysPreset* p_physPreset;
		float invHighMipRadius;
		float shatteredInvHighMipRadius;
	};

	struct FxSpatialFrame
	{
		float quat[4];
		__vector4 quatVec;
		float origin[3];
		float originVec4[4];
		__vector4 originVec;
	};

	union FxGlassPiecePlace
	{
		FxSpatialFrame frame;
		float radius;
		unsigned int nextFree;
		unsigned int pad[3];
	};

	struct FxGlassPieceState
	{
		float texCoordOrigin[2];
		unsigned int supportMask;
		unsigned short initIndex;
		unsigned short geoDataStart;
		unsigned char defIndex;
		unsigned char pad[5];
		unsigned char vertCount;
		unsigned char holeDataCount;
		unsigned char crackDataCount;
		unsigned char fanDataCount;
		unsigned short flags;
		float areaX2;
	};

	struct FxGlassPieceDynamics
	{
		int fallTime;
		int physObjId;
		int physJointId;
		float vel[3];
		float avel[3];
	};

	struct FxGlassInitPieceState
	{
		FxSpatialFrame frame;
		float radius;
		float texCoordOrigin[2];
		unsigned int supportMask;
		float areaX2;
		unsigned char defIndex;
		unsigned char vertCount;
		unsigned char fanDataCount;
		unsigned char pad[1];
		int pad1[2];
	};

	struct FxGlassVertex
	{
		short x;
		short y;
	};

	struct FxGlassHoleHeader
	{
		unsigned short uniqueVertCount;
		unsigned char touchVert;
		unsigned char pad[1];
	};

	struct FxGlassCrackHeader
	{
		unsigned short uniqueVertCount;
		unsigned char beginVertIndex;
		unsigned char endVertIndex;
	};

	union FxGlassGeometryData
	{
		FxGlassVertex vert;
		FxGlassHoleHeader hole;
		FxGlassCrackHeader crack;
		unsigned char asBytes[4];
		short anonymous[2];
	};

	struct FxGlassSystem
	{
		int time;
		int prevTime;
		unsigned int defCount;
		unsigned int pieceLimit;
		unsigned int pieceWordCount;
		unsigned int initPieceCount;
		unsigned int cellCount;
		unsigned int activePieceCount;
		unsigned int firstFreePiece;
		unsigned int geoDataLimit;
		unsigned int geoDataCount;
		unsigned int initGeoDataCount;
		FxGlassDef* p_defs;
		FxGlassPiecePlace* p_piecePlaces;
		FxGlassPieceState* p_pieceStates;
		FxGlassPieceDynamics* p_pieceDynamics;
		FxGlassGeometryData* p_geoData;
		unsigned int* p_isInUse;
		unsigned int* p_cellBits;
		unsigned char* p_visData;
		float(*p_linkOrg)[3];
		float* p_halfThickness;
		unsigned short* p_lightingHandles;
		FxGlassInitPieceState* p_initPieceStates;
		FxGlassGeometryData* p_initGeoData;
		bool needToCompactData;
		unsigned char initCount;
		float effectChanceAccum;
		int lastPieceDeletionTime;
	};

	struct FxWorld
	{
		const char* name;
		FxGlassSystem glassSys;
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
