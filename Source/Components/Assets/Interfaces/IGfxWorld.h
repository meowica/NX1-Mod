#pragma once

#include "IGfxImage.h"
#include "IClipMap.h"
#include "IMaterial.h"
#include "IXModel.h"

namespace IGfxWorld
{
	struct GfxPlacement
	{
		float quat[4];
		float origin[3];
	};

	union GfxColor
	{
		unsigned int packed;
		unsigned char array[4];
	};

	struct GfxSky
	{
		int skySurfCount;
		int* skyStartSurfs;
		IGfxImage::GfxImage* skyImage;
		unsigned char skySamplerState;
	};

	struct GfxWorldDpvsPlanes
	{
		int cellCount;
		IClipMap::cplane_s* planes;
		unsigned short* nodes;
		unsigned int* sceneEntCellBits;
	};

	struct GfxCellTreeCount
	{
		int aabbTreeCount;
	};

	struct GfxAabbTree
	{
		IClipMap::Bounds bounds;
		unsigned short childCount;
		unsigned short surfaceCount;
		unsigned short startSurfIndex;
		unsigned short smodelIndexCount;
		unsigned short* smodelIndexes;
		int childrenOffset;
	};

	struct GfxCellTree
	{
		GfxAabbTree* aabbTree;
	};

	struct GfxPortal;

	struct GfxPortalWritable
	{
		bool isQueued;
		bool isAncestor;
		unsigned char recursionDepth;
		unsigned char hullPointCount;
		float(*hullPoints)[2];
		GfxPortal* queuedParent;
	};

	struct DpvsPlane
	{
		float coeffs[4];
	};

	struct GfxPortal
	{
		GfxPortalWritable writable;
		DpvsPlane plane;
		float(*vertices)[3];
		unsigned short cellIndex;
		unsigned char vertexCount;
		float hullAxis[2][3];
	};

	struct GfxCell
	{
		IClipMap::Bounds bounds;
		int portalCount;
		GfxPortal* portals;
		unsigned char reflectionProbeCount;
		unsigned char* reflectionProbes;
	};

	struct GfxReflectionProbe
	{
		float origin[3];
	};

	struct GfxLightmapArray
	{
		IGfxImage::GfxImage* primary;
		IGfxImage::GfxImage* secondary;
	};

	struct GfxWorldVertex
	{
		float xyz[3];
		float binormalSign;
		GfxColor color;
		Structs::PackedUnitVec binormal;
		float texCoord[2];
		float lmapCoord[2];
		Structs::PackedUnitVec normal;
		Structs::PackedUnitVec tangent;
	};

	struct GfxWorldVertexData
	{
		GfxWorldVertex* vertices;
		D3DVertexBuffer worldVb;
	};

	struct GfxWorldVertexLayerData
	{
		unsigned char* data;
		D3DVertexBuffer layerVb;
	};

	struct GfxWorldDraw
	{
		unsigned int reflectionProbeCount;
		IGfxImage::GfxImage** reflectionProbes;
		GfxReflectionProbe* reflectionProbeOrigins;
		IGfxImage::GfxTexture* reflectionProbeTextures;
		int lightmapCount;
		GfxLightmapArray* lightmaps;
		IGfxImage::GfxTexture* lightmapPrimaryTextures;
		IGfxImage::GfxTexture* lightmapSecondaryTextures;
		IGfxImage::GfxImage* lightmapOverridePrimary;
		IGfxImage::GfxImage* lightmapOverrideSecondary;
		IGfxImage::GfxImage* mp_light_lut;
		unsigned int m_num_light_lut;
		unsigned int m_light_lut_grids_x;
		unsigned int m_light_lut_grids_y;
		unsigned int vertexCount;
		GfxWorldVertexData vd;
		unsigned int vertexLayerDataSize;
		GfxWorldVertexLayerData vld;
		unsigned int indexCount;
		unsigned short* indices;
		D3DIndexBuffer indexBuffer;
	};

	struct GfxLightGridEntry
	{
		unsigned short colorsIndex;
		unsigned char primaryLightIndex;
		unsigned char needsTrace;
	};

	struct GfxLightGridColors
	{
		unsigned char rgb[56][3];
	};

	struct GfxLightGridVolumeNode
	{
		unsigned short reference;
		unsigned short childMask;
	};

	struct DiskGfxLightGridSH
	{
		unsigned short m_coeff[27];
	};

	struct GfxLightGrid
	{
		bool hasLightRegions;
		unsigned int lastSunPrimaryLightIndex;
		unsigned short mins[3];
		unsigned short maxs[3];
		unsigned int rowAxis;
		unsigned int colAxis;
		unsigned short* rowDataStart;
		unsigned int rawRowDataSize;
		unsigned char* rawRowData;
		unsigned int entryCount;
		GfxLightGridEntry* entries;
		unsigned int colorCount;
		GfxLightGridColors* colors;
		unsigned short lightGridMins[3];
		unsigned short lightGridMaxs[3];
		unsigned short lightBlockMins[3];
		unsigned short lightBlockMaxs[3];
		unsigned short nodeTableVersion;
		unsigned short leafTableVersion;
		unsigned int lightGridVolumeRootNodeCount;
		unsigned int* mp_rootNodeTable;
		unsigned int lightGridVolumeNodeCount;
		GfxLightGridVolumeNode* mp_nodeTable;
		unsigned short* mp_nodeArray;
		unsigned int lightGridVolumeLeafSize;
		unsigned char* mp_leafTable;
		unsigned int m_spherical_harmonics_count;
		DiskGfxLightGridSH* mp_spherical_harmonics;
	};

	struct GfxBrushModelWritable
	{
		IClipMap::Bounds bounds;
	};

	struct GfxBrushModel
	{
		GfxBrushModelWritable writable;
		IClipMap::Bounds bounds;
		float radius;
		unsigned short surfaceCount;
		unsigned short startSurfIndex;
	};

	struct MaterialMemory
	{
		IMaterial::Material* material;
		int memory;
	};

	struct sunflare_t
	{
		bool hasValidData;
		IMaterial::Material* spriteMaterial;
		IMaterial::Material* flareMaterial;
		float spriteSize;
		float flareMinSize;
		float flareMinDot;
		float flareMaxSize;
		float flareMaxDot;
		float flareMaxAlpha;
		int flareFadeInTime;
		int flareFadeOutTime;
		float blindMinDot;
		float blindMaxDot;
		float blindMaxDarken;
		int blindFadeInTime;
		int blindFadeOutTime;
		float glareMinDot;
		float glareMaxDot;
		float glareMaxLighten;
		int glareFadeInTime;
		int glareFadeOutTime;
		float sunFxPosition[3];
	};

	struct XModelDrawInfo
	{
		unsigned char hasGfxEntIndex;
		unsigned char lod;
		unsigned short surfId;
	};

	struct GfxSceneDynModel
	{
		XModelDrawInfo info;
		unsigned short dynEntId;
	};

	struct BModelDrawInfo
	{
		unsigned short surfId;
	};

	struct GfxSceneDynBrush
	{
		BModelDrawInfo info;
		unsigned short dynEntId;
	};

	struct GfxShadowGeometry
	{
		unsigned short surfaceCount;
		unsigned short smodelCount;
		unsigned short* sortedSurfIndex;
		unsigned short* smodelIndex;
	};

	struct GfxLightRegionAxis
	{
		float dir[3];
		float midPoint;
		float halfSize;
	};

	struct GfxLightRegionHull
	{
		float kdopMidPoint[9];
		float kdopHalfSize[9];
		unsigned int axisCount;
		GfxLightRegionAxis* axis;
	};

	struct GfxLightRegion
	{
		unsigned int hullCount;
		GfxLightRegionHull* hulls;
	};

	struct GfxStaticModelInst
	{
		IClipMap::Bounds bounds;
		float lightingOrigin[3];
	};

	struct srfTriangles_t
	{
		unsigned int vertexLayerData;
		unsigned int firstVertex;
		unsigned short vertexCount;
		unsigned short triCount;
		unsigned int baseIndex;
	};

	struct GfxSurfaceLightingAndFlagsFields
	{
		unsigned char lightmapIndex;
		unsigned char reflectionProbeIndex;
		unsigned char primaryLightIndex;
		unsigned char flags;
	};

	union GfxSurfaceLightingAndFlags
	{
		GfxSurfaceLightingAndFlagsFields fields;
		unsigned int packed;
	};

	struct GfxSurface
	{
		srfTriangles_t tris;
		IMaterial::Material* material;
		GfxSurfaceLightingAndFlags laf;
	};

	struct GfxSurfaceBounds
	{
		IClipMap::Bounds bounds;
		unsigned short mipRadius;
		unsigned char invHighMipRadius[5];
	};

	struct GfxPackedPlacement
	{
		float origin[3];
		Structs::PackedUnitVec axis[3];
		float scale;
	};

	struct GfxMatrix
	{
		float m[4][4];
	};

	struct SCamoPaletteObjectData
	{
		GfxMatrix m_world_transform;
		float m_origin[4];
		float m_half_lengths[4];
		float m_hsv_vec[4];
		float m_palette_colors[4][3];
		IGfxImage::GfxImage* mp_texture;
		int m_flags;
		float m_intensity;
		int pad[1];
	};

	struct GfxStaticModelDrawInst
	{
		GfxPackedPlacement placement;
		IXModel::XModel* model;
		unsigned short cullDist;
		unsigned short lightingHandle;
		unsigned char reflectionProbeIndex;
		unsigned char primaryLightIndex;
		unsigned char flags;
		unsigned char firstMtlSkinIndex;
		GfxColor groundLighting;
		SCamoPaletteObjectData* mp_camo_palette_data;
	};

	struct GfxCasterBitsLight
	{
		unsigned int primaryLightIndex;
		unsigned int casterBitsIndex;
	};

	struct GfxCasterBits
	{
		unsigned int* bits;
		unsigned int* sortedBits;
	};

	struct GfxWorldDpvsStatic
	{
		unsigned int smodelCount;
		unsigned int staticSurfaceCount;
		unsigned int litOpaqueSurfsBegin;
		unsigned int litOpaqueSurfsEnd;
		unsigned int litTransSurfsBegin;
		unsigned int litTransSurfsEnd;
		unsigned int shadowCasterSurfsBegin;
		unsigned int shadowCasterSurfsEnd;
		unsigned int emissiveSurfsBegin;
		unsigned int emissiveSurfsEnd;
		unsigned int smodelVisDataCount;
		unsigned int surfaceVisDataCount;
		unsigned char* smodelVisData[3];
		unsigned char* surfaceVisData[3];
		unsigned short* sortedSurfIndex;
		GfxStaticModelInst* smodelInsts;
		GfxSurface* surfaces;
		GfxSurfaceBounds* surfacesBounds;
		GfxStaticModelDrawInst* smodelDrawInsts;
		IMaterial::GfxDrawSurf* surfaceMaterials;
		unsigned int* surfaceCastsSunShadow;
		volatile int usageCount;
		unsigned int casterBitsLightsCount;
		GfxCasterBitsLight* casterBitsLights;
		unsigned int casterBitsElemCount;
		unsigned int casterBitsCount;
		GfxCasterBits* casterBits;
	};

	struct GfxWorldDpvsDynamic
	{
		unsigned int dynEntClientWordCount[2];
		unsigned int dynEntClientCount[2];
		unsigned int* dynEntCellBits[2];
		unsigned char* dynEntVisData[2][3];
	};

	struct GfxHeroOnlyLight
	{
		unsigned char type;
		unsigned char unused[3];
		float color[3];
		float dir[3];
		float origin[3];
		float radius;
		float cosHalfFovOuter;
		float cosHalfFovInner;
		int exponent;
	};

	struct GfxWorld
	{
		const char* name;
		const char* baseName;
		int planeCount;
		int nodeCount;
		unsigned int surfaceCount;
		int skyCount;
		GfxSky* skies;
		const char* skyBoxModel;
		unsigned int lastSunPrimaryLightIndex;
		unsigned int primaryLightCount;
		unsigned int sortKeyLitDecal;
		unsigned int sortKeyEffectDecal;
		unsigned int sortKeyEffectAuto;
		unsigned int sortKeyDistortion;
		GfxWorldDpvsPlanes dpvsPlanes;
		GfxCellTreeCount* aabbTreeCounts;
		GfxCellTree* aabbTrees;
		GfxCell* cells;
		GfxWorldDraw draw;
		GfxLightGrid lightGrid;
		int modelCount;
		GfxBrushModel* models;
		IClipMap::Bounds bounds;
		unsigned int checksum;
		int materialMemoryCount;
		MaterialMemory* materialMemory;
		sunflare_t sun;
		float outdoorLookupMatrix[4][4];
		IGfxImage::GfxImage* outdoorImage;
		unsigned int* cellCasterBits;
		unsigned int* cellHasSunLitSurfsBits;
		GfxSceneDynModel* sceneDynModel;
		GfxSceneDynBrush* sceneDynBrush;
		unsigned int* primaryLightEntityShadowVis;
		unsigned int* primaryLightDynEntShadowVis[2];
		unsigned char* nonSunPrimaryLightForModelDynEnt;
		GfxShadowGeometry* shadowGeom;
		GfxLightRegion* lightRegion;
		GfxWorldDpvsStatic dpvs;
		GfxWorldDpvsDynamic dpvsDyn;
		unsigned int mapVtxChecksum;
		unsigned int heroOnlyLightCount;
		GfxHeroOnlyLight* heroOnlyLights;
		unsigned char fogTypesAllowed;
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
