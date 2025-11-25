#pragma once

namespace IMaterialVertexShader
{
	struct GfxShaderLoadDef
	{
		unsigned char* cachedPart;
		unsigned char* physicalPart;
		unsigned short cachedPartSize;
		unsigned short physicalPartSize;
	};

	union MaterialVertexShaderProgram
	{
		D3DVertexShader* vs;
		GfxShaderLoadDef loadDef;
	};

	struct MaterialVertexShader
	{
		const char* name;
		MaterialVertexShaderProgram prog;
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
