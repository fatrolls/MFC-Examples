// About v2.0

#include "stdafx.h"
#include "About.h"

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ABOUT_EMAIL, m_ctrlEmail);
	//}}AFX_DATA_MAP
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString s = _T("");
	s.Format(_T("_MSC_VER=%d  _MFC_VER=0x%X  WINVER=0x%X  _WIN32_WINNT=0x%X  _WIN32_IE=0x%X "),
		_MSC_VER, _MFC_VER, WINVER, _WIN32_WINNT, _WIN32_IE);
	GetDlgItem(IDC_VERSION)->SetWindowText(s);

	CString strMailTo = _T("");
	strMailTo.LoadString(IDS_MAILTO);

	m_ctrlEmail.SetURL(strMailTo);

	CenterWindow();

	return TRUE;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->m_hWnd == GetDlgItem(IDC_VERSION)->m_hWnd)
	{
		pDC->SetBkColor(RGB(255,255,255));
		hbr = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	}
	
	return hbr;
}
