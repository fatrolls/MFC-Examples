#if !defined(AFX_BALLOON_H__0D5B7B66_3BDF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_BALLOON_H__0D5B7B66_3BDF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CBalloonApp : public CWinApp
{
public:
	CBalloonApp();
	//{{AFX_VIRTUAL(CBalloonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CBalloonApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_BALLOON_H__0D5B7B66_3BDF_11D1_9C9A_444553540000__INCLUDED_)
