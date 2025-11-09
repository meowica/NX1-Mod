namespace Util
{
	namespace Command
	{
		static std::vector<Structs::cmd_function_s*> cmds;
#ifdef IS_MULTIPLAYER
		static Structs::CmdArgs*& g_cmdArgs = Symbols::Multiplayer::cmd_args;
#elif IS_SINGLEPLAYER
		static Structs::CmdArgs*& g_cmdArgs = Symbols::Singleplayer::cmd_args;
#endif

		Args::Args()
		{
			this->nesting_ = g_cmdArgs->nesting - 1;

			if (this->nesting_ < 0)
				this->nesting_ = 0;
		}

		int Args::Size() const
		{
			return g_cmdArgs->argc[nesting_];
		}

		const char* Args::Get(int index) const
		{
			if (index >= g_cmdArgs->argc[this->nesting_])
				return "";
			return g_cmdArgs->argv[this->nesting_][index];
		}

		static Structs::cmd_function_s* allocedCmd()
		{
			auto* cmd = new Structs::cmd_function_s;
			cmds.push_back(cmd);
			return cmd;
		}

		void Add(const char* cmdName, void(__cdecl* function)())
		{
#ifdef IS_MULTIPLAYER
			Symbols::Multiplayer::Cmd_AddCommand(cmdName, function, allocedCmd());
#elif IS_SINGLEPLAYER
			Symbols::Singleplayer::Cmd_AddCommand(cmdName, function, allocedCmd());
#endif
		}
	}
}
