
#include "stdafx.h"
#include "BitWnd.h"
#include "BitItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBitWnd::CBitWnd()
  : m_lpBit(NULL),
	m_bMute(FALSE),
	m_bCanMute(FALSE),
	m_hCursor(NULL),
	m_bNotify(FALSE),
	m_bTracking(FALSE),
	m_bAllocFlag(FALSE),
	m_nState(kNormalBit),
	m_bLDownNotify(FALSE)
{
}

CBitWnd::~CBitWnd()
{
	if( m_lpBit != NULL && m_bAllocFlag )
	{
		delete m_lpBit;
		m_lpBit = NULL;
	}
}

BEGIN_MESSAGE_MAP(CBitWnd, CWnd)
	//{{AFX_MSG_MAP(CBitWnd)
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

BOOL CBitWnd::Create(UINT wStyle, CWnd * pParentWnd, UINT nID)
{
	LPCTSTR	lpWndName = NULL;
	lpWndName = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
									AfxGetApp()->LoadStandardCursor(IDC_ARROW),
									(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);
	if( lpWndName == NULL )
		return FALSE;
	//
	// 2.0 Create the window directly...
	//wStyle |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return CWnd::Create(lpWndName, NULL, wStyle, CRect(0, 0, 0, 0), pParentWnd, nID);
}

void CBitWnd::ReLoadBitItem(UINT nResID, int cx, int cy)
{
	if( m_lpBit != NULL && m_bAllocFlag )
	{
		delete m_lpBit;
		m_lpBit = NULL;
		m_bAllocFlag = FALSE;
	}
	ASSERT( m_hWnd != NULL );
	m_lpBit = new CBitItem(nResID, cx, cy);
	m_bAllocFlag = TRUE;
	ASSERT( m_lpBit != NULL );
	this->MoveWindow(0, 0, m_lpBit->GetItemWidth(), m_lpBit->GetItemHeight());
}
void CBitWnd::SetBitItem(CBitItem * lpBit)
{
	ASSERT( m_lpBit == NULL );
	ASSERT( this->m_hWnd != NULL);
	m_lpBit = lpBit;
	this->MoveWindow(0, 0, m_lpBit->GetItemWidth(), m_lpBit->GetItemHeight());
}

BOOL CBitWnd::OnEraseBkgnd(CDC* pDC) 
{
	(m_lpBit != NULL) ? m_lpBit->CopyItemIndex(pDC, m_nState, FALSE) : NULL;
	return TRUE;
}

BOOL CBitWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if( m_hCursor != NULL )
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return FALSE;
}

LRESULT CBitWnd::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_nState = m_bMute ? kActiveBit : kNormalBit;
	m_nState = (m_lpBit->GetItemNums() > 1) ? m_nState : kNormalBit;

	m_bTracking = FALSE;
	this->Invalidate();
	return 0;
}

LRESULT CBitWnd::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_nState = (m_lpBit->GetItemNums() > 1) ? kHoverBit : kNormalBit;
	m_nState = m_bMute ? kActiveBit : m_nState;

	this->Invalidate();
	return 0;
}

void CBitWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( !m_bTracking )
	{
		TRACKMOUSEEVENT tme = {0};
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
	if( m_bNotify )
	{
		ASSERT( GetParent() != NULL );
		this->ClientToScreen(&point);
		GetParent()->ScreenToClient(&point);
		GetParent()->SendMessage(WM_MOUSEMOVE, nFlags, MAKELPARAM(point.x, point.y));
	}
}

void CBitWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_nState = (m_lpBit->GetItemNums() > 2) ? kActiveBit : kNormalBit;
	m_nState = m_bMute ? kNormalBit : m_nState;
	m_bMute	 = m_bCanMute ? !m_bMute : m_bMute;
	this->Invalidate();

	if( m_bLDownNotify )
	{
		ASSERT( GetParent() != NULL );
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	}
	
	if( m_bNotify )
	{
		ASSERT( GetParent() != NULL );
		this->ClientToScreen(&point);
		GetParent()->ScreenToClient(&point);
		GetParent()->SendMessage(WM_LBUTTONDOWN, nFlags, MAKELPARAM(point.x, point.y));
	}
}

void CBitWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( !m_bMute )
	{
		m_nState = (m_lpBit->GetItemNums() > 1) ? kHoverBit : kNormalBit;
		this->Invalidate();
	}
	if( !m_bLDownNotify )
	{
		ASSERT( GetParent() != NULL );
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	}
	if( m_bNotify )
	{
		ASSERT( GetParent() != NULL );
		this->ClientToScreen(&point);
		GetParent()->ScreenToClient(&point);
		GetParent()->SendMessage(WM_LBUTTONUP, nFlags, MAKELPARAM(point.x, point.y));
	}
}
