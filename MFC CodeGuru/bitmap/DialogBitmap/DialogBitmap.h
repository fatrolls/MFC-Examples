// DialogBitmap.h : main header file for the DIALOGBITMAP application
//

#if !defined(AFX_DIALOGBITMAP_H__2839F6C5_7788_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_DIALOGBITMAP_H__2839F6C5_7788_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDialogBitmapApp:
// See DialogBitmap.cpp for the implementation of this class
//

class CDialogBitmapApp : public CWinApp
{
public:
	CDialogBitmapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBitmapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDialogBitmapApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBITMAP_H__2839F6C5_7788_11D1_ABBA_00A0243D1382__INCLUDED_)
