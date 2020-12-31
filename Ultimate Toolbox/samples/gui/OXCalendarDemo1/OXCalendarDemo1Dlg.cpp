// OXCalendarDemo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "OXCalendarDemo1.h"
#include "OXCalendarDemo1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// COXCalendarDemo1Dlg dialog

COXCalendarDemo1Dlg::COXCalendarDemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(COXCalendarDemo1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COXCalendarDemo1Dlg)
	m_First = _T("First");
	m_Last = _T("Knight");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COXCalendarDemo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COXCalendarDemo1Dlg)
	DDX_Control(pDX, IDC_CALENDAR2, m_Calendar2);
	DDX_Control(pDX, IDC_CALENDAR1, m_Calendar1);
	DDX_Text(pDX, IDC_EDIT1, m_First);
	DDX_Text(pDX, IDC_EDIT2, m_Last);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COXCalendarDemo1Dlg, CDialog)
	//{{AFX_MSG_MAP(COXCalendarDemo1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COXCalendarDemo1Dlg message handlers

BOOL COXCalendarDemo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_Calendar1.SetFirstDayOfWeek(0);
	m_Calendar2.SetFirstDayOfWeek(0);
	//
	COleDateTime SampleLastDay = COleDateTime::GetCurrentTime();  // give a sample last 
	///
	// do it before SetCurrentDate()
	m_Calendar1.SetFormat(_T("%m/%d/%y"));

	///
	//Set current date value
	m_Calendar1.SetCurrentDate( SampleLastDay );

	// Set Date Range for calendar
	m_Calendar2.SetDateRange(COleDateTime(SampleLastDay.GetYear()-1,1,1,0,0,0),
							 COleDateTime(SampleLastDay.GetYear()+1,12,31,0,0,0));
	
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

void COXCalendarDemo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COXCalendarDemo1Dlg::OnPaint() 
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
HCURSOR COXCalendarDemo1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
