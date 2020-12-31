#if !defined(AFX_SENDER_H__D649DA64_3EFC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_SENDER_H__D649DA64_3EFC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "..\Common.h"

#define BUFFER_SIZE		0x400

class CSenderApp : public CWinApp
{
public:
	CSenderApp();
	//{{AFX_VIRTUAL(CSenderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CSenderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_SENDER_H__D649DA64_3EFC_11D1_9C9A_444553540000__INCLUDED_)
