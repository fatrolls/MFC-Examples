// NMiniDockFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "NMiniDockFrameWnd.h"
#include "NGenericToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNMiniDockFrameWnd

IMPLEMENT_DYNCREATE(CNMiniDockFrameWnd, CMiniDockFrameWnd)

CNMiniDockFrameWnd::CNMiniDockFrameWnd()
{
}

CNMiniDockFrameWnd::~CNMiniDockFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CNMiniDockFrameWnd, CMiniDockFrameWnd)
	//{{AFX_MSG_MAP(CNMiniDockFrameWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNMiniDockFrameWnd message handlers

void CNMiniDockFrameWnd::RecalcLayout(BOOL bNotify) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CMiniDockFrameWnd::RecalcLayout(bNotify);

	int nPos = 1;
	CControlBar* pBar = NULL;
	while(pBar == NULL && nPos < m_wndDockBar.m_arrBars.GetSize())
	{
		pBar = (CControlBar*)m_wndDockBar.m_arrBars[nPos];
		if (HIWORD(pBar) == 0)
			pBar =  NULL;
	}
	if(pBar)
	{
		ASSERT_KINDOF(CNGenericToolBar, pBar);
		if(pBar->IsKindOf(RUNTIME_CLASS(CNGenericToolBar)))
		{
			DWORD dwStyle = ((CNGenericToolBar*)pBar)->GetGenericToolBarStyle();
			DWORD dwTestStyle = dwStyle&NGTB_NO_SYSMENU;
			if(dwTestStyle == NGTB_NO_SYSMENU)
				ModifyStyle(WS_SYSMENU,0 );
		}
	}
}
