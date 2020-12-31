#if !defined(AFX_INI_H__D1C586A6_3E3F_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_INI_H__D1C586A6_3E3F_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CIniApp : public CWinApp
{
public:
	CIniApp();
	//{{AFX_VIRTUAL(CIniApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CIniApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_INI_H__D1C586A6_3E3F_11D1_9C9A_444553540000__INCLUDED_)
