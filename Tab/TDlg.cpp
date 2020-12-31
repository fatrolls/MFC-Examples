// TDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tab.h"
#include "TDlg.h"


// CTDlg dialog

CTabCtrl CTDlg::m_tab;

IMPLEMENT_DYNAMIC(CTDlg, CDialog)

CTDlg::CTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTDlg::IDD, pParent)
{

}

CTDlg::~CTDlg()
{
}

void CTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}


BEGIN_MESSAGE_MAP(CTDlg, CDialog)
END_MESSAGE_MAP()


// CTDlg message handlers
