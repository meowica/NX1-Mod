#include "IFxWorld.h"

namespace IFxWorld
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_FxWorld(const FxWorld* fxWorld)
		{
			if (!fxWorld)
				return;

			std::string assetName = fxWorld->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".fxworld.json";

			const FxGlassSystem& glassSys = fxWorld->glassSys;

			std::ostringstream oss;
			oss << std::fixed << std::setprecision(6);
			oss << "{\n";
			oss << "  \"name\": \"" << assetName << "\",\n";
			oss << "  \"glassSystem\": {\n";
			oss << "    \"time\": " << glassSys.time << ",\n";
			oss << "    \"prevTime\": " << glassSys.prevTime << ",\n";
			oss << "    \"defCount\": " << glassSys.defCount << ",\n";
			oss << "    \"pieceLimit\": " << glassSys.pieceLimit << ",\n";
			oss << "    \"pieceWordCount\": " << glassSys.pieceWordCount << ",\n";
			oss << "    \"initPieceCount\": " << glassSys.initPieceCount << ",\n";
			oss << "    \"cellCount\": " << glassSys.cellCount << ",\n";
			oss << "    \"activePieceCount\": " << glassSys.activePieceCount << ",\n";
			oss << "    \"firstFreePiece\": " << glassSys.firstFreePiece << ",\n";
			oss << "    \"geoDataCount\": " << glassSys.geoDataCount << ",\n";
			oss << "    \"needToCompactData\": " << (glassSys.needToCompactData ? "true" : "false") << ",\n";
			oss << "    \"defs\": [\n";
			for (unsigned int i = 0; i < glassSys.defCount; ++i)
			{
				const FxGlassDef& def = glassSys.p_defs[i];
				oss << "      {\n";
				oss << "        \"halfThickness\": " << def.halfThickness << ",\n";
				oss << "        \"color\": " << def.color.packed << ",\n";
				oss << "        \"invHighMipRadius\": " << def.invHighMipRadius << ",\n";
				oss << "        \"shatteredInvHighMipRadius\": " << def.shatteredInvHighMipRadius << "\n";
				oss << "      }";
				if (i + 1 < glassSys.defCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"piecePlaces\": [\n";
			for (unsigned int i = 0; i < glassSys.initPieceCount; ++i)
			{
				const FxGlassPiecePlace& place = glassSys.p_piecePlaces[i];
				oss << "      {\n";
				oss << "        \"origin\": ["
					<< place.frame.origin[0] << ", "
					<< place.frame.origin[1] << ", "
					<< place.frame.origin[2] << "],\n";
				oss << "        \"quat\": ["
					<< place.frame.quat[0] << ", "
					<< place.frame.quat[1] << ", "
					<< place.frame.quat[2] << ", "
					<< place.frame.quat[3] << "]\n";
				oss << "      }";
				if (i + 1 < glassSys.initPieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"pieceStates\": [\n";
			for (unsigned int i = 0; i < glassSys.activePieceCount; ++i)
			{
				const FxGlassPieceState& piece = glassSys.p_pieceStates[i];
				oss << "      {\n";
				oss << "        \"initIndex\": " << piece.initIndex << ",\n";
				oss << "        \"vertCount\": " << (int)piece.vertCount << ",\n";
				oss << "        \"areaX2\": " << piece.areaX2 << ",\n";
				oss << "        \"supportMask\": " << piece.supportMask << "\n";
				oss << "      }";
				if (i + 1 < glassSys.activePieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"pieceDynamics\": [\n";
			for (unsigned int i = 0; i < glassSys.activePieceCount; ++i)
			{
				const FxGlassPieceDynamics& dyn = glassSys.p_pieceDynamics[i];
				oss << "      {\n";
				oss << "        \"fallTime\": " << dyn.fallTime << ",\n";
				oss << "        \"physObjId\": " << dyn.physObjId << ",\n";
				oss << "        \"physJointId\": " << dyn.physJointId << ",\n";
				oss << "        \"vel\": [" << dyn.vel[0] << ", " << dyn.vel[1] << ", " << dyn.vel[2] << "],\n";
				oss << "        \"avel\": [" << dyn.avel[0] << ", " << dyn.avel[1] << ", " << dyn.avel[2] << "]\n";
				oss << "      }";
				if (i + 1 < glassSys.activePieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"initPieceStates\": [\n";
			for (unsigned int i = 0; i < glassSys.initPieceCount; ++i)
			{
				const FxGlassInitPieceState& initPiece = glassSys.p_initPieceStates[i];
				oss << "      {\n";
				oss << "        \"origin\": [" << initPiece.frame.origin[0] << ", " << initPiece.frame.origin[1] << ", " << initPiece.frame.origin[2] << "],\n";
				oss << "        \"quat\": [" << initPiece.frame.quat[0] << ", " << initPiece.frame.quat[1] << ", " << initPiece.frame.quat[2] << ", " << initPiece.frame.quat[3] << "],\n";
				oss << "        \"radius\": " << initPiece.radius << ",\n";
				oss << "        \"vertCount\": " << (int)initPiece.vertCount << ",\n";
				oss << "        \"fanDataCount\": " << (int)initPiece.fanDataCount << ",\n";
				oss << "        \"areaX2\": " << initPiece.areaX2 << ",\n";
				oss << "        \"supportMask\": " << initPiece.supportMask << "\n";
				oss << "      }";
				if (i + 1 < glassSys.initPieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ]\n";

			oss << "  }\n";
			oss << "}";

			std::string& outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_FxWorldPtr_Hook;
		void Load_FxWorldPtr(bool atStreamStart)
		{
			auto varFxWorldPtr = *reinterpret_cast<FxWorld***>(0x82CE676C);

			Load_FxWorldPtr_Hook.Invoke<void>(atStreamStart);

			if (varFxWorldPtr && *varFxWorldPtr)
			{
				if (IniConfig::EnableFxWorldDumper)
					Dump_FxWorld(*varFxWorldPtr);
				//if (IniConfig::EnableFxWorldLoader)
				//	Load_FxWorld(*varFxWorldPtr);
			}
		}

		void Load()
		{
			Load_FxWorldPtr_Hook.Create(0x8230EC98, Load_FxWorldPtr);
		}

		void Unload()
		{
			Load_FxWorldPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_FxWorld(const FxWorld* fxWorld)
		{
			if (!fxWorld)
				return;

			std::string assetName = fxWorld->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".fxworld.json";

			const FxGlassSystem& glassSys = fxWorld->glassSys;

			std::ostringstream oss;
			oss << std::fixed << std::setprecision(6);
			oss << "{\n";
			oss << "  \"name\": \"" << assetName << "\",\n";
			oss << "  \"glassSystem\": {\n";
			oss << "    \"time\": " << glassSys.time << ",\n";
			oss << "    \"prevTime\": " << glassSys.prevTime << ",\n";
			oss << "    \"defCount\": " << glassSys.defCount << ",\n";
			oss << "    \"pieceLimit\": " << glassSys.pieceLimit << ",\n";
			oss << "    \"pieceWordCount\": " << glassSys.pieceWordCount << ",\n";
			oss << "    \"initPieceCount\": " << glassSys.initPieceCount << ",\n";
			oss << "    \"cellCount\": " << glassSys.cellCount << ",\n";
			oss << "    \"activePieceCount\": " << glassSys.activePieceCount << ",\n";
			oss << "    \"firstFreePiece\": " << glassSys.firstFreePiece << ",\n";
			oss << "    \"geoDataCount\": " << glassSys.geoDataCount << ",\n";
			oss << "    \"needToCompactData\": " << (glassSys.needToCompactData ? "true" : "false") << ",\n";
			oss << "    \"defs\": [\n";
			for (unsigned int i = 0; i < glassSys.defCount; ++i)
			{
				const FxGlassDef& def = glassSys.p_defs[i];
				oss << "      {\n";
				oss << "        \"halfThickness\": " << def.halfThickness << ",\n";
				oss << "        \"color\": " << def.color.packed << ",\n";
				oss << "        \"invHighMipRadius\": " << def.invHighMipRadius << ",\n";
				oss << "        \"shatteredInvHighMipRadius\": " << def.shatteredInvHighMipRadius << "\n";
				oss << "      }";
				if (i + 1 < glassSys.defCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"piecePlaces\": [\n";
			for (unsigned int i = 0; i < glassSys.initPieceCount; ++i)
			{
				const FxGlassPiecePlace& place = glassSys.p_piecePlaces[i];
				oss << "      {\n";
				oss << "        \"origin\": ["
					<< place.frame.origin[0] << ", "
					<< place.frame.origin[1] << ", "
					<< place.frame.origin[2] << "],\n";
				oss << "        \"quat\": ["
					<< place.frame.quat[0] << ", "
					<< place.frame.quat[1] << ", "
					<< place.frame.quat[2] << ", "
					<< place.frame.quat[3] << "]\n";
				oss << "      }";
				if (i + 1 < glassSys.initPieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"pieceStates\": [\n";
			for (unsigned int i = 0; i < glassSys.activePieceCount; ++i)
			{
				const FxGlassPieceState& piece = glassSys.p_pieceStates[i];
				oss << "      {\n";
				oss << "        \"initIndex\": " << piece.initIndex << ",\n";
				oss << "        \"vertCount\": " << (int)piece.vertCount << ",\n";
				oss << "        \"areaX2\": " << piece.areaX2 << ",\n";
				oss << "        \"supportMask\": " << piece.supportMask << "\n";
				oss << "      }";
				if (i + 1 < glassSys.activePieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"pieceDynamics\": [\n";
			for (unsigned int i = 0; i < glassSys.activePieceCount; ++i)
			{
				const FxGlassPieceDynamics& dyn = glassSys.p_pieceDynamics[i];
				oss << "      {\n";
				oss << "        \"fallTime\": " << dyn.fallTime << ",\n";
				oss << "        \"physObjId\": " << dyn.physObjId << ",\n";
				oss << "        \"physJointId\": " << dyn.physJointId << ",\n";
				oss << "        \"vel\": [" << dyn.vel[0] << ", " << dyn.vel[1] << ", " << dyn.vel[2] << "],\n";
				oss << "        \"avel\": [" << dyn.avel[0] << ", " << dyn.avel[1] << ", " << dyn.avel[2] << "]\n";
				oss << "      }";
				if (i + 1 < glassSys.activePieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ],\n";
			oss << "    \"initPieceStates\": [\n";
			for (unsigned int i = 0; i < glassSys.initPieceCount; ++i)
			{
				const FxGlassInitPieceState& initPiece = glassSys.p_initPieceStates[i];
				oss << "      {\n";
				oss << "        \"origin\": [" << initPiece.frame.origin[0] << ", " << initPiece.frame.origin[1] << ", " << initPiece.frame.origin[2] << "],\n";
				oss << "        \"quat\": [" << initPiece.frame.quat[0] << ", " << initPiece.frame.quat[1] << ", " << initPiece.frame.quat[2] << ", " << initPiece.frame.quat[3] << "],\n";
				oss << "        \"radius\": " << initPiece.radius << ",\n";
				oss << "        \"vertCount\": " << (int)initPiece.vertCount << ",\n";
				oss << "        \"fanDataCount\": " << (int)initPiece.fanDataCount << ",\n";
				oss << "        \"areaX2\": " << initPiece.areaX2 << ",\n";
				oss << "        \"supportMask\": " << initPiece.supportMask << "\n";
				oss << "      }";
				if (i + 1 < glassSys.initPieceCount)
					oss << ",";
				oss << "\n";
			}
			oss << "    ]\n";

			oss << "  }\n";
			oss << "}";

			std::string& outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_FxWorldPtr_Hook;
		void Load_FxWorldPtr(bool atStreamStart)
		{
			auto varFxWorldPtr = *reinterpret_cast<FxWorld***>(0x82C6E16C);

			Load_FxWorldPtr_Hook.Invoke<void>(atStreamStart);

			if (varFxWorldPtr && *varFxWorldPtr)
			{
				if (IniConfig::EnableFxWorldDumper)
					Dump_FxWorld(*varFxWorldPtr);
				//if (IniConfig::EnableFxWorldLoader)
				//	Load_FxWorld(*varFxWorldPtr);
			}
		}

		void Load()
		{
			Load_FxWorldPtr_Hook.Create(0x822588C0, Load_FxWorldPtr);
		}

		void Unload()
		{
			Load_FxWorldPtr_Hook.Clear();
		}
	}
#endif
}
