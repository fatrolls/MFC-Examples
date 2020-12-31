// HistogramCtrl.cpp : implementation file
//

// stdafx.cpp : source file that includes just the standard includes
//	CPanel.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#include "HistogramCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramCtrl

CHistogramCtrl::CHistogramCtrl()
{
	m_nPos      = 0;
	m_nLower    = 0;
	m_nUpper    = 100;
}

CHistogramCtrl::~CHistogramCtrl()
{
}


BEGIN_MESSAGE_MAP(CHistogramCtrl, CWnd)
	//{{AFX_MSG_MAP(CHistogramCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSpikeCtrl message handlers

BOOL CHistogramCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

	return  CWnd::CreateEx(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE, 
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

void CHistogramCtrl::SetRange(UINT nLower, UINT nUpper)
{
	ASSERT(nLower >= 0 && nLower < 0xffff);
	ASSERT(nUpper > nLower && nUpper < 0xffff);

	m_nLower = nLower;
	m_nUpper = nUpper;
	
	InvalidateCtrl();
}

void CHistogramCtrl::InvalidateCtrl()
{
	// Small optimization that just invalidates the client area
	// (The borders don't usually need updating)
	CClientDC dc(this);
	CRect rcClient;

	GetClientRect(rcClient);

	if (m_MemDC.GetSafeHdc() == NULL)
	{
		m_MemDC.CreateCompatibleDC(&dc);
		m_Bitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
		m_MemDC.SelectObject(m_Bitmap);
		// draw scale
		m_MemDC.SetBkColor(RGB(0,0,0));
		CBrush bkBrush(HS_HORIZONTAL,RGB(0,128,0));
    m_MemDC.FillRect(rcClient,&bkBrush);
	}

	InvalidateRect(rcClient);
}

UINT CHistogramCtrl::SetPos(UINT nPos)
{
	if (nPos > m_nUpper)
		nPos = m_nUpper;

	if (nPos < m_nLower)
		nPos = m_nLower;

	UINT nOld = m_nPos;
	m_nPos = nPos;

	DrawSpike();

	Invalidate();

	return nOld;
}

void CHistogramCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
	// draw scale
	CRect rcClient;
	GetClientRect(rcClient);

	// draw scale
	if (m_MemDC.GetSafeHdc() != NULL)
	{
		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_MemDC, 0, 0, SRCCOPY);
	}
}

void CHistogramCtrl::DrawSpike()
{
//	CClientDC dc(this);
	UINT  nRange = m_nUpper - m_nLower;
	CRect rcClient;
	GetClientRect(rcClient);

	if (m_MemDC.GetSafeHdc() != NULL)
	{
		m_MemDC.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_MemDC, 4, 0, SRCCOPY);

		CRect rcTop(rcClient.right - 4, 0, rcClient.right - 2, rcClient.bottom);
		rcTop.top  = (long) (((float) (m_nPos - m_nLower) / nRange) * rcClient.Height());
		rcTop.top  = rcClient.bottom - rcTop.top;

		// draw scale
		CRect rcRight = rcClient;
		rcRight.left = rcRight.right - 4;
		m_MemDC.SetBkColor(RGB(0,0,0));

    CBrush bkBrush(HS_HORIZONTAL,RGB(0,128,0));  
    m_MemDC.FillRect(rcRight,&bkBrush);

		// draw current spike
		CBrush brush(RGB(0,255,0));
		m_MemDC.FillRect(rcTop, &brush);
	}
}
