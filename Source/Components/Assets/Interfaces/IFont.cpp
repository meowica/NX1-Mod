#include "IFont.h"

namespace IFont
{
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

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"fontName\": \"" << assetName << "\",\n";
			oss << "  \"pixelHeight\": " << font->pixelHeight << ",\n";
			oss << "  \"glyphCount\": " << font->glyphCount << ",\n";
			oss << "  \"material\": \"" << font->material->info.name << "\",\n";
			oss << "  \"glowMaterial\": \"" << font->glowMaterial->info.name << "\",\n";
			oss << "  \"glyphs\": [\n";

			for (int i = 0; i < font->glyphCount; ++i)
			{
				const Glyph& g = font->glyphs[i];
				oss << "    {\n";
				oss << "      \"letter\": " << g.letter << ",\n";
				oss << "      \"x0\": " << static_cast<int>(g.x0) << ",\n";
				oss << "      \"y0\": " << static_cast<int>(g.y0) << ",\n";
				oss << "      \"dx\": " << static_cast<int>(g.dx) << ",\n";
				oss << "      \"pixelWidth\": " << static_cast<int>(g.pixelWidth) << ",\n";
				oss << "      \"pixelHeight\": " << static_cast<int>(g.pixelHeight) << ",\n";
				oss << std::fixed << std::setprecision(6);
				oss << "      \"s0\": " << g.s0 << ",\n";
				oss << "      \"t0\": " << g.t0 << ",\n";
				oss << "      \"s1\": " << g.s1 << ",\n";
				oss << "      \"t1\": " << g.t1 << "\n";
				oss << "    }";

				if (i < font->glyphCount - 1)
					oss << ",";
				oss << "\n";
			}

			oss << "  ]\n";
			oss << "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), oss.str().c_str(), oss.str().size());
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

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName + ".json";

			std::ostringstream oss;
			oss << "{\n";
			oss << "  \"fontName\": \"" << assetName << "\",\n";
			oss << "  \"pixelHeight\": " << font->pixelHeight << ",\n";
			oss << "  \"glyphCount\": " << font->glyphCount << ",\n";
			oss << "  \"material\": \"" << font->material->info.name << "\",\n";
			oss << "  \"glowMaterial\": \"" << font->glowMaterial->info.name << "\",\n";
			oss << "  \"glyphs\": [\n";

			for (int i = 0; i < font->glyphCount; ++i)
			{
				const Glyph& g = font->glyphs[i];
				oss << "    {\n";
				oss << "      \"letter\": " << g.letter << ",\n";
				oss << "      \"x0\": " << static_cast<int>(g.x0) << ",\n";
				oss << "      \"y0\": " << static_cast<int>(g.y0) << ",\n";
				oss << "      \"dx\": " << static_cast<int>(g.dx) << ",\n";
				oss << "      \"pixelWidth\": " << static_cast<int>(g.pixelWidth) << ",\n";
				oss << "      \"pixelHeight\": " << static_cast<int>(g.pixelHeight) << ",\n";
				oss << std::fixed << std::setprecision(6);
				oss << "      \"s0\": " << g.s0 << ",\n";
				oss << "      \"t0\": " << g.t0 << ",\n";
				oss << "      \"s1\": " << g.s1 << ",\n";
				oss << "      \"t1\": " << g.t1 << "\n";
				oss << "    }";

				if (i < font->glyphCount - 1)
					oss << ",";
				oss << "\n";
			}

			oss << "  ]\n";
			oss << "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), oss.str().c_str(), oss.str().size());
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
