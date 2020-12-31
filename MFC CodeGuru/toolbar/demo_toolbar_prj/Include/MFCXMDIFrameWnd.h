// MFCXMDIFrameWnd.h : header file
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

#ifndef MFCXMDIFRAMEWND__H
#define MFCXMDIFRAMEWND__H

#ifndef MFCX_PROJ
#define CLASS_EXPORT AFX_CLASS_EXPORT
#else
#define CLASS_EXPORT AFX_CLASS_IMPORT
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCXMDIFrameWnd ( originally CNMDIMenuFrameWnd )

class CLASS_EXPORT CMFCXMDIFrameWnd : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CMFCXMDIFrameWnd)
protected:
	CMFCXMDIFrameWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void EnableDocking(DWORD dwDockStyle);
	virtual BOOL LoadFrame( UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCXMDIFrameWnd)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMFCXMDIFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CMFCXMDIFrameWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
