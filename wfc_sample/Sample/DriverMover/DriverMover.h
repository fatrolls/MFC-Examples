// DriverMover.h : main header file for the DRIVERMOVER application
//

#if !defined(AFX_DRIVERMOVER_H__8D5CEDF5_518E_11D3_B0CD_00600898269E__INCLUDED_)
#define AFX_DRIVERMOVER_H__8D5CEDF5_518E_11D3_B0CD_00600898269E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDriverMoverApplication:
// See DriverMover.cpp for the implementation of this class
//

class CDriverMoverApplication : public CWinApp
{
public:
	CDriverMoverApplication();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverMoverApplication)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDriverMoverApplication)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERMOVER_H__8D5CEDF5_518E_11D3_B0CD_00600898269E__INCLUDED_)
