// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#define _UNICODE
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
//#include <afxsock.h>
#include <winsock.h>		// MFC socket extensions

#define MFC_VER_4
#define INDEX           register int
#define WINDEX          register WORD
#define LINDEX          register long
#define DWINDEX         register DWORD
typedef signed  char    INT8  ;
typedef unsigned char   UINT8 ;
typedef signed  short   INT16 ;
typedef unsigned short  UINT16;
typedef signed  long    INT32 ;
typedef unsigned long   UINT32;


