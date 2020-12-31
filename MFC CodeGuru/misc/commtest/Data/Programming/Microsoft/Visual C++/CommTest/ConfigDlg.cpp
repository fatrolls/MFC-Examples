/*
**	FILENAME			ConfigDlg.cpp
**
**	PURPOSE				Here the ports can be configured
**
**	CREATION DATE		15-09-1997
**	LAST MODIFICATION	12-11-1997
**
**	AUTHOR				Remon Spekreijse
**
*/


#include "stdafx.h"
#include "commtest.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_strBaudRate = _T("");
	m_strDataBits = _T("");
	m_strParity = _T("");
	m_strStopBits = _T("");
	m_CommBreakDetected = FALSE;
	m_CommCTSDetected = FALSE;
	m_CommDSRDetected = FALSE;
	m_CommERRDetected = FALSE;
	m_CommRingDetected = FALSE;
	m_CommRLSDDetected = FALSE;
	m_CommRxchar = TRUE;
	m_CommRxcharFlag = FALSE;
	m_CommTXEmpty = FALSE;
	m_strSendBuffer = _T("");
	//}}AFX_DATA_INIT
}

CConfigDlg::CConfigDlg(CWnd* pParent, DCB dcb)
	: CDialog(CConfigDlg::IDD, pParent)
{
	m_dcb = dcb;
}



void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_CBString(pDX, IDC_BAUDRATECOMBO, m_strBaudRate);
	DDX_CBString(pDX, IDC_DATABITSCOMBO, m_strDataBits);
	DDX_CBString(pDX, IDC_PARITYCOMBO, m_strParity);
	DDX_CBString(pDX, IDC_STOPBITSCOMBO, m_strStopBits);
	DDX_Check(pDX, IDC_CHECK1, m_CommBreakDetected);
	DDX_Check(pDX, IDC_CHECK2, m_CommCTSDetected);
	DDX_Check(pDX, IDC_CHECK3, m_CommDSRDetected);
	DDX_Check(pDX, IDC_CHECK4, m_CommERRDetected);
	DDX_Check(pDX, IDC_CHECK5, m_CommRingDetected);
	DDX_Check(pDX, IDC_CHECK6, m_CommRLSDDetected);
	DDX_Check(pDX, IDC_CHECK7, m_CommRxchar);
	DDX_Check(pDX, IDC_CHECK8, m_CommRxcharFlag);
	DDX_Check(pDX, IDC_CHECK9, m_CommTXEmpty);
	DDX_CBString(pDX, IDC_SENDBUFFERCOMBO, m_strSendBuffer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString strTemp;
	strTemp.Format("%d", m_dcb.BaudRate);
	((CComboBox*)GetDlgItem(IDC_BAUDRATECOMBO))->SelectString(0, strTemp);

	((CComboBox*)GetDlgItem(IDC_PARITYCOMBO))->SetCurSel(m_dcb.Parity);

	((CComboBox*)GetDlgItem(IDC_STOPBITSCOMBO))->SetCurSel(m_dcb.StopBits);

	strTemp.Format("%d", m_dcb.ByteSize);
	((CComboBox*)GetDlgItem(IDC_DATABITSCOMBO))->SelectString(0, strTemp);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
																  

