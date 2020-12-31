// MarkupApp.h : main header file for the MARKUP application
//

#if !defined(AFX_MARKUPAPP_H__7E553A2E_D0C6_11D6_9F49_00500486CAFC__INCLUDED_)
#define AFX_MARKUPAPP_H__7E553A2E_D0C6_11D6_9F49_00500486CAFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMarkupApp:
// See Markup.cpp for the implementation of this class
//

class CMarkupApp : public CWinApp
{
public:
	CMarkupApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMarkupApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPAPP_H__7E553A2E_D0C6_11D6_9F49_00500486CAFC__INCLUDED_)
