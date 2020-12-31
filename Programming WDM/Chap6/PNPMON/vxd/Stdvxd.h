// StdVxd.h -- Standard declarations for C-language VxDs
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef STDVXD_H
#define STDVXD_H

#ifdef __cplusplus
	extern "C" {
	#define SYSCTL extern "C"
#else
	#define SYSCTL
#endif
#include <wdm.h>
#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vpicd.h>
#pragma warning(disable:4229)
#include <shell.h>
#include <vwin32.h>
#include <ntkern.h>
#include <vxdldr.h>

#include <vxdwraps.h>

#include <configmg.h>
#include <winerror.h>
#ifdef __cplusplus
}
#endif
		
///////////////////////////////////////////////////////////////////////////////
// Useful general-purpose definitions

#include <string.h>
#include <conio.h>
#pragma intrinsic(memcmp, memcpy, memset, strcat, strcmp, strcpy, strlen, _inp, _outp)

#undef ASSERT
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

#endif // STDVXD_H
