// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Wanderer.h"
#include "WandererDoc.h"
#include "DriveView.h"
#include "FileView.h"
#include "MainFrm.h"

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
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
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
	//
	// Note: Create the CFileView first so the CDriveView's OnInitialUpdate
	// function can call OnUpdate on the CFileView.
	//
    if (!m_wndSplitter.CreateStatic (this, 1, 2) ||
        !m_wndSplitter.CreateView (0, 1, RUNTIME_CLASS
            (CFileView), CSize (0, 0), pContext) ||
        !m_wndSplitter.CreateView (0, 0, RUNTIME_CLASS (CDriveView),
            CSize (192, 0), pContext))
        return FALSE;

    return TRUE;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	//
    // Route to standard command targets first.
	//
    if (CFrameWnd::OnCmdMsg (nID, nCode, pExtra, pHandlerInfo))
        return TRUE;

	//
    // Route to inactive views second.
	//
    CWandererDoc* pDoc = (CWandererDoc*) GetActiveDocument ();
    if (pDoc != NULL) { // Important!
		return pDoc->RouteCmdToAllViews (GetActiveView (),
			nID, nCode, pExtra, pHandlerInfo);
	}
    return FALSE;
}
