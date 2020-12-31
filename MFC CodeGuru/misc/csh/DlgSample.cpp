// DlgSample.cpp : implementation file
//

#include "stdafx.h"
#include "CSH.h"
#include "DlgSample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CDlgSample dialog
#include "resource.hm"
const DWORD CDlgSample::m_nHelpIDs[] = 
{
	IDC_CHECK1,	HIDC_CHECK1,
	IDC_COMBO1,	HIDC_COMBO1,
	IDC_LIST1,	HIDC_LIST1,
	IDOK,		HIDOK,	
	0,			0
};


CDlgSample::CDlgSample(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSample::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSample)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSample::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSample)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSample, CDialog)
	//{{AFX_MSG_MAP(CDlgSample)
	ON_WM_CONTEXTMENU()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSample message handlers

BOOL CDlgSample::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0, WS_EX_CONTEXTHELP);		
	return TRUE;  
}

void CDlgSample::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	::WinHelp(pWnd->m_hWnd, AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(LPVOID)m_nHelpIDs);
	
}

BOOL CDlgSample::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return ::WinHelp((HWND)pHelpInfo->hItemHandle, AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, (DWORD)(LPVOID)m_nHelpIDs);
}
