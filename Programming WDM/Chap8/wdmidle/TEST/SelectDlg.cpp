// SelectDlg.cpp : implementation file
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "test.h"
#include "SelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog


CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDlg)
	m_devicelist = -1;
	//}}AFX_DATA_INIT
}


void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDlg)
	DDX_Control(pDX, IDC_DEVICELIST, m_ctlDevicelist);
	DDX_CBIndex(pDX, IDC_DEVICELIST, m_devicelist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg message handlers

BOOL CSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	for (int i = 0; i < m_list->m_list.GetSize(); ++i)
		m_ctlDevicelist.AddString(m_list->m_list[i].m_friendlyname);
	m_ctlDevicelist.SetCurSel(i - 1);
	
	return TRUE;
}
