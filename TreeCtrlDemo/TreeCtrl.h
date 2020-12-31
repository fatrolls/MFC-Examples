/////////////////////////////////////////////////////////////////////////////
// 
// CTreeCtrl - A WTL tree control with Windows Vista style item selection.
//
// Revision:      1.2
// Last modified: 5th April 2006
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atltheme.h>

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

class CTreeCtrl : public CWindowImpl< CTreeCtrl, CTreeViewCtrl >,
				  public CCustomDraw< CTreeCtrl >,
				  public CDoubleBufferImpl< CTreeCtrl >
{
public:
	CTreeCtrl()
	{
		m_bShowThemed = TRUE;
		m_bMultipleSelect = FALSE;
		m_bCtrlKey = FALSE;
		m_bShiftKey = FALSE;
		m_hFirstSelected = NULL;
	}
	
	~CTreeCtrl()
	{
	}

protected:
	BOOL m_bShowThemed;
	BOOL m_bMultipleSelect;
	BOOL m_bCtrlKey;
	BOOL m_bShiftKey;
	HTREEITEM m_hFirstSelected;
	
	COLORREF m_rgbBackground;
	COLORREF m_rgbItemText;
	COLORREF m_rgbSelectOuter;
	COLORREF m_rgbSelectInner;
	COLORREF m_rgbSelectTop;
	COLORREF m_rgbSelectBottom;
	COLORREF m_rgbNoFocusTop;
	COLORREF m_rgbNoFocusBottom;
	COLORREF m_rgbNoFocusOuter;
	COLORREF m_rgbNoFocusInner;
	
	CFont m_fntTreeFont;
	
public:
	BOOL Initialise()
	{
		// load interface settings
		if ( !LoadSettings() )
			return FALSE;
		
		// give control a static border
		ModifyStyle( WS_BORDER, WS_CLIPCHILDREN | TVS_SHOWSELALWAYS, SWP_FRAMECHANGED );
		ModifyStyleEx( WS_EX_CLIENTEDGE, WS_EX_STATICEDGE, SWP_FRAMECHANGED );
		
		return TRUE;
	}

	BOOL SubclassWindow( HWND hWnd )
	{
		return CWindowImpl< CTreeCtrl, CTreeViewCtrl >::SubclassWindow( hWnd ) ? Initialise() : FALSE;
	}
	
	void ShowThemed( BOOL bShowThemed = TRUE )
	{
		m_bShowThemed = bShowThemed;
		Invalidate();
	}
	
	void SetMultipleSelect( BOOL bMultipleSelect )
	{
		m_bMultipleSelect = bMultipleSelect;
	}
	
	BOOL SelectItem( HTREEITEM hItem )
	{
		if ( m_bMultipleSelect )
			SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
		return CWindowImpl< CTreeCtrl, CTreeViewCtrl >::SelectItem( hItem );
	}

	void GetSelectedItems( CSimpleArray < HTREEITEM >& aSelectedItems )
	{
		aSelectedItems.RemoveAll();
		
		if ( !m_bMultipleSelect )
		{
			aSelectedItems.Add( GetSelectedItem() );
			return;
		}
		
		// get all selected tree items (recursive)
		GetSelectedItems( GetRootItem(), aSelectedItems );
	}
		
	HTREEITEM GetSelectedItems( HTREEITEM hItem, CSimpleArray < HTREEITEM >& aSelectedItems )
	{
		if ( hItem == NULL )
			return NULL;
		
		// first scan siblings
		HTREEITEM hSelectedItem = GetNextSiblingItem( hItem );
		
		if ( hSelectedItem != NULL )
		{
			hSelectedItem = GetSelectedItems( hSelectedItem, aSelectedItems );
			if ( hSelectedItem != NULL )
				return hSelectedItem;
		}
		
		// then scan next children
		hSelectedItem = GetChildItem( hItem );
		
		if ( hSelectedItem != NULL )
		{
			hSelectedItem = GetSelectedItems( hSelectedItem, aSelectedItems );
			if ( hSelectedItem != NULL )
				return hSelectedItem;
		}
		
		// add selected to list
		if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
			aSelectedItems.Add( hItem );
		
		// continue searching
		return hSelectedItem;
	}

	void ResetSelected( HTREEITEM hItem )
	{
		for ( ; hItem != NULL; hItem = GetNextSiblingItem( hItem ) )
		{
			ResetSelected( GetChildItem( hItem ) );
			SetItemState( hItem, 0, TVIS_SELECTED );
		}
	}

	BOOL SelectItems( HTREEITEM hItemFrom, HTREEITEM hItemTo )
	{
		BOOL bSelectItem = FALSE;
		
		// select range of visible items
		for ( HTREEITEM hItem = GetRootItem(); hItem != NULL; hItem = GetNextVisibleItem( hItem ) )
		{
			if ( hItemFrom == hItemTo )
				bSelectItem = FALSE;
			else if ( hItem == hItemFrom || hItem == hItemTo )
				bSelectItem = !bSelectItem;
			SetItemState( hItem, hItem == hItemFrom || hItem == hItemTo || bSelectItem ? TVIS_SELECTED : 0, TVIS_SELECTED );
		}
		
		Invalidate();

		return TRUE;
	}
	
	BOOL LoadSettings()
	{
		m_rgbBackground = GetSysColor( COLOR_WINDOW );
		m_rgbItemText = GetSysColor( COLOR_WINDOWTEXT );
		m_rgbSelectOuter = RGB( 170, 200, 245 );
		m_rgbSelectInner = RGB( 230, 250, 250 );
		m_rgbSelectTop = RGB( 210, 240, 250 );
		m_rgbSelectBottom = RGB( 185, 215, 250 );
		m_rgbNoFocusTop = RGB( 250, 250, 250 );
		m_rgbNoFocusBottom = RGB( 235, 235, 235 );
		m_rgbNoFocusOuter = RGB( 220, 220, 220 );
		m_rgbNoFocusInner = RGB( 245, 245, 245 );
		
		// get system message font
		CLogFont logFont;
		logFont.SetMessageBoxFont();
		if ( !m_fntTreeFont.IsNull() )
			m_fntTreeFont.DeleteObject();
		if ( m_fntTreeFont.CreateFontIndirect( &logFont ) == NULL )
			return FALSE;
		
		return TRUE;
	}
	
	BEGIN_MSG_MAP_EX(CTreeCtrl)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_SETFOCUS(OnSetFocus)
		MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_KEYDOWN(OnKeyDown)
		MSG_WM_SETTINGCHANGE(OnSettingsChange)
		MSG_WM_SYSCOLORCHANGE(OnSettingsChange)
		MSG_WM_FONTCHANGE(OnSettingsChange)
		MSG_WM_THEMECHANGED(OnSettingsChange)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(NM_DBLCLK, OnDblClick)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(TVN_BEGINDRAG, OnBeginDrag)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		CHAIN_MSG_MAP_ALT(CCustomDraw< CTreeCtrl >, 1)
		CHAIN_MSG_MAP(CDoubleBufferImpl< CTreeCtrl >)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP_EX()
	
	int OnCreate( LPCREATESTRUCT lpCreateStruct )
	{
		SetMsgHandled( FALSE );
		return Initialise() ? 0 : -1;
	}
	
	void OnSettingsChange( UINT nFlags, LPCTSTR lpszSection )
	{
		OnSettingsChange();
	}
	
	void OnSettingsChange()
	{
		LoadSettings();
		Invalidate();
	}
	
	void OnSetFocus( HWND hOldWnd )
	{
		SetMsgHandled( FALSE );
		Invalidate();
	}

	void OnKillFocus( HWND hNewWnd )
	{
		SetMsgHandled( FALSE );
		Invalidate();
	}

	void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags )
	{
		if ( m_bMultipleSelect && ( nChar == VK_UP || nChar == VK_DOWN ) )
		{
			if ( GetKeyState( VK_SHIFT ) & 0x8000 )
			{
				// initialise the reference item if this is the first shift selection
				if ( m_hFirstSelected == NULL )
					m_hFirstSelected = GetSelectedItem();

				// find which item is currently selected
				HTREEITEM hPrevItem = GetSelectedItem();
				HTREEITEM hItemNext = nChar == VK_UP ? GetPrevVisibleItem( hPrevItem ) : GetNextVisibleItem( hPrevItem );
				
				if ( hItemNext != NULL )
				{
					BOOL bSelectItem = !( GetItemState( hItemNext, TVIS_SELECTED ) & TVIS_SELECTED );

					// select the next item - this will also deselect the previous item
					SelectItem( hItemNext );

					// reselect the previously selected item
					if ( bSelectItem )
						SetItemState( hPrevItem, TVIS_SELECTED, TVIS_SELECTED );
				}
				return;
			}
			else // no shift key
			{
				HTREEITEM hSelectedItem = GetSelectedItem();
				m_hFirstSelected = NULL;
				ResetSelected( GetRootItem() );
				SelectItem( hSelectedItem );
			}
		}
		else if ( nChar == VK_SPACE && ( GetStyle() & TVS_CHECKBOXES ) == TVS_CHECKBOXES )
		{
			HTREEITEM hSelectedItem = GetSelectedItem();
			BOOL bChecked = hSelectedItem == NULL ? FALSE : GetCheckState( hSelectedItem );
			
			CSimpleArray< HTREEITEM > aSelectedItems;
			GetSelectedItems( aSelectedItems );
			
			// set checkbox for all selected items
			for ( int nItem = 0; nItem < aSelectedItems.GetSize(); nItem++ )
			{
				if ( aSelectedItems[ nItem ] != hSelectedItem )
					SetCheckState( aSelectedItems[ nItem ], !bChecked );
			}
		}
		else if ( _istalnum( nChar ) )
		{
			m_hFirstSelected = NULL;
			ResetSelected( GetRootItem() );
		}
		
		SetMsgHandled( FALSE );
	}
	
	LRESULT OnBeginDrag( LPNMHDR lpNMHDR )
	{
		LPNMTREEVIEW lpTreeView = reinterpret_cast<LPNMTREEVIEW>( lpNMHDR );
		
		m_hFirstSelected = NULL;
		ResetSelected( GetRootItem() );
		SelectItem( lpTreeView->itemNew.hItem );
				
		SetMsgHandled( FALSE );
		
		return TRUE;
	}	
	
	LRESULT OnDblClick( LPNMHDR lpNMHDR )
	{
		DWORD dwPoint = GetMessagePos();
		CPoint ptMouse( GET_X_LPARAM( dwPoint ), GET_Y_LPARAM( dwPoint ) );
		ScreenToClient( &ptMouse );
		
		// handle double-clicks (for drawing)
		SendMessage( WM_LBUTTONDOWN, 0, MAKELPARAM( ptMouse.x, ptMouse.y ) );
		SendMessage( WM_LBUTTONUP, 0, MAKELPARAM( ptMouse.x, ptMouse.y ) );
	
		SetMsgHandled( FALSE );
		
		return TRUE;
	}
	
	void OnLButtonDown( UINT nFlags, CPoint point )
	{
		if ( m_bMultipleSelect )
		{
			m_bCtrlKey = ( ( GetKeyState( VK_CONTROL ) & 0x8000 ) != 0 );
			m_bShiftKey = ( ( GetKeyState( VK_SHIFT ) & 0x8000 ) != 0 );
			
			if ( m_bCtrlKey || m_bShiftKey )
				return;
			
			// reset selected item if click on a single item
			HTREEITEM hNewItem = HitTest( point, NULL );
			if ( hNewItem != NULL )
			{
				UINT nNewSelectState = ( GetItemState( hNewItem, TVIS_SELECTED ) & TVIS_SELECTED );
				ResetSelected( GetRootItem() );
				SetItemState( hNewItem, nNewSelectState, TVIS_SELECTED );
				m_hFirstSelected = hNewItem;
			}
		}
		
		SetMsgHandled( FALSE );
	}

	void OnLButtonUp( UINT nFlags, CPoint point )
	{
		SetMsgHandled( FALSE );
		
		if ( !m_bMultipleSelect )
			return;
			
		HTREEITEM hNewItem = HitTest( point, NULL );
		HTREEITEM hOldItem = GetSelectedItem();
		
		if ( m_bCtrlKey )
		{
			if ( hNewItem != NULL )
			{
				UINT nNewSelectState = GetItemState( hNewItem, TVIS_SELECTED ) & TVIS_SELECTED ? 0 : TVIS_SELECTED;
				UINT nOldSelectState = hOldItem == NULL ? 0 : GetItemState( hOldItem, TVIS_SELECTED );
				
				// select new item (to get focus)
				SelectItem( hNewItem );
				
				// set highlight state for new item
				if ( GetItemState( hNewItem, TVIS_SELECTED ) != nNewSelectState )
					SetItemState( hNewItem, nNewSelectState, TVIS_SELECTED );
				
				// restore state of old selected item
				if ( hOldItem != NULL && hOldItem != hNewItem && GetItemState( hOldItem, TVIS_SELECTED ) != nOldSelectState )
					SetItemState( hOldItem, nOldSelectState, TVIS_SELECTED );
				
				m_hFirstSelected = NULL;
			}
		}
		else if ( m_bShiftKey )
		{
			// initialise the reference item if this is the first shift selection
			if ( m_hFirstSelected == NULL )
				m_hFirstSelected = GetSelectedItem();
				
			// select new item (to get focus)
			if ( hOldItem == hNewItem )
				SelectItem( NULL ); // to prevent edit

			if ( m_hFirstSelected != NULL )
				SelectItems( m_hFirstSelected, hNewItem );
		}
		
		m_bCtrlKey = FALSE;
		m_bShiftKey = FALSE;
	}
	
	void DoPaint( CDCHandle dcPaint )
	{
		// default paint handlers will call custom draw
		DefWindowProc( WM_ERASEBKGND, (WPARAM)dcPaint.m_hDC, 0 );
		DefWindowProc( WM_PAINT, (WPARAM)dcPaint.m_hDC, 0 );
	}
	
	DWORD OnPrePaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw )
	{		
	    return m_bShowThemed ? CDRF_NOTIFYITEMDRAW : CDRF_DODEFAULT;
	}
	
	DWORD OnItemPrePaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw )
	{
		return m_bShowThemed ? CDRF_NOTIFYPOSTPAINT : CDRF_DODEFAULT;
	}
	
	DWORD OnItemPostPaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw )
	{
		LPNMLVCUSTOMDRAW lpCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>( lpNMCustomDraw );
		
		CRect rcItem;
		if ( !GetItemRect( (HTREEITEM)lpCustomDraw->nmcd.dwItemSpec, rcItem, TRUE ) )
			return CDRF_DODEFAULT;
		
		CDCHandle dcPaint( lpCustomDraw->nmcd.hdc );
		int nContextState = dcPaint.SaveDC();
		
		dcPaint.SetBkColor( m_rgbBackground );
		dcPaint.ExtTextOut( rcItem.left, rcItem.top, ETO_OPAQUE, rcItem, _T( "" ), 0, NULL );
		
		// only one item is selected at any one time
		BOOL bSelected = ( GetItemState( (HTREEITEM)lpCustomDraw->nmcd.dwItemSpec, TVIS_SELECTED | TVIS_DROPHILITED ) & ( TVIS_SELECTED | TVIS_DROPHILITED ) );
		HTREEITEM hHighlightItem = GetDropHilightItem();
		if ( hHighlightItem != NULL && hHighlightItem != (HTREEITEM)lpCustomDraw->nmcd.dwItemSpec )
			bSelected = FALSE;
		
		// draw selected background and border
		if ( bSelected )
		{
			BOOL bControlFocus = ( GetFocus() == m_hWnd );
			CRect rcSelect( rcItem );
			
			CPen penBorder;
			penBorder.CreatePen( PS_SOLID, 1, bControlFocus ? m_rgbSelectOuter : m_rgbNoFocusOuter );
			CBrush bshInterior;
			bshInterior.CreateSolidBrush( m_rgbBackground );
			
			dcPaint.SelectPen( penBorder );
			dcPaint.SelectBrush( bshInterior );
			
			dcPaint.RoundRect( rcSelect, CPoint( 5, 5 ) );
			rcSelect.DeflateRect( 1, 1 );
			
			CPen penInnerBorder;
			penInnerBorder.CreatePen( PS_SOLID, 1, bControlFocus ? m_rgbSelectInner : m_rgbNoFocusInner );
			dcPaint.SelectPen( penInnerBorder );
			
			dcPaint.RoundRect( rcSelect, CPoint( 2, 2 ) );
			rcSelect.DeflateRect( 1, 1 );
			
			GRADIENT_RECT grdRect = { 0, 1 };
			TRIVERTEX triVertext[ 2 ] = {
											rcSelect.left,
											rcSelect.top,
											GetRValue( bControlFocus ? m_rgbSelectTop : m_rgbNoFocusTop ) << 8,
											GetGValue( bControlFocus ? m_rgbSelectTop : m_rgbNoFocusTop ) << 8,
											GetBValue( bControlFocus ? m_rgbSelectTop : m_rgbNoFocusTop ) << 8,
											0x0000,			
											rcSelect.right,
											rcSelect.bottom,
											GetRValue( bControlFocus ? m_rgbSelectBottom : m_rgbNoFocusBottom ) << 8,
											GetGValue( bControlFocus ? m_rgbSelectBottom : m_rgbNoFocusBottom ) << 8,
											GetBValue( bControlFocus ? m_rgbSelectBottom : m_rgbNoFocusBottom ) << 8,
											0x0000
										};
			
			dcPaint.GradientFill( triVertext, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
		}
		
		CString strItemText;
		GetItemText( (HTREEITEM)lpCustomDraw->nmcd.dwItemSpec, strItemText );
		
		if ( !strItemText.IsEmpty() )
		{
			CRect rcItemText( rcItem );
			rcItemText.DeflateRect( 3, 0, 2, 0 );
			
			dcPaint.SelectFont( m_fntTreeFont );
			dcPaint.SetTextColor( m_rgbItemText );
			dcPaint.SetBkMode( TRANSPARENT );
			dcPaint.DrawText( strItemText, strItemText.GetLength(), rcItemText, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER );
		}
		
		dcPaint.RestoreDC( nContextState );
		
		return CDRF_DODEFAULT;
	}
};
