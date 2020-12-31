// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RotoZoom.h"
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
	// Romove Minimize and Maximize
	cs.style^=WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
	// Resize Window so that the ClientArea is 100x100
	CRect WindowRect ( 0, 0, 100, 100 );
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

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// Keep User from Sizing the Window
	CView *View=GetActiveView ();

	if ( View )
	{
		if ( View->SendMessage ( MSG_ISDOUBLESIZE ) )
		{
			CRect WindowRect ( 0, 0, 200, 200 );
			AdjustWindowRect ( &WindowRect, GetStyle (), TRUE );
			lpMMI->ptMinTrackSize=CPoint ( WindowRect.Width (), WindowRect.Height () );
			lpMMI->ptMaxTrackSize=CPoint ( WindowRect.Width (), WindowRect.Height () );
		}
		else
		{
			// Yeah I know, it should be ( 0, 0, 100, 100 ), but
			// for some strange reason it only works like this.
			CRect WindowRect ( 0, 0, 104, 100 );
			AdjustWindowRect ( &WindowRect, GetStyle (), TRUE );
			lpMMI->ptMinTrackSize=CPoint ( WindowRect.Width (), WindowRect.Height () );
			lpMMI->ptMaxTrackSize=CPoint ( WindowRect.Width (), WindowRect.Height () );
		}
	}
	
	CFrameWnd::OnGetMinMaxInfo ( lpMMI );
}
