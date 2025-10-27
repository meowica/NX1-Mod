namespace CustomCommands
{
#ifdef MP_MOD
	namespace MP
	{
		struct XAssetListContext
		{
			Structs::XAssetType type;
			int totalAssets;
		};

		void XAssetList_f(Structs::XAssetHeader header, void* inData)
		{
			XAssetListContext* ctx = static_cast<XAssetListContext*>(inData);
			if (!ctx)
				return;

			const Structs::XAsset asset = { ctx->type, header };
			const char* assetName = Symbols::MP::DB_GetXAssetName(&asset);
			ctx->totalAssets++;

			Symbols::MP::Com_Printf(0, "%s\n", assetName);
		}

		void Cmd_ListAssetPool_f()
		{
			Util::Command::Args Args;

			if (Args.Size() < 2)
			{
				Symbols::MP::Com_Printf(0, "listassetpool <poolnumber>: lists all the assets in the specified pool\n");

				for (int i = 0; i < Structs::ASSET_TYPE_COUNT; i++)
				{
					Symbols::MP::Com_Printf(0, "%d %s\n", i, Symbols::MP::DB_GetXAssetTypeName(i));
				}
				return;
			}

			const int typeInt = atoi(Args.Get(1));
			if (typeInt < 0 || typeInt >= Structs::ASSET_TYPE_COUNT)
			{
				Symbols::MP::Com_Printf(0, "Invalid pool, must be between [%d, %d]\n", 0, Structs::ASSET_TYPE_COUNT - 1);
				return;
			}

			const Structs::XAssetType type = static_cast<Structs::XAssetType>(typeInt);
			Symbols::MP::Com_Printf(16, "Listing assets in %s pool.\n", Symbols::MP::DB_GetXAssetTypeName(type));

			XAssetListContext ctx;
			ctx.type = type;
			ctx.totalAssets = 0;

			Symbols::MP::DB_EnumXAssets_Internal(type, &XAssetList_f, &ctx, true);

			Symbols::MP::Com_Printf(0, "Total of %d assets in %s pool, size %d\n", ctx.totalAssets, Symbols::MP::DB_GetXAssetTypeName(type), Symbols::MP::DB_GetXAssetTypeSize(type));
		}

		void AddCommands()
		{
			Util::Command::Add("listassetpool", Cmd_ListAssetPool_f);
		}

		Util::Hook::Detour Cmd_Init_Hook;
		void Cmd_Init()
		{
			auto Invoke = Cmd_Init_Hook.Invoke<void(*)()>();
			Invoke();

			AddCommands();
		}

		void Hooks()
		{
			Cmd_Init_Hook.Create(0x82438AD0, Cmd_Init);
		}

		void ClearHooks()
		{
			Cmd_Init_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#elif SP_MOD
	namespace SP
	{
		struct XAssetListContext
		{
			Structs::XAssetType type;
			int totalAssets;
		};

		void XAssetList_f(Structs::XAssetHeader header, void* inData)
		{
			XAssetListContext* ctx = static_cast<XAssetListContext*>(inData);
			if (!ctx)
				return;

			const Structs::XAsset asset = { ctx->type, header };
			const char* assetName = Symbols::SP::DB_GetXAssetName(&asset);
			ctx->totalAssets++;

			Symbols::SP::Com_Printf(0, "%s\n", assetName);
		}

		void Cmd_ListAssetPool_f()
		{
			Util::Command::Args Args;

			if (Args.Size() < 2)
			{
				Symbols::SP::Com_Printf(0, "listassetpool <poolnumber>: lists all the assets in the specified pool\n");

				for (int i = 0; i < Structs::ASSET_TYPE_COUNT; i++)
				{
					Symbols::SP::Com_Printf(0, "%d %s\n", i, Symbols::SP::DB_GetXAssetTypeName(i));
				}
				return;
			}

			const int typeInt = atoi(Args.Get(1));
			if (typeInt < 0 || typeInt >= Structs::ASSET_TYPE_COUNT)
			{
				Symbols::SP::Com_Printf(0, "Invalid pool, must be between [%d, %d]\n", 0, Structs::ASSET_TYPE_COUNT - 1);
				return;
			}

			const Structs::XAssetType type = static_cast<Structs::XAssetType>(typeInt);
			Symbols::SP::Com_Printf(16, "Listing assets in %s pool.\n", Symbols::SP::DB_GetXAssetTypeName(type));

			XAssetListContext ctx;
			ctx.type = type;
			ctx.totalAssets = 0;

			Symbols::SP::DB_EnumXAssets_Internal(type, &XAssetList_f, &ctx, true);

			Symbols::SP::Com_Printf(0, "Total of %d assets in %s pool, size %d\n", ctx.totalAssets, Symbols::SP::DB_GetXAssetTypeName(type), Symbols::SP::DB_GetXAssetTypeSize(type));
		}

		void AddCommands()
		{
			Util::Command::Add("listassetpool", Cmd_ListAssetPool_f);
		}

		Util::Hook::Detour Cmd_Init_Hook;
		void Cmd_Init()
		{
			auto Invoke = Cmd_Init_Hook.Invoke<void(*)()>();
			Invoke();

			AddCommands();
		}

		void Hooks()
		{
			Cmd_Init_Hook.Create(0x82423308, Cmd_Init);
		}

		void ClearHooks()
		{
			Cmd_Init_Hook.Clear();
		}

		void Load()
		{
			Hooks();
		}

		void Unload()
		{
			ClearHooks();
		}
	}
#endif
}
