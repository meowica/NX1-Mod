namespace Symbols
{
#ifdef MP_MOD
	namespace MP
	{
		Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x82437980);
		Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x82436918);

		Com_Printf_t Com_Printf = Com_Printf_t(0x82451A80);

		CL_ConsolePrint_t CL_ConsolePrint = CL_ConsolePrint_t(0x8229A338);
		Con_IsActive_t Con_IsActive = Con_IsActive_t(0x8229D670);
		Con_CheckResize_t Con_CheckResize = Con_CheckResize_t(0x82297850);
		Con_DrawSolidConsole_t Con_DrawSolidConsole = Con_DrawSolidConsole_t(0x8229F2C8);

		DevGui_IsActive_t DevGui_IsActive = DevGui_IsActive_t(0x82352E70);

		Key_IsCatcherActive_t Key_IsCatcherActive = Key_IsCatcherActive_t(0x822A87C0);

		R_AddCmdDrawText_t R_AddCmdDrawText = R_AddCmdDrawText_t(0x82803710);

		Structs::CmdArgs* cmd_args = (Structs::CmdArgs*)0x83A0C448;

		Structs::ScreenPlacement* scrPlaceFullUnsafe = (Structs::ScreenPlacement*)0x82B8DDA8;
	}
#elif SP_MOD
	namespace SP
	{
		Cmd_AddCommand_t Cmd_AddCommand = Cmd_AddCommand_t(0x824221C8);
		Cbuf_AddText_t Cbuf_AddText = Cbuf_AddText_t(0x82421160);

		Com_Printf_t Com_Printf = Com_Printf_t(0x82427A50);

		CL_ConsolePrint_t CL_ConsolePrint = CL_ConsolePrint_t(0x82209DB0);
		Con_IsActive_t Con_IsActive = Con_IsActive_t(0x8220CDB8);
		Con_CheckResize_t Con_CheckResize = Con_CheckResize_t(0x822072D0);
		Con_DrawSolidConsole_t Con_DrawSolidConsole = Con_DrawSolidConsole_t(0x8220E9D0);

		DevGui_IsActive_t DevGui_IsActive = DevGui_IsActive_t(0x8229CB50);

		Key_IsCatcherActive_t Key_IsCatcherActive = Key_IsCatcherActive_t(0x82217FB0);

		I_strncpyz_t I_strncpyz = I_strncpyz_t(0x826FCB00);
		I_stristr_t I_stristr = I_stristr_t(0x824ECB90);

		R_AddCmdDrawText_t R_AddCmdDrawText = R_AddCmdDrawText_t(0x826FCB00);

		Structs::CmdArgs* cmd_args = (Structs::CmdArgs*)0x83A76D48;

		Structs::ScreenPlacement* scrPlaceFull = (Structs::ScreenPlacement*)0x82B15C08;
	}
#endif
}
