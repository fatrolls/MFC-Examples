// PictureExDemo.h : main header file for the PICTUREEXDEMO application
//

#if !defined(AFX_PICTUREEXDEMO_H__CEFF87E5_8346_11D5_991B_B9143490767B__INCLUDED_)
#define AFX_PICTUREEXDEMO_H__CEFF87E5_8346_11D5_991B_B9143490767B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPictureExDemoApp:
// See PictureExDemo.cpp for the implementation of this class
//

class CPictureExDemoApp : public CWinApp
{
public:
	CPictureExDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictureExDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPictureExDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTUREEXDEMO_H__CEFF87E5_8346_11D5_991B_B9143490767B__INCLUDED_)
