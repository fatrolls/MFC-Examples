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
//	Easy to use, simply create an instance of it, call it's COriginWnd::Create and respond to the
//	two static registered messages. See sample CScrollView derived view class in the associated
//	sample program.
//
//	Author: Russell Freeman
//	date:		13/6/98
//	Email:	russf@dircon.co.uk or russf@digita.com
//
//	Tested in ANSI and UNICODE builds.
//	Tested using Window NT 4.0 sp3, not tested using Windows 95
//	Linted	13/6/98

#include "stdafx.h"
#include "OriginWnd.h"
#include "OWndDLL.h"
//lint -esym( 613, COriginWnd::m_pParent )

extern "C" BOOL StartPanning( CWnd *pwndParent, BOOL bVert, BOOL bHorz, CPoint point )
//
//	Start panning on the window passed.
//
//	Return non-zero if we successfully started, zero otherwise
{
	ASSERT_VALID( pwndParent );
	//
	//	Must be dynamically created because it will delete itself when it gets destroyed
	COriginWnd *pwndPanWindow = new COriginWnd( bHorz, bVert, point );
	if( !pwndPanWindow->Create( pwndParent ) )
	{
		delete pwndPanWindow;
		return FALSE;
	}
	return TRUE;	
}
