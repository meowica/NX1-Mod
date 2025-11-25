#pragma once

#include "IMenuDef.h"

namespace IMenuList
{
	struct MenuList
	{
		const char* name;
		int menuCount;
		IMenuDef::menuDef_t** menus;
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
