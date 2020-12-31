#include "stdafx.h"
#include "GDI.h"
#include "ProgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_ID	500

CProgDlg::CProgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgDlg)
	//}}AFX_DATA_INIT
	m_nPercent=0;
}

void CProgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProgDlg, CDialog)
	//{{AFX_MSG_MAP(CProgDlg)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CProgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_perBar.SubclassDlgItem(IDC_STATIC_PROG, this);
	SetTimer(TIMER_ID, 100, NULL);
	return TRUE;
}

void CProgDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMER_ID)
	{
		m_perBar.SetPercentage(m_nPercent++);
		if(m_nPercent == 100)m_nPercent=0;
	}
	CDialog::OnTimer(nIDEvent);
}

void CProgDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(TIMER_ID);
}
