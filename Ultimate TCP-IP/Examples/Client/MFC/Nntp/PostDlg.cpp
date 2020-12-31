// PostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NNTPclient.h"
#include "PostDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostDlg dialog


CPostDlg::CPostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPostDlg)
	m_strArtBody = _T("This is a test. I love NNTP 8-p");
	m_strSubject = _T("Test (please Ignore)");
	m_strFrom = _T("\"Your Name\" <youremail@yourdomain.com>");
	m_strTargetNewsGroups = _T("microsoft.test");
	//}}AFX_DATA_INIT
}


void CPostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPostDlg)
	DDX_Text(pDX, IDC_ART_BODY, m_strArtBody);
	DDX_Text(pDX, IDC_EDIT2, m_strSubject);
	DDX_Text(pDX, IDC_EDIT1, m_strFrom);
	DDX_Text(pDX, IDC_TARGET_NEWS_GROUPS, m_strTargetNewsGroups);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPostDlg, CDialog)
	//{{AFX_MSG_MAP(CPostDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostDlg message handlers

void CPostDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialog::OnOK();

	
}

void CPostDlg::OnButton1() 
{
	static _TCHAR szFilter[] = _T("All Files (*.*)|*.*||");
 	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, szFilter, this);

	dlg.m_ofn.lpstrTitle = _T("Select a single attachment");
	
	if (dlg.DoModal() == IDOK)
		m_sAttachment = dlg.GetPathName();

}
