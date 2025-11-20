namespace Drawing
{
#ifdef IS_MP
	namespace MP
	{
		void DrawWatermark()
		{
			if (!*Symbols::MP::fwSmallFont || Symbols::MP::Con_IsActive(0) || Symbols::MP::DevGui_IsActive())
				return;

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::MP::R_AddCmdDrawText(
				BRANDING_STR,
				MAX_CHARS,
				*Symbols::MP::fwSmallFont,
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
			if (!*Symbols::MP::fwSmallFont || Symbols::MP::Con_IsActive(0))
				return;

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

			Symbols::MP::R_AddCmdDrawText(
				text,
				MAX_CHARS,
				*Symbols::MP::fwSmallFont,
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
			if (IniConfig::ShowWatermark)
				DrawWatermark();

			if (IniConfig::ShowFPSCounter)
				DrawFPSCounter();

			CL_DrawScreen_Hook.Invoke<void>();
		}

		void Load()
		{
			// draw our watermark and fps counter
			CL_DrawScreen_Hook.Create(0x822BD290, CL_DrawScreen);

			// disable some unneeded drawing
			Util::Hook::Nop(0x822BD2E8, 2); // CG_DrawVersion
			Util::Hook::Nop(0x82510438, 2); // UI_DrawBuildNumber
		}

		void Unload()
		{
			CL_DrawScreen_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void DrawWatermark()
		{
			if (!*Symbols::SP::fwSmallFont || Symbols::SP::Con_IsActive(0) || Symbols::SP::DevGui_IsActive())
				return;

			float colour[4] = { 1.0f, 1.0f, 1.0f, 0.25f };

			Symbols::SP::R_AddCmdDrawText(
				BRANDING_STR,
				MAX_CHARS,
				*Symbols::SP::fwSmallFont,
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
			if (!*Symbols::SP::fwSmallFont || Symbols::SP::Con_IsActive(0))
				return;

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

			Symbols::SP::R_AddCmdDrawText(
				text,
				MAX_CHARS,
				*Symbols::SP::fwSmallFont,
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
			if (IniConfig::ShowWatermark)
				DrawWatermark();

			if (IniConfig::ShowFPSCounter)
				DrawFPSCounter();

			CL_DrawScreen_Hook.Invoke<void>();
		}

		void Load()
		{
			// draw our watermark and fps counter
			CL_DrawScreen_Hook.Create(0x8221F858, CL_DrawScreen);

			// disable some unneeded drawing
			Util::Hook::Nop(0x8221F894, 2); // CG_DrawVersion
			Util::Hook::Nop(0x824A6F3C, 2); // UI_DrawBuildNumber
		}

		void Unload()
		{
			CL_DrawScreen_Hook.Clear();
		}
	}
#endif
}
