// MdiEx.h : main header file for the MDIEX application
//

#if !defined(AFX_MDIEX_H__250DE495_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_)
#define AFX_MDIEX_H__250DE495_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMdiExApp:
// See MdiEx.cpp for the implementation of this class
//

class CMdiExApp : public CWinApp
{
public:

	UINT		m_clientBkgndId;
	COLORREF	m_clientBkgndRGB;
	CString		m_clientBkgndFilename;
	BOOL		m_useFileForBkgnd;
	BOOL		m_useBitmap;
	BOOL		m_useTile;

public:
	CMdiExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMdiExApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMdiExApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CMdiExApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIEX_H__250DE495_9D5B_11D1_8FBE_0060084A0C51__INCLUDED_)
