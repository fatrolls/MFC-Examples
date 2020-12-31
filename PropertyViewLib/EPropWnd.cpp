// EPropWnd.cpp: implementation of the EPropWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EProperty.h"
#include "IPropertyChangeListener.h"
#include "ECommentPane.h"
#include "IPropertyHost.h"
#include "EPropWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(EPropWnd, CWnd)

BEGIN_MESSAGE_MAP(EPropWnd, CWnd)
	//{{AFX_MSG_MAP(CPropListView)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_EN_KILLFOCUS( 600 , OnEditKillFocus )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString EPropWnd::s_FitStringToWidth( CString s , int nRequiredWidth , CDC* pDC )
{
	while( true )
	{
		int nTextWidth = pDC->GetTextExtent(s).cx;

		if( nTextWidth <= nRequiredWidth )
		{
			break;
		}

		int n = s.GetLength();

		if( n>=4 )
		{
			s = s.Left( n-4 );	//chop away 4
			s += "...";						//then add "..."
		}
		else
		{
			s.Empty();

			if( n==1 )	//there was one character in string, and it was too big!
			{
				break;
			}

			for( int i=0 ; i<n-1 ; i++ )
			{
				s += ".";
			}
		}
	}

	return s;
}

void EPropWnd::OnEditKillFocus()
{
	if( m_bApplyOnKillFocus )
	{
		OnDoPropApply();
	}

	if( m_bCloseOnKillFocus )
	{
		OnDoPropClose();
	}

	m_bApplyOnKillFocus = true;
	m_bCloseOnKillFocus = true;
}


EPropWnd::EPropWnd()
{
	m_cPane = ::GetSysColor( COLOR_3DFACE    );
	m_cLigh = ::GetSysColor( COLOR_3DHILIGHT );
	m_cDark = ::GetSysColor( COLOR_3DSHADOW  );
	m_cOuts = m_cPane - 0x505050;

	m_PenLigh.CreatePen( PS_SOLID , 0 , m_cLigh );
	m_PenDark.CreatePen( PS_SOLID , 0 , m_cDark );

	m_pChangeListener = NULL;

	m_pActiveProperty = NULL;
	m_nFontHeight = 13;

	m_Font.DeleteObject();
	m_Font.CreateFont( m_nFontHeight , 0, 0, 0, FW_MEDIUM, FALSE,	FALSE,
		0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH , "tahoma" );

	m_nEdgeWidth  = 1;

	m_bApplyOnKillFocus = true;
	m_bCloseOnKillFocus = true;

	m_pCommentPane = NULL;
}

EPropWnd::~EPropWnd()
{

}


void EPropWnd::GetIDRange( int& nID_PROPERTY_RANGE_BEG , int& nID_PROPERTY_RANGE_END )
{
	nID_PROPERTY_RANGE_BEG = 600;
	nID_PROPERTY_RANGE_END = 700;
}

void EPropWnd::PropertyChanged()
{
	NotifyPropertyChanged();
}

void EPropWnd::OnDoPropApply()
{
	if( m_pActiveProperty != NULL )
	{
		if( m_pActiveProperty->IsEnabled() )
		{
			bool bChanged = m_pActiveProperty->OnPropApply();

			if( bChanged )
			{
				if( m_pActiveProperty->m_pParentHost!=NULL )
				{
					m_pActiveProperty->m_pParentHost->PropertyChanging( m_pActiveProperty->m_pProperty , NULL );
				}

				NotifyPropertyChanged();
			}

			Invalidate();
		}
	}
}

void EPropWnd::OnDoPropClose()
{
//	if( m_pActiveProperty != NULL )
//	{
//		m_pActiveProperty->OnPropClose();
//		m_pActiveProperty = NULL;
		SetActiveProperty(NULL);
//		Invalidate();
//	}
}

int EPropWnd::GetFontHeight()
{
	return m_nFontHeight;
}

COLORREF EPropWnd::GetColorPaneKey()
{
	return m_cPane;
}
COLORREF EPropWnd::GetColorPaneVal()
{
	return RGB(255,255,255);
}
COLORREF EPropWnd::GetColorPaneKeyActive()
{
	return m_cPane - 0x202020;
}
COLORREF EPropWnd::GetColorPaneValActive()
{
	return RGB(255,255,255);	//m_cPane - 0x202020;
}

CFont* EPropWnd::GetFont()
{
	return &m_Font;
}


void EPropWnd::NotifyPropertyChanged()
{
	if( m_pChangeListener != NULL )
	{
		// maybe change propertylist as property changes, combo-choises may add/remove properties from list??

		//RefreshHostList();	//this was enabled again to provide change in gui in case of combobox change. It was once disabled, but as for now i cant remember why..?
								//disabled again, because tab was set out of order..

		// SetPropertyHost(m_pPropertyHost);
		m_pChangeListener->PropertyChanged();
	}

//	Invalidate();
}

void EPropWnd::OnSize(UINT nType, int cx, int cy) 
{
	cy -= 20;

	CWnd::OnSize(nType, cx, cy);

	SetScrollPage();
}


void EPropWnd::SetScrollPage()
{
	CSize PageSize = GetScrollPageSize();

	if( PageSize.cx==0 && PageSize.cy==0 )
	{
		SetScrollPos ( SB_HORZ , 0     );
		SetScrollPos ( SB_VERT , 0     );
		ShowScrollBar( SB_BOTH , FALSE );
	}
	else
	{
		CRect wr;
		GetWindowRect(&wr);
		CSize ClientSize = wr.Size();

		bool bEnableH = false;
		bool bEnableV = false;

		if( PageSize.cx > ClientSize.cx )
		{
			ClientSize.cy -= GetSystemMetrics(SM_CYHSCROLL);
			bEnableH = true;
		}

		if( PageSize.cy > ClientSize.cy )
		{
			ClientSize.cx -= GetSystemMetrics(SM_CXVSCROLL);
			bEnableV = true;

			if( bEnableH == false )
			{
				if( PageSize.cx > ClientSize.cx )
				{
					ClientSize.cy -= GetSystemMetrics(SM_CYHSCROLL);
					bEnableH = true;
				}
			}
		}

		SCROLLINFO si;
		si.cbSize = sizeof(si);
		si.fMask  = SIF_PAGE | SIF_POS | SIF_RANGE;

		if( bEnableH )
		{
			si.nPage  = ClientSize.cx;			//size of scrolltab
			si.nMin   = 0;
			si.nMax   = PageSize.cx-1;
			si.nPos   = GetScrollPos(SB_HORZ);
			ShowScrollBar( SB_HORZ , TRUE );
			SetScrollInfo( SB_HORZ , &si );
		}
		else
		{
			ShowScrollBar( SB_HORZ , FALSE );
			SetScrollPos( SB_HORZ , 0 );
		}

		if( bEnableV )
		{
			si.nPage  = ClientSize.cy;			//size of scrolltab
			si.nMin   = 0;
			si.nMax   = PageSize.cy-1;
			si.nPos   = GetScrollPos(SB_VERT);
			ShowScrollBar( SB_VERT , TRUE );
			SetScrollInfo( SB_VERT , &si );
		}
		else
		{
			ShowScrollBar( SB_VERT , FALSE );
			SetScrollPos( SB_VERT , 0 );
		}

	}
}


void EPropWnd::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	int nNewPos = -1;
	int sp = GetScrollPos(SB_HORZ);

	if( nSBCode==SB_THUMBPOSITION || nSBCode==SB_THUMBTRACK )
	{
		nNewPos = nPos;
	}
	else if( nSBCode==SB_LINELEFT )
	{
		sp -= 5;
		nNewPos = sp;
	}
	else if( nSBCode==SB_LINERIGHT )
	{
		sp+=5;
		nNewPos = sp;
	}
	else if( nSBCode==SB_PAGELEFT )
	{
		sp-=20;
		nNewPos = sp;
	}
	else if( nSBCode==SB_PAGERIGHT )
	{
		sp+=20;
		nNewPos = sp;
	}
	
	if( nNewPos >= 0 )
	{
		SetScrollPos( SB_HORZ , nNewPos );
		Invalidate();
	}
}


void EPropWnd::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	int nNewPos = -1;
	int sp = GetScrollPos(SB_VERT);

	if( nSBCode==SB_THUMBPOSITION || nSBCode==SB_THUMBTRACK )
	{
		nNewPos = nPos;
	}
	else if( nSBCode==SB_LINEUP )
	{
		sp -= 5;
		nNewPos = sp;
	}
	else if( nSBCode==SB_LINEDOWN )
	{
		sp+=5;
		nNewPos = sp;
	}
	else if( nSBCode==SB_PAGEUP )
	{
		sp-=20;
		nNewPos = sp;
	}
	else if( nSBCode==SB_PAGEDOWN )
	{
		sp+=20;
		nNewPos = sp;
	}

	if( nNewPos >= 0 )
	{
		SetScrollPos( SB_VERT , nNewPos );
		Invalidate();
	}
}

void EPropWnd::DrawFrame( CDC* pDC , const CRect& r , bool bRaised , int nColor )
{
	CRect rect;

	if( bRaised )
	{
		pDC->SelectObject( &m_PenLigh );
	}
	else
	{
		pDC->SelectObject( &m_PenDark );
	}

	pDC->MoveTo( r.left  , r.bottom-1 );
	pDC->LineTo( r.left  , r.top );
	pDC->LineTo( r.right-1 , r.top );

	if( bRaised )
	{
		pDC->SelectObject( &m_PenDark );
	}
	else
	{
		pDC->SelectObject( &m_PenLigh );
	}

	pDC->LineTo( r.right-1 , r.bottom-1 );
	pDC->LineTo( r.left , r.bottom-1 );

	if( nColor != -1 )
	{
		rect = r;
		rect.DeflateRect(m_nEdgeWidth,m_nEdgeWidth);
		pDC->FillSolidRect( &rect , nColor );
	}
}

void EPropWnd::DrawNipple( CDC* pDC , int x , int y , bool bRaised )
{
	if( bRaised )
	{
		pDC->FillSolidRect( x+1 , y+1 , 2 , 2 , m_cDark );
		pDC->FillSolidRect( x   , y   , 2 , 2 , m_cLigh );
	}
	else
	{
		pDC->FillSolidRect( x+1 , y+1 , 2 , 2 , m_cLigh );
		pDC->FillSolidRect( x   , y   , 2 , 2 , m_cDark );
	}
}

void EPropWnd::SetActiveProperty( EProperty* pNewActiveProperty )
{
	if( pNewActiveProperty != m_pActiveProperty )
	{
		//
		// close old active (apply and close)
		//

		bool bChanged = false;

		if( m_pActiveProperty != NULL )
		{
			m_pActiveProperty->OnPropClose();	//causes killfocus on properties with cedit control!
		}

		//
		// set and activate
		//

		m_pActiveProperty = pNewActiveProperty;

		if( m_pActiveProperty != NULL )
		{
			m_pActiveProperty->OnPropActivate(this);
		}

		if(bChanged)
		{
			NotifyPropertyChanged();
		}

		Invalidate();								//only update this view (selection changed)

		if( m_pCommentPane != NULL )
		{
			m_pCommentPane->Invalidate();
		}

	}
}

CSize EPropWnd::GetScrollPageSize()
{
	return CSize(100,100);
}

BOOL EPropWnd::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	int nBeg;
	int nEnd;
	GetIDRange(nBeg,nEnd);

//	TRACE("PropView wParam=%d lParam=%d!\n" , wParam , lParam );

	int nCommandID           = LOWORD(wParam);	//command of menu, control or accelerator
	int nNotificationMessage = HIWORD(wParam);	//notification message if this is from a control

	bool bMessageIsFromAccelerator = (HIWORD(wParam)==1);
	bool bMessageIsFromMenu        = (HIWORD(wParam)==0);
	bool bMessageFromControl       = (bMessageIsFromAccelerator==false) && (bMessageIsFromMenu==false);

	if( bMessageFromControl )
	{
		int nControlThatSendTheMessage = lParam;
	}

	if( nNotificationMessage==0 )
	{
		if( nBeg <= nCommandID && nCommandID <= nEnd )
		{
			if( m_pActiveProperty != NULL )
			{
				bool bChanged = m_pActiveProperty->OnCommand(this,wParam,lParam);

				if( bChanged )
				{
					NotifyPropertyChanged();
				}

				Invalidate();

			}

			return TRUE;
		}
	}

	return CWnd::OnCommand(wParam, lParam);
}
