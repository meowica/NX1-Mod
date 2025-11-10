namespace AssetHandler
{
#ifdef IS_MULTIPLAYER
	namespace Multiplayer
	{
		void* ReallocateAssetPool(uint32_t type, unsigned int newSize)
		{
			int oldSize = Symbols::Multiplayer::DB_GetXAssetSizeHandlers[type]();

			void* poolEntry = malloc(newSize * oldSize);
			Symbols::Multiplayer::DB_XAssetPool[type] = poolEntry;
			Symbols::Multiplayer::g_poolSize[type] = newSize;
			return poolEntry;
		}

		void Load()
		{
			// IW4x limits

			ReallocateAssetPool(Structs::ASSET_TYPE_GAMEWORLD_SP, 1);
			// ReallocateAssetPool(Structs::ASSET_TYPE_IMAGE, 7168); // Causes the game to crash somewhere else, if the default limit is exceeded
			ReallocateAssetPool(Structs::ASSET_TYPE_LOADED_SOUND, 5400);
			ReallocateAssetPool(Structs::ASSET_TYPE_FX, 2400);
			ReallocateAssetPool(Structs::ASSET_TYPE_LOCALIZE_ENTRY, 14000);
			ReallocateAssetPool(Structs::ASSET_TYPE_XANIMPARTS, 16384);
			// ReallocateAssetPool(Structs::ASSET_TYPE_XMODEL, 10250); // Causes the game to crash somewhere else, if the default limit is exceeded
			ReallocateAssetPool(Structs::ASSET_TYPE_PHYSPRESET, 128);
			ReallocateAssetPool(Structs::ASSET_TYPE_PIXELSHADER, 10000);
			// ReallocateAssetPool(Structs::ASSET_TYPE_MATERIAL, 16384); // Causes the game to crash somewhere else, if the default limit is exceeded
			ReallocateAssetPool(Structs::ASSET_TYPE_WEAPON, 2400);
			ReallocateAssetPool(Structs::ASSET_TYPE_STRINGTABLE, 800);
			ReallocateAssetPool(Structs::ASSET_TYPE_IMPACT_FX, 8);
		}

		void Unload()
		{
			// nothing
		}
	}
#elif IS_SINGLEPLAYER
	namespace Singleplayer
	{
		void Load()
		{
			// add soon
		}

		void Unload()
		{
			// nothing
		}
	}
#endif
}
