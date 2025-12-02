#include "IMenuList.h"

namespace IMenuList
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_MenuList(const MenuList* menuList)
		{
			if (!menuList)
				return;

			std::string assetName = menuList->name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			std::ostringstream oss;
			oss << "{\n";

			if (!menuList->menus && menuList->menuCount < 0)
				return;

			std::string prefix = menuList->name;
			const size_t p = prefix.find_first_of("/\\");
			if (p != std::string::npos)
				prefix = prefix.substr(0, p + 1);  // keep the slash
			else
				prefix.clear();

			for (int i = 0; i < menuList->menuCount; i++)
			{
				const auto* menu = menuList->menus[i];
				if (!menu)
					continue;

				const char* rawName = menu->window.name;
				if (!rawName || !rawName[0])
					continue;

				std::string cleanName(rawName);

				const size_t dot = cleanName.rfind('.');
				if (dot != std::string::npos && cleanName.compare(dot, 5, ".menu") == 0)
					cleanName = cleanName.substr(0, dot);

				oss << "\tloadMenu { \""
					<< prefix
					<< cleanName
					<< ".menu\" }\n";
			}

			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
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

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			std::ostringstream oss;
			oss << "{\n";

			if (!menuList->menus && menuList->menuCount < 0)
				return;

			std::string prefix = menuList->name;
			const size_t p = prefix.find_first_of("/\\");
			if (p != std::string::npos)
				prefix = prefix.substr(0, p + 1);  // keep the slash
			else
				prefix.clear();

			for (int i = 0; i < menuList->menuCount; i++)
			{
				const auto* menu = menuList->menus[i];
				if (!menu)
					continue;

				const char* rawName = menu->window.name;
				if (!rawName || !rawName[0])
					continue;

				std::string cleanName(rawName);

				const size_t dot = cleanName.rfind('.');
				if (dot != std::string::npos && cleanName.compare(dot, 5, ".menu") == 0)
					cleanName = cleanName.substr(0, dot);

				oss << "\tloadMenu { \""
					<< prefix
					<< cleanName
					<< ".menu\" }\n";
			}

			oss << "}\n";

			std::string outStr = oss.str();
			Util::FileSystem::WriteFile(outPath.c_str(), outStr.c_str(), outStr.size());
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
