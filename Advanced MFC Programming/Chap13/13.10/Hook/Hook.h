#if !defined(AFX_HOOK_H__D649DA93_3EFC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_HOOK_H__D649DA93_3EFC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CHookApp : public CWinApp
{
public:
	CHookApp();
	//{{AFX_VIRTUAL(CHookApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CHookApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_HOOK_H__D649DA93_3EFC_11D1_9C9A_444553540000__INCLUDED_)
