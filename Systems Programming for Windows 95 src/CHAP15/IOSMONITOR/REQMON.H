// REQMON.H -- Declarations for VSD sample
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#ifndef REQMON_H
#define REQMON_H

#ifndef Not_VxD

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

#pragma warning(disable:4035)

#ifndef NAKED
	#define NAKED __declspec(naked)
#endif

BOOL VXDINLINE NAKED _VWIN32_QueueUserApc(DWORD userproc, DWORD refdata, PTCB thread)
	{
	VxDJmp(_VWIN32_QueueUserApc)
	}

#pragma warning(default:4035)

///////////////////////////////////////////////////////////////////////////////
// Data structures for this driver

#endif // Not_VxD

///////////////////////////////////////////////////////////////////////////////

// IOCTL codes:

#define REQMON_SETMONITORADDRESS	1		// record monitor function address
#define REQMON_RETURNBLOCK			2		// return memory block to VMM pool
#define REQMON_GETIVTADDR			3		// retrieve IVT pointer

// Monitor info block shared between ring-0 and ring-3:

typedef struct tagMONINFO
	{							// MONINFO
	struct tagMONINFO* next;	// chaining field for ring-3 use
	PDCB dcb;					// physical dcb for this request
	DWORD nbytes;				// # bytes involved in op
	DWORD sector;				// starting sector
	BYTE opcode;				// I/O operation code
	BYTE status;				// completion code
	} MONINFO, *PMONINFO;		// MONINFO

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

#endif // REQMON_H
