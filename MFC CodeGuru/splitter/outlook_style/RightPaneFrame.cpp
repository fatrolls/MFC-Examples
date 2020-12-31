// RightPaneFrame.cpp : implementation file
//

#include "stdafx.h"
#include "OutLookStyle.h"
#include "RightPaneFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRightPaneFrame

IMPLEMENT_DYNCREATE(CRightPaneFrame, CFrameWnd)

CRightPaneFrame::CRightPaneFrame()
{
}

CRightPaneFrame::~CRightPaneFrame()
{
}


BEGIN_MESSAGE_MAP(CRightPaneFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CRightPaneFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRightPaneFrame message handlers

BOOL CRightPaneFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	m_pSplitterView = new CSplitterView;
	m_pSplitterView->Create(NULL, NULL, 0L, CFrameWnd::rectDefault, this, VIEW_SPLITTER, pContext);
	SetActiveView(m_pSplitterView);
	m_pSplitterView->ShowWindow(SW_SHOW);
	m_pSplitterView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	m_nCurrentViewID = VIEW_SPLITTER;

	m_pListCtrlView = new CListCtrlView;
	((CView*) m_pListCtrlView)->Create(NULL, NULL, 0L, CFrameWnd::rectDefault, this, VIEW_LISTCTRL, pContext);
	m_pListCtrlView->ShowWindow(SW_HIDE);
	m_pListCtrlView->SetDlgCtrlID(VIEW_LISTCTRL);

	m_pEditCtrlView = new CEditCtrlView;
	((CView*) m_pEditCtrlView)->Create(NULL, NULL, 0L, CFrameWnd::rectDefault, this, VIEW_EDIT, pContext);
	m_pEditCtrlView->ShowWindow(SW_HIDE);
	m_pEditCtrlView->SetDlgCtrlID(VIEW_EDIT);


	RecalcLayout();
	
	return TRUE;
}

void CRightPaneFrame::SwitchToView(UINT nView)
{
	CView* pOldActiveView = GetActiveView();
	CView* pNewActiveView = NULL;

	switch (nView)
	{
	case	VIEW_SPLITTER:
				pNewActiveView = (CView*) m_pSplitterView;
				break;

	case	VIEW_LISTCTRL:
				pNewActiveView = (CView*) m_pListCtrlView;
				break;
	case	VIEW_EDIT:
				pNewActiveView = (CView*) m_pEditCtrlView;
				break;
	}

	if (pNewActiveView)
	{
		// don't switch when views are the same
		if (pOldActiveView == pNewActiveView) return;

		SetActiveView(pNewActiveView);
		pNewActiveView->ShowWindow(SW_SHOW);
		pNewActiveView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
		pOldActiveView->ShowWindow(SW_HIDE);
		pOldActiveView->SetDlgCtrlID(m_nCurrentViewID);
		m_nCurrentViewID = nView;

		RecalcLayout();
	}
}

