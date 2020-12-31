// DictComp.h : main header file for the DICTCOMP DLL
//

#if !defined(AFX_DICTCOMP_H__84B0BBFB_AD8B_11D2_A2DC_A31D6122660F__INCLUDED_)
#define AFX_DICTCOMP_H__84B0BBFB_AD8B_11D2_A2DC_A31D6122660F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDictCompApp
// See DictComp.cpp for the implementation of this class
//

class CDictCompApp : public CWinApp
{
public:
	CDictCompApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDictCompApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDictCompApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DICTCOMP_H__84B0BBFB_AD8B_11D2_A2DC_A31D6122660F__INCLUDED_)
