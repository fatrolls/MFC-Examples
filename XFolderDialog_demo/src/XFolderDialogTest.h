// XFolderDialogTest.h : main header file for the XFOLDERDIALOGTEST application
//

#ifndef XFOLDERDIALOGTEST_H
#define XFOLDERDIALOGTEST_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXFolderDialogTestApp:
// See XFolderDialogTest.cpp for the implementation of this class
//

class CXFolderDialogTestApp : public CWinApp
{
public:
	CXFolderDialogTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXFolderDialogTestApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXFolderDialogTestApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XFOLDERDIALOGTEST_H
