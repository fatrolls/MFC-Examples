#if !defined(AFX_SPW_H__D3F202BB_FC3A_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_SPW_H__D3F202BB_FC3A_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CSpwApp : public CWinApp
{
public:
	CSpwApp();
	//{{AFX_VIRTUAL(CSpwApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CSpwApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SPW_H__D3F202BB_FC3A_11D0_9C9A_444553540000__INCLUDED_)
