// CSHDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CSHDialog.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSHDialog dialog
CCSHDialog::CCSHDialog(UINT nIDTemplate, CWnd* pParentWnd)
	: CDialog(nIDTemplate, pParentWnd)
{
}

CCSHDialog::CCSHDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
	: CDialog(lpszTemplateName, pParentWnd)
{
}

CCSHDialog::CCSHDialog() : CDialog()
{
}

BEGIN_MESSAGE_MAP(CCSHDialog, CDialog)
	//{{AFX_MSG_MAP(CCSHDialog)
	ON_WM_CONTEXTMENU()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCSHDialog message handlers
void CCSHDialog::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	::WinHelp(pWnd->m_hWnd, AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(LPVOID)GetHelpIDs());
}

BOOL CCSHDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return ::WinHelp((HWND)pHelpInfo->hItemHandle, AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, (DWORD)(LPVOID)GetHelpIDs());
}

BOOL CCSHDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0, WS_EX_CONTEXTHELP);		
	return TRUE;  
}


