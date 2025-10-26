namespace Util
{
	namespace Command
	{
		static std::vector<Structs::cmd_function_s*> cmds;
#ifdef SP_MOD
		static Structs::CmdArgs*& g_cmd_args = Symbols::SP::cmd_args;
#else
		static Structs::CmdArgs*& g_cmd_args = Symbols::MP::cmd_args;
#endif

		Args::Args()
		{
			this->nesting_ = g_cmd_args->nesting - 1;

			if (this->nesting_ < 0)
				this->nesting_ = 0;
		}

		int Args::Size() const
		{
			return g_cmd_args->argc[nesting_];
		}

		const char* Args::Get(int index) const
		{
			if (index >= g_cmd_args->argc[this->nesting_])
				return "";
			return g_cmd_args->argv[this->nesting_][index];
		}

		static Structs::cmd_function_s* allocedCmd()
		{
			auto* cmd = new Structs::cmd_function_s;
			cmds.push_back(cmd);
			return cmd;
		}

		void Add(const char* cmdName, void(__cdecl* function)())
		{
#ifdef SP_MOD
			Symbols::SP::Cmd_AddCommand(cmdName, function, allocedCmd());
#else
			Symbols::MP::Cmd_AddCommand(cmdName, function, allocedCmd());
#endif
		}
	}
}
