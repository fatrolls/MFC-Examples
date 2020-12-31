// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:40  $

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>			// MFC Win'95 common control

#include "mrcext.h"			// MRCEXT.DLL functions

// some extended styles that come in handy occasionally.
#ifndef WS_EX_CONTEXTHELP
#define WS_EX_CONTEXTHELP       0x0400L
#endif

#ifndef WS_EX_CLIENTEDGE
#define WS_EX_CLIENTEDGE 0x0200L
#endif
