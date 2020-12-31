// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "MdLessPpsh.h"

#include "Pg1.h"
#include "Pg2.h"
#include "ModelessPpsh.h"
#include "ChildFrm.h"

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
	ON_COMMAND(ID_VIEW_PPSH, OnViewPpsh)
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
	delete m_pPg1;
	delete m_pPg2;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
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

void CChildFrame::OnViewPpsh() 
{
	CModelessPpsh Ppsh;
	CPg1 pPg1;
	CPg2 pPg2;

	
	Ppsh.AddPage(&pPg1);
	Ppsh.AddPage(&pPg2);
	Ppsh.DoModal();

}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// do not call base class!
	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
	m_pPg1 = new CPg1();
	m_pPg2 = new CPg2();
	
	m_Ppsh.AddPage(m_pPg1);
	m_Ppsh.AddPage(m_pPg2);
	
	m_Ppsh.Create(this, WS_CHILD);
	m_Ppsh.ShowWindow(SW_SHOW);
	
	CRect clientRect;

	return TRUE;	 
}

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	if(m_Ppsh.m_hWnd == 0)
		return;
	
	//this will change only the size of property sheet.
	//you will have to add code to resize property pages.
	//use m_Ppsh.GetTabControl()->MoveWindow to do it
	CRect clientRect;
	GetClientRect(clientRect);
	m_Ppsh.MoveWindow(clientRect);
}
