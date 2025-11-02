# NX1-Mod - Modification for Future Warfare (NX1)

## Supported XEXs
- 1-nx1sp.xex
- 2-nx1mp.xex

## How to use (Xenia Canary)
### Patches
- Download the required [game patches](https://github.com/hindercanrun/NX1-Mod/tree/main/Xenia/patches).
- Put them into `xenia\patches`.
- Make sure `apply_patches` is set to `true` in the Xenia Canary config (It's `true` by default).
- Done.
### Plugins
- Make sure `allow_plugins` is set to `true` in the Xenia Canary config (It's `false` by default).
- Download the latest `NX1-Mod.xex` and place it in into `xenia\plugins\4156089E\`.
- Place the `plugins.toml` there too, depending on the mode you want, `SP-Mod` for Campaign, `MP-Mod` for Multiplayer.
- Done.
### Playing
- Launch Xenia Canary and load up Future Warfare (NX1).
- Done.

## How to use (Xbox 360)
- Uhhh...

## Changes (mode)
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
- Open main_selection instead of main_lockout (SP)
- Console + DevGui safe area fits the full screen, like it does on PC (SP/MP)
- Missing localization strings no longer error by default (SP/MP)
- Added listassetpool command for modders (SP/MP)
- printf outputs to the console log file (SP/MP)
