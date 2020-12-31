// CustomizeAssertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "advancedassert.h"
#include "CustomizeAssertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeAssertDlg dialog


CCustomizeAssertDlg::CCustomizeAssertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomizeAssertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomizeAssertDlg)
	m_bSendMail = FALSE;
	m_sEmailAddress = _T("");
	m_sNote1 = _T("");
	m_sNote2 = _T("");
	//}}AFX_DATA_INIT
}


void CCustomizeAssertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomizeAssertDlg)
	DDX_Check(pDX, IDC_CHECK_SENDMAIL, m_bSendMail);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_sEmailAddress);
	DDX_Text(pDX, IDC_EDIT_NOTE1, m_sNote1);
	DDX_Text(pDX, IDC_EDIT_NOTE2, m_sNote2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomizeAssertDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomizeAssertDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeAssertDlg message handlers

void CCustomizeAssertDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
