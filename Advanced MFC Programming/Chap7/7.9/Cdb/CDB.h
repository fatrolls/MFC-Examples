#if !defined(AFX_CDB_H__2D7EBBE4_0A8A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CDB_H__2D7EBBE4_0A8A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CCDBApp : public CWinApp
{
public:
	CCDBApp();
	//{{AFX_VIRTUAL(CCDBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CCDBApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CDB_H__2D7EBBE4_0A8A_11D1_9C9A_444553540000__INCLUDED_)
