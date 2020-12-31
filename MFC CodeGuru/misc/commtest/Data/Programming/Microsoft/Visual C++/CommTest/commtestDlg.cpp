/*
**	FILENAME			CommTestDlg.cpp
**
**	PURPOSE				This is the dialog that shows the comm activity.
**
**	CREATION DATE		15-09-1997
**	LAST MODIFICATION	12-11-1997
**
**	AUTHOR				Remon Spekreijse
**
*/

#include "stdafx.h"
#include "commtest.h"
#include "commtestDlg.h"
#include "configdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCommtestDlg::CCommtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommtestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommtestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommtestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCommtestDlg, CDialog)
	//{{AFX_MSG_MAP(CCommtestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnSendButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnSendButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnSendButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnSendButton4)
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_MESSAGE(WM_COMM_CTS_DETECTED, OnCTSDetected)
	ON_BN_CLICKED(IDC_BUTTON7, OnClearButton1)
	ON_BN_CLICKED(IDC_BUTTON8, OnClearButton2)
	ON_BN_CLICKED(IDC_BUTTON9, OnClearButton3)
	ON_BN_CLICKED(IDC_BUTTON10, OnClearButton4)
	ON_BN_CLICKED(IDC_CONFIGBUTTON1, OnConfigbutton1)
	ON_BN_CLICKED(IDC_CONFIGBUTTON2, OnConfigbutton2)
	ON_BN_CLICKED(IDC_CONFIGBUTTON3, OnConfigbutton3)
	ON_BN_CLICKED(IDC_CONFIGBUTTON4, OnConfigbutton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCommtestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_ListBox[0].SubclassDlgItem(IDC_LIST1, this);
	m_ListBox[1].SubclassDlgItem(IDC_LIST2, this);
	m_ListBox[2].SubclassDlgItem(IDC_LIST3, this);
	m_ListBox[3].SubclassDlgItem(IDC_LIST4, this);

	m_Edit[0].SubclassDlgItem(IDC_EDIT1, this);
	m_Edit[1].SubclassDlgItem(IDC_EDIT2, this);
	m_Edit[2].SubclassDlgItem(IDC_EDIT3, this);
	m_Edit[3].SubclassDlgItem(IDC_EDIT4, this);

	// init the ports
	for (int i = 0; i < 4; i++)
	{
		if (m_Ports[i].InitPort(this, i + 1, i == 0 ? 9600 : 19200))
			m_Ports[i].StartMonitoring();
		else
		{
			// port not found
			m_Edit[i].SetWindowText("NOT FOUND");
			m_Edit[i].EnableWindow(FALSE);
			m_ListBox[i].EnableWindow(FALSE);
		}
			
	}
			
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCommtestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CCommtestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCommtestDlg::OnSendButton1() 
{
	char buf[100];
	memset(&buf, 0, sizeof(buf));
	GetDlgItemText(IDC_EDIT1, buf, sizeof(buf));
	if (strcmp("NOT FOUND", buf) == 0)
		return;

	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
		buf[strlen(buf)] = 13;
	m_Ports[0].WriteToPort(buf);	
}

void CCommtestDlg::OnSendButton2() 
{
	char buf[100];
	memset(&buf, 0, sizeof(buf));
	GetDlgItemText(IDC_EDIT2, buf, sizeof(buf));
	if (strcmp("NOT FOUND", buf) == 0)
		return;

	if (((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
		buf[strlen(buf)] = 13;
	m_Ports[1].WriteToPort(buf);	
}

void CCommtestDlg::OnSendButton3() 
{
	char buf[100];
	memset(&buf, 0, sizeof(buf));
	GetDlgItemText(IDC_EDIT3, buf, sizeof(buf));
	if (strcmp("NOT FOUND", buf) == 0)
		return;
	
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
		buf[strlen(buf)] = 13;
	m_Ports[2].WriteToPort(buf);	
}

void CCommtestDlg::OnSendButton4() 
{
	char buf[100];
	memset(&buf, 0, sizeof(buf));
	GetDlgItemText(IDC_EDIT4, buf, sizeof(buf));
	if (strcmp("NOT FOUND", buf) == 0)
		return;

	if (((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck())
		buf[strlen(buf)] = 13;
	m_Ports[3].WriteToPort(buf);
}

LONG CCommtestDlg::OnCommunication(WPARAM ch, LPARAM port)
{
	if (port <= 0 || port > 4)
		return -1;

	if (ch == 13 && ((CButton*)GetDlgItem(IDC_CHECK5 + port - 1))->GetCheck())
	{
		m_ListBox[port-1].AddString(m_strReceived[port-1]);
		m_ListBox[port-1].SetSel(m_ListBox[port-1].GetCount()-1, TRUE);
		(m_strReceived[port-1]).Empty();
	}
	else if (((CButton*)GetDlgItem(IDC_CHECK5 + port - 1))->GetCheck())
		m_strReceived[port-1] += (char)ch;
	else
	{
		CString string;
		string += (char)ch;
		m_ListBox[port-1].AddString(string);
		m_ListBox[port-1].SetSel(m_ListBox[port-1].GetCount()-1, TRUE);
	}

	return 0;
}

LONG CCommtestDlg::OnCTSDetected(WPARAM, LPARAM port)
{
	if (port <= 0 || port > 4)
		return -1;

	CString string;
	string = "Clear To Send";
	m_ListBox[port-1].AddString(string);
	m_ListBox[port-1].SetSel(m_ListBox[port-1].GetCount()-1, TRUE);

	return 0;
}


void CCommtestDlg::OnClearButton1() 
{
	m_ListBox[0].ResetContent();
}

void CCommtestDlg::OnClearButton2() 
{
	m_ListBox[1].ResetContent();
}

void CCommtestDlg::OnClearButton3() 
{
	m_ListBox[2].ResetContent();
}

void CCommtestDlg::OnClearButton4() 
{
	m_ListBox[3].ResetContent();
}

void CCommtestDlg::OnConfigbutton1() 
{
	CConfigDlg* dlg = new CConfigDlg(this, m_Ports[0].GetDCB());
	dlg->m_strSendBuffer.Format("%d", m_Ports[0].GetWriteBufferSize());
	
	DWORD dwCommEvents = m_Ports[0].GetCommEvents();
	dlg->m_CommBreakDetected = (dwCommEvents & EV_BREAK) > 0 ? TRUE : FALSE;
	dlg->m_CommCTSDetected   = (dwCommEvents & EV_CTS) > 0 ? TRUE : FALSE;
	dlg->m_CommDSRDetected   = (dwCommEvents & EV_DSR) > 0 ? TRUE : FALSE;
	dlg->m_CommERRDetected   = (dwCommEvents & EV_ERR) > 0 ? TRUE : FALSE;
	dlg->m_CommRingDetected  = (dwCommEvents & EV_RING) > 0 ? TRUE : FALSE;
	dlg->m_CommRLSDDetected  = (dwCommEvents & EV_RLSD) > 0 ? TRUE : FALSE;
	dlg->m_CommRxchar        = (dwCommEvents & EV_RXCHAR) > 0 ? TRUE : FALSE;
	dlg->m_CommRxcharFlag    = (dwCommEvents & EV_RXFLAG) > 0 ? TRUE : FALSE;
	dlg->m_CommTXEmpty       = (dwCommEvents & EV_TXEMPTY) > 0 ? TRUE : FALSE;

	if (dlg->DoModal() == IDOK)
	{
		DWORD dwCommEvents = 0;
		if (dlg->m_CommBreakDetected)
			dwCommEvents |= EV_BREAK;
		if (dlg->m_CommCTSDetected)
			dwCommEvents |= EV_CTS;
		if (dlg->m_CommDSRDetected)
			dwCommEvents |= EV_DSR;
		if (dlg->m_CommERRDetected)
			dwCommEvents |= EV_ERR;
		if (dlg->m_CommRingDetected)
			dwCommEvents |= EV_RING;
		if (dlg->m_CommRLSDDetected)
			dwCommEvents |= EV_RLSD;
		if (dlg->m_CommRxchar)
			dwCommEvents |= EV_RXCHAR;
		if (dlg->m_CommRxcharFlag)
			dwCommEvents |= EV_RXFLAG;
		if (dlg->m_CommTXEmpty)
			dwCommEvents |= EV_TXEMPTY;

		m_Ports[0].InitPort(this, 1, 
			atoi(dlg->m_strBaudRate),
			dlg->m_strParity[0],
			atoi(dlg->m_strDataBits),
			atoi(dlg->m_strStopBits),
			dwCommEvents,
			atoi(dlg->m_strSendBuffer));

		m_Ports[0].StartMonitoring();
	}
	
	delete dlg;
}

void CCommtestDlg::OnConfigbutton2() 
{
	CConfigDlg* dlg = new CConfigDlg(this, m_Ports[1].GetDCB());
	
	DWORD dwCommEvents = m_Ports[1].GetCommEvents();
	
	dlg->m_strSendBuffer.Format("%d", m_Ports[1].GetWriteBufferSize());
	dlg->m_CommBreakDetected = (dwCommEvents & EV_BREAK) > 0 ? TRUE : FALSE;
	dlg->m_CommCTSDetected   = (dwCommEvents & EV_CTS) > 0 ? TRUE : FALSE;
	dlg->m_CommDSRDetected   = (dwCommEvents & EV_DSR) > 0 ? TRUE : FALSE;
	dlg->m_CommERRDetected   = (dwCommEvents & EV_ERR) > 0 ? TRUE : FALSE;
	dlg->m_CommRingDetected  = (dwCommEvents & EV_RING) > 0 ? TRUE : FALSE;
	dlg->m_CommRLSDDetected  = (dwCommEvents & EV_RLSD) > 0 ? TRUE : FALSE;
	dlg->m_CommRxchar        = (dwCommEvents & EV_RXCHAR) > 0 ? TRUE : FALSE;
	dlg->m_CommRxcharFlag    = (dwCommEvents & EV_RXFLAG) > 0 ? TRUE : FALSE;
	dlg->m_CommTXEmpty       = (dwCommEvents & EV_TXEMPTY) > 0 ? TRUE : FALSE;

	if (dlg->DoModal() == IDOK)
	{
		dwCommEvents = 0;
		if (dlg->m_CommBreakDetected)
			dwCommEvents |= EV_BREAK;
		if (dlg->m_CommCTSDetected)
			dwCommEvents |= EV_CTS;
		if (dlg->m_CommDSRDetected)
			dwCommEvents |= EV_DSR;
		if (dlg->m_CommERRDetected)
			dwCommEvents |= EV_ERR;
		if (dlg->m_CommRingDetected)
			dwCommEvents |= EV_RING;
		if (dlg->m_CommRLSDDetected)
			dwCommEvents |= EV_RLSD;
		if (dlg->m_CommRxchar)
			dwCommEvents |= EV_RXCHAR;
		if (dlg->m_CommRxcharFlag)
			dwCommEvents |= EV_RXFLAG;
		if (dlg->m_CommTXEmpty)
			dwCommEvents |= EV_TXEMPTY;

		m_Ports[1].InitPort(this, 2, 
			atoi(dlg->m_strBaudRate),
			dlg->m_strParity[0],
			atoi(dlg->m_strDataBits),
			atoi(dlg->m_strStopBits),
			dwCommEvents,
			atoi(dlg->m_strSendBuffer));

		m_Ports[1].StartMonitoring();
	}
	
	delete dlg;

}

void CCommtestDlg::OnConfigbutton3() 
{
	CConfigDlg* dlg = new CConfigDlg(this, m_Ports[2].GetDCB());

	DWORD dwCommEvents = m_Ports[2].GetCommEvents();
	
	dlg->m_strSendBuffer.Format("%d", m_Ports[2].GetWriteBufferSize());
	dlg->m_CommBreakDetected = (dwCommEvents & EV_BREAK) > 0 ? TRUE : FALSE;
	dlg->m_CommCTSDetected   = (dwCommEvents & EV_CTS) > 0 ? TRUE : FALSE;
	dlg->m_CommDSRDetected   = (dwCommEvents & EV_DSR) > 0 ? TRUE : FALSE;
	dlg->m_CommERRDetected   = (dwCommEvents & EV_ERR) > 0 ? TRUE : FALSE;
	dlg->m_CommRingDetected  = (dwCommEvents & EV_RING) > 0 ? TRUE : FALSE;
	dlg->m_CommRLSDDetected  = (dwCommEvents & EV_RLSD) > 0 ? TRUE : FALSE;
	dlg->m_CommRxchar        = (dwCommEvents & EV_RXCHAR) > 0 ? TRUE : FALSE;
	dlg->m_CommRxcharFlag    = (dwCommEvents & EV_RXFLAG) > 0 ? TRUE : FALSE;
	dlg->m_CommTXEmpty       = (dwCommEvents & EV_TXEMPTY) > 0 ? TRUE : FALSE;

	if (dlg->DoModal() == IDOK)
	{
		dwCommEvents = 0;

		if (dlg->m_CommBreakDetected)
			dwCommEvents |= EV_BREAK;
		if (dlg->m_CommCTSDetected)
			dwCommEvents |= EV_CTS;
		if (dlg->m_CommDSRDetected)
			dwCommEvents |= EV_DSR;
		if (dlg->m_CommERRDetected)
			dwCommEvents |= EV_ERR;
		if (dlg->m_CommRingDetected)
			dwCommEvents |= EV_RING;
		if (dlg->m_CommRLSDDetected)
			dwCommEvents |= EV_RLSD;
		if (dlg->m_CommRxchar)
			dwCommEvents |= EV_RXCHAR;
		if (dlg->m_CommRxcharFlag)
			dwCommEvents |= EV_RXFLAG;
		if (dlg->m_CommTXEmpty)
			dwCommEvents |= EV_TXEMPTY;

		m_Ports[2].InitPort(this, 3, 
			atoi(dlg->m_strBaudRate),
			dlg->m_strParity[0],
			atoi(dlg->m_strDataBits),
			atoi(dlg->m_strStopBits),
			dwCommEvents,
			atoi(dlg->m_strSendBuffer));

		m_Ports[2].StartMonitoring();
	}
	
	delete dlg;

}

void CCommtestDlg::OnConfigbutton4() 
{
	CConfigDlg* dlg = new CConfigDlg(this, m_Ports[3].GetDCB());

	DWORD dwCommEvents = m_Ports[3].GetCommEvents();
	
	dlg->m_strSendBuffer.Format("%d", m_Ports[3].GetWriteBufferSize());
	dlg->m_CommBreakDetected = (dwCommEvents & EV_BREAK) > 0 ? TRUE : FALSE;
	dlg->m_CommCTSDetected   = (dwCommEvents & EV_CTS) > 0 ? TRUE : FALSE;
	dlg->m_CommDSRDetected   = (dwCommEvents & EV_DSR) > 0 ? TRUE : FALSE;
	dlg->m_CommERRDetected   = (dwCommEvents & EV_ERR) > 0 ? TRUE : FALSE;
	dlg->m_CommRingDetected  = (dwCommEvents & EV_RING) > 0 ? TRUE : FALSE;
	dlg->m_CommRLSDDetected  = (dwCommEvents & EV_RLSD) > 0 ? TRUE : FALSE;
	dlg->m_CommRxchar        = (dwCommEvents & EV_RXCHAR) > 0 ? TRUE : FALSE;
	dlg->m_CommRxcharFlag    = (dwCommEvents & EV_RXFLAG) > 0 ? TRUE : FALSE;
	dlg->m_CommTXEmpty       = (dwCommEvents & EV_TXEMPTY) > 0 ? TRUE : FALSE;

	if (dlg->DoModal() == IDOK)
	{
		dwCommEvents = 0;

		if (dlg->m_CommBreakDetected)
			dwCommEvents |= EV_BREAK;
		if (dlg->m_CommCTSDetected)
			dwCommEvents |= EV_CTS;
		if (dlg->m_CommDSRDetected)
			dwCommEvents |= EV_DSR;
		if (dlg->m_CommERRDetected)
			dwCommEvents |= EV_ERR;
		if (dlg->m_CommRingDetected)
			dwCommEvents |= EV_RING;
		if (dlg->m_CommRLSDDetected)
			dwCommEvents |= EV_RLSD;
		if (dlg->m_CommRxchar)
			dwCommEvents |= EV_RXCHAR;
		if (dlg->m_CommRxcharFlag)
			dwCommEvents |= EV_RXFLAG;
		if (dlg->m_CommTXEmpty)
			dwCommEvents |= EV_TXEMPTY;

		m_Ports[3].InitPort(this, 4, 
			atoi(dlg->m_strBaudRate),
			dlg->m_strParity[0],
			atoi(dlg->m_strDataBits),
			atoi(dlg->m_strStopBits),
			dwCommEvents,
			atoi(dlg->m_strSendBuffer));

		m_Ports[3].StartMonitoring();
	}
	
	delete dlg;
}
