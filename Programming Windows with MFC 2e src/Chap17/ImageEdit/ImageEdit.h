// ImageEdit.h : main header file for the IMAGEEDIT application
//

#if !defined(AFX_IMAGEEDIT_H__9D77AEE4_AA14_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_IMAGEEDIT_H__9D77AEE4_AA14_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageEditApp:
// See ImageEdit.cpp for the implementation of this class
//

class CImageEditApp : public CWinApp
{
public:
	CImageEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImageEditApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEEDIT_H__9D77AEE4_AA14_11D2_8E53_006008A82731__INCLUDED_)
