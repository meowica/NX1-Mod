#pragma once

namespace Symbols
{
#ifdef IS_MP
	namespace MP
	{
		typedef void (*Cmd_AddCommand_t)(const char* cmdName, void (__cdecl* function)(),
			Structs::cmd_function_s* allocedCmd);
		extern Cmd_AddCommand_t Cmd_AddCommand;

		typedef void (*Cbuf_AddText_t)(int localClientNum, const char* text);
		extern Cbuf_AddText_t Cbuf_AddText;

		typedef void (*Com_Printf_t)(int channel, const char* fmt, ...);
		extern Com_Printf_t Com_Printf;

		typedef void (*CL_ConsolePrint_t)(int localClientNum, int channel, const char* txt,
			int duration, int pixelWidth, int flags);
		extern CL_ConsolePrint_t CL_ConsolePrint;

		typedef BOOL (*Con_IsActive_t)(int localClientNum);
		extern Con_IsActive_t Con_IsActive;

		typedef void (*Con_CheckResize_t)(const Structs::ScreenPlacement* scrPlace);
		extern Con_CheckResize_t Con_CheckResize;

		typedef void (*Con_DrawSolidConsole_t)(int localClientNum);
		extern Con_DrawSolidConsole_t Con_DrawSolidConsole;

		typedef void (*DB_EnumXAssets_Internal_t)(Structs::XAssetType type,
			void(__cdecl* func)(Structs::XAssetHeader, void*),
			const void* inData, bool includeOverride);
		extern DB_EnumXAssets_Internal_t DB_EnumXAssets_Internal;

		typedef const char* (*DB_GetXAssetName_t)(const Structs::XAsset* asset);
		extern DB_GetXAssetName_t DB_GetXAssetName;

		typedef const char* (*DB_GetXAssetTypeName_t)(unsigned int type);
		extern DB_GetXAssetTypeName_t DB_GetXAssetTypeName;

		typedef int (*DB_GetXAssetTypeSize_t)(int type);
		extern DB_GetXAssetTypeSize_t DB_GetXAssetTypeSize;

		typedef int (*DB_GetXAssetSizeHandler_t)();
		extern DB_GetXAssetSizeHandler_t* DB_GetXAssetSizeHandlers;

		typedef BOOL (*DevGui_IsActive_t)();
		extern DevGui_IsActive_t DevGui_IsActive;

		typedef const Structs::dvar_t* (*Dvar_FindVar_t)(const char* dvarName);
		extern Dvar_FindVar_t Dvar_FindVar;

		typedef BOOL (*Key_IsCatcherActive_t)(int localClientNum, int mask);
		extern Key_IsCatcherActive_t Key_IsCatcherActive;

		typedef void (*R_AddCmdDrawText_t)(const char* text, int maxChars,
			Structs::Font_s* font, float x, float y, float xScale, float yScale,
			float rotation, const float* colour, int style, Structs::EScreenLayer layer);
		extern R_AddCmdDrawText_t R_AddCmdDrawText;

		extern Structs::CmdArgs* cmd_args;

		extern const char** g_assetNames;
		extern int* g_poolSize;
		extern void** DB_XAssetPool;
		extern Structs::ScreenPlacement* scrPlaceFullUnsafe;

		extern Structs::Font_s** fwSmallFont;
	}
#elif IS_SP
	namespace SP
	{
		typedef void (*Cmd_AddCommand_t)(const char* cmdName, void (__cdecl* function)(),
			Structs::cmd_function_s* allocedCmd);
		extern Cmd_AddCommand_t Cmd_AddCommand;

		typedef void (*Cbuf_AddText_t)(int localClientNum, const char* text);
		extern Cbuf_AddText_t Cbuf_AddText;

		typedef void (*Com_Printf_t)(int channel, const char* fmt, ...);
		extern Com_Printf_t Com_Printf;

		typedef void (*CL_ConsolePrint_t)(int localClientNum, int channel, const char* txt,
			int duration, int pixelWidth, int flags);
		extern CL_ConsolePrint_t CL_ConsolePrint;

		typedef BOOL (*Con_IsActive_t)(int localClientNum);
		extern Con_IsActive_t Con_IsActive;

		typedef void (*Con_CheckResize_t)(const Structs::ScreenPlacement* scrPlace);
		extern Con_CheckResize_t Con_CheckResize;

		typedef void (*Con_DrawSolidConsole_t)(int localClientNum);
		extern Con_DrawSolidConsole_t Con_DrawSolidConsole;

		typedef void (*DB_EnumXAssets_Internal_t)(Structs::XAssetType type,
			void(__cdecl* func)(Structs::XAssetHeader, void*),
			const void* inData, bool includeOverride);
		extern DB_EnumXAssets_Internal_t DB_EnumXAssets_Internal;

		typedef const char* (*DB_GetXAssetName_t)(const Structs::XAsset* asset);
		extern DB_GetXAssetName_t DB_GetXAssetName;

		typedef const char* (*DB_GetXAssetTypeName_t)(unsigned int type);
		extern DB_GetXAssetTypeName_t DB_GetXAssetTypeName;

		typedef int (*DB_GetXAssetTypeSize_t)(int type);
		extern DB_GetXAssetTypeSize_t DB_GetXAssetTypeSize;

		typedef BOOL (*DevGui_IsActive_t)();
		extern DevGui_IsActive_t DevGui_IsActive;

		typedef const Structs::dvar_t* (*Dvar_FindVar_t)(const char* dvarName);
		extern Dvar_FindVar_t Dvar_FindVar;

		typedef BOOL (*Key_IsCatcherActive_t)(int localClientNum, int mask);
		extern Key_IsCatcherActive_t Key_IsCatcherActive;

		typedef void (*R_AddCmdDrawText_t)(const char* text, int maxChars,
			Structs::Font_s* font, float x, float y, float xScale, float yScale,
			float rotation, const float* colour, int style, Structs::EScreenLayer layer);
		extern R_AddCmdDrawText_t R_AddCmdDrawText;

		extern Structs::CmdArgs* cmd_args;

		extern const char** g_assetNames;
		extern int* g_poolSize;

		extern Structs::ScreenPlacement* scrPlaceFull;

		extern Structs::Font_s** fwSmallFont;
	}
#endif
}
