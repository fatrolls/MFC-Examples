// EventLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EventLog.h"
#include "EventLogDlg.h"

#include "UTSampleAbout.h"   

#include "msgs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventLogDlg dialog

CEventLogDlg::CEventLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEventLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEventLogDlg)
	m_nEvent = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEventLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventLogDlg)
	DDX_Control(pDX, IDC_RFR_BUTTON, m_ctlButtonRefresh);
	DDX_Control(pDX, IDC_REP_BUTTON, m_ctlButtonReport);
	DDX_Control(pDX, IDC_LIST_EVENTS, m_ctlListEvents);
	DDX_Radio(pDX, IDC_EVNT1_RADIO, m_nEvent);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventLogDlg, CDialog)
	//{{AFX_MSG_MAP(CEventLogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE_BUTTON, OnCreateButton)
	ON_BN_CLICKED(IDC_OPEN_BUTTON, OnOpenButton)
	ON_BN_CLICKED(IDC_REG_BUTTON, OnRegButton)
	ON_BN_CLICKED(IDC_REP_BUTTON, OnRepButton)
	ON_BN_CLICKED(IDC_RFR_BUTTON, OnRfrButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventLogDlg message handlers

BOOL CEventLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEventLogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg aboutDlg(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		aboutDlg.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEventLogDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEventLogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEventLogDlg::OnCreateButton() 
{
	// TODO: Add your control notification handler code here
	
	CString sMsgPath;

	::GetCurrentDirectory(_MAX_PATH, sMsgPath.GetBuffer(_MAX_PATH + 1));
	sMsgPath.ReleaseBuffer();
	sMsgPath += _T("\\messages.dll");

	DWORD dwOptions = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE |
					  EVENTLOG_INFORMATION_TYPE;

	if (!m_EventLog.CreateApplicationLog(_T("EventLog"), sMsgPath, dwOptions))
	{
		if (m_EventLog.GetErrorCode() == 5)
			// Display the string.
			AfxMessageBox(GetErrorMessage(m_EventLog.GetErrorCode()) +
				_T("\nyou'll need administrator priviledges to add this registry key"), MB_OK|MB_ICONINFORMATION);
		else
			// Display the string.
			AfxMessageBox(GetErrorMessage(m_EventLog.GetErrorCode()), MB_OK|MB_ICONINFORMATION);
	}
	else
		AfxMessageBox(_T("Creation succeeded"));

}

void CEventLogDlg::OnOpenButton() 
{
	// TODO: Add your control notification handler code here
	
	m_EventLog.Close();

	if (!m_EventLog.Open(_T("EventLog")))
	{
		// Display the string.
		AfxMessageBox(GetErrorMessage(m_EventLog.GetErrorCode()), MB_OK|MB_ICONINFORMATION);
		m_ctlButtonRefresh.EnableWindow(FALSE);
		return;
	}

	m_ctlButtonRefresh.EnableWindow(TRUE);
}

void CEventLogDlg::OnRegButton() 
{
	// TODO: Add your control notification handler code here
	
	if (!m_EventLog.RegisterSource(_T("EventLog")))
	{
		// Display the string.
		AfxMessageBox(GetErrorMessage(m_EventLog.GetErrorCode()), MB_OK|MB_ICONINFORMATION);
		return;
	}

	m_ctlButtonReport.EnableWindow(TRUE);
}

void CEventLogDlg::OnRepButton() 
{
	// TODO: Add your control notification handler code here
	
	if (UpdateData(TRUE))
	{
		LPCTSTR aInsertStrs[4];   /* array of pointers to insert
                                           strings */
		switch(m_nEvent)
		{
		case 0:
			{
				  /* Set up our array of insert strings for error message */
				aInsertStrs[0] = _T("test.cpp");
				aInsertStrs[1] = _T("Z");

				m_EventLog.Report(eventError, MSG_FILE_NOT_FOUND, 0, 2, aInsertStrs);
				break;
			}
		case 1:
			{
				m_EventLog.Report(eventWarning, MSG_UNABLE_START_GUARDIAN);
				break;
			}
		case 2:
			{
				  /* Set up our array of insert strings for error message */
				aInsertStrs[0] = _T("UNICORN");
				aInsertStrs[1] = _T("PERI");

				m_EventLog.Report(eventInformation, MSG_COMP_LOGGED_ON, 0, 2, aInsertStrs);
				break;
			}
		case 3:
			{
				m_EventLog.Report(eventInformation, MSG_ULTIMATE_TOOLBOX);
				break;
			}
		default:
			{
				TRACE0("not supported message");
			}
		}
	}
}

void CEventLogDlg::OnRfrButton() 
{
	// TODO: Add your control notification handler code here
	
	m_EventLog.Close();

	if (!m_EventLog.Open(_T("EventLog")))
	{
		// Display the string.
		AfxMessageBox(GetErrorMessage(m_EventLog.GetErrorCode()), MB_OK|MB_ICONINFORMATION);
		return;
	}

	m_ctlListEvents.ResetContent();

	BYTE bBuffer[512];            /* hold the event log record raw data */
	EVENTLOGRECORD* pevlr;
	pevlr = (EVENTLOGRECORD*)&bBuffer;

	DWORD dwRead = sizeof(bBuffer);

	CString sListLine;
	while (m_EventLog.Read(0,			 /* ignored for sequential reads */
							bBuffer,     /* address of buffer            */
							dwRead))     /* size of buffer as input and count of bytes read as output */
	{
		while (dwRead > 0)
		{
		    // List the event ID, type, and source name. The source name is
			// just past the end of the formal structure.
			sListLine.Format(_T("Event ID: 0x%08X EventType: %d Source: %s"),
									pevlr->EventID, pevlr->EventType, 
									(LPTSTR)((LPBYTE) pevlr + sizeof(EVENTLOGRECORD)));
			
			m_ctlListEvents.SetItemData(m_ctlListEvents.AddString(sListLine),
				pevlr->EventID);
			// Subtract the size of the event log record we just read
		    dwRead -= pevlr->Length;
			// Point to the next event log record in the buffer
			pevlr = (EVENTLOGRECORD*)((LPBYTE)pevlr + pevlr->Length);
		}

		// reset our event log record pointer back to the beginning of the
		// buffer in preparation for reading the next record.
		pevlr = (EVENTLOGRECORD*)&bBuffer;
		dwRead = sizeof(bBuffer);
	}
}
