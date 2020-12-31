#if !defined(AFX_BAR_H__C0A99CF1_ED67_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_BAR_H__C0A99CF1_ED67_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CBarApp : public CWinApp
{
public:
	CBarApp();
	//{{AFX_VIRTUAL(CBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CBarApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_BAR_H__C0A99CF1_ED67_11D0_9C9A_444553540000__INCLUDED_)
