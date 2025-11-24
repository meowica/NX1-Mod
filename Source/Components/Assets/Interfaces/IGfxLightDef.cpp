#include "IGfxImage.h"

namespace IGfxLightDef
{
	struct GfxLightImage
	{
		IGfxImage::GfxImage* image;
		unsigned char samplerState;
	};

	struct GfxLightDef
	{
		const char* name;
		GfxLightImage attenuation;
		int lmapLookupStart;
	};

#ifdef IS_MP
	namespace MP
	{
		void Dump_GfxLightDef(const GfxLightDef* gfxLightDef)
		{
			if (!gfxLightDef)
				return;

			std::string assetName = gfxLightDef->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\lights\\" + assetName + ".json";

			std::ostringstream json;
			json << "{\n";
			json << "  \"name\": \"" << assetName << "\",\n";
			json << "  \"attenuation\": {\n";
			json << "    \"image\": ";
			json << "\"" << gfxLightDef->attenuation.image->name << "\"";
			json << ",\n";
			json << "    \"samplerState\": " << (unsigned int)gfxLightDef->attenuation.samplerState << "\n";
			json << "  },\n";
			json << "  \"lmapLookupStart\": " << gfxLightDef->lmapLookupStart << "\n";
			json << "}\n";

			const std::string out = json.str();
			Util::FileSystem::WriteFile(outPath.c_str(), out.c_str(), out.size());
		}

		Util::Hook::Detour Load_GfxLightDefPtr_Hook;
		void Load_GfxLightDefPtr(bool atStreamStart)
		{
			auto varGfxLightDefPtr = *reinterpret_cast<GfxLightDef***>(0x82CE5FD8);

			Load_GfxLightDefPtr_Hook.Invoke<void>(atStreamStart);

			if (varGfxLightDefPtr && *varGfxLightDefPtr)
			{
				if (IniConfig::EnableGfxLightDefDumper)
					Dump_GfxLightDef(*varGfxLightDefPtr);
				//if (IniConfig::EnableGfxLightDefLoader)
				//	Load_GfxLightDef(*varGfxLightDefPtr);
			}
		}

		void Load()
		{
			Load_GfxLightDefPtr_Hook.Create(0x82304EE8, Load_GfxLightDefPtr);
		}

		void Unload()
		{
			Load_GfxLightDefPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_GfxLightDef(const GfxLightDef* gfxLightDef)
		{
			if (!gfxLightDef)
				return;

			std::string assetName = gfxLightDef->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\lights\\" + assetName + ".json";

			std::ostringstream json;
			json << "{\n";
			json << "  \"name\": \"" << assetName << "\",\n";
			json << "  \"attenuation\": {\n";
			json << "    \"image\": ";
			json << "\"" << gfxLightDef->attenuation.image->name << "\"";
			json << ",\n";
			json << "    \"samplerState\": " << (unsigned int)gfxLightDef->attenuation.samplerState << "\n";
			json << "  },\n";
			json << "  \"lmapLookupStart\": " << gfxLightDef->lmapLookupStart << "\n";
			json << "}\n";

			const std::string out = json.str();
			Util::FileSystem::WriteFile(outPath.c_str(), out.c_str(), out.size());
		}

		Util::Hook::Detour Load_GfxLightDefPtr_Hook;
		void Load_GfxLightDefPtr(bool atStreamStart)
		{
			auto varGfxLightDefPtr = *reinterpret_cast<GfxLightDef***>(0x82C6D9D8);

			Load_GfxLightDefPtr_Hook.Invoke<void>(atStreamStart);

			if (varGfxLightDefPtr && *varGfxLightDefPtr)
			{
				if (IniConfig::EnableGfxLightDefDumper)
					Dump_GfxLightDef(*varGfxLightDefPtr);
				//if (IniConfig::EnableGfxLightDefLoader)
				//	Load_GfxLightDef(*varGfxLightDefPtr);
			}
		}

		void Load()
		{
			Load_GfxLightDefPtr_Hook.Create(0x8224EB10, Load_GfxLightDefPtr);
		}

		void Unload()
		{
			Load_GfxLightDefPtr_Hook.Clear();
		}
	}
#endif
}
