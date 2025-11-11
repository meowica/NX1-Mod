#include "IniConfig.h"

namespace Drawing
{
#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		void DrawWatermark()
		{
			if (!IniConfig::ShouldShowWatermark() ||
				!*Symbols::Multiplayer::fwSmallFont ||
				Symbols::Multiplayer::Con_IsActive(0) ||
				Symbols::Multiplayer::DevGui_IsActive())
			{
				return;
			}

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::Multiplayer::R_AddCmdDrawText(
				BRANDING_STR,
				MAX_CHARS,
				*Symbols::Multiplayer::fwSmallFont,
				2.0f,
				20.0f,
				0.8f,
				0.8f,
				0.0f,
				colour,
				3,
				Structs::SL_SYSTEM);
		}

		void DrawFPSCounter()
		{
			if (!IniConfig::ShouldShowFPSCounter() ||
				!*Symbols::Multiplayer::fwSmallFont ||
				Symbols::Multiplayer::Con_IsActive(0))
			{
				return;
			}

			float colourGood[4] = { 0.6f, 1.0f, 0.0f, 1.0f };
			float colourOkay[4] = { 1.0f, 0.7f, 0.3f, 1.0f };
			float colourBad[4]  = { 1.0f, 0.3f, 0.3f, 1.0f };

			// im only doing this cause im too lazy to grab the games version
			Util::FPS& FPS = Util::FPS::GetInstance();
			FPS.Update();

			float fpsValue = FPS.GetFPS();
			int count = static_cast<int>(fpsValue + 0.5f);

			float* colour = (count >= 60) ? colourGood :
							(count >= 50) ? colourOkay : colourBad;

			char text[4];
			snprintf(text, sizeof(text), "%d", count);

			float x = (count <= 99) ? 1255.0f : 1243.0f;

			Symbols::Multiplayer::R_AddCmdDrawText(
				text,
				MAX_CHARS,
				*Symbols::Multiplayer::fwSmallFont,
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
			DrawFPSCounter();

			auto Invoke = CL_DrawScreen_Hook.Invoke<void(*)()>();
			Invoke();
		}

		void Hooks()
		{
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
			if (!IniConfig::ShouldShowWatermark() ||
				!*Symbols::Singleplayer::fwSmallFont ||
				Symbols::Singleplayer::Con_IsActive(0) ||
				Symbols::Singleplayer::DevGui_IsActive())
			{
				return;
			}

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::Singleplayer::R_AddCmdDrawText(
				BRANDING_STR,
				MAX_CHARS,
				*Symbols::Singleplayer::fwSmallFont,
				2.0f,
				20.0f,
				0.8f,
				0.8f,
				0.0f,
				colour,
				3,
				Structs::SL_SYSTEM);
		}

		void DrawFPSCounter()
		{
			if (!IniConfig::ShouldShowFPSCounter() ||
				!*Symbols::Singleplayer::fwSmallFont ||
				Symbols::Singleplayer::Con_IsActive(0))
			{
				return;
			}

			float colourGood[4] = { 0.6f, 1.0f, 0.0f, 1.0f };
			float colourOkay[4] = { 1.0f, 0.7f, 0.3f, 1.0f };
			float colourBad[4]  = { 1.0f, 0.3f, 0.3f, 1.0f };

			// im only doing this cause im too lazy to grab the games version
			Util::FPS& FPS = Util::FPS::GetInstance();
			FPS.Update();

			float fpsValue = FPS.GetFPS();
			int count = static_cast<int>(fpsValue + 0.5f);

			float* colour = (count >= 60) ? colourGood :
							(count >= 50) ? colourOkay : colourBad;

			char text[4];
			snprintf(text, sizeof(text), "%d", count);

			float x = (count <= 99) ? 1255.0f : 1243.0f;

			Symbols::Singleplayer::R_AddCmdDrawText(
				text,
				MAX_CHARS,
				*Symbols::Singleplayer::fwSmallFont,
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
			DrawFPSCounter();

			auto Invoke = CL_DrawScreen_Hook.Invoke<void(*)()>();
			Invoke();
		}

		void Hooks()
		{
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
