// EPropCtrl.cpp: implementation of the EPropCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EPropCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EPropCtrl::EPropCtrl()
{
	m_nTabHeight = 30;

	m_CommentPane.SetCommentHost( &m_PropListCtrl );
	m_CommentPane.m_pPropWnd = &m_PropListCtrl;
	
	m_PropListCtrl.m_pCommentPane = &m_CommentPane;

	m_bCommentPaneEnabled = false;

	m_nCommentPaneHeight = 13*3 + 6;
//	m_MouseDownPosition.x = -1;
}

EPropCtrl::~EPropCtrl()
{

}

IMPLEMENT_DYNCREATE(EPropCtrl, CWnd)

BEGIN_MESSAGE_MAP(EPropCtrl, CWnd)
	//{{AFX_MSG_MAP(EPropCtrl)
	ON_NOTIFY(TCN_SELCHANGE, 1 , OnSelchangeTab)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void EPropCtrl::Create( CWnd* pParent , int nDestinationCWndID )
{
	CRect r;
	CWnd* pWnd = pParent->GetDlgItem( nDestinationCWndID );
	pWnd->GetWindowRect(&r);
	pParent->ScreenToClient(&r);
	pWnd->DestroyWindow();
	Create( pParent , nDestinationCWndID, r );
}

void EPropCtrl::Create( CWnd* pParent , int nDestinationCWndID , const CRect& rect , IPropertyChangeListener* pListener )
{
	//
	// create myselc
	//
	CRuntimeClass* rtc = GetRuntimeClass();

	CWnd::Create( NULL , GetRuntimeClass()->m_lpszClassName , WS_VISIBLE | WS_CHILD , rect , pParent , nDestinationCWndID );

	//
	// adjust rect for tab control
	//

	int w = rect.Width();
	int h = rect.Height();


	int y0 = 0;
	int y1 = h-m_nTabHeight-m_nCommentPaneHeight;
	int y2 = h-m_nTabHeight;
	int y3 = h;

	
	CRect r( 0 , 0 , w , 0 );


	r.top    = y0;
	r.bottom = y1;
	m_PropListCtrl.Create( NULL , m_PropListCtrl.GetRuntimeClass()->m_lpszClassName , WS_VISIBLE | WS_CHILD , r , this , -1 );

	r.top    = y1;
	r.bottom = y2;
	m_CommentPane.Create( NULL , m_CommentPane.GetRuntimeClass()->m_lpszClassName , WS_VISIBLE | WS_CHILD , r , this , 2 );

	r.top    = y2;
	r.bottom = y3;
	m_TabCtrl.Create( WS_VISIBLE | WS_CHILD | TCS_RIGHT , r , this , 1 );
	m_TabCtrl.SetFont( m_PropListCtrl.GetFont() );

	//
	//
	//
	SetPropertyChangeListener(pListener);
}

void EPropCtrl::SetImageList( int nBitmapID , int nIconWidth , COLORREF nTransparentColor )
{
	m_ImageList.DeleteImageList();
	m_ImageList.Create( nBitmapID , nIconWidth , 10 , nTransparentColor );
	m_TabCtrl.SetImageList(&m_ImageList);
}

void EPropCtrl::Resize( const CRect& Rect ) 
{
//	MoveWindow(Rect);

	int cx = Rect.Width();
	int cy = Rect.Height();

	int nTabPaneHeight = m_nTabHeight;
	int nComPaneHeight = m_bCommentPaneEnabled ? m_nCommentPaneHeight /*m_CommentPane.GetHeight(cx)*/ : 0;

	if( m_PropListCtrl.GetPropertyList()->HasUserTabs() )
	{
		m_TabCtrl.ShowWindow(SW_SHOW);
	}
	else
	{
		nTabPaneHeight = 0;
		m_TabCtrl.ShowWindow(SW_HIDE);
	}

	if( nComPaneHeight > 0 )
	{
		m_CommentPane.ShowWindow(SW_SHOW);
	}
	else
	{
		m_CommentPane.ShowWindow(SW_HIDE);
	}

	int nPropPaneHeight = cy - nComPaneHeight - nTabPaneHeight - 8;

	CRect r( 0 , 0 , cx , 0 );
	
	r.top    = 0;
	r.bottom = r.top + nPropPaneHeight;
	m_PropListCtrl.MoveWindow(&r);

	r.top    = r.bottom;
	r.bottom = r.top + nTabPaneHeight;
	m_TabCtrl.MoveWindow(&r);

	r.top    = r.bottom;
	r.bottom = r.top + 8;
	m_CommentSplitterRect = r;

	r.top    = r.bottom;
	r.bottom = r.top + nComPaneHeight;
	m_CommentPane.MoveWindow(&r);

	Invalidate();
}


void EPropCtrl::SetPropertyChangeListener( IPropertyChangeListener* pListener )
{
	m_PropListCtrl.SetPropertyChangeListener( pListener );
}

void EPropCtrl::RefreshHostList()
{
	m_PropListCtrl.RefreshHostList();
	RefreshTabCtrl();
}

void EPropCtrl::RefreshTabCtrl()
{
	IPropertyHost* pHost = m_PropListCtrl.GetPropertyHost();

	m_TabCtrl.DeleteAllItems();

	if( pHost != NULL )
	{
		EPropList* pList = m_PropListCtrl.GetPropertyList();

		int nNumTabs = pList->GetTabCount();

		if( pList->HasUserTabs() )
		{
			for( int i=0 ; i<nNumTabs ; i++ )
			{
				EPropList::ETabGroup* pTab = pList->GetTab(i);
				CString* pName = pTab->GetName();
				int      nIcon = pTab->GetIcon();

				if( nIcon==-1 )
				{
					m_TabCtrl.InsertItem(i,*pName);
				}
				else
				{
					ASSERT( m_ImageList.GetSafeHandle()!=0 );	//dont' forget to SetImageList()
					m_TabCtrl.InsertItem(i,*pName,nIcon);
				}
			}

			int nActiveTab = m_PropListCtrl.GetPropertyList()->GetActiveTab();
			m_TabCtrl.SetCurSel( nActiveTab );
		}

//moved outside to also resize if propertyhost is null
//		CRect r;
//		GetWindowRect(&r);
//		GetParent()->ScreenToClient(&r);
//		Resize(r);

	}

	CRect r;
	GetWindowRect(&r);
	GetParent()->ScreenToClient(&r);
	Resize(r);
}


void EPropCtrl::SetPropertyHost( IPropertyHost* pHost )
{
//	IPropertyHost*pPrevHost = m_PropListCtrl.GetPropertyHost();
//	if(pPrevHost == pHost)
//		return;

	m_PropListCtrl.SetPropertyHost( pHost );

	//
	//
	//

	RefreshTabCtrl();
}

void EPropCtrl::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	int n = m_TabCtrl.GetCurSel();
	m_PropListCtrl.SetActiveTab(n);
}

void EPropCtrl::ChildSizeChanged()
{
	CRect r;
	GetWindowRect(&r);
	GetParent()->ScreenToClient(&r);
	Resize(r);
}

void EPropCtrl::EnableCommentPane( bool bEnable )
{
	m_bCommentPaneEnabled = bEnable;
	CRect r;
	GetWindowRect(&r);
	GetParent()->ScreenToClient(&r);
	Resize(r);
}

void EPropCtrl::SetActiveTab(int n)
{
	m_PropListCtrl.SetActiveTab(n);
	m_TabCtrl.SetCurSel(n);
}

void EPropCtrl::OnSize(UINT nType, int cx, int cy) 
{
	if(m_TabCtrl.m_hWnd!=0)
	{
		Resize( CRect(0,0,cx,cy));
	}
}



void EPropCtrl::OnPaint()
{
	CPaintDC dc(this);
	m_PropListCtrl.DrawFrame( &dc , m_CommentSplitterRect , true , m_PropListCtrl.GetColorPaneKey() );

	//
	// sunken nipples on splitter?
	//

//	int x = m_CommentSplitterRect.right - 5;
//	int y = m_CommentSplitterRect.top   + 3;
//
//	for( int i=0 ; i<3 ; i++ )
//	{
//		m_PropListCtrl.DrawNipple( &dc , x , y , false );
//		x -= 4;
//	}
}

void EPropCtrl::OnLButtonDown( UINT nFlags , CPoint PointCP )
{
	bool bMouseOverSplitter = m_CommentSplitterRect.PtInRect(PointCP) == TRUE;

	if( bMouseOverSplitter )
	{
		SetCapture();
		SetCursor( LoadCursor(NULL,IDC_SIZENS) );
	}
}

void EPropCtrl::OnLButtonUp( UINT nFlags , CPoint PointCP )
{
	ReleaseCapture();
}

void EPropCtrl::OnMouseMove( UINT nFlags , CPoint PointCP )
{
	if( GetCapture()==this )
	{
		if( nFlags&MK_LBUTTON )
		{
			CRect cr;
			GetClientRect(&cr);

			int y = cr.Height() - PointCP.y;	//mouse y position, from bottom

			y -= 4;		//half splitter width

			y -= 6;		//text margin y

			y += 6;
			y /= 13;
			y *= 13;
			y += 6;

			if( y<13*1+6 )
			{
				y = 0;
			}

			SetCommentPaneHeight(y);
		}
		else
		{
			ASSERT(false);
		}
	}
	else
	{
		bool bMouseOverSplitter = m_CommentSplitterRect.PtInRect(PointCP) == TRUE;

		if( bMouseOverSplitter )
		{
			SetCursor( LoadCursor(NULL,IDC_SIZENS) );
		}
	}


}

void EPropCtrl::SetCommentPaneHeight( int nHeight )
{
	if( nHeight != m_nCommentPaneHeight )
	{
		m_nCommentPaneHeight = nHeight;
		CRect cr;
		GetClientRect(&cr);
		Resize(cr);
	}
}
