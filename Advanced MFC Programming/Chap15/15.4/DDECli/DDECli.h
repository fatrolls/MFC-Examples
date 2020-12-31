#if !defined(AFX_DDECLI_H__747EBB38_49F6_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DDECLI_H__747EBB38_49F6_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CDDECliApp : public CWinApp
{
public:
	CDDECliApp();
	//{{AFX_VIRTUAL(CDDECliApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDDECliApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DDECLI_H__747EBB38_49F6_11D1_9C9A_444553540000__INCLUDED_)
