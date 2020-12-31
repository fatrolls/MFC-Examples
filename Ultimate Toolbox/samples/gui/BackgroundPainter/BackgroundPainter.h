// BackgroundPainter.h : main header file for the BACKGROUNDPAINTER application
//

#if !defined(AFX_BACKGROUNDPAINTER_H__24987B17_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
#define AFX_BACKGROUNDPAINTER_H__24987B17_8DEB_11D2_A792_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBackgroundPainterApp:
// See BackgroundPainter.cpp for the implementation of this class
//

class CBackgroundPainterApp : public CWinApp
{
public:
	CBackgroundPainterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackgroundPainterApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBackgroundPainterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKGROUNDPAINTER_H__24987B17_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
