#pragma once

namespace ISndAliasList
{
	struct SndAliasList
	{
		const char* p_aliasName;
		/*SndAlias* p_head;*/
		int count;
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
