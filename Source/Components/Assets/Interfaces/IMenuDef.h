#pragma once

#include "ISndAliasList.h"
#include "IMaterial.h"

namespace IMenuDef
{
	enum operationEnum : int
	{
		OP_NOOP = 0x0,
		OP_RIGHTPAREN = 0x1,
		OP_MULTIPLY = 0x2,
		OP_DIVIDE = 0x3,
		OP_MODULUS = 0x4,
		OP_ADD = 0x5,
		OP_SUBTRACT = 0x6,
		OP_NOT = 0x7,
		OP_LESSTHAN = 0x8,
		OP_LESSTHANEQUALTO = 0x9,
		OP_GREATERTHAN = 0xA,
		OP_GREATERTHANEQUALTO = 0xB,
		OP_EQUALS = 0xC,
		OP_NOTEQUAL = 0xD,
		OP_AND = 0xE,
		OP_OR = 0xF,
		OP_LEFTPAREN = 0x10,
		OP_COMMA = 0x11,
		OP_BITWISEAND = 0x12,
		OP_BITWISEOR = 0x13,
		OP_BITWISENOT = 0x14,
		OP_BITSHIFTLEFT = 0x15,
		OP_BITSHIFTRIGHT = 0x16,
		OP_STATICDVARINT = 0x17,
		OP_FIRSTFUNCTIONCALL = 0x17,
		OP_STATICDVARBOOL = 0x18,
		OP_STATICDVARFLOAT = 0x19,
		OP_STATICDVARSTRING = 0x1A,
		OP_TOINT = 0x1B,
		OP_TOSTRING = 0x1C,
		OP_TOFLOAT = 0x1D,
		LAST_COMMONLY_CALLED_FUNCTION = 0x1D,
		OP_SIN = 0x1E,
		OP_COS = 0x1F,
		OP_MIN = 0x20,
		OP_MAX = 0x21,
		OP_MILLISECONDS = 0x22,
		OP_DVARINT = 0x23,
		OP_DVARBOOL = 0x24,
		OP_DVARFLOAT = 0x25,
		OP_DVARSTRING = 0x26,
		OP_STAT = 0x27,
		OP_UIACTIVE = 0x28,
		OP_FLASHBANGED = 0x29,
		OP_USINGVEHICLE = 0x2A,
		OP_MISSILECAM = 0x2B,
		OP_SCOPED = 0x2C,
		OP_SCOPEDTHERMAL = 0x2D,
		OP_SCOREBOARDVISIBLE = 0x2E,
		OP_INKILLCAM = 0x2F,
		OP_INKILLCAM_NPC = 0x30,
		OP_PLAYERFIELD = 0x31,
		OP_GET_PLAYER_PERK = 0x32,
		OP_SELECTINGLOCATION = 0x33,
		OP_SELECTINGDIRECTION = 0x34,
		OP_SELECTINGUGVLOCATION = 0x35,
		OP_TEAMFIELD = 0x36,
		OP_OTHERTEAMFIELD = 0x37,
		OP_MARINESFIELD = 0x38,
		OP_OPFORFIELD = 0x39,
		OP_MENUISOPEN = 0x3A,
		OP_WRITINGDATA = 0x3B,
		OP_INLOBBY = 0x3C,
		OP_INPRIVATEPARTY = 0x3D,
		OP_PRIVATEPARTYHOST = 0x3E,
		OP_PRIVATEPARTYHOSTINLOBBY = 0x3F,
		OP_ALONEINPARTY = 0x40,
		OP_ADSJAVELIN = 0x41,
		OP_WEAPLOCKBLINK = 0x42,
		OP_WEAPATTACKTOP = 0x43,
		OP_WEAPATTACKDIRECT = 0x44,
		OP_WEAPLOCKING = 0x45,
		OP_WEAPLOCKED = 0x46,
		OP_WEAPLOCKTOOCLOSE = 0x47,
		OP_WEAPLOCKSCREENPOSX = 0x48,
		OP_WEAPLOCKSCREENPOSY = 0x49,
		OP_SECONDSASTIME = 0x4A,
		OP_TABLELOOKUP = 0x4B,
		OP_TABLELOOKUPBYROW = 0x4C,
		OP_TABLEGETROWNUM = 0x4D,
		OP_LOCALIZESTRING = 0x4E,
		OP_LOCALVARINT = 0x4F,
		OP_LOCALVARBOOL = 0x50,
		OP_LOCALVARFLOAT = 0x51,
		OP_LOCALVARSTRING = 0x52,
		OP_TIMELEFT = 0x53,
		OP_SECONDSASCOUNTDOWN = 0x54,
		OP_GAMEMSGWNDACTIVE = 0x55,
		OP_GAMETYPENAME = 0x56,
		OP_GAMETYPE = 0x57,
		OP_GAMETYPEDESCRIPTION = 0x58,
		OP_ISPARTYREADY = 0x59,
		OP_ARECURRENTANDPREVIOUSMAPENTRYAVAILABLE = 0x5A,
		OP_CURRENTGAMETYPE = 0x5B,
		OP_CURRENTMAPNAME = 0x5C,
		OP_PREVIOUSGAMETYPE = 0x5D,
		OP_PREVIOUSMAPNAME = 0x5E,
		OP_SCORE = 0x5F,
		OP_FRIENDSONLINE = 0x60,
		OP_FOLLOWING = 0x61,
		OP_SPECTATINGFREE = 0x62,
		OP_STATRANGEBITSSET = 0x63,
		OP_KEYBINDING = 0x64,
		OP_ACTIONSLOTUSABLE = 0x65,
		OP_HUDFADE = 0x66,
		OP_HUDDETAILFADE = 0x67,
		OP_MAXPLAYERS = 0x68,
		OP_ACCEPTINGINVITE = 0x69,
		OP_ISINTERMISSION = 0x6A,
		OP_GAMEHOST = 0x6B,
		OP_PARTYHASMISSINGMAPPACK = 0x6C,
		OP_PARTYMISSINGMAPPACKERROR = 0x6D,
		OP_ANYNEWMAPPACKS = 0x6E,
		OP_AMISELECTED = 0x6F,
		OP_PARTYSTATUSSTRING = 0x70,
		OP_ATTACHED_CONTROLLER_COUNT = 0x71,
		OP_IS_SPLIT_SCREEN_ONLINE_POSSIBLE = 0x72,
		OP_SPLITSCREENPLAYERCOUNT = 0x73,
		OP_GETPLAYERDATA = 0x74,
		OP_GETPLAYERDATASPLITSCREEN = 0x75,
		OP_EXPERIENCE_FOR_LEVEL = 0x76,
		OP_LEVEL_FOR_EXPERIENCE = 0x77,
		OP_IS_ITEM_UNLOCKED = 0x78,
		OP_IS_ITEM_UNLOCKEDSPLITSCREEN = 0x79,
		OP_DEBUG_PRINT = 0x7A,
		OP_GETPLAYERDATA_ANYBOOLTRUE = 0x7B,
		OP_WEAPON_CLASS_NEW = 0x7C,
		OP_WEAPONNAME = 0x7D,
		OP_ISRELOADING = 0x7E,
		OP_SAVE_GAME_AVAILABLE = 0x7F,
		OP_UNLOCKED_ITEM_COUNT = 0x80,
		OP_UNLOCKED_ITEM_COUNT_SPLITSCREEN = 0x81,
		OP_UNLOCKED_ITEM = 0x82,
		OP_UNLOCKED_ITEM_SPLITSCREEN = 0x83,
		OP_MAIL_SUBJECT = 0x84,
		OP_MAIL_FROM = 0x85,
		OP_MAIL_RECEIVED = 0x86,
		OP_MAIL_BODY = 0x87,
		OP_MAIL_LOOT_LOCALIZED = 0x88,
		OP_MAIL_GIVES_LOOT = 0x89,
		OP_ANY_NEW_MAIL = 0x8A,
		OP_MAIL_TIME_TO_FOLLOWUP = 0x8B,
		OP_MAIL_LOOT_TYPE = 0x8C,
		OP_MAIL_RAN_LOTTERY = 0x8D,
		OP_LOTTERY_LOOT_LOCALIZED = 0x8E,
		OP_RADAR_IS_JAMMED = 0x8F,
		OP_RADAR_JAM_INTENSITY = 0x90,
		OP_RADAR_IS_ENABLED = 0x91,
		OP_EMP_JAMMED = 0x92,
		OP_PLAYERADS = 0x93,
		OP_WEAPON_ZOOM = 0x94,
		OP_WEAPON_HEAT_ACTIVE = 0x95,
		OP_WEAPON_HEAT_VALUE = 0x96,
		OP_WEAPON_HEAT_OVERHEATED = 0x97,
		OP_SPLASH_TEXT = 0x98,
		OP_SPLASH_DESCRIPTION = 0x99,
		OP_SPLASH_MATERIAL = 0x9A,
		OP_SPLASH_HAS_ICON = 0x9B,
		OP_SPLASH_ROWNUM = 0x9C,
		OP_GETFOCUSED_NAME = 0x9D,
		OP_GETFOCUSED_X = 0x9E,
		OP_GETFOCUSED_Y = 0x9F,
		OP_GETFOCUSED_W = 0xA0,
		OP_GETFOCUSED_H = 0xA1,
		OP_GETITEMDEF_X = 0xA2,
		OP_GETITEMDEF_Y = 0xA3,
		OP_GETITEMDEF_W = 0xA4,
		OP_GETITEMDEF_H = 0xA5,
		OP_PLAYLISTFIELD = 0xA6,
		OP_SCOREBOARD_EXTERNALMUTE_NOTICE = 0xA7,
		OP_CLIENT_MATCH_DATA = 0xA8,
		OP_CLIENT_MATCH_DATA_DEF = 0xA9,
		OP_GET_MAP_NAME = 0xAA,
		OP_GET_MAP_IMAGE = 0xAB,
		OP_GET_MAP_CUSTOM = 0xAC,
		OP_GET_MIGRATION_STATUS = 0xAD,
		OP_GET_PLAYERCARD_INFO = 0xAE,
		OP_IS_OFFLINE_PROFILE_SELECTED = 0xAF,
		OP_COOP_PLAYERFIELD = 0xB0,
		OP_IS_COOP = 0xB1,
		OP_GETPARTYSTATUS = 0xB2,
		OP_GETSEARCHPARAMS = 0xB3,
		OP_GETTIMEPLAYED = 0xB4,
		OP_IS_SELECTED_PLAYER_FRIEND = 0xB5,
		OP_GETCHARBYINDEX = 0xB6,
		OP_GETPLAYERPROFILEDATA = 0xB7,
		OP_IS_PROFILE_SIGNED_IN = 0xB8,
		OP_GET_WAIT_POPUP_STATUS = 0xB9,
		OP_GETNATTYPE = 0xBA,
		OP_GETLOCALIZEDNATTYPE = 0xBB,
		OP_GET_ADJUSTED_SAFEAREA_HORIZONTAL = 0xBC,
		OP_GET_ADJUSTED_SAFEAREA_VERTICAL = 0xBD,
		OP_CONNECTION_INFO = 0xBE,
		OP_OFFLINE_PROFILE_CAN_SAVE = 0xBF,
		OP_ALL_SPLITSCREEN_PROFILES_CAN_SAVE = 0xC0,
		OP_ALL_SPLITSCREEN_PROFILES_ARE_SIGNED_IN = 0xC1,
		OP_COOP_READY = 0xC2,
		OP_IS_DEVICE_SELECTED = 0xC3,
		OP_SUIT_SHIELD_ENABLED = 0xC4,
		OP_SUIT_SHIELD_HEALTH = 0xC5,
		OP_SUIT_SHIELD_HEALTH_METER_INTERPOLATE_CHAN = 0xC6,
		OP_DEVELOPER = 0xC7,
		NUM_OPERATORS = 0xC8,
	};

	enum expDataType
	{
		VAL_INT,
		VAL_FLOAT,
		VAL_STRING,
		NUM_INTERNAL_DATATYPES3,
		VAL_FUNCTION,
		NUM_DATATYPES,
	};

	struct ExpressionString
	{
		const char* string;
	};

	struct Statement_s;

	union operandInternalDataUnion
	{
		int intVal;
		float floatVal;
		ExpressionString stringVal;
		Statement_s* function;
	};

	struct Operand
	{
		expDataType dataType;
		operandInternalDataUnion internals;
	};

	union entryInternalData
	{
		operationEnum op;
		Operand operand;
	};

	struct expressionEntry
	{
		int type;
		entryInternalData data;
	};

	struct ExpressionSupportingData;

	struct Statement_s
	{
		int numEntries;
		expressionEntry *entries;
		ExpressionSupportingData *supportingData;
		int lastExecuteTime;
		Operand lastResult;
	};

	struct MenuEventHandlerSet;

	struct ConditionalScript
	{
		MenuEventHandlerSet *eventHandlerSet;
		Statement_s *eventExpression;
	};

	struct MenuEventHandlerSet;

	struct SetLocalVarData
	{
		const char* localVarName;
		Statement_s* expression;
	};

	union EventData
	{
		const char* unconditionalScript;
		ConditionalScript* conditionalScript;
		MenuEventHandlerSet* elseScript;
		SetLocalVarData* setLocalVarData;
	};

	struct MenuEventHandler
	{
		EventData eventData;
		unsigned char eventType;
	};

	struct MenuEventHandlerSet
	{
		int eventHandlerCount;
		MenuEventHandler** eventHandlers;
	};

	struct ItemKeyHandler
	{
		int key;
		MenuEventHandlerSet* action;
		ItemKeyHandler* next;
	};

	struct menuTransition
	{
		int transitionType;
		int startTime;
		float startVal;
		float endVal;
		float time;
		int endTriggerType;
	};

	struct UIFunctionList
	{
		int totalFunctions;
		Statement_s** functions;
	};

	struct StaticDvar
	{
		const Structs::dvar_t* dvar;
		char* dvarName;
	};

	struct StaticDvarList
	{
		int numStaticDvars;
		StaticDvar** staticDvars;
	};

	struct StringList
	{
		int totalStrings;
		const char** strings;
	};

	struct ExpressionSupportingData
	{
		UIFunctionList uifunctions;
		StaticDvarList staticDvarList;
		StringList uiStrings;
	};

	struct menuData_t
	{
		unsigned int menuFlags;
		int fadeCycle;
		float fadeClamp;
		float fadeAmount;
		float fadeInAmount;
		float blurRadius;
		Structs::EScreenLayer screenLayer;
		MenuEventHandlerSet* onOpen;
		MenuEventHandlerSet* onCloseRequest;
		MenuEventHandlerSet* onClose;
		MenuEventHandlerSet* onESC;
		ItemKeyHandler* onKey;
		Statement_s* visibleExp;
		const char* allowedBinding;
		const char* soundName;
		float focusColor[4];
		Statement_s* rectXExp;
		Statement_s* rectYExp;
		Statement_s* rectWExp;
		Statement_s* rectHExp;
		Statement_s* openSoundExp;
		Statement_s* closeSoundExp;
		int cursorItem[4];
		menuTransition scaleTransition[4];
		menuTransition alphaTransition[4];
		menuTransition xTransition[4];
		menuTransition yTransition[4];
		ExpressionSupportingData* expressionData;
	};

	struct rectDef_s
	{
		float x;
		float y;
		float w;
		float h;
		unsigned char horzAlign;
		unsigned char vertAlign;
	};

	struct windowDef_t
	{
		const char* name;
		rectDef_s rect;
		rectDef_s rectClient;
		const char* group;
		int style;
		int border;
		int ownerDraw;
		int ownerDrawFlags;
		float borderSize;
		int staticFlags;
		int dynamicFlags[4];
		int nextTime;
		float foreColor[4];
		float backColor[4];
		float borderColor[4];
		float outlineColor[4];
		float disableColor[4];
		IMaterial::Material* background;
	};

	struct menuDef_t;

	struct columnInfo_s
	{
		int pos;
		int width;
		int maxChars;
		int alignment;
	};

	struct listBoxDef_s
	{
		int startPos[4];
		int endPos[4];
		int drawPadding;
		float elementWidth;
		float elementHeight;
		int elementStyle;
		int numColumns;
		columnInfo_s columnInfo[16];
		MenuEventHandlerSet* onDoubleClick;
		int notselectable;
		int noScrollBars;
		int usePaging;
		float selectBorder[4];
		IMaterial::Material* selectIcon;
	};

	struct editFieldDef_s
	{
		float minVal;
		float maxVal;
		float defVal;
		float range;
		int maxChars;
		int maxCharsGotoNext;
		int maxPaintChars;
		int paintOffset;
	};

	struct multiDef_s
	{
		const char* dvarList[32];
		const char* dvarStr[32];
		float dvarValue[32];
		int count;
		int strDef;
	};

	struct newsTickerDef_s
	{
		int feedId;
		int speed;
		int spacing;
		int lastTime;
		int start;
		int end;
		float x;
	};

	struct textScrollDef_s
	{
		int startTime;
	};

	union itemDefData_t
	{
		listBoxDef_s* listBox;
		editFieldDef_s* editField;
		multiDef_s* multi;
		const char* enumDvarName;
		newsTickerDef_s* ticker;
		textScrollDef_s* scroll;
		void* data;
	};

	struct ItemFloatExpression
	{
		int target;
		Statement_s* expression;
	};

	struct animParamsDef_t
	{
		const char* name;
		rectDef_s rectClient;
		float borderSize;
		float foreColor[4];
		float backColor[4];
		float borderColor[4];
		float outlineColor[4];
		float textscale;
		float glowColor[4];
		MenuEventHandlerSet* onEnter;
	};

	struct itemDef_s
	{
		windowDef_t window;
		rectDef_s textRect[4];
		int type;
		int dataType;
		int alignment;
		int fontEnum;
		int textAlignMode;
		float textalignx;
		float textaligny;
		float textscale;
		int textStyle;
		int gameMsgWindowIndex;
		int gameMsgWindowMode;
		const char* text;
		unsigned int itemFlags;
		menuDef_t* parent;
		MenuEventHandlerSet *mouseEnterText;
		MenuEventHandlerSet *mouseExitText;
		MenuEventHandlerSet *mouseEnter;
		MenuEventHandlerSet *mouseExit;
		MenuEventHandlerSet *action;
		MenuEventHandlerSet *accept;
		MenuEventHandlerSet *onFocus;
		MenuEventHandlerSet *leaveFocus;
		MenuEventHandlerSet *onEnter;
		const char *dvar;
		const char *dvarTest;
		ItemKeyHandler *onKey;
		const char *enableDvar;
		const char *localVar;
		int dvarFlags;
		ISndAliasList::SndAliasList* focusSound;
		float special;
		int cursorPos[4];
		itemDefData_t typeData;
		int floatExpressionCount;
		ItemFloatExpression* floatExpressions;
		Statement_s* visibleExp;
		Statement_s* disabledExp;
		Statement_s* textExp;
		Statement_s* materialExp;
		Structs::EScreenLayer screenLayer;
		float glowColor[4];
		int fxBirthTime;
		int fxLetterTime;
		int fxDecayStartTime;
		int fxDecayDuration;
		int lastSoundPlayedTime;
		int animStateCount;
		animParamsDef_t** animStates;
		animParamsDef_t currentAnimState;
		animParamsDef_t* nextAnimState;
		int animStartTime;
		int animDuration;
	};

	struct menuDef_t
	{
		menuData_t* data;
		windowDef_t window;
		int itemCount;
		itemDef_s** items;
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
