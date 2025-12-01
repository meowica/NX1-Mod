#include "IGfxWorld.h"

namespace IGfxWorld
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_GfxWorld(const GfxWorld* gfxWorld)
		{
			if (!gfxWorld)
				return;

			std::string assetName = gfxWorld->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".gfxworld.json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"name\": \"" << gfxWorld->name << "\",\n";
			oss << "  \"baseName\": \"" << gfxWorld->baseName << "\",\n";
			oss << "  \"planeCount\": " << gfxWorld->planeCount << ",\n";
			oss << "  \"nodeCount\": " << gfxWorld->nodeCount << ",\n";
			oss << "  \"surfaceCount\": " << gfxWorld->surfaceCount << ",\n";
			oss << "  \"skyBoxModel\": \"" << gfxWorld->skyBoxModel << "\",\n";
			oss << "  \"modelCount\": " << gfxWorld->modelCount << ",\n";
			oss << "  \"bounds\": {\n";
			oss << "    \"midPoint\": ["
				<< gfxWorld->bounds.midPoint[0] << ", "
				<< gfxWorld->bounds.midPoint[1] << ", "
				<< gfxWorld->bounds.midPoint[2] << "],\n";
			oss << "    \"halfSize\": ["
				<< gfxWorld->bounds.halfSize[0] << ", "
				<< gfxWorld->bounds.halfSize[1] << ", "
				<< gfxWorld->bounds.halfSize[2] << "]\n";
			oss << "  },\n";
			oss << "  \"skies\": [\n";
			for (int i = 0; i < gfxWorld->skyCount; ++i)
			{
				const GfxSky& sky = gfxWorld->skies[i];
				oss << "    {\n";
				oss << "      \"skySurfCount\": " << sky.skySurfCount << ",\n";
				oss << "      \"skyStartSurfs\": \"" << sky.skyStartSurfs << "\",\n";
				oss << "      \"skyImage\": \"" << sky.skyImage->name << "\",\n";
				oss << "      \"skySamplerState\": " << static_cast<int>(sky.skySamplerState) << "\n";
				oss << "    }" << (i + 1 < gfxWorld->skyCount ? "," : "") << "\n";
			}
			oss << "  ],\n";
			oss << "  \"sunflare\": {\n";
			oss << "    \"hasValidData\": " << ((gfxWorld->sun.hasValidData) ? "true" : "false") << ",\n";
			oss << "    \"spriteMaterial\": \"" << gfxWorld->sun.spriteMaterial->info.name << "\",\n";
			oss << "    \"flareMaterial\": \"" << gfxWorld->sun.flareMaterial->info.name << "\",\n";
			oss << "    \"spriteSize\": " << gfxWorld->sun.spriteSize << ",\n";
			oss << "    \"flareMinSize\": " << gfxWorld->sun.flareMinSize << ",\n";
			oss << "    \"flareMinDot\": " << gfxWorld->sun.flareMinDot << ",\n";
			oss << "    \"flareMaxSize\": " << gfxWorld->sun.flareMaxSize << ",\n";
			oss << "    \"flareMaxDot\": " << gfxWorld->sun.flareMaxDot << ",\n";
			oss << "    \"flareMaxAlpha\": " << gfxWorld->sun.flareMaxAlpha << ",\n";
			oss << "    \"flareFadeInTime\": " << gfxWorld->sun.flareFadeInTime << ",\n";
			oss << "    \"flareFadeOutTime\": " << gfxWorld->sun.flareFadeOutTime << ",\n";
			oss << "    \"blindMinDot\": " << gfxWorld->sun.blindMinDot << ",\n";
			oss << "    \"blindMaxDot\": " << gfxWorld->sun.blindMaxDot << ",\n";
			oss << "    \"blindMaxDarken\": " << gfxWorld->sun.blindMaxDarken << ",\n";
			oss << "    \"blindFadeInTime\": " << gfxWorld->sun.blindFadeInTime << ",\n";
			oss << "    \"blindFadeOutTime\": " << gfxWorld->sun.blindFadeOutTime << ",\n";
			oss << "    \"glareMinDot\": " << gfxWorld->sun.glareMinDot << ",\n";
			oss << "    \"glareMaxDot\": " << gfxWorld->sun.glareMaxDot << ",\n";
			oss << "    \"glareMaxLighten\": " << gfxWorld->sun.glareMaxLighten << ",\n";
			oss << "    \"glareFadeInTime\": " << gfxWorld->sun.glareFadeInTime << ",\n";
			oss << "    \"glareFadeOutTime\": " << gfxWorld->sun.glareFadeOutTime << ",\n";
			oss << "    \"sunFxPosition\": ["
				<< gfxWorld->sun.sunFxPosition[0] << ", "
				<< gfxWorld->sun.sunFxPosition[1] << ", "
				<< gfxWorld->sun.sunFxPosition[2] << "]\n";
			oss << "  }\n";
			oss << "}";

			Util::FileSystem::WriteFile(outPath.c_str(), oss.str().c_str(), oss.str().size());
		}

		Util::Hook::Detour Load_GfxWorldPtr_Hook;
		void Load_GfxWorldPtr(bool atStreamStart)
		{
			auto varGfxWorldPtr = *reinterpret_cast<GfxWorld***>(0x82CE6C2C);

			Load_GfxWorldPtr_Hook.Invoke<void>(atStreamStart);

			if (varGfxWorldPtr && *varGfxWorldPtr)
			{
				if (IniConfig::EnableGfxWorldDumper)
					Dump_GfxWorld(*varGfxWorldPtr);
				//if (IniConfig::EnableGfxWorldLoader)
				//	Load_GfxWorld(*varGfxWorldPtr);
			}
		}

		void Load()
		{
			Load_GfxWorldPtr_Hook.Create(0x8232E080, Load_GfxWorldPtr);
		}

		void Unload()
		{
			Load_GfxWorldPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{

	}
#endif
}
