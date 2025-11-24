#include "IMaterial.h"

namespace IFont_s
{
	struct Glyph
	{
		unsigned short letter;
		char x0;
		char y0;
		unsigned char dx;
		unsigned char pixelWidth;
		unsigned char pixelHeight;
		float s0;
		float t0;
		float s1;
		float t1;
	};

	struct Font_s
	{
		const char* fontName;
		int pixelHeight;
		int glyphCount;
		IMaterial::Material* material;
		IMaterial::Material* glowMaterial;
		Glyph* glyphs;
	};

#ifdef IS_MP
	namespace MP
	{
		void Dump_FontHandle(const Font_s* font)
		{
			if (!font)
				return;

			std::string assetName = font->fontName;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');
			std::transform(assetName.begin(), assetName.end(), assetName.begin(), ::tolower);

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".json";

			std::ostringstream json;
			json << "{\n";
			json << "  \"fontName\": \"" << assetName << "\",\n";
			json << "  \"pixelHeight\": " << font->pixelHeight << ",\n";
			json << "  \"glyphCount\": " << font->glyphCount << ",\n";
			json << "  \"material\": \"" << font->material->info.name << "\",\n";
			json << "  \"glowMaterial\": \"" << font->glowMaterial->info.name << "\",\n";
			json << "  \"glyphs\": [\n";

			for (int i = 0; i < font->glyphCount; ++i)
			{
				const Glyph& g = font->glyphs[i];
				json << "    {\n";
				json << "      \"letter\": " << g.letter << ",\n";
				json << "      \"x0\": " << static_cast<int>(g.x0) << ",\n";
				json << "      \"y0\": " << static_cast<int>(g.y0) << ",\n";
				json << "      \"dx\": " << static_cast<int>(g.dx) << ",\n";
				json << "      \"pixelWidth\": " << static_cast<int>(g.pixelWidth) << ",\n";
				json << "      \"pixelHeight\": " << static_cast<int>(g.pixelHeight) << ",\n";
				json << std::fixed << std::setprecision(6);
				json << "      \"s0\": " << g.s0 << ",\n";
				json << "      \"t0\": " << g.t0 << ",\n";
				json << "      \"s1\": " << g.s1 << ",\n";
				json << "      \"t1\": " << g.t1 << "\n";
				json << "    }";

				if (i < font->glyphCount - 1)
					json << ",";
				json << "\n";
			}

			json << "  ]\n";
			json << "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), json.str().c_str(), json.str().size());
		}

		Util::Hook::Detour Load_FontHandle_Hook;
		void Load_FontHandle(bool atStreamStart)
		{
			auto varFontHandle = *reinterpret_cast<Font_s***>(0x82CE66B4);

			Load_FontHandle_Hook.Invoke<void>(atStreamStart);

			if (varFontHandle && *varFontHandle)
			{
				if (IniConfig::EnableFontHandleDumper)
					Dump_FontHandle(*varFontHandle);
				//if (IniConfig::EnableFontHandleLoader)
				//	Load_FontHandle(*varFontHandle);
			}
		}

		void Load()
		{
			Load_FontHandle_Hook.Create(0x82321E00, Load_FontHandle);
		}

		void Unload()
		{
			Load_FontHandle_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_FontHandle(const Font_s* font)
		{
			if (!font)
				return;

			std::string assetName = font->fontName;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');
			std::transform(assetName.begin(), assetName.end(), assetName.begin(), ::tolower);

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\fonts\\" + assetName + ".json";

			std::ostringstream json;
			json << "{\n";
			json << "  \"fontName\": \"" << assetName << "\",\n";
			json << "  \"pixelHeight\": " << font->pixelHeight << ",\n";
			json << "  \"glyphCount\": " << font->glyphCount << ",\n";
			json << "  \"material\": \"" << font->material->info.name << "\",\n";
			json << "  \"glowMaterial\": \"" << font->glowMaterial->info.name << "\",\n";
			json << "  \"glyphs\": [\n";

			for (int i = 0; i < font->glyphCount; ++i)
			{
				const Glyph& g = font->glyphs[i];
				json << "    {\n";
				json << "      \"letter\": " << g.letter << ",\n";
				json << "      \"x0\": " << static_cast<int>(g.x0) << ",\n";
				json << "      \"y0\": " << static_cast<int>(g.y0) << ",\n";
				json << "      \"dx\": " << static_cast<int>(g.dx) << ",\n";
				json << "      \"pixelWidth\": " << static_cast<int>(g.pixelWidth) << ",\n";
				json << "      \"pixelHeight\": " << static_cast<int>(g.pixelHeight) << ",\n";
				json << std::fixed << std::setprecision(6);
				json << "      \"s0\": " << g.s0 << ",\n";
				json << "      \"t0\": " << g.t0 << ",\n";
				json << "      \"s1\": " << g.s1 << ",\n";
				json << "      \"t1\": " << g.t1 << "\n";
				json << "    }";
				if (i < font->glyphCount - 1)
					json << ",";
				json << "\n";
			}

			json << "  ]\n";
			json << "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), json.str().c_str(), json.str().size());
		}

		Util::Hook::Detour Load_FontHandle_Hook;
		void Load_FontHandle(bool atStreamStart)
		{
			auto varFontHandle = *reinterpret_cast<Font_s***>(0x82C6E0B4);

			Load_FontHandle_Hook.Invoke<void>(atStreamStart);

			if (varFontHandle && *varFontHandle)
			{
				if (IniConfig::EnableFontHandleDumper)
					Dump_FontHandle(*varFontHandle);
				//if (IniConfig::EnableFontHandleLoader)
				//	Load_FontHandle(*varFontHandle);
			}
		}

		void Load()
		{
			Load_FontHandle_Hook.Create(0x8226BA28, Load_FontHandle);
		}

		void Unload()
		{
			Load_FontHandle_Hook.Clear();
		}
	}
#endif
}
