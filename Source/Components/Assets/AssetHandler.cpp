// Interfaces
#include "Interfaces\IPhysPreset.h"
#include "Interfaces\IMaterial.h"
#include "Interfaces\ISndVfCurve.h"
#include "Interfaces\IClipMap.h"
#include "Interfaces\IComWorld.h"
#include "Interfaces\IGameWorldSp.h"
#include "Interfaces\IGameWorldMp.h"
#include "Interfaces\IMapEnts.h"
#include "Interfaces\IFxWorld.h"
#include "Interfaces\IGfxWorld.h"
#include "Interfaces\IGfxLightDef.h"
#include "Interfaces\IFont.h"
#include "Interfaces\IMenuList.h"
#include "Interfaces\ILocalizeEntry.h"
#include "Interfaces\ISndDriverGlobals.h"
#include "Interfaces\IRawFile.h"
#include "Interfaces\IStringTable.h"
#include "Interfaces\ILeaderboardDef.h"
#include "Interfaces\IStructuredDataDefSet.h"
#include "Interfaces\ITracerDef.h"
#include "Interfaces\ILaserDef.h"
//VehicleDef
#include "Interfaces\IAddonMapEnts.h"
#include "Interfaces\IShellShockParams.h"
#include "Interfaces\IAudioVolumeSetting.h"
#include "Interfaces\IRadVerbPreset.h"
#include "Interfaces\IFogDef.h"

namespace AssetHandler
{
#ifdef IS_MP
	namespace MP
	{
		void RegisterLoadersAndDumpers()
		{
			IPhysPreset::MP::Load();
			IMaterial::MP::Load();
			ISndVfCurve::MP::Load();
			IClipMap::MP::Load();
			IComWorld::MP::Load();
			IGameWorldMp::MP::Load();
			IMapEnts::MP::Load();
			IFxWorld::MP::Load();
			IGfxWorld::MP::Load();
			IGfxLightDef::MP::Load();
			IFont::MP::Load();
			IMenuList::MP::Load();
			ILocalizeEntry::MP::Load();
			ISndDriverGlobals::MP::Load();
			IRawFile::MP::Load();
			IStringTable::MP::Load();
			ILeaderboardDef::MP::Load();
			IStructuredDataDefSet::MP::Load();
			ITracerDef::MP::Load();
			ILaserDef::MP::Load();
			IAddonMapEnts::MP::Load();
			IShellShockParams::MP::Load();
			IAudioVolumeSetting::MP::Load();
			IRadVerbPreset::MP::Load();
			IFogDef::MP::Load();
		}

		void* ReallocateAssetPool(unsigned int type, unsigned int newSize)
		{
			int oldSize = Symbols::MP::DB_GetXAssetSizeHandlers[type]();

			void* poolEntry = malloc(newSize * oldSize);
			Symbols::MP::DB_XAssetPool[type] = poolEntry;
			Symbols::MP::g_poolSize[type] = newSize;
			return poolEntry;
		}

		void Load()
		{
			RegisterLoadersAndDumpers();

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
		}
	}
#elif IS_SP
	namespace SP
	{
		void RegisterLoadersAndDumpers()
		{
			IPhysPreset::SP::Load();
			ISndVfCurve::SP::Load();
			IComWorld::SP::Load();
			IGameWorldSp::SP::Load();
			IMapEnts::SP::Load();
			IFxWorld::SP::Load();
			IGfxLightDef::SP::Load();
			IFont::SP::Load();
			IMenuList::SP::Load();
			ILocalizeEntry::SP::Load();
			ISndDriverGlobals::SP::Load();
			IRawFile::SP::Load();
			IStringTable::SP::Load();
			ILeaderboardDef::SP::Load();
			IStructuredDataDefSet::SP::Load();
			ITracerDef::SP::Load();
			ILaserDef::SP::Load();
			IAddonMapEnts::SP::Load();
			IShellShockParams::SP::Load();
			IAudioVolumeSetting::SP::Load();
			IRadVerbPreset::SP::Load();
			IFogDef::SP::Load();
		}

		void* ReallocateAssetPool(unsigned int type, unsigned int newSize)
		{
			int oldSize = Symbols::SP::DB_GetXAssetSizeHandlers[type]();

			void* poolEntry = malloc(newSize * oldSize);
			Symbols::SP::DB_XAssetPool[type] = poolEntry;
			Symbols::SP::g_poolSize[type] = newSize;
			return poolEntry;
		}

		void Load()
		{
			RegisterLoadersAndDumpers();

			// IW4x limits

			ReallocateAssetPool(Structs::ASSET_TYPE_GAMEWORLD_MP, 1);
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
		}
	}
#endif
}
