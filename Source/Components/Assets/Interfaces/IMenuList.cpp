namespace IMenuList
{
	struct menuData_t
	{/*
		unsigned int menuFlags;
		int fadeCycle;
		float fadeClamp;
		float fadeAmount;
		float fadeInAmount;
		float blurRadius;
		EScreenLayer screenLayer;
		MenuEventHandlerSet *onOpen;
		MenuEventHandlerSet *onCloseRequest;
		MenuEventHandlerSet *onClose;
		MenuEventHandlerSet *onESC;
		ItemKeyHandler *onKey;
		Statement_s *visibleExp;
		const char *allowedBinding;
		const char *soundName;
		float focusColor[4];
		Statement_s *rectXExp;
		Statement_s *rectYExp;
		Statement_s *rectWExp;
		Statement_s *rectHExp;
		Statement_s *openSoundExp;
		Statement_s *closeSoundExp;
		int cursorItem[4];
		menuTransition scaleTransition[4];
		menuTransition alphaTransition[4];
		menuTransition xTransition[4];
		menuTransition yTransition[4];
		ExpressionSupportingData *expressionData;*/
	};

	struct Material;

	struct rectDef_s
	{
		float x;
		float y;
		float w;
		float h;
		unsigned char horzAlign;
		unsigned char vertAlign;
	};

	struct windowDef_t
	{
		const char* name;
		rectDef_s rect;
		rectDef_s rectClient;
		const char* group;
		int style;
		int border;
		int ownerDraw;
		int ownerDrawFlags;
		float borderSize;
		int staticFlags;
		int dynamicFlags[4];
		int nextTime;
		float foreColor[4];
		float backColor[4];
		float borderColor[4];
		float outlineColor[4];
		float disableColor[4];
		Material* background;
	};

	struct itemDef_s
	{/*
		windowDef_t window;
		rectDef_s textRect[4];
		int type;
		int dataType;
		int alignment;
		int fontEnum;
		int textAlignMode;
		float textalignx;
		float textaligny;
		float textscale;
		int textStyle;
		int gameMsgWindowIndex;
		int gameMsgWindowMode;
		const char *text;
		unsigned int itemFlags;
		menuDef_t *parent;
		MenuEventHandlerSet *mouseEnterText;
		MenuEventHandlerSet *mouseExitText;
		MenuEventHandlerSet *mouseEnter;
		MenuEventHandlerSet *mouseExit;
		MenuEventHandlerSet *action;
		MenuEventHandlerSet *accept;
		MenuEventHandlerSet *onFocus;
		MenuEventHandlerSet *leaveFocus;
		MenuEventHandlerSet *onEnter;
		const char *dvar;
		const char *dvarTest;
		ItemKeyHandler *onKey;
		const char *enableDvar;
		const char *localVar;
		int dvarFlags;
		SndAliasList *focusSound;
		float special;
		int cursorPos[4];
		itemDefData_t typeData;
		int floatExpressionCount;
		ItemFloatExpression *floatExpressions;
		Statement_s *visibleExp;
		Statement_s *disabledExp;
		Statement_s *textExp;
		Statement_s *materialExp;
		EScreenLayer screenLayer;
		float glowColor[4];
		int fxBirthTime;
		int fxLetterTime;
		int fxDecayStartTime;
		int fxDecayDuration;
		int lastSoundPlayedTime;
		int animStateCount;
		animParamsDef_t **animStates;
		animParamsDef_t currentAnimState;
		animParamsDef_t *nextAnimState;
		int animStartTime;
		int animDuration;*/
	};

	struct menuDef_t
	{
		menuData_t* data;
		windowDef_t window;
		int itemCount;
		//itemDef_s **items;
	};

	struct MenuList
	{
		const char* name;
		int menuCount;
		menuDef_t** menus;
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
