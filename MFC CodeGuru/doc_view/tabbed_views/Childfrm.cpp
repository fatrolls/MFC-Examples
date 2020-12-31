// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Tab.h"

#include "ChildFrm.h"
#include "tabwnd.h"
#include "tabdoc.h"
#include "tabview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	BOOL bStatus=CMDIChildWnd::PreCreateWindow(cs);
	cs.dwExStyle&=~WS_EX_CLIENTEDGE;
	return bStatus;
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_tabWnd.Create(WS_VISIBLE|WS_CHILD, this, 0x1245);
	m_tabWnd.CreateView("Page 1", RUNTIME_CLASS(CTabView), pContext);
	m_tabWnd.CreateView("Page 2", RUNTIME_CLASS(CTabView), pContext);
	m_tabWnd.CreateView("Page 3", RUNTIME_CLASS(CTabView), pContext);
	m_tabWnd.CreateView("Page 4", RUNTIME_CLASS(CTabView), pContext);
	//	CMDIChildWnd::OnCreateClient(lpcs, pContext);
	return TRUE;	
}

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	
    	
}
