// MetaFile.h : main header file for the METAFILE application
//

#if !defined(AFX_METAFILE_H__D6580AE8_EA6C_11D1_8856_0080C83F712F__INCLUDED_)
#define AFX_METAFILE_H__D6580AE8_EA6C_11D1_8856_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMetaFileApp:
// See MetaFile.cpp for the implementation of this class
//

class CMetaFileApp : public CWinApp
{
public:
	CMetaFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMetaFileApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMetaFileApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METAFILE_H__D6580AE8_EA6C_11D1_8856_0080C83F712F__INCLUDED_)
