// CompFile.h : main header file for the COMPFILE application
//

#if !defined(AFX_COMPFILE_H__4F168D5D_C210_11D2_9E60_00104B08CC22__INCLUDED_)
#define AFX_COMPFILE_H__4F168D5D_C210_11D2_9E60_00104B08CC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCompFileApp:
// See CompFile.cpp for the implementation of this class
//

class CCompFileApp : public CWinApp
{
public:
	CCompFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompFileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCompFileApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPFILE_H__4F168D5D_C210_11D2_9E60_00104B08CC22__INCLUDED_)
