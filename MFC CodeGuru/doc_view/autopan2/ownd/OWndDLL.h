///////////////////////////////////////////////////////////////////
//	Written by Russ Freeman (russf@dircon.co.uk or russf@digita.com)
//	Copyright (c) 1998.
//
//	This code may be used in compiled form in any way you desire. This
//	file may be redistributed unmodified by any means PROVIDING it is 
//	not sold for profit without the authors written consent, and 
//	providing that this notice and the authors name is included. If 
//	the source code in this file is used in any commercial application 
//	then acknowledgement must be made to the author of this file 
//	(in whatever form you wish).
//
//	This file is provided "as is" with no expressed or implied warranty.
//
//	Implements the origin window, cursor handling and a fair bit of the processing required
//	to handle the middle mouse button.
//
//	Easy to use, simply call StartPanning(...)
//	See sample CScrollView derived view class in the associated sample program.
//
#ifndef __OWNDDLL_H__
#define __OWNDDLL_H__

#ifdef UNICODE
	#define LIBNAME	"OWndU"
#else	//	UNICODE
	#define LIBNAME	"OWnd"
#endif	//	UNICODE

#ifndef BUILD_OWND_DLL
	#ifdef _DEBUG
		#pragma comment(lib, LIBNAME "D.lib")
	#else	//	_DEBUG
		#pragma comment(lib, LIBNAME ".lib")
	#endif	//	_DEBUG
#endif	//BUILD_OWND_DLL


//
//	registered message sent by the origin window when you need to update your window.
#define OWND_WINDOW_UPDATE _T("rjf_OriginWindowUpdate")

//
//	Start panning, call thsi to start panning and if your window handles scrolling okay you need
//	do nothing else!
extern "C" BOOL StartPanning( CWnd *pwndParent, BOOL bCanScrollVert, BOOL bCanScrollHorz, CPoint point );

#endif //__OWNDDLL_H__