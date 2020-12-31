// Widget.h : main header file for the WIDGET application
//

#if !defined(AFX_WIDGET_H__02909A45_3F5C_11D2_AC89_006008A8274D__INCLUDED_)
#define AFX_WIDGET_H__02909A45_3F5C_11D2_AC89_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWidgetApp:
// See Widget.cpp for the implementation of this class
//

class CWidgetApp : public CWinApp
{
public:
	UINT GetClipboardFormat ();
	CWidgetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWidgetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWidgetApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	UINT m_nFormat;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIDGET_H__02909A45_3F5C_11D2_AC89_006008A8274D__INCLUDED_)
