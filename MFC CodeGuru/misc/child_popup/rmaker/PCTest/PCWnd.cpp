// PCWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PCWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCWnd

CPCWnd::CPCWnd()
{
	m_pOuter = NULL;
}

CPCWnd::~CPCWnd()
{
}

BOOL CPCWnd::Create(CPopChildWnd* pOuter, DWORD dwStyle, const RECT& rect, HWND hParentWnd, UINT nID)
{
	ASSERT(pOuter != NULL);

	BOOL bRet = CreateEx(NULL, AfxRegisterWndClass(0), _T(""), dwStyle, 
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 
		hParentWnd, NULL, NULL );
	m_pOuter = pOuter;

	return bRet;
}

BEGIN_MESSAGE_MAP(CPCWnd, CWnd)
	//{{AFX_MSG_MAP(CPCWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPCWnd message handlers

void CPCWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_pOuter->OnMouseMove(this))
		;
	else
	{
		if(m_pOuter->Captured())
		{
			CPoint point;
			::GetCursorPos(&point);
			if(GetStyle() & WS_CHILD)
				GetParent()->ScreenToClient(&point);
			SetWindowPos(NULL, point.x-m_point.x, point.y-m_point.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
		}
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CPCWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_pOuter->OnLButtonDown(this, point))
		;
	else
	{
		SetCapture();
		m_point = point;
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CPCWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(GetCapture() == this)
	{
		ReleaseCapture();
	}
	m_pOuter->OnLButtonUp(this);
	
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CPCWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(m_pOuter->OnSetCursor(this, nHitTest, message))
		return TRUE;

	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CPCWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	Draw(&dc);
}

BOOL CPCWnd::OnEraseBkgnd(CDC* pDC) 
{
	if(m_pOuter == NULL)
		return FALSE;

	CBrush backBrush(m_pOuter->OnGetBkColor());
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);
	
	CRect rect;
	pDC->GetClipBox(&rect);	//erase the area needed
	pDC->PatBlt(rect.left,rect.top,rect.Width(),rect.Height(),PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}

void CPCWnd::Draw(CDC* pDC)
{
	m_pOuter->OnDraw(pDC, this);
}

///////////////////////////////////////////////////////////
// CPopChildWnd

CPopChildWnd::CPopChildWnd()
{
	m_BkColor = RGB(129, 129, 129);
}

CPopChildWnd::~CPopChildWnd()
{
}

void CPopChildWnd::Create(HWND hParentOwner, CRect& rect, BOOL bChildFirst)
{
	DWORD styleChild, stylePop;
	if(bChildFirst)
	{
		styleChild = WS_CHILD | WS_VISIBLE;
		stylePop = WS_POPUP;
	}
	else
	{
		styleChild = WS_CHILD;
		stylePop = WS_POPUP | WS_VISIBLE;
	}
#define CHILDID 200
	m_ChildWnd.Create(this, styleChild, rect, hParentOwner, CHILDID);
	m_PopupWnd.Create(this, stylePop, rect, hParentOwner, CHILDID+1);
	m_PopupWnd.Invalidate();

	m_hParentOwner = hParentOwner;
}

////////////////////////////////
// return FALSE to let the window to continue its handling
//
BOOL CPopChildWnd::OnMouseMove(CPCWnd* pWnd)
{
	if(CWnd::GetCapture() != &m_ChildWnd && CWnd::GetCapture() != &m_PopupWnd)
		return FALSE;

	return OnChange(pWnd);
}

BOOL CPopChildWnd::Captured()
{
	return (CWnd::GetCapture() == &m_ChildWnd || CWnd::GetCapture() == &m_PopupWnd);
}

BOOL CPopChildWnd::OnChange(CPCWnd* pWhichWnd)
{
	CRect rcWnd, rcParent;
	CPCWnd* pWnd;
	if(m_ChildWnd.GetStyle() & WS_VISIBLE)
		pWnd = &m_ChildWnd;
	else
		pWnd = &m_PopupWnd;
	pWnd->GetWindowRect(&rcWnd);
	::GetWindowRect(m_hParentOwner, &rcParent);
	rcWnd.NormalizeRect();
	rcParent.NormalizeRect();
	int iRet = RectRect(rcParent, rcWnd);

	if(pWnd->GetStyle() & WS_CHILD) // child window
	{
		if(iRet == TOUCH || iRet == OUTSIDE)  // switch to popup
		{
			m_ChildWnd.ShowWindow(SW_HIDE);
			CPoint point;
			::GetCursorPos(&point);
			m_PopupWnd.SetWindowPos(NULL, point.x - m_offPt.x, point.y-m_offPt.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
			m_PopupWnd.ShowWindow(SW_SHOW);
			return TRUE;
		}
		if(iRet == INSIDE) //
		{
			CPoint point;
			::GetCursorPos(&point);
			::ScreenToClient(m_hParentOwner, &point);
			m_ChildWnd.SetWindowPos(NULL, point.x-m_offPt.x, point.y-m_offPt.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
			return TRUE;
		}
	}
	else // popup window
	{
		if(iRet == INSIDE)  // switch to child
		{
			m_PopupWnd.ShowWindow(SW_HIDE);
 			CPoint point;
			::GetCursorPos(&point);
			::ScreenToClient(m_hParentOwner, &point);
			m_ChildWnd.SetWindowPos(NULL, point.x-m_offPt.x, point.y-m_offPt.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
			m_ChildWnd.ShowWindow(SW_SHOW);
			return TRUE;
		}
		if(iRet == TOUCH || iRet == OUTSIDE)  // just switched from child
		{
			CPoint point;
			::GetCursorPos(&point);
			m_PopupWnd.SetWindowPos(NULL, point.x-m_offPt.x, point.y-m_offPt.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
			return TRUE;
		}	
	}
	return FALSE;
}

BOOL CPopChildWnd::OnLButtonDown(CPCWnd* pWnd, CPoint point)
{
	m_offPt = point;
	return FALSE;
}

BOOL CPopChildWnd::OnLButtonUp(CPCWnd* pWnd)
{
	return OnChange(NULL);
}

//////////////////////////////////////////////////////////////
// Override this function to provide custom drawing.
//
void CPopChildWnd::OnDraw(CDC* pDC, CPCWnd* pWnd)
{
	CString str = "Draw your stuff here";
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(0, 0, str);
}

///////////////////////////////////////////
// Override this function to set a cursor when mouse moves into this window.
//
BOOL CPopChildWnd::OnSetCursor(CPCWnd* pWnd, UINT nHitTest, UINT message)
{
	return FALSE;
}

void CPopChildWnd::Destroy()
{
	m_ChildWnd.DestroyWindow();
	m_PopupWnd.DestroyWindow();
}

/////////////////////
// Force a switch
//
void CPopChildWnd::Switch()
{
	CRect rcWnd;
	if(m_ChildWnd.GetStyle() & WS_VISIBLE)
	{			
		m_ChildWnd.GetWindowRect(&rcWnd);
		m_ChildWnd.ShowWindow(SW_HIDE);
		m_PopupWnd.SetWindowPos(NULL, rcWnd.left, rcWnd.top, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
		m_PopupWnd.ShowWindow(SW_SHOW);
	}
	else
	{
		m_PopupWnd.GetWindowRect(&rcWnd);
		CPoint point(rcWnd.left, rcWnd.top);
		::ScreenToClient(m_hParentOwner, &point);
		m_PopupWnd.ShowWindow(SW_HIDE);
		m_ChildWnd.SetWindowPos(NULL, point.x, point.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);
		m_ChildWnd.ShowWindow(SW_SHOW);
	}
}

//////////////////////////////
// When setting position, if current visible window is popup, the rect
// is in screen coordinates. If it's the child window, the rect is in
// the parent-owner's client coordinates.
//
void CPopChildWnd::SetPos(CRect& rect, BOOL bChildOnly)
{
	if(!::IsWindow(m_ChildWnd.GetSafeHwnd()) || !::IsWindow(m_PopupWnd.GetSafeHwnd()))
		return;

	if(m_ChildWnd.GetStyle() & WS_VISIBLE)
	{
		m_ChildWnd.MoveWindow(rect);
	}
	else
		if(!bChildOnly)
			m_PopupWnd.MoveWindow(rect);
}


///////////////////////////////////////////////////////////////
// Tests the condition of two rects. Returns INSIDE if rc2 is complete inside
// of rc1, OUTSIDE if rc2 is completely outside of rc1, and TOUCH otherwise.
//
int CPopChildWnd::RectRect(CRect rc1, CRect rc2)
{
	if(rc2.left > rc1.left &&
		rc2.top > rc1.top &&
		rc2.right < rc1.right &&
		rc2.bottom < rc1.bottom)
		return INSIDE;

	if(rc2.bottom < rc1.top ||
		rc2.top > rc1.bottom ||
		rc2.right < rc1.left ||
		rc2.left > rc1.right)
		return OUTSIDE;

	return TOUCH;
}
