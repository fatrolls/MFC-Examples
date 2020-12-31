#include "stdafx.h"
#include "DB.h"
#include "ToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_TIMER_WAIT   0xE000
#define ID_TIMER_CHECK  0xE001

CDlgToolBar::CDlgToolBar():CToolBar()
{
}

CDlgToolBar::~CDlgToolBar()
{
}


BEGIN_MESSAGE_MAP(CDlgToolBar, CToolBar)
	//{{AFX_MSG_MAP(CDlgToolBar)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgToolBar::OnTimer(UINT nIDEvent) 
{
	if (GetKeyState(VK_LBUTTON) < 0)
		return;

	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();

	// get current mouse position for hit test
	CPoint point; GetCursorPos(&point);
	ScreenToClient(&point);
	int nHit = OnToolHitTest(point, NULL);
	if (nHit >= 0)
	{
		// determine if status bar help should go away
		CWnd* pParent = GetParent();
		if (!IsTopParentActive() || !pParent->IsWindowEnabled())
			nHit = -1;

		// remove status help if capture is set
		HWND hWndTip = pThreadState->m_pToolTip->GetSafeHwnd();
		CWnd* pCapture = GetCapture();
		if (pCapture != this && pCapture->GetSafeHwnd() != hWndTip &&
			pCapture->GetTopLevelParent() == pParent)
		{
			nHit = -1;
		}
	}
	else
	{
		pThreadState->m_nLastStatus = -1;
	}

	// make sure it isn't over some other app's window
	if (nHit >= 0)
	{
		ClientToScreen(&point);
		HWND hWnd = ::WindowFromPoint(point);
		if (hWnd == NULL || (hWnd != m_hWnd && !::IsChild(m_hWnd, hWnd) &&
			pThreadState->m_pToolTip->GetSafeHwnd() != hWnd))
		{
			nHit = -1;
			pThreadState->m_nLastStatus = -1;
		}
	}

	// handle the result
	if (nHit < 0)
	{
		if (pThreadState->m_nLastStatus == -1)
			KillTimer(ID_TIMER_CHECK);
		SetStatusText(-1);
	}

	// set status text after initial timeout
	if (nIDEvent == ID_TIMER_WAIT)
	{
		KillTimer(ID_TIMER_WAIT);
		if (nHit >= 0)
			SetStatusText(nHit);
	}
}
