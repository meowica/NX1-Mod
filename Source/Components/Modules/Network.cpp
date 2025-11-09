namespace Network
{
#ifdef IS_MULTIPLAYER
	namespace MP
	{
		Util::Hook::Detour SanityCheckSession_Hook;
		void SanityCheckSession(const char** unknown)
		{
			return;
		}

		Util::Hook::Detour LSP_CheckOngoingTasks_Hook;
		void LSP_CheckOngoingTasks(int PacketsInternal)
		{
			return;
		}

		void Hooks()
		{
			// dont check the session's sanity state on xenia
			if (Util::XBox::IsInXenia())
			{
				SanityCheckSession_Hook.Create(0x82625188, SanityCheckSession);
			}

			// dont check any lsp tasks
			LSP_CheckOngoingTasks_Hook.Create(0x82633810, LSP_CheckOngoingTasks);
		}

		void ClearHooks()
		{
			SanityCheckSession_Hook.Clear();
			LSP_CheckOngoingTasks_Hook.Clear();
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
	namespace SP
	{
		Util::Hook::Detour SanityCheckSession_Hook;
		void SanityCheckSession(const char** unknown)
		{
			return;
		}

		Util::Hook::Detour LSP_CheckOngoingTasks_Hook;
		void LSP_CheckOngoingTasks(int PacketsInternal)
		{
			return;
		}

		void Hooks()
		{
			// dont check the session's sanity state on xenia
			if (Util::XBox::IsInXenia())
			{
				SanityCheckSession_Hook.Create(0x82597720, SanityCheckSession);
			}

			// dont check any lsp tasks
			LSP_CheckOngoingTasks_Hook.Create(0x825A2C68, LSP_CheckOngoingTasks);
		}

		void ClearHooks()
		{
			SanityCheckSession_Hook.Clear();
			LSP_CheckOngoingTasks_Hook.Clear();
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
