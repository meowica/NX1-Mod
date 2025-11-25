#pragma once

#include "IGfxImage.h"
#include "IMaterialTechniqueSet.h"

namespace IMaterial
{
	struct GfxDrawSurfFields
	{
		unsigned long long objectId : 16;
		unsigned long long reflectionProbeIndex : 8;
		unsigned long long hasGfxEntIndex : 1;
		unsigned long long customIndex : 5;
		unsigned long long materialSortedIndex : 12;
		unsigned long long prepass : 2;
		unsigned long long useHeroLighting : 1;
		unsigned long long sceneLightIndex : 8;
		unsigned long long surfType : 4;
		unsigned long long primarySortKey : 6;
		unsigned long long unused : 1;
	};

	union GfxDrawSurf
	{
		GfxDrawSurfFields fields;
		unsigned long long packed;
	};

	struct MaterialInfo
	{
		const char* name;
		unsigned short gameFlags;
		unsigned char sortKey;
		unsigned char textureAtlasRowCount;
		unsigned char textureAtlasColumnCount;
		unsigned char textureAtlasFrameBlend;
		GfxDrawSurf drawSurf;
		unsigned int surfaceTypeBits;
	};

	struct WaterWritable
	{
		float floatTime;
	};

	struct water_t
	{
		WaterWritable writable;
		float* H0X;
		float* H0Y;
		float* wTerm;
		int M;
		int N;
		float Lx;
		float Lz;
		float gravity;
		float windvel;
		float winddir[2];
		float amplitude;
		float codeConstant[4];
		IGfxImage::GfxImage* image;
	};

	union MaterialTextureDefInfo
	{
		IGfxImage::GfxImage* image;
		water_t* water;
	};

	struct MaterialTextureDef
	{
		unsigned int nameHash;
		char nameStart;
		char nameEnd;
		unsigned char samplerState;
		unsigned char m_semantic;
		MaterialTextureDefInfo u;
		IGfxImage::GfxImage* mp_override_image;
		unsigned int m_override_image;
	};

	struct MaterialConstantDef
	{
		unsigned int nameHash;
		char name[12];
		float literal[4];
	};

	struct GfxStateBits
	{
		unsigned int loadBits[3];
	};

	struct Material
	{
		MaterialInfo info;
		unsigned char stateBitsEntry[52];
		unsigned char textureCount;
		unsigned char constantCount;
		unsigned char stateBitsCount;
		unsigned char stateFlags;
		unsigned char cameraRegion;
		unsigned char layerCount;
		IMaterialTechniqueSet::MaterialTechniqueSet* techniqueSet;
		MaterialTextureDef* textureTable;
		MaterialConstantDef* constantTable;
		GfxStateBits* stateBitsTable;
		const char** subMaterials;
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
