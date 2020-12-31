// TimeoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Serial.h"
#include "TimeoutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeoutDlg dialog


CTimeoutDlg::CTimeoutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeoutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeoutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_dwRxTimeout =
	m_dwTxTimeout = 0;
}


void CTimeoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeoutDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimeoutDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeoutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeoutDlg message handlers

void CTimeoutDlg::OnOK() 
{
	UpdateData(TRUE);
	CString sBuffer;

	//
	// Retreive the dialog data	
	//
	GetDlgItemText(IDC_TIMEOUT_RX, sBuffer);
	m_dwRxTimeout = _ttol(sBuffer);

	GetDlgItemText(IDC_TIMEOUT_TX, sBuffer);
	m_dwTxTimeout = _ttol(sBuffer);

	CDialog::OnOK();
}

BOOL CTimeoutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//
	// Set the dialog data
	//	
	TCHAR szBuffer[20];
	_ltot(m_dwRxTimeout, szBuffer, 10);
	SetDlgItemText(IDC_TIMEOUT_RX, szBuffer);

	_ltot(m_dwTxTimeout, szBuffer, 10);
	SetDlgItemText(IDC_TIMEOUT_TX, szBuffer);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
