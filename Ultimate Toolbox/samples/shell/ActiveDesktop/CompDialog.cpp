// CompDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ActiveDesktop.h"
#include "CompDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompDialog dialog


CCompDialog::CCompDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCompDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompDialog)
	m_bEnabled = FALSE;
	m_bScrollable = FALSE;
	m_bSizeable = FALSE;
	m_nHeight = 0;
	m_nLeft = 0;
	m_sName = _T("");
	m_sSource = _T("");
	m_nTop = 0;
	m_nWidth = 0;
	//}}AFX_DATA_INIT
	m_nAction=NULL;
}


void CCompDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompDialog)
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnabled);
	DDX_Check(pDX, IDC_CHECK_SCROLLABLE, m_bScrollable);
	DDX_Check(pDX, IDC_CHECK_SIZEABLE, m_bSizeable);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_nLeft);
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDX_Text(pDX, IDC_EDIT_SOURCE, m_sSource);
	DDX_Text(pDX, IDC_EDIT_TOP, m_nTop);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompDialog, CDialog)
	//{{AFX_MSG_MAP(CCompDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompDialog message handlers

void CCompDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CCompDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	switch (m_nAction)
	{
	case ACTION_NEW:
		{
			m_bEnabled=1;
			m_bScrollable=1;
			m_bSizeable=1;
			m_nHeight=60;
			m_nWidth=180;
			m_nLeft=240;
			m_nTop=180;
			m_sName=_T("Ultimate Toolbox");
			m_sSource=_T("http://www.theultimatetoolbox.com");
			CWnd* pWnd=GetDlgItem(IDC_STATIC_SOURCE);
			pWnd->SetWindowText(_T("URL"));
			UpdateData(FALSE);
			GetDlgItem(IDC_EDIT_WIDTH)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_LEFT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_TOP)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK_SIZEABLE)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SOURCE)->EnableWindow(TRUE);
		}
		break;
	case ACTION_MODIFY:
		GetDlgItem(IDC_EDIT_WIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_SIZEABLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SOURCE)->EnableWindow(FALSE);

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
