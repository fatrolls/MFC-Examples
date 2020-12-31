// RootDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "RootDlg.h"
#include "RemoteAdminDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRootDlg dialog

IMPLEMENT_DYNCREATE(CRootDlg, CBCGPDialog)

CRootDlg::CRootDlg(UINT uIDD, CWnd* pParent /*=NULL*/)
	: CBCGPDialog(uIDD, pParent)
{
	//{{AFX_DATA_INIT(CRootDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	IDD = uIDD;
}


void CRootDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRootDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRootDlg, CBCGPDialog)
	//{{AFX_MSG_MAP(CRootDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CRootDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CBCGPDialog::OnShowWindow(bShow, nStatus);
	if (bShow)
	{
		//SetBackgroundColor(RGB(255, 255, 255));
		CMainDlg* pParent = (CMainDlg*)GetParent();
		//pParent->m_FuncList.LockWindowUpdate();
		CRect rcClient, rcWindow;
		pParent->m_wndPlace.GetClientRect(rcClient);
		pParent->m_wndPlace.GetWindowRect(rcWindow);
		if (rcClient.Width() == m_rcWindow.Width() && 
			rcClient.Height() == m_rcWindow.Height() )
			return;
		int difx = m_rcWindow.Width() - rcClient.Width();
		int dify = m_rcWindow.Height() - rcClient.Height();
		CRect rcWindow2;
		pParent->GetWindowRect(rcWindow2);
		rcWindow2.right += difx;
		rcWindow2.bottom += dify;
		pParent->MoveWindow(rcWindow2);
		rcWindow.right += difx;
		rcWindow.bottom += dify;
		pParent->ScreenToClient(&rcWindow);
		pParent->m_wndPlace.MoveWindow(rcWindow);
		MoveWindow(rcWindow);
		pParent->Invalidate();
		Invalidate();
		pParent->m_FuncList.UnlockWindowUpdate();
		//pParent->m_FuncList.Invalidate();

		if (IDD = CRemoteControlDlg::IDD)
			pParent->CenterWindow();
	}
}
