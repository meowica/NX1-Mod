namespace Assertion
{
#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		Util::Hook::Detour MAssertVargs_Hook;
		int MAssertVargs(const char* filename, int line, int type, int unknown, const char* fmt, ...)
		{
			// TODO: implement symbols printing

			static const char* lastFilename = NULL;
			static int lastLine = -1;
			static int repeatCount = 0;

			// check if this is the same assert location as last time
			if (lastFilename && strcmp(lastFilename, filename) == 0 && lastLine == line)
			{
				repeatCount++;
			}
			else
			{
				lastFilename = filename;
				lastLine = line;
				repeatCount = 1;
			}

			char message[1024];

			va_list va;
			va_start(va, fmt);
			vsnprintf_s(message, sizeof(message), fmt, va);
			message[sizeof(message) - 1] = '\0';

			Symbols::Multiplayer::Com_Printf(0, "\n");
			Symbols::Multiplayer::Com_Printf(0, "****************************************\n");
			Symbols::Multiplayer::Com_Printf(0, "*  Assertion Info:\n");
			Symbols::Multiplayer::Com_Printf(0, "*  Message:       %s\n", message);
			Symbols::Multiplayer::Com_Printf(0, "*  File:          %s\n", filename);
			Symbols::Multiplayer::Com_Printf(0, "*  Line:          %d\n", line);
			Symbols::Multiplayer::Com_Printf(0, "*  Type:          %d\n", type);
			Symbols::Multiplayer::Com_Printf(0, "****************************************\n");

			if (repeatCount >= 2)
			{
				Symbols::Multiplayer::Com_Printf(0, "*  Warning:       Same assert triggered multiple times.\n");
				Symbols::Multiplayer::Com_Printf(0, "****************************************\n");
				return 0;
			}
			else
			{
				Symbols::Multiplayer::Com_Printf(0, "*  Note:          First time this assert occurred.\n");
				Symbols::Multiplayer::Com_Printf(0, "****************************************\n");
				return 0;
			}
		}

		void Hooks()
		{
			// our custom assertion handler
			MAssertVargs_Hook.Create(0x82527570, MAssertVargs);
		}

		void ClearHooks()
		{
			MAssertVargs_Hook.Clear();
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
		Util::Hook::Detour MAssertVargs_Hook;
		int MAssertVargs(const char* filename, int line, int type, int unknown, const char* fmt, ...)
		{
			// TODO: implement symbols printing

			static const char* lastFilename = NULL;
			static int lastLine = -1;
			static int repeatCount = 0;

			// check if this is the same assert location as last time
			if (lastFilename && strcmp(lastFilename, filename) == 0 && lastLine == line)
			{
				repeatCount++;
			}
			else
			{
				lastFilename = filename;
				lastLine = line;
				repeatCount = 1;
			}

			char message[1024];

			va_list va;
			va_start(va, fmt);
			vsnprintf_s(message, sizeof(message), fmt, va);
			message[sizeof(message) - 1] = '\0';

			Symbols::Singleplayer::Com_Printf(0, "\n");
			Symbols::Singleplayer::Com_Printf(0, "****************************************\n");
			Symbols::Singleplayer::Com_Printf(0, "*  Assertion Info:\n");
			Symbols::Singleplayer::Com_Printf(0, "*  Message:       %s\n", message);
			Symbols::Singleplayer::Com_Printf(0, "*  File:          %s\n", filename);
			Symbols::Singleplayer::Com_Printf(0, "*  Line:          %d\n", line);
			Symbols::Singleplayer::Com_Printf(0, "*  Type:          %d\n", type);
			Symbols::Singleplayer::Com_Printf(0, "****************************************\n");

			if (repeatCount >= 2)
			{
				Symbols::Singleplayer::Com_Printf(0, "*  Warning:       Same assert triggered multiple times.\n");
				Symbols::Singleplayer::Com_Printf(0, "****************************************\n");
				return 0;
			}
			else
			{
				Symbols::Singleplayer::Com_Printf(0, "*  Note:          First time this assert occurred.\n");
				Symbols::Singleplayer::Com_Printf(0, "****************************************\n");
				return 0;
			}
		}

		void Hooks()
		{
			// our custom assertion handler
			MAssertVargs_Hook.Create(0x824BCD10, MAssertVargs);
		}

		void ClearHooks()
		{
			MAssertVargs_Hook.Clear();
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
