#pragma once

namespace IPhysCollmap
{
	struct cplane_s
	{
		float normal[3];
		float dist;
		unsigned char type;
		unsigned char pad1[1];
		unsigned short depth;
	};

	struct cbrushside_t
	{
		cplane_s* plane;
		unsigned short materialNum;
		unsigned char firstAdjacentSideOffset;
		unsigned char edgeCount;
	};

	struct cbrush_t
	{
		unsigned short numsides;
		unsigned short glassPieceIndex;
		cbrushside_t* sides;
		unsigned char* baseAdjacentSide;
		short axialMaterialNum[2][3];
		unsigned char firstAdjacentSideOffsets[2][3];
		unsigned char edgeCount[2][3];
	};

	struct Bounds
	{
		float midPoint[3];
		float halfSize[3];
	};

	struct BrushWrapper
	{
		Bounds bounds;
		cbrush_t brush;
		int totalEdgeCount;
		cplane_s* planes;
	};

	struct PhysGeomInfo
	{
		BrushWrapper* brushWrapper;
		int type;
		float orientation[3][3];
		Bounds bounds;
	};

	struct PhysMass
	{
		float centerOfMass[3];
		float momentsOfInertia[3];
		float productsOfInertia[3];
	};

	struct PhysCollmap
	{
		const char* name;
		unsigned int count;
		PhysGeomInfo* geoms;
		PhysMass mass;
		Bounds bounds;
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
