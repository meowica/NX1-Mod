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

	enum EScreenLayer : int
	{
		SL_SYSTEM = 0,
		SL_HUD_BOB_NO_DISTORT,
		SL_HUD_DISTORT,
		SL_NUM_LAYERS,
	};

	enum consoleChannel_e : int
	{
		CON_CHANNEL_DONT_FILTER = 0,
		CON_CHANNEL_ERROR,
		CON_CHANNEL_GAMENOTIFY,
		CON_CHANNEL_BOLDGAME,
		CON_CHANNEL_SUBTITLE,
		CON_CHANNEL_OBITUARY ,
		CON_CHANNEL_LOGFILEONLY,
		CON_CHANNEL_CONSOLEONLY,
		CON_CHANNEL_GFX,
		CON_CHANNEL_SOUND,
		CON_CHANNEL_FILES,
		CON_CHANNEL_DEVGUI,
		CON_CHANNEL_PROFILE,
		CON_CHANNEL_UI,
		CON_CHANNEL_CLIENT,
		CON_CHANNEL_SERVER,
		CON_CHANNEL_SYSTEM,
		CON_CHANNEL_PLAYERWEAP,
		CON_CHANNEL_AI,
		CON_CHANNEL_ANIM,
		CON_CHANNEL_PHYS,
		CON_CHANNEL_FX,
		CON_CHANNEL_LEADERBOARDS,
		CON_CHANNEL_PARSERSCRIPT,
		CON_CHANNEL_SCRIPT,
		CON_CHANNEL_NETWORK,
		CON_CHANNEL_VERBOSE,
		CON_CHANNEL_DEMO,

		CON_BUILTIN_CHANNEL_COUNT,
	};

	enum XAssetType : int
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
		ASSET_TYPE_UI_MAP = 0x16, // never ever used
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

	struct Font_s; // forced against my will

	union XAssetHeader
	{
		void *data;
	}; // incomplete

	struct XAsset
	{
		XAssetType type;
		XAssetHeader header;
	};

	struct GfxConfiguration
	{
		bool inited;
		unsigned int maxClientViews;
		unsigned int maxClientRenderViews;
		unsigned int entCount;
		unsigned int entnumNone;
		unsigned int entnumOrdinaryEnd;
		int threadContextCount;
		int critSectCount;
		bool defaultFullscreen;
		unsigned short defaultFullscreenFlags;
		int defaultMode;
		unsigned int textureMinVRamTier1;
		unsigned int textureMinVRamTier2;
	};
}
