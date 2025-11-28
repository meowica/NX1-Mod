#pragma once

#include "IMaterial.h"
#include "IPhysCollmap.h"
#include "IPhysPreset.h"
#include "IXModelSurfs.h"

namespace IXModel
{
	struct DObjAnimMat
	{
		float quat[4];
		float trans[3];
		float transWeight;
	};

	struct XModelLodInfo
	{
		float dist;
		unsigned short numsurfs;
		unsigned short surfIndex;
		IXModelSurfs::XModelSurfs* modelSurfs;
		IXModelSurfs::XPartBits partBits;
		IXModelSurfs::XSurface* surfs;
	};

	struct XModelCollSurf_s
	{
		IPhysCollmap::Bounds bounds;
		int boneIdx;
		int contents;
		int surfFlags;
	};

	struct XBoneInfo
	{
		IPhysCollmap::Bounds bounds;
		float radiusSquared;
	};

	struct XModel
	{
		const char* name;
		unsigned char numBones;
		unsigned char numRootBones;
		unsigned char numsurfs;
		float scale;
		unsigned int noScalePartBits[6];
		unsigned short* boneNames;
		unsigned char* parentList;
		short* quats;
		float* trans;
		unsigned char* partClassification;
		DObjAnimMat* baseMat;
		IMaterial::Material** materialHandles;
		XModelLodInfo lodInfo[4];
		char maxLoadedLod;
		char numLods;
		char collLod;
		unsigned char flags;
		XModelCollSurf_s* collSurfs;
		int numCollSurfs;
		int contents;
		XBoneInfo* boneInfo;
		float radius;
		IPhysCollmap::Bounds bounds;
		unsigned short* invHighMipRadius;
		int memUsage;
		IPhysPreset::PhysPreset* physPreset;
		IPhysCollmap::PhysCollmap* physCollmap;
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
