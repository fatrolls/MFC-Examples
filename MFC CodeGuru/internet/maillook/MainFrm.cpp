// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "splitter.h"
#include "MainFrm.h"
#include "CMFormView.h" 
#include "CMRichView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if(!m_splitterWnd1.CreateStatic(this, 1,2) ||
	   !m_splitterWnd1.CreateView(0, 0, RUNTIME_CLASS(CSplitterView), CSize(100,0), pContext) ||
	   !m_splitterWnd2.CreateStatic(&m_splitterWnd1, 2, 1, WS_CHILD | WS_VISIBLE, m_splitterWnd1.IdFromRowCol(0,1)) ||
	   !m_splitterWnd2.CreateView(0, 0, RUNTIME_CLASS(CMFormView), CSize(0, 355),pContext) ||
	   !m_splitterWnd2.CreateView(1, 0, RUNTIME_CLASS(CMRichView), CSize(0, 0),pContext))
		{
			return FALSE;
		}		
	return TRUE;
}
