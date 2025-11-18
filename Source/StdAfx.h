#pragma once

#define NOMINMAX
#define MAX_CHARS				std::numeric_limits<int>::max()

#ifdef _XBOX
	#define snprintf			_snprintf
#endif

#define TITLE_ID				0x4156089E // nx1

#define BASE_FOLDER				"NX1-Mod"

#ifdef IS_MP
	#define BRANDING_STR		"NX1-Mod MP"
#elif IS_SP
	#define BRANDING_STR		"NX1-Mod SP"
#else // fallback
	#define BRANDING_STR		"NX1-Mod"
#endif

// quake define
#define KEYCATCH_CONSOLE		0x0001

// the order of everything below matters

// base includes
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <algorithm>
#include <vector>

// xbox stuff
#include <xtl.h>
#include <xbox.h>
#include <xgraphics.h>
#include <direct.h>
#include <io.h>
#include <time.h>

// external libs
#include <xkelib.h>
#include <zlib.h>

// utils
#include "Util\Command.h"
#include "Util\FileSystem.h"
#include "Util\FPS.h"
#include "Util\Hook.h"
#include "Util\Ini.h"
#include "Util\String.h"
#include "Util\XBox.h"

// game symbols/structs
#include "Game\Structs.h"
#include "Game\Symbols.h"

// client config
#include "Components\IniConfig.h"

// client components loader
#include "Loader.h"
