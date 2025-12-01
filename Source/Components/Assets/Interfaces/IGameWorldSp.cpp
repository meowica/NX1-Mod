#include "IGameWorldSp.h"

namespace IGameWorldSp
{
	static void JsonEscape(const char* in, std::string& out)
	{
		if (!in)
			return;

		for (const char* p = in; *p; ++p)
		{
			switch (*p)
			{
			case '\"':
				out += "\\\"";
				break;
			case '\\':
				out += "\\\\";
				break;
			case '\b':
				out += "\\b";
				break;
			case '\f':
				out += "\\f";
				break;
			case '\n':
				out += "\\n";
				break;
			case '\r':
				out += "\\r";
				break;
			case '\t':
				out += "\\t";
				break;
			default:
				out += *p;
				break;
			}
		}
	}

#ifdef IS_SP
	namespace SP
	{
		void Dump_GameWorldSp(const GameWorldSp* gameWorldSp)
		{
			if (!gameWorldSp)
				return;

			std::string assetName = gameWorldSp->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".gameworldsp.json";

			Util::FileSystem::WriteFile(outPath.c_str(), "no", 2);
		}

		Util::Hook::Detour Load_GameWorldSpPtr_Hook;
		void Load_GameWorldSpPtr(bool atStreamStart)
		{
			auto varGameWorldSpPtr = *reinterpret_cast<GameWorldSp***>(0x82C6D9EC);

			Load_GameWorldSpPtr_Hook.Invoke<void>(atStreamStart);

			if (varGameWorldSpPtr && *varGameWorldSpPtr)
			{
				if (IniConfig::EnableGameWorldSpDumper)
					Dump_GameWorldSp(*varGameWorldSpPtr);
				//if (IniConfig::EnableGameWorldSpLoader)
				//	Load_GameWorldSp(*varGameWorldSpPtr);
			}
		}

		void Load()
		{
			Load_GameWorldSpPtr_Hook.Create(0x8226FE70, Load_GameWorldSpPtr);
		}

		void Unload()
		{
			Load_GameWorldSpPtr_Hook.Clear();
		}
	}
#endif
}
