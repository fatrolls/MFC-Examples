// PathList.h : main header file for the PATHLIST application
//

#if !defined(AFX_PATHLIST_H__710413E4_AC66_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_PATHLIST_H__710413E4_AC66_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPathListApp:
// See PathList.cpp for the implementation of this class
//

class CPathListApp : public CWinApp
{
public:
	CPathListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPathListApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHLIST_H__710413E4_AC66_11D2_8E53_006008A82731__INCLUDED_)
