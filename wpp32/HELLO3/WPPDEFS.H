//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPPDEFS.H
//
// Basic Windows++ type definitions, constants, etc.

#ifndef WPPDEFS_H
#define WPPDEFS_H

#ifndef RC_INVOKED
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#endif

const MAXINT = 0x7fff;
const MAXFILENAMELEN = 128;

typedef char*	STR;
typedef const	char* CSTR;
typedef const	char FAR* LPCSTR;

extern int ErrBox(CSTR format, ...);

//////////////////
// All the classes are declared below, without being defined.
// This is so we can make forward references to class types in
// function arguments, etc., (before the class is actually defined).
// 
class WPRect;
class WPWin;
class WPMainWin;

#ifdef __BORLANDC__
#define max(a,b)	(((a) > (b)) ? (a) : (b))
#define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif

#endif
