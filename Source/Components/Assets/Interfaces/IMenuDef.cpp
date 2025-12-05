#include "IMenuDef.h"

namespace IMenuDef
{
#ifdef IS_MP
	namespace MP
	{
		void Dump_MenuDef(const menuDef_t* menuDef)
		{
			if (!menuDef)
				return;

			std::string assetName = menuDef->window.name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			Util::FileSystem::WriteFile(outPath.c_str(), "no", 2);
		}

		Util::Hook::Detour Load_menuDef_ptr_Hook;
		void Load_menuDef_ptr(bool atStreamStart)
		{
			auto varmenuDef_ptr = *reinterpret_cast<menuDef_t***>(0x82CE682C);

			Load_menuDef_ptr_Hook.Invoke<void>(atStreamStart);

			if (varmenuDef_ptr && *varmenuDef_ptr)
			{
				if (IniConfig::EnableMenuDefDumper)
					Dump_MenuDef(*varmenuDef_ptr);
				//if (IniConfig::EnableLeaderboardDefLoader)
				//	Load_MenuDef(*varmenuDef_ptr);
			}
		}

		void Load()
		{
			Load_menuDef_ptr_Hook.Create(0x82333920, Load_menuDef_ptr);
		}

		void Unload()
		{
			Load_menuDef_ptr_Hook.Clear();
		}
	}
#elif IS_SP
	namespace SP
	{
		void Dump_MenuDef(const menuDef_t* menuDef)
		{
			if (!menuDef)
				return;

			std::string assetName = menuDef->window.name;
			std::replace(assetName.begin(), assetName.end(), '/', '\\');

			std::string outPath = "game:\\" BASE_FOLDER "\\dump\\" + assetName;

			Util::FileSystem::WriteFile(outPath.c_str(), "no", 2);
		}

		Util::Hook::Detour Load_menuDef_ptr_Hook;
		void Load_menuDef_ptr(bool atStreamStart)
		{
			auto varmenuDef_ptr = *reinterpret_cast<menuDef_t***>(0x82C6E22C);

			Load_menuDef_ptr_Hook.Invoke<void>(atStreamStart);

			if (varmenuDef_ptr && *varmenuDef_ptr)
			{
				if (IniConfig::EnableMenuDefDumper)
					Dump_MenuDef(*varmenuDef_ptr);
				//if (IniConfig::EnableLeaderboardDefLoader)
				//	Load_MenuDef(*varmenuDef_ptr);
			}
		}

		void Load()
		{
			Load_menuDef_ptr_Hook.Create(0x8227D590, Load_menuDef_ptr);
		}

		void Unload()
		{
			Load_menuDef_ptr_Hook.Clear();
		}
	}
#endif
}
