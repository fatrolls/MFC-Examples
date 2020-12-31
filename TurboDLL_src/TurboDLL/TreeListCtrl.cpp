// TreeListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TreeListDC.h"
#include "TreeListHeaderCtrl.h"
#include "TreeListTipCtrl.h"
#include "TreeListStaticCtrl.h"
#include "TreeListEditCtrl.h"
#include "TreeListComboCtrl.h"
#include "TLCDragWnd.h"
#include "TLCDropWnd.h"
#include "TreeListCtrl.h"
#include "TreeListResource.h"
#include "TreeListItem.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrl
IMPLEMENT_DYNCREATE(CTreeListCtrl, CWnd)

CTreeListCtrl::CTreeListCtrl() : 
	m_nItemHeight( 0 ),
	m_dwStyle( 0 ),
	m_dwState( TLS_OFFSCREENBUFFER ),
	m_pRootItem( NULL ),
	m_iSelCol( -1 ),
	m_pFocusItem( NULL ),
	m_pTargetItem( NULL ),
	m_pHoverItem( NULL ),
	m_iHoverItem( -1 ),
	m_iModifyCol( -1 ),
	m_pModifyItem( NULL ),
	m_pUpdateItem( NULL ),
	m_hButton( NULL ),
	m_hCheck( NULL ),
	m_hLock( NULL ),
	m_hDrop( NULL ),
	m_hStop( NULL ),
	m_pImageList( NULL ),
	m_pDragWnd( NULL ),
	m_pDropWnd( NULL ),
	m_pTargetWnd( NULL )
{
	// construct

	// create windows class
	WNDCLASS wndclass;
	HINSTANCE hInst = AfxGetInstanceHandle();
	CTreeListResource	TreeListResource;

	if( !::GetClassInfo(hInst, TREELISTCTRL_CLASSNAME, &wndclass) )
	{
        wndclass.style			= CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
		wndclass.lpfnWndProc	= ::DefWindowProc;
		wndclass.cbClsExtra		= 0;
		wndclass.cbWndExtra		= 0;
		wndclass.hInstance		= hInst;
		wndclass.hIcon			= NULL;
		wndclass.hCursor		= AfxGetApp()->LoadStandardCursor( IDC_ARROW);
		wndclass.hbrBackground	= (HBRUSH)COLOR_WINDOW;
		wndclass.lpszMenuName	= NULL;
		wndclass.lpszClassName	= TREELISTCTRL_CLASSNAME;

		if (!AfxRegisterClass(&wndclass))
			AfxThrowResourceException();
	}

	// back ground colors of normal status
	m_crBkColor				= 0xFFFFE0;				
	m_crBkColor_0			= 0xFCFCFC;				
	m_crBkColor_1			= 0xF0F0F0;				
	m_crBkColor_2			= 0xF8F8F8;				

	// back ground colors of disable status
	m_crBkDisable			= 0xC0C080;				
	m_crBkDisable_0			= 0xCCCCCC;				
	m_crBkDisable_1			= 0xC0C0C0;				
	m_crBkDisable_2			= 0xC8C8C8;				

	// back ground colors of selected item
	m_crBkSelected			= 0xC08080;				
	m_crBkSelectedRow		= 0xA00000;				
	m_crBkSelectedColumn	= 0xD00000;				
	m_crBkSelectedNoFocus	= 0xD0A0A0;				

	// text colors
	m_crTextSelected		= 0xE8E8E8;				
	m_crTextSelectedRow		= 0xF0F0F0;				
	m_crTextSelectedColumn	= 0xFFFFFF;				
	m_crTextSelectedNoFocus	= 0xE0E0E0;				

	// normal text color
	m_crText				= 0x000000;				
	m_crTextHover			= 0x00FF00;				

	// grid color
	m_crGrid				= 0xD0D0D0;				
	m_crTreeLine			= 0x808080;				

	m_Palette.CreateStockObject( DEFAULT_PALETTE );
	m_Font.CreateStockObject( SYSTEM_FIXED_FONT );

	m_hButton	= AfxGetApp()->LoadCursor( IDC_CURSOR_BUTTON );
	m_hCheck	= AfxGetApp()->LoadCursor( IDC_CURSOR_CHECK );
	m_hLock		= AfxGetApp()->LoadCursor( IDC_CURSOR_LOCK );

	m_hDrop		= AfxGetApp()->LoadCursor( IDC_CURSOR_DROP );
	m_hStop		= AfxGetApp()->LoadCursor( IDC_CURSOR_STOP );
	m_hArrow	= AfxGetApp()->LoadStandardCursor( IDC_ARROW );

	m_pRootItem = new CTreeListItem( 1 );
	m_pRootItem->Expand();
}

CTreeListCtrl::~CTreeListCtrl()
{
	// deconstruct
	m_wndHeader.DestroyWindow();
	m_wndTip.DestroyWindow();

	if( m_Palette.m_hObject != NULL )
		m_Palette.DeleteObject();

	if( m_Font.m_hObject != NULL )
		m_Font.DeleteObject();

	if( m_hButton != NULL )
		DestroyCursor( m_hButton );

	if( m_hCheck != NULL )
		DestroyCursor( m_hCheck );

	if( m_hLock != NULL )
		DestroyCursor( m_hLock );

	if( m_hDrop != NULL )
		DestroyCursor( m_hDrop );

	if( m_hStop != NULL )
		DestroyCursor( m_hStop );

	if( m_hArrow != NULL )
		DestroyCursor( m_hArrow );

	while( m_arColumns.GetSize() > 0 )
	{
		CTreeListColumnInfo* pColumnInfo;
		int nIndex;
		
		nIndex = m_arColumns.GetUpperBound();
		pColumnInfo = (CTreeListColumnInfo*) m_arColumns[nIndex];

		m_arColumns.RemoveAt( nIndex );
		delete pColumnInfo;
	}

	m_bmpBkBitmap.DeleteObject();
	m_bmpBkDisable.DeleteObject();

	m_imgCheck.DeleteImageList();
	m_imgLock.DeleteImageList();
	m_imgTree.DeleteImageList();

	delete m_pRootItem;
}

BEGIN_MESSAGE_MAP(CTreeListCtrl, CWnd)
	//{{AFX_MSG_MAP(CTreeListCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_ENABLE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrl message handler
BOOL CTreeListCtrl::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	// create control
	SetState( TLS_SUBCLASSFROMCREATE );
	DWORD dwExStyle = 0;

	if( dwStyle&WS_BORDER )
	{
		dwStyle &= ~WS_BORDER;
		dwExStyle |= WS_EX_CLIENTEDGE;
	}

	if( !CWnd::CreateEx( dwExStyle, TREELISTCTRL_CLASSNAME, NULL, dwStyle, rect, pParentWnd, nID ) )
		return FALSE;

	if( !Create() )
		return FALSE;

	return TRUE;
}

BOOL CTreeListCtrl::Create()
{
	// create control
	CRect Rect( 0, 0, 0, 0);

	if( !m_wndHeader.Create( 0, Rect, this, 0 ) )
		return FALSE;

	if( !m_wndTip.Create( this ) )
		return FALSE;

	DWORD dwStyle;

	dwStyle = WS_BORDER | WS_CHILD | SS_NOTIFY | SS_CENTERIMAGE;
	if( !m_wndStatic.Create( _T("123"), dwStyle, Rect, this, 0 ) )
		return FALSE;

	dwStyle = WS_BORDER | WS_CHILD | ES_CENTER | ES_AUTOHSCROLL;

	if( !m_wndEdit.Create( dwStyle, Rect, this, 0 ) )
		return FALSE;

	dwStyle = WS_CHILD | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | CBS_NOINTEGRALHEIGHT;

	if( !m_wndCombo.Create( dwStyle, Rect, this, 0 ) )
		return FALSE;

	if( !m_bmpBkBitmap.LoadBitmap( IDB_TREELIST_BITMAP ) )
		return FALSE;

	if( !m_bmpBkDisable.LoadBitmap( IDB_TREELIST_DISABLE ) )
		return FALSE;

	if( !m_imgCheck.Create( IDB_TREELIST_CHECK, 16, 3, 0xFF00FF ) )
		return FALSE;

	if( !m_imgLock.Create( IDB_TREELIST_LOCK, 8, 3, 0xFF00FF ) )
		return FALSE;

	if( !m_imgTree.Create( IDB_TREELIST_TREE, 16, 3, 0xFFFFFF ) )
		return FALSE;

	m_pImageList = &m_imgTree;

	SetFont();
	SetItemHeight();
	
	m_wndHeader.SetHeaderFont();
	m_wndHeader.SetHeaderHeight();
	m_wndTip.SetFont();
	
	m_wndStatic.SetFont( GetFont() );
	m_wndEdit.SetFont( GetFont() );
	m_wndCombo.SetFont( GetFont() );

	Layout();

	return TRUE;
}

void CTreeListCtrl::PreSubclassWindow() 
{
	// pre subclass window
	CWnd::PreSubclassWindow();

	if( !GetState( TLS_SUBCLASSFROMCREATE ) )
	{
		if( !Create() )
		{
			AfxThrowMemoryException();
			return;
		}
	}

	return;
}

void CTreeListCtrl::OnDestroy() 
{
	CWnd::OnDestroy();
	
	m_arShows.RemoveAll();
	m_arSorts.RemoveAll();

	DeleteItem( TLI_ROOT );
}

void CTreeListCtrl::SetAllScroll()
{
	// set all scroll bars
	CRect rcPreClient;
	GetWindowRect( &rcPreClient );
	rcPreClient.DeflateRect( 1, 1 );

	int cx = ::GetSystemMetrics( SM_CXVSCROLL );
	int cy = ::GetSystemMetrics( SM_CYHSCROLL );

	SCROLLINFO siv;
	SCROLLINFO sih;

	GetScrollInfo( SB_VERT, &siv, SIF_POS | SIF_RANGE );
	GetScrollInfo( SB_HORZ, &sih, SIF_POS | SIF_RANGE );

	BOOL bHorzScroll = FALSE;
	BOOL bVertScroll = FALSE;

	if( rcPreClient.Width() < GetWidth() )
	{
		bHorzScroll = TRUE;

		if( rcPreClient.Height() - cy < m_wndHeader.GetHeaderHeight() + GetVisibleCount() * GetItemHeight() )
			bVertScroll = TRUE;
	}
	else if( rcPreClient.Height() < m_wndHeader.GetHeaderHeight() + GetVisibleCount() * GetItemHeight() )
	{
		bVertScroll = TRUE;

		if( rcPreClient.Width() - cx < GetWidth() )
			bHorzScroll = TRUE;
	}

	if( sih.nPos != sih.nMin )
		bHorzScroll = TRUE;

	if( siv.nPos != siv.nMin )
		bVertScroll = TRUE;

	if( bHorzScroll )
	{
		if( rcPreClient.Width() > cx )
			rcPreClient.right -= cx;
		else
			rcPreClient.right = rcPreClient.left;
	}

	if( bVertScroll )
	{
		if( rcPreClient.Height() > cy )
			rcPreClient.bottom -= cy;
		else
			rcPreClient.bottom = rcPreClient.top;
	}

	SetHorzScroll( &rcPreClient );
	SetVertScroll( &rcPreClient );
}

void CTreeListCtrl::SetHorzScroll( CRect* pPreClient )
{
	// set horizonal scroll
	SCROLLINFO si;
	GetScrollInfo( SB_HORZ, &si, SIF_ALL );

	if( pPreClient->Width() < GetWidth() )
	{
		si.cbSize	= sizeof( SCROLLINFO );
		si.nMin		= 0;
		si.nMax		= GetWidth() - 1;
		si.nPage	= pPreClient->Width();
		si.nPos		= si.nPos;
		si.fMask	=  SIF_PAGE | SIF_RANGE | SIF_POS;
		if( si.nPos > si.nMax - (int)si.nPage )
			si.nPos = si.nMax - (int)si.nPage;
	}
	else
	{
		si.cbSize	= sizeof( SCROLLINFO );
		si.nMin		= 0;
		si.nMax		= 0;
		si.nPage	= 0;
		si.nPos		= 0;
		si.fMask	=  SIF_PAGE | SIF_RANGE | SIF_POS;
	}
	
	SetScrollInfo( SB_HORZ, &si, TRUE );
}

void CTreeListCtrl::SetVertScroll( CRect* pPreClient )
{
	// set vertical scroll
	SCROLLINFO si;
	GetScrollInfo( SB_VERT, &si, SIF_ALL );

	if( pPreClient->Height() < m_wndHeader.GetHeaderHeight() + GetVisibleCount() * GetItemHeight() || si.nPos != si.nMin )
	{
		int nShowRows	=	m_rcTreeList.Height() / GetItemHeight();

		si.cbSize	= sizeof( SCROLLINFO );
		si.nMin		= 0;
		si.nMax		= GetVisibleCount() - 1;
		si.nPos		= si.nPos;
		si.nPage	= max( nShowRows, 1 ); // min( pPreClient->Height()/m_nRowHeight, si.nMax -si.nPos );
		si.fMask	=  SIF_PAGE | SIF_RANGE | SIF_POS;
		if( si.nPos > si.nMax )
			si.nPos = si.nMax;
	}
	else
	{
		si.cbSize	= sizeof( SCROLLINFO );
		si.nMin		= 0;
		si.nMax		= 0;
		si.nPage	= 0;
		si.nPos		= 0;
		si.fMask	=  SIF_PAGE | SIF_RANGE | SIF_POS;
	}

	SetScrollInfo( SB_VERT, &si, TRUE );
}


void CTreeListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// on horizonal scroll
	SCROLLINFO si;
	GetScrollInfo( SB_HORZ, &si, SIF_ALL );

	switch( nSBCode )
	{
	case SB_LINEUP:
		if( si.nPos > si.nMin )
			si.nPos--;
		break;

	case SB_LINEDOWN:
		if( si.nPos <= si.nMax - (int)si.nPage )
			si.nPos++;
		break;

	case SB_PAGEUP:
		si.nPos -= si.nPage;
		if( si.nPos < si.nMin )
			si.nPos = si.nMin;
		break;

	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		if( si.nPos > si.nMax )
			si.nPos = si.nMax;
		break;

	case SB_TOP:
		si.nPos = si.nMin;
		break;

	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;

	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;

	default:
		break;
	}
	
	SetScrollPos( SB_HORZ, si.nPos );
	m_wndHeader.RedrawWindow();
	RedrawWindow();
}

void CTreeListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// on vertival scroll
	SCROLLINFO si;
	GetScrollInfo( SB_VERT, &si, SIF_ALL );

	switch( nSBCode )
	{
	case SB_LINEUP:
		if( si.nPos > si.nMin )
			si.nPos--;
		break;

	case SB_LINEDOWN:
		if( si.nPos <= si.nMax - (int)si.nPage )
			si.nPos++;;
		break;

	case SB_PAGEUP:
		si.nPos -= si.nPage;
		if( si.nPos < si.nMin )
			si.nPos = si.nMin;
		break;

	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		if( si.nPos > si.nMax )
			si.nPos = si.nMax;
		break;

	case SB_TOP:
		si.nPos = si.nMin;
		break;

	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;

	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;

	default:
		break;
	}

	if( si.nPos == si.nMin )
	{
		if(  si.nMax-si.nMin+1 <= m_rcClient.Height()/m_nItemHeight )
		{
			Layout();
		}
	}

	SetScrollPos( SB_VERT, si.nPos );

	Invalidate();
}

LRESULT CTreeListCtrl::Notify( DWORD dwMessage, CTreeListItem* pItem, int iCol )
{
	// notify a message
	NMTREELIST nm;
	nm.hdr.hwndFrom = GetSafeHwnd();
	nm.hdr.idFrom	= GetDlgCtrlID();
	nm.hdr.code		= dwMessage;

	nm.pItem	= pItem;
	nm.iCol		= iCol;

	if( nm.iCol == -1 )
		nm.iCol = 0;

	CWnd* pWnd		= GetParent();
	LRESULT lResult	= 0;

	if( pWnd == NULL )
		lResult = 0;
	else
		lResult = pWnd->SendMessage( WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&nm );

	return lResult;	
}

LRESULT CTreeListCtrl::NotifyDrop( DWORD dwMessage, CTreeListCtrl* pSource , CTreeListItem* pItem )
{
	// notify drop messages
	NMTREELISTDROP nm;
	nm.hdr.hwndFrom	= GetSafeHwnd();
	nm.hdr.idFrom	= GetDlgCtrlID();
	nm.hdr.code		= dwMessage;

	nm.pSource	= pSource;
	nm.pItem	= pItem;

	CWnd* pWnd		= GetParent();
	LRESULT lResult = 0;

	if( pWnd == NULL )
		lResult = 0;
	else
		lResult = pWnd->SendMessage( WM_NOTIFY, GetDlgCtrlID(), (LPARAM)&nm );

	return lResult;	
}

void CTreeListCtrl::Layout()
{
	// layout size
	if( !IsWindow( m_wndHeader.GetSafeHwnd() ) )
		return;

	if( !IsWindow( m_wndTip.GetSafeHwnd() ) )
		return;

	m_wndTip.Hide();

	SetAllScroll();

	GetClientRect( &m_rcClient );
	m_rcHeader		= m_rcClient;
	m_rcTreeList	= m_rcClient;

	m_wndHeader.SendMessage( HDM_LAYOUT, (WPARAM)0, (LPARAM)&m_rcHeader );

	if( m_rcHeader.Height() == 0 )
	{
		m_rcTreeList = m_rcClient;
	}
	else if( m_rcHeader.Height() == m_rcClient.Height() )
	{
		m_rcTreeList.top	= m_rcHeader.bottom;
		m_rcTreeList.bottom = m_rcHeader.bottom;
	}
	else
	{
		m_rcTreeList.top	= m_rcHeader.bottom;
	}

	SetAllScroll();

	return;
}
int CTreeListCtrl::GetWidth()
{
	// retrieve total width
	int nWidth = 0;

	for( int iShow=0; iShow<m_arShows.GetSize(); iShow++ )
	{
		CTreeListColumnInfo* pColumnInfo;
		int iCol;

		iCol = m_arShows[iShow];
		pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];

		nWidth += pColumnInfo->m_nWidth;
	}

	return nWidth;
}

int CTreeListCtrl::GetHeight()
{
	// retrieve total height
	return GetItemHeight() * GetVisibleCount();
}

int CTreeListCtrl::GetColumns()
{
	// retrieve total number of columns
	return m_arColumns.GetSize();
}

int CTreeListCtrl::GetCount()
{
	// retrieve a count of the items in treelist control
	return m_pRootItem->m_nChild - 1;
}

CImageList* CTreeListCtrl::GetImageList()
{
	// retrieve global point of image list
	return m_pImageList;
}

void CTreeListCtrl::SetImageList( CImageList* pImageList )
{
	// set global point of image list
	ASSERT_VALID( pImageList );
	m_pImageList = pImageList;

	Invalidate();
}

CTreeListItem* CTreeListCtrl::GetNextItem( CTreeListItem* pItem, UINT nCode )
{
	// retrieve next item specified by pItem
	CTreeListItem* pRetItem = NULL;

	switch( nCode )
	{
	case TLGN_ROOT:				pRetItem = GetRootItem();					break;
	case TLGN_NEXT:				pRetItem = GetNextSiblingItem( pItem );		break;
	case TLGN_PREVIOUS:			pRetItem = GetPrevSiblingItem( pItem );		break;
	case TLGN_PARENT:			pRetItem = GetParentItem( pItem );			break;
	case TLGN_CHILD:			pRetItem = GetChildItem( pItem );			break;
	case TLGN_FIRSTVISIBLE:		pRetItem = GetFirstVisibleItem();			break;
	case TLGN_NEXTVISIBLE:		pRetItem = GetNextVisibleItem( pItem );		break;
	case TLGN_PREVIOUSVISIBLE:	pRetItem = GetPrevVisibleItem( pItem );		break;
	case TLGN_DROPHILITE:		pRetItem = NULL;							break;
	case TLGN_CARET:			pRetItem = GetSelectedItem();				break;
	case TLGN_NEXTSELECT:		pRetItem = GetNextSelectedItem( pItem );	break;
	default:					pRetItem = NULL;							break;
	}

	return pRetItem;
}

BOOL CTreeListCtrl::ItemHasChildren( CTreeListItem* pItem )
{
	// determine whether the treelist item specified by pItem has a child item
	ASSERT( pItem != NULL );

	if( pItem->m_pChild == NULL )
		return FALSE;

	return TRUE;
}

CTreeListItem* CTreeListCtrl::GetChildItem( CTreeListItem* pItem )
{
	// retrieve first child item specified by pItem
	ASSERT( pItem != NULL );
	return pItem->m_pChild;
}

CTreeListItem* CTreeListCtrl::GetNextSiblingItem( CTreeListItem* pItem )
{
	// retrieve next sibling item specified by pItem
	ASSERT( pItem != NULL );
	return pItem->m_pNext;
}

CTreeListItem* CTreeListCtrl::GetPrevSiblingItem( CTreeListItem* pItem )
{
	// retrieve prev sibling item specified by pItem
	ASSERT( pItem != NULL );
	return pItem->m_pPrev;
}

CTreeListItem* CTreeListCtrl::GetParentItem( CTreeListItem* pItem )
{
	// retrieve parent item specified by pItem
	ASSERT( pItem != NULL );
	if( pItem->m_pParent == m_pRootItem )
		return NULL;
	else
		return pItem->m_pParent;
}

CTreeListItem* CTreeListCtrl::GetFirstVisibleItem()
{
	// retrieve first visible item of treelist
	if( m_pRootItem->m_pChild != NULL )
		return m_pRootItem->m_pChild;

	return NULL;
}

CTreeListItem* CTreeListCtrl::GetNextVisibleItem( CTreeListItem* pItem )
{
	// retrieve next visible item of treelist
	ASSERT( pItem != NULL );

	return GetNextVisibleItem( pItem, TRUE );
}

CTreeListItem* CTreeListCtrl::GetNextVisibleItem( CTreeListItem* pItem, BOOL bChild )
{
	// retrieve next visible item of treelist
	ASSERT( pItem != NULL );

	if( pItem->GetState()&TLIS_EXPANDED )
		if( bChild && pItem->m_pChild != NULL )
			return pItem->m_pChild;

	if( pItem->m_pNext != NULL )
		return pItem->m_pNext;

	if( pItem != m_pRootItem )
	{
		pItem = pItem->m_pParent;
		if( pItem != m_pRootItem )
			return GetNextVisibleItem( pItem, FALSE );
	}

	return NULL;
}

CTreeListItem* CTreeListCtrl::GetPrevVisibleItem( CTreeListItem* pItem )
{
	// retrieve previous visible item of treelist
	ASSERT( pItem != NULL );

	return GetPrevVisibleItem( pItem, TRUE );
}

CTreeListItem* CTreeListCtrl::GetPrevVisibleItem( CTreeListItem* pItem, BOOL bChild )
{
	// retrieve previous visible item of treelist
	ASSERT( pItem != NULL );

	if( pItem->m_pPrev != NULL )
	{
		pItem = pItem->m_pPrev;
		if( pItem->GetState()&TLIS_EXPANDED && pItem->m_pChild != NULL )
		{
			pItem = GetLastVisibleItem( pItem );
		}
		return pItem;
	}

	pItem = pItem->m_pParent;
	if( pItem != m_pRootItem )
		return pItem;

	return FALSE;
}

CTreeListItem* CTreeListCtrl::GetLastVisibleItem( CTreeListItem* pItem )
{
	// retrieve last visible child item of item specified by pItem
	ASSERT( pItem != NULL && pItem->m_pChild != NULL );

	CTreeListItem* pChild;
	pChild = pItem->m_pChild;

	while( pChild->m_pNext != NULL )
	{
		pChild = pChild->m_pNext;
	}

	if( pChild->GetState()&TLIS_EXPANDED && pChild->m_pChild != NULL  )
		return GetLastVisibleItem( pChild );
	else
		return pChild;
}


CTreeListItem* CTreeListCtrl::GetSelectedItem()
{
	// always retrieve first selected item
	POSITION pos = GetFirstSelectedItemPosition();
	return GetNextSelectedItem( pos );
}

CTreeListItem* CTreeListCtrl::GetNextSelectedItem( CTreeListItem* pItem )
{
	// retrieve next selected item specified by pItem
	if( pItem == NULL )
		return NULL;

	if( pItem == m_pRootItem && m_arSelects.GetSize() > 0 )
		return (CTreeListItem*)m_arSelects[0];

	for( int iSel = 0; iSel<m_arSelects.GetSize()-1; iSel++ )
	{
		if( pItem == (CTreeListItem*)m_arSelects[iSel] )
			return (CTreeListItem*)m_arSelects[iSel+1];
	}

	return NULL;
}

CTreeListItem* CTreeListCtrl::GetRootItem()
{
	// retrieve root item of treelist control
	return m_pRootItem->m_pChild;
}

DWORD CTreeListCtrl::GetItemState( CTreeListItem* pItem, DWORD nStateMask )
{
	// retrieve status of item specified by pItem
	ASSERT( pItem != NULL );
	return pItem->GetState( nStateMask );
}

void CTreeListCtrl::SetItemState( CTreeListItem* pItem, DWORD dwAddState, DWORD dwRemoveState )
{
	// set status of item specified by pItem
	ASSERT( pItem != NULL );
	pItem->SetState( dwAddState, dwRemoveState );
	Invalidate();
}

void CTreeListCtrl::GetItemImage( CTreeListItem* pItem, int& nImage, int& nExpandImage, int& nSelectedImage, int& nExpandSelectedImage )
{
	// retrieve images of item specified by pItem
	ASSERT( pItem != NULL );
	pItem->GetImage( nImage, nExpandImage, nSelectedImage, nExpandSelectedImage );
}

void CTreeListCtrl::SetItemImage( CTreeListItem* pItem, int nImage, int nExpandImage, int nSelectedImage, int nExpandSelectedImage )
{
	// set images of item specified by pItem
	ASSERT( pItem != NULL );
	pItem->SetState( TLIS_SHOWTREEIMAGE );
	pItem->SetImage( nImage, nExpandImage, nSelectedImage, nExpandSelectedImage );
	Invalidate();
}	

LPCTSTR	CTreeListCtrl::GetItemText( CTreeListItem* pItem, int nSubItem )
{
	// retrieve text of item specified by pItem
	ASSERT( pItem != NULL );
	return pItem->GetText( nSubItem );
}

BOOL CTreeListCtrl::SetItemText( CTreeListItem* pItem, LPCTSTR lpszText, int nSubItem )
{
	// set text of item specified by pItem
	ASSERT( pItem != NULL );
	BOOL bRet = pItem->SetText( lpszText, nSubItem );
	Invalidate();
	return bRet;
}

DWORD CTreeListCtrl::GetItemData( CTreeListItem* pItem )
{
	// retrieve 32-bit data of item specified by pItem
	ASSERT( pItem != NULL );
	return pItem->GetData();
}

void CTreeListCtrl::SetItemData( CTreeListItem* pItem, DWORD dwData )
{
	// set 32-bit data of item specified by pItem
	ASSERT( pItem != NULL );
	pItem->SetData( dwData );
}

int CTreeListCtrl::GetVisibleCount()
{
	// retrieve the  number of visible items in the treelist control
	return GetVisibleCount( m_pRootItem );
}

int CTreeListCtrl::GetItemHeight()
{
	// retrieve the height of the item
	return m_nItemHeight;
}

int CTreeListCtrl::SetItemHeight( int cyHeight )
{
	// set the height of the item
	int nOldHeight = m_nItemHeight;

	if( cyHeight == -1 )
	{
		ASSERT( m_Font.m_hObject != NULL );

		LOGFONT lf;
		m_Font.GetLogFont( &lf );
	
		if( lf.lfHeight < 0 )
		{
			m_nItemHeight = -lf.lfHeight + 5;
		}
		else if( lf.lfHeight == 0 )
		{
			m_nItemHeight = DEFAULT_HEIGHT;
		}
		else
		{
			m_nItemHeight = lf.lfHeight + 5;
		}
	}
	else
	{
		m_nItemHeight = cyHeight;
	}

	if( m_nItemHeight % 2 == 1 )
		m_nItemHeight ++;

	Invalidate();

	return nOldHeight;
}

COLORREF CTreeListCtrl::GetBkColor( int nColor )
{
	// set background color of treelist control
	COLORREF clr;

	switch( nColor )
	{
	case 0:		clr = m_crBkColor_0;		break;
	case 1:		clr = m_crBkColor_1;		break;
	case 2:		clr = m_crBkColor_2;		break;
	default:	clr = m_crBkColor;		break;
	}

	return clr;
}

COLORREF CTreeListCtrl::SetBkColor( COLORREF clr, int nColor )
{
	// retrieve background color of treelist control
	COLORREF oldclr;

	switch( nColor )
	{
	case 0:		oldclr = m_crBkColor_0;		m_crBkColor_0 = clr;		break;
	case 1:		oldclr = m_crBkColor_1;		m_crBkColor_1 = clr;		break;
	case 2:		oldclr = m_crBkColor_2;		m_crBkColor_2 = clr;		break;
	default:	oldclr = m_crBkColor;		m_crBkColor = clr;		break;
	}

	Invalidate();
	return oldclr;
}

COLORREF CTreeListCtrl::GetTextColor()
{
	// retrieve the color of the text
	return m_crText;
}

COLORREF CTreeListCtrl::SetTextColor( COLORREF clr )
{
	// set the color of the text
	COLORREF oldclr;
	oldclr = m_crText;
	m_crText = clr;

	Invalidate();

	return m_crText;
}

int CTreeListCtrl::GetCheck( CTreeListItem* pItem )
{
	// retrieve an item checked box state
	ASSERT( pItem != NULL );
	return pItem->GetCheck();
}

void CTreeListCtrl::SetCheck( CTreeListItem* pItem, BOOL bCheck )
{
	// set an item checked box state
	ASSERT( pItem != NULL );
	pItem->SetCheck( bCheck );
	
	if( pItem->GetCheck() )
	{
		SetItemChildStatus( pItem, TLIS_CHECKED, TLIS_CHECKED_NULL );
		SetItemParentStatus( pItem, TLIS_CHECKEDMASK );
	}
	else
	{
		SetItemChildStatus( pItem, TLIS_CHECKED_NULL, TLIS_CHECKED );
		SetItemParentStatus( pItem, TLIS_CHECKEDMASK );
	}

	Invalidate();
}

int CTreeListCtrl::GetLock( CTreeListItem* pItem )
{
	// retrieve an item locked box state
	ASSERT( pItem != NULL );
	return pItem->GetLock();
}

void CTreeListCtrl::SetLock( CTreeListItem* pItem, BOOL bLock )
{
	// set an item locked box state
	ASSERT( pItem != NULL );
	pItem->SetLock( bLock );

	if( pItem->GetLock() )
	{
		SetItemChildStatus( pItem, TLIS_LOCKED, TLIS_LOCKED_NULL );
		SetItemParentStatus( pItem, TLIS_LOCKEDMASK );
	}
	else
	{
		SetItemChildStatus( pItem, TLIS_LOCKED_NULL, TLIS_LOCKED );
		SetItemParentStatus( pItem, TLIS_LOCKEDMASK );
	}
	Invalidate();
}

BOOL CTreeListCtrl::GetItemRect( CTreeListItem* pItem, LPRECT lpRect )
{
	// retrieve rect of an item
	int nFirstRow	=	GetScrollPos( SB_VERT );
	int	nShowRows	=	m_rcTreeList.Height() / GetItemHeight() + 1;

	CRect rcItem;
	rcItem.SetRect( 0, 0, GetWidth(), GetItemHeight() );
	rcItem.OffsetRect( m_rcTreeList.left, m_rcTreeList.top );
	rcItem.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

	for( int i = nFirstRow; i<= nFirstRow + nShowRows && i < GetVisibleCount(); i++ )
	{
		CTreeListItem* pShowItem = GetFirstShowItem( i );
		if( pShowItem == pItem )
		{
			lpRect->left	= rcItem.left;
			lpRect->right	= rcItem.right;
			lpRect->top		= rcItem.top;
			lpRect->bottom	= rcItem.bottom;

//			lpRect->top		+= 1;
//			lpRect->bottom	-= 1;

			return TRUE;
		}

		rcItem.OffsetRect( 0, GetItemHeight() );
	}
	return FALSE;
}

BOOL CTreeListCtrl::GetItemRect( CTreeListItem* pItem, int iSubItem, LPRECT lpRect, BOOL bTextOnly )
{
	// retrieve rect of a column of an item
	CRect rcItem;
	
	if( GetItemRect( pItem, rcItem ) )
	{
		int nColPos = 0;
		CTreeListColumnInfo* pColumnInfo;

		for( int iShow = 0; iShow < m_arShows.GetSize(); iShow++, nColPos += pColumnInfo->GetWidth() )
		{
			int iCol;

			iCol = m_arShows[iShow];
			pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];

			if( iCol == iSubItem )
			{
				CRect rcColumn;
				rcColumn.SetRect( 0, rcItem.top, pColumnInfo->GetWidth(), rcItem.bottom );
				rcColumn.OffsetRect( nColPos, 0 );
				rcColumn.OffsetRect( rcItem.left, 0 );

				lpRect->left	= rcColumn.left;
				lpRect->right	= rcColumn.right;
				lpRect->top		= rcColumn.top;
				lpRect->bottom	= rcColumn.bottom;

				if( iCol == 0 && bTextOnly )
				{
					if ( m_dwStyle&TLC_TREELIST )
						return GetItemRectTree( pItem, lpRect );
					else
						return GetItemRectMain( pItem, lpRect );

				}

//				lpRect->left	+= 1;
//				lpRect->right	-= 1;

				return TRUE;
			}
		}
	}
	
	return FALSE;
}	

BOOL CTreeListCtrl::GetItemRectTree( CTreeListItem* pItem, LPRECT lpRect )
{
	int nPerfix = 0;

	// skip perfix and tree line
	nPerfix += TLL_BORDER;
	nPerfix += (pItem->m_nLevel-1) * TLL_WIDTH;

	// skip tree button
	if( m_dwStyle&(TLC_TREELINE|TLC_BUTTON) )
		nPerfix += TLL_WIDTH;

	// skip tree check box
	if( m_dwStyle&TLC_CHECKBOX )
		if( pItem->GetState()&TLIS_SHOWCHECKBOX )
			nPerfix += TLL_WIDTH;

	// skip tree lock box
	if( m_dwStyle&TLC_LOCKBOX )
		if( pItem->GetState()&TLIS_SHOWLOCKBOX )
			nPerfix += TLL_WIDTH/2;

	// skip tree image
	if( m_dwStyle&TLC_IMAGE )
		if( pItem->GetState()&TLIS_SHOWTREEIMAGE )
			nPerfix += TLL_WIDTH;

	// skip gaps between text and image/loc
	if( m_dwStyle&TLC_LOCKBOX || m_dwStyle&TLC_IMAGE )
		nPerfix += 2;

	if( lpRect->left + nPerfix + 2 <= lpRect->right )
	{
		lpRect->left	+= nPerfix;
//		lpRect->left	+= 1;
//		lpRect->right	-= 1;
		return TRUE;
	}
	
	lpRect->left	+= nPerfix;
	return FALSE;
}

BOOL CTreeListCtrl::GetItemRectMain( CTreeListItem* pItem, LPRECT lpRect )
{
	int nPerfix = 0;

	// skip perfix
	nPerfix += TLL_BORDER;

	// skip tree button
	if( m_dwStyle&(TLC_TREELINE|TLC_BUTTON) )
		nPerfix += TLL_WIDTH;

	// skip tree check box
	if( m_dwStyle&TLC_CHECKBOX )
		if( pItem->GetState()&TLIS_SHOWCHECKBOX )
			nPerfix += TLL_WIDTH;

	// skip tree lock box
	if( m_dwStyle&TLC_LOCKBOX )
		if( pItem->GetState()&TLIS_SHOWLOCKBOX )
			nPerfix += TLL_WIDTH/2;

	// skip tree image
	if( m_dwStyle&TLC_IMAGE )
		if( pItem->GetState()&TLIS_SHOWTREEIMAGE )
			nPerfix += TLL_WIDTH;

	// skip gaps between text and image/loc
	if( m_dwStyle&TLC_LOCKBOX || m_dwStyle&TLC_IMAGE )
		nPerfix += 2;

	if( lpRect->left + nPerfix + 2 <= lpRect->right )
	{
		lpRect->left	+= nPerfix;
//		lpRect->left	+= 1;
//		lpRect->right	-= 1;
		return TRUE;
	}
	
	lpRect->left += nPerfix;
	return FALSE;
}

BOOL CTreeListCtrl::EnsureVisible( CTreeListItem* pItem, int iSubItem )
{
	// ensure an item is visible that specified by pItem
	int nItem		=	GetTreeListItem( pItem );
	int nFirstRow	=	GetScrollPos( SB_VERT );
	int nShowRows	=	m_rcTreeList.Height() / GetItemHeight();

	if( nShowRows > 0 )
		nShowRows = nShowRows - 1;

	if( nItem < nFirstRow )
	{
		SetScrollPos( SB_VERT, nItem );
	}
	else
	{
		if( nItem > nFirstRow + nShowRows )
			SetScrollPos( SB_VERT, nItem - nShowRows );
	}

	CRect rcClient;
	GetClientRect( rcClient );
	int	nCurrent	=	GetScrollPos( SB_HORZ );
	int nLeft		=	0;
	int nRight		=	0;
	for( int iShow = 0; iShow < m_arShows.GetSize(); iShow ++ )
	{
		CTreeListColumnInfo* pColumnInfo;
		pColumnInfo = (CTreeListColumnInfo*)m_arColumns[m_arShows[iShow]];

		if( m_arShows[iShow] == iSubItem )
		{
			nRight = pColumnInfo->GetWidth();
			break;
		}
		nLeft += pColumnInfo->GetWidth();
	}
	nRight = nLeft + nRight;

	if( iSubItem == 0 )
	{
		int iLevel		= pItem->m_nLevel - 1;
		CTreeListColumnInfo* pColumnInfo;
		pColumnInfo = (CTreeListColumnInfo*)m_arColumns[0];
		nLeft += TLL_WIDTH * iLevel;
	}

	if( nLeft <= nCurrent )
	{
		SetScrollPos( SB_HORZ, nLeft );
	}
	else
	{
		if( nCurrent + rcClient.Width() < nRight )
		{
			if( nRight-nLeft <= rcClient.Width() )
			{
				SetScrollPos( SB_HORZ, nRight - rcClient.Width() );
			}
			else
			{
				SetScrollPos( SB_HORZ, nLeft );
			}
		}
	}

	Invalidate();
	return TRUE;
}

int	CTreeListCtrl::GetItemCount()
{
	// retrieve count of all items.
	return m_pRootItem->m_nChild - 1;
}

int CTreeListCtrl::GetNextItem( int nItem, int nFlags )
{
	// retrieve next item specified by nItem
	CTreeListItem* pItem = NULL;
	pItem = GetTreeListItem( nItem );

	if( pItem == NULL )
		return -1;

	if( nFlags&TLNI_ABOVE )
		return GetTreeListItem( GetPrevSiblingItem( pItem ) );

	if( nFlags&TLNI_BELOW )
		return GetTreeListItem( GetNextSiblingItem( pItem ) );

	return -1;
}

POSITION CTreeListCtrl::GetFirstSelectedItemPosition()
{
	// retrieve position of selected item
	if( m_arSelects.GetSize() == 0 )
		return NULL;

	POSITION pos = (POSITION)m_pRootItem;
	return pos;
}

CTreeListItem* CTreeListCtrl::GetNextSelectedItem( POSITION& pos )
{
	// retrieve next selected item specified by pItem
	CTreeListItem* pItem;
	
	pItem = GetNextSelectedItem( (CTreeListItem*)pos );
	pos = (POSITION)pItem;
	return pItem;
}

int CTreeListCtrl::GetStringWidth( LPCTSTR lpsz )
{
	// retrieve width of string in pixel
	CPaintDC dc(this);

	CFont* pOldFont = dc.SelectObject( GetFont() );
	CSize sz = dc.GetTextExtent( lpsz, _tcslen(lpsz) );
	dc.SelectObject( pOldFont );

	return sz.cx + 6;
}

DWORD CTreeListCtrl::SetColumnFormat( int nCol, DWORD dwAdd, DWORD dwRemove )
{
	// set column fromat
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	DWORD dwFormat = pColumnInfo->SetFormat( dwAdd, dwRemove );

	Invalidate();

	return dwFormat;
}

DWORD CTreeListCtrl::GetColumnFormat( int nCol, DWORD dwMask )
{
	// retrieve column format
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	return pColumnInfo->GetFormat();
}

DWORD CTreeListCtrl::SetColumnModify( int nCol, DWORD dwModify )
{
	// retrieve column modify
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	return pColumnInfo->SetModify( dwModify );
}

DWORD CTreeListCtrl::GetColumnModify( int nCol )
{
	// retrieve column modify
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	return pColumnInfo->GetModify();
}

int CTreeListCtrl::SetColumnWidth( int nCol, int nWidth, int nMin, int nMax )
{
	// set column width
	if( nWidth == TLSCW_AUTOSIZE || nWidth == TLSCW_AUTOSIZE_USEHEADER )
	{
		// AutoSetWidth();		// all show items
		if( nWidth == TLSCW_AUTOSIZE )
		{
			nWidth = nMin;
		}
		else
		{
			nWidth = GetStringWidth( GetColumnText( nCol ) ) + 4;
		}

		CTreeListItem* pShowItem = GetFirstShowItem( 0 );
		while( pShowItem != NULL )
		{
			ASSERT( pShowItem != NULL );

			int x = 0;
			if( nCol == 0 )
			{
				if( m_dwStyle&TLC_TREELIST )
					x += (pShowItem->m_nLevel-1) * TLL_WIDTH;

				if( m_dwStyle&(TLC_TREELINE|TLC_BUTTON) )
					x += TLL_WIDTH;

				if( m_dwStyle&TLC_CHECKBOX )
					if( pShowItem->GetState()&TLIS_SHOWCHECKBOX )
						x += TLL_WIDTH;

				if( m_dwStyle&TLC_LOCKBOX )
					if( pShowItem->GetState()&TLIS_SHOWLOCKBOX )
						x += TLL_WIDTH/2;

				if( m_dwStyle&TLC_IMAGE )
					if( pShowItem->GetState()&TLIS_SHOWTREEIMAGE )
						x += TLL_WIDTH;

				if( m_dwStyle&TLC_LOCKBOX || m_dwStyle&TLC_IMAGE )
					x += 2;
			}

			x += GetStringWidth( pShowItem->GetText( nCol ) );
			x += 2;

			if( nWidth < x )
				nWidth = x;

			pShowItem = GetNextShowItem( pShowItem );
		}
		return SetColumnWidth( nCol, nWidth, nMin, nMax );
	}
	else if( nWidth == TLSCW_AUTOSIZEV || nWidth == TLSCW_AUTOSIZEV_USEHEADER )
	{
		// AutoSetWidth();		// all visible items
		if( nWidth == TLSCW_AUTOSIZEV )
		{
			nWidth = nMin;
		}
		else
		{
			nWidth = GetStringWidth( GetColumnText( nCol ) ) + 4;
		}

		CTreeListItem* pVisibleItem = GetFirstVisibleItem();
		while( pVisibleItem != NULL )
		{
			ASSERT( pVisibleItem != NULL );
			int x = 0;
			if( nCol == 0 )
			{
				if( m_dwStyle&TLC_TREELIST )
					x += (pVisibleItem->m_nLevel-1) * TLL_WIDTH;

				if( m_dwStyle&(TLC_TREELINE|TLC_BUTTON) )
					x += TLL_WIDTH;

				if( m_dwStyle&TLC_CHECKBOX )
					if( pVisibleItem->GetState()&TLIS_SHOWCHECKBOX )
						x += TLL_WIDTH;

				if( m_dwStyle&TLC_LOCKBOX )
					if( pVisibleItem->GetState()&TLIS_SHOWLOCKBOX )
						x += TLL_WIDTH/2;

				if( m_dwStyle&TLC_IMAGE )
					if( pVisibleItem->GetState()&TLIS_SHOWTREEIMAGE )
						x += TLL_WIDTH;

				if( m_dwStyle&TLC_LOCKBOX || m_dwStyle&TLC_IMAGE )
					x += 2;
			}

			x += GetStringWidth( pVisibleItem->GetText( nCol ) );
			x += 2;

			if( nWidth < x )
				nWidth = x;

			pVisibleItem = GetNextShowItem( pVisibleItem );
		}
		return SetColumnWidth( nCol, nWidth, nMin, nMax );
	}
	else
	{
		// SetWidth()
		ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

		CTreeListColumnInfo* pColumnInfo;
		pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

		int iRet = pColumnInfo->SetWidth( nWidth, nMin, nMax );
		Layout();
		Invalidate();
		return iRet;
	}
}

int CTreeListCtrl::GetColumnWidth( int nCol )
{
	// retrieve column width
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	return pColumnInfo->GetWidth();
}

int CTreeListCtrl::SetColumnImage( int nCol, int iImage )
{
	// set index of column image
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	int iRet = pColumnInfo->SetImage( iImage );

	Invalidate();

	return iRet;
}

int CTreeListCtrl::GetColumnImage( int nCol )
{
	// retrieve index of column image
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	return pColumnInfo->GetImage();
}

BOOL CTreeListCtrl::SetColumnText( int nCol, LPCTSTR lpszText )
{
	// set text of column
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	BOOL bRet = pColumnInfo->SetText( lpszText );

	Invalidate();

	return bRet;
}

LPCTSTR CTreeListCtrl::GetColumnText( int nCol )
{
	// retrieve text of column
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	return pColumnInfo->GetText();
}

BOOL CTreeListCtrl::SetColumnDefaultText( int nCol, LPCTSTR lpszText )
{
	// set default text of column
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	return pColumnInfo->SetDefaultText( lpszText );
}

LPCTSTR CTreeListCtrl::GetColumnDefaultText( int nCol )
{
	// retrieve default text of column
	ASSERT( 0 <= nCol && nCol < m_arColumns.GetSize() );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[nCol];

	return pColumnInfo->GetDefaultText();
}

DWORD CTreeListCtrl::GetItemState( int nItem, DWORD nStateMask )
{
	// retrieve item state ( list )
	ASSERT( 0 <= nItem && nItem < GetCount() );
	return GetItemState( GetTreeListItem(nItem), nStateMask );
}

void CTreeListCtrl::SetItemState( int nItem, DWORD dwAddState, DWORD dwRemoveState )
{
	// set item state ( list )
	ASSERT( 0 <= nItem && nItem < GetCount() );
	SetItemState( GetTreeListItem(nItem), dwAddState, dwRemoveState );
}

void CTreeListCtrl::GetItemImage( int nItem, int& nImage, int& nExpandImage, int& nSelectedImage, int& nExpandSelectedImage )
{
	// retrieve index of item image ( list )
	ASSERT( 0 <= nItem && nItem < GetCount() );
	GetItemImage( GetTreeListItem(nItem), nImage, nExpandImage, nSelectedImage, nExpandSelectedImage );
}

void CTreeListCtrl::SetItemImage( int nItem, int nImage, int nExpandImage, int nSelectedImage, int nExpandSelectedImage )
{
	// set index of item image ( list )
	ASSERT( 0 <= nItem && nItem < GetCount() );
	SetItemImage( GetTreeListItem(nItem), nImage, nExpandImage, nSelectedImage, nExpandSelectedImage );
}

LPCTSTR CTreeListCtrl::GetItemText( int nItem, int nSubItem )
{
	// retrieve text of sub item ( list )
	ASSERT( 0 <= nItem && nItem < GetCount() );
	return GetItemText( GetTreeListItem(nItem), nSubItem );
}

BOOL CTreeListCtrl::SetItemText( int nItem, int nSubItem, LPCTSTR lpszText )
{
	// set text of sub item ( list )
	ASSERT( 0 <= nItem && nItem < GetCount() );
	return SetItemText( GetTreeListItem(nItem), lpszText, nSubItem );
}

DWORD CTreeListCtrl::GetItemData( int nItem )
{
	// retrieve data of item ( list )
	ASSERT( 0 <= nItem && nItem < GetCount() );
	return GetItemData( GetTreeListItem(nItem) );
}

void CTreeListCtrl::SetItemData( int nItem, DWORD dwData )
{
	// set data of item ( list )
	ASSERT( 0 <= nItem && nItem < GetCount() );
	SetItemData( GetTreeListItem(nItem), dwData );
}

BOOL CTreeListCtrl::GetViewRect( LPRECT lpRect )
{
	// retrieve list rect ( list )
	lpRect->left	= m_rcTreeList.left;
	lpRect->right	= m_rcTreeList.right;
	lpRect->top		= m_rcTreeList.top;
	lpRect->bottom	= m_rcTreeList.bottom;

	return m_rcTreeList.IsRectEmpty();
}

int CTreeListCtrl::GetTopIndex()
{
	// retrieve index of first visible item ( list )
	return GetScrollPos( SB_VERT );
}

int CTreeListCtrl::GetCountPerPage()
{
	// retrieve rows of visible item of one page ( list )
	return m_rcTreeList.Height() / GetItemHeight() + 1;
}

BOOL CTreeListCtrl::GetOrigin( LPPOINT lpPoint )
{
	// retrieve origin point of a list ( list )
	lpPoint->x = m_rcTreeList.left;
	lpPoint->y = m_rcTreeList.top;
	return TRUE;
}

UINT CTreeListCtrl::GetSelectedCount()
{
	// retrieve count of selected item ( list )
	return m_arSelects.GetSize();
}

BOOL CTreeListCtrl::SetColumnOrderArray( int iCount, LPINT piArray )
{
	// set show order of columns
	m_arShows.RemoveAll();

	for( int iShow=0; iShow<iCount; iShow++ )
		m_arShows.Add( piArray[iShow] );

	Invalidate();

	return TRUE;
}

BOOL CTreeListCtrl::GetColumnOrderArray( LPINT piArray, int iCount )
{
	// retrieve column show order
	if( iCount <= 0 )
		iCount = m_arShows.GetSize();

	for( int iShow=0; iShow<m_arShows.GetSize(); iShow++ )
		piArray[iShow] = m_arShows[iShow];

	Invalidate();

	return TRUE;
}

CTreeListHeaderCtrl* CTreeListCtrl::GetHeaderCtrl()
{
	// retrieve header control
	return &m_wndHeader;
}

int CTreeListCtrl::GetSelectionMark()
{
	// retrieve selection 
	POSITION pos = GetFirstSelectedItemPosition();
	return GetTreeListItem( GetNextSelectedItem( pos ) );
}

int CTreeListCtrl::SetSelectionMark( int iIndex )
{
	// set selection mark of an item
	int nItem = GetSelectionMark();
	SelectItem( GetTreeListItem( iIndex ), 0, FALSE );

	Invalidate();

	return nItem;
}

void CTreeListCtrl::SetFont()
{
	// set font with font of parent window
	CWnd* pWnd = GetParent();
	if( pWnd == NULL )
		return;

	CFont* pFont = pWnd->GetFont();
	if( pFont == NULL )
		return;

	LOGFONT lf;
	pFont->GetLogFont(&lf);
	m_Font.DeleteObject();
	m_Font.CreateFontIndirect(&lf);

	Invalidate();
}

CFont* CTreeListCtrl::GetFont()
{
	// retrieve font
	return &m_Font;
}

DWORD CTreeListCtrl::SetStyle( DWORD dwStyle )
{
	// set style of treelist control
	DWORD dwoldStyle = m_dwStyle;
	m_dwStyle = dwStyle;

	if( !(m_dwStyle&TLC_TREELIST ) )
	{
		m_dwStyle &= ~TLC_TREELINE;
		m_dwStyle &= ~TLC_ROOTLINE;
		m_dwStyle &= ~TLC_BUTTON;	
	}

	if( !(m_dwStyle&TLC_HGRID) )
	{
		m_dwStyle &= ~TLC_TGRID;
		m_dwStyle &= ~TLC_HGRID_EXT;
		m_dwStyle &= ~TLC_HGRID_FULL;
	}

	if( !(m_dwStyle&TLC_VGRID) )
	{
		m_dwStyle &= ~TLC_VGRID_EXT;
	}

	if( m_dwStyle&TLC_HGRID && m_dwStyle&TLC_VGRID )
	{
		if( m_dwStyle&TLC_HGRID_EXT && !(m_dwStyle&TLC_VGRID_EXT) )
			m_dwStyle &= ~( TLC_HGRID_EXT | TLC_VGRID_EXT );
		if( !(m_dwStyle&TLC_HGRID_EXT) && m_dwStyle&TLC_VGRID_EXT )
			m_dwStyle &= ~( TLC_HGRID_EXT | TLC_VGRID_EXT );
	}

	if( !(m_dwStyle&TLC_HEADER) )
	{
		m_dwStyle &= ~TLC_HEADDRAGDROP;
		m_dwStyle &= ~TLC_HEADFULLDRAG;
	}

	if( GetStyle()&TLC_HEADDRAGDROP )
		m_wndHeader.SetStyle( m_wndHeader.GetStyle()|TLHS_DRAGDROP );
	else
		m_wndHeader.SetStyle( m_wndHeader.GetStyle()&~TLHS_DRAGDROP );
	
	if( GetStyle()&TLC_HEADFULLDRAG )
		m_wndHeader.SetStyle( m_wndHeader.GetStyle()|TLHS_FULLDRAG );
	else
		m_wndHeader.SetStyle( m_wndHeader.GetStyle()&~TLHS_FULLDRAG );

	if( GetStyle()&TLC_HEADER )
		m_wndHeader.SetStyle( m_wndHeader.GetStyle()|TLHS_SHOWHEAD );
	else
		m_wndHeader.SetStyle( m_wndHeader.GetStyle()&~TLHS_SHOWHEAD );

	if( GetStyle()&TLC_HOTTRACK )
		m_wndHeader.SetStyle( m_wndHeader.GetStyle()|TLHS_HOTTRACK );
	else
		m_wndHeader.SetStyle( m_wndHeader.GetStyle()&~TLHS_HOTTRACK );

	Invalidate();

	return dwoldStyle;
}

DWORD CTreeListCtrl::GetStyle()
{
	// retrieve treelist control style
	return m_dwStyle;
}

void CTreeListCtrl::SetState( DWORD dwAddState, DWORD dwRemoveState )
{
	// set retrieve state of control
	m_dwState |= dwAddState;
	m_dwState &=~dwRemoveState;
	return; 
}

DWORD CTreeListCtrl::GetState( DWORD nStateMask )
{
	// retrieve state of control
	return m_dwState&nStateMask;
}

int CTreeListCtrl::GetSelectColumn()
{
	// retrieve select column
	return m_iSelCol;
}

int CTreeListCtrl::GetColumnCount()
{
	// retrieve column count
	return GetColumns();
}

int CTreeListCtrl::GetVisibleCount( CTreeListItem* pParent )
{
	// retrieve visible rows
	if( pParent == m_pRootItem )
		return pParent->m_nVisibleChild - 1;
	else
		return pParent->m_nVisibleChild;
}

void CTreeListCtrl::StatChildAdd( CTreeListItem* pItem, int nChild, int nVisibleChild )
{
	// stat. number of child & visible child on any level when add some new child
	ASSERT( pItem != NULL );
	
	if( pItem->m_pParent == NULL )
		return;
	
	CTreeListItem* pParent = pItem->m_pParent;

	pParent->m_nChild			+= nChild;

	if( pParent->GetState()&TLIS_EXPANDED )
	{
		pParent->m_nVisibleChild	+= nVisibleChild;
		StatChildAdd( pParent, nChild, nVisibleChild );
	}
	else
	{
		StatChildAdd( pParent, nChild, 0 );
	}
}

void CTreeListCtrl::StatChildDel( CTreeListItem* pItem, int nChild, int nVisibleChild )
{
	// stat. number of child & visible child on any level when add some new child
	ASSERT( pItem != NULL );
	
	if( pItem->m_pParent == NULL )
		return;
	
	CTreeListItem* pParent = pItem->m_pParent;
	
	pParent->m_nChild			-= nChild;
	
	if( pParent->GetState()&TLIS_EXPANDED )
	{
		pParent->m_nVisibleChild	-= nVisibleChild;
		StatChildDel( pParent, nChild, nVisibleChild );
	}
	else
	{
		StatChildDel( pParent, nChild, 0 );
	}
}

void CTreeListCtrl::StatExpand( CTreeListItem* pItem )
{
	// stat. number of child & visible child on any level when expand an item
	ASSERT( pItem != NULL );
	if( pItem->m_pChild == NULL )
		return;

	int nVisibleChild = 0;
	
	CTreeListItem* pChild = pItem->m_pChild;
	while( pChild != NULL )
	{
		nVisibleChild += pChild->m_nVisibleChild;
		pChild = pChild->m_pNext;
	}
	pItem->m_nVisibleChild += nVisibleChild;
	
	CTreeListItem* pParent = pItem->m_pParent;
	while( pParent != NULL )
	{
		pParent->m_nVisibleChild += nVisibleChild;
		pParent = pParent->m_pParent;
	}

	return;
}

void CTreeListCtrl::StatCollapse( CTreeListItem* pItem )
{
	// stat. number of child & visible child on any level when collapse an item
	ASSERT( pItem != NULL );
	if( pItem->m_pChild == NULL )
		return;

	int nVisibleChild = 0;

	CTreeListItem* pChild = pItem->m_pChild;
	while( pChild != NULL )
	{
		nVisibleChild += pChild->m_nVisibleChild;
		pChild = pChild->m_pNext;
	}
	pItem->m_nVisibleChild -= nVisibleChild;

	CTreeListItem* pParent = pItem->m_pParent;
	while( pParent != NULL )
	{
		pParent->m_nVisibleChild -= nVisibleChild;
		pParent = pParent->m_pParent;
	}

	return;
}

void CTreeListCtrl::SetItemCheck( CTreeListItem* pItem, BOOL bAutoCheck )
{
	// auto set check status ( include parent and child )
	LRESULT lResult;

	lResult = Notify( TLN_ITEMCHECK, pItem, 0 );
	if( lResult == -1 )
		return;

	if( bAutoCheck )
		pItem->SetCheck( !pItem->GetCheck() );

	if( m_dwStyle&TLC_NOAUTOCHECK )
		return;

	if( pItem->GetCheck() )
	{
		SetItemChildStatus( pItem, TLIS_CHECKED, TLIS_CHECKED_NULL );
		SetItemParentStatus( pItem, TLIS_CHECKEDMASK );
	}
	else
	{
		SetItemChildStatus( pItem, TLIS_CHECKED_NULL, TLIS_CHECKED );
		SetItemParentStatus( pItem, TLIS_CHECKEDMASK );
	}

	Invalidate();

	return;
}

void CTreeListCtrl::SetItemLock( CTreeListItem* pItem, BOOL bAutoLock )
{
	// auto set lock status ( include parent and child )
	LRESULT lResult;

	lResult = Notify( TLN_ITEMLOCK, pItem, 0 );
	if( lResult == -1 )
		return;

	if( bAutoLock )
		pItem->SetLock( !pItem->GetLock() );

	if( m_dwStyle&TLC_NOAUTOLOCK )
		return;

	if( pItem->GetLock() )
	{
		SetItemChildStatus( pItem, TLIS_LOCKED, TLIS_LOCKED_NULL );
		SetItemParentStatus( pItem, TLIS_LOCKEDMASK );
	}
	else
	{
		SetItemChildStatus( pItem, TLIS_LOCKED_NULL, TLIS_LOCKED );
		SetItemParentStatus( pItem, TLIS_LOCKEDMASK );
	}

	Invalidate();

	return;
}

void CTreeListCtrl::SetItemParentStatus( CTreeListItem* pItem, DWORD dwMask )
{
	// set parent items status;
	CTreeListItem* pParent;
	pParent = pItem->m_pParent;

	DWORD dwShow;

	if( pParent == NULL )
		return;

	ASSERT( dwMask == TLIS_CHECKEDMASK || dwMask == TLIS_LOCKEDMASK );
	if( dwMask == TLIS_CHECKEDMASK )
		dwShow = TLIS_SHOWCHECKBOX;
	else
		dwShow = TLIS_SHOWLOCKBOX;
		

	DWORD dwAdd = 0;
	DWORD dwRemove = 0;
	CTreeListItem* pNext = pItem->m_pParent->m_pChild;
	if( pNext->GetState()&dwShow )
		dwAdd |= pNext->GetState();
	while( pNext != NULL )
	{
		if( pNext->GetState()&dwShow )
			dwAdd |= pNext->GetState();
		pNext = pNext->m_pNext;
	}
	dwAdd		 =  dwAdd;
	dwRemove	 = ~dwAdd;
	dwAdd		&=  dwMask;
	dwRemove	&=  dwMask;

	pParent->SetState( dwAdd, dwRemove );
	SetItemParentStatus( pParent, dwMask );

	return;
}


void CTreeListCtrl::SetItemChildStatus( CTreeListItem* pItem, DWORD dwAdd, DWORD dwRemove )
{
	// set child items status
	CTreeListItem* pChild;
	pChild = pItem->m_pChild;

	while( pChild != NULL )
	{
		if( pChild->m_pChild != NULL )
			SetItemChildStatus( pChild, dwAdd, dwRemove );

		pChild->SetState( dwAdd, dwRemove );
		pChild = pChild->m_pNext;
	}

	return;
}

CTreeListItem* CTreeListCtrl::GetFirstShowItem( int nShowItem )
{
	// retrieve first visible item after n visible items
	if( nShowItem < 0 )
		return NULL;

	if( nShowItem >= m_pRootItem->m_nVisibleChild )
		return NULL;
	
	CTreeListItem* pItem = m_pRootItem->m_pChild;
	while( nShowItem != 0 )
	{
		ASSERT( nShowItem > 0 );

		if( nShowItem < pItem->m_nVisibleChild )
		{
			nShowItem --;
			pItem = pItem->m_pChild;
		}
		else
		{
			nShowItem -= pItem->m_nVisibleChild;
			pItem = pItem->m_pNext;
		}
	}

	return pItem;
}

CTreeListItem* CTreeListCtrl::GetNextShowItem( CTreeListItem* pItem, BOOL bChild )
{
	// retrieve next visible item
	ASSERT( pItem != NULL );

	if( pItem->GetState()&TLIS_EXPANDED )
		if( bChild && pItem->m_pChild != NULL )
			return pItem->m_pChild;

	if( pItem->m_pNext != NULL )
		return pItem->m_pNext;

	pItem = pItem->m_pParent;
	if( pItem != m_pRootItem )
		return GetNextShowItem( pItem, FALSE );

	return NULL;
}

BOOL CTreeListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// wm_erasebkgnd
	return TRUE;
}

void CTreeListCtrl::OnPaint() 
{
	// wm_paint
	CPaintDC dc(this);
	CPalette* pPalette = NULL;

	if( dc.GetDeviceCaps(RASTERCAPS)&RC_PALETTE )
	{
		pPalette = dc.SelectPalette( &m_Palette, FALSE );
		dc.RealizePalette();
	}

	dc.ExcludeClipRect( m_rcHeader );

	if( GetState( TLS_OFFSCREENBUFFER ) )
	{
		CTreeListDC TreeListDC(&dc);
		DrawCtrl( &TreeListDC );
	}
	else
	{
		DrawCtrl( &dc );
	}

	if( pPalette != NULL && dc.GetDeviceCaps(RASTERCAPS)&RC_PALETTE )
	{
		dc.SelectPalette( pPalette, FALSE );
	}
}

void CTreeListCtrl::DrawCtrl( CDC* pDC )
{
	// draw the control
	CRect rcClip;
	if( pDC->GetClipBox( &rcClip ) == ERROR )
		return;

	DrawBkgnd( pDC, rcClip );
	DrawItems( pDC, rcClip );
}

void CTreeListCtrl::DrawBkgnd( CDC* pDC, CRect rcClip )
{
	// draw background
	CRect rectClip;
	if (pDC->GetClipBox(&rectClip) == ERROR)
		return;

	if( CWnd::GetStyle()&WS_DISABLED )
	{
		if( m_dwStyle&TLC_BKGNDIMAGE )
		{
			DrawBkgndBmp( pDC, rcClip, &m_bmpBkDisable );
		}
		else if( m_dwStyle&TLC_BKGNDCOLOR )
		{
			pDC->FillSolidRect( rectClip, m_crBkDisable );
		}
		else
		{
			pDC->FillSolidRect( rectClip, m_crBkDisable_0 );
		}
	}
	else
	{
		if( m_dwStyle&TLC_BKGNDIMAGE )
		{
			DrawBkgndBmp( pDC, rcClip, &m_bmpBkBitmap );
		}
		else if( m_dwStyle&TLC_BKGNDCOLOR )
		{
			pDC->FillSolidRect( rectClip, m_crBkColor );
		}
		else
		{
			pDC->FillSolidRect( rectClip, m_crBkColor_0 );
		}
	}

	return;
}

void CTreeListCtrl::DrawBkgndBmp( CDC* pDC, CRect rcClip, CBitmap* pBkgnd )
{
	// draw bitmap background
	CRect rcClient;
	BITMAP bmBkgnd;
	
	GetClientRect( rcClient );
	pBkgnd->GetBitmap( &bmBkgnd );
	
	CDC dc;
	dc.CreateCompatibleDC( pDC );
	CBitmap* pBmp = dc.SelectObject( pBkgnd );

	pDC->IntersectClipRect( rcClip );

	int nPerfix = - ( GetScrollPos( SB_HORZ ) % bmBkgnd.bmWidth );
	for( int y = 0; y < rcClient.Height(); y += bmBkgnd.bmHeight )
		for( int x = nPerfix; x < rcClient.Width(); x += bmBkgnd.bmWidth )
			pDC->BitBlt( x, y, bmBkgnd.bmWidth, bmBkgnd.bmHeight, &dc, 0, 0, SRCCOPY);

	::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );

	dc.SelectObject( pBmp );
	dc.DeleteDC();

}

void CTreeListCtrl::DrawItems( CDC* pDC, CRect rcClip )
{
	// draw items
	CTreeListItem* pShowItem;
	
	pShowItem = GetFirstVisibleItem();
	if( pShowItem == NULL )
		return;

	CPen Pen( PS_SOLID, 1, m_crGrid );
	CPen* pOldPen	= pDC->SelectObject( &Pen );
	CFont* pOldFont	= pDC->SelectObject( &m_Font );
	int nOldMode = pDC->SetBkMode( TRANSPARENT );

	CRect rcClient;
	GetClientRect( rcClient );

	CRect rcItem;
	rcItem.SetRect( 0, 0, GetWidth(), GetItemHeight() );
	rcItem.OffsetRect( m_rcTreeList.left, m_rcTreeList.top );
	rcItem.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

	int nFirstRow;
	int nShowRows;

	nFirstRow	=	GetScrollPos( SB_VERT );
	nShowRows	=	m_rcTreeList.Height() / GetItemHeight() + 1;

	pShowItem	=	GetFirstShowItem( nFirstRow );

	for( int iRow=nFirstRow; iRow<= nFirstRow + nShowRows && iRow < GetVisibleCount(); iRow++, pShowItem = GetNextShowItem( pShowItem ) )
	{
		ASSERT( pShowItem != NULL );

		COLORREF crBkColor;

		if( !(m_dwStyle&TLC_BKGNDIMAGE) )
		{
			if( !(CWnd::GetStyle()&WS_DISABLED) )
			{
				if( m_dwStyle&TLC_DOUBLECOLOR )
				{
					if( iRow%2 == 1 )
						crBkColor = m_crBkColor_1;
					else
						crBkColor = m_crBkColor_2;
				}
				else
				{
					crBkColor = m_crBkColor_0;
				}
			}
			else
			{
				if( m_dwStyle&TLC_DOUBLECOLOR )
				{
					if( iRow%2 == 1 )
						crBkColor = m_crBkDisable_1;
					else
						crBkColor = m_crBkDisable_2;
				}
				else
				{
					crBkColor = m_crBkDisable_0;
				}
			}
			pDC->FillSolidRect( rcItem, crBkColor );
		}

		DrawItem( pDC, rcItem, pShowItem ); 
		
		if( m_dwStyle&TLC_HGRID_FULL && rcItem.right<rcClient.right )
		{
			pDC->MoveTo( rcItem.right, rcItem.bottom - 1);
			pDC->LineTo( rcClient.right, rcItem.bottom - 1);
		}

		rcItem.OffsetRect( 0, m_nItemHeight );
	}

	if( GetVisibleCount() > 0 )
	{
		if( m_dwStyle&TLC_HGRID && !(m_dwStyle&TLC_HGRID_EXT) && !(m_dwStyle&TLC_VGRID_EXT) )
		{
			pDC->MoveTo( rcItem.left, rcItem.top - 1);
			pDC->LineTo( rcItem.right-1, rcItem.top - 1);
		}
	}

	for( int iGrid=GetVisibleCount(); iGrid<= nFirstRow + nShowRows; iGrid++ )
	{
		COLORREF crBkColor;

		if( !(m_dwStyle&TLC_BKGNDIMAGE) )
		{
			if( !(CWnd::GetStyle()&WS_DISABLED) )
			{
				if( m_dwStyle&TLC_DOUBLECOLOR )
				{
					if( iGrid%2 == 1 )
						crBkColor = m_crBkColor_1;
					else
						crBkColor = m_crBkColor_2;
				}
				else
				{
					crBkColor = m_crBkColor_0;
				}
			}
			else
			{
				if( m_dwStyle&TLC_DOUBLECOLOR )
				{
					if( iGrid%2 == 1 )
						crBkColor = m_crBkDisable_1;
					else
						crBkColor = m_crBkDisable_2;
				}
				else
				{
					crBkColor = m_crBkDisable_0;
				}
			}
			pDC->FillSolidRect( rcItem, crBkColor );
		}

		DrawGrid( pDC, rcItem );

		if( m_dwStyle&TLC_HGRID_EXT && m_dwStyle&TLC_HGRID_FULL && rcItem.right<rcClient.right )
		{
			pDC->MoveTo( rcItem.right, rcItem.bottom - 1 );
			pDC->LineTo( rcClient.right, rcItem.bottom - 1 );
		}

		rcItem.OffsetRect( 0, m_nItemHeight );
	}

	pDC->SetBkMode( nOldMode );
	pDC->SelectObject( pOldFont );
	pDC->SelectObject( pOldPen );
	return;
}

void CTreeListCtrl::DrawItem( CDC* pDC, CRect rcItem, CTreeListItem* pItem )
{
	// draw item background
	DrawItemBkgnd( pDC, rcItem, pItem );

	// draw all columns
	CTreeListColumnInfo* pColumnInfo;
	int nColPos = 0;
	for( int iShow = 0; iShow < m_arShows.GetSize(); iShow++, nColPos += pColumnInfo->m_nWidth )
	{
		int iCol;
		
		// do NOT draw zero column;
		iCol = m_arShows[iShow];
		pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];
		if( pColumnInfo->m_nWidth == 0 )
			continue;

		CRect rcColumn;
		rcColumn.SetRect( 0, rcItem.top, pColumnInfo->m_nWidth, rcItem.bottom );
		rcColumn.OffsetRect( nColPos, 0 );
		rcColumn.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

		if( iCol == 0 )
		{
			if ( m_dwStyle&TLC_TREELIST )
				DrawItemTree( pDC, rcColumn, pItem, iCol );
			else
				DrawItemMain( pDC, rcColumn, pItem, iCol );
		}
		else
		{
			DrawItemList( pDC, rcColumn, pItem, iCol );
		}

	}

	CRect rcFocus;
	if( pItem == m_pFocusItem )
	{
		CPen pen;
		pen.CreatePen( PS_SOLID, 1, (COLORREF)0x000000 );
		CPen* ppen = pDC->SelectObject( &pen );

		CRect rcFocus;
		rcFocus.SetRect( 0, rcItem.top, GetWidth(), rcItem.bottom );
		rcFocus.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

		if( GetStyle()&TLC_HGRID )
			rcFocus.DeflateRect( 0, 0, 0, 1 );

		if( GetStyle()&TLC_VGRID )
			rcFocus.DeflateRect( 0, 0, 1, 0 );

		COLORREF crBkgnd, croldBkgnd;
		if( CWnd::GetStyle()&WS_DISABLED )
		{
			if( m_dwStyle&TLC_BKGNDIMAGE )
				crBkgnd = m_crBkDisable;
			else if( m_dwStyle&TLC_BKGNDCOLOR )
				crBkgnd = m_crBkDisable;
			else
				crBkgnd = m_crBkDisable_0;
		}
		else
		{
			if( m_dwStyle&TLC_BKGNDIMAGE )
				crBkgnd = m_crBkColor;
			else if( m_dwStyle&TLC_BKGNDCOLOR )
				crBkgnd = m_crBkColor;
			else
				crBkgnd = m_crBkColor_0;
		}

		croldBkgnd = pDC->SetBkColor( crBkgnd );
		pDC->SetTextColor( m_crText );
		pDC->DrawFocusRect( rcFocus );
		pDC->SetBkColor( croldBkgnd );

		pDC->SelectObject( ppen );
	}

	return;
}

void CTreeListCtrl::DrawGrid( CDC* pDC, CRect rcItem )
{
	// draw all grids
	CTreeListColumnInfo* pColumnInfo;
	int nColPos = 0;
	for( int iShow = 0; iShow < m_arShows.GetSize(); iShow++, nColPos += pColumnInfo->m_nWidth )
	{
		int iCol;
		
		iCol = m_arShows[iShow];
		pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];
		if( pColumnInfo->m_nWidth == 0 )
			continue;

		CRect rcColumn;
		rcColumn.SetRect( 0, rcItem.top, pColumnInfo->m_nWidth, rcItem.bottom );
		rcColumn.OffsetRect( nColPos, 0 );
		rcColumn.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

		if( iCol == 0 )
		{
			// draw vertical grid line of tree
			if( m_dwStyle&TLC_HGRID_EXT && m_dwStyle&TLC_TGRID )
			{
				pDC->MoveTo( rcColumn.left, rcColumn.bottom - 1);
				pDC->LineTo( rcColumn.right-1, rcColumn.bottom - 1);
			}

			if( m_dwStyle&TLC_VGRID_EXT )
			{
				pDC->MoveTo( rcColumn.right-1, rcColumn.bottom - 1);
				pDC->LineTo( rcColumn.right-1, rcColumn.top - 1 );
			}
		}
		else
		{
			// draw vertical grid line and horizonal grid lin
			if( m_dwStyle&TLC_HGRID_EXT )
			{
				pDC->MoveTo( rcColumn.left, rcColumn.bottom - 1);
				pDC->LineTo( rcColumn.right, rcColumn.bottom - 1);
			}

			if( m_dwStyle&TLC_VGRID_EXT )
			{
				pDC->MoveTo( rcColumn.right-1, rcColumn.bottom - 1);
				pDC->LineTo( rcColumn.right-1, rcColumn.top - 1 );
			}
		}
	}
}

void CTreeListCtrl::DrawItemBkgnd( CDC* pDC, CRect rcItem, CTreeListItem* pItem )
{
	// draw selected background
	CRect		rcBkgnd;
	COLORREF	crBkgnd;
	if( pItem == m_pTargetItem )
	{
		rcBkgnd.SetRect( 0, rcItem.top, GetWidth(), rcItem.bottom );
		rcBkgnd.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

		if( GetStyle()&TLC_HGRID )
			rcBkgnd.DeflateRect( 0, 0, 0, 1 );

		if( GetStyle()&TLC_VGRID )
			rcBkgnd.DeflateRect( 0, 0, 1, 0 );

		crBkgnd = m_crBkSelectedColumn;
		
		DrawItemExclude( pDC, rcItem, pItem );
		pDC->FillSolidRect( rcBkgnd, crBkgnd );
		::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );
	}
	else if( pItem->GetSelected() && GetStyle()&TLC_SHOWSELFULLROWS )
	{
		rcBkgnd.SetRect( 0, rcItem.top, GetWidth(), rcItem.bottom );
		rcBkgnd.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

		if( GetStyle()&TLC_HGRID )
			rcBkgnd.DeflateRect( 0, 0, 0, 1 );

		if( GetStyle()&TLC_VGRID )
			rcBkgnd.DeflateRect( 0, 0, 1, 0 );

		if( GetState( TLS_FOCUS ) )
		{
			if( !(m_dwStyle&TLC_MULTIPLESELECT) )
			{
				// single select
				crBkgnd = m_crBkSelectedRow;
			}
			else
			{
				// multiple select
				if( m_arSelects.GetSize() > 0 && pItem == (CTreeListItem*)m_arSelects[0] )
					crBkgnd = m_crBkSelectedRow;
				else
					crBkgnd = m_crBkSelected;
			}
			DrawItemExclude( pDC, rcItem, pItem );
			pDC->FillSolidRect( rcBkgnd, crBkgnd );
			::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );
		}
		else
		{
			if( m_dwStyle&TLC_SHOWSELALWAYS )
			{
				crBkgnd = m_crBkSelectedNoFocus;
				DrawItemExclude( pDC, rcItem, pItem );
				pDC->FillSolidRect( rcBkgnd, crBkgnd );
				::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );
			}
		}
	}
}

void CTreeListCtrl::DrawItemExclude( CDC* pDC, CRect rcItem, CTreeListItem* pItem )
{
	// exclude rects of selected item
	CTreeListColumnInfo* pColumnInfo;
	int nColPos = 0;

	if( !pItem->GetSelected() || !(GetStyle()&TLC_SHOWSELFULLROWS) )
		return;

	for( int iShow = 0; iShow < m_arShows.GetSize(); iShow++, nColPos += pColumnInfo->m_nWidth )
	{
		int iCol;
		
		iCol = m_arShows[iShow];
		pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];

		CRect rcColumn;
		rcColumn.SetRect( 0, rcItem.top, pColumnInfo->m_nWidth, rcItem.bottom );
		rcColumn.OffsetRect( nColPos, 0 );
		rcColumn.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

		if( iCol == 0 )
		{
			CRect rcExclude;
			int nPerfix = TLL_BORDER;
			if ( m_dwStyle&TLC_TREELIST )
			{
				nPerfix += TLL_WIDTH * ( pItem->m_nLevel - 1 );

				if( m_dwStyle&(TLC_TREELINE|TLC_BUTTON) )
					nPerfix += TLL_WIDTH;
			}

			if( m_dwStyle&TLC_CHECKBOX )
			{
				if( pItem->GetState()&TLIS_SHOWCHECKBOX )
				{
					CRect rcCheckBox;
					rcCheckBox.SetRect( 0, 0, TLL_WIDTH, TLL_WIDTH );
					rcCheckBox.OffsetRect( rcColumn.left + nPerfix, rcColumn.top + ( rcColumn.Height() - TLL_HEIGHT)/2 );
					rcExclude = rcColumn & rcCheckBox;

					if( !rcExclude.IsRectEmpty() )
						pDC->ExcludeClipRect( rcExclude );

					nPerfix += TLL_HEIGHT;
				}
			}

			if( m_dwStyle&TLC_LOCKBOX )
			{
				if( pItem->GetState()&TLIS_SHOWLOCKBOX )
				{
					CRect rcLockBox;
					rcLockBox.SetRect( 0, 0, TLL_WIDTH / 2, TLL_WIDTH );
					rcLockBox.OffsetRect( rcColumn.left + nPerfix, rcColumn.top + ( rcColumn.Height() - TLL_HEIGHT)/2 );
					rcExclude = rcColumn & rcLockBox;

					if( !rcExclude.IsRectEmpty() )
						pDC->ExcludeClipRect( rcExclude );

					nPerfix += TLL_HEIGHT / 2;
				}
			}
		
			if( m_dwStyle&TLC_IMAGE )
			{
				if( pItem->GetState()&TLIS_SHOWTREEIMAGE )
				{
					CRect rcImage;
					rcImage.SetRect( 0, 0, TLL_WIDTH, TLL_WIDTH );
					rcImage.OffsetRect( rcColumn.left + nPerfix, rcColumn.top + ( rcColumn.Height() - TLL_HEIGHT)/2 );
					rcExclude = rcColumn & rcImage;

					if( !rcExclude.IsRectEmpty() )
						pDC->ExcludeClipRect( rcExclude );

					nPerfix += TLL_HEIGHT;
				}
			}

			break;
		}
	}

}

void CTreeListCtrl::DrawItemTree( CDC* pDC, CRect rcColumn, CTreeListItem* pItem, int iCol )
{
	// draw tree column of treelist control
	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];

	CRect rcGraph;
	rcGraph = rcColumn;
	rcGraph.DeflateRect( TLL_BORDER, 0, TLL_BORDER+1, 0 );
	if( rcGraph.Width() <= 0 )
		return;
	CRect rcTree;
	rcTree = rcGraph;
	rcTree.right = rcTree.left + TLL_WIDTH;

	int nPerfix = TLL_BORDER;
	// draw prefix vertical line
	for( int iLevel=1; iLevel<pItem->m_nLevel; iLevel++, nPerfix += TLL_WIDTH )
	{
		CTreeListItem* pCheckItem = pItem;
		while( pCheckItem->m_nLevel != iLevel )
		{
			pCheckItem = pCheckItem->m_pParent;
		}

		rcTree.left = rcColumn.left + nPerfix;
		rcTree.right = rcTree.left + TLL_WIDTH;

		if( pCheckItem->m_pNext != NULL )
		{
			if( iLevel != 1 || m_dwStyle&TLC_ROOTLINE )
			{
				DrawItemTreeLine( pDC, rcGraph, rcTree, TLL_TOP | TLL_BOTTOM );				// ©§
			}
		}
	}

	// draw cross line
	if( m_dwStyle&(TLC_TREELINE|TLC_BUTTON) )
	{
		rcTree.left = rcColumn.left + nPerfix;
		rcTree.right = rcTree.left + TLL_WIDTH;
		if( pItem->m_nLevel == 1 )
		{
			// child item of root item
			if( m_dwStyle&TLC_ROOTLINE )
			{
				if( pItem->m_pPrev == NULL && pItem->m_pNext == NULL )
					DrawItemTreeLine( pDC, rcGraph, rcTree, TLL_RIGHT );						// ©¥ ( right part )
				else if( pItem->m_pPrev == NULL )
					DrawItemTreeLine( pDC, rcGraph, rcTree, TLL_RIGHT | TLL_BOTTOM );			// ©³
				else if( pItem->m_pNext == NULL )
					DrawItemTreeLine( pDC, rcGraph, rcTree, TLL_RIGHT | TLL_TOP );				// ©»
				else
					DrawItemTreeLine( pDC, rcGraph, rcTree, TLL_RIGHT | TLL_TOP | TLL_BOTTOM );	// ©Ç
			}
			else
			{
				DrawItemTreeLine( pDC, rcGraph, rcTree, TLL_RIGHT );							// ©¥ ( right part )
			}
		}
		else
		{
			// child item of other items ( not root item )
			if( pItem->m_pNext == NULL )
				DrawItemTreeLine( pDC, rcGraph, rcTree, TLL_RIGHT | TLL_TOP );					// ©»
			else
				DrawItemTreeLine( pDC, rcGraph, rcTree, TLL_RIGHT | TLL_TOP | TLL_BOTTOM );		// ©Ç
		}
		
		// draw button of child item of root item
		if( m_dwStyle&TLC_BUTTON )
		{
			if( pItem->GetState()&TLIS_EXPANDEDONCE )
			{
				if( pItem->m_pChild != NULL )
				{
					if( pItem->GetState()&TLIS_EXPANDED )
						DrawItemTreeButton( pDC, rcGraph, rcTree, TLB_MINUS );
					else
						DrawItemTreeButton( pDC, rcGraph, rcTree, TLB_PLUS );
				}				
			}
			else
			{
				DrawItemTreeButton( pDC, rcGraph, rcTree, TLB_UNKNOW );
			}
		}
		nPerfix += TLL_WIDTH;
	}

	// draw check box
	if( m_dwStyle&TLC_CHECKBOX )
	{
		if( pItem->GetState()&TLIS_SHOWCHECKBOX )
		{
			CRect rcCheckBox;
			rcCheckBox = rcGraph;
			rcCheckBox.left = rcColumn.left + nPerfix;
			rcCheckBox.right = rcCheckBox.left + TLL_WIDTH;

			POINT pt;
			pt.x = rcCheckBox.left;
			pt.y = rcCheckBox.top + (rcCheckBox.Height() - TLL_HEIGHT)/2;

			pDC->IntersectClipRect( rcGraph );
			pDC->IntersectClipRect( rcCheckBox );
			
			UINT nStyle = ILD_TRANSPARENT;
			if( pItem == m_pTargetItem || pItem == m_pHoverItem )
				nStyle |= ILD_FOCUS;
			m_imgCheck.Draw( pDC, pItem->GetCheck(), pt, nStyle );
			::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );

			nPerfix += TLL_WIDTH;
		}
	}

	// draw lock box
	if( m_dwStyle&TLC_LOCKBOX )
	{
		if( pItem->GetState()&TLIS_SHOWLOCKBOX )
		{
			CRect rcLockBox;
			rcLockBox = rcGraph;
			rcLockBox.left = rcColumn.left + nPerfix;
			rcLockBox.right = rcLockBox.left + TLL_WIDTH/2;

			POINT pt;
			pt.x = rcLockBox.left;
			pt.y = rcLockBox.top + (rcLockBox.Height() - TLL_HEIGHT)/2;

			pDC->IntersectClipRect( rcGraph );
			pDC->IntersectClipRect( rcLockBox );
			UINT nStyle = ILD_TRANSPARENT;
			if( pItem == m_pTargetItem || pItem == m_pHoverItem )
				nStyle |= ILD_FOCUS;
			m_imgLock.Draw( pDC, pItem->GetLock(), pt, nStyle );
			::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );
			
			nPerfix += TLL_WIDTH/2;
		}
	}

	// draw image box
	if( m_dwStyle&TLC_IMAGE )
	{
		if( pItem->GetState()&TLIS_SHOWTREEIMAGE )
		{
			CRect rcImage;
			rcImage = rcGraph;
			rcImage.left = rcColumn.left + nPerfix;
			rcImage.right = rcImage.left + TLL_WIDTH;

			POINT pt;
			pt.x = rcImage.left;
			pt.y = rcImage.top + (rcImage.Height() - TLL_HEIGHT)/2;

			pDC->IntersectClipRect( rcGraph );
			pDC->IntersectClipRect( rcImage );

			UINT nStyle = ILD_TRANSPARENT;
			if( pItem == m_pTargetItem || pItem == m_pHoverItem )
				nStyle |= ILD_FOCUS;

			if( pItem->GetState()&TLIS_EXPANDED && pItem->m_pChild != NULL )
			{
				if( m_arSelects.GetSize() > 0 && pItem == (CTreeListItem*)m_arSelects[0] )
					m_pImageList->Draw( pDC, pItem->m_nExpandSelectedImage, pt, nStyle );
				else
					m_pImageList->Draw( pDC, pItem->m_nSelectedImage, pt, nStyle );
			}
			else
			{
				if( m_arSelects.GetSize() > 0 && pItem == (CTreeListItem*)m_arSelects[0] )
					m_pImageList->Draw( pDC, pItem->m_nExpandImage, pt, nStyle );
				else
					m_pImageList->Draw( pDC, pItem->m_nImage, pt, nStyle );
			}

			::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );

			nPerfix += TLL_WIDTH;
		}
	}

	// add gaps between text and image 
	if( m_dwStyle&TLC_LOCKBOX || m_dwStyle&TLC_IMAGE )
		nPerfix += 2;

	// draw item text
	CRect rcBkgnd;
	rcBkgnd = rcColumn;
	rcBkgnd.left = rcColumn.left + nPerfix;

	DrawItemTreeText( pDC, rcBkgnd, pItem, iCol );

	// draw vertical grid line of tree
	if( m_dwStyle&TLC_TGRID )
	{
		pDC->MoveTo( rcColumn.left, rcColumn.bottom - 1);
		pDC->LineTo( rcColumn.right-1, rcColumn.bottom - 1);
	}

	if( m_dwStyle&TLC_VGRID )
	{
		pDC->MoveTo( rcColumn.right-1, rcColumn.bottom - 1);
		pDC->LineTo( rcColumn.right-1, rcColumn.top - 1 );
	}

	return;
}

void CTreeListCtrl::DrawItemMain( CDC* pDC, CRect rcColumn, CTreeListItem* pItem, int iCol )
{
	// draw main column of list
	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];

	CRect rcGraph;
	rcGraph = rcColumn;
	rcGraph.DeflateRect( TLL_BORDER, 0, TLL_BORDER+1, 0 );
	if( rcGraph.Width() <= 0 )
		return;
	
	CRect rcTree;
	rcTree = rcGraph;
	rcTree.right = rcTree.left + TLL_WIDTH;

	int nPerfix = TLL_BORDER;

	// draw check box
	if( m_dwStyle&TLC_CHECKBOX )
	{
		if( pItem->GetState()&TLIS_SHOWCHECKBOX )
		{
			CRect rcCheckBox;
			rcCheckBox = rcGraph;
			rcCheckBox.left = rcColumn.left + nPerfix;
			rcCheckBox.right = rcCheckBox.left + TLL_WIDTH;

			POINT pt;
			pt.x = rcCheckBox.left;
			pt.y = rcCheckBox.top + (rcCheckBox.Height() - TLL_HEIGHT)/2;

			pDC->IntersectClipRect( rcGraph );
			pDC->IntersectClipRect( rcCheckBox );
			UINT nStyle = ILD_TRANSPARENT;
			if( pItem == m_pTargetItem || pItem == m_pHoverItem )
				nStyle |= ILD_FOCUS;
			m_imgCheck.Draw( pDC, pItem->GetCheck(), pt, nStyle );
			::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );

			nPerfix += TLL_WIDTH;
		}
	}

	// draw lock box
	if( m_dwStyle&TLC_LOCKBOX )
	{
		if( pItem->GetState()&TLIS_SHOWLOCKBOX )
		{
			CRect rcLockBox;
			rcLockBox = rcGraph;
			rcLockBox.left = rcColumn.left + nPerfix;
			rcLockBox.right = rcLockBox.left + TLL_WIDTH/2;

			POINT pt;
			pt.x = rcLockBox.left;
			pt.y = rcLockBox.top + (rcLockBox.Height() - TLL_HEIGHT)/2;

			pDC->IntersectClipRect( rcGraph );
			pDC->IntersectClipRect( rcLockBox );
			UINT nStyle = ILD_TRANSPARENT;
			if( pItem == m_pTargetItem || pItem == m_pHoverItem )
				nStyle |= ILD_FOCUS;
			m_imgLock.Draw( pDC, pItem->GetLock(), pt, nStyle );
			::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );
			
			nPerfix += TLL_WIDTH/2;
		}
	}

	// draw image box
	if( m_dwStyle&TLC_IMAGE )
	{
		if( pItem->GetState()&TLIS_SHOWTREEIMAGE )
		{
			CRect rcImage;
			rcImage = rcGraph;
			rcImage.left = rcColumn.left + nPerfix;
			rcImage.right = rcImage.left + TLL_WIDTH;

			POINT pt;
			pt.x = rcImage.left;
			pt.y = rcImage.top + (rcImage.Height() - TLL_HEIGHT)/2;

			pDC->IntersectClipRect( rcGraph );
			pDC->IntersectClipRect( rcImage );

			UINT nStyle = ILD_TRANSPARENT;
			if( pItem == m_pTargetItem || pItem == m_pHoverItem )
				nStyle |= ILD_FOCUS;
			if( m_arSelects.GetSize() > 0 && pItem == (CTreeListItem*)m_arSelects[0] )
				m_pImageList->Draw( pDC, pItem->m_nExpandImage, pt, nStyle );
			else
				m_pImageList->Draw( pDC, pItem->m_nImage, pt, nStyle );

			::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );

			nPerfix += TLL_WIDTH;
		}
	}

	// add gaps between text and image 
	if( m_dwStyle&TLC_LOCKBOX || m_dwStyle&TLC_IMAGE )
		nPerfix += 2;

	// draw item text
	CRect rcBkgnd;
	rcBkgnd = rcColumn;
	rcBkgnd.left = rcColumn.left + nPerfix;

	DrawItemTreeText( pDC, rcBkgnd, pItem, iCol );

	// draw vertical grid line of tree
	if( m_dwStyle&TLC_TGRID )
	{
		pDC->MoveTo( rcColumn.left, rcColumn.bottom - 1);
		pDC->LineTo( rcColumn.right-1, rcColumn.bottom - 1);
	}

	if( m_dwStyle&TLC_VGRID )
	{
		pDC->MoveTo( rcColumn.right-1, rcColumn.bottom - 1);
		pDC->LineTo( rcColumn.right-1, rcColumn.top - 1 );
	}
}

void CTreeListCtrl::DrawItemList( CDC* pDC, CRect rcColumn, CTreeListItem* pItem, int iCol )
{
	// draw list
	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];

	CRect rcBkgnd;
	rcBkgnd = rcColumn;
	rcBkgnd.left = rcColumn.left;

	DrawItemListText( pDC, rcBkgnd, pItem, iCol );

	// draw vertical grid line and horizonal grid lin
	if( m_dwStyle&TLC_HGRID )
	{
		pDC->MoveTo( rcColumn.left, rcColumn.bottom - 1);
		pDC->LineTo( rcColumn.right, rcColumn.bottom - 1);
	}

	if( m_dwStyle&TLC_VGRID )
	{
		pDC->MoveTo( rcColumn.right-1, rcColumn.bottom - 1);
		pDC->LineTo( rcColumn.right-1, rcColumn.top - 1 );
	}
}

void CTreeListCtrl::DrawItemTreeLine( CDC* pDC, CRect rcColumn, CRect rcTree, DWORD dwFormat )
{
	// draw line of tree
	if( rcColumn.Width() == 0 || rcColumn.Height() == 0 )
		return;

	if( !(m_dwStyle&TLC_TREELINE) )
		return;

	ASSERT( rcTree.Width()	% 2 == 0 );
	ASSERT( rcTree.Height() % 2 == 0 );

	// clip column
	pDC->IntersectClipRect( rcColumn );
	pDC->IntersectClipRect( rcTree );

	CPoint ptCenter;
	ptCenter.x = rcTree.left + rcTree.Width() / 2 - 1;
	ptCenter.y = rcTree.top  + rcTree.Height() / 2 - 1;

	// draw center-left
	if( dwFormat&TLL_LEFT )
	{
		for( int ix = ptCenter.x; ix >= rcTree.left; ix -= 2 )
			pDC->SetPixelV( ix, ptCenter.y, m_crTreeLine );
	}

	// draw center-right
	if( dwFormat&TLL_RIGHT )
	{
		for( int ix = ptCenter.x; ix <= rcTree.right; ix += 2 )
			pDC->SetPixelV( ix, ptCenter.y, m_crTreeLine );
	}

	// draw center-top
	if( dwFormat&TLL_TOP )
	{
		for( int iy = ptCenter.y; iy >= rcTree.top; iy -= 2 )
			pDC->SetPixelV( ptCenter.x, iy, m_crTreeLine );
	}

	// draw center-bottom
	if( dwFormat&TLL_BOTTOM )
	{
		for( int iy = ptCenter.y; iy <= rcTree.bottom; iy += 2 )
			pDC->SetPixelV( ptCenter.x, iy, m_crTreeLine );
	}

	::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );
}

void CTreeListCtrl::DrawItemTreeButton( CDC* pDC, CRect rcColumn, CRect rcTree, DWORD dwFormat )
{
	// draw tree button [+][-][?]
	if( rcColumn.Width() == 0 || rcColumn.Height() == 0 )
		return;

	ASSERT( rcTree.Width()  % 2 == 0 );
	ASSERT( rcTree.Height() % 2 == 0 );

	// clip column
	pDC->IntersectClipRect( rcColumn );
	pDC->IntersectClipRect( rcTree );

	// button center
	CPoint ptCenter;
	ptCenter.x = rcTree.left + rcTree.Width() / 2 - 1;
	ptCenter.y = rcTree.top	+ rcTree.Height() / 2 - 1;

	CRect rcButton;
	rcButton.SetRect( -TLL_BUTTON, -TLL_BUTTON, TLL_BUTTON+1, TLL_BUTTON+1 );
	rcButton.OffsetRect( ptCenter );

	CBrush brButton;
	brButton.CreateSolidBrush( m_crTreeLine );

	if ( !(CWnd::GetStyle()&WS_DISABLED) )
		pDC->FillSolidRect( rcButton, 0x00FFFFFF );
	else
		pDC->FillSolidRect( rcButton, 0x00D0D0D0 );
	pDC->FrameRect( rcButton, &brButton );

	rcButton.DeflateRect( 2, 2, 2, 2 );
	// draw unknow button [+] in grey
	if( dwFormat&TLB_UNKNOW )
	{
		CPen Pen, *pOldPen;
		Pen.CreatePen( PS_SOLID, 1, m_crTreeLine );
		pOldPen = pDC->SelectObject( &Pen );
		pDC->MoveTo( rcButton.left, ptCenter.y );
		pDC->LineTo( rcButton.right, ptCenter.y );
		pDC->MoveTo( ptCenter.x, rcButton.top );
		pDC->LineTo( ptCenter.x, rcButton.bottom );
		pDC->SelectObject( pOldPen );
	}

	// draw plus button [+]
	if( dwFormat&TLB_PLUS )
	{
		CPen Pen, *pOldPen;
		Pen.CreatePen( PS_SOLID, 1, (COLORREF)0x000000 );
		pOldPen = pDC->SelectObject( &Pen );
		pDC->MoveTo( rcButton.left, ptCenter.y );
		pDC->LineTo( rcButton.right, ptCenter.y );
		pDC->MoveTo( ptCenter.x, rcButton.top );
		pDC->LineTo( ptCenter.x, rcButton.bottom );
		pDC->SelectObject( pOldPen );
	}

	// draw minus button [-]
	if( dwFormat&TLB_MINUS )
	{
		CPen Pen, *pOldPen;
		Pen.CreatePen( PS_SOLID, 1, (COLORREF)0x000000 );
		pOldPen = pDC->SelectObject( &Pen );
		pDC->MoveTo( rcButton.left, ptCenter.y );
		pDC->LineTo( rcButton.right, ptCenter.y );
		pDC->SelectObject( pOldPen );
	}

	::ExtSelectClipRgn( pDC->m_hDC, DEFAULT_HRGN, RGN_COPY );
}

void CTreeListCtrl::DrawItemTreeText( CDC* pDC, CRect rcBkgnd, CTreeListItem* pItem, int iCol )
{
	// draw text on tree
	CRect rcText;
	rcText = rcBkgnd;
	rcText.DeflateRect( 2, 0, 3, 0 );
	rcBkgnd.bottom = rcBkgnd.bottom - 1;
	DrawItemText( pDC, rcBkgnd, rcText, pItem, iCol );
}

void CTreeListCtrl::DrawItemListText( CDC* pDC, CRect rcBkgnd, CTreeListItem* pItem, int iCol )
{
	// draw text on list
	CRect rcText;
	rcText = rcBkgnd;
	rcText.DeflateRect( 2, 0, 3, 0 );
	rcBkgnd.bottom = rcBkgnd.bottom - 1;
	DrawItemText( pDC, rcBkgnd, rcText, pItem, iCol );
}

void CTreeListCtrl::DrawItemText( CDC* pDC, CRect rcBkgnd, CRect rcText, CTreeListItem* pItem, int iCol )
{
	COLORREF crBkgnd;
	COLORREF crText = m_crText;

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];

	// draw selected background
	if( rcBkgnd.Width() <= 0 || rcBkgnd.Height() <= 0 )
		return;

	if( pItem == m_pTargetItem )
	{
		crBkgnd = m_crBkSelectedColumn;
		crText	= m_crTextSelectedColumn;
	}
	else if( pItem->GetSelected() )
	{
		if( GetState( TLS_FOCUS ) )
		{
			if( !(m_dwStyle&TLC_MULTIPLESELECT) )
			{
				// single select
				if( iCol == m_iSelCol && m_dwStyle&TLC_SHOWSELACTIVE )
				{
					crBkgnd = m_crBkSelectedColumn;
					crText	= m_crTextSelectedColumn;
				}
				else
				{
					crBkgnd = m_crBkSelectedRow;
					crText	= m_crTextSelectedRow;
				}
			}
			else
			{
				// multiple select
				if( m_arSelects.GetSize() > 0 && pItem == (CTreeListItem*)m_arSelects[0] )
				{
					if( iCol == m_iSelCol && m_dwStyle&TLC_SHOWSELACTIVE )
					{
						crBkgnd = m_crBkSelectedColumn;
						crText	= m_crTextSelectedColumn;
					}
					else
					{
						crBkgnd = m_crBkSelectedRow;
						crText	= m_crTextSelectedRow;
					}
				}
				else
				{
					crBkgnd = m_crBkSelected;
					crText	= m_crTextSelected;
				}
			}
		
			pDC->FillSolidRect( rcBkgnd, crBkgnd );
		}
		else
		{
			if( m_dwStyle&TLC_SHOWSELALWAYS )
			{
				crBkgnd = m_crBkSelectedNoFocus;
				crText = m_crTextSelectedNoFocus;

				if( !(GetStyle()&TLC_SHOWSELFULLROWS) )
					pDC->FillSolidRect( rcBkgnd, crBkgnd );
			}
		}
	}

	// draw text
	if( rcText.Width() <= 0 || rcText.Height() <= 0 )
		return;

	COLORREF crOldText = pDC->SetTextColor( crText );

	UINT dwFormat = pColumnInfo->GetTextFormat();

	pDC->DrawText( pItem->GetText(iCol), rcText, dwFormat );

	pDC->SetTextColor( crOldText );
}

void CTreeListCtrl::OnEnable(BOOL bEnable) 
{
	// enable or disable control
	CWnd::OnEnable(bEnable);
	
	m_wndHeader.EnableWindow( bEnable );
	m_wndTip.EnableWindow( bEnable );

	Invalidate();

	return;
}

void CTreeListCtrl::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// calculate size of not client area
	if( !(CWnd::GetExStyle()&WS_EX_CLIENTEDGE) )
	{
		LPRECT pRECT = &lpncsp->rgrc[0];
		::InflateRect( pRECT, -1, -1 );
	}

	Default();
	return;
}

void CTreeListCtrl::OnNcPaint() 
{
	// draw 3d frame rect
	Default();

	if( !(CWnd::GetExStyle()&WS_EX_CLIENTEDGE) )
	{
		CWindowDC dc(this);
		CRect rcBorder;
		GetWindowRect( &rcBorder );
		ScreenToClient( &rcBorder );
		rcBorder.OffsetRect( -rcBorder.left, -rcBorder.top );
		dc.Draw3dRect( &rcBorder, GetSysColor( COLOR_3DDKSHADOW ), GetSysColor( COLOR_3DHILIGHT ) );
	}

	return;
}

void CTreeListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	// resize tree list control
	CWnd::OnSize(nType, cx, cy);
	
	Layout();

	return;
}

BOOL CTreeListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// translate mouse wheel message
	int nPos = zDelta / 120;

	if( IsWindow(m_wndTip.GetSafeHwnd()) && m_wndTip.IsWindowVisible() )
		m_wndTip.Hide();

	if( nPos > 0 )
	{
		PostMessage( WM_VSCROLL, (WPARAM)SB_PAGEUP );
	}
	else
	{
		PostMessage( WM_VSCROLL, (WPARAM)SB_PAGEDOWN );
	}
	return TRUE;
}


BOOL CTreeListCtrl::InsertColumn( LPCTSTR lpszColumnHeading, DWORD dwFormat, int nWidth, int iImage, int nMin, int nMax)
{
	// insert a column
	ASSERT( m_pRootItem->m_pChild == NULL );

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = new CTreeListColumnInfo;

	pColumnInfo->m_strCaption	= lpszColumnHeading;
	pColumnInfo->m_dwFormat		= dwFormat;
	pColumnInfo->m_nWidth		= nWidth;
	pColumnInfo->m_iImage		= iImage;
	pColumnInfo->m_nMin			= nMin;
	pColumnInfo->m_nMax			= nMax;

	int nCol = m_arColumns.Add( (void*)pColumnInfo );
	
	if( (pColumnInfo->m_dwFormat&TLF_HIDDEN) == 0 )
		m_arShows.Add( nCol );

	if( pColumnInfo->m_dwFormat&TLF_CAPTION_SORT )
		if( pColumnInfo->m_dwFormat&TLF_SORT_MASK )
			m_arSorts.Add( nCol );

	Layout();
	Invalidate();

	return TRUE;
}

BOOL CTreeListCtrl::DeleteColumn( int iCol )
{
	// delete a column
	ASSERT( m_pRootItem->m_pChild == NULL );

	if( iCol < 0  || m_arColumns.GetSize() <= iCol )
		return FALSE;

	CTreeListColumnInfo* pColumnInfo;
	pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];
	m_arColumns.RemoveAt( iCol );

	for( int iShow=0; iShow<m_arShows.GetSize(); iShow++ )
	{
		if( m_arShows[iShow] == iCol )
		{
			m_arShows.RemoveAt( iCol );
		}

		if( iShow<m_arShows.GetSize() )
		{
			if( m_arShows[iShow] > iCol )
				m_arShows[iShow] -= 1;
		}
	}

	for( int iSort=0; iSort<m_arSorts.GetSize(); iSort++ )
	{
		if( m_arSorts[iSort] == iCol )
			m_arSorts.RemoveAt( iCol );

		if( iSort<m_arSorts.GetSize() )
			if( m_arSorts[iSort] > iCol )
				m_arSorts[iSort] -= 1;
	}

	Layout();
	Invalidate();

	return TRUE;
}

int CTreeListCtrl::InsertItem( int nItem, LPCTSTR lpszItem )
{
	// insert an new item ( list )
	ASSERT( !(m_dwStyle&TLC_TREELIST) );
	CTreeListItem* pItem;

	if( m_pRootItem->m_pChild == NULL )
	{
		InsertItemNew( lpszItem, m_pRootItem );
		return 0;
	}

	if( nItem == 0 )
	{
		InsertItemFirst( lpszItem, m_pRootItem );
		return 0;
	}

	if( nItem >= GetCount() )
	{
		pItem = InsertItem( lpszItem, TLI_ROOT, TLI_LAST );
		return GetTreeListItem( pItem );
	}

	pItem = GetTreeListItem( nItem );
	pItem = InsertItem( lpszItem, TLI_ROOT, pItem );
	return GetTreeListItem( pItem );
}

BOOL CTreeListCtrl::DeleteItem( int nItem )
{
	// delete an item ( list )
	ASSERT( !(m_dwStyle&TLC_TREELIST) );
	CTreeListItem* pItem;

	pItem = GetTreeListItem( nItem );

	if( pItem == NULL )
		return FALSE;

	return DeleteItem( pItem );
}

CTreeListItem* CTreeListCtrl::InsertItem( LPCTSTR lpszItem, CTreeListItem* pParent, CTreeListItem* pInsertAfter )
{
	// insert an new item
	ASSERT( m_dwStyle&TLC_TREELIST || pParent == TLI_ROOT || pParent == m_pRootItem ) ;

	// add first level item
	if( pParent == TLI_ROOT )
	{
		return InsertItem( lpszItem, m_pRootItem, pInsertAfter );
	}

	// no child item
	if( pParent->m_pChild == NULL )
	{
		return InsertItemNew( lpszItem, pParent );
	}

	// add befor first child item
	if( pInsertAfter == TLI_FIRST )
	{
		return InsertItemFirst( lpszItem, pParent );
	}

	// add befor or after a child item by sorting
	if( pInsertAfter == TLI_SORT )
	{
		CTreeListItem* pPrevItem = GetSortChildItem( pParent );
		if( pPrevItem == NULL )
			return InsertItemFirst( lpszItem, pParent );
		else
			return InsertItemNext( lpszItem, pParent, pPrevItem );
	}

	// add after a child item
	if( pInsertAfter == TLI_LAST )
	{
		CTreeListItem* pPrevItem = GetLastChildItem( pParent );
		return InsertItemNext( lpszItem, pParent, pPrevItem );
	}
	
	// add after some child item
	{
		CTreeListItem* pPrevItem = GetValidChildItem( pParent, pInsertAfter );
		if( pPrevItem == NULL )
			return InsertItemFirst( lpszItem, pParent );
		else
			return InsertItemNext( lpszItem, pParent, pPrevItem );
	}

	return NULL;
}

BOOL CTreeListCtrl::DeleteItem( CTreeListItem* pItem )
{
	// delete an item
	if( pItem == TLI_ROOT )
	{
		CTreeListItem* pChild = m_pRootItem->m_pChild;
		CTreeListItem* pDelete;
		while( pChild != NULL )
		{
			pDelete = pChild;
			pChild = pChild->m_pNext;
			DeleteItemX( pDelete );
		}
	}
	else
	{
		DeleteItemX( pItem );
	}

	if( IsWindow( GetSafeHwnd() ) )
	{
		Layout();
		Invalidate();
	}

	return TRUE;
}

BOOL CTreeListCtrl::DeleteAllItems()
{
	// delete all items of treelist control
	BOOL bRedraw = IsWindowVisible();
	
	if( bRedraw )
		SetRedraw( FALSE );

	BOOL bDelte = DeleteItem( TLI_ROOT );

	if( bRedraw )
		SetRedraw( TRUE );

	Invalidate();

	return bDelte;
}

BOOL CTreeListCtrl::Expand( CTreeListItem* pItem, int nCode )
{
	// expand an item
	return Expand( pItem, nCode, m_iSelCol );
}

BOOL CTreeListCtrl::Expand( CTreeListItem* pItem, int nCode, int iSubItem )
{
	// expand an item or collapse an item
	ASSERT( m_dwStyle&TLC_TREELIST );
	LRESULT lResult;

	if( pItem == NULL )
		return FALSE;

	if( pItem->GetState()&TLIS_EXPANDEDONCE && pItem->m_pChild == NULL )
		return TRUE;

	if( nCode == TLE_TOGGLE )
	{
		if( pItem->GetState()&TLIS_EXPANDED )
			nCode = TLE_COLLAPSE;
		else
			nCode = TLE_EXPAND;
	}

	switch( nCode )
	{
	case TLE_EXPAND:
		if( pItem->GetState()&TLIS_EXPANDED )
			return TRUE;
		break;

	case TLE_COLLAPSE:
	case TLE_COLLAPSERESET:
		if( !(pItem->GetState()&TLIS_EXPANDED ) )
			return TRUE;
		break;

	default:
		return FALSE;
		break;
	}

	lResult = Notify( TLN_ITEMEXPANDING, pItem, iSubItem );
	if( lResult == -1 )
		return FALSE;

	BOOL bRedraw = IsWindowVisible();
	
	if( bRedraw )
		SetRedraw( FALSE );

	BOOL bExpand = FALSE;

	switch( nCode )
	{
	case TLE_EXPAND:
		pItem->Expand();
		StatExpand( pItem );
		break;

	case TLE_COLLAPSE:
		pItem->Collapse();
		StatCollapse( pItem );
		break;

	case TLE_COLLAPSERESET:
		pItem->Collapse();
		while( pItem->m_pChild != NULL )
		{
			DeleteItem( pItem->m_pChild );
		}
		StatCollapse( pItem );
		break;

	default:
		ASSERT( FALSE );
		break;
	}

	//SelectItem( pItem, iSubItem );
	if( bRedraw )
		SetRedraw( TRUE );

	Layout();
	Invalidate();

	Notify( TLN_ITEMEXPANDED, pItem, iSubItem );

	return bExpand;
}

BOOL CTreeListCtrl::Select( CTreeListItem* pItem, int nCode )
{
	// select an item
	SelectItem( pItem, 0, FALSE );
	return TRUE;
}

CTreeListItem* CTreeListCtrl::InsertItemNew( LPCTSTR lpszItem, CTreeListItem* pParent )
{
	// insert a new item
	ASSERT( pParent != NULL );

	CTreeListItem* pNewItem;
	pNewItem = new CTreeListItem(GetColumns());

	pNewItem->SetText( lpszItem );

	pNewItem->m_pParent	= pParent;
	pNewItem->m_nLevel	= pParent->m_nLevel + 1;

	if( pParent->GetCheck() == 1 )
		pNewItem->SetCheck( TRUE );

	if( pParent->GetLock() == 1 )
		pNewItem->SetLock( TRUE );


	pParent->m_pChild	= pNewItem;
	pParent->GetState( TLIS_EXPANDEDONCE );

	return InsertItemX( pParent, pNewItem );
}

CTreeListItem* CTreeListCtrl::InsertItemFirst( LPCTSTR lpszItem, CTreeListItem* pParent )
{
	// insert a child item before first child item
	ASSERT( pParent != NULL );

	CTreeListItem* pNewItem;
	pNewItem = new CTreeListItem(GetColumns());

	pNewItem->SetText( lpszItem );

	CTreeListItem* pFirstItem;
	pFirstItem	= pParent->m_pChild;

	pNewItem->m_pParent = pFirstItem->m_pParent;
	pNewItem->m_pNext	= pFirstItem;
	pNewItem->m_nLevel	= pFirstItem->m_nLevel;

	if( pParent->GetCheck() == 1 )
		pNewItem->SetCheck( TRUE );

	if( pParent->GetLock() == 1 )
		pNewItem->SetLock( TRUE );
		
	pFirstItem->m_pPrev		= pNewItem;
	pParent->m_pChild	= pNewItem;

	return InsertItemX( pParent, pNewItem );
}

CTreeListItem* CTreeListCtrl::InsertItemNext( LPCTSTR lpszItem, CTreeListItem* pParent, CTreeListItem* pInsertAfter )
{
	// insert a child item after some item
	ASSERT( pParent != NULL && pInsertAfter != NULL );

	CTreeListItem* pNewItem;
	pNewItem = new CTreeListItem(GetColumns());

	pNewItem->SetText( lpszItem );

	pNewItem->m_pParent = pInsertAfter->m_pParent;
	pNewItem->m_pNext	= pInsertAfter->m_pNext;
	pNewItem->m_pPrev	= pInsertAfter;
	pNewItem->m_nLevel	= pInsertAfter->m_nLevel;

	if( pParent->GetCheck() == 1 )
		pNewItem->SetCheck( TRUE );

	if( pParent->GetLock() == 1 )
		pNewItem->SetLock( TRUE );

	pInsertAfter->m_pNext	= pNewItem;

	if( pNewItem->m_pNext != NULL )
		pNewItem->m_pNext->m_pPrev = pNewItem;

	return InsertItemX( pParent, pNewItem );
}

CTreeListItem* CTreeListCtrl::InsertItemX( CTreeListItem* pParent, CTreeListItem* pNewItem )
{
	// insert an item
	ASSERT( pParent != NULL );
	ASSERT( pNewItem != NULL );

	StatChildAdd( pNewItem, pNewItem->m_nChild, pNewItem->m_nVisibleChild );

	pNewItem->SetImage( 0, 1, 2, 3 );

	Layout();
	Invalidate();

	return pNewItem;
}

BOOL CTreeListCtrl::DeleteItemX( CTreeListItem* pItem )
{
	// delete an item
	if( pItem->m_pPrev == NULL && pItem->m_pNext == NULL )
	{
		// no brother
		pItem->m_pParent->m_pChild = NULL;
	}
	else if( pItem->m_pPrev == NULL )
	{
		// first item of parent
		pItem->m_pParent->m_pChild = pItem->m_pNext;
		pItem->m_pNext->m_pPrev = NULL;
	}
	else if( pItem->m_pNext == NULL )
	{
		// last item of parent
		pItem->m_pPrev->m_pNext = NULL;
	}
	else
	{
		// middle item of parent
		pItem->m_pPrev->m_pNext = pItem->m_pNext;
		pItem->m_pNext->m_pPrev = pItem->m_pPrev;
	}

	StatChildDel( pItem, pItem->m_nChild, pItem->m_nVisibleChild );

	DeleteItemFast( pItem );

	return TRUE;
}

BOOL CTreeListCtrl::DeleteItemFast( CTreeListItem* pItem )
{
	// fast delete child items of pItem
	CTreeListItem* pChild;
	CTreeListItem* pDelete;

	pChild = pItem->m_pChild;
	while( pChild != NULL )
	{
		pDelete = pChild;
		pChild = pChild->m_pNext;
		DeleteItemFast( pDelete );
	}

	for( int iSel=0; iSel<m_arSelects.GetSize(); iSel++ )
	{
		if( pItem == (CTreeListItem*)m_arSelects[iSel] )
		{
			m_arSelects.RemoveAt( iSel );
			break;
		}
	}

	if( pItem == m_pFocusItem )
	{
		m_pFocusItem = NULL;
	}

	Notify( TLN_SELCHANGING, pItem, 0 );

	delete pItem;

	return TRUE;
}

void CTreeListCtrl::ActiveItem( CTreeListItem* pItem, int iSubItem )
{
	// active a selected item
	ASSERT( pItem != NULL && pItem->GetSelected() );

	if( !(m_dwStyle&TLC_MULTIPLESELECT) )
	{
		// single selected
		ASSERT( pItem == (CTreeListItem*)m_arSelects[0] );
		ASSERT( pItem == m_pFocusItem );
		m_iSelCol = iSubItem;
	}
	else
	{
		// multi selected
		BOOL bFound = FALSE;
		int iItem;
		for( iItem=0; iItem<m_arSelects.GetSize(); iItem++ )
		{
			if( (void*)pItem == m_arSelects[iItem] )
			{
				bFound = TRUE;
				break;
			}
		}

		ASSERT( bFound );
		
		m_arSelects.RemoveAt( iItem );
		m_arSelects.InsertAt( 0, (void*)pItem );
		m_iSelCol = iSubItem;
		m_pFocusItem = pItem;
	}
	
	EnsureVisible( pItem, iSubItem );
}

void CTreeListCtrl::SetTargetItem( CTreeListItem* pItem )
{
	// set drop target item
	m_pTargetItem = pItem;
	Invalidate();
}

void CTreeListCtrl::SetHoverItem( CTreeListItem* pItem )
{
	// set hover target item
	m_pHoverItem = pItem;
	m_iHoverItem = GetTreeListItem( pItem );
	Invalidate();
}

void CTreeListCtrl::SelectItem( CTreeListItem* pItem, int iSubItem, BOOL bClearLastSelected )
{
	LRESULT lResult;

	if( m_arSelects.GetSize() > 0 )
	{
		CTreeListItem* pSelItem = (CTreeListItem*)m_arSelects[0];
		if( pItem == pSelItem && iSubItem == m_iSelCol )
		{
			EnsureVisible( pItem, iSubItem );
			Invalidate();
			return;
		}
	}

	lResult = Notify( TLN_SELCHANGING, pItem, iSubItem );
	if( lResult == -1 )
		return;

	// select a new item
	if( pItem == NULL )
	{
		int iItem;
		for( iItem=0; iItem<m_arSelects.GetSize(); iItem++ )
		{
			CTreeListItem* pOldItem;
			pOldItem = (CTreeListItem*)m_arSelects[iItem];
			pOldItem->SetSelected( FALSE );
		}

		m_arSelects.RemoveAll();

		Notify( TLN_SELCHANGED, pItem, iSubItem );
		Invalidate();
		return;
	}

	// select a new item
	if( !(m_dwStyle&TLC_MULTIPLESELECT) )
	{
		// single select
		ASSERT( m_arSelects.GetSize() <= 1 );

		if( m_arSelects.GetSize() == 1 )
		{
			CTreeListItem* pOldItem = (CTreeListItem*)m_arSelects[0];
			pOldItem->SetSelected( FALSE );
			m_arSelects.RemoveAll();
		}

		pItem->SetSelected();
		m_iSelCol = iSubItem;
		m_pFocusItem = pItem;
		m_arSelects.Add( (void*) pItem );
	}
	else
	{
		// multi select
		if( bClearLastSelected )
		{
			int iItem;
			for( iItem=0; iItem<m_arSelects.GetSize(); iItem++ )
			{
				CTreeListItem* pOldItem;
				pOldItem = (CTreeListItem*)m_arSelects[iItem];
				pOldItem->SetSelected( FALSE );
			}

			m_arSelects.RemoveAll();
			pItem->SetSelected();
			m_iSelCol = iSubItem;
			m_pFocusItem = pItem;
			m_arSelects.Add( (void*)pItem );
		}
		else
		{
			BOOL bFound = FALSE;
			int iItem;
			for( iItem=0; iItem<m_arSelects.GetSize(); iItem++ )
			{
				if( (void*)pItem == m_arSelects[iItem] )
				{
					bFound = TRUE;
					break;
				}
			}

			if( bFound )
			{
				pItem->SetSelected( FALSE );
				m_arSelects.RemoveAt( iItem );
				m_iSelCol = iSubItem;
				m_pFocusItem = pItem;
			}
			else
			{
				pItem->SetSelected();
				m_arSelects.InsertAt( 0, (void*)pItem );
				m_iSelCol = iSubItem;
				m_pFocusItem = pItem;
			}
		}
	}

	Notify( TLN_SELCHANGED, pItem, iSubItem );
	EnsureVisible( pItem, iSubItem );
	Invalidate();
	return;
}

/*
void CTreeListCtrl::SetImageList( CTreeListItem* pItem, CImageList* pImageList )
{
	// 
	ASSERT( FALSE );

	pItem->SetImageList( pImageList );

	return;
}
*/

CTreeListItem* CTreeListCtrl::GetLastChildItem( CTreeListItem* pParent )
{
	// retrieve last child item
	if( pParent == TLI_ROOT )
		return GetLastChildItem( m_pRootItem );

	if( pParent->m_pChild == NULL )
		return NULL;

	CTreeListItem* pChildItem;
	pChildItem = pParent->m_pChild;

	while( pChildItem->m_pNext != NULL )
	{
		pChildItem = pChildItem->m_pNext;
	}

	return pChildItem;
}

CTreeListItem* CTreeListCtrl::GetSortChildItem( CTreeListItem* pParent )
{
	// retrieve sort child item
	if( pParent == TLI_ROOT )
		return GetSortChildItem( m_pRootItem );

	return GetLastChildItem( pParent );
}

CTreeListItem* CTreeListCtrl::GetValidChildItem( CTreeListItem* pParent, CTreeListItem* pChild )
{
	// is it a valid child item
	ASSERT( pChild != NULL );

	if( pParent == TLI_ROOT )
	{
		return GetValidChildItem( m_pRootItem, pChild );
	}

	if( pParent->m_pChild == NULL )
	{
		return NULL;
	}

	if( pChild == NULL )
	{
		return NULL;
	}

	BOOL bValid = FALSE;
	CTreeListItem* pChildItem;
	pChildItem = pParent->m_pChild;

	while( pChildItem != NULL )
	{
		if( pChildItem == pChild )
		{
			bValid = TRUE;
			break;
		}
		pChildItem = pChildItem->m_pNext;
	}
	
	if( !bValid )
	{
		return NULL;
	}

	return pChild;
}

void CTreeListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// on mouse move
	int nFlag, iSubItem;
	
	BOOL bHide = TRUE;
	
	CRect rcText;
	CTreeListItem* pItem;

	if( GetState( TLS_DRAG ) )
	{
		ASSERT( GetState( TLS_CAPTURE ) );
		DoDraging( point );
	}
	else
	{
		pItem = HitTest( point, &nFlag, &iSubItem, &rcText );
		if( pItem != NULL )
		{
			if( GetState( TLS_FOCUS ) && !(nFlags&(MK_LBUTTON | MK_RBUTTON | MK_MBUTTON)) )
			{
				CTreeListColumnInfo* pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iSubItem];
				m_wndTip.Show( rcText, pItem->GetText( iSubItem ), pColumnInfo->GetTextFormat() );
			}
			else
			{
				if( IsWindow( m_wndTip.GetSafeHwnd() ) && m_wndTip.IsWindowVisible() )
					m_wndTip.Hide();
			}

			if( nFlag&TLHT_ONITEMBUTTON )
			{
				SetCursor( m_hButton );
			} 

			if( nFlag&TLHT_ONITEMCHECKBOX )
			{
				SetCursor( m_hCheck );
			}

			if( nFlag&TLHT_ONITEMLOCKBOX )
			{
				SetCursor( m_hLock );
			}
		}
		else
		{
			if( IsWindow( m_wndTip.GetSafeHwnd() ) )
				m_wndTip.Hide();
		}

	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CTreeListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// left button was down
	SetFocus();

	CWnd::OnLButtonDown( nFlags, point );

	int nFlag, iSubItem;
	CRect rcText;

	CTreeListItem* pItem = HitTest( point, &nFlag, &iSubItem, &rcText );
	if( pItem != NULL )
	{
		if( m_dwStyle&TLC_TREELIST )
		{
			if( nFlag&TLHT_ONITEMBUTTON )
			{
				if( pItem->GetState() & TLIS_EXPANDED )
				{
					Expand( pItem, TLE_COLLAPSE, iSubItem );
				}
				else
				{
					Expand( pItem, TLE_EXPAND, iSubItem );
				}
				SetCursor( m_hButton );
			}
		}

		if( nFlag&TLHT_ONITEMCHECKBOX )
		{
			SetItemCheck( pItem );
			SetCursor( m_hCheck );
		}

		if( nFlag&TLHT_ONITEMLOCKBOX )
		{
			SetItemLock( pItem );
			SetCursor( m_hLock );
		}

		if( nFlag&TLHT_ONITEMTEXT && GetState( TLS_MODIFY ) )
		{
			if( pItem == m_pModifyItem )
				BeginModify( pItem, iSubItem );
			else
				FinishModify();
		}

		if( nFlag&TLHT_ONITEM && !(nFlag&TLHT_ONITEMBUTTON) && !(nFlag&TLHT_ONITEMCHECKBOX) && !(nFlag&TLHT_ONITEMLOCKBOX))
		{
			BOOL bDraging;
			if( !pItem->GetSelected() )
			{
				if( !(nFlags&MK_CONTROL) )
				{
					SelectItem( pItem, iSubItem );
				}
				else
				{
					SelectItem( pItem, iSubItem, FALSE );
				}
				bDraging = BeginDraging( point );
			}
			else
			{
				ActiveItem( pItem, iSubItem );
				bDraging = BeginDraging( point );
			}

			if( bDraging )
			{
				ASSERT( !GetState( TLS_CAPTURE ) );
				SetState( TLS_CAPTURE );
				SetCapture();
			}
		}

		Layout();
		Invalidate();
	}
	else
	{
		FinishModify();
		SelectItem( NULL );
		Layout();
		Invalidate();
	}

}

void CTreeListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// left button was up
	int nFlag, iSubItem;
	CTreeListItem* pItem;

	if( GetState( TLS_DRAG ) )
	{
		ReleaseCapture();
		SetState( 0, TLS_CAPTURE );

		EndDraging( point );

		Invalidate();
	}
	else
	{
		pItem = HitTest( point, &nFlag, &iSubItem );
		if( pItem != NULL )
		{
			if( nFlag&TLHT_ONITEMBUTTON )
			{
				SetCursor( m_hButton );
			}

			if( nFlag&TLHT_ONITEMCHECKBOX )
			{
				SetCursor( m_hCheck );
			}

			if( nFlag&TLHT_ONITEMLOCKBOX )
			{
				SetCursor( m_hLock );
			}
		}
	}
	
	ASSERT( !GetState( TLS_CAPTURE ) );

	CWnd::OnLButtonUp(nFlags, point);
}

void CTreeListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// left button double click
	CWnd::OnLButtonDblClk( nFlags, point );

	int nFlag, iSubItem;

	CTreeListItem* pItem = HitTest( point, &nFlag, &iSubItem );
	if( pItem != NULL )
	{
		if( nFlag&TLHT_ONITEMBUTTON )
		{
			SetCursor( m_hButton );
		}

		if( nFlag&TLHT_ONITEMCHECKBOX )
		{
			SetCursor( m_hCheck );
		}

		if( nFlag&TLHT_ONITEMLOCKBOX )
		{
			SetCursor( m_hLock );
		}

		if( m_dwStyle&TLC_TREELIST )
		{
			if ( nFlag&TLHT_ONITEMIMAGE || nFlag&TLHT_ONITEMTEXT )
			{
				//SelectItem( pItem, iSubItem );
				Expand( pItem, TLE_TOGGLE, iSubItem );
			}
		}

		Layout();
		Invalidate();
	}

}

void CTreeListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// right button was down
	SetFocus();

	CWnd::OnRButtonDown(nFlags, point);

	int nFlag, iSubItem;
	CRect rcText;

	CTreeListItem* pItem = HitTest( point, &nFlag, &iSubItem, &rcText );
	if( pItem != NULL )
	{
		if( nFlag&TLHT_ONITEM && !(nFlag&TLHT_ONITEMBUTTON) )
		{
			if( !(nFlags&MK_CONTROL) )
				SelectItem( pItem, iSubItem );
			else
				SelectItem( pItem, iSubItem, FALSE ); 
		}

		Layout();
		Invalidate();
	}
	else
	{
		if( GetState( TLS_MODIFY ) )
		{
			CancelModify();
		}

		SelectItem( NULL );
		Layout();
		Invalidate();
	}
}

void CTreeListCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// right button was up
	CWnd::OnRButtonUp(nFlags, point);
}

CTreeListItem* CTreeListCtrl::HitTest( CPoint pt, int* pFlag, int* pSubItem, CRect* prcText )
{
	// hittest of all items
	int nFlag, nSubItem;
	CRect rcText;

	if( pFlag == NULL )
		pFlag = &nFlag;

	if( pSubItem == NULL )
		pSubItem = &nSubItem;

	if( prcText == NULL )
		prcText = &rcText;

	*pFlag		= 0;
	*pSubItem	= 0;
	rcText.SetRect( 0, 0, 0, 0 );

	int nFirstRow	=	GetScrollPos( SB_VERT );
	int	nShowRows	=	m_rcTreeList.Height() / GetItemHeight() + 1;

	CRect rcItem;
	rcItem.SetRect( 0, 0, GetWidth(), GetItemHeight() );
	rcItem.OffsetRect( m_rcTreeList.left, m_rcTreeList.top );
	rcItem.OffsetRect( -GetScrollPos( SB_HORZ ), 0 );

	for( int i = nFirstRow; i <= nFirstRow + nShowRows && i < GetVisibleCount(); i++ )
	{
		if( rcItem.PtInRect( pt ) )
		{
			CTreeListItem* pItem = GetFirstShowItem( i );
			ASSERT( pItem != NULL );

			return HitTest( pt, pFlag, pSubItem, prcText, rcItem, pItem );
		}
		rcItem.OffsetRect( 0, m_nItemHeight );
	}
	return NULL;
}

CTreeListItem* CTreeListCtrl::HitTest( CPoint pt, int* pFlag, int* pSubItem, CRect* prcText, CRect rcItem, CTreeListItem* pItem )
{
	// hittest of one item
	ASSERT( pFlag != NULL && pSubItem != NULL );

	int nColPos = 0;

	CTreeListColumnInfo* pColumnInfo;

	for( int iShow = 0; iShow < m_arShows.GetSize(); iShow++, nColPos += pColumnInfo->m_nWidth )
	{
		int iCol;

		// do NOT test zero column;
		iCol = m_arShows[iShow];
		pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];
		if( pColumnInfo->m_nWidth == 0 )
			continue;

		CRect rcColumn;
		rcColumn.SetRect( 0, rcItem.top, pColumnInfo->m_nWidth, rcItem.bottom );
		rcColumn.OffsetRect( nColPos, 0 );
		rcColumn.OffsetRect( rcItem.left, 0 );

		if( rcColumn.PtInRect( pt ) )
		{
			*pSubItem = iCol;
			if( iCol == 0 )
			{
				if ( m_dwStyle&TLC_TREELIST )
					return HitTestTree( pt, pFlag, prcText, rcColumn, pItem );
				else
					return HitTestMain( pt, pFlag, prcText, rcColumn, pItem );
			}
			else
			{
				*prcText = rcColumn;
				return HitTestList( pt, pFlag, prcText, rcColumn, pItem );
			}
		}
	}

	return NULL;
}

CTreeListItem* CTreeListCtrl::HitTestTree( CPoint pt, int* pFlag, CRect* prcText, CRect rcColumn, CTreeListItem* pItem )
{
	// hittest of tree column of treelist control
	ASSERT( pFlag != NULL );
	ASSERT( pItem != NULL );

	int nPerfix = 0;
	CRect rcGraph;
	
	// skip perfix and tree line
	nPerfix += TLL_BORDER;
	nPerfix += (pItem->m_nLevel-1) * TLL_WIDTH;

	// check tree button
	if( m_dwStyle&(TLC_TREELINE|TLC_BUTTON) )
	{
		if( !(pItem->GetState()&TLIS_EXPANDEDONCE) || pItem->m_pChild != NULL )
		{
			rcGraph.SetRect( 0, rcColumn.top, TLL_WIDTH, rcColumn.bottom );
			rcGraph.OffsetRect( nPerfix, 0 );
			rcGraph.OffsetRect( rcColumn.left, 0 );

			CPoint ptCenter;
			ptCenter.x = rcGraph.left + rcGraph.Width() / 2 - 1;
			ptCenter.y = rcGraph.top + rcGraph.Height() / 2 - 1;

			CRect rcButton;
			rcButton.SetRect( -TLL_BUTTON, -TLL_BUTTON, TLL_BUTTON+1, TLL_BUTTON+1 );
			rcButton.OffsetRect( ptCenter );

			if( rcButton.PtInRect( pt ) )
				*pFlag |= TLHT_ONITEMBUTTON;
		}
		nPerfix += TLL_WIDTH;
	}

	// check tree check box;
	if( m_dwStyle&TLC_CHECKBOX )
	{
		if( pItem->GetState()&TLIS_SHOWCHECKBOX )
		{
			rcGraph.SetRect( 0, rcColumn.top, TLL_WIDTH, rcColumn.bottom );
			rcGraph.OffsetRect( nPerfix, 0 );
			rcGraph.OffsetRect( rcColumn.left, 0 );

			if( rcGraph.PtInRect( pt ) )
				*pFlag |= TLHT_ONITEMCHECKBOX;

			nPerfix += TLL_WIDTH;
		}
	}

	// check tree lock box;
	if( m_dwStyle&TLC_LOCKBOX )
	{
		if( pItem->GetState()&TLIS_SHOWLOCKBOX )
		{
			rcGraph.SetRect( 0, rcColumn.top, TLL_WIDTH/2, rcColumn.bottom );
			rcGraph.OffsetRect( nPerfix, 0 );
			rcGraph.OffsetRect( rcColumn.left, 0 );

			if( rcGraph.PtInRect( pt ) )
				*pFlag |= TLHT_ONITEMLOCKBOX;

			nPerfix += TLL_WIDTH/2;
		}
	}

	// check tree image
	if( m_dwStyle&TLC_IMAGE )
	{
		if( pItem->GetState()&TLIS_SHOWTREEIMAGE )
		{
			rcGraph.SetRect( 0, rcColumn.top, TLL_WIDTH, rcColumn.bottom );
			rcGraph.OffsetRect( nPerfix, 0 );
			rcGraph.OffsetRect( rcColumn.left, 0 );
	
			if( rcGraph.PtInRect( pt ) )
				*pFlag |= TLHT_ONITEMIMAGE;

			nPerfix += TLL_WIDTH;
		}
	}

	// add gaps between text and image/lock 
	if( m_dwStyle&TLC_LOCKBOX || m_dwStyle&TLC_IMAGE )
		nPerfix += 2;

	// check tree text
	CRect rcText;
	rcText = rcColumn;
	rcText.left = rcText.left + nPerfix;

	if( rcText.Width() > 0 )
	{
		if( rcText.PtInRect( pt ) )
		{
			*pFlag |= TLHT_ONITEMTEXT;
			*prcText = rcText;
		}
	}

	if( *pFlag == 0 )
		*pFlag |= TLHT_ONITEMSPACE;

	return pItem;
}

CTreeListItem* CTreeListCtrl::HitTestMain( CPoint pt, int* pFlag, CRect* prcText, CRect rcColumn, CTreeListItem* pItem )
{
	// hittest of main column of list control
	ASSERT( pFlag != NULL );
	ASSERT( pItem != NULL );

	int nPerfix = 0;
	CRect rcGraph;
	
	// skip perfix and tree line
	nPerfix += TLL_BORDER;

	// check tree check box;
	if( m_dwStyle&TLC_CHECKBOX )
	{
		if( pItem->GetState()&TLIS_SHOWCHECKBOX )
		{
			rcGraph.SetRect( 0, rcColumn.top, TLL_WIDTH, rcColumn.bottom );
			rcGraph.OffsetRect( nPerfix, 0 );
			rcGraph.OffsetRect( rcColumn.left, 0 );

			if( rcGraph.PtInRect( pt ) )
				*pFlag |= TLHT_ONITEMCHECKBOX;

			nPerfix += TLL_WIDTH;
		}
	}

	// check tree lock box;
	if( m_dwStyle&TLC_LOCKBOX )
	{
		if( pItem->GetState()&TLIS_SHOWLOCKBOX )
		{
			rcGraph.SetRect( 0, rcColumn.top, TLL_WIDTH/2, rcColumn.bottom );
			rcGraph.OffsetRect( nPerfix, 0 );
			rcGraph.OffsetRect( rcColumn.left, 0 );

			if( rcGraph.PtInRect( pt ) )
				*pFlag |= TLHT_ONITEMLOCKBOX;

			nPerfix += TLL_WIDTH/2;
		}
	}

	// check tree image
	if( m_dwStyle&TLC_IMAGE )
	{
		if( pItem->GetState()&TLIS_SHOWTREEIMAGE )
		{
			rcGraph.SetRect( 0, rcColumn.top, TLL_WIDTH, rcColumn.bottom );
			rcGraph.OffsetRect( nPerfix, 0 );
			rcGraph.OffsetRect( rcColumn.left, 0 );
	
			if( rcGraph.PtInRect( pt ) )
				*pFlag |= TLHT_ONITEMIMAGE;

			nPerfix += TLL_WIDTH;
		}
	}

	// add gaps between text and image/lock 
	if( m_dwStyle&TLC_LOCKBOX || m_dwStyle&TLC_IMAGE )
		nPerfix += 2;

	// check tree text
	CRect rcText;
	rcText = rcColumn;
	rcText.left = rcText.left + nPerfix;

	if( rcText.Width() > 0 )
	{
		if( rcText.PtInRect( pt ) )
		{
			*pFlag |= TLHT_ONITEMTEXT;
			*prcText = rcText;
		}
	}

	if( *pFlag == 0 )
		*pFlag |= TLHT_ONITEMSPACE;

	return pItem;}

CTreeListItem* CTreeListCtrl::HitTestList( CPoint pt, int* pFlag, CRect* prcText, CRect rcColumn, CTreeListItem* pItem )
{
	// hittest of other columns of treelist control
	ASSERT( pFlag != NULL );
	ASSERT( pItem != NULL );

	*pFlag = TLHT_ONITEMTEXT;
	*prcText = rcColumn;

	return pItem;
}

void CTreeListCtrl::OnSetFocus( CWnd* pOldWnd ) 
{
	// set focus
	CWnd::OnSetFocus( pOldWnd );
	
	SetCtrlFocus( pOldWnd, TRUE );

	Invalidate();

	return;
}

void CTreeListCtrl::OnKillFocus( CWnd* pNewWnd ) 
{
	// lost focus
	CWnd::OnKillFocus( pNewWnd );

	SetCtrlFocus( pNewWnd, FALSE );

	Invalidate();

	return;
}

BOOL CTreeListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// pre translate some messages
	switch( pMsg->message )
	{
	case WM_MOUSEMOVE:
		// cancel tips
		{
			POINTS points;
			CPoint pt;

			points = MAKEPOINTS( pMsg->lParam );
			pt.x = points.x;
			pt.y = points.y;

			if( m_rcHeader.PtInRect( pt ) )
			{
				if( IsWindow( m_wndTip.GetSafeHwnd() ) && m_wndTip.IsWindowVisible() )
					m_wndTip.Hide();
			}
		}
		break;

	case WM_LBUTTONDOWN:
		// cancel midified controls
		if( GetState( TLS_MODIFY ) )
		{
			POINTS points;
			CPoint pt;

			points = MAKEPOINTS( pMsg->lParam );
			pt.x = points.x;
			pt.y = points.y;

			if( pMsg->hwnd == m_wndHeader.GetSafeHwnd() && m_rcHeader.PtInRect( pt ) )
			{
				if( !FinishModify() )
				{
					return TRUE;
				}			
			}

			int nFlag;
			int iSubItem;
			CRect rcText;
			CTreeListItem* pItem = HitTest( pt, &nFlag, &iSubItem, &rcText );
			if( pMsg->hwnd == GetSafeHwnd() && pItem != NULL && pItem != m_pModifyItem )
			{
				if( !FinishModify() )
				{
					return TRUE;
				}			
			}
		}
		break;

	case WM_LBUTTONDBLCLK:
		// filter dbclk message on button & chanbox & lockbox of treelist control
		{
			CTreeListItem* pItem = NULL;
			POINTS points;
			CPoint pt;
			int nFlag;
			int iSubItem;

			points = MAKEPOINTS( pMsg->lParam );
			pt.x = points.x;
			pt.y = points.y;

			pItem = HitTest( pt, &nFlag, &iSubItem );
			if( pItem != NULL && nFlag&TLHT_ONITEMBUTTON )
			{
				pMsg->message = WM_LBUTTONDOWN;
				return PreTranslateMessage( pMsg );
			}
			if( pItem != NULL && nFlag&TLHT_ONITEMCHECKBOX )
			{
				pMsg->message = WM_LBUTTONDOWN;
				return PreTranslateMessage( pMsg );
			}

			if( pItem != NULL && nFlag&TLHT_ONITEMLOCKBOX )
			{
				pMsg->message = WM_LBUTTONDOWN;
				return PreTranslateMessage( pMsg );
			}
		}
		break;

	case WM_RBUTTONDOWN:
		// dragging...
		if( GetState( TLS_DRAG ) )
		{
			return TRUE;
		}

		// cancel modified control
		if( GetState( TLS_MODIFY ) )
		{
			POINTS points;
			CPoint pt;

			points = MAKEPOINTS( pMsg->lParam );
			pt.x = points.x;
			pt.y = points.y;

			if( pMsg->hwnd == m_wndHeader.GetSafeHwnd() && m_rcHeader.PtInRect( pt ) )
			{
				CancelModify();
				return TRUE;
			}
			
			int nFlag;
			int iSubItem;
			CRect rcText;
			CTreeListItem* pItem = HitTest( pt, &nFlag, &iSubItem, &rcText );
			if( pMsg->hwnd == GetSafeHwnd() && m_rcTreeList.PtInRect( pt ) )
			{
				if( pItem != m_pModifyItem )
				{
					CancelModify();
					return TRUE;
				}
				else
				{
					return TRUE;
				}
			}
		}
		break;

	case WM_RBUTTONDBLCLK:
		// filter dbclk message on button & chanbox & lockbox of treelist control
		if( pMsg->hwnd == GetSafeHwnd() )
		{
			pMsg->message = WM_RBUTTONDOWN;
			return PreTranslateMessage( pMsg );
		}
		break;

	case WM_NCLBUTTONDOWN:
		// cancel modified controls
		if( GetState( TLS_MODIFY ) )
		{
			CancelModify();
			PostMessage( WM_NCLBUTTONDOWN, pMsg->wParam, pMsg->lParam );
			PostMessage( WM_NCLBUTTONUP,   pMsg->wParam, pMsg->lParam );
			return TRUE;
		}
		break;

	case WM_NCRBUTTONDOWN:
		// cancel modified controls
		if( GetState( TLS_MODIFY ) )
		{
			CancelModify();
			PostMessage( WM_NCRBUTTONDOWN, pMsg->wParam, pMsg->lParam );
			PostMessage( WM_NCRBUTTONUP,   pMsg->wParam, pMsg->lParam );
			return TRUE;
		}
		break;

	case WM_KEYDOWN:
		// filter keydown mesages by status
		{
			ASSERT( GetState( TLS_FOCUS ) );

			if( GetState( TLS_DRAG ) )
			{
				return TRUE;
			}

			if( !GetState( TLS_MODIFY ) )
			{
				if( PreTranslateKeyDownMessage( pMsg ) )
					return TRUE;
			}
			else
			{
				if( PreTranslateKeyDownMessage2( pMsg ) )
					return TRUE;
			}
		}
		break;

	case WM_CHAR:
	case WM_SYSCHAR:
	case WM_DEADCHAR:
	case WM_SYSDEADCHAR:

	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:

	case WM_COMMAND:
	case WM_SYSCOMMAND:
//	case WM_MENUCOMMAND:
		// filter keyup mesages by status
		{
			if( GetState( TLS_DRAG ) )
			{
				return TRUE;
			}
		}

	default:
		break;
	}

	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CTreeListCtrl::PreTranslateKeyDownMessage( MSG* pMsg )
{
	// pre translate key down messages
	ASSERT( pMsg->message == WM_KEYDOWN );
	CTreeListItem* pItem;
	int iShow;
	BOOL bFound;

	if( m_arShows.GetSize() == 0 )
		return TRUE;

	switch( pMsg->wParam )
	{
	case VK_ADD:
		{
			if( GetStyle()&TLC_TREELIST )
			{
				Expand( m_pFocusItem, TLE_EXPAND );
				return TRUE;
			}
		}
		break;

	case VK_SUBTRACT:
		{
			if( GetStyle()&TLC_TREELIST )
			{
				Expand( m_pFocusItem, TLE_COLLAPSE );
				return TRUE;
			}
		}
		break;

	case VK_SPACE:
		{
			if( GetStyle()&TLC_TREELIST )
			{
				Expand( m_pFocusItem, TLE_TOGGLE );
				return TRUE;
			}
		}
		break;

	case VK_LEFT:
		{
			if( GetKeyState( VK_SHIFT ) < 0 && GetStyle()&TLC_TREELIST )
			{
				Expand( m_pFocusItem, TLE_COLLAPSE );
				return TRUE;
			}

			for( iShow=0; iShow<m_arShows.GetSize(); iShow++ )
			{
				if( m_arShows[iShow] == m_iSelCol )
					break;
			}

			if( iShow == m_arShows.GetSize() )
			{
				m_iSelCol = m_arShows[0];
			}
			else
			{
				iShow = iShow - 1;
				if( iShow < 0 )
					iShow = 0;
				m_iSelCol = m_arShows[iShow];
			}

			if( m_pFocusItem != NULL )
				pItem = m_pFocusItem;
			else
				pItem = GetNextVisibleItem( m_pRootItem );

			if( pItem != NULL )
				SelectItem( pItem, m_iSelCol );

			return TRUE;
		}
		break;

	case VK_RIGHT:
		{
			if( GetKeyState( VK_SHIFT ) < 0 && GetStyle()&TLC_TREELIST )
			{
				Expand( m_pFocusItem, TLE_EXPAND );
				return TRUE;
			}

			for( iShow=0; iShow<m_arShows.GetSize(); iShow++ )
			{
				if( m_arShows[iShow] == m_iSelCol )
					break;
			}

			if( iShow == m_arShows.GetSize() )
			{
				m_iSelCol = m_arShows[0];
			}
			else
			{
				iShow = iShow + 1;
				if( iShow >= m_arShows.GetSize() )
					iShow = m_arShows.GetUpperBound();
				m_iSelCol = m_arShows[iShow];
			}


			if( m_pFocusItem != NULL )
				pItem = m_pFocusItem;
			else
				pItem = GetNextVisibleItem( m_pRootItem );

			if( pItem != NULL )
				SelectItem( pItem, m_iSelCol );

			return TRUE;
		}
		break;

	case VK_UP:
		{
			if( m_pFocusItem != NULL )
				pItem = GetPrevVisibleItem( m_pFocusItem );
			else
				pItem = GetNextVisibleItem( m_pRootItem );

			for( iShow=0, bFound=FALSE; iShow<m_arShows.GetSize(); iShow++ )
			{
				if( m_arShows[iShow] == m_iSelCol )
				{
					bFound = TRUE;
					break;
				}
			}

			if( !bFound )
			{
				m_iSelCol = 0;
			}

			if( pItem != NULL )
				SelectItem( pItem, m_iSelCol );

			return TRUE;
		}
		break;

	case VK_DOWN:
		{
			if( m_pFocusItem != NULL )
				pItem = GetNextVisibleItem( m_pFocusItem );
			else
				pItem = GetNextVisibleItem( m_pRootItem );

			for( iShow=0, bFound=FALSE; iShow<m_arShows.GetSize(); iShow++ )
			{
				if( m_arShows[iShow] == m_iSelCol )
				{
					bFound = TRUE;
					break;
				}
			}

			if( !bFound )
			{
				m_iSelCol = 0;
			}

			if( pItem != NULL )
				SelectItem( pItem, m_iSelCol );

			return TRUE;
		}
		break;

	case VK_PRIOR:	// VK_PAGE_UP
		{
			int nFirstItem;
			int nLastItem;
			int nCount;
			CTreeListItem* pFirstItem = NULL;

			nCount		= m_rcTreeList.Height() / GetItemHeight();
			if( m_rcTreeList.Height() >= GetItemHeight() )
			{
				nCount -= 1;
			}

			nFirstItem	= GetScrollPos( SB_VERT );
			nLastItem	= nFirstItem + nCount;

			pFirstItem = GetTreeListItem( nFirstItem );

			for( iShow=0, bFound=FALSE; iShow<m_arShows.GetSize(); iShow++ )
			{
				if( m_arShows[iShow] == m_iSelCol )
				{
					bFound = TRUE;
					break;
				}
			}

			if( !bFound )
			{
				m_iSelCol = 0;
			}

			if( m_pFocusItem != NULL )
			{
				int nFocusItem = GetTreeListItem( m_pFocusItem );
				if( nFirstItem > nFocusItem )
				{
					EnsureVisible( m_pFocusItem, m_iSelCol );
					return TRUE;
				}
			}

			if( pFirstItem != NULL )
			{
				if( pFirstItem != m_pFocusItem )
				{
					SelectItem( pFirstItem, m_iSelCol );
				}
				else
				{
					nFirstItem = nFirstItem - nCount - 1;
					if( nFirstItem < 0 )
						nFirstItem = 0;

					nLastItem = nLastItem - nCount - 1;
					if( nLastItem < 0 )
						nLastItem = 0;

					pFirstItem = GetTreeListItem( nFirstItem );
					SetScrollPos( SB_VERT, nFirstItem );
					SelectItem( pFirstItem, m_iSelCol );
				}
			}

			return TRUE;

		}
	case VK_NEXT:	// VK_PAGE_DOWN
		{
			int nFirstItem;
			int nLastItem;
			int nCount;
			CTreeListItem* pLastItem = NULL;
			
			nCount		= m_rcTreeList.Height() / GetItemHeight();
			if( m_rcTreeList.Height() >= GetItemHeight() )
			{
				nCount -= 1;
			}

			nFirstItem	= GetScrollPos( SB_VERT );
			nLastItem	= nFirstItem + nCount;

			if( nLastItem >= GetVisibleCount() )
			{
				nLastItem  = GetVisibleCount() - 1;
			}

			pLastItem = GetTreeListItem( nLastItem );

			for( iShow=0, bFound=FALSE; iShow<m_arShows.GetSize(); iShow++ )
			{
				if( m_arShows[iShow] == m_iSelCol )
				{
					bFound = TRUE;
					break;
				}
			}

			if( !bFound )
			{
				m_iSelCol = 0;
			}

			if( m_pFocusItem != NULL )
			{
				int nFocusItem = GetTreeListItem( m_pFocusItem );
				if( nLastItem < nFocusItem )
				{
					EnsureVisible( m_pFocusItem, m_iSelCol );
					return TRUE;
				}
			}
			
			if( pLastItem != NULL )
			{
				if( pLastItem != m_pFocusItem )
				{
					SelectItem( pLastItem, m_iSelCol );
				}
				else
				{
					if( nFirstItem < GetVisibleCount() - nCount - 1 )
					{
						if( nFirstItem + nCount + 1 < GetVisibleCount() - nCount - 1 )
						{
							nFirstItem = nFirstItem + nCount + 1;
						}
					}
					
					nLastItem	= nLastItem + nCount + 1;
					if( nLastItem >= GetVisibleCount() )
					{
						nLastItem = GetVisibleCount() - 1;
					}

					pLastItem = GetTreeListItem( nLastItem );
					SetScrollPos( SB_VERT, nFirstItem );
					SelectItem( pLastItem, m_iSelCol );
				}
			}

			return TRUE;
		}
		break;

	case VK_HOME:
		{
			pItem = GetNextVisibleItem( m_pRootItem );

			for( iShow=0, bFound=FALSE; iShow<m_arShows.GetSize(); iShow++ )
			{
				if( m_arShows[iShow] == m_iSelCol )
				{
					bFound = TRUE;
					break;
				}
			}

			if( !bFound )
			{
				m_iSelCol = 0;
			}

			if( pItem != NULL )
				SelectItem( pItem, m_iSelCol );

			return TRUE;
		}
		break;

	case VK_END:
		{
			CTreeListItem* pNextItem;
			pItem = GetNextVisibleItem( m_pRootItem );
			pNextItem = pItem;
			while( pNextItem != NULL )
			{
				pItem = pNextItem;
				pNextItem = GetNextVisibleItem( pNextItem );
			}

			for( iShow=0, bFound=FALSE; iShow<m_arShows.GetSize(); iShow++ )
			{
				if( m_arShows[iShow] == m_iSelCol )
				{
					bFound = TRUE;
					break;
				}
			}

			if( !bFound )
			{
				m_iSelCol = 0;
			}

			if( pItem != NULL )
				SelectItem( pItem, m_iSelCol );

			return TRUE;
		}

		break;

	case VK_RETURN:
		/*
		if( m_arSelects.GetSize() > 0 )
		{
			pItem = (CTreeListItem*)m_arSelects[0];
			int iModify = m_iSelCol;

			if( 0 <= iModify && iModify < m_arColumns.GetSize() )
				BeginModify( pItem, iModify );
		}
		return TRUE;
		*/
		break;

	default:
		break;

	}

	return FALSE;
}

BOOL CTreeListCtrl::PreTranslateKeyDownMessage2( MSG* pMsg )
{
	// pre translate key down messages
	ASSERT( pMsg->message == WM_KEYDOWN );
	int iPrevCol;
	int iNextCol;

	if( m_arShows.GetSize() == 0 )
		return TRUE;

	switch( pMsg->wParam )
	{
	case VK_TAB:
		if( GetKeyState( VK_SHIFT ) < 0 )
		{
			iPrevCol = GetPrevModifyCol();
			if( iPrevCol != -1 )
				BeginModify( m_pModifyItem, iPrevCol );
		}
		else
		{
			iNextCol = GetNextModifyCol();
			if( iNextCol != -1 )
				BeginModify( m_pModifyItem, iNextCol );
		}

		return TRUE;
		break;

	case VK_ESCAPE:
		if( GetState( TLS_MODIFY ) )
		{
			CancelModify();
			return TRUE;
		}
		break;

	case VK_RETURN:
		{
			FinishModify();
			return TRUE;
		}
		break;

	default:
		break;
	}

	return FALSE;
}

CTreeListItem* CTreeListCtrl::GetTreeListItem( int nItem )
{
	// retrieve pointer of item by index of item
	if( GetCount() == 0 )
		return NULL;

	if( nItem < 0 || GetCount() <= nItem )
		return NULL;

	CTreeListItem* pItem = m_pRootItem->m_pChild;
	while( nItem != 0 )
	{
		ASSERT( nItem > 0 );

		if( nItem < pItem->m_nVisibleChild )
		{
			nItem --;
			pItem = pItem->m_pChild;
		}
		else
		{
			nItem -= pItem->m_nVisibleChild;
			pItem = pItem->m_pNext;
		}
	}

	return pItem;
}

int CTreeListCtrl::GetTreeListItem( CTreeListItem* pItem )
{
	// retrieve index of item by pointer of item
	if( GetCount() == 0 )
		return -1;

	if( pItem == NULL )
		return -1;

	if( pItem == m_pRootItem )
		return -1;

	int iItem = 1;
	while( pItem->m_pPrev != NULL )
	{
		pItem = pItem->m_pPrev;
		iItem = iItem + pItem->m_nVisibleChild;
	}

	pItem = pItem->m_pParent;
	iItem = iItem + GetTreeListItem( pItem );
	return iItem;
}

BOOL CTreeListCtrl::SetCtrlFocus( CWnd* pWnd, BOOL bFocus )
{
	// set focus

	// hidden tooltips
	if( IsWindow( m_wndTip.GetSafeHwnd() ) )
		m_wndTip.Hide();

	if( bFocus )
	{
		CWnd* pOldWnd = pWnd;
		if( pOldWnd == this )
			return FALSE;

		if( IsChild( pOldWnd ) )
			return FALSE;

		SetState( TLS_FOCUS );
	}
	else
	{
		CWnd* pNewWnd = pWnd;
		if( pNewWnd == this )
			return FALSE;

		if( IsChild( pNewWnd ) )
			return FALSE;

		if( GetState( TLS_MODIFY ) )
		{
			CancelModify();
		}

		SetState( 0, TLS_FOCUS );
	}
	
	Invalidate();

	return TRUE;
}

BOOL CTreeListCtrl::BeginModify( CTreeListItem* pItem, int iCol )
{
	// begin modify a column of an item
	ASSERT( pItem != NULL && 0 <= iCol && iCol < GetColumns() );

	if( (GetStyle()&TLC_READONLY) )
		return FALSE;

	// save values in m_pUpdateItem
	if( !GetState( TLS_MODIFY ) )
	{
		ASSERT( m_pModifyItem == NULL && m_pUpdateItem == NULL && m_iModifyCol == -1 );

		m_pModifyItem	= pItem;
		m_iModifyCol	= iCol;

		m_pUpdateItem	= new CTreeListItem( GetColumns() );
		for( int iColumn = 0; iColumn < GetColumns(); iColumn++ )
		{
			m_pUpdateItem->SetText( pItem->GetText( iColumn ), iColumn );
		}
	}

	// update modified columns
	if( GetState( TLS_MODIFY ) )
	{
		if( pItem == m_pModifyItem )
		{
			if( !UpdateModifyColumn() )
			{
				ASSERT( !GetState( TLS_MODIFY ) );
				SetState( TLS_MODIFY );
				RestoreControl( pItem, m_iModifyCol );
				return FALSE;
			}
			else
			{
				ASSERT( !GetState( TLS_MODIFY ) );
				SetState( TLS_MODIFY );
				return BeginControl( pItem, iCol );
			}
		}
		else
		{
			if( !UpdateModify() )
			{
				ASSERT( !GetState( TLS_MODIFY ) );
				return FALSE;
			}
			else
			{
				ASSERT( !GetState( TLS_MODIFY ) );
				return BeginModify( pItem, iCol );
			}
		}
	}
	
	// begin modify a new column
	ASSERT( !GetState( TLS_MODIFY ) );

	SetState( TLS_MODIFY );
	BeginControl( pItem, iCol );

	Invalidate();

	return TRUE;
}

BOOL CTreeListCtrl::UpdateModify()
{
	// update modified column ( must cancel modified item )

	// avoid reentry
	if( GetState( TLS_MODIFYING ) )
		return TRUE;

	if( !GetState( TLS_MODIFY ) )
		return FALSE;

	// update all columns of an item
	ASSERT( GetState( TLS_MODIFY ) );
	ASSERT( m_pModifyItem != NULL && m_pUpdateItem != NULL && m_iModifyCol != -1 );

	ASSERT( !GetState( TLS_MODIFYING ) );

	LRESULT lr = 0;
	SetState( TLS_MODIFYING );

	// cancel control of an item
	CancelControl();

	// update modified column
 	CString strText;
	strText = m_pUpdateItem->GetText( m_iModifyCol );

	if( strText.Compare( m_pModifyItem->GetText( m_iModifyCol ) ) != 0 )
	{
		lr = Notify( TLN_ITEMUPDATING, m_pModifyItem, m_iModifyCol );

		if( lr < 0 )
		{
			m_pModifyItem->SetText( strText, m_iModifyCol );
			Notify( TLN_ITEMFINISHED, m_pModifyItem, -1 );
			delete m_pUpdateItem;
			m_pUpdateItem = NULL;
			m_pModifyItem = NULL;
			m_iModifyCol  = -1;
			SetState( 0, TLS_MODIFY | TLS_MODIFYING );
			Invalidate();
			return FALSE;
		}
	}

	// check if need update
	BOOL bUpdate = FALSE;
	for( int iCol=0; iCol<m_arColumns.GetSize(); iCol++ )
	{
		CString strText;
		strText = m_pUpdateItem->GetText( iCol );
		if( strText.Compare( m_pModifyItem->GetText( iCol ) ) != 0 )
		{
			bUpdate = TRUE;
			break;
		}
	}

	// update all columns
	if( bUpdate )
	{
		lr = Notify( TLN_ITEMUPDATED, m_pModifyItem, -1 );
	
		if( lr < 0 )
		{
			for( iCol = 0; iCol<m_arColumns.GetSize(); iCol++ )
			{
				CString strText;
				strText = m_pUpdateItem->GetText( iCol );
				m_pModifyItem->SetText( strText, iCol );
			}
			Notify( TLN_ITEMFINISHED, m_pModifyItem, -1 );
			delete m_pUpdateItem;
			m_pUpdateItem = NULL;
			m_pModifyItem = NULL;
			m_iModifyCol  = -1;
			SetState( 0, TLS_MODIFY | TLS_MODIFYING );
			Invalidate();
			return FALSE;
		}
		else
		{
			Notify( TLN_ITEMFINISHED, m_pModifyItem, 0 );
			delete m_pUpdateItem;
			m_pUpdateItem = NULL;
			m_pModifyItem = NULL;
			m_iModifyCol  = -1;
			SetState( 0, TLS_MODIFY | TLS_MODIFYING );
			Invalidate();
			return TRUE;
		}
	}
	else
	{
		Notify( TLN_ITEMFINISHED, m_pModifyItem, 1 );
		delete m_pUpdateItem;
		m_pUpdateItem = NULL;
		m_pModifyItem = NULL;
		m_iModifyCol  = -1;
		SetState( 0, TLS_MODIFY | TLS_MODIFYING );
		Invalidate();
		return TRUE;
	}
}

BOOL CTreeListCtrl::FinishModify()
{
	// finish modify
	
	// avoid reentry
	if( GetState( TLS_MODIFYING ) )
		return TRUE;

	if( !GetState( TLS_MODIFY ) )
		return FALSE;

	if( !UpdateModifyColumns() )
	{
		ASSERT( !GetState( TLS_MODIFY ) );
		SetState( TLS_MODIFY );
		RestoreControl( m_pModifyItem, m_iModifyCol );
		Invalidate();
		return FALSE;
	}

	Invalidate();
	return TRUE;
}

BOOL CTreeListCtrl::CancelModify()
{
	// cancel modify

	// avoid reentry
	if( GetState( TLS_MODIFYING ) )
		return TRUE;

	if( !GetState( TLS_MODIFY ) )
		return FALSE;

	ASSERT( GetState( TLS_MODIFY ) );
	ASSERT( m_pModifyItem != NULL && m_pUpdateItem != NULL && m_iModifyCol != -1 );

	// cancel all columns of an item
	CancelControl();

	// restore values from m_pUpdateItem
	for( int iColumn = 0; iColumn < GetColumns(); iColumn++ )
	{
		m_pModifyItem->SetText( m_pUpdateItem->GetText( iColumn ), iColumn );
	}

	Notify( TLN_ITEMFINISHED, m_pModifyItem, 1 );
	delete m_pUpdateItem;
	m_pUpdateItem = NULL;
	m_pModifyItem = NULL;
	m_iModifyCol  = -1;
	SetState( 0, TLS_MODIFY );

	Invalidate();
	
	return TRUE;
}

BOOL CTreeListCtrl::UpdateModifyColumn()
{
	// update modified column ( do not cancel modified item )

	// avoid reentry
	if( GetState( TLS_MODIFYING ) )
		return TRUE;

	if( !GetState( TLS_MODIFY ) )
		return TRUE;

	ASSERT( GetState( TLS_MODIFY ) );
	ASSERT( m_pModifyItem != NULL && m_pUpdateItem != NULL && m_iModifyCol != -1 );

	ASSERT( !GetState( TLS_MODIFYING ) );

	LRESULT lr = 0;
	SetState( TLS_MODIFYING );

	// cancel control of an item
	CancelControl();

	// update active column
 	CString strText;
	strText = m_pUpdateItem->GetText( m_iModifyCol );

	if( strText.Compare( m_pModifyItem->GetText( m_iModifyCol ) ) != 0 )
	{
		lr = Notify( TLN_ITEMUPDATING, m_pModifyItem, m_iModifyCol );

		if( lr < 0 )
		{
			m_pModifyItem->SetText( strText, m_iModifyCol );
			SetState( 0, TLS_MODIFY | TLS_MODIFYING );
			return FALSE;
		}
	}

	SetState( 0, TLS_MODIFY | TLS_MODIFYING );
	return TRUE;
}

BOOL CTreeListCtrl::UpdateModifyColumns()
{
	// update modified columns ( cancel modified item on suceed )

	// avoid reentry
	if( GetState( TLS_MODIFYING ) )
		return TRUE;

	if( !GetState( TLS_MODIFY ) )
		return TRUE;

	ASSERT( GetState( TLS_MODIFY ) );
	ASSERT( m_pModifyItem != NULL && m_pUpdateItem != NULL && m_iModifyCol != -1 );

	ASSERT( !GetState( TLS_MODIFYING ) );

	LRESULT lr = 0;
	SetState( TLS_MODIFYING );

	// cancel control of an item
	CancelControl();

	// update active column
 	CString strText;
	strText = m_pUpdateItem->GetText( m_iModifyCol );

	if( strText.Compare( m_pModifyItem->GetText( m_iModifyCol ) ) != 0 )
	{
		lr = Notify( TLN_ITEMUPDATING, m_pModifyItem, m_iModifyCol );

		if( lr < 0 )
		{
			SetState( 0, TLS_MODIFY | TLS_MODIFYING );
			return FALSE;
		}
	}

	// check if need update
	BOOL bUpdate = FALSE;
	for( int iCol=0; iCol<m_arColumns.GetSize(); iCol++ )
	{
		CString strText;
		strText = m_pUpdateItem->GetText( iCol );
		if( strText.Compare( m_pModifyItem->GetText( iCol ) ) != 0 )
		{
			bUpdate = TRUE;
			break;
		}
	}

	// update all columns
	if( bUpdate )
	{
		lr = Notify( TLN_ITEMUPDATED, m_pModifyItem, -1 );
	
		if( lr < 0 )
		{
			SetState( 0, TLS_MODIFY | TLS_MODIFYING );
			return FALSE;
		}
		else
		{
			Notify( TLN_ITEMFINISHED, m_pModifyItem, 0 );
			delete m_pUpdateItem;
			m_pUpdateItem = NULL;
			m_pModifyItem = NULL;
			m_iModifyCol  = -1;
			SetState( 0, TLS_MODIFY | TLS_MODIFYING );
			return TRUE;
		}
	}
	else
	{
		Notify( TLN_ITEMFINISHED, m_pModifyItem, 1 );
		delete m_pUpdateItem;
		m_pUpdateItem = NULL;
		m_pModifyItem = NULL;
		m_iModifyCol  = -1;
		SetState( 0, TLS_MODIFY | TLS_MODIFYING );
		return TRUE;
	}
}

CWnd* CTreeListCtrl::GetControl( CTreeListItem* pItem, int iCol )
{
	// get pointer of modified control

	// check parameter
	if( pItem == NULL )
		return NULL;

	if( iCol < 0 ||  m_arColumns.GetSize() <= iCol )
		return NULL;

	// check state of control
	if( !GetState( TLS_MODIFY ) )
		return NULL;

	CWnd* pWnd;
	// restore a control
	switch( GetColumnModify( iCol ) )
	{
	case TLM_STATIC:
		pWnd = (CWnd*)&m_wndStatic;
		break;

	case TLM_EDIT:
		pWnd = (CWnd*)&m_wndEdit;
		break;

	case TLM_COMBO:
		pWnd = (CWnd*)&m_wndCombo;
		break;

	default:
		break;
	}

	return pWnd;
}

int CTreeListCtrl::GetPrevModifyCol()
{
	// retrieve previous modify column
	ASSERT( GetState( TLS_MODIFY ) );

	int  iShow;
	int  iShowCol	= -1;
	int  iPrevCol	= -1;
	BOOL bFound		= FALSE;

	for( iShow = 0; iShow < m_arShows.GetSize(); iShow++ )
	{
		if( m_arShows[iShow] == m_iModifyCol )
		{
			iShowCol = iShow;
			bFound = TRUE;
			break;
		}
	}

	ASSERT( bFound == TRUE );

	for( iShow = iShowCol - 1; iShow >= 0; iShow-- )
	{
		if( GetColumnModify( m_arShows[iShow] ) )
		{
			iPrevCol = m_arShows[iShow];
			break;
		}
	}

	return iPrevCol;
}

int CTreeListCtrl::GetNextModifyCol()
{
	// retrieve next modify column
	ASSERT( GetState( TLS_MODIFY ) );

	int  iShow;
	int  iShowCol	= -1;
	int  iNextCol	= -1;
	BOOL bFound		= FALSE;

	for( iShow = 0; iShow < m_arShows.GetSize(); iShow++ )
	{
		if( m_arShows[iShow] == m_iModifyCol )
		{
			iShowCol = iShow;
			bFound	 = TRUE;
			break;
		}
	}

	ASSERT( bFound == TRUE );

	for( iShow = iShowCol + 1; iShow < m_arShows.GetSize(); iShow++ )
	{
		if( GetColumnModify( m_arShows[iShow] ) )
		{
			iNextCol = m_arShows[iShow];
			break;
		}
	}

	return iNextCol;
}

BOOL CTreeListCtrl::BeginControl( CTreeListItem* pItem, int iCol )
{
	// begin a modify control
	ASSERT( GetState( TLS_MODIFY ) );

	// clean first
	m_wndStatic.SetWindowText( _T("") );
	m_wndEdit.SetWindowText( _T("") );
	m_wndCombo.ResetContent();

	// notify
	Notify( TLN_BEGINCONTROL, m_pModifyItem, iCol );

	// get text rect
	CRect rcText;
	GetItemRect( pItem, iCol, &rcText, TRUE );

	// begin a control
	switch( GetColumnModify( iCol ) )
	{
	case TLM_STATIC:
		BeginStatic( pItem, iCol, rcText );
		break;

	case TLM_EDIT:
		BeginEdit( pItem, iCol, rcText );
		break;

	case TLM_COMBO:
		rcText.OffsetRect( 0, -1 );
		BeginCombo( pItem, iCol, rcText );
		break;

	default:
		break;
	}

	return TRUE;
}

BOOL CTreeListCtrl::CancelControl()
{
	// end modify a column of an item
	ASSERT( GetState( TLS_MODIFY ) );

	// cancel a control
	switch( GetColumnModify( m_iModifyCol ) )
	{
	case TLM_STATIC:
		CancelStatic();
		break;

	case TLM_EDIT:
		CancelEdit();
		break;

	case TLM_COMBO:
		CancelCombo();
		break;

	default:
		break;
	}

	// notify
	Notify( TLN_ENDCONTROL, m_pModifyItem, m_iModifyCol );

	return TRUE;
}

BOOL CTreeListCtrl::RestoreControl( CTreeListItem* pItem, int iCol )
{
	// restore a modify control
	ASSERT( GetState( TLS_MODIFY ) );

	// get text rect
	CRect rcText;
	GetItemRect( pItem, iCol, &rcText, TRUE );

	// restore a control
	switch( GetColumnModify( iCol ) )
	{
	case TLM_STATIC:
		RestoreStatic( pItem, iCol, rcText );
		break;

	case TLM_EDIT:
		RestoreEdit( pItem, iCol, rcText );
		break;

	case TLM_COMBO:
		RestoreCombo( pItem, iCol, rcText );
		break;

	default:
		break;
	}

	return TRUE;
}

BOOL CTreeListCtrl::BeginStatic( CTreeListItem* pItem, int iCol, CRect rcText )
{
	// begin static a column of an item
	ASSERT( 0 <= iCol && iCol <= m_arColumns.GetSize() );

	if( rcText.IsRectEmpty() )
		return FALSE;

	CTreeListColumnInfo* pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];
	int nMin = GetStringWidth( pItem->GetText( iCol ) );
	DWORD dwStyle = 0;

	if( rcText.Width() < pColumnInfo->GetMinWidth() )
		rcText.right = rcText.left + pColumnInfo->GetWidth();

	if( rcText.Width() < nMin )
		rcText.right = rcText.left + pColumnInfo->GetWidth();

	if( GetStyle()&TLC_HGRID )
		rcText.top--;

	if( GetStyle()&TLC_VGRID )
		rcText.left--;

	if( pColumnInfo->GetFormat()&TLF_TEXTALIGN_LEFT )
		dwStyle |= SS_LEFT;
	else if( pColumnInfo->GetFormat()&TLF_TEXTALIGN_RIGHT )
		dwStyle |= SS_RIGHT;
	else if( pColumnInfo->GetFormat()&TLF_TEXTALIGN_CENTER )
		dwStyle |= SS_CENTER;
	else
		dwStyle |= SS_LEFT;

	m_pModifyItem	= pItem;
	m_iModifyCol	= iCol;

	m_wndStatic.ModifyStyle( SS_LEFT|SS_RIGHT|SS_CENTER, 0, SS_LEFT|SS_RIGHT|SS_CENTER );
	m_wndStatic.ModifyStyle( 0, dwStyle, dwStyle );
	m_wndStatic.MoveWindow( rcText );
	m_wndStatic.EnableWindow( TRUE );
	m_wndStatic.SetWindowText( GetItemText( pItem, iCol ) );
	m_wndStatic.ShowWindow( SW_SHOW );
	m_wndStatic.SetFocus();

	return TRUE;
}

BOOL CTreeListCtrl::CancelStatic()
{
	// cancel an static control
	m_wndStatic.ShowWindow( SW_HIDE );
	m_wndStatic.EnableWindow( FALSE );

	return TRUE;
}

BOOL CTreeListCtrl::RestoreStatic( CTreeListItem* pItem, int iCol, CRect rcText )
{
	// restore an static control
	ASSERT( m_pModifyItem	== pItem );
	ASSERT(m_iModifyCol		== iCol  );

	m_wndStatic.MoveWindow( rcText );
	m_wndStatic.EnableWindow( TRUE );
	m_wndStatic.ShowWindow( SW_SHOW );
	m_wndStatic.SetFocus();

	return TRUE;
}

BOOL CTreeListCtrl::BeginEdit( CTreeListItem* pItem, int iCol, CRect rcText )
{
	// begin edit a column of an item
	ASSERT( 0 <= iCol && iCol <= m_arColumns.GetSize() );

	if( rcText.IsRectEmpty() )
		return FALSE;

	CTreeListColumnInfo* pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];
	int nMin = GetStringWidth( pItem->GetText( iCol ) );
	DWORD dwStyle = 0;

	if( rcText.Width() < pColumnInfo->GetMinWidth() )
		rcText.right = rcText.left + pColumnInfo->GetWidth();

	if( rcText.Width() < nMin )
		rcText.right = rcText.left + pColumnInfo->GetWidth();

	if( GetStyle()&TLC_HGRID )
		rcText.top--;

	if( GetStyle()&TLC_VGRID )
		rcText.left--;

	if( pColumnInfo->GetFormat()&TLF_TEXTALIGN_LEFT )
		dwStyle |= ES_LEFT;
	else if( pColumnInfo->GetFormat()&TLF_TEXTALIGN_RIGHT )
		dwStyle |= ES_RIGHT;
	else if( pColumnInfo->GetFormat()&TLF_TEXTALIGN_CENTER )
		dwStyle |= ES_CENTER;
	else
		dwStyle |= ES_LEFT;

	m_pModifyItem	= pItem;
	m_iModifyCol	= iCol;

	m_wndEdit.ModifyStyle( ES_LEFT|ES_RIGHT|ES_CENTER, 0, ES_LEFT|ES_RIGHT|ES_CENTER );
	m_wndEdit.ModifyStyle( 0, dwStyle, dwStyle );
	m_wndEdit.MoveWindow( rcText );
	m_wndEdit.EnableWindow( TRUE );
	m_wndEdit.SetWindowText( GetItemText( pItem, iCol ) );
	m_wndEdit.SetSel( 0, -1 );
	m_wndEdit.ShowWindow( SW_SHOW );
	m_wndEdit.SetFocus();

	return TRUE;
}

BOOL CTreeListCtrl::CancelEdit()
{
	// cancel an edit control
	CString strText;
	m_wndEdit.GetWindowText( strText );

	m_pModifyItem->SetText( strText, m_iModifyCol );

	m_wndEdit.ShowWindow( SW_HIDE );
	m_wndEdit.EnableWindow( FALSE );

	return TRUE;
}

BOOL CTreeListCtrl::RestoreEdit( CTreeListItem* pItem, int iCol, CRect rcText )
{
	// restore an edit control
	ASSERT( m_pModifyItem	== pItem );
	ASSERT(m_iModifyCol		== iCol  );

	m_wndEdit.MoveWindow( rcText );
	m_wndEdit.EnableWindow( TRUE );
	m_wndEdit.ShowWindow( SW_SHOW );
	m_wndEdit.SetFocus();

	return TRUE;
}

BOOL CTreeListCtrl::BeginCombo( CTreeListItem* pItem, int iCol, CRect rcText )
{
	// begin combo a column of an item
	ASSERT( 0 <= iCol && iCol <= m_arColumns.GetSize() );

	if( rcText.IsRectEmpty() )
		return FALSE;

	rcText.bottom += GetItemHeight() * 6;

	CTreeListColumnInfo* pColumnInfo = (CTreeListColumnInfo*)m_arColumns[iCol];
	int nMin = GetStringWidth( pItem->GetText( iCol ) );
	DWORD dwStyle = 0;

	m_pModifyItem	= pItem;
	m_iModifyCol	= iCol;

	CString strInit = GetColumnDefaultText( iCol );
	CString strItem;

	int nBeg = 0;
	int nEnd = strInit.Find( _T("|"), nBeg );
	while( nEnd != -1 )
	{
		strItem = strInit.Mid( nBeg, nEnd-nBeg );
		m_wndCombo.InsertString( -1, strItem );
		nBeg = nEnd + 1;
		nEnd = strInit.Find( _T("|"), nBeg );
	}
	strItem = strInit.Mid( nBeg );
	m_wndCombo.InsertString( -1, strItem );

	m_wndCombo.MoveWindow( rcText );
	m_wndCombo.EnableWindow( TRUE );
	if( m_wndCombo.SelectString( -1, GetItemText( pItem, iCol ) ) == -1 )
	{
		m_wndCombo.InsertString( 0, GetItemText( pItem, iCol ) );
		m_wndCombo.SelectString( -1, GetItemText( pItem, iCol ) );
	}

	m_wndCombo.ShowWindow( SW_SHOW );
	m_wndCombo.SetFocus();

	return TRUE;
}

BOOL CTreeListCtrl::CancelCombo()
{
	// cancel a combo control
	CString strText;
	m_wndCombo.GetWindowText( strText );

	m_pModifyItem->SetText( strText, m_iModifyCol );

	m_wndCombo.ShowWindow( SW_HIDE );
	m_wndCombo.EnableWindow( FALSE );

	return TRUE;
}

BOOL CTreeListCtrl::RestoreCombo( CTreeListItem* pItem, int iCol, CRect rcText)
{
	// restore a combo control
	ASSERT( m_pModifyItem	== pItem );
	ASSERT(m_iModifyCol		== iCol  );

	m_wndCombo.MoveWindow( rcText );
	m_wndCombo.EnableWindow( TRUE );
	m_wndCombo.ShowWindow( SW_SHOW );
	m_wndCombo.SetFocus();

	return TRUE;
}

BOOL CTreeListCtrl::BeginDraging( CPoint point )
{
	// begin a draging
	ASSERT( GetSelectedItem() != NULL );
	
	if( !(GetStyle()&TLC_DRAG) )
		return FALSE;

	LRESULT lResult = NotifyDrop( TLN_BEGINDRAG, this, NULL );
	if( lResult < 0 )
		return FALSE;

	SetState( TLS_DRAG );
	
	m_ptBegin = point;
	m_ptDelta.x = -160;
	m_ptDelta.y = -160;

	return TRUE;
}

BOOL CTreeListCtrl::EndDraging( CPoint point )
{
	// end a draging
	ASSERT( GetStyle()&TLC_DRAG );

	if( m_pDragWnd != NULL )
	{
		m_pDragWnd->Hide();
		m_pDragWnd->DestroyWindow();
		delete m_pDragWnd;
		m_pDragWnd = NULL;
	}

	if( m_pDropWnd != NULL )
	{
		m_pDropWnd->Hide();
		m_pDropWnd->DestroyWindow();
		delete m_pDropWnd;
		m_pDropWnd = NULL;
	}
	
	ClientToScreen( &point );

	CWnd* pWnd;
	pWnd = CWnd::WindowFromPoint( point );
	if( pWnd != NULL && pWnd->IsKindOf( RUNTIME_CLASS(CTreeListCtrl) ) )
	{
		CTreeListCtrl* pTargetWnd;
		pTargetWnd = (CTreeListCtrl*)pWnd;
		pTargetWnd->Drop( this, point );
	}

	SetState( 0, TLS_DRAG );
	
	return TRUE;
}

BOOL CTreeListCtrl::EndDraging()
{
	// cancel a draging
	ASSERT( GetStyle()&TLC_DRAG );

	if( m_pDragWnd != NULL )
	{
		m_pDragWnd->Hide();
		m_pDragWnd->DestroyWindow();
		delete m_pDragWnd;
		m_pDragWnd = NULL;
	}

	if( m_pDropWnd != NULL )
	{
		m_pDropWnd->Hide();
		m_pDropWnd->DestroyWindow();
		delete m_pDropWnd;
		m_pDropWnd = NULL;
	}

	if( m_pTargetWnd != NULL && m_pTargetWnd->IsKindOf( RUNTIME_CLASS( CTreeListCtrl ) ) )
	{
		m_pTargetWnd->DragLeave( this );
		m_pTargetWnd = NULL;
	}

	SetState( 0, TLS_DRAG );
	return TRUE;
}

BOOL CTreeListCtrl::DoDraging( CPoint point )
{
	// draging
	ASSERT( GetStyle()&TLC_DRAG );

	if( m_pDragWnd == NULL )
	{
		int cx = GetSystemMetrics( SM_CXDRAG );
		int cy = GetSystemMetrics( SM_CYDRAG );

		CRect rcDrag;
		rcDrag.SetRect( -cx, -cy, cx, cy );
		rcDrag.OffsetRect( m_ptBegin );

		if( !rcDrag.PtInRect( point ) )
		{
			CRect rcDragWnd;
			rcDragWnd.SetRect( 0, 0, 320, 320 );
			rcDragWnd.OffsetRect( point );
			rcDragWnd.OffsetRect( m_ptDelta );
			ClientToScreen( rcDragWnd );

			m_pDragWnd = new CTLCDragWnd;
			m_pDragWnd->Create( rcDragWnd, this );
			m_pDragWnd->Show();

			m_pDropWnd = new CTLCDropWnd;
			m_pDropWnd->Create( this );

			DoDraging( point );
		}
	}
	else
	{
		CRect rcDragWnd;
		m_pDragWnd->GetClientRect( &rcDragWnd );
		rcDragWnd.OffsetRect( point );
		if( m_pDragWnd->m_bLayeredWindows )
			rcDragWnd.OffsetRect( m_ptDelta );
		else
			rcDragWnd.OffsetRect( 20, 4 );

		ClientToScreen( rcDragWnd );

		m_pDragWnd->MoveWindow( rcDragWnd );

		CPoint pt;
		pt = point;
		ClientToScreen( &pt );

		CWnd* pWnd;
		pWnd = CWnd::WindowFromPoint( pt );
		if( pWnd != NULL && pWnd->IsKindOf( RUNTIME_CLASS(CTreeListCtrl) ) )
		{
			CTreeListCtrl* pTargetWnd;
			pTargetWnd = (CTreeListCtrl*)pWnd;

			if( m_pTargetWnd != NULL && m_pTargetWnd != pTargetWnd )
			{
				m_pTargetWnd->DragLeave( this );
				m_pTargetWnd = NULL;
			}

			if( m_pTargetWnd == NULL && pTargetWnd->DragEnter( this ))
			{
				m_pTargetWnd = pTargetWnd;
			}

			if( m_pTargetWnd != NULL )
			{
				CTreeListItem* pItem = NULL;
				CRect rcItem;
				CRect rcClient;
				int nDrag = m_pTargetWnd->DragOver( this, pt, &pItem );
				switch( nDrag )
				{
				case DROP_NONE:
					SetCursor( m_hStop );
					m_pDropWnd->Hide();
					break;

				case DROP_SELF:
					SetCursor( m_hArrow );
					m_pDropWnd->Hide();
					break;

				case DROP_ITEM:
					SetCursor( m_hDrop );
					m_pTargetWnd->GetItemRect( pItem, &rcItem );
					m_pTargetWnd->ClientToScreen( &rcItem );
					m_pTargetWnd->GetClientRect( &rcClient );
					m_pTargetWnd->ClientToScreen( &rcClient );
					m_pDropWnd->Show( CPoint( rcClient.left, ( rcItem.top + rcItem.bottom ) / 2 ) );
					break;

				case DROP_ROOT:
					SetCursor( m_hDrop );
					m_pTargetWnd->GetItemRect( pItem, &rcItem );
					m_pTargetWnd->ClientToScreen( &rcItem );
					m_pTargetWnd->GetClientRect( &rcClient );
					m_pTargetWnd->ClientToScreen( &rcClient );
					m_pDropWnd->Show( CPoint( rcClient.left, ( rcItem.top + rcItem.bottom ) / 2 ) );
					break;

				default:
					ASSERT( FALSE );
					break;
				}
			}
			else
			{
				SetCursor( m_hStop );
				m_pDropWnd->Hide();
			}
		}
		else
		{
			if( m_pTargetWnd != NULL )
			{
				m_pTargetWnd->DragLeave( this );
				m_pTargetWnd = NULL;
			}
			SetCursor( m_hStop );
			m_pDropWnd->Hide();
		}
	}

	return TRUE;
}

void CTreeListCtrl::ExchangeItem( CTreeListItem* pItemA, CTreeListItem* pItemB )
{
	// exchange itemA and itemB ( the same parent )
	ASSERT( pItemA != NULL && pItemB != NULL );

	if( pItemA == pItemB )
		return;

	if( pItemA->m_pParent != pItemB->m_pParent )
		return;

	CTreeListItem* pParentA;
	CTreeListItem* pParentB;

	pParentA = pItemA->m_pParent;
	pParentB = pItemB->m_pParent;

	if( pParentA->m_pChild == pItemA )
	{
		pParentA->m_pChild = pItemB;
	}
	else if( pParentB->m_pChild == pItemB )
	{
		pParentB->m_pChild = pItemA;
	}

	if( pItemA->m_pNext == pItemB )
	{
		pItemA->m_pNext = pItemB->m_pNext;
		pItemB->m_pPrev = pItemA->m_pPrev;

		pItemA->m_pPrev->m_pNext = pItemB;
		pItemB->m_pNext->m_pPrev = pItemA;
		
		pItemA->m_pPrev = pItemB;
		pItemB->m_pNext = pItemA;
	}
	else if( pItemA->m_pPrev == pItemB )
	{
		pItemB->m_pNext	= pItemA->m_pNext;
		pItemA->m_pPrev = pItemB->m_pPrev;

		pItemB->m_pPrev->m_pNext = pItemA;
		pItemA->m_pNext->m_pPrev = pItemB;

		pItemB->m_pPrev = pItemA;
		pItemA->m_pNext	= pItemB;
	}
	else
	{
		CTreeListItem* pPrevA;
		CTreeListItem* pPrevB;

		pPrevA	= pItemA->m_pPrev;
		pPrevB	= pItemB->m_pPrev;

		pItemA->m_pPrev	= pPrevB;
		pItemB->m_pPrev = pPrevA;

		if( pPrevA != NULL )
			pPrevA->m_pNext	= pItemB;

		if( pPrevB != NULL )
			pPrevB->m_pNext	= pItemA;

		CTreeListItem* pNextA;
		CTreeListItem* pNextB;

		pNextA	= pItemA->m_pNext;
		pNextB	= pItemB->m_pNext;

		pItemA->m_pNext	= pNextB;
		pItemB->m_pNext	= pNextA;

		if( pNextA != NULL )
			pNextA->m_pPrev	= pItemB;

		if( pNextB != NULL )
			pNextB->m_pPrev = pItemA;
	}

	Invalidate();

	return;
}

void CTreeListCtrl::MoveAfterItem( CTreeListItem* pItem, CTreeListItem* pAfter )
{
	// move pItemA after pAfter ( the same parent )
	ASSERT( pItem != NULL );

	CTreeListItem* pParent;
	CTreeListItem* pFirst;
	CTreeListItem* pPrev;
	CTreeListItem* pNext;
		 
	pParent = pItem->m_pParent;
	pFirst = pParent->m_pChild;
	pPrev = pItem->m_pPrev;
	pNext = pItem->m_pNext;

	if( pAfter == NULL )
	{
		if( pParent->m_pChild == pItem )
			return;
	}
	else
	{
		if( pItem == pAfter )
			return;
	}

	if( pParent->m_pChild == pItem )
		pParent->m_pChild = pItem->m_pNext;

	if( pPrev != NULL )
		pPrev->m_pNext = pItem->m_pNext;

	if( pNext != NULL )
		pNext->m_pPrev = pItem->m_pPrev;

	if( pAfter == NULL )
	{
		pParent->m_pChild = pItem;

		pItem->m_pPrev = pFirst->m_pPrev;

		pItem->m_pNext = pFirst;
		pFirst->m_pPrev = pItem;
	}
	else
	{
		ASSERT( pParent == pAfter->m_pParent );
		
		pPrev = pAfter;
		pNext = pAfter->m_pNext;

		pItem->m_pPrev = pPrev;
		pPrev->m_pNext = pItem;

		pItem->m_pNext = pNext;
		if( pNext != NULL )
			pNext->m_pPrev = pItem;
	}

	Invalidate();

	return;
}

BOOL CTreeListCtrl::DragEnter( CTreeListCtrl* pTreeListCtrl )
{
	// drag enter
	if( !(GetStyle()&TLC_DROP) )
		return FALSE;

	LRESULT lResult = NotifyDrop( TLN_DRAGENTER, pTreeListCtrl, NULL );
	if( lResult < 0 )
		return FALSE;

	return TRUE;
}

BOOL CTreeListCtrl::DragLeave( CTreeListCtrl* pTreeListCtrl )
{
	// drag leave
	NotifyDrop( TLN_DRAGLEAVE, pTreeListCtrl, NULL );
	SetTargetItem( NULL );
	SetHoverItem( NULL );
	return TRUE;
}

int CTreeListCtrl::DragOver( CTreeListCtrl* pTreeListCtrl, CPoint point, CTreeListItem** pp )
{
	// drag over
	ASSERT( pTreeListCtrl != NULL );
	ASSERT_VALID( pTreeListCtrl );

	LRESULT lResult;
	CTreeListItem* pItem;
	CTreeListItem* pSelItem;

	ScreenToClient( &point );
	pItem = HitTest( point );

	if( pp != NULL )
		*pp = pItem;

	int nDropEffect;

	if( pTreeListCtrl != this )
	{
		if( GetStyle()&TLC_DROP )
		{
			if( pItem != NULL )
			{
				lResult = NotifyDrop( TLN_DRAGOVER, pTreeListCtrl, pItem );
				if( lResult >= 0 )
					nDropEffect = DROP_ITEM;
				else
					nDropEffect = DROP_NONE;
			}
			else
			{
				if( GetStyle()&TLC_DROPROOT )
					nDropEffect = DROP_ROOT;
				else
					nDropEffect = DROP_NONE;
			}
		}
		else
		{
			nDropEffect = DROP_NONE;
		}
	}
	else
	{
		if( GetStyle()&TLC_DROP && GetStyle()&TLC_DROPTHIS )
		{
			if( pItem != NULL )
			{
				if( !IsInSelectsTree( pItem ) )
				{
					lResult = NotifyDrop( TLN_DRAGOVER, pTreeListCtrl, pItem );
					if( lResult >= 0 )
						nDropEffect = DROP_ITEM;
					else
						nDropEffect = DROP_NONE;
				}
				else
				{
					nDropEffect = DROP_SELF;
				}
			}
			else
			{
				if( GetStyle()&TLC_DROPROOT )
				{
					pSelItem = (CTreeListItem*)m_arSelects[0];
					if( pSelItem->m_pParent != m_pRootItem )
						nDropEffect = DROP_ROOT;
					else
						nDropEffect = DROP_SELF;
				}
				else
				{
					nDropEffect = DROP_SELF;
				}
			}
		}
		else
		{
			nDropEffect = DROP_SELF;
		}
	}

	switch( nDropEffect )
	{
	case DROP_NONE:
		SetTargetItem( NULL );
		SetHoverItem( pItem );
		if( GetStyle()&TLC_TREELIST )
		{
			SetTimer( 2, 100, NULL );
			SetTimer( 1, 500, NULL );
		}
		break;

	case DROP_SELF:
	case DROP_ROOT:
		SetTargetItem( NULL );
		SetHoverItem( NULL );
		break;

	case DROP_ITEM:
		SetTargetItem( pItem );
		SetHoverItem( pItem );
		if( GetStyle()&TLC_TREELIST )
		{
			SetTimer( 2, 200, NULL );
			SetTimer( 1,1000, NULL );
		}
		break;

	default:
		ASSERT( FALSE );
		break;
	}

	return nDropEffect;
}

int CTreeListCtrl::Drop( CTreeListCtrl* pTreeListCtrl, CPoint point )
{
	int		nDrag;
	LRESULT lResult;

	CTreeListItem* pItem;

	nDrag = DragOver( pTreeListCtrl, point, &pItem );
	DragLeave( pTreeListCtrl );
	switch( nDrag )
	{
	case DROP_NONE:
	case DROP_SELF:
		break;

	case DROP_ITEM:
	case DROP_ROOT:
		lResult = NotifyDrop( TLN_DROP, pTreeListCtrl, pItem );
		break;

	default:
		ASSERT( FALSE );
		break;
	}
	return 0;
}

BOOL CTreeListCtrl::IsInSelectsTree( CTreeListItem* pItem )
{
	ASSERT( pItem != NULL );
	ASSERT( m_arSelects.GetSize() > 0 );
	
	CTreeListItem* pSelItem;

	pSelItem	= (CTreeListItem*)m_arSelects[0];

	while( pItem->m_nLevel > pSelItem->m_nLevel )
	{
		pItem = pItem->m_pParent;
	}
	
	BOOL bFound = FALSE;
	for( int iSel = 0; iSel < m_arSelects.GetSize(); iSel++ )
	{
		pSelItem = (CTreeListItem*)m_arSelects[iSel];
		if( pItem == pSelItem )
		{
			bFound = TRUE;
			break;
		}
	}

	return bFound;
}

void CTreeListCtrl::OnTimer(UINT nIDEvent) 
{
	CPoint point;
	CTreeListItem* pItem;
	int nItem;
	int nPosition;
	int nPage;

	switch( nIDEvent )
	{
	case 1:
		::GetCursorPos( &point );
		ScreenToClient( &point );
		pItem = HitTest( point  );

		if( pItem == m_pHoverItem )
		{
			Expand( pItem, TLE_EXPAND );
		}

		KillTimer( 1 );

		break;

	case 2:
		nPosition	= GetScrollPos( SB_VERT );
		nPage		= GetCountPerPage(); 

		::GetCursorPos( &point );
		ScreenToClient( &point );
		pItem = HitTest( point );

		nItem = GetTreeListItem( pItem );
		if( nItem == 0 )
		{
			KillTimer( 2 );
		}
		else if( nItem == nPosition )
		{
			KillTimer( 1 );
			SendMessage( WM_VSCROLL, (WPARAM)SB_LINEUP );
			pItem = HitTest( point );
			SetHoverItem( pItem );

			if( m_pDropWnd != NULL )
				m_pDropWnd->Hide();
		}
		else if( nItem >= nPosition + nPage - 1 )
		{
			KillTimer( 1 );
			SendMessage( WM_VSCROLL, (WPARAM)SB_LINEDOWN );
			pItem = HitTest( point );
			SetHoverItem( pItem );

			if( m_pDropWnd != NULL )
				m_pDropWnd->Hide();
		}
		else
		{
			KillTimer( 2 );
		}

		break;

	default:
		break;
	}
	
	CWnd::OnTimer(nIDEvent);
}

void CTreeListCtrl::OnCancelMode() 
{
	// cancel internal event
	if( GetState( TLS_DRAG ) )
	{
		ASSERT( GetState( TLS_CAPTURE ) );
		EndDraging();
	}

	if( GetState( TLS_CAPTURE ) )
	{
		ReleaseCapture();
		SetState( 0, TLS_CAPTURE );
	}

	ASSERT( !GetState( TLS_CAPTURE ) );
	CWnd::OnCancelMode();
}
