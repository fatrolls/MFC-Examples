//
// Author: Xie Jingwei, Chinese Spell: Ð»¾´Î°
// Email to me, jw_xie@usa.net
// A digital clock control, :-)
//

//
// Usage: See the header, just simple 
// Please Note: Make sure ADD the 12 bitmaps to your project, and 
// sort the ID to correct order. I used IDB_BITMAP1 to IDB_BITMAP12 
// side by side. See following:
//
// Digit:     ID				VALUE
//   0        IDB_BITMAP1		 100
//   1        IDB_BITMAP2		 101	
//   2        IDB_BITMAP3		 102	
//   3        IDB_BITMAP4		 103	
//   4        IDB_BITMAP5		 104
//   5        IDB_BITMAP6		 105	
//   6        IDB_BITMAP7		 106	
//   7        IDB_BITMAP8		 107
//   8        IDB_BITMAP9		 108
//   9        IDB_BITMAP10		 109	
//   :        IDB_BITMAP11		 110
//            IDB_BITMAP12		 111	
//

// There are three properties.
// face color <-----> SetColor();
// style <-----> SetStyle();
// alarm mode <----> SetAlarm();



// EDClock.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"
#include "EDClock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// The resource bitmap face color 
//static COLORREF origin; 
COLORREF CXJWDigitClock::origin = RGB(255, 0, 0); 

/////////////////////////////////////////////////////////////////////////////
// CXJWDigitClock

CXJWDigitClock::CXJWDigitClock()
{
	m_bAlarm = FALSE;
	m_style = XDC_NOSECOND;
	m_color = origin;
	for(int i = 0; i< 12; i++) {
		HBITMAP temp = (HBITMAP)::CreateMappedBitmap(AfxGetApp()->m_hInstance, i+IDB_BITMAP1, 0, NULL, 0);
		m_hBitmap[i] = (HBITMAP)::CopyImage( temp, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG | LR_COPYDELETEORG);
	}
}

CXJWDigitClock::~CXJWDigitClock()
{
	for(int i = 0; i< 12; i++) {
		if(m_hBitmap[i])
			::DeleteObject(m_hBitmap[i]);
	}
}


BEGIN_MESSAGE_MAP(CXJWDigitClock, CStatic)
	//{{AFX_MSG_MAP(CXJWDigitClock)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXJWDigitClock message handlers

void CXJWDigitClock::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//
	// Note: Set the Timer here Pls. 
	// Dont set timer in OnCreate(), you cant recieve WM_CREATE 
	// when control construted in Dialog template. Say: OnCreate not called.
	//
	m_nTimer = SetTimer(1, 1000, NULL);
	::GetObject(m_hBitmap[0], sizeof BITMAP, &m_bm);
	
	CStatic::PreSubclassWindow();
}

void CXJWDigitClock::OnDestroy() 
{
	CStatic::OnDestroy();
	
	// TODO: Add your message handler code here
	KillTimer(m_nTimer);	
}

void CXJWDigitClock::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
}

BOOL CXJWDigitClock::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush brush;
	brush.CreateSolidBrush( ::GetSysColor(COLOR_WINDOWTEXT) ); 
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	CRect rectClient;
	GetClientRect(&rectClient);
	pDC->PatBlt(0, 0, rectClient.Width(), rectClient.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);
	
	return CStatic::OnEraseBkgnd(pDC);
}

void CXJWDigitClock::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == m_nTimer) {
		m_nCount++;
		CRect rectClient;
		GetClientRect(&rectClient);
		m_h = rectClient.Height();
		if(m_style == XDC_SECOND) {
			m_w = rectClient.Width()/8;
		} else {
			m_w = rectClient.Width()/5;
		}

		CTime time = CTime::GetCurrentTime();
		int nh1 = time.GetHour()/10;
		if(nh1)
			Output(nh1, 0);
		else 
			Output(11, 0);
		int nh2 = time.GetHour()%10;
		Output(nh2, 1);
		int nm1 = time.GetMinute()/10;
		Output(nm1, 3);
		int nm2 = time.GetMinute()%10;
		Output(nm2, 4);

		switch(m_style) {
			case XDC_SECOND:
			{
				int ns1 = time.GetSecond()/10;
   				Output(ns1, 6);
				int s2 = time.GetSecond()%10;
				Output(s2, 7);
				Output(10, 2); // double points
				Output(10, 5); // double points
			}
			break;
			case XDC_NOSECOND:
			default:
				if(m_bAlarm)
					Output(10, 2);
				else 
					if(m_nCount%2)
						Output(10, 2); // double points
					else 
						Output(11, 2); // 
				break;
		}
		if(m_bAlarm)
			MessageBeep(-1);
	}
	CStatic::OnTimer(nIDEvent);
}

void CXJWDigitClock::Output(UINT digit, UINT pos)
{
    // draw the bitmap
	CClientDC dc(this);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	// 
	// Alarm mode 
	// 
	if(m_bAlarm && m_nCount%2) 
		digit = 11;
	CBitmap* pBitmap = CBitmap::FromHandle( m_hBitmap[digit] );
	CBitmap* pOldBitmap = dcMem.SelectObject(pBitmap);
    dc.StretchBlt(m_w*pos, 0, m_w, m_h,
			&dcMem, 0, 0, m_bm.bmWidth, m_bm.bmHeight, SRCCOPY);
 	dcMem.SelectObject(pOldBitmap);
	dcMem.DeleteDC();
}


CXJWDigitClock::CClockStyle CXJWDigitClock::SetStyle(CClockStyle style)
{
	CClockStyle temp = m_style;
	m_style = style;
//	if(::IsWindow(m_hWnd))
//		Invalidate();
	return temp;
}

COLORREF CXJWDigitClock::SetColor(COLORREF color)
{
	if(m_color == color)
		return color;
	COLORREF temp = m_color;
	m_color = color;
	for(int i = 0; i< 12; i++) {
		if(m_hBitmap[i])
			::DeleteObject(m_hBitmap[i]);
		COLORMAP	mapColor;
		mapColor.from = origin;
		mapColor.to  = color;
		HBITMAP temp = (HBITMAP)::CreateMappedBitmap(AfxGetApp()->m_hInstance, i+IDB_BITMAP1, 0, &mapColor, 1);
		m_hBitmap[i] = (HBITMAP)::CopyImage( temp, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG | LR_COPYDELETEORG);
	}
	return temp;
}

BOOL CXJWDigitClock::SetAlarm(BOOL bAlarm /*= TRUE*/)
{
	BOOL temp = m_bAlarm;
	m_bAlarm = bAlarm;
	return temp;
}


