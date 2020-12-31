// CBitmapSlider Demo.h : main header file for the CBITMAPSLIDER DEMO application
//

#if !defined(AFX_CBITMAPSLIDERDEMO_H__73339594_0403_46B6_91FC_349C146D47AE__INCLUDED_)
#define AFX_CBITMAPSLIDERDEMO_H__73339594_0403_46B6_91FC_349C146D47AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoApp:
// See CBitmapSlider Demo.cpp for the implementation of this class
//

class CDemoApp : public CWinApp
{
public:
	CDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBITMAPSLIDERDEMO_H__73339594_0403_46B6_91FC_349C146D47AE__INCLUDED_)
