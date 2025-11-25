#pragma once

namespace IMaterialVertexDeclaration
{
	struct MaterialStreamRouting
	{
		unsigned char source;
		unsigned char dest;
	};

	union MaterialVertexStreamRouting
	{
		MaterialStreamRouting data[13];
		D3DVertexDeclaration* decl[17];
	};

	struct MaterialVertexDeclaration
	{
		unsigned char streamCount;
		bool hasOptionalSource;
		MaterialVertexStreamRouting routing;
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
