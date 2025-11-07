<p align="center">
  <img src="Assets/GitHub/Banner.gif?raw=true" />
</p>

<div align="center">

# NX1-Mod - Modification for Future Warfare (NX1).

![downloads](https://img.shields.io/github/downloads/hindercanrun/NX1-Mod/total?style=flat-square&label=Total%20Downloads&labelColor=F3F8FF&color=F88379)
![latest release](https://img.shields.io/github/v/tag/hindercanrun/NX1-Mod?filter=!v*-pre&style=flat-square&label=Latest%20Release&labelColor=F3F8FF&color=F88379)
![release date](https://img.shields.io/github/release-date-pre/hindercanrun/NX1-Mod?style=flat-square&label=Release%20Date&labelColor=F3F8FF&color=F88379)
![code size](https://img.shields.io/github/languages/code-size/hindercanrun/NX1-Mod?style=flat-square&label=Code%20Size&labelColor=F3F8FF&color=F88379)
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

## Changelist
- You can disable any of these changes (soon) within the NX1-Mod.ini

#### Changes
- Removed Black Box (SP/MP)
- Removed Anti Cheat (SP/MP)
- Unlocked FPS (SP/MP)
- Custom FPS counter (SP/MP)
- Console + DevGui font changed (SP/MP)
- Start-up configs no longer execute multiple times (SP/MP)
- Custom intro movie (SP/MP)
- Removed XRay material from scoreboard (MP)
- Fixed thread names showing as gibberish (SP/MP)
- Removed dev autoexec for a cleaner screen (SP/MP)
- Removed some prints for a cleaner log (SP/MP)
- Enabled unsecure Fast File loading (MP)
- Inital menu is now main_selection instead of main_lockout (SP)
- Console + DevGui safe area fits the full screen, like it does on PC (SP/MP)
- Missing localization strings no longer error by default (SP/MP)
- Added listassetpool command for modders (SP/MP)
- printf outputs to the console log file (SP/MP)
- Removed un-needed build version from the external console window (SP/MP)
- NX1-Host is the default host name, used to be CoD4Host (MP)
- Game no longer performs a session sanity check on Xenia (SP/MP)
- SP BSP resolving works in MP (and vice versa) (SP/MP)
