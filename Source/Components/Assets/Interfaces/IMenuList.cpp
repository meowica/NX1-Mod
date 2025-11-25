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
		void Dump_MenuList(const MenuList* menuList)
		{
			if (!menuList)
				return;

			std::string assetName = menuList->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\menus\\" + assetName;

			std::string buffer;

			buffer += "{\n";

			if (menuList->menus)
			{
				std::string path = menuList->name;

				if (path.find_first_of("/\\") != std::string::npos)
				{
					path = path.substr(0, path.find_first_of("/\\") + 1);
				}
				else
				{
					path = "";
				}

				for (int i = 0; i < menuList->menuCount; i++)
				{
					if (menuList->menus[i])
					{
						// start bad
						const char* rawName = menuList->menus[i]->window.name;
						if (!rawName || !rawName[0])
							continue;

						std::string cleanName(rawName);
						size_t nullpos = cleanName.find('\0');
						if (nullpos != std::string::npos)
							cleanName.resize(nullpos);
						//end bad

						buffer += Util::String::VA("\tloadMenu { \"%s%s.menu\" }\n", path.c_str(), cleanName.c_str());
					}
				}
			}

			buffer += "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), buffer.c_str(), buffer.size());
		}

		Util::Hook::Detour Load_MenuListPtr_Hook;
		void Load_MenuListPtr(bool atStreamStart)
		{
			auto varMenuListPtr = *reinterpret_cast<MenuList***>(0x82CE60F4);

			Load_MenuListPtr_Hook.Invoke<void>(atStreamStart);

			if (varMenuListPtr && *varMenuListPtr)
			{
				if (IniConfig::EnableMenuListDumper)
					Dump_MenuList(*varMenuListPtr);
				//if (IniConfig::EnableMenuListLoader)
				//	Load_MenuList(*varMenuListPtr);
			}
		}

		void Load()
		{
			Load_MenuListPtr_Hook.Create(0x82334098, Load_MenuListPtr);
		}

		void Unload()
		{
			Load_MenuListPtr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_MenuList(const MenuList* menuList)
		{
			if (!menuList)
				return;

			std::string assetName = menuList->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\menus\\" + assetName;

			std::string buffer;

			buffer += "{\n";

			if (menuList->menus)
			{
				std::string path = menuList->name;

				if (path.find_first_of("/\\") != std::string::npos)
				{
					path = path.substr(0, path.find_first_of("/\\") + 1);
				}
				else
				{
					path = "";
				}

				for (int i = 0; i < menuList->menuCount; i++)
				{
					if (menuList->menus[i])
					{
						const char* rawName = menuList->menus[i]->window.name;
						if (!rawName || !rawName[0])
							continue;
						std::string cleanName(rawName);
						size_t nullpos = cleanName.find('\0');
						if (nullpos != std::string::npos)
							cleanName.resize(nullpos);
						buffer += Util::String::VA("\tloadMenu { \"%s%s.menu\" }\n", path.c_str(), cleanName.c_str());
					}
				}
			}

			buffer += "}\n";

			Util::FileSystem::WriteFile(outPath.c_str(), buffer.c_str(), buffer.size());
		}

		Util::Hook::Detour Load_MenuListPtr_Hook;
		void Load_MenuListPtr(bool atStreamStart)
		{
			auto varMenuListPtr = *reinterpret_cast<MenuList***>(0x82C6DAF4);

			Load_MenuListPtr_Hook.Invoke<void>(atStreamStart);

			if (varMenuListPtr && *varMenuListPtr)
			{
				if (IniConfig::EnableMenuListDumper)
					Dump_MenuList(*varMenuListPtr);
				//if (IniConfig::EnableMenuListLoader)
				//	Load_MenuList(*varMenuListPtr);
			}
		}

		void Load()
		{
			Load_MenuListPtr_Hook.Create(0x8227DD08, Load_MenuListPtr);
		}

		void Unload()
		{
			Load_MenuListPtr_Hook.Clear();
		}
	}
#endif
}
