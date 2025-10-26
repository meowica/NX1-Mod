#pragma once

#include "Types\PhysPreset.h"
// ASSET_TYPE_PHYSCOLLMAP - collmaps..? like .map? needs research
// ASSET_TYPE_XANIMPARTS
// ASSET_TYPE_XMODEL_SURFS - new, needs research
// ASSET_TYPE_XMODEL
#include "Types\Material.h"
// ASSET_TYPE_PIXELSHADER
// ASSET_TYPE_TECHNIQUE_SET
// ASSET_TYPE_IMAGE = 0x8,
#include "Types\SndAliasList.h" // needs research
#include "Types\SndVfCurve.h" // needs research
#include "Types\SndLpfCurve.h" // needs research
// ASSET_TYPE_LOADED_SOUND - new, needs research
// ASSET_TYPE_CLIPMAP_SP
// ASSET_TYPE_CLIPMAP_MP - used to be CLIPMAP_PVS, anything else change?
// ASSET_TYPE_COMWORLD
// ASSET_TYPE_GAMEWORLD_SP
// ASSET_TYPE_GAMEWORLD_MP
#include "Types\MapEnts.h"
// ASSET_TYPE_FXWORLD - new, needs research
// ASSET_TYPE_GFXWORLD
#include "Types\GfxLightDef.h"
// ASSET_TYPE_UI_MAP - never used
// ASSET_TYPE_FONT
// ASSET_TYPE_MENULIST
// ASSET_TYPE_MENU
#include "Types\LocalizeEntry.h"
#include "Types\WeaponCompleteDef.h"
// ASSET_TYPE_SNDDRIVER_GLOBALS
#include "Types\FxEffectDef.h"
// ASSET_TYPE_IMPACT_FX
// ASSET_TYPE_SURFACE_FX - new, needs research
// ASSET_TYPE_AITYPE - raw file
// ASSET_TYPE_MPTYPE - raw file
// ASSET_TYPE_CHARACTER - raw file
// ASSET_TYPE_XMODELALIAS - raw file
#include "Types\RawFile.h"
#include "Types\StringTable.h"
// ASSET_TYPE_LEADERBOARD - might be 1:1 to T6s
// ASSET_TYPE_STRUCTURED_DATA_DEF
#include "Types\TracerDef.h"
#include "Types\LaserDef.h" // new, needs research
#include "Types\VehicleDef.h"
// ASSET_TYPE_ADDON_MAP_ENTS - possibly (?) never used
#include "Types\ShellshockParams.h"
// ASSET_TYPE_VOLUMESETTING - new, needs research
// ASSET_TYPE_REVERBPRESET - new, needs research
#include "Types\FogDef.h"

namespace Assets
{
#ifdef MP_MOD
	namespace MP
	{
		void Load();
		void Unload();
	}
#endif

#ifdef SP_MOD
	namespace SP
	{
		void Load();
		void Unload();
	}
#endif
}
