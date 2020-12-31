// StdVxd.h -- Standard declarations for C-language VxDs
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#ifndef STDVXD_H
#define STDVXD_H

#ifdef __cplusplus
	extern "C" {
	#ifndef SETINITSEG
		#define SETINITSEG
		#pragma warning(disable:4075) // nonstandard init seg
		#pragma init_seg("INITCODE")
		#pragma warning(default:4075)
	#endif // SETINITSEG
	#define SYSCTL extern "C"
#else // not __cplusplus
	#define SYSCTL
#endif // not __cplusplus

#define WANTVXDWRAPS
#include <basedef.h>
#undef NULL
#define NULL 0
#include <vmm.h>
#include <debug.h>
#include <crs.h>

// Virtual Communications Driver:

#include <vcomm.h>

#include <vxdwraps.h>

#include <stdarg.h>
#include <configmg.h>
#include <vport.h>

#ifdef __cplusplus
} // extern "C"
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

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

#ifndef NAKED
	#define NAKED __declspec(NAKED)
#endif

#ifndef min
	#define min(a,b) ((a) > (b) ? (a) : (b))
#endif

#endif // STDVXD_H
