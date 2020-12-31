// winpe.h : main header file for the WINPE application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#define WM_RESET_FRAMEVIEW (WM_USER + 10) //posted from doc.
#define MakePtr(cast,ptr,addValue) (cast)((DWORD)(ptr)+(DWORD)(addValue))
/////////////////////////////////////////////////////////////////////////////
// CWinpeApp:
// See winpe.cpp for the implementation of this class
//

class CWinpeApp : public CWinApp
{
public:
	CWinpeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinpeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinpeApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	
};


/////////////////////////////////////////////////////////////////////////////
