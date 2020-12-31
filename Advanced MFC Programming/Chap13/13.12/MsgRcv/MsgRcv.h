#if !defined(AFX_MSGRCV_H__D649DA71_3EFC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_MSGRCV_H__D649DA71_3EFC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "..\Common.h"
#include "resource.h"

class CMsgRcvApp : public CWinApp
{
protected:
	BOOL m_bRegistered;

public:
	CMsgRcvApp();
	//{{AFX_VIRTUAL(CMsgRcvApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CMsgRcvApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MSGRCV_H__D649DA71_3EFC_11D1_9C9A_444553540000__INCLUDED_)
