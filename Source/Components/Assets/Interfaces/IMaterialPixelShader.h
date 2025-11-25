#pragma once

namespace IMaterialPixelShader
{
	struct GfxShaderLoadDef
	{
		unsigned char* cachedPart;
		unsigned char* physicalPart;
		unsigned short cachedPartSize;
		unsigned short physicalPartSize;
	};

	union MaterialPixelShaderProgram
	{
		D3DPixelShader* ps;
		GfxShaderLoadDef loadDef;
	};

	struct MaterialPixelShader
	{
		const char* name;
		MaterialPixelShaderProgram prog;
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
