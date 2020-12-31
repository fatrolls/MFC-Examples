#include "stdafx.h"
#include "Bar.h"
#include "MainFrm.h"
#include "MDlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MCDialogBar::MCDialogBar():CDialogBar()
{
	//{{AFX_DATA_INIT(MCDialogBar)
	//}}AFX_DATA_INIT
}

void MCDialogBar::OnSize(UINT nType, int cx, int cy) 
{
	CWnd *ptrWnd;
	CRect rectWnd;

	CDialogBar::OnSize(nType, cx, cy);

	GetClientRect(rectWnd);
	ptrWnd=GetDlgItem(IDC_EDIT);
	if(ptrWnd != NULL)
	{
		ptrWnd->MoveWindow
		(
			rectWnd.left+15,
			rectWnd.top+15,
			rectWnd.Width()-30,
			rectWnd.Height()-30
		);
	}
}

CSize MCDialogBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{
	CSize size;
	CMainFrame *ptrWnd;
	CRect rect;

	ptrWnd=(CMainFrame *)(AfxGetApp()->m_pMainWnd);
	ptrWnd->GetClientRect(rect);
	if((dwMode & LM_VERTDOCK) || (dwMode & LM_HORZDOCK))
	{
		size.cx=(dwMode & LM_HORZ) ? rect.Width():m_sizeDefault.cx;
		size.cy=(dwMode & LM_HORZ) ? m_sizeDefault.cy:rect.Height();

		return size;
	}
	return CDialogBar::CalcDynamicLayout(nLength, dwMode);
}

BEGIN_MESSAGE_MAP(MCDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(MCDialogBar)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
