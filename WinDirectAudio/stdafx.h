#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <windows.h>
#include <commdlg.h>
#include <mmreg.h>
#include <mmsystem.h>
#include <dsound.h>
#include <strsafe.h>
#include <wmsdk.h>
#include <msacm.h>

/* libmad support */
#include "mad.h"

/* libogg support */
#include "ogg/ogg.h"

/* libvorbis support */
#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "strsafe.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "wmvcore.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "msacm32.lib")

#define USE_DAUDIO TRUE
#define USE_ERROR
#define USE_TRACE
