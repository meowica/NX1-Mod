#pragma once

#define TITLE_ID			0x4156089E // nx1

#define BASE_FOLDER			"nx1-data"

#define NOMINMAX
#define MAX_CHARS			std::numeric_limits<int>::max()

#define KEYCATCH_CONSOLE	0x1

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include <xtl.h>
#include <xbox.h>
#include <xgraphics.h>
#include <direct.h>
#include <io.h>
#include <time.h>

#include "Game\Structs.h"
#include "Game\Symbols.h"

#include "Util\Command.h"
#include "Util\FileSystem.h"
#include "Util\Hook.h"
#include "Util\Print.h"
#include "Util\String.h"
#include "Util\XBox.h"

#include "Components\Loader.h"

extern "C"
{
	NTSYSAPI DWORD NTAPI XamGetCurrentTitleId(VOID);
}
