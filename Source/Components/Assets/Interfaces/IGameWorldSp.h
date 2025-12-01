#pragma once

namespace IGameWorldSp
{
	enum nodeType
	{
		NODE_ERROR,
		NODE_PATHNODE,
		NODE_UAV_CIRCLE,
		NODE_COVER_STAND,
		NODE_COVER_CROUCH,
		NODE_COVER_CROUCH_WINDOW,
		NODE_COVER_PRONE,
		NODE_COVER_RIGHT,
		NODE_COVER_LEFT,
		NODE_AMBUSH,
		NODE_EXPOSED,
		NODE_CONCEALMENT_STAND,
		NODE_CONCEALMENT_CROUCH,
		NODE_CONCEALMENT_PRONE,
		NODE_DOOR,
		NODE_DOOR_INTERIOR,
		NODE_SCRIPTED,
		NODE_CUSTOM,
		NODE_NEGOTIATION_BEGIN,
		NODE_NEGOTIATION_END,
		NODE_TURRET,
		NODE_GUARD,
		NODE_NUMTYPES,
		NODE_DONTLINK,
	};

	enum PathNodeErrorCode
	{
		PNERR_NONE,
		PNERR_INSOLID,
		PNERR_FLOATING,
		PNERR_NOLINK,
		PNERR_DUPLICATE,
		PNERR_NOSTANCE,
		PNERR_INVALIDDOOR,
		PNERR_NOANGLES,
		PNERR_BADPLACEMENT,
		NUM_PATH_NODE_ERRORS,
	};

	struct pathlink_s
	{
		float fDist;
		unsigned short nodeNum;
		unsigned char disconnectCount;
		unsigned char negotiationLink;
		unsigned char flags;
		unsigned char ubBadPlaceCount[3];
	};

	struct pathnode_constant_t
	{
		nodeType type;
		unsigned short spawnflags;
		unsigned short targetname;
		unsigned short script_linkName;
		unsigned short script_noteworthy;
		unsigned short target;
		unsigned short animscript;
		int animscriptfunc;
		float vOrigin[3];
		float fAngle;
		float forward[2];
		float fRadius;
		float minUseDistSq;
		PathNodeErrorCode error;
		short wOverlapNode[2];
		unsigned short totalLinkCount;
		pathlink_s* Links;
	};

	struct pathnode_dynamic_t
	{
		void* pOwner;
		int iFreeTime;
		int iValidTime[3];
		int dangerousNodeTime[3];
		int inPlayerLOSTime;
		short wLinkCount;
		short wOverlapCount;
		short turretEntNumber;
		unsigned char userCount;
		bool hasBadPlaceLink;
	};

	struct pathnode_t;

	struct pathnode_transient_t
	{
		int iSearchFrame;
		pathnode_t* pNextOpen;
		pathnode_t* pPrevOpen;
		pathnode_t* pParent;
		float fCost;
		float fHeuristic;
		float nodeCost;
		int linkIndex;
	};

	struct pathnode_t
	{
		pathnode_constant_t constant;
		pathnode_dynamic_t dynamic;
		pathnode_transient_t transient;
	};

	struct pathbasenode_t
	{
		float vOrigin[3];
		unsigned int type;
	};

	struct pathnode_tree_t;

	struct pathnode_tree_nodes_t
	{
		int nodeCount;
		unsigned short* nodes;
	};

	union pathnode_tree_info_t
	{
		pathnode_tree_t* child[2];
		pathnode_tree_nodes_t s;
	};

	struct pathnode_tree_t
	{
		int axis;
		float dist;
		pathnode_tree_info_t u;
	};

	struct PathData
	{
		unsigned int nodeCount;
		pathnode_t* nodes;
		pathbasenode_t* basenodes;
		unsigned int chainNodeCount;
		unsigned short* chainNodeForNode;
		unsigned short* nodeForChainNode;
		int visBytes;
		unsigned char* pathVis;
		int nodeTreeCount;
		pathnode_tree_t* nodeTree;
	};

	struct VehicleTrackObstacle
	{
		float origin[2];
		float radius;
	};

	struct VehicleTrackSector
	{
		float startEdgeDir[2];
		float startEdgeDist;
		float leftEdgeDir[2];
		float leftEdgeDist;
		float rightEdgeDir[2];
		float rightEdgeDist;
		float sectorLength;
		float sectorWidth;
		float totalPriorLength;
		float totalFollowingLength;
		VehicleTrackObstacle* obstacles;
		unsigned int obstacleCount;
	};

	struct VehicleTrackSegment
	{
		const char* targetName;
		VehicleTrackSector* sectors;
		unsigned int sectorCount;
		const VehicleTrackSegment** nextBranches;
		unsigned int nextBranchesCount;
		const VehicleTrackSegment** prevBranches;
		unsigned int prevBranchesCount;
		float endEdgeDir[2];
		float endEdgeDist;
		float totalLength;
	};

	struct VehicleTrack
	{
		VehicleTrackSegment* segments;
		unsigned int segmentCount;
	};

	struct G_GlassPiece
	{
		unsigned short damageTaken;
		unsigned short collapseTime;
		int lastStateChangeTime;
		unsigned char impactDir;
		unsigned char impactPos[2];
	};

	struct G_GlassName
	{
		char* nameStr;
		unsigned short name;
		unsigned short pieceCount;
		unsigned short *pieceIndices;
	};

	struct G_GlassData
	{
		G_GlassPiece* glassPieces;
		unsigned int pieceCount;
		unsigned short damageToWeaken;
		unsigned short damageToDestroy;
		unsigned int glassNameCount;
		G_GlassName* glassNames;
		unsigned char pad[108];
	};

	struct GameWorldSp
	{
		const char* name;
		PathData path;
		VehicleTrack vehicleTrack;
		G_GlassData* g_glassData;
	};

#ifdef IS_SP
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
