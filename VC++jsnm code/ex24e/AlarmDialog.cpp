// AlarmDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ex24e.h"
#include "AlarmDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmDialog dialog


CAlarmDialog::CAlarmDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmDialog)
	m_nHours = 0;
	m_nMinutes = 0;
	m_nSeconds = 0;
	//}}AFX_DATA_INIT
}


void CAlarmDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmDialog)
	DDX_Text(pDX, IDC_HOURS, m_nHours);
	DDV_MinMaxInt(pDX, m_nHours, 0, 23);
	DDX_Text(pDX, IDC_MINUTES, m_nMinutes);
	DDV_MinMaxInt(pDX, m_nMinutes, 0, 59);
	DDX_Text(pDX, IDC_SECONDS, m_nSeconds);
	DDV_MinMaxInt(pDX, m_nSeconds, 0, 59);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmDialog, CDialog)
	//{{AFX_MSG_MAP(CAlarmDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmDialog message handlers
