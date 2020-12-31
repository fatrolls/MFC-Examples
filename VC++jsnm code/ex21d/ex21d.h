// ex21d.h : main header file for the EX21D DLL
//

#if !defined(AFX_EX21D_H__1AA889CE_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_)
#define AFX_EX21D_H__1AA889CE_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx21dApp
// See ex21d.cpp for the implementation of this class
//

class CEx21dApp : public CWinApp
{
public:
	CEx21dApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx21dApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEx21dApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX21D_H__1AA889CE_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_)
