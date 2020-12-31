// BuddiedSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "colorselector.h"
#include "BuddiedSliderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuddiedSliderCtrl

CBuddiedSliderCtrl::CBuddiedSliderCtrl()
{
	m_pBuddyWnd = NULL;
	m_brWhiteBrush.CreateStockObject( WHITE_BRUSH );
}

CBuddiedSliderCtrl::~CBuddiedSliderCtrl()
{
}


BEGIN_MESSAGE_MAP(CBuddiedSliderCtrl, CCustomDrawSliderCtrl)
	//{{AFX_MSG_MAP(CBuddiedSliderCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuddiedSliderCtrl message handlers

HWND CBuddiedSliderCtrl::SetBuddy(CWnd *pBuddyWnd)
{
	ASSERT( ::IsWindow(pBuddyWnd->m_hWnd) );
	m_pBuddyWnd = pBuddyWnd;
	pBuddyWnd->SetOwner( this );
	pBuddyWnd->ShowWindow( SW_SHOW );
	HWND hWnd = (HWND) SendMessage( TBM_SETBUDDY, (WPARAM)FALSE, (LPARAM)pBuddyWnd->m_hWnd );
	ReflectedScrollMessage();	// in order to get the initial display of text
	return hWnd;
}

void CBuddiedSliderCtrl::ReflectedScrollMessage()
{
	// update buddy's text, if there is a buddy
	if ( m_pBuddyWnd != NULL )
	{
		int iPos = GetPos();
		int iMax = GetRangeMax();
		CString text;
		text.Format( "%d (0x%02X)", iMax - iPos, iMax - iPos );	// BAD!!! Because of top-to-bottom orientation of slider
		m_pBuddyWnd->SetWindowText( text );
	}
}

void CBuddiedSliderCtrl::SetPos(int nPos)
{
	CSliderCtrl::SetPos( nPos );

	ReflectedScrollMessage();
}



