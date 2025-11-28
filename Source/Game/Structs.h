#pragma once

namespace Structs
{
	union PackedUnitVec
	{
		unsigned int packed;
	};

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

	typedef struct dvar_s
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
		dvar_s* hashNext;
	} dvar_t;

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

	enum EScreenLayer
	{
		SL_SYSTEM,
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

	enum XAssetType
	{
		ASSET_TYPE_PHYSPRESET,
		ASSET_TYPE_PHYSCOLLMAP,
		ASSET_TYPE_XANIMPARTS,
		ASSET_TYPE_XMODEL_SURFS,
		ASSET_TYPE_XMODEL,
		ASSET_TYPE_MATERIAL,
		ASSET_TYPE_PIXELSHADER,
		ASSET_TYPE_TECHNIQUE_SET,
		ASSET_TYPE_IMAGE,
		ASSET_TYPE_SOUND,
		ASSET_TYPE_SND_VOLUME_FALLOFF_CURVE,
		ASSET_TYPE_SND_LPF_CURVE,
		ASSET_TYPE_LOADED_SOUND,
		ASSET_TYPE_CLIPMAP_SP,
		ASSET_TYPE_CLIPMAP_MP,
		ASSET_TYPE_COMWORLD,
		ASSET_TYPE_GAMEWORLD_SP,
		ASSET_TYPE_GAMEWORLD_MP,
		ASSET_TYPE_MAP_ENTS,
		ASSET_TYPE_FXWORLD,
		ASSET_TYPE_GFXWORLD,
		ASSET_TYPE_LIGHT_DEF,
		ASSET_TYPE_UI_MAP,
		ASSET_TYPE_FONT,
		ASSET_TYPE_MENULIST,
		ASSET_TYPE_MENU,
		ASSET_TYPE_LOCALIZE_ENTRY,
		ASSET_TYPE_WEAPON,
		ASSET_TYPE_SNDDRIVER_GLOBALS,
		ASSET_TYPE_FX,
		ASSET_TYPE_IMPACT_FX,
		ASSET_TYPE_SURFACE_FX,
		ASSET_TYPE_AITYPE,
		ASSET_TYPE_MPTYPE,
		ASSET_TYPE_CHARACTER,
		ASSET_TYPE_XMODELALIAS,
		ASSET_TYPE_RAWFILE,
		ASSET_TYPE_STRINGTABLE,
		ASSET_TYPE_LEADERBOARD,
		ASSET_TYPE_STRUCTURED_DATA_DEF,
		ASSET_TYPE_TRACER,
		ASSET_TYPE_LASER,
		ASSET_TYPE_VEHICLE,
		ASSET_TYPE_ADDON_MAP_ENTS,
		ASSET_TYPE_SHOCKFILE,
		ASSET_TYPE_VOLUMESETTING,
		ASSET_TYPE_REVERBPRESET,
		ASSET_TYPE_FOG,
		ASSET_TYPE_COUNT,
		ASSET_TYPE_STRING,
		ASSET_TYPE_ASSETLIST,
	};

	struct Font_s;

	union XAssetHeader
	{
		void* data;
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

	struct SessionStaticData
	{
		char* sessionName;
		bool registerUsersWithVoice;
		/*IXHV2Engine* voiceEngine;*/
	};

	enum IWNetServerSessionStatus
	{
		SESSION_ONCLIENTONLY,
		SESSION_BEINGCREATED,
		SESSION_CREATED,
		SESSION_BEINGDELETED,
	};

	struct IWNetServerInfoAboutPlayer
	{
		bool active;
		long long uid;
		unsigned char skill;
		unsigned char teamIndex;
		int mapPackFlags;
	};

	struct IWNetSessionStatus
	{
		IWNetServerSessionStatus status;
		int sessionId;
		int lastHeartbeatSent;
		bool needsUpdate;
		bool updatingPlayers;
		int newPlayerCount;
		IWNetServerInfoAboutPlayer pendingServerInfoForPlayers[18];
	};

	enum netadrtype_t
	{
		NA_BOT,
		NA_BAD,
		NA_LOOPBACK,
		NA_BROADCAST,
		NA_IP,
	};

	struct netadr_t
	{
		netadrtype_t type;
		unsigned char ip[4];
		unsigned short port;
	};

	struct ClientInfo
	{
		bool registered;
		bool voiceRegistered;
		unsigned long long xuid;
		int natType;
		netadr_t addr;
		int voiceConnectivityBits;
		int lastConnectivityTestTime;
		bool friends;
		bool muted;
		bool privateSlot;
	};

	struct LocalTalkerInfo
	{
		bool enabled;
	};

	struct RegisteredUser
	{
		bool active;
		unsigned long long xuid;
	};

	struct SessionDynamicData
	{
		HANDLE sessionHandle;
		int actualPublicSlots;
		IWNetSessionStatus iwnetServerSessionStatus;
		XSESSION_INFO sessionInfo;
		bool keysGenerated;
		bool sessionStartCalled;
		unsigned long long sessionNonce;
		int privateSlots;
		int publicSlots;
		int flags;
		bool qosListenEnabled;
		ClientInfo users[18];
		LocalTalkerInfo localTalkers[4];
		int voiceConnectivityBits;
		int sessionCreateController;
		int sessionDeleteTime;
		bool allowJoining;
		RegisteredUser internalRegisteredUsers[18];
	};

	struct SessionData
	{
		SessionStaticData staticData;
		SessionDynamicData dyn;
	};
}
