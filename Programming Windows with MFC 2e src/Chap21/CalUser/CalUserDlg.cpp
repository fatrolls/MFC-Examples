// CalUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CalUser.h"
#include "CalUserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalUserDlg dialog

CCalUserDlg::CCalUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalUserDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalUserDlg)
	DDX_Control(pDX, IDC_YEAR, m_ctlYear);
	DDX_Control(pDX, IDC_MONTH, m_ctlMonth);
	DDX_Control(pDX, IDC_CALENDAR, m_ctlCalendar);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalUserDlg, CDialog)
	//{{AFX_MSG_MAP(CCalUserDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELENDOK(IDC_MONTH, OnChangeDate)
	ON_CBN_SELENDOK(IDC_YEAR, OnChangeDate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const CString CCalUserDlg::m_strMonths[] = {
	_T ("January"),
	_T ("February"),
	_T ("March"),
	_T ("April"),
	_T ("May"),
	_T ("June"),
	_T ("July"),
	_T ("August"),
	_T ("September"),
	_T ("October"),
	_T ("November"),
	_T ("December")
};

/////////////////////////////////////////////////////////////////////////////
// CCalUserDlg message handlers

BOOL CCalUserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//
	// Initialize the Month control.
	//
	COleDateTime date = m_ctlCalendar.GetDate ();
	int nMonth = date.GetMonth ();
	int nYear = date.GetYear ();

	InitListOfMonths ();
	m_ctlMonth.SetCurSel (nMonth - 1);

	//
	// Initialize the Year control.
	//
	InitListOfYears ();
	m_ctlYear.SetCurSel (nYear - 1970);

	return TRUE;
}

void CCalUserDlg::OnPaint() 
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

HCURSOR CCalUserDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalUserDlg::InitListOfMonths()
{
	for (int i=0; i<12; i++)
		m_ctlMonth.AddString (m_strMonths[i]);
}

void CCalUserDlg::InitListOfYears()
{
	for (int i=1970; i<=2037; i++) {
		CString string;
		string.Format (_T ("%d"), i);
		m_ctlYear.AddString (string);
	}
}

void CCalUserDlg::OnChangeDate() 
{
	int nMonth = m_ctlMonth.GetCurSel () + 1;
	int nYear = GetDlgItemInt (IDC_YEAR);
	ASSERT (nYear != 0);
	m_ctlCalendar.SetDate (nYear, nMonth, 1);
}

BEGIN_EVENTSINK_MAP(CCalUserDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CCalUserDlg)
	ON_EVENT(CCalUserDlg, IDC_CALENDAR, 1 /* NewDay */, OnNewDay, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCalUserDlg::OnNewDay(short nDay) 
{
	static const CString strDays[] = {
		_T ("Sunday"),
		_T ("Monday"),
		_T ("Tuesday"),
		_T ("Wednesday"),
		_T ("Thursday"),
		_T ("Friday"),
		_T ("Saturday"),
	};

	COleDateTime date = m_ctlCalendar.GetDate ();
	int nMonth = date.GetMonth ();
	int nYear = date.GetYear ();

	CTime time (nYear, nMonth, nDay, 12, 0, 0);
	int nDayOfWeek = time.GetDayOfWeek () - 1;

	CString string;
	string.Format (_T ("%s, %s %d, %d"), strDays[nDayOfWeek],
		m_strMonths[nMonth - 1], nDay, nYear);

	MessageBox (string);
}
