#include "IComWorld.h"

namespace IComWorld
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_ComWorld(const ComWorld* comWorld)
		{
			if (!comWorld)
				return;

			std::string assetName = comWorld->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".comworld.json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << Util::JSON::JsonEscape(comWorld->name) << "\",\n";
			oss << "  \"isInUse\": " << comWorld->isInUse << ",\n";
			oss << "  \"primaryLightCount\": " << comWorld->primaryLightCount << ",\n";
			oss << "  \"primaryLights\": [\n";

			for (unsigned int i = 0; i < comWorld->primaryLightCount; ++i)
			{
				const ComPrimaryLight& L = comWorld->primaryLights[i];

				oss << "    {\n";
				oss << "      \"type\": " << (int)L.type << ",\n";
				oss << "      \"canUseShadowMap\": " << (int)L.canUseShadowMap << ",\n";
				oss << "      \"exponent\": " << (int)L.exponent << ",\n";
				oss << "      \"lut_id\": " << (int)L.lut_id << ",\n";
				oss << "      \"spot_rotation\": " << (int)L.spot_rotation << ",\n";
				oss << "      \"color\": [ "
					<< L.color[0] << ", " << L.color[1] << ", " << L.color[2]
					<< " ],\n";
				oss << "      \"dir\": [ "
					<< L.dir[0] << ", " << L.dir[1] << ", " << L.dir[2]
					<< " ],\n";
				oss << "      \"origin\": [ "
					<< L.origin[0] << ", " << L.origin[1] << ", " << L.origin[2]
					<< " ],\n";
				oss << "      \"radius\": " << L.radius << ",\n";
				oss << "      \"cosHalfFovOuter\": " << L.cosHalfFovOuter << ",\n";
				oss << "      \"cosHalfFovInner\": " << L.cosHalfFovInner << ",\n";
				oss << "      \"cosHalfFovExpanded\": " << L.cosHalfFovExpanded << ",\n";
				oss << "      \"rotationLimit\": " << L.rotationLimit << ",\n";
				oss << "      \"translationLimit\": " << L.translationLimit << ",\n";
				oss << "      \"defName\": \"" << Util::JSON::JsonEscape(L.defName) << "\"\n";
				oss << "    }";
				if (i + 1 < comWorld->primaryLightCount)
					oss << ",";
				oss << "\n";
			}
			oss << "  ]\n";
			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_ComWorldPtr_Hook;
		void Load_ComWorldPtr(bool atStreamStart)
		{
			auto varComWorldPtr = *reinterpret_cast<ComWorld***>(0x82CE5FB8);

			Load_ComWorldPtr_Hook.Invoke<void>(atStreamStart);

			if (varComWorldPtr && *varComWorldPtr)
			{
				if (IniConfig::EnableComWorldDumper)
					Dump_ComWorld(*varComWorldPtr);
				//if (IniConfig::EnableComWorldLoader)
				//	Load_ComWorld(*varComWorldPtr);
			}
		}

		void Load()
		{
			Load_ComWorldPtr_Hook.Create(0x82312318, Load_ComWorldPtr);
		}

		void Unload()
		{
			Load_ComWorldPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_ComWorld(const ComWorld* comWorld)
		{
			if (!comWorld)
				return;

			std::string assetName = comWorld->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".comworld.json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << Util::JSON::JsonEscape(comWorld->name) << "\",\n";
			oss << "  \"isInUse\": " << comWorld->isInUse << ",\n";
			oss << "  \"primaryLightCount\": " << comWorld->primaryLightCount << ",\n";
			oss << "  \"primaryLights\": [\n";

			for (unsigned int i = 0; i < comWorld->primaryLightCount; ++i)
			{
				const ComPrimaryLight& L = comWorld->primaryLights[i];

				oss << "    {\n";
				oss << "      \"type\": " << (int)L.type << ",\n";
				oss << "      \"canUseShadowMap\": " << (int)L.canUseShadowMap << ",\n";
				oss << "      \"exponent\": " << (int)L.exponent << ",\n";
				oss << "      \"lut_id\": " << (int)L.lut_id << ",\n";
				oss << "      \"spot_rotation\": " << (int)L.spot_rotation << ",\n";
				oss << "      \"color\": [ "
					<< L.color[0] << ", " << L.color[1] << ", " << L.color[2]
					<< " ],\n";
				oss << "      \"dir\": [ "
					<< L.dir[0] << ", " << L.dir[1] << ", " << L.dir[2]
					<< " ],\n";
				oss << "      \"origin\": [ "
					<< L.origin[0] << ", " << L.origin[1] << ", " << L.origin[2]
					<< " ],\n";
				oss << "      \"radius\": " << L.radius << ",\n";
				oss << "      \"cosHalfFovOuter\": " << L.cosHalfFovOuter << ",\n";
				oss << "      \"cosHalfFovInner\": " << L.cosHalfFovInner << ",\n";
				oss << "      \"cosHalfFovExpanded\": " << L.cosHalfFovExpanded << ",\n";
				oss << "      \"rotationLimit\": " << L.rotationLimit << ",\n";
				oss << "      \"translationLimit\": " << L.translationLimit << ",\n";
				oss << "      \"defName\": \"" << Util::JSON::JsonEscape(L.defName) << "\"\n";
				oss << "    }";
				if (i + 1 < comWorld->primaryLightCount)
					oss << ",";
				oss << "\n";
			}
			oss << "  ]\n";
			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_ComWorldPtr_Hook;
		void Load_ComWorldPtr(bool atStreamStart)
		{
			auto varComWorldPtr = *reinterpret_cast<ComWorld***>(0x82C6D9B8);

			Load_ComWorldPtr_Hook.Invoke<void>(atStreamStart);

			if (varComWorldPtr && *varComWorldPtr)
			{
				if (IniConfig::EnableComWorldDumper)
					Dump_ComWorld(*varComWorldPtr);
				//if (IniConfig::EnableComWorldLoader)
				//	Load_ComWorld(*varComWorldPtr);
			}
		}

		void Load()
		{
			Load_ComWorldPtr_Hook.Create(0x8225BF40, Load_ComWorldPtr);
		}

		void Unload()
		{
			Load_ComWorldPtr_Hook.Clear();
		}
	}
#endif
}
