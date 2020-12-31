// UrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyBrowser.h"
#include "UrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// UrlDlg dialog


UrlDlg::UrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(UrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(UrlDlg)
	m_Edit = _T("");
	//}}AFX_DATA_INIT
}


void UrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(UrlDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(UrlDlg, CDialog)
	//{{AFX_MSG_MAP(UrlDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// UrlDlg message handlers

BOOL UrlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	GetDlgItem( IDC_EDIT1 )->SetFocus();
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
