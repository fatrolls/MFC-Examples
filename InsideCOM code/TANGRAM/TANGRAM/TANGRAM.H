// Tangram.h : main header file for the TANGRAM application
//

#if !defined(AFX_TANGRAM_H__8639B382_4321_11D0_9C97_00A0C90A632C__INCLUDED_)
#define AFX_TANGRAM_H__8639B382_4321_11D0_9C97_00A0C90A632C__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTangramApp:
// See Tangram.cpp for the implementation of this class
//

class CTangramApp : public CWinApp
{
public:
	CTangramApp();
	virtual ~CTangramApp() ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTangramApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTangramApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TANGRAM_H__8639B382_4321_11D0_9C97_00A0C90A632C__INCLUDED_)
