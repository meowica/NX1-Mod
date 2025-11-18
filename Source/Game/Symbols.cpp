namespace Symbols
{
#ifdef IS_MP
	namespace MP
	{
		Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x82437980);
		Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x82436918);

		Com_Printf_t Com_Printf = Com_Printf_t(0x82451A80);
		Com_sprintf_t Com_sprintf = Com_sprintf_t(0x8256BA80);
		Com_GetBaseMapName_t Com_GetBaseMapName = Com_GetBaseMapName_t(0x8252F990);

		CL_ConsolePrint_t CL_ConsolePrint = CL_ConsolePrint_t(0x8229A338);
		Con_IsActive_t Con_IsActive = Con_IsActive_t(0x8229D670);
		Con_CheckResize_t Con_CheckResize = Con_CheckResize_t(0x82297850);
		Con_DrawSolidConsole_t Con_DrawSolidConsole = Con_DrawSolidConsole_t(0x8229F2C8);

		DB_EnumXAssets_Internal_t DB_EnumXAssets_Internal = DB_EnumXAssets_Internal_t(0x823368A8);
		DB_GetXAssetName_t DB_GetXAssetName = DB_GetXAssetName_t(0x822ECE18);
		DB_GetXAssetTypeName_t DB_GetXAssetTypeName = DB_GetXAssetTypeName_t(0x822ECF50);
		DB_GetXAssetTypeSize_t DB_GetXAssetTypeSize = DB_GetXAssetTypeSize_t(0x822ECEE0);
		DB_GetXAssetSizeHandler_t* DB_GetXAssetSizeHandlers = (DB_GetXAssetSizeHandler_t*)0x8297CD78;

		DevGui_IsActive_t DevGui_IsActive = DevGui_IsActive_t(0x82352E70);

		Dvar_FindVar_t Dvar_FindVar = Dvar_FindVar_t(0x82556958);

		Key_IsCatcherActive_t Key_IsCatcherActive = Key_IsCatcherActive_t(0x822A87C0);

		R_AddCmdDrawText_t R_AddCmdDrawText = R_AddCmdDrawText_t(0x82803710);

		I_strnicmp_t I_strnicmp = I_strnicmp_t(0x8256B110);

		Structs::CmdArgs* cmd_args = (Structs::CmdArgs*)0x83A0C448;

		const char** g_assetNames = (const char**)0x8297CB38;
		int* g_poolSize = (int*)0x8297CF10;
		void** DB_XAssetPool = (void**)0x8297D210;

		Structs::ScreenPlacement* scrPlaceFullUnsafe = (Structs::ScreenPlacement*)0x82B8DDA8;

		Structs::Font_s** fwSmallFont = (Structs::Font_s**)0x85ECBACC;
	}
#elif IS_SP
	namespace SP
	{
		Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x824221C8);
		Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x82421160);

		Com_Printf_t Com_Printf = Com_Printf_t(0x82427A50);

		CL_ConsolePrint_t CL_ConsolePrint = CL_ConsolePrint_t(0x82209DB0);
		Con_IsActive_t Con_IsActive = Con_IsActive_t(0x8220CDB8);
		Con_CheckResize_t Con_CheckResize = Con_CheckResize_t(0x822072D0);
		Con_DrawSolidConsole_t Con_DrawSolidConsole = Con_DrawSolidConsole_t(0x8220E9D0);

		DB_EnumXAssets_Internal_t DB_EnumXAssets_Internal = DB_EnumXAssets_Internal_t(0x82280540);
		DB_GetXAssetName_t DB_GetXAssetName = DB_GetXAssetName_t(0x82236B30);
		DB_GetXAssetTypeName_t DB_GetXAssetTypeName = DB_GetXAssetTypeName_t(0x82236C68);
		DB_GetXAssetTypeSize_t DB_GetXAssetTypeSize = DB_GetXAssetTypeSize_t(0x82236BF8);

		DevGui_IsActive_t DevGui_IsActive = DevGui_IsActive_t(0x8229CB50);

		Dvar_FindVar_t Dvar_FindVar = Dvar_FindVar_t(0x824D98C8);

		Key_IsCatcherActive_t Key_IsCatcherActive = Key_IsCatcherActive_t(0x82217FB0);

		R_AddCmdDrawText_t R_AddCmdDrawText = R_AddCmdDrawText_t(0x826FCB00);

		Structs::CmdArgs* cmd_args = (Structs::CmdArgs*)0x83A76D48;

		const char** g_assetNames = (const char**)0x8280AE60;
		int* g_poolSize = (int*)0x8280B230;

		Structs::ScreenPlacement* scrPlaceFull = (Structs::ScreenPlacement*)0x82B15C08;

		Structs::Font_s** fwSmallFont = (Structs::Font_s**)0x8423B21C;
	}
#endif
}
