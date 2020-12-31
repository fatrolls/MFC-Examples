// AutoPan.h : main header file for the AUTOPAN application
//

#if !defined(AFX_AUTOPAN_H__4E9C2716_CFCD_11D1_87BA_400011900025__INCLUDED_)
#define AFX_AUTOPAN_H__4E9C2716_CFCD_11D1_87BA_400011900025__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAutoPanApp:
// See AutoPan.cpp for the implementation of this class
//

class CAutoPanApp : public CWinApp
{
public:
	CAutoPanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAutoPanApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPAN_H__4E9C2716_CFCD_11D1_87BA_400011900025__INCLUDED_)
