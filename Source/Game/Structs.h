#pragma once

namespace Structs
{
	struct CmdArgs
	{
		int nesting;
		int localClientNum[8];
		int controllerIndex[8];
		int argc[8];
		const char** argv[8];
	};

	struct cmd_function_s
	{
		cmd_function_s* next;
		const char* name;
		const char* autoCompleteDir;
		const char* autoCompleteExt;
		void (__cdecl* function)();
	};

	enum DvarSetSource
	{
		DVAR_SOURCE_INTERNAL,
		DVAR_SOURCE_EXTERNAL,
		DVAR_SOURCE_SCRIPT,
	};

	union DvarValue
	{
		bool enabled;
		int integer;
		unsigned int unsignedInt;
		float value;
		float vector[4];
		const char* string;
		unsigned char color[4];
	};

	struct EnumLimit
	{
		int stringCount;
		const char** strings;
	};

	struct IntLimit
	{
		int min;
		int max;
	};

	struct FloatLimit
	{
		float min;
		float max;
	};

	union DvarLimits
	{
		EnumLimit enumeration;
		IntLimit integer;
		FloatLimit value;
		FloatLimit vector;
	};

	struct dvar_t
	{
		const char* name;
		const char* description;
		unsigned int flags;
		char type;
		bool modified;
		DvarValue current;
		DvarValue latched;
		DvarValue reset;
		DvarLimits domain;
		dvar_t* hashNext;
	};

	struct ScreenPlacement
	{
		float scaleVirtualToReal[2];
		float scaleVirtualToFull[2];
		float scaleRealToVirtual[2];
		float realViewportPosition[2];
		float realViewportSize[2];
		float virtualViewableMin[2];
		float virtualViewableMax[2];
		float realViewableMin[2];
		float realViewableMax[2];
		float virtualAdjustableMin[2];
		float virtualAdjustableMax[2];
		float realAdjustableMin[2];
		float realAdjustableMax[2];
		float subScreenLeft;
	};

	struct SysFile
	{
		HANDLE handle;
		int startOffset;
	};

	struct DBFile
	{
		SysFile handle;
		char name[64];
	};

	struct db_internal_state
	{
		int dummy;
	};

	struct db_z_stream_s
	{
		unsigned char *next_in;
		unsigned int avail_in;
		unsigned int total_in;
		unsigned char *next_out;
		unsigned int avail_out;
		unsigned int total_out;
		char *msg;
		db_internal_state *state;
		unsigned char *(__cdecl *zalloc)(unsigned char *, unsigned int, unsigned int);
		void (__cdecl *zfree)(unsigned char *, unsigned char *);
		unsigned char *opaque;
		int data_type;
	};

	struct DBLoadData
	{
	  DBFile *p_file;
	  int outstandingRead;
	  unsigned char *p_fileBuffer;
	  unsigned int readSize;
	  unsigned int completedReadSize;
	  unsigned int offset;
	  unsigned char *p_startIn;
	  OVERLAPPED overlapped;
	  unsigned int readError;
	  db_z_stream_s stream;
	  unsigned int lookaheadReadSize;
	  unsigned int lookaheadOffset;
	  unsigned int lookaheadClearAvailIn;
	};

	struct XZoneInfo
	{
		const char* name;
		int allocFlags;
		int freeFlags;
	};

	enum EScreenLayer : int
	{
		SL_SYSTEM = 0x0,
		SL_HUD_BOB_NO_DISTORT = 0x1,
		SL_HUD_DISTORT = 0x2,
		SL_NUM_LAYERS = 0x3,
	};

enum XAssetType : __int32
{
  ASSET_TYPE_PHYSPRESET = 0x0,
  ASSET_TYPE_PHYSCOLLMAP = 0x1,
  ASSET_TYPE_XANIMPARTS = 0x2,
  ASSET_TYPE_XMODEL_SURFS = 0x3,
  ASSET_TYPE_XMODEL = 0x4,
  ASSET_TYPE_MATERIAL = 0x5,
  ASSET_TYPE_PIXELSHADER = 0x6,
  ASSET_TYPE_TECHNIQUE_SET = 0x7,
  ASSET_TYPE_IMAGE = 0x8,
  ASSET_TYPE_SOUND = 0x9,
  ASSET_TYPE_SND_VOLUME_FALLOFF_CURVE = 0xA,
  ASSET_TYPE_SND_LPF_CURVE = 0xB,
  ASSET_TYPE_LOADED_SOUND = 0xC,
  ASSET_TYPE_CLIPMAP_SP = 0xD,
  ASSET_TYPE_CLIPMAP_MP = 0xE,
  ASSET_TYPE_COMWORLD = 0xF,
  ASSET_TYPE_GAMEWORLD_SP = 0x10,
  ASSET_TYPE_GAMEWORLD_MP = 0x11,
  ASSET_TYPE_MAP_ENTS = 0x12,
  ASSET_TYPE_FXWORLD = 0x13,
  ASSET_TYPE_GFXWORLD = 0x14,
  ASSET_TYPE_LIGHT_DEF = 0x15,
  ASSET_TYPE_UI_MAP = 0x16,
  ASSET_TYPE_FONT = 0x17,
  ASSET_TYPE_MENULIST = 0x18,
  ASSET_TYPE_MENU = 0x19,
  ASSET_TYPE_LOCALIZE_ENTRY = 0x1A,
  ASSET_TYPE_WEAPON = 0x1B,
  ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1C,
  ASSET_TYPE_FX = 0x1D,
  ASSET_TYPE_IMPACT_FX = 0x1E,
  ASSET_TYPE_SURFACE_FX = 0x1F,
  ASSET_TYPE_AITYPE = 0x20,
  ASSET_TYPE_MPTYPE = 0x21,
  ASSET_TYPE_CHARACTER = 0x22,
  ASSET_TYPE_XMODELALIAS = 0x23,
  ASSET_TYPE_RAWFILE = 0x24,
  ASSET_TYPE_STRINGTABLE = 0x25,
  ASSET_TYPE_LEADERBOARD = 0x26,
  ASSET_TYPE_STRUCTURED_DATA_DEF = 0x27,
  ASSET_TYPE_TRACER = 0x28,
  ASSET_TYPE_LASER = 0x29,
  ASSET_TYPE_VEHICLE = 0x2A,
  ASSET_TYPE_ADDON_MAP_ENTS = 0x2B,
  ASSET_TYPE_SHOCKFILE = 0x2C,
  ASSET_TYPE_VOLUMESETTING = 0x2D,
  ASSET_TYPE_REVERBPRESET = 0x2E,
  ASSET_TYPE_FOG = 0x2F,
  ASSET_TYPE_COUNT = 0x30,
  ASSET_TYPE_STRING = 0x30,
  ASSET_TYPE_ASSETLIST = 0x31,
};
/*
struct Glyph
{
  unsigned __int16 letter;
  char x0;
  char y0;
  unsigned __int8 dx;
  unsigned __int8 pixelWidth;
  unsigned __int8 pixelHeight;
  float s0;
  float t0;
  float s1;
  float t1;
};
*/
/* 5318 */
struct Font_s
{
  //const char *fontName;
  //int pixelHeight;
  //int glyphCount;
  //Material *material;
  //Material *glowMaterial;
  //Glyph *glyphs;
};

union XAssetHeader
{/*
  PhysPreset *physPreset;
  PhysCollmap *physCollmap;
  XAnimParts *parts;
  XModelSurfs *modelSurfs;
  XModel *model;
  Material *material;
  MaterialPixelShader *pixelShader;
  MaterialVertexShader *vertexShader;
  MaterialVertexDeclaration *vertexDecl;
  MaterialTechniqueSet *techniqueSet;
  GfxImage *image;
  SndAliasList *sound;
  SndVfCurve *sndVfCurve;
  SndLpfCurve *sndLpfCurve;
  LoadedSound *loadSnd;
  clipMap_t *clipMap;
  ComWorld *comWorld;
  GameWorldSp *gameWorldSp;
  GameWorldMp *gameWorldMp;
  MapEnts *mapEnts;
  FxWorld *fxWorld;
  GfxWorld *gfxWorld;
  GfxLightDef *lightDef;
  Font_s *font;
  MenuList *menuList;
  menuDef_t *menu;*/
  //LocalizeEntry *localize;
  /*WeaponCompleteDef *weapon;
  SndDriverGlobals *sndDriverGlobals;
  const FxEffectDef *fx;
  FxImpactTable *impactFx;
  SurfaceFxTable *surfaceFx;
  RawFile *rawfile;
  StringTable *stringTable;
  LeaderboardDef *leaderboardDef;
  StructuredDataDefSet *structuredDataDefSet;
  TracerDef *tracerDef;
  LaserDef *laserDef;
  VehicleDef *vehDef;
  AddonMapEnts *addonMapEnts;
  ShellShockParams *shockParams;
  AudioVolumeSetting *audioVolumeSetting;
  RadVerbPreset *reverbPreset;
  FogDef *fogDef;*/
  void *data;
};
}
