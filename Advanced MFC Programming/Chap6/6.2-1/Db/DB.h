#if !defined(AFX_DB_H__6F1FA2CA_130A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DB_H__6F1FA2CA_130A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CDBApp : public CWinApp
{
public:
	CDBApp();
	//{{AFX_VIRTUAL(CDBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDBApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DB_H__6F1FA2CA_130A_11D1_9C9A_444553540000__INCLUDED_)
