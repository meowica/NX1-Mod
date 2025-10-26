#include "../../Util/FPS.h"

namespace Drawing
{
#ifdef MP_MOD	
	namespace MP
	{
		Structs::Font_s** Font;

		Util::Hook::Detour DevGui_GetScreenXPad_Hook;
		int DevGui_GetScreenXPad()
		{
			return 0;
		}

		Util::Hook::Detour DevGui_GetScreenYPad_Hook;
		int DevGui_GetScreenYPad()
		{
			return 0;
		}

		Util::Hook::Detour Con_DrawConsole_Hook;
		void Con_DrawConsole(int localClientNum)
		{
			Symbols::MP::Con_CheckResize(Symbols::MP::scrPlaceFullUnsafe);
			if (Symbols::MP::Key_IsCatcherActive(localClientNum, KEYCATCH_CONSOLE))
			{
				Symbols::MP::Con_DrawSolidConsole(localClientNum);
			}
		}

		void DrawWatermark()
		{
			if (!*Font)
				return;
			if (Symbols::MP::Con_IsActive(0))
				return;
			if (Symbols::MP::DevGui_IsActive())
				return;

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::MP::R_AddCmdDrawText("NX1-Mod MP", MAX_CHARS, *Font, 2.0f, 20.0f, 0.8f, 0.8f, 0.0f, colour, 3, Structs::SL_SYSTEM);
		}

		Util::FPS g_fps;

		void DrawFPS()
		{
			if (!*Font)
				return;
			if (Symbols::MP::Con_IsActive(0))
				return;

			g_fps.Update();

			float colourGood[4] = { 0.6f, 1.0f, 0.0f, 1.0f };
			float colourOkay[4] = { 1.0f, 0.7f, 0.3f, 1.0f };
			float colourBad[4]  = { 1.0f, 0.3f, 0.3f, 1.0f };

			float fpsValue = g_fps.GetFPS();
			int count = static_cast<int>(fpsValue + 0.5f);

			float* colour = (count >= 60) ? colourGood :
							(count >= 50) ? colourOkay : colourBad;

			char text[16];
			_snprintf(text, sizeof(text), "%d", count);
			text[sizeof(text) - 1] = '\0'; // ensure null-termination

			float x = (count <= 99) ? 1255.0f : 1245.0f;

			Symbols::MP::R_AddCmdDrawText(text, MAX_CHARS, *Font, x, 20.0f, 1.0f, 1.0f, 0.0f, colour, 3, Structs::SL_SYSTEM);
		}

		Util::Hook::Detour CL_DrawScreen_Hook;
		void CL_DrawScreen()
		{
			DrawWatermark();
			DrawFPS();

			auto Invoke = CL_DrawScreen_Hook.Invoke<void(*)()>();
			Invoke();
		}

		void Hooks()
		{
			Font = (Structs::Font_s**)0x85ECBACC; // fonts/fwsmallfont

			// change the safe area to match pc
			DevGui_GetScreenXPad_Hook.Create(0x82353A68, DevGui_GetScreenXPad);
			DevGui_GetScreenYPad_Hook.Create(0x82353AD0, DevGui_GetScreenYPad);

			// change the safe area to match pc
			Con_DrawConsole_Hook.Create(0x8229F388, Con_DrawConsole);

			// draw our watermark and fps counter
			CL_DrawScreen_Hook.Create(0x822BD290, CL_DrawScreen);

			// disable some unneeded drawing
			Util::Hook::SetValue(0x822BD2E8, 0x60000000); // CG_DrawVersion
			Util::Hook::SetValue(0x82510438, 0x60000000); // UI_DrawBuildNumber
			Util::Hook::SetValue(0x8229D414, 0x60000000); // Con_DrawOutputVersion

			// change output box size
			Util::Hook::SetValue(0x82013E14, 36.0f);

			// change console font
			Util::Hook::SetString(0x8203259C, "fonts/fwsmallfont");
		}

		void ClearHooks()
		{
			DevGui_GetScreenXPad_Hook.Clear();
			DevGui_GetScreenYPad_Hook.Clear();
			Con_DrawConsole_Hook.Clear();
			CL_DrawScreen_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif

#ifdef SP_MOD
	namespace SP
	{
		Structs::Font_s** Font;

		Util::Hook::Detour DevGui_GetScreenXPad_Hook;
		int DevGui_GetScreenXPad()
		{
			return 0;
		}

		Util::Hook::Detour DevGui_GetScreenYPad_Hook;
		int DevGui_GetScreenYPad()
		{
			return 0;
		}

		Util::Hook::Detour Con_DrawConsole_Hook;
		void Con_DrawConsole(int localClientNum)
		{
			Symbols::SP::Con_CheckResize(Symbols::SP::scrPlaceFull);
			if (Symbols::SP::Key_IsCatcherActive(localClientNum, KEYCATCH_CONSOLE))
			{
				Symbols::SP::Con_DrawSolidConsole(localClientNum);
			}
		}

		void DrawWatermark()
		{
			if (!*Font)
				return;
			if (Symbols::SP::Con_IsActive(0))
				return;
			if (Symbols::SP::DevGui_IsActive())
				return;

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::SP::R_AddCmdDrawText("NX1-Mod SP", MAX_CHARS, *Font, 2.0f, 20.0f, 0.8f, 0.8f, 0.0f, colour, 3, Structs::SL_SYSTEM);
		}

		Util::FPS g_fps;

		void DrawFPS()
		{
			if (!*Font)
				return;
			if (Symbols::SP::Con_IsActive(0))
				return;

			g_fps.Update();

			float colourGood[4] = { 0.6f, 1.0f, 0.0f, 1.0f };
			float colourOkay[4] = { 1.0f, 0.7f, 0.3f, 1.0f };
			float colourBad[4]  = { 1.0f, 0.3f, 0.3f, 1.0f };

			float fpsValue = g_fps.GetFPS();
			int count = static_cast<int>(fpsValue + 0.5f);

			float* colour = (count >= 60) ? colourGood :
							(count >= 50) ? colourOkay : colourBad;

			char text[16];
			_snprintf(text, sizeof(text), "%d", count);
			text[sizeof(text) - 1] = '\0'; // ensure null-termination

			float x = (count <= 99) ? 1255.0f : 1245.0f;

			Symbols::SP::R_AddCmdDrawText(text, MAX_CHARS, *Font, x, 20.0f, 1.0f, 1.0f, 0.0f, colour, 3, Structs::SL_SYSTEM);
		}

		Util::Hook::Detour CL_DrawScreen_Hook;
		void CL_DrawScreen()
		{
			DrawWatermark();
			DrawFPS();

			auto Invoke = CL_DrawScreen_Hook.Invoke<void(*)()>();
			Invoke();
		}

		void Hooks()
		{
			Font = (Structs::Font_s**)0x8423B21C; // fonts/fwsmallfont

			// change the safe area to match pc
			DevGui_GetScreenXPad_Hook.Create(0x8229D748, DevGui_GetScreenXPad);
			DevGui_GetScreenYPad_Hook.Create(0x8229D7B0, DevGui_GetScreenYPad);

			// change the safe area to match pc
			Con_DrawConsole_Hook.Create(0x8220EA90, Con_DrawConsole);

			// draw our watermark and fps counter
			CL_DrawScreen_Hook.Create(0x8221F858, CL_DrawScreen);

			// disable some unneeded drawing
			Util::Hook::SetValue(0x8221F894, 0x60000000); // CG_DrawVersion
			Util::Hook::SetValue(0x824A6F3C, 0x60000000); // UI_DrawBuildNumber
			Util::Hook::SetValue(0x8220CB80, 0x60000000); // Con_DrawOutputVersion

			// change output box size
			Util::Hook::SetValue(0x8201DF2C, 36.0f);

			// change console font
			Util::Hook::SetString(0x820214C0, "fonts/fwsmallfont");
		}

		void ClearHooks()
		{
			DevGui_GetScreenXPad_Hook.Clear();
			DevGui_GetScreenYPad_Hook.Clear();
			Con_DrawConsole_Hook.Clear();
			CL_DrawScreen_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif
}
