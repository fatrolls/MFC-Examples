#if !defined(AFX_GDI_H__E61CF0F7_17B9_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_GDI_H__E61CF0F7_17B9_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CGDIApp : public CWinApp
{
public:
	CGDIApp();
	//{{AFX_VIRTUAL(CGDIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CGDIApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_GDI_H__E61CF0F7_17B9_11D1_9C9A_444553540000__INCLUDED_)
