namespace Network
{
#ifdef IS_MP
	namespace MP
	{
		Util::Hook::Detour SanityCheckSession_Hook;
		void SanityCheckSession(Structs::SessionData* session)
		{
		}

		Util::Hook::Detour LSP_CheckOngoingTasks_Hook;
		void LSP_CheckOngoingTasks(int PacketsInternal)
		{
		}

		void Load()
		{
			// don't check the session sanity state
			SanityCheckSession_Hook.Create(0x82625188, SanityCheckSession);

			// dont check any lsp tasks
			LSP_CheckOngoingTasks_Hook.Create(0x82633810, LSP_CheckOngoingTasks);
		}

		void Unload()
		{
			SanityCheckSession_Hook.Clear();
			LSP_CheckOngoingTasks_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		Util::Hook::Detour SanityCheckSession_Hook;
		void SanityCheckSession(Structs::SessionData* session)
		{
		}

		Util::Hook::Detour LSP_CheckOngoingTasks_Hook;
		void LSP_CheckOngoingTasks(int PacketsInternal)
		{
		}

		void Load()
		{
			// don't check the session sanity state
			SanityCheckSession_Hook.Create(0x82597720, SanityCheckSession);

			// dont check any lsp tasks
			LSP_CheckOngoingTasks_Hook.Create(0x825A2C68, LSP_CheckOngoingTasks);
		}

		void Unload()
		{
			SanityCheckSession_Hook.Clear();
			LSP_CheckOngoingTasks_Hook.Clear();
		}
	}
#endif
}
