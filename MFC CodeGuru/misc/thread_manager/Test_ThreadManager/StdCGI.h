// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x400
#endif //

#define __AFXSTATE_H__

#ifndef __AFX_H__
#include <Afx.h>
#endif //

//#include <afxsock.h>		// MFC socket extensions

#ifndef _INC_IOSTREAM
#include <iostream.h>
#endif //

//////////////////////////////////////////////////////////////////////////////
// Some Useful thingys
typedef CONST CString	CCSTRING;
typedef CONST INT		CINT;
typedef CONST BOOL		CBOOL;
typedef CONST BYTE		CBYTE;
typedef CONST DWORD		CDWORD;
typedef CONST WORD		CWORD;

//////////////////////////////////////////////////////////////////////////////
// Function declarations that are useful for decoding a problem
void OutPutInfoLine( PCSTR cpszFileName, CINT ciLine, PCSTR cpszOutput );
#ifdef _DEBUG
// Debug Definitions while in debug
void AssertFailedLine( PCSTR lpszFileName, CINT ciLine );
// Ver c++ changes __FILE__ on its own, if in console mode
//#define THIS_FILE          __FILE__
// This function does not do anything if used in release mode
#define ASSERT_RETURN(f) \
	do \
	{ \
	if ( !(f) ) \
		AssertFailedLine(THIS_FILE, __LINE__); \
	} while (0) \

// If in release mode then the function is still perform but the assert is ignored
#define VERIFY_RETURN(f)      ASSERT_RETURN(f)
// Function only included in debug, hence does not need commenting out if in 
// release mode
#define ONLY_IN_DEBUG(f)      (f)

#define OUTPUTINFOLINE(INFO) \
	do \
	{ \
		OutPutInfoLine(THIS_FILE, __LINE__, INFO); \
	} while (0) \

#else   // _DEBUG
// Overrides for the functions if in release mode
#define ASSERT_RETURN(f)		((void)0)
#define VERIFY_RETURN(f)		((void)(f))
#define ONLY_IN_DEBUG(f)		((void)0)
#define OUTPUTINFOLINE(INFO) \
	do \
	{ \
		OutPutInfoLine(NULL, NULL, INFO); \
	} while (0) \

#endif // !_DEBUG
// End of Debug Helper declarations
//////////////////////////////////////////////////////////////////////////////

