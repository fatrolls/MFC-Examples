#if !defined(AFX_CTL_H__F2267946_01AE_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CTL_H__F2267946_01AE_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CCtlApp : public CWinApp
{
public:
	CCtlApp();
	//{{AFX_VIRTUAL(CCtlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CCtlApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CTL_H__F2267946_01AE_11D1_9C9A_444553540000__INCLUDED_)
