#pragma once

#include "IMaterial.h"

namespace IFont
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
		void Load();
		void Unload();
	}
#elif IS_SP
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
