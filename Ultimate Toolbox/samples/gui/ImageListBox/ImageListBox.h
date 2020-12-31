// ImageListBox.h : main header file for the IMAGELISTBOX application
//

#if !defined(AFX_IMAGELISTBOX_H__A574A805_4041_11D3_8AF4_0080C8F8F09F__INCLUDED_)
#define AFX_IMAGELISTBOX_H__A574A805_4041_11D3_8AF4_0080C8F8F09F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageListBoxApp:
// See ImageListBox.cpp for the implementation of this class
//

class CImageListBoxApp : public CWinApp
{
public:
	CImageListBoxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageListBoxApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImageListBoxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGELISTBOX_H__A574A805_4041_11D3_8AF4_0080C8F8F09F__INCLUDED_)
