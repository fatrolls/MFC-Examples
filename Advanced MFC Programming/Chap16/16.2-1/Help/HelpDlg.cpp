#include "stdafx.h"
#include "Help.h"
#include "HelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpDlg)
	//}}AFX_DATA_INIT
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CHelpDlg)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHelpDlg::SetContextHelpId()
{
	CWnd *ptrWnd;

	ptrWnd=GetWindow(GW_CHILD);
	while(TRUE)
	{
		ptrWnd->SetWindowContextHelpId(ptrWnd->GetDlgCtrlID()+0x10000);
		if(ptrWnd == ptrWnd->GetWindow(GW_HWNDLAST))break;
		ptrWnd=ptrWnd->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CHelpDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	DWORD dwContextID;

	dwContextID=pHelpInfo->dwContextId-0x10000;
	switch(dwContextID)
	{
		case IDC_EDIT:
		case IDC_RADIO:
		case IDC_BUTTON:
		case IDC_COMBO:
		{
			AfxGetApp()->WinHelp(pHelpInfo->dwContextId);
			return TRUE;
		}
		default: break;
	}
	return CDialog::OnHelpInfo(pHelpInfo);
}

BOOL CHelpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetContextHelpId();
	
	return TRUE;
}
