#if !defined(AFX_DDESRV_H__747EBB24_49F6_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DDESRV_H__747EBB24_49F6_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CDDESrvApp : public CWinApp
{
public:
	CDDESrvApp();
	//{{AFX_VIRTUAL(CDDESrvApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDDESrvApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DDESRV_H__747EBB24_49F6_11D1_9C9A_444553540000__INCLUDED_)
