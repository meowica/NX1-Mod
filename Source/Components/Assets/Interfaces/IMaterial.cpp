#include "IMaterial.h"

namespace IMaterial
{
	static std::string JsonEscape(const char* string)
	{
		if (!string)
			return "";

		std::string input = string;
		std::string out;
		out.reserve(input.size() + 8);

		for (size_t i = 0; i < input.size(); i++)
		{
			char c = input[i];
			switch (c)
			{
			case '\\':
				out += "\\\\";
				break;
			case '"':
				out += "\\\"";
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
				if ((unsigned char)c < 0x20)
				{
					char buf[8];
					sprintf(buf, "\\u%04x", c);
					out += buf;
				}
				else
				{
					out += c;
				}
			}
		}
		return out;
	}

#ifdef IS_MP
	namespace MP
	{
		void Dump_Material(const IMaterial::Material* asset)
		{
			if (!asset)
				return;

			std::string assetName = asset->info.name ? asset->info.name : "unnamed";
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\materials\\" + assetName + ".json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << JsonEscape(asset->info.name) << "\",\n";
			oss << "  \"gameFlags\": " << asset->info.gameFlags << ",\n";
			oss << "  \"sortKey\": " << (int)asset->info.sortKey << ",\n";
			oss << "  \"surfaceTypeBits\": " << asset->info.surfaceTypeBits << ",\n";
			oss << "  \"stateFlags\": " << (int)asset->stateFlags << ",\n";
			oss << "  \"cameraRegion\": " << (int)asset->cameraRegion << ",\n";
			if (asset->techniqueSet)
				oss << "  \"techniqueSet\": \"" << JsonEscape(asset->techniqueSet->name) << "\",\n";
			else
				oss << "  \"techniqueSet\": null,\n";
			oss << "  \"constants\": [\n";
			for (int i = 0; i < asset->constantCount; i++)
			{
				const MaterialConstantDef& con = asset->constantTable[i];
				oss << "    {\n";
				oss << "      \"nameHash\": " << con.nameHash << ",\n";
				oss << "      \"name\": \"" << JsonEscape(con.name) << "\",\n";
				oss << "      \"literal\": ["
					<< con.literal[0] << ", " << con.literal[1] << ", "
					<< con.literal[2] << ", " << con.literal[3] << "]\n";
				oss << "    }";
				if (i + 1 != asset->constantCount) oss << ",";
				oss << "\n";
			}
			oss << "  ],\n";
			oss << "  \"stateBitsEntry\": [";
			for (int i = 0; i < 52; i++)
			{
				oss << (int)asset->stateBitsEntry[i];
				if (i != 51) oss << ", ";
			}
			oss << "],\n";
			oss << "  \"maps\": [\n";
			for (int i = 0; i < asset->textureCount; i++)
			{
				const MaterialTextureDef& tex = asset->textureTable[i];
				oss << "    {\n";
				oss << "      \"nameHash\": " << tex.nameHash << ",\n";
				oss << "      \"firstCharacter\": \"" << tex.nameStart << "\",\n";
				oss << "      \"secondLastCharacter\": \"" << tex.nameEnd << "\",\n";
				oss << "      \"sampleState\": " << (int)tex.samplerState << ",\n";
				oss << "      \"semantic\": " << (int)tex.m_semantic << ",\n";
				if (tex.m_semantic == 11 && tex.u.water)
				{
					water_t* waterData = tex.u.water;

					oss << "      \"image\": \""
						<< (waterData->image ? JsonEscape(waterData->image->name) : "null") << "\",\n";

					oss << "      \"waterinfo\": {\n";
					oss << "        \"floatTime\": " << waterData->writable.floatTime << ",\n";
					oss << "        \"codeConstant\": ["
						<< waterData->codeConstant[0] << ", "
						<< waterData->codeConstant[1] << ", "
						<< waterData->codeConstant[2] << ", "
						<< waterData->codeConstant[3] << "],\n";
					oss << "        \"M\": " << waterData->M << ",\n";
					oss << "        \"N\": " << waterData->N << ",\n";
					oss << "        \"Lx\": " << waterData->Lx << ",\n";
					oss << "        \"Lz\": " << waterData->Lz << ",\n";
					oss << "        \"gravity\": " << waterData->gravity << ",\n";
					oss << "        \"windvel\": " << waterData->windvel << ",\n";
					oss << "        \"winddir\": [" << waterData->winddir[0] << ", " << waterData->winddir[1] << "],\n";
					oss << "        \"amplitude\": " << waterData->amplitude << ",\n";
					oss << "        \"complex\": [";
					for (int j = 0; j < waterData->M * waterData->N; j++)
					{
						oss << "{ \"real\": " << waterData->H0X[j] << ", \"imag\": " << waterData->H0Y[j] << " }";
						if (j + 1 != waterData->M * waterData->N) oss << ", ";
					}
					oss << "],\n";
					oss << "        \"wTerm\": [";
					for (int j = 0; j < waterData->M * waterData->N; j++)
					{
						oss << waterData->wTerm[j];
						if (j + 1 != waterData->M * waterData->N) oss << ", ";
					}
					oss << "]\n";
					oss << "      }\n";
				}
				else
				{
					oss << "      \"image\": \"" << (tex.u.image ? JsonEscape(tex.u.image->name) : "null") << "\"\n";
				}
				oss << "    }";
				if (i + 1 != asset->textureCount)
					oss << ",";
				oss << "\n";
			}
			oss << "  ],\n";
			oss << "  \"subMaterials\": [";
			if (asset->subMaterials)
			{
				for (int i = 0; i < asset->layerCount; i++)
				{
					if (!asset->subMaterials[i])
						oss << "null";
					else
						oss << "\"" << JsonEscape(asset->subMaterials[i]) << "\"";
					if (i + 1 != asset->layerCount)
						oss << ", ";
				}
			}
			oss << "]\n";
			oss << "}\n";

			const std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
		}

		Util::Hook::Detour Load_MaterialHandle_Hook;
		void Load_MaterialHandle(bool atStreamStart)
		{
			auto varMaterialHandle = *reinterpret_cast<IMaterial::Material***>(0x82CE6148);

			Load_MaterialHandle_Hook.Invoke<void>(atStreamStart);

			if (varMaterialHandle && *varMaterialHandle)
			{
				//if (IniConfig::EnableLaserDefDumper)
				//	Dump_Material(*varMaterialHandle);
				//if (IniConfig::EnableLaserDefLoader)
				//	Load_Material(*varMaterialHandle);
			}
		}

		void Load()
		{
			//Load_MaterialHandle_Hook.Create(0x82303C58, Load_MaterialHandle);
		}

		void Unload()
		{
			Load_MaterialHandle_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Load()
		{

		}

		void Unload()
		{

		}
	}
#endif
}
