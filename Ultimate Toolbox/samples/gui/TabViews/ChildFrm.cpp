// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "TabViews.h"

#include "TabViewsDoc.h"
#include "TabViewsView.h"
#include "HexView.h"
#include "StatisticsView.h"
#include "ChildFrm.h"
#include "MyFormView.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
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

	cs.lpszClass=AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,
		AfxGetApp()->LoadIcon(IDR_TABVIETYPE));
	ASSERT(cs.lpszClass);
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

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	UNREFERENCED_PARAMETER(lpcs);

	if(!m_TabViewContainer.Create(this))
		return FALSE;

	if(!m_TabViewContainer.AddPage(pContext->m_pNewViewClass,
		pContext,_T("Editor")))
		return FALSE;
	if(!m_TabViewContainer.AddPage(RUNTIME_CLASS(CHexView),
		pContext,_T("HexView")))
		return FALSE;

	if(!m_TabViewContainer.AddPage(RUNTIME_CLASS(CStatisticsView),
		pContext,_T("Statistics")))
		return FALSE;

	if(!m_TabViewContainer.AddPage(RUNTIME_CLASS(CMyFormView),
		pContext,_T("FormView")))
		return FALSE;

	m_TabViewContainer.SetActivePageIndex(0);
	
	return TRUE;

//	return CMDIChildWnd::OnCreateClient(lpcs,pContext);
}
