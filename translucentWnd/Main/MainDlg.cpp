
// MainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CMainDlg::CMainDlg(CWnd* pParent/*=NULL*/) : CImgWnd(L"background.png", IDD, pParent)
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CImgWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CImgWnd)
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CImgWnd::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}