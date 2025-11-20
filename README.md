<p align="center">
  <img src="Assets/GitHub/Banner.gif?raw=true" />
</p>

<div align="center">

# NX1-Mod - Modification for Future Warfare (NX1).

</div>

## Supported XEXs
- 1-nx1sp.xex
- 2-nx1mp.xex

## How to use (Xenia Canary)
### Patches
- Download the required [game patches](https://github.com/hindercanrun/NX1-Mod/tree/main/Assets/Xenia/patches).
- Put them into `xenia\patches`.
- Make sure `apply_patches` is set to `true` in the Xenia Canary config (It's `true` by default).
- Done.
### Plugins
- Make sure `allow_plugins` is set to `true` in the Xenia Canary config (It's `false` by default).
- Download the [latest version](https://github.com/hindercanrun/NX1-Mod/releases) and place it in into `Xenia Canary\plugins\4156089E\`.
- Place the `plugins.toml` there too, depending on the mode you want, `SP-Mod` for Campaign, `MP-Mod` for Multiplayer.
- Done.
### Playing
- Launch Xenia Canary and load up Future Warfare (NX1).
- Done.

## How to use (Xbox 360)
- Uhhh...

## Changes
- Black Box will no longer start (MP/SP)
- Unlocked FPS (MP/SP)
- Custom FPS counter (MP/SP)
- Console + DevGui font is now fwsmallfont instead of consolefont (MP/SP)
- Console + DevGui safe area fits the full screen, like it does on PC (MP/SP)
- Start-up configs no longer execute multiple times (MP/SP)
- Custom intro movie (MP/SP)
- Removed XRay material from scoreboard (MP)
- Fixed thread names showing as gibberish (MP/SP)
- Removed dev autoexec for a cleaner screen (MP/SP)
- Enabled unsecure Fast File loading (MP)
- Inital menu is now main_selection instead of main_lockout (SP)
- Missing localization strings no longer error by default (MP/SP)
- Added listassetpool command for modders (MP/SP)
- printf outputs to the console log file (MP/SP)
- Removed un-needed build version from the external console window (MP/SP)
- NX1-Host is the default host name, used to be CoD4Host (MP)
- Game no longer performs a session sanity check (MP/SP)
- SP BSP resolving works in MP (and vice versa) (MP/SP)
- Reallocated some asset sizes (MP/SP):
  - Loaded Sound: 5400
  - FX: 2400
  - Localize Entry: 14000
  - XAnim: 16384
  - Phys Preset: 128
  - Pixel Shader: 10000
  - Weapon: 2400
  - String Table: 800
  - Impact FX: 8
- Added a print that tells you what .d3dbsp has loaded (MP/SP)
- Added game init print (SP)
- Added asset loaders (MP/SP):
  - Map Ents - Load any entity files from NX1-Mod/raw/maps
  - Raw File - Load any raw file from NX1-Mod/raw
- Added asset dumpers (MP/SP):
  - Phys Preset - Dump any physic preset file
  - Raw File - Dump any raw file
- replaced IW4 references with NX1 (MP)
- Removed some prints (MP/SP):
  - dvar set
  - cmd line
  - unknown map add to xlast
  - start $init
  - end $init
  - looking for alias
  - com_init_tbf build version
  - loading from disc, not update drive
  - missing soundalias
  - adding/hiding channel
  - no channels added/hidden
  - log file opened
