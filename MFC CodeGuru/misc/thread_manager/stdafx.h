// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
 
//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x400
#endif //

#define WIN32_EXTRA_LEAN
#define NOSERVICE
#define NOMCX
#define NOIME
#define NOSOUND
//#define NOCOMM
#define NOKANJI
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#endif // _AFX_NO_OLE_SUPPORT

//////////////////////////////////////////////////////////////////////////////
// Turn on some ueful warnings
//#pragma warning(default: 4xxx)
#pragma warning(default: 4705)  // statement has no effect in optimized code
#pragma warning(default: 4702)  // unreachable code caused by optimizations
#pragma warning(default: 4701)  // local variable *may* be used without init
#pragma warning(default: 4710)  // private constructors are disallowed

//////////////////////////////////////////////////////////////////////////////
// Some Useful thingys
typedef CONST CString	CCSTRING;
typedef CONST INT		CINT;
typedef CONST BOOL		CBOOL;
typedef CONST BYTE		CBYTE;
typedef CONST WORD		CWORD;
typedef CONST DWORD		CDWORD;

// Useful inline function to do some conversion { typesafe }
#ifndef MakeDword
#define MakeDword
inline CDWORD MAKEDWORD( CWORD cwHi, CWORD cwLo ) { return( (((DWORD)(cwHi)) << 16) | ((DWORD)(cwLo)) ); };
//
// AHW - We had a problem here. I'm using a switch statement, and it's giving error
// C2051 - case expression not constant. Thing is that I'm using a CDWORD defined
// by this macro, so it surely is constant. After a little interrogation, it's not
// that I'm using a DWORD value, as I had expected, but the method with which
// the DWORD is being created, ie MAKEDWORD. I tried rewriting the MAKEDWORD
// using #define so that it is a true macro, and suddenly everything works, although
// compilation seems a little slower. 1997-10-06
//
//inline CDWORD MAKEDWORD( CBYTE cbtHi, CBYTE cbtLo, CWORD cwLo ) { return( (((DWORD)(cbtHi)) << 24) | (((DWORD)(cbtLo)) << 16) | ((DWORD)(cwLo)) ); };
#define MAKEDWORD(a,b,c) (CDWORD)((DWORD)a<<24)|((DWORD)b<<16)|((DWORD)c)
#endif // MakeDword

#ifndef _INC_IOSTREAM
#include <iostream.h>
#endif //

//////////////////////////////////////////////////////////////////////////////
// Function declarations that are useful for decoding a problem
#ifdef _DEBUG
// Function only included in debug, hence does not need commenting out if in 
// release mode
#define ONLY_IN_DEBUG(f)      (f)

#else   // _DEBUG
// Overrides for the functions if in release mode
#define ONLY_IN_DEBUG(f)		((void)0)
#endif // !_DEBUG
// End of Debug Helper declarations
//////////////////////////////////////////////////////////////////////////////

