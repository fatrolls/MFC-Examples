#if !defined(AFX_ZORDER_H__D649DA86_3EFC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_ZORDER_H__D649DA86_3EFC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CZOrderApp : public CWinApp
{
public:
	CZOrderApp();
	//{{AFX_VIRTUAL(CZOrderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CZOrderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_ZORDER_H__D649DA86_3EFC_11D1_9C9A_444553540000__INCLUDED_)
