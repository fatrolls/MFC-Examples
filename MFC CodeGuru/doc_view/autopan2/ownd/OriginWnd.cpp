///////////////////////////////////////////////////////////////////
//	Written by Russ Freeman (russf@dircon.co.uk or russf@digita.com)
//	Copyright (c) 1998.
//
//	This code may be used in compiled form in any way you desire. This
//	file may be redistributed unmodified by any means PROVIDING it is 
//	not sold for profit without the authors written consent, and 
//	providing that this notice and the authors name is included. If 
//	the source code in this file is used in any commercial application 
//	then acknowledgement must be made to the author of this file 
//	(in whatever form you wish).
//
//	This file is provided "as is" with no expressed or implied warranty.
//
//	Implements the origin window, cursor handling and a fair bit of the processing required
//	to handle the middle mouse button.
//
//	Easy to use, simply call StartPanning(...)
//	See sample CScrollView derived view class in the associated sample program.
//
//	Author: Russell Freeman
//	date:		13/6/98
//	Email:	russf@dircon.co.uk or russf@digita.com
//
//	Tested in ANSI and UNICODE builds.
//	Tested using Window NT 4.0 sp3, not tested using Windows 95
//	Linted	13/6/98

#include "stdafx.h"
#include "resource.h"
#include "OriginWnd.h"
#include "OWndDLL.h"

//lint -esym( 613, COriginWnd::m_pParent )


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum {
			knTimerID = 999
			, knTimerDuration = 25
			, knDistanceToScrollDivisor = 16
		};

static const UINT uOriginWindowUpdateMessage = ::RegisterWindowMessage( OWND_WINDOW_UPDATE );

//
//	These arrays are identical except for the middle cursor, this just makes 
static const UINT g_arrCursorsBoth[3][3] =
												{
													IDC_NW,			IDC_WEST,		IDC_SW,
													IDC_NORTH,	IDC_NOMOVE,	IDC_SOUTH,
													IDC_NE,			IDC_EAST,		IDC_SE,
												};

static const UINT g_arrCursorsVert[3][3] =
												{
													IDC_NW,			IDC_WEST,		IDC_SW,
													IDC_NORTH,	IDC_NOMOVE_VERTICAL,	IDC_SOUTH,
													IDC_NE,			IDC_EAST,		IDC_SE,
												};

static const UINT g_arrCursorsHorz[3][3] =
												{
													IDC_NW,			IDC_WEST,		IDC_SW,
													IDC_NORTH,	IDC_NOMOVE_HORIZONTAL,	IDC_SOUTH,
													IDC_NE,			IDC_EAST,		IDC_SE,
												};

COriginWnd::CursorArray COriginWnd::GetCursorArray( BOOL bHorz, BOOL bVert )
//
//	Return a pointer to the array above to use for the mouse cursor
{
	if( bHorz == FALSE )
	{
		return &g_arrCursorsVert;
	}
	else if( bVert == FALSE )
	{
		return &g_arrCursorsHorz;
	}
	return &g_arrCursorsBoth;
}

//
//	One and only origin window, used by the one and only hook.
static COriginWnd *g_pOriginWnd = NULL;
static HHOOK g_hdlHook = NULL;


LRESULT CALLBACK COriginWnd::HookProc(int code, WPARAM wParam ,LPARAM lParam)
//
//	Hook procedure to catch messages that should terminate our origin window.
{
	MSG		*pMsg = reinterpret_cast<MSG *>(lParam);

	ASSERT_VALID( g_pOriginWnd );
	ASSERT_VALID( g_pOriginWnd->m_pParent );
	if( pMsg->hwnd == g_pOriginWnd->m_pParent->GetSafeHwnd() )
	{
		switch( pMsg -> message )
		{
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
		case WM_CHAR:
		case WM_KILLFOCUS:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_MOUSEWHEEL:
			VERIFY( g_pOriginWnd->DestroyWindow() );
			break;
		default:
			//	Intentionally do nothing
			;
		}
	}
	return CallNextHookEx( g_hdlHook, code, wParam, lParam );
}

/////////////////////////////////////////////////////////////////////////////
// COriginWnd

COriginWnd::COriginWnd( BOOL bHorz, BOOL bVert, CPoint ptOrigin )
	: m_sizeBitmap( 0, 0 )
	, m_bScrollVert( bVert ? 1 : 0 )		//	Our boolean values are used in the lookup table below so the must be either one or zero
	, m_bScrollHorz( bHorz ? 1 : 0 )
	, m_ptOrigin( ptOrigin )
	, m_sizeDistance(0,0)
	, m_ptCursorPrevious( 0, 0 )
	, m_parrnIDs( GetCursorArray( m_bScrollHorz, m_bScrollVert ) )
	, m_pParent( NULL )
	, m_bScrolledAlready( FALSE )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState( ) );

	//	It's pointless displaying the origin window when you are not going to do any scrolling
	ASSERT( m_bScrollVert || m_bScrollHorz );

	//
	//	Determine which of the origin bitmaps to display using a simple table. We want pretty
	//	much the same behaviour as IE.
	static const UINT arrOrigin[2][2] = { 0, IDB_ORIGIN_VERTICAL, IDB_ORIGIN_HORIZONTAL, IDB_ORIGIN_ALL };
	ASSERT( arrOrigin[ m_bScrollHorz ][ m_bScrollVert ] != 0 );	//	Oops, how did this happen?
	VERIFY( m_bitmap.LoadBitmap( arrOrigin[ m_bScrollHorz ][ m_bScrollVert ] ) );

	BITMAP bmp;
	VERIFY( m_bitmap.GetBitmap( &bmp ) );
	m_sizeBitmap.cx = bmp.bmWidth;
	m_sizeBitmap.cy = bmp.bmHeight;
}

COriginWnd::~COriginWnd()
{
	m_pParent = NULL;
}


BEGIN_MESSAGE_MAP(COriginWnd, CWnd)
	//{{AFX_MSG_MAP(COriginWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_MBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL COriginWnd::Create( CWnd *pParent )
//
//	Actually create the window.
//
//	I would have done this in the constructor but how could I have returned an error?
{
	//	Must be a valid parent window
	ASSERT_VALID( pParent );

	CPoint pt = m_ptOrigin;
	pParent->ClientToScreen( &pt );


	//
	//	We create the window, the centre of the window should be the origin point so when all of the startup is done the cursor
	//	will appear over the centre of the origin window.
	const int nHalfHeight = m_sizeBitmap.cy / 2;
	const int nHalfWidth = m_sizeBitmap.cx / 2;
	if( CWnd::CreateEx( WS_EX_TOOLWINDOW, AfxRegisterWndClass(CS_SAVEBITS), NULL, WS_CLIPSIBLINGS | WS_POPUP, pt.x - nHalfWidth, pt.y - nHalfHeight, m_sizeBitmap.cx, m_sizeBitmap.cy, pParent->GetSafeHwnd(), 0 ) )
	{
		VERIFY( SetWindowPos( &wndTopMost, 0,0,0,0, SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE ) );
		m_pParent = pParent;
		//
		//	Determine the thresholds for the cursor changing, while the cursor is between these points the cursor does not
		//	change to one of the diagonal cursors. I think this is how IE does it - sure looks like it.
		m_rcCursorMargin.SetRect( m_ptOrigin.x - nHalfWidth, m_ptOrigin.y - nHalfHeight, m_ptOrigin.x + nHalfWidth, m_ptOrigin.y + nHalfHeight );

		//
		//	We want a circular(or as much as the bitmap allows) window, so do the usual
		//	thing of creating a region and assigning it to the window.
		CRgn rgn;
		VERIFY( rgn.CreateEllipticRgn( 0, 0, m_sizeBitmap.cx, m_sizeBitmap.cy ) );
		VERIFY( SetWindowRgn( static_cast<HRGN>( rgn.Detach() ), TRUE ) );

		//
		//	Set our mouse capture so that all mouse messages go to us and also set a timer
		//	so that we can periodically send our message to our parent.
		SetCapture();
		VERIFY( SetTimer( knTimerID, knTimerDuration, NULL ) == knTimerID );
		g_pOriginWnd = this;
		g_hdlHook = SetWindowsHookEx( WH_GETMESSAGE, HookProc, NULL, GetCurrentThreadId() );
		return TRUE;
	}
	TRACE0("Failed to create Origin window\n");
	return FALSE;
}


HCURSOR COriginWnd::GetNewCursorAndDistance( CPoint pt )
//
//	Figures out the new cursor to display and the distance the cursor is from our
//	origin point.
//
//	Returns a new cursor or NULL if the cursor and therefore the distance has not changed
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState( ) );
	if( m_ptCursorPrevious != pt )
	{
		m_ptCursorPrevious = pt;

		//
		//	If the point is within one of our margins or we are doing one way scrolling then we correct the point
		//	by setting it's axis value to the same as our origin. This makes makes the cursor behaviour
		//	the same as IE.
		if( m_bScrollHorz == FALSE || ( pt.x > m_rcCursorMargin.left && pt.x < m_rcCursorMargin.right ) )
			pt.x = m_ptOrigin.x;

		if( m_bScrollVert == FALSE || ( pt.y > m_rcCursorMargin.top && pt.y < m_rcCursorMargin.bottom ) )
			pt.y = m_ptOrigin.y;

		//
		//	Determine the distance the the cursor is from our origin point
		m_sizeDistance.cx = pt.x - m_ptOrigin.x;
		m_sizeDistance.cy = pt.y - m_ptOrigin.y;

		//
		//	Now that we have our distance from our origin and we have normalised it to be within our margins
		//	where necessary we now figure out which cursor to use, this is a simple lookup into a table again.
		const int nHoriz = max( -1, min( 1, m_sizeDistance.cx ) ) + 1;
		const int nVert = max( -1, min( 1, m_sizeDistance.cy ) ) + 1;

		return AfxGetApp()->LoadCursor( (*m_parrnIDs)[nHoriz][nVert] );
	}
	return NULL;
} 

/////////////////////////////////////////////////////////////////////////////
// COriginWnd message handlers

void COriginWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	//
	//	Simple drawing code, all it does is blt the bitmap we have chosen onto our window.
	CDC dcMem;
	VERIFY( dcMem.CreateCompatibleDC( &dc ) );
	CGdiObject *pOldBmp = dcMem.SelectObject( &m_bitmap );
	VERIFY( dc.BitBlt( 0, 0, m_sizeBitmap.cx, m_sizeBitmap.cy, &dcMem, 0, 0, SRCCOPY ) );
	(void)dcMem.SelectObject( pOldBmp );
}


void COriginWnd::OnTimer(UINT nIDEvent) 
{
	ASSERT( nIDEvent == knTimerID );
	UNREFERENCED_PARAMETER( nIDEvent );

	CPoint ptCursor;
	VERIFY( GetCursorPos( &ptCursor ) );

	ASSERT_VALID( m_pParent );
	m_pParent->ScreenToClient( &ptCursor );
	HCURSOR hc = GetNewCursorAndDistance( ptCursor );
	if( hc )
	{
		SetCursor( hc );
	}

	//
	//	If the parent did not respond then we will handle the scrolling.
	CSize sizeLocalDistance( m_sizeDistance.cx / knDistanceToScrollDivisor, m_sizeDistance.cy / knDistanceToScrollDivisor );
	if( !m_pParent->SendMessage( uOriginWindowUpdateMessage, 0, reinterpret_cast<LPARAM>( &sizeLocalDistance ) ) )
	{
		const CSize sizeScrollLimit( m_pParent->GetScrollLimit( SB_HORZ ), m_pParent->GetScrollLimit( SB_VERT ) );

		const int nHorzScrollPos = m_pParent->GetScrollPos( SB_HORZ );
		const int nVertScrollPos = m_pParent->GetScrollPos( SB_VERT );

		const int nNewHorzScrollPos = max( 0, min( sizeScrollLimit.cx, nHorzScrollPos + sizeLocalDistance.cx ) );
		const int nNewVertScrollPos = max( 0, min( sizeScrollLimit.cy, nVertScrollPos + sizeLocalDistance.cy ) );

		CSize sizeDiff( nNewHorzScrollPos - nHorzScrollPos , nNewVertScrollPos - nVertScrollPos  );
		
		if( sizeDiff.cx || sizeDiff.cy )
		{
			m_bScrolledAlready = TRUE;

			if( nNewVertScrollPos != m_pParent->GetScrollPos( SB_VERT ) )
				(void)m_pParent->SetScrollPos( SB_VERT, nNewVertScrollPos );

			if( nNewHorzScrollPos != m_pParent->GetScrollPos( SB_HORZ ) )
				(void)m_pParent->SetScrollPos( SB_HORZ, nNewHorzScrollPos );

			m_pParent->ScrollWindow( -sizeDiff.cx, -sizeDiff.cy );
			m_pParent->UpdateWindow();
		}
	}
}




LRESULT COriginWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//
//	I have used the WindowProc function because having these messages as sperate functions
//	is a waste and I am not using the messages for what they are I am only using them to signal
//	to myself that it's time to go.
{
	switch( message )
	{
	case WM_RBUTTONDOWN:			//	Intentionally drop through!
	case WM_MBUTTONDOWN:			//	Intentionally drop through!
	case WM_LBUTTONDOWN:			//	Intentionally drop through!
	case WM_CANCELMODE:				//	Intentionally drop through!
	case WM_CAPTURECHANGED:
		VERIFY( DestroyWindow() );
		break;		
	default:
		return CWnd::WindowProc(message, wParam, lParam);
	}

	return 0;
}


void COriginWnd::PostNcDestroy()
{
	CWnd::PostNcDestroy();
	delete this;
}


void COriginWnd::OnDestroy() 
{
	CWnd::OnDestroy();

	VERIFY( UnhookWindowsHookEx( g_hdlHook ) );
	g_hdlHook = NULL;
	g_pOriginWnd = NULL;
}


void COriginWnd::OnMButtonUp(UINT /*nFlags*/, CPoint /*point*/) 
{
	if( m_bScrolledAlready )
	{
		VERIFY( DestroyWindow() );
	}	
}
