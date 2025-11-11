#include "IniConfig.h"

namespace Drawing
{
	Structs::Font_s** fwSmallFont;

#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		void DrawWatermark()
		{
			if (!IniConfig::ShouldShowWatermark() || !*fwSmallFont || Symbols::Multiplayer::Con_IsActive(0) || Symbols::Multiplayer::DevGui_IsActive())
				return;

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::Multiplayer::R_AddCmdDrawText(BRANDING_STR, MAX_CHARS, *fwSmallFont, 2.0f, 20.0f, 0.8f, 0.8f, 0.0f, colour, 3, Structs::SL_SYSTEM);
		}

		void DrawFPS()
		{
			if (!IniConfig::ShouldShowFPSCounter() || !*fwSmallFont || Symbols::Multiplayer::Con_IsActive(0))
				return;

			float colourGood[4] = { 0.6f, 1.0f, 0.0f, 1.0f };
			float colourOkay[4] = { 1.0f, 0.7f, 0.3f, 1.0f };
			float colourBad[4]  = { 1.0f, 0.3f, 0.3f, 1.0f };

			Util::FPS& fps = Util::FPS::GetInstance();
			fps.Update();

			float fpsValue = fps.GetFPS();
			int count = static_cast<int>(fpsValue + 0.5f);

			float* colour = (count >= 60) ? colourGood :
							(count >= 50) ? colourOkay : colourBad;

			char text[16];
			snprintf(text, sizeof(text), "%d", count);

			float x = (count <= 99) ? 1255.0f : 1245.0f;

			Symbols::Multiplayer::R_AddCmdDrawText(
				text,
				MAX_CHARS,
				*fwSmallFont,
				x,
				20.0f,
				1.0f,
				1.0f,
				0.0f,
				colour,
				3,
				Structs::SL_SYSTEM);
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
			fwSmallFont = reinterpret_cast<Structs::Font_s**>(0x85ECBACC); // fonts/fwsmallfont

			// draw our watermark and fps counter
			CL_DrawScreen_Hook.Create(0x822BD290, CL_DrawScreen);

			// disable some unneeded drawing
			Util::Hook::Nop(0x822BD2E8, 2); // CG_DrawVersion
			Util::Hook::Nop(0x82510438, 2); // UI_DrawBuildNumber
		}

		void ClearHooks()
		{
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
#elif IS_SINGLEPLAYER
	namespace Singleplayer
	{
		void DrawWatermark()
		{
			if (!IniConfig::ShouldShowWatermark() || !*fwSmallFont || Symbols::Singleplayer::Con_IsActive(0) || Symbols::Singleplayer::DevGui_IsActive())
				return;

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::Singleplayer::R_AddCmdDrawText(BRANDING_STR, MAX_CHARS, *fwSmallFont, 2.0f, 20.0f, 0.8f, 0.8f, 0.0f, colour, 3, Structs::SL_SYSTEM);
		}

		void DrawFPS()
		{
			if (!IniConfig::ShouldShowFPSCounter() || !*fwSmallFont || Symbols::Singleplayer::Con_IsActive(0))
				return;

			float colourGood[4] = { 0.6f, 1.0f, 0.0f, 1.0f };
			float colourOkay[4] = { 1.0f, 0.7f, 0.3f, 1.0f };
			float colourBad[4]  = { 1.0f, 0.3f, 0.3f, 1.0f };

			Util::FPS& fps = Util::FPS::GetInstance();
			fps.Update();

			float fpsValue = fps.GetFPS();
			int count = static_cast<int>(fpsValue + 0.5f);

			float* colour = (count >= 60) ? colourGood :
							(count >= 50) ? colourOkay : colourBad;

			char text[16];
			snprintf(text, sizeof(text), "%d", count);

			float x = (count <= 99) ? 1255.0f : 1245.0f;

			Symbols::Singleplayer::R_AddCmdDrawText(
				text,
				MAX_CHARS,
				*fwSmallFont,
				x,
				20.0f,
				1.0f,
				1.0f,
				0.0f,
				colour,
				3,
				Structs::SL_SYSTEM);
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
			fwSmallFont = reinterpret_cast<Structs::Font_s**>(0x8423B21C); // fonts/fwsmallfont

			// draw our watermark and fps counter
			CL_DrawScreen_Hook.Create(0x8221F858, CL_DrawScreen);

			// disable some unneeded drawing
			Util::Hook::Nop(0x8221F894, 2); // CG_DrawVersion
			Util::Hook::Nop(0x824A6F3C, 2); // UI_DrawBuildNumber
		}

		void ClearHooks()
		{
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
