/*
** Author: Guy Gascoigne - Piggford
** Internet: guy@wyrdrune.com
**
** You can use this source in any way you like as long as you don't try to sell it.
**
** Any attempt to sell this in source code form must have the permission
** of the original author. You can produce commercial executables with
** this source, but you may not sell it.
**
** Copyright, 1994-98 Guy Gascoigne - Piggford
**
*/

#include "stdafx.h"
#include "resource.h"
#include "SplitFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame

IMPLEMENT_DYNAMIC(CSplitFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CSplitFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSplitFrame)
	ON_COMMAND(ID_VIEW_TOGGLESPLITTER, OnToggleSplitter)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOGGLESPLITTER, OnUpdateToggleSplitter)
	ON_COMMAND(ID_VIEW_BOTH, OnViewBoth)
	ON_COMMAND(ID_VIEW_FIRSTVIEW, OnViewFirstView)
	ON_COMMAND(ID_VIEW_SECONDVIEW, OnViewSecondView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame construction/destruction

CSplitFrame::CSplitFrame( CRuntimeClass * pView1, CRuntimeClass * pView2 )
	: m_pView1( pView1 ),
	m_pView2( pView2 ),
	m_bInitialOrientation(0)
{
	m_splitSizes[0] = CSize(0,0);
	m_splitSizes[1] = CSize(0,0);
}

CSplitFrame::~CSplitFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame diagnostics

#ifdef _DEBUG
void CSplitFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CSplitFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame message handlers

void CSplitFrame::SetInitialOrienation( BOOL bHoriz )
{
	m_bInitialOrientation = bHoriz;
}

BOOL CSplitFrame::OnCreateClient(LPCREATESTRUCT /* lpcs */, CCreateContext* pContext)
{
	BOOL horizBar = m_bInitialOrientation;

	CSize size1, size2;
	MakeSplitSizes( horizBar, size1, size2 );

	int rows, cols;
	if ( horizBar )
	{
		cols = 1, rows = 2;
	}
	else
	{
		cols = 2, rows = 1;
	}
	BOOL bSuccess;
	bSuccess  = m_wndSplitter.CreateStatic( this, rows, cols );
	bSuccess &= m_wndSplitter.CreateView(0, 0, m_pView1, size1, pContext);
	bSuccess &= m_wndSplitter.CreateView(rows-1, cols-1, m_pView2, size2, pContext);

	return bSuccess;
}

void CSplitFrame::OnToggleSplitter()
{
	if ( m_wndSplitter.GetSafeHwnd() )
	{
		CacheSize();
		m_wndSplitter.Toggle();

		CSize sz1, sz2;
		MakeSplitSizes( m_wndSplitter.BarIsHorizontal(), sz1, sz2 );
		m_wndSplitter.UpdateSizes( sz1, sz2 );
	}
}

void CSplitFrame::OnUpdateToggleSplitter(CCmdUI* pCmdUI)
{
	if ( m_wndSplitter.BarIsHorizontal() )
		pCmdUI->SetText( CString( (LPCTSTR)IDS_SPLIT_VER ) );
	else
		pCmdUI->SetText( CString( (LPCTSTR)IDS_SPLIT_HOR ) );
}

void CSplitFrame::MakeSplitSizes( BOOL horizBar, CSize & sz1, CSize & sz2 )
{
	CRect rect;
	GetClientRect(&rect);
	CSize clientSize = rect.Size();

	CSize sz = ReadCachedSize( horizBar );

	if ( sz != CSize( 0, 0 ) )
	{
		sz2.cx = clientSize.cx - sz.cx;
		sz2.cy = clientSize.cy - sz.cy;
		sz1.cx = sz.cx;
		sz1.cy = sz.cy;
	}
	else
	{
		sz1 = clientSize;
		sz1.cx /= 3;
		sz1.cy /= 2;

		sz2.cx = sz1.cx * 2;
		sz2.cy = sz1.cy * 1;
	}
}

void CSplitFrame::OnViewBoth() 
{
	CSize sz1, sz2;
	MakeSplitSizes( m_wndSplitter.BarIsHorizontal(), sz1, sz2 );
	m_wndSplitter.UpdateSizes( sz1, sz2 );
}

void CSplitFrame::OnViewFirstView() 
{
	viewSomeView( 1 );
}

void CSplitFrame::OnViewSecondView() 
{
	viewSomeView( 2 );
}

void CSplitFrame::viewSomeView( int iView ) 
{
	ASSERT( iView == 1 || iView == 2 );

	CacheSize();

	CRect rect;
	GetClientRect(&rect);
	CSize clientSize = rect.Size();
	CSize csZero( 0, 0 );

	if ( iView == 1 )
		m_wndSplitter.UpdateSizes( clientSize, csZero );
	else
		m_wndSplitter.UpdateSizes( csZero, clientSize );
}

void CSplitFrame::CacheSize()
{
	BOOL okToWrite = FALSE;
	int min, dummy1, dummy2;

	if ( m_wndSplitter.BarIsHorizontal() )
	{
		m_wndSplitter.GetRowInfo( 0, dummy1, min );
		m_wndSplitter.GetRowInfo( 1, dummy2, min );
	}
	else
	{
		m_wndSplitter.GetColumnInfo( 0, dummy1, min );
		m_wndSplitter.GetColumnInfo( 1, dummy2, min );
	}

	okToWrite = ( dummy1 != 0 && dummy2 != 0 );
	if ( okToWrite )	// we want to discount the maximized views.
	{
		int dummy, x, y;
		m_wndSplitter.GetColumnInfo( 0, x, dummy );
		m_wndSplitter.GetRowInfo( 0, y, dummy );

		m_splitSizes[ (int)((BOOL)m_wndSplitter.BarIsHorizontal()) ] = CSize( x, y );
	}
}

CSize CSplitFrame::ReadCachedSize( BOOL horizBar )
{
	CSize sz;
	sz = m_splitSizes[ (int)(horizBar) ];
	return sz;
}

