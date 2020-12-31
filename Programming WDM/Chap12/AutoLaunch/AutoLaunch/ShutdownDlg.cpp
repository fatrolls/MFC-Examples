// ShutdownDlg.cpp : implementation file
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "ShutdownDlg.h"

#ifdef NTSERVICE
	#error This file should not be included in the service build!
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShutdownDlg dialog


CShutdownDlg::CShutdownDlg(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CShutdownDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Create(IDD, pParent);
}


void CShutdownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShutdownDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShutdownDlg, CDialog)
	//{{AFX_MSG_MAP(CShutdownDlg)
	ON_BN_CLICKED(IDNO, OnNo)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShutdownDlg message handlers

void CShutdownDlg::OnNo() 
{
	ShowWindow(SW_HIDE);
}

void CShutdownDlg::OnYes() 
{
	ShowWindow(SW_HIDE);
	GetParent()->DestroyWindow();
}

BOOL CShutdownDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow(GetDesktopWindow());
	return TRUE;
}
