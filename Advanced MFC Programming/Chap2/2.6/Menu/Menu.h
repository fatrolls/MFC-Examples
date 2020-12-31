#if !defined(AFX_MENU_H__D7E0A2E5_F772_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MENU_H__D7E0A2E5_F772_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CMenuApp : public CWinApp
{
public:
	CMenuApp();
	//{{AFX_VIRTUAL(CMenuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CMenuApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MENU_H__D7E0A2E5_F772_11D0_9C9A_444553540000__INCLUDED_)
