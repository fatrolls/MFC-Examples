#include "stdafx.h"
#include "DB.h"
#include "ToolBar.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_TIMER_DLGCHECK	500
#define ID_TIMER_DLGWAIT	501

CDlgToolBar::CDlgToolBar():CToolBar()
{
	m_bTimerOn=FALSE;
}

CDlgToolBar::~CDlgToolBar()
{
}


BEGIN_MESSAGE_MAP(CDlgToolBar, CToolBar)
	//{{AFX_MSG_MAP(CDlgToolBar)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgToolBar::PreTranslateMessage(MSG *pMsg)
{
	if(pMsg->message == WM_MOUSEMOVE && m_bTimerOn == FALSE)
	{
		SetTimer(ID_TIMER_DLGWAIT, 300, NULL);
		m_bTimerOn=TRUE;
	}
	return CToolBar::PreTranslateMessage(pMsg);
}

void CDlgToolBar::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == ID_TIMER_DLGWAIT || nIDEvent == ID_TIMER_DLGCHECK)
	{
		CPoint point;
		int nHit;
		
		::GetCursorPos(&point);
		ScreenToClient(&point);
		nHit=OnToolHitTest(point, NULL);
		if(nHit >= 0)
		{
			GetParent()->SendMessage(WM_SETMESSAGESTRING, nHit);
			if(nIDEvent == ID_TIMER_DLGWAIT)
			{
				KillTimer(ID_TIMER_DLGWAIT);
				SetTimer(ID_TIMER_DLGCHECK, 200, NULL);
			}
		}
		if(nHit < 0)
		{
			KillTimer(nIDEvent);
			m_bTimerOn=FALSE;
			GetParent()->SendMessage(WM_POPMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
		}
	}
	else CToolBar::OnTimer(nIDEvent);
}
