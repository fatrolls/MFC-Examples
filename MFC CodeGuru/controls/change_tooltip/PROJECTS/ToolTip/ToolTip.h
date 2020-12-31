// ToolTip.h : main header file for the TOOLTIP application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


#include "resource.h"       // main symbols
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ToolTipDoc.h"
#include "ChangeTTT.h"
#include "ToolTipView.h"



/////////////////////////////////////////////////////////////////////////////
// CToolTipApp:
// See ToolTip.cpp for the implementation of this class
//

class CToolTipApp : public CWinApp
{
public:
	CToolTipApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CToolTipApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
