#pragma once

namespace IRawFile
{
	struct RawFile
	{
		const char* name;
		int compressedLen;
		int len;
		const char* buffer;
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
