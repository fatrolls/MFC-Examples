// Controls.cpp : implementation file
//

#include "stdafx.h"
#include "TaskBar.h"
#include "Controls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlsDlg dialog


CControlsDlg::CControlsDlg(CWnd* pParent /*=NULL*/)
	: CAppBarDlg(CControlsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CAppBarDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlsDlg)
	DDX_Control(pDX, IDC_START, m_btnStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControlsDlg, CAppBarDlg)
	//{{AFX_MSG_MAP(CControlsDlg)
	ON_BN_CLICKED(IDC_START, OnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlsDlg message handlers

void CControlsDlg::OnStart() 
{
    CRect rect;
    m_btnStart.GetWindowRect (&rect);
    ShowMenu (rect, IDR_EPIC_BUTTON_MENU, -1);
}

