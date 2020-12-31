//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: ERRBOX.H
//
// Declaration for only DLL one function: ErrBox

#if defined (_MSC_VER) 
#	if (_MSC_VER < 1000)
#		error "Requires MS C/C++ 10.0 or greater"
#	endif
#elif defined (__BORLANDC__)
#	if (__BORLANDC__ < 0x500)
#		error "Requires Borland C/C++ 5.0 or greater"
#	endif
#else
#	error "Unsupported compiler."
#endif

#include <windows.h>

#if defined(WPPDLL)
#	define DLLFUNC __declspec( dllexport )
#elif defined(USEDLL)
#	define DLLFUNC  __declspec ( dllimport )
#else
#	define DLLFUNC
#endif

extern int DLLFUNC DisplayMessage(const char* format, ...);
