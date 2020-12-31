// MYVXD.H -- Declarations for IFS Monitor Sample
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#ifndef MYVXD_H
#define MYVXD_H

#ifndef Not_VxD

#pragma warning(disable:4075) // nonstandard init seg
#pragma init_seg("INITCODE")
#pragma warning(default:4075)

#ifdef __cplusplus
extern "C" {
#endif

#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vwin32.h>
#include <vxdwraps.h>
#include <winerror.h>

#ifdef __cplusplus
}
#endif

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

#define SYSCTL extern "C"

///////////////////////////////////////////////////////////////////////////////

#include "ifsmgr.h"

BOOL VXDINLINE NAKED _VWIN32_QueueUserApc(DWORD userproc, DWORD refdata, PTCB thread)
	{
	VxDJmp(_VWIN32_QueueUserApc)
	}

#endif // Not_VxD

///////////////////////////////////////////////////////////////////////////////

// IOCTL codes:

#define REQMON_SETMONITORADDRESS	1		// record monitor function address
#define REQMON_RETURNBLOCK			2		// return memory block to VMM pool

// Monitor info block shared between ring-0 and ring-3:

typedef struct tagMONINFO
	{							// MONINFO
	struct	tagMONINFO* next;	// chaining field for ring-3 use
	int		fcn;				// what function was issued
	int		drive;				// target drive
	int		flags;				// flags
	int		cp;					// code page
	ioreq	req;				// the request we intercepted
	BYTE	path1[MAX_PATH];	// 1st pathname involved (if any)
	BYTE	path2[MAX_PATH];	// 2d pathname involved (if any)
	} MONINFO, *PMONINFO;		// MONINFO

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

#endif // MYVXD_H
