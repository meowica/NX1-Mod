namespace CustomCommands
{
#ifdef IS_MULTIPLAYER
	namespace Multiplayer
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
			const char* assetName = Symbols::Multiplayer::DB_GetXAssetName(&asset);
			ctx->totalAssets++;

			Symbols::Multiplayer::Com_Printf(0, "%s\n", assetName);
		}

		void Cmd_ListAssetPool_f()
		{
			Util::Command::Args Args;

			if (Args.Size() < 2)
			{
				Symbols::Multiplayer::Com_Printf(0, "listassetpool <poolnumber>: lists all the assets in the specified pool\n");

				for (int i = 0; i < Structs::ASSET_TYPE_COUNT; i++)
				{
					Symbols::Multiplayer::Com_Printf(0, "%d %s\n", i, Symbols::Multiplayer::DB_GetXAssetTypeName(i));
				}
				return;
			}

			const int typeInt = atoi(Args.Get(1));
			if (typeInt < 0 || typeInt >= Structs::ASSET_TYPE_COUNT)
			{
				Symbols::Multiplayer::Com_Printf(0, "Invalid pool, must be between [%d, %d]\n", 0, Structs::ASSET_TYPE_COUNT - 1);
				return;
			}

			const Structs::XAssetType type = static_cast<Structs::XAssetType>(typeInt);
			Symbols::Multiplayer::Com_Printf(16, "Listing assets in %s pool.\n", Symbols::Multiplayer::DB_GetXAssetTypeName(type));

			XAssetListContext ctx;
			ctx.type = type;
			ctx.totalAssets = 0;

			Symbols::Multiplayer::DB_EnumXAssets_Internal(type, &XAssetList_f, &ctx, true);

			Symbols::Multiplayer::Com_Printf(0, "Total of %d assets in %s pool, size %d\n", ctx.totalAssets, Symbols::Multiplayer::DB_GetXAssetTypeName(type), Symbols::Multiplayer::DB_GetXAssetTypeSize(type));
		}

		void Load()
		{
			Util::Command::Add("listassetpool", Cmd_ListAssetPool_f);
		}

		void Unload()
		{
			// nothing
		}
	}
#elif IS_SINGLEPLAYER
	namespace Singleplayer
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
			const char* assetName = Symbols::Singleplayer::DB_GetXAssetName(&asset);
			ctx->totalAssets++;

			Symbols::Singleplayer::Com_Printf(0, "%s\n", assetName);
		}

		void Cmd_ListAssetPool_f()
		{
			Util::Command::Args Args;

			if (Args.Size() < 2)
			{
				Symbols::Singleplayer::Com_Printf(0, "listassetpool <poolnumber>: lists all the assets in the specified pool\n");

				for (int i = 0; i < Structs::ASSET_TYPE_COUNT; i++)
				{
					Symbols::Singleplayer::Com_Printf(0, "%d %s\n", i, Symbols::Singleplayer::DB_GetXAssetTypeName(i));
				}
				return;
			}

			const int typeInt = atoi(Args.Get(1));
			if (typeInt < 0 || typeInt >= Structs::ASSET_TYPE_COUNT)
			{
				Symbols::Singleplayer::Com_Printf(0, "Invalid pool, must be between [%d, %d]\n", 0, Structs::ASSET_TYPE_COUNT - 1);
				return;
			}

			const Structs::XAssetType type = static_cast<Structs::XAssetType>(typeInt);
			Symbols::Singleplayer::Com_Printf(16, "Listing assets in %s pool.\n", Symbols::Singleplayer::DB_GetXAssetTypeName(type));

			XAssetListContext ctx;
			ctx.type = type;
			ctx.totalAssets = 0;

			Symbols::Singleplayer::DB_EnumXAssets_Internal(type, &XAssetList_f, &ctx, true);

			Symbols::Singleplayer::Com_Printf(0, "Total of %d assets in %s pool, size %d\n", ctx.totalAssets, Symbols::Singleplayer::DB_GetXAssetTypeName(type), Symbols::Singleplayer::DB_GetXAssetTypeSize(type));
		}

		void Load()
		{
			Util::Command::Add("listassetpool", Cmd_ListAssetPool_f);
		}

		void Unload()
		{
			// nothing
		}
	}
#endif // IS_SINGLEPLAYER
}
