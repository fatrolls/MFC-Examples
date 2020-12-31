// DatePickerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DatePicker.h"
#include "DatePickerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatePickerDlg dialog

CDatePickerDlg::CDatePickerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDatePickerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDatePickerDlg)
	//}}AFX_DATA_INIT
}

void CDatePickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatePickerDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CUSTOM1, m_DateTime);
}

BEGIN_MESSAGE_MAP(CDatePickerDlg, CDialog)
	//{{AFX_MSG_MAP(CDatePickerDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(DTN_DATETIMECHANGE,IDC_CUSTOM1,OnDateChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatePickerDlg message handlers

BOOL CDatePickerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_DateTime.SetFormat("ddd',' MMM dd yyyy");
	m_DateTime.SetMonthCalColour(MCSC_MONTHBK, RGB(220,220,255));

	// Demonstrate restriction to a time range (today +/- 3 months)
	//CTime MinTime(CTime::GetCurrentTime()-CTimeSpan(90,0,0,0));
	//CTime MaxTime(CTime::GetCurrentTime()+CTimeSpan(90,0,0,0));

	COleDateTime MinTime(COleDateTime::GetCurrentTime()-COleDateTimeSpan(90,0,0,0));
	COleDateTime MaxTime(COleDateTime::GetCurrentTime()+COleDateTimeSpan(90,0,0,0));

	m_DateTime.SetRange(&MinTime, &MaxTime);	// Try each of these to see the effect
	//m_DateTime.SetRange(NULL, &MaxTime);
	//m_DateTime.SetRange(&MinTime, NULL);
	//m_DateTime.SetRange(NULL, NULL);

	// This does not seem to be working. Any ideas?
	CFont *pFont = m_DateTime.GetMonthCalFont();
	if (pFont) {
		LOGFONT lf;
		pFont->GetLogFont(&lf);
		lf.lfItalic = TRUE;
		m_font.CreateFontIndirect(&lf);
		m_DateTime.SetMonthCalFont(m_font);
	}

	return TRUE;  
}

void CDatePickerDlg::OnOK() 
{
	CString msg;

	CTime MinTime, MaxTime;
	DWORD result = m_DateTime.GetRange(&MinTime, &MaxTime);

	msg = _T("\nMin Time: ");
	if (result & GDTR_MIN) 
		msg += MinTime.Format("%#x");
	else
		msg += _T("None.");

	msg += _T("\nMax Time: ");
	if (result & GDTR_MAX) 
		msg += MaxTime.Format("%#x");
	else
		msg += _T("None.");
	

	CTime time = m_DateTime.GetDateTime();
	msg += _T("\n\nTime chosen: ");
	msg += time.Format("%#x");

	AfxMessageBox(msg);
}

void CDatePickerDlg::OnDateChange(NMHDR* pNotifyStruct, LRESULT* result)
{
	CTime time = m_DateTime.GetDateTime();
	CString msg = _T("DateTime Picker notification: Date is ");
	msg += time.Format("%#x");

	TRACE("%s\n",msg);
	AfxMessageBox(msg);
}

