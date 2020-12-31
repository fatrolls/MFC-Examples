// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "TabViews.h"

#include "TabViewsDoc.h"
#include "TabViewsView.h"
#include "HexView.h"
#include "StatisticsView.h"
#include "Customize.h"
#include "ChildFrm.h"

#include "MainFrm.h"

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
	ON_COMMAND(ID_VIEW_SHOW_CUSTOMIZE_DLG, OnViewShowCustomizeDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_CUSTOMIZE_DLG, OnUpdateViewShowCustomizeDlg)
	ON_WM_DESTROY()
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

	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();

	if(pFrame->m_bOpenCustomizeDlg)
	{
		CCustomizeDlg dlgCustomize(this);
		dlgCustomize.m_dwOffsetExt=pFrame->m_dwOffsetExt;
		dlgCustomize.m_dwOffsetInt=pFrame->m_dwOffsetInt;
		dlgCustomize.m_dwStyle=pFrame->m_dwStyle;
		dlgCustomize.m_bOpenCustomizeDlg=pFrame->m_bOpenCustomizeDlg;

		if(dlgCustomize.DoModal()==IDOK)
		{
			pFrame->m_dwOffsetExt=dlgCustomize.m_dwOffsetExt;
			pFrame->m_dwOffsetInt=dlgCustomize.m_dwOffsetInt;
			pFrame->m_dwStyle=dlgCustomize.m_dwStyle;
			pFrame->m_bOpenCustomizeDlg=dlgCustomize.m_bOpenCustomizeDlg;
		}
	}

	DWORD style = pFrame->m_dwStyle | TCS_FOCUSNEVER | WS_VISIBLE | WS_CHILD;
	if(!m_TabViewContainer.Create(this,CRect(0,0,0,0), style, AFX_IDW_PANE_FIRST))
		return FALSE;

	m_TabViewContainer.SetOffsetExternal(pFrame->m_dwOffsetExt);
	m_TabViewContainer.SetOffsetInternal(pFrame->m_dwOffsetInt);

	VERIFY(m_ilContainer.Create(IDB_IL_TABVIEWS,16,0,RGB(255,0,255)));
	m_TabViewContainer.SetImageList(&m_ilContainer);

	if(!m_TabViewContainer.AddPage(pContext->m_pNewViewClass,
		pContext,_T("Editor"),0))
		return FALSE;
	if(!m_TabViewContainer.AddPage(RUNTIME_CLASS(CHexView),
		pContext,_T("HexView"),1))
		return FALSE;

	if(!m_TabViewContainer.AddPage(RUNTIME_CLASS(CStatisticsView),
		pContext,_T("Statistics"),2))
		return FALSE;

	m_TabViewContainer.SetActivePageIndex(0);
	
	return TRUE;
}


void CChildFrame::OnViewShowCustomizeDlg() 
{
	// TODO: Add your command handler code here
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	pFrame->m_bOpenCustomizeDlg=!pFrame->m_bOpenCustomizeDlg;
}

void CChildFrame::OnUpdateViewShowCustomizeDlg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	pCmdUI->SetCheck(pFrame->m_bOpenCustomizeDlg);
}

void CChildFrame::OnDestroy() 
{
	CMDIChildWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
