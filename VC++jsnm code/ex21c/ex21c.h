// ex21c.h : main header file for the EX21C DLL
//

#if !defined(AFX_EX21C_H__CBB3141D_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_)
#define AFX_EX21C_H__CBB3141D_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx21cApp
// See ex21c.cpp for the implementation of this class
//

class CEx21cApp : public CWinApp
{
public:
	CEx21cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx21cApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEx21cApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX21C_H__CBB3141D_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_)
