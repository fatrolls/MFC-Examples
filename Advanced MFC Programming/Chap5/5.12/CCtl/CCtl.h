#if !defined(AFX_CCTL_H__E6660F31_04F2_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CCTL_H__E6660F31_04F2_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CCCtlApp : public CWinApp
{
public:
	CCCtlApp();
	//{{AFX_VIRTUAL(CCCtlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CCCtlApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CCTL_H__E6660F31_04F2_11D1_9C9A_444553540000__INCLUDED_)
