// BLOBS.h : main header file for the BLOBS application
//

#if !defined(AFX_BLOBS_H__18FE210D_F229_11D1_8F3C_0080C82231F1__INCLUDED_)
#define AFX_BLOBS_H__18FE210D_F229_11D1_8F3C_0080C82231F1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBLOBSApp:
// See BLOBS.cpp for the implementation of this class
//

class CBLOBSApp : public CWinApp
{
public:
	CBLOBSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBLOBSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBLOBSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOBS_H__18FE210D_F229_11D1_8F3C_0080C82231F1__INCLUDED_)
