// ApBarWnd.cpp : implementation file
//

#include "stdafx.h"
#include "TaskBar.h"
#include "ApBarWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppBarWnd

CAppBarWnd::CAppBarWnd()
{
}

CAppBarWnd::~CAppBarWnd()
{
}


BEGIN_MESSAGE_MAP(CAppBarWnd, CWnd)
	//{{AFX_MSG_MAP(CAppBarWnd)
	ON_WM_ACTIVATE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAppBarWnd message handlers

void CAppBarWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}

void CAppBarWnd::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CWnd::OnWindowPosChanged(lpwndpos);
	
	// TODO: Add your message handler code here
	
}

UINT CAppBarWnd::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CWnd::OnNcHitTest(point);
}
    

void CAppBarWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CAppBarWnd::OnMove(int x, int y) 
{
	CWnd::OnMove(x, y);
	
	// TODO: Add your message handler code here
	
}

void CAppBarWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnMouseMove(nFlags, point);
}

void CAppBarWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonUp(nFlags, point);
}
