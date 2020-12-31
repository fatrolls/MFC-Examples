// ActiveXDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex08a.h"
#include "ActiveXDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveXDialog dialog


CActiveXDialog::CActiveXDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CActiveXDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CActiveXDialog)
	m_sDay = 0;
	m_sMonth = 0;
	m_sYear = 0;
	//}}AFX_DATA_INIT
	m_BackColor = 0x8000000F;
}


void CActiveXDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActiveXDialog)
	DDX_Control(pDX, IDC_CALENDAR1, m_calendar);
	DDX_Text(pDX, IDC_DAY, m_sDay);
	DDX_Text(pDX, IDC_MONTH, m_sMonth);
	DDX_Text(pDX, IDC_YEAR, m_sYear);
	//}}AFX_DATA_MAP
	DDX_OCColor(pDX, IDC_CALENDAR1, DISPID_BACKCOLOR, m_BackColor);
}


BEGIN_MESSAGE_MAP(CActiveXDialog, CDialog)
	//{{AFX_MSG_MAP(CActiveXDialog)
	ON_BN_CLICKED(IDC_SELECTDATE, OnSelectDate)
	ON_BN_CLICKED(IDC_NEXTWEEK, OnNextWeek)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveXDialog message handlers

BEGIN_EVENTSINK_MAP(CActiveXDialog, CDialog)
    //{{AFX_EVENTSINK_MAP(CActiveXDialog)
	ON_EVENT(CActiveXDialog, IDC_CALENDAR1, 3 /* NewMonth */, OnNewMonthCalendar1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CActiveXDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_calendar.SetValue(m_varValue); // no DDX for VARIANTs

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CActiveXDialog::OnNewMonthCalendar1() 
{
	AfxMessageBox("EVENT:  CActiveXDialog::OnNewMonthCalendar1");
}

void CActiveXDialog::OnSelectDate() 
{
	CDataExchange dx(this, TRUE);
	DDX_Text(&dx, IDC_DAY, m_sDay);
	DDX_Text(&dx, IDC_MONTH, m_sMonth);
	DDX_Text(&dx, IDC_YEAR, m_sYear);
	m_calendar.SetDay(m_sDay);
	m_calendar.SetMonth(m_sMonth);
	m_calendar.SetYear(m_sYear);
}

void CActiveXDialog::OnNextWeek() 
{
	m_calendar.NextWeek();
}

void CActiveXDialog::OnOK() 
{
	CDialog::OnOK();
	m_varValue = m_calendar.GetValue(); // no DDX for VARIANTs
}

