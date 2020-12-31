// ServiceDlg.cpp : implementation file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#include "stdafx.h"
#include "utsampleabout.h"
#include "Service.h"
#include "ServiceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ACTION_GOBACK				0
#define ACTION_ITERDEPEND			1
#define ACTION_START				2
#define ACTION_PAUSE				3
#define ACTION_CONTINUE				4
#define ACTION_STOP					5
#define ACTION_GET_SERVICESTATUS	6
#define ACTION_GET_DISPLAYNAME		7
#define ACTION_GET_SERVICETYPE		8
#define ACTION_GET_STARTYPE			9
#define ACTION_GET_ERRORCONTROL		10
#define ACTION_GET_BINARYPATHNAME	11
#define ACTION_GET_LOADORDERGROUP	12
#define ACTION_GET_TAGID			13
#define ACTION_GET_DEPENDENCIES		14
#define ACTION_GET_STARTNAME		15

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CServiceDlg dialog

CServiceDlg::CServiceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServiceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServiceDlg)
	m_sDisplayName = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServiceDlg)
	DDX_Control(pDX, IDC_LIST_SERVICE, m_ctrlListService);
	DDX_Control(pDX, IDC_LIST_ACTION, m_ctrlListAction);
	DDX_LBString(pDX, IDC_LIST_SERVICE, m_sDisplayName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServiceDlg, CDialog)
	//{{AFX_MSG_MAP(CServiceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_DBLCLK(IDC_LIST_ACTION, OnDblclkListAction)
	ON_LBN_DBLCLK(IDC_LIST_SERVICE, OnDblclkListService)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServiceDlg message handlers

CServiceDlg::~CServiceDlg()
{
	COXService::CloseSCManager();
}

BOOL CServiceDlg::OnInitDialog()
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_ctrlListAction.AddString(_T("(go back)"));
	m_ctrlListAction.AddString(_T("(enum dependents)"));
	m_ctrlListAction.AddString(_T("Start"));
	m_ctrlListAction.AddString(_T("Pause"));
	m_ctrlListAction.AddString(_T("Continue"));
	m_ctrlListAction.AddString(_T("Stop"));
	m_ctrlListAction.AddString(_T("QueryStatus"));
	m_ctrlListAction.AddString(_T("QueryDisplayName"));
	m_ctrlListAction.AddString(_T("QueryServiceType"));
	m_ctrlListAction.AddString(_T("QueryStartType"));
	m_ctrlListAction.AddString(_T("QueryErrorControl"));
	m_ctrlListAction.AddString(_T("QueryBinaryPathName"));
	m_ctrlListAction.AddString(_T("QueryLoadOrderGroup"));
	m_ctrlListAction.AddString(_T("QueryTagID"));
	m_ctrlListAction.AddString(_T("QueryDependencies"));
	m_ctrlListAction.AddString(_T("QueryStartName"));

	if (m_itersrv.StartIteration())
		UpdateServiceList();
	else
		AfxMessageBox(_T("Failed to enumerate services."));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServiceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServiceDlg::OnPaint() 
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

HCURSOR CServiceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CServiceDlg::OnDblclkListAction() 
{
	OnOK();
}

void CServiceDlg::OnDblclkListService() 
{
	OnOK();
}

void CServiceDlg::OnOK() 
{
	if (m_ctrlListAction.GetCurSel() != ACTION_GOBACK &&
	   (m_ctrlListService.GetCurSel() == LB_ERR || 
		m_ctrlListAction.GetCurSel() == LB_ERR))
		{
		AfxMessageBox(_T("Please follow step 1, 2 and then 3."));
		return;
		}

	UpdateData(TRUE);
	COXIteratorService itersrv(COXService::QueryKeyName(m_sDisplayName));
	switch(m_ctrlListAction.GetCurSel())
		{
		case ACTION_GOBACK:
			if (m_itersrvLast.GetServiceCount() > 0)
				{
				m_itersrv = m_itersrvLast;
				m_itersrvLast.End();
				}
			else
				m_itersrv.StartIteration();
			UpdateServiceList();
			break;
		case ACTION_ITERDEPEND:
			m_itersrvLast = m_itersrv;
			m_itersrv = itersrv;
			m_itersrv.StartDependentIteration();
			UpdateServiceList();
			break;
		case ACTION_START:
			if (Confirm()) ReportIfFail(itersrv.Start()); break;
		case ACTION_PAUSE:
			if (Confirm()) ReportIfFail(itersrv.Pause()); break;
		case ACTION_CONTINUE:
			if (Confirm()) ReportIfFail(itersrv.Continue()); break;
		case ACTION_STOP:
			if (Confirm()) ReportIfFail(itersrv.Stop()); break;
		case ACTION_GET_SERVICESTATUS:
			SERVICE_STATUS ss;
			itersrv.QueryStatus(&ss, TRUE);
			OutputStatus(&ss);
			break;
		case ACTION_GET_DISPLAYNAME:
			OutputString(itersrv.QueryDisplayName()); break;
		case ACTION_GET_SERVICETYPE:
			OutputDword(itersrv.QueryServiceType(), ACTION_GET_SERVICETYPE); break;
		case ACTION_GET_STARTYPE:
			OutputDword(itersrv.QueryStartType(), ACTION_GET_STARTYPE); break;
		case ACTION_GET_ERRORCONTROL:
			OutputDword(itersrv.QueryErrorControl(), ACTION_GET_ERRORCONTROL); break;
		case ACTION_GET_BINARYPATHNAME:
			OutputString(itersrv.QueryBinaryPathName()); break;
		case ACTION_GET_LOADORDERGROUP:
			OutputString(itersrv.QueryLoadOrderGroup()); break;
		case ACTION_GET_TAGID:
			OutputDword(itersrv.QueryTagId(), ACTION_GET_TAGID); break;
		case ACTION_GET_DEPENDENCIES:
			OutputString(BarToCR(itersrv.QueryDependencies())); break;
		case ACTION_GET_STARTNAME:
			OutputString(itersrv.QueryStartName()); break;
		}
}

BOOL CServiceDlg::Confirm()
{
	return AfxMessageBox(_T("Proceed? "), MB_OKCANCEL | MB_ICONQUESTION)
		== IDOK;
}

void CServiceDlg::OutputString(LPCTSTR sOut)
{
	CString sOutput = sOut;
	if (sOutput.IsEmpty()) sOutput = _T("(empty)");
	AfxMessageBox(sOutput, MB_OK | MB_ICONINFORMATION);
}

void CServiceDlg::OutputDword(DWORD dwOut, int nActionCode)
{
	CString sOut;
	switch(nActionCode)
	{
	case ACTION_GET_SERVICETYPE:
		if (dwOut & SERVICE_WIN32_OWN_PROCESS)
			sOut = _T("SERVICE_WIN32_OWN_PROCESS");
		else if (dwOut & SERVICE_WIN32_SHARE_PROCESS)
			sOut = _T("SERVICE_WIN32_SHARE_PROCESS");
		else if (dwOut & SERVICE_KERNEL_DRIVER)
			sOut = _T("SERVICE_KERNEL_DRIVER");
		else if (dwOut & SERVICE_FILE_SYSTEM_DRIVER)
			sOut = _T("SERVICE_FILE_SYSTEM_DRIVER");

		if (dwOut & SERVICE_INTERACTIVE_PROCESS)
			sOut += _T(" | SERVICE_INTERACTIVE_PROCESS");

		OutputString(sOut);
		break;
	case ACTION_GET_STARTYPE:
		switch(dwOut)
			{
			case SERVICE_BOOT_START:
				OutputString(_T("SERVICE_BOOT_START"));
				break;
			case SERVICE_SYSTEM_START: 
				OutputString(_T("SERVICE_SYSTEM_START"));
				break;
			case SERVICE_AUTO_START: 
				OutputString(_T("SERVICE_AUTO_START"));
				break;
			case SERVICE_DEMAND_START:
				OutputString(_T("SERVICE_DEMAND_START"));
				break;
			case SERVICE_DISABLED:
				OutputString(_T("SERVICE_DISABLED"));
				break;
			default:
				OutputString(_T("unknown start type"));
			}
		break;
	case ACTION_GET_ERRORCONTROL:
		switch(dwOut)
			{
			case SERVICE_ERROR_IGNORE:
				OutputString(_T("SERVICE_ERROR_IGNORE"));
				break;
			case SERVICE_ERROR_NORMAL: 
				OutputString(_T("SERVICE_ERROR_NORMAL"));
				break;
			case SERVICE_ERROR_SEVERE: 
				OutputString(_T("SERVICE_ERROR_SEVERE"));
				break;
			case SERVICE_ERROR_CRITICAL: 
				OutputString(_T("SERVICE_ERROR_CRITICAL"));
				break;
			default:
				OutputString(_T("unknown error control"));
			}
 		break;
	default:
		sOut.Format(_T("%d"), dwOut);
		OutputString(sOut);
	}
}

void CServiceDlg::OutputStatus(LPSERVICE_STATUS lpss)
{
	CString sOut = _T("Service Status:\r\n");

	// DWORD dwServiceType; 
	sOut += _T("\r\nService Type:\t");
	if (lpss->dwServiceType & SERVICE_WIN32_OWN_PROCESS)
		sOut += _T("SERVICE_WIN32_OWN_PROCESS");
	else if (lpss->dwServiceType & SERVICE_WIN32_SHARE_PROCESS)
		sOut += _T("SERVICE_WIN32_SHARE_PROCESS");
	else if (lpss->dwServiceType & SERVICE_KERNEL_DRIVER)
		sOut += _T("SERVICE_KERNEL_DRIVER");
	else if (lpss->dwServiceType & SERVICE_FILE_SYSTEM_DRIVER)
		sOut += _T("SERVICE_FILE_SYSTEM_DRIVER");

	if (lpss->dwServiceType & SERVICE_INTERACTIVE_PROCESS)
		sOut += _T("\r\n\t\tSERVICE_INTERACTIVE_PROCESS");

    // DWORD dwCurrentState; 
 	sOut += _T("\r\nCurrent State:\t");
	switch (lpss->dwCurrentState)
		{
		case SERVICE_STOPPED:
			sOut += _T("SERVICE_STOPPED"); break;
		case SERVICE_START_PENDING:
			sOut += _T("SERVICE_START_PENDING"); break;
		case SERVICE_STOP_PENDING:
			sOut += _T("SERVICE_STOP_PENDING"); break;
		case SERVICE_RUNNING:
			sOut += _T("SERVICE_RUNNING"); break;
		case SERVICE_CONTINUE_PENDING:
			sOut += _T("SERVICE_CONTINUE_PENDING"); break;
		case SERVICE_PAUSE_PENDING:
			sOut += _T("SERVICE_PAUSE_PENDING"); break;
		case SERVICE_PAUSED:
			sOut += _T("SERVICE_PAUSED"); break;
		default:
			sOut += _T("(unknown)");
		}

	// DWORD dwControlsAccepted;
	sOut += _T("\r\nControls Accepted:\t");
	if (lpss->dwControlsAccepted & SERVICE_ACCEPT_STOP)
		sOut += _T("SERVICE_ACCEPT_STOP");
	else if (lpss->dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE)
		sOut += _T("SERVICE_ACCEPT_PAUSE_CONTINUE");
	else if (lpss->dwControlsAccepted & SERVICE_ACCEPT_SHUTDOWN)
		sOut += _T("SERVICE_ACCEPT_SHUTDOWN");
	
	if (lpss->dwControlsAccepted & SERVICE_CONTROL_INTERROGATE)
		sOut += _T("\r\n\t\tSERVICE_CONTROL_INTERROGATE");

    // DWORD dwWin32ExitCode; 
    // DWORD dwServiceSpecificExitCode; 
    // DWORD dwCheckPoint; 
    // DWORD dwWaitHint; 
	CString sFmt, sTemp;
	sFmt = _T("\r\nWin32 Exit Code:\t%d");
	sFmt += _T("\r\nSpecific Exit Code:\t%d");
	sFmt += _T("\r\nCheck Point:\t%d");
	sFmt += _T("\r\nWait Hint:\t\t%d");

	sTemp.Format(sFmt, lpss->dwWin32ExitCode, lpss->dwServiceSpecificExitCode,
		lpss->dwCheckPoint, lpss->dwWaitHint);
	sOut += sTemp;

	OutputString(sOut);
}

void CServiceDlg::ReportIfFail(BOOL bReturn)
{
	if (!bReturn)
		AfxMessageBox(_T("Failed. See output window for details"), 
		MB_OK | MB_ICONSTOP);
}

void CServiceDlg::UpdateServiceList()
{
	m_ctrlListService.ResetContent();
	CStringArray SrvDspNames;
	m_itersrv.GetDisplayNames(SrvDspNames);
	for (int i = 0; i < SrvDspNames.GetSize(); i++)
		m_ctrlListService.AddString(SrvDspNames[i]);
}

CString CServiceDlg::BarToCR(LPCTSTR sIn)
{
	CString sOut = sIn;
	for (int i = 0; i < sOut.GetLength(); i++)
		{
		if (sOut[i] == _T('|'))
			sOut.SetAt(i, _T('\r'));
		}
	return sOut;
}
