#if !defined(AFX_EXPLORER_H__D1AB5344_4563_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_EXPLORER_H__D1AB5344_4563_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

#define BMP_SIZE_X		16
#define BMP_SIZE_Y		15
#define BIGBMP_SIZE_X	32
#define BIGBMP_SIZE_Y	32

class CExplorerApp : public CWinApp
{
public:
	CExplorerApp();
	//{{AFX_VIRTUAL(CExplorerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CExplorerApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_EXPLORER_H__D1AB5344_4563_11D1_9C9A_444553540000__INCLUDED_)
