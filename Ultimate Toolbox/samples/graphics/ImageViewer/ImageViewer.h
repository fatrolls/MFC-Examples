// ImageViewer.h : main header file for the IMAGEVIEWER application
//

#if !defined(AFX_IMAGEVIEWER_H__AEC86165_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_)
#define AFX_IMAGEVIEWER_H__AEC86165_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageViewerApp:
// See ImageViewer.cpp for the implementation of this class
//

class CImageViewerApp : public CWinApp
{
public:
	CImageViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImageViewerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEWER_H__AEC86165_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_)
