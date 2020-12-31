// RAMDISK.H -- Declarations for port driver sample
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#ifndef RAMDISK_H
#define RAMDISK_H

#include <debug.h>

///////////////////////////////////////////////////////////////////////////////
// Useful general-purpose definitions

#include <string.h>
#pragma intrinsic(memcmp, memcpy, memset, strcat, strcmp, strcpy, strlen)

#ifdef DEBUG
	#define ASSERT(e) if(!(e)){Debug_Printf("Assertion failure in " __FILE__ ", line %d: " #e "\r\n", __LINE__);\
		_asm int 1\
		}
#else
	#define ASSERT(e)
#endif

#ifndef MAKELONG
	#define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))
#endif

#ifndef FIELDOFFSET
	#define FIELDOFFSET(type, field) ((DWORD)(&((type *)0)->field))
#endif

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

///////////////////////////////////////////////////////////////////////////////
// Data structures for this driver

typedef struct tagRAMDISKDDB
	{							// RAMDISKDDB
	struct DDB;					// unnamed structure so we don't have to incessantly qualify names
	} RAMDISKDDB, *PRAMDISKDDB;

#endif // RAMDISK_H
