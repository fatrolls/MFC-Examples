// DialogGL.h : main header file for the DIALOGGL application
//

#if !defined(AFX_DIALOGGL_H__A779FD05_4258_11D1_88DD_A4B001C10000__INCLUDED_)
#define AFX_DIALOGGL_H__A779FD05_4258_11D1_88DD_A4B001C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDialogGLApp:
// See DialogGL.cpp for the implementation of this class
//

class CDialogGLApp : public CWinApp
{
public:
	virtual BOOL OnIdle(LONG lCount);
	CDialogGLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogGLApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDialogGLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGGL_H__A779FD05_4258_11D1_88DD_A4B001C10000__INCLUDED_)
