#pragma once

namespace ILocalizeEntry
{
	struct LocalizeEntry
	{
		const char* value;
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
#pragma once
