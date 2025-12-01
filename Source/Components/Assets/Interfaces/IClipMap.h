#pragma once

#include "IMapEnts.h"
#include "IXModel.h"
#include "IPhysPreset.h"
#include "IFxEffectDef.h"

namespace IClipMap
{
	struct cplane_s
	{
		float normal[3];
		float dist;
		unsigned char type;
		unsigned char pad1[1];
		unsigned short depth;
	};

	struct Bounds
	{
		float midPoint[3];
		float halfSize[3];
	};

	struct cStaticModel_s
	{
		IXModel::XModel *xmodel;
		float origin[3];
		float invScaledAxis[3][3];
		Bounds absBounds;
	};

	struct ClipMaterial
	{
		const char* name;
		int surfaceFlags;
		int contents;
	};

	struct cbrushside_t
	{
		cplane_s* plane;
		unsigned short materialNum;
		unsigned char firstAdjacentSideOffset;
		unsigned char edgeCount;
	};

	struct cNode_t
	{
		cplane_s* plane;
		short children[2];
	};

	struct cLeaf_t
	{
		unsigned short firstCollAabbIndex;
		unsigned short collAabbCount;
		int brushContents;
		int terrainContents;
		Bounds bounds;
		int leafBrushNode;
	};

	struct cLeafBrushNodeLeaf_t
	{
		unsigned short* brushes;
	};

	struct cLeafBrushNodeChildren_t
	{
		float dist;
		float range;
		unsigned short childOffset[2];
	};

	union cLeafBrushNodeData_t
	{
		cLeafBrushNodeLeaf_t leaf;
		cLeafBrushNodeChildren_t children;
	};

	struct cLeafBrushNode_s
	{
		unsigned char axis;
		short leafBrushCount;
		int contents;
		cLeafBrushNodeData_t data;
	};

	struct CollisionBorder
	{
		float distEq[3];
		float zBase;
		float zSlope;
		float start;
		float length;
	};

	struct CollisionPartition
	{
		unsigned char triCount;
		unsigned char borderCount;
		unsigned char firstVertSegment;
		int firstTri;
		CollisionBorder* borders;
	};

	union CollisionAabbTreeIndex
	{
		int firstChildIndex;
		int partitionIndex;
	};

	struct CollisionAabbTree
	{
		float midPoint[3];
		unsigned short materialIndex;
		unsigned short childCount;
		float halfSize[3];
		CollisionAabbTreeIndex u;
	};

	struct cmodel_t
	{
		Bounds bounds;
		float radius;
		cLeaf_t leaf;
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

	struct SModelAabbNode
	{
		Bounds bounds;
		unsigned short firstChild;
		unsigned short childCount;
	};

	enum DynEntityType
	{
		DYNENT_TYPE_INVALID,
		DYNENT_TYPE_CLUTTER,
		DYNENT_TYPE_DESTRUCT,
		DYNENT_TYPE_HINGE,
		DYNENT_TYPE_COUNT,
	};

	struct PhysMass
	{
		float centerOfMass[3];
		float momentsOfInertia[3];
		float productsOfInertia[3];
	};

	struct DynEntityHingeDef;

	struct DynEntityDef
	{
		DynEntityType type;
		//IGfxWorld::GfxPlacement pose;
		IXModel::XModel* xModel;
		unsigned short brushModel;
		unsigned short physicsBrushModel;
		const IFxEffectDef::FxEffectDef* destroyFx;
		IPhysPreset::PhysPreset* physPreset;
		int health;
		DynEntityHingeDef* hinge;
		PhysMass mass;
		int contents;
	};

	struct DynEntityPose
	{
		//IGfxWorld::GfxPlacement pose;
		float radius;
	};

	struct DynEntityHingeDef
	{
		float axisOrigin[3];
		float axisDir[3];
		bool isLimited;
		float angleMin;
		float angleMax;
		float momentOfInertia;
		float friction;
	};

	struct Hinge
	{
		float angle;
		float quat[4];
		float angularVel;
		float torqueAccum;
		bool active;
		float autoDisableTimeLeft;
		const DynEntityHingeDef* def;
		const IPhysPreset::PhysPreset* physPreset;
		float centerOfMassRelToAxisOriginAtAngleZero[3];
	};

	struct DynEntityClient
	{
		int physObjId;
		unsigned short flags;
		unsigned short lightingHandle;
		int health;
		Hinge *hinge;
	};

	struct DynEntityColl
	{
		unsigned short sector;
		unsigned short nextEntInSector;
		float linkMins[2];
		float linkMaxs[2];
	};

	struct clipMap_t
	{
		const char* name;
		int isInUse;
		int planeCount;
		cplane_s* planes;
		unsigned int numStaticModels;
		cStaticModel_s* staticModelList;
		unsigned int numMaterials;
		ClipMaterial* materials;
		unsigned int numBrushSides;
		cbrushside_t* brushsides;
		unsigned int numBrushEdges;
		unsigned char* brushEdges;
		unsigned int numNodes;
		cNode_t* nodes;
		unsigned int numLeafs;
		cLeaf_t* leafs;
		unsigned int leafbrushNodesCount;
		cLeafBrushNode_s* leafbrushNodes;
		unsigned int numLeafBrushes;
		unsigned short* leafbrushes;
		unsigned int numLeafSurfaces;
		unsigned int* leafsurfaces;
		unsigned int vertCount;
		float(*verts)[3];
		int triCount;
		unsigned short* triIndices;
		unsigned char* triEdgeIsWalkable;
		int borderCount;
		CollisionBorder* borders;
		int partitionCount;
		CollisionPartition* partitions;
		int aabbTreeCount;
		CollisionAabbTree* aabbTrees;
		unsigned int numSubModels;
		cmodel_t* cmodels;
		unsigned short numBrushes;
		cbrush_t* brushes;
		Bounds* brushBounds;
		int* brushContents;
		IMapEnts::MapEnts* mapEnts;
		unsigned short smodelNodeCount;
		SModelAabbNode* smodelNodes;
		unsigned short originalDynEntCount;
		unsigned short dynEntCount[2];
		DynEntityDef* dynEntDefList[2];
		DynEntityPose* dynEntPoseList[2];
		DynEntityClient* dynEntClientList[2];
		DynEntityColl* dynEntCollList[2];
		unsigned int checksum;
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
