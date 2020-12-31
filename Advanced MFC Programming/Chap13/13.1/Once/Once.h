#if !defined(AFX_ONCE_H__21AF8604_30FF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_ONCE_H__21AF8604_30FF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

#define ONCE_CLASSNAME		"OnceClass"

class COnceApp : public CWinApp
{
protected:
	BOOL m_bRegistered;

public:
	COnceApp();

	//{{AFX_VIRTUAL(COnceApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(COnceApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_ONCE_H__21AF8604_30FF_11D1_9C9A_444553540000__INCLUDED_)
