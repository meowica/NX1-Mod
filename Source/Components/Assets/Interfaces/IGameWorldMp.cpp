#include "IGameWorldMp.h"

namespace IGameWorldMp
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

#ifdef IS_MP
	namespace MP
	{
		void Dump_GameWorldMp(const GameWorldMp* gameWorldMp)
		{
			if (!gameWorldMp)
				return;

			std::string assetName = gameWorldMp->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".gameworldmp.json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"";
			{
				std::string esc;
				JsonEscape(gameWorldMp->name, esc);
				oss << esc;
			}
			oss << "\",\n";
			G_GlassData* gd = gameWorldMp->g_glassData;
			if (!gd)
			{
				oss << "  \"glassData\": null\n";
				oss << "}\n";

				std::string outStr = oss.str();
				Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
				return;
			}
			oss << "  \"glassData\": {\n";
			oss << "    \"pieceCount\": " << gd->pieceCount << ",\n";
			oss << "    \"damageToWeaken\": " << gd->damageToWeaken << ",\n";
			oss << "    \"damageToDestroy\": " << gd->damageToDestroy << ",\n";
			oss << "    \"glassPieces\": [\n";
			for (unsigned int i = 0; i < gd->pieceCount; ++i)
			{
				const G_GlassPiece& p = gd->glassPieces[i];

				oss << "      {\n";
				oss << "        \"damageTaken\": " << p.damageTaken << ",\n";
				oss << "        \"collapseTime\": " << p.collapseTime << ",\n";
				oss << "        \"lastStateChangeTime\": " << p.lastStateChangeTime << ",\n";
				oss << "        \"impactDir\": " << (int)p.impactDir << ",\n";
				oss << "        \"impactPos\": [ "
					<< (int)p.impactPos[0] << ", "
					<< (int)p.impactPos[1] << " ]\n";
				oss << "      }";
				if (i + 1 < gd->pieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"glassNames\": [\n";
			for (unsigned int i = 0; i < gd->glassNameCount; ++i)
			{
				const G_GlassName& gn = gd->glassNames[i];

				oss << "      {\n";
				oss << "        \"nameStr\": \"";
				{
					std::string esc;
					JsonEscape(gn.nameStr, esc);
					oss << esc;
				}
				oss << "\",\n";
				oss << "        \"name\": " << gn.name << ",\n";
				oss << "        \"pieceCount\": " << gn.pieceCount << ",\n";
				oss << "        \"pieceIndices\": [";
				for (unsigned int j = 0; j < gn.pieceCount; ++j)
				{
					oss << gn.pieceIndices[j];
					if (j + 1 < gn.pieceCount)
						oss << ", ";
				}
				oss << "]\n";
				oss << "      }";
				if (i + 1 < gd->glassNameCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ]\n";
			oss << "  }\n";
			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_GameWorldMpPtr_Hook;
		void Load_GameWorldMpPtr(bool atStreamStart)
		{
			auto varGameWorldMpPtr = *reinterpret_cast<GameWorldMp***>(0x82CE6C1C);

			Load_GameWorldMpPtr_Hook.Invoke<void>(atStreamStart);

			if (varGameWorldMpPtr && *varGameWorldMpPtr)
			{
				if (IniConfig::EnableGameWorldMpDumper)
					Dump_GameWorldMp(*varGameWorldMpPtr);
				//if (IniConfig::EnableGameWorldMpLoader)
				//	Load_GameWorldMp(*varGameWorldMpPtr);
			}
		}

		void Load()
		{
			Load_GameWorldMpPtr_Hook.Create(0x8230AAB8, Load_GameWorldMpPtr);
		}

		void Unload()
		{
			Load_GameWorldMpPtr_Hook.Clear();
		}
	}
#endif
}
