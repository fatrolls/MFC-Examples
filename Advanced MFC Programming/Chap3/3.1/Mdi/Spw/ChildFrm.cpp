// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Spw.h"
#include "ChildFrm.h"
#include "SpwDoc.h"
#include "SpwView.h"
#include "SpwEVw.h"
#include "SpwFVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CChildFrame::CChildFrame()
{
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CMDIChildWnd::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if
	(
		!m_wndSpMain.CreateStatic
		(
			this, 1, 2, WS_CHILD | WS_VISIBLE, AFX_IDW_PANE_FIRST
		)
	)
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	if
	(
		!m_wndSpMain.CreateView
		(
			0, 0, RUNTIME_CLASS(CSpwView), CSize(100, 100), pContext
		)
	)
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	if
	(
		!m_wndSpSub.CreateStatic
		(
			&m_wndSpMain, 2, 1, 
			WS_CHILD | WS_VISIBLE, m_wndSpMain.IdFromRowCol(0, 1)
		)
	)
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	if
	(
		!m_wndSpSub.CreateView
		(
			0, 0, RUNTIME_CLASS(CSpwFView), CSize(50, 50), pContext
		)
	)
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	
	if
	(
		!m_wndSpSub.CreateView
		(
			1, 0,	RUNTIME_CLASS(CSpwEView), CSize(50, 50), pContext
		)
	)
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}
	
	return TRUE;
}
