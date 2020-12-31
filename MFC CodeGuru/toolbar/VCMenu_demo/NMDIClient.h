#if !defined(AFX_NMDICLIENT_H__2F686112_A464_11D1_B0D4_00A0C94457BF__INCLUDED_)
#define AFX_NMDICLIENT_H__2F686112_A464_11D1_B0D4_00A0C94457BF__INCLUDED_
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

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NMDIClient.h : header file
//

class CNGenericMenu;

/////////////////////////////////////////////////////////////////////////////
// CNMDIClient window

class CNMDIClient : public CWnd
{
// Construction
public:
	CNMDIClient(CNGenericMenu* pMenu);

// Attributes
public:
	CNGenericMenu* m_pMenu;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNMDIClient)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNMDIClient();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNMDIClient)
	//}}AFX_MSG
	afx_msg LRESULT OnSetMenu(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NMDICLIENT_H__2F686112_A464_11D1_B0D4_00A0C94457BF__INCLUDED_)
