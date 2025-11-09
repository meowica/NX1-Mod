#pragma once

#define NX1_TITLE_ID		0x4156089E

#define BASE_FOLDER			"NX1-Mod"

#define NOMINMAX
#define MAX_CHARS			std::numeric_limits<int>::max()

#ifdef _XBOX
	#define snprintf _snprintf
#endif

// quake define
#define KEYCATCH_CONSOLE	0x0001

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <xtl.h>
#include <xbox.h>
#include <xgraphics.h>
#include <direct.h>
#include <io.h>
#include <time.h>

// external libs
#include <xkelib.h>

#include "Game\Structs.h"
#include "Game\Symbols.h"

#include "Util\Command.h"
#include "Util\Hook.h"
#include "Util\String.h"
#include "Util\XBox.h"

#include "Components\Loader.h"
