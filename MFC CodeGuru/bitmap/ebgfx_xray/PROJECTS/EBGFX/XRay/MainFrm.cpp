// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "XRay.h"

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
	ON_WM_GETMINMAXINFO()
	ON_WM_MOVE()
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
	// Remove Minimize and Maximize
	cs.style^=WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
	cs.dwExStyle^=WS_EX_TOPMOST;
	// Resize Window so that the ClientArea is 200x200
	CRect WindowRect ( 0, 0, 200, 200 );
	AdjustWindowRect ( &WindowRect, cs.style, TRUE );
	cs.cx=WindowRect.Width ();
	cs.cy=WindowRect.Height ();

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

void CMainFrame::OnGetMinMaxInfo ( MINMAXINFO FAR* lpMMI ) 
{
	// Keep User from Sizing the Window
	CRect WindowRect ( 0, 0, 200, 200 );
	AdjustWindowRect ( &WindowRect, GetStyle (), TRUE );
	lpMMI->ptMinTrackSize=CPoint ( WindowRect.Width (), WindowRect.Height () );
	lpMMI->ptMaxTrackSize=CPoint ( WindowRect.Width (), WindowRect.Height () );
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnMove ( int x, int y ) 
{
	// If Move, Notify View
	CFrameWnd::OnMove ( x, y );

	CView *View=GetActiveView ();

	if ( View )
		View->PostMessage ( MSG_PARENTMOVE );
}
