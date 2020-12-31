// MFCXMiniDockFrameWnd.h : header file
/*
Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
//////////////////////////////////////////////////////////////////////

#ifndef MFCXMINIDOCKFRAMEWND__H
#define MFCXMINIDOCKFRAMEWND__H

#include <afxpriv.h>

/////////////////////////////////////////////////////////////////////////////
// CMFCXMiniDockFrameWnd ( originally CNMiniDockFrameWnd )

class CMFCXMiniDockFrameWnd : public CMiniDockFrameWnd
{
	DECLARE_DYNCREATE(CMFCXMiniDockFrameWnd)
protected:
	CMFCXMiniDockFrameWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCXMiniDockFrameWnd)
	public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMFCXMiniDockFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CMFCXMiniDockFrameWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
