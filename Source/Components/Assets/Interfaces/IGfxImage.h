#pragma once

namespace IGfxImage
{
	union GfxTexture
	{
		D3DBaseTexture basemap;
		D3DLineTexture linemap;
		D3DTexture map;
		D3DVolumeTexture volmap;
		D3DCubeTexture cubemap;
	};

	struct CardMemory
	{
		int platform[1];
	};

	struct GfxImageStreamData
	{
		unsigned short width;
		unsigned short height;
		unsigned int pixelSize;
	};

	struct GfxImage
	{
		GfxTexture texture;
		int format;
		unsigned char mapType;
		unsigned char semantic;
		unsigned char category;
		CardMemory cardMemory;
		unsigned short width;
		unsigned short height;
		unsigned short depth;
		unsigned char levelCount;
		unsigned char cached;
		unsigned char* pixels;
		GfxImageStreamData streams[4];
		const char* name;
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
