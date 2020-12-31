// ResFile.h : main header file for the RESFILE application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CResFileApp:
// See ResFile.cpp for the implementation of this class
//

class CResFileApp : public CWinApp
{
public:
	CResFileApp();
	CLIPFORMAT m_nClipFormat;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResFileApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CResFileApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
