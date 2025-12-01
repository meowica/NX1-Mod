#include "IClipMap.h"

namespace IClipMap
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_ClipMap(const clipMap_t* clipMap)
		{
			if (!clipMap)
				return;

			std::string assetName = clipMap->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".clipmap.json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << assetName << "\",\n";
			oss << "  \"isInUse\": " << clipMap->isInUse << ",\n";
			oss << "  \"planeCount\": " << clipMap->planeCount << ",\n";
			oss << "  \"numStaticModels\": " << clipMap->numStaticModels << ",\n";
			oss << "  \"numMaterials\": " << clipMap->numMaterials << ",\n";
			oss << "  \"numBrushSides\": " << clipMap->numBrushSides << ",\n";
			oss << "  \"numNodes\": " << clipMap->numNodes << ",\n";
			oss << "  \"numLeafs\": " << clipMap->numLeafs << ",\n";
			oss << "  \"vertCount\": " << clipMap->vertCount << ",\n";
			oss << "  \"triCount\": " << clipMap->triCount << ",\n";
			oss << "  \"borderCount\": " << clipMap->borderCount << ",\n";
			oss << "  \"partitionCount\": " << clipMap->partitionCount << ",\n";
			oss << "  \"checksum\": " << clipMap->checksum << ",\n";
			oss << "  \"staticModels\": [\n";
			for (unsigned int i = 0; i < clipMap->numStaticModels; ++i)
			{
				const cStaticModel_s& sm = clipMap->staticModelList[i];
				oss << "    {\n";
				oss << "      \"xmodel\": \"" << sm.xmodel->name << "\",\n";
				oss << "      \"origin\": [" << sm.origin[0] << ", " << sm.origin[1] << ", " << sm.origin[2] << "],\n";
				oss << "      \"absBounds\": {\n";
				oss << "        \"midPoint\": [" << sm.absBounds.midPoint[0] << ", " << sm.absBounds.midPoint[1] << ", " << sm.absBounds.midPoint[2] << "],\n";
				oss << "        \"halfSize\": [" << sm.absBounds.halfSize[0] << ", " << sm.absBounds.halfSize[1] << ", " << sm.absBounds.halfSize[2] << "]\n";
				oss << "      }\n";
				oss << "    }" << (i + 1 < clipMap->numStaticModels ? "," : "") << "\n";
			}
			oss << "  ]\n";
			oss << "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), oss.str().c_str(), oss.str().size());
		}

		Util::Hook::Detour Load_clipMap_ptr_Hook;
		void Load_clipMap_ptr(bool atStreamStart)
		{
			auto varclipMap_ptr = *reinterpret_cast<clipMap_t***>(0x82CE61F8);

			Load_clipMap_ptr_Hook.Invoke<void>(atStreamStart);

			if (varclipMap_ptr && *varclipMap_ptr)
			{
				if (IniConfig::EnableClipMapDumper)
					Dump_ClipMap(*varclipMap_ptr);
				//if (IniConfig::EnableClipMapLoader)
				//	Load_AudioVolumeSetting(*varclipMap_ptr);
			}
		}

		void Load()
		{
			Load_clipMap_ptr_Hook.Create(0x82327BC0, Load_clipMap_ptr);
		}

		void Unload()
		{
			Load_clipMap_ptr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{

	}
#endif
}
