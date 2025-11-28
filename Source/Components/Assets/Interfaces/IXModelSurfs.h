#pragma once

namespace IXModelSurfs
{
	struct XSurfaceVertexInfo
	{
		short vertCount[4];
		unsigned short* vertsBlend;
		float* tensionData;
	};

	union GfxColor
	{
		unsigned int packed;
		unsigned char array[4];
	};

	union PackedUnitVec
	{
		unsigned int packed;
	};

	union PackedTexCoords
	{
		unsigned int packed;
	};

	struct GfxPackedVertex
	{
		float xyz[3];
		float binormalSign;
		GfxColor color;
		PackedUnitVec binormal;
		PackedTexCoords texCoord;
		PackedUnitVec normal;
		PackedUnitVec tangent;
	};

	struct XPartBits
	{
		int m_array[6];
	};

	struct XSurfaceCollisionAabb
	{
		unsigned short mins[3];
		unsigned short maxs[3];
	};

	struct XSurfaceCollisionNode
	{
		XSurfaceCollisionAabb aabb;
		unsigned short childBeginIndex;
		unsigned short childCount;
	};

	struct XSurfaceCollisionLeaf
	{
		unsigned short triangleBeginIndex;
	};

	struct XSurfaceCollisionTree
	{
		float trans[3];
		unsigned int nodeCount;
		float scale[3];
		XSurfaceCollisionNode* nodes;
		float invScale[3];
		unsigned int leafCount;
		XSurfaceCollisionLeaf* leafs;
		unsigned int pad[3];
	};

	struct XRigidVertList
	{
		unsigned short boneOffset;
		unsigned short vertCount;
		unsigned short triOffset;
		unsigned short triCount;
		XSurfaceCollisionTree* collisionTree;
	};

	struct XSurface
	{
		unsigned char tileMode;
		bool deformed;
		unsigned short vertCount;
		unsigned short triCount;
		unsigned short *triIndices;
		XSurfaceVertexInfo vertInfo;
		unsigned int m_flags;
		GfxPackedVertex* verts0;
		void* p_stream0;
		D3DVertexBuffer vb0;
		unsigned int vertListCount;
		XRigidVertList* vertList;
		D3DIndexBuffer indexBuffer;
		XPartBits partBits;
	};

	struct XModelSurfs
	{
		const char* name;
		XSurface* surfs;
		unsigned short numsurfs;
		XPartBits partBits;
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
