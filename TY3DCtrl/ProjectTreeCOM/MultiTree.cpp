#include "stdafx.h"
#include "MultiTree.h"

#include "CreateCheckboxImageList.h"
CTreeDropTarget::CTreeDropTarget(HWND hTargetWnd, CMultiTree* pTreeCtrl)
    :CIDropTarget(hTargetWnd),m_pSourceTreeCtrl(pTreeCtrl){}	

bool CTreeDropTarget::OnDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium, DWORD *pdwEffect)
{
    if(pFmtEtc->cfFormat == CF_TEXT && medium.tymed == TYMED_HGLOBAL)
    {
        TCHAR* pStr = (TCHAR*)GlobalLock(medium.hGlobal);
        if(pStr != NULL)
        {
            //TVINSERTSTRUCT tvins;
            //tvins.hParent = TVI_ROOT;
            //tvins.hInsertAfter = TVI_LAST;
            //TVITEM tvit={0};
            //tvit.mask = TVIF_TEXT;
            //tvit.pszText = pStr;
            //tvins.item = tvit;
            //TreeView_InsertItem(m_hTargetWnd, &tvins);
        }
        GlobalUnlock(medium.hGlobal);
        //Get the selected item from Source and destination Tree controls 
        HTREEITEM hSelectedItem = m_pSourceTreeCtrl->GetSelectedItem();
        HTREEITEM hTDropItem =m_pSourceTreeCtrl->GetDropHilightItem();

        if(hSelectedItem == hTDropItem)
            return FALSE;

        HTREEITEM hAfter = hTDropItem;
        HTREEITEM hNewParent = m_pSourceTreeCtrl->GetParentItem(hAfter);

        if(!m_pSourceTreeCtrl->DealDragTree(hSelectedItem,hNewParent,hAfter))
            return FALSE;

        HTREEITEM hNewItem = m_pSourceTreeCtrl->MoveBranch(hSelectedItem,hNewParent,hAfter);
        m_pSourceTreeCtrl->DeleteBranch(hSelectedItem);

        //Remove highlighting
        m_pSourceTreeCtrl->SendMessage(TVM_SELECTITEM, TVGN_DROPHILITE,0); 
        m_pSourceTreeCtrl->SelectItem(hNewItem);
        m_pSourceTreeCtrl->OnDragComplete(hNewItem);
    }
    if(pFmtEtc->cfFormat == CF_HDROP && medium.tymed == TYMED_HGLOBAL)
    {
        HDROP hDrop = (HDROP)GlobalLock(medium.hGlobal);
        if(hDrop != NULL)
        {
            TCHAR szFileName[MAX_PATH];

            UINT cFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); 
            for(UINT i = 0; i < cFiles; ++i)
            {
                DragQueryFile(hDrop, i, szFileName, sizeof(szFileName));
                TVINSERTSTRUCT tvins;
                tvins.hParent = TVI_ROOT;
                tvins.hInsertAfter = TVI_LAST;
                TVITEM tvit={0};
                tvit.mask = TVIF_TEXT;
                tvit.pszText = szFileName;
                tvins.item = tvit;
                TreeView_InsertItem(m_hTargetWnd, &tvins);
            }  
            //DragFinish(hDrop); // base class calls ReleaseStgMedium
        }
        GlobalUnlock(medium.hGlobal);
    }
    TreeView_SelectDropTarget(m_hTargetWnd, NULL);
    return true; //let base free the medium
}

HRESULT STDMETHODCALLTYPE CTreeDropTarget::DragOver( 
    /* [in] */ DWORD grfKeyState,
    /* [in] */ POINTL pt,
    /* [out][in] */ DWORD __RPC_FAR *pdwEffect)
{
    TVHITTESTINFO hit;
    hit.pt = (POINT&)pt;
    ScreenToClient(m_hTargetWnd,&hit.pt);
    hit.flags = TVHT_ONITEM;
    HTREEITEM hItem = TreeView_HitTest(m_hTargetWnd,&hit);
    if(hItem != NULL)
    {
        TreeView_Expand(m_hTargetWnd, hItem, TVE_EXPAND);
        TreeView_SelectDropTarget(m_hTargetWnd, hItem);
    }

    // Scroll Tree control depending on mouse position
    WTL::CRect rectClient;
    CWindow wnd = m_hTargetWnd;
    wnd.GetClientRect(&rectClient);
    wnd.ClientToScreen(&rectClient);
    POINT point = (POINT&)pt;
    wnd.ClientToScreen(&point);
    int nScrollDir = -1;
    if ( pt.y >= rectClient.bottom - RECT_BORDER)
        nScrollDir = SB_LINEDOWN;
    else
        if ( (pt.y <= rectClient.top + RECT_BORDER) )
            nScrollDir = SB_LINEUP;


    if ( nScrollDir != -1 ) 
    {
        int nScrollPos = wnd.GetScrollPos(SB_VERT);
        WPARAM wParam = MAKELONG(nScrollDir, nScrollPos);
        wnd.SendMessage(WM_VSCROLL, wParam, 0);
    }

    nScrollDir = -1;
    if ( point.x <= rectClient.left + RECT_BORDER )
        nScrollDir = SB_LINELEFT;
    else
        if ( point.x >= rectClient.right - RECT_BORDER)
            nScrollDir = SB_LINERIGHT;

    if ( nScrollDir != -1 ) 
    {
        int nScrollPos = wnd.GetScrollPos(SB_VERT);
        WPARAM wParam = MAKELONG(nScrollDir, nScrollPos);
        wnd.SendMessage(WM_HSCROLL, wParam, 0);
    }

    return CIDropTarget::DragOver(grfKeyState, pt, pdwEffect);
}
HRESULT STDMETHODCALLTYPE CTreeDropTarget::DragLeave(void)
{
    //SendMessage(m_hTargetWnd, TVM_SELECTITEM, TVGN_DROPHILITE,0);
    TreeView_SelectDropTarget(m_hTargetWnd, NULL);
    return CIDropTarget::DragLeave();
}
///////////////////////////////////////////////////////////////////////////////////

CMultiTree::CMultiTree():m_pDropTarget(NULL)
{
    m_bShowThemed = TRUE;
    m_bMultipleSelect = FALSE;
    m_bCtrlKey = FALSE;
    m_bShiftKey = FALSE;
    m_hFirstSelected = NULL;
    m_uFlags=0;
    m_bEnableDrag = FALSE;
}

CMultiTree::~CMultiTree()
{
}

BOOL CMultiTree::Initialise()
{
    // load interface settings
    if ( !LoadSettings() )
        return FALSE;
    WTL::CBitmap bmp;
    bmp.LoadBitmap (IDB_TREE);
    m_ilItemImages.Create (16, 16, ILC_COLOR32 | ILC_MASK, 0, 0);
    m_ilItemImages.Add (bmp, RGB (255, 0, 255));
    //SetImageList(m_ilItemImages,TVSIL_NORMAL);


    CDCHandle pDC = GetDC();
    BOOL rc = HDCheckboxImageList::CreateCheckboxImageList(pDC, m_ilItemStates, 
        16, m_rgbBackground);
    ReleaseDC(pDC);
    SetImageList(m_ilItemStates, TVSIL_STATE);
    if (!rc)
    {
        WTL::CBitmap bmp2;
        bmp2.LoadBitmap (IDB_TREE_STATE);
        m_ilItemStates.Create (16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
        m_ilItemStates.Add (bmp2, RGB (255, 0, 255));
        SetImageList(m_ilItemStates,TVSIL_STATE);
    }

    if (m_bEnableDrag && !InitDragDrop() )
        return FALSE;

    return TRUE;
}

//BOOL CMultiTree::SubclassWindow( HWND hWnd )
//{
//	return CWindowImpl< CMultiTree, WTL::CTreeViewCtrl >::SubclassWindow( hWnd ) ? Initialise() : FALSE;
//}

//void CMultiTree::ShowThemed( BOOL bShowThemed )
//{
//    m_bShowThemed = bShowThemed;
//    Invalidate();
//}

//void CMultiTree::SetMultipleSelect( BOOL bMultipleSelect )
//{
//    m_bMultipleSelect = bMultipleSelect;
//}

//BOOL CMultiTree::SelectItem( HTREEITEM hItem )
//{
//    if ( m_bMultipleSelect )
//        WTL::CTreeViewCtrl::SetItemState( hItem, TVIS_SELECTED, TVIS_SELECTED );
//    return WTL::CTreeViewCtrl::SelectItem( hItem );
//}

//void CMultiTree::GetSelectedItems( CSimpleArray < HTREEITEM >& aSelectedItems )
//{
//    aSelectedItems.RemoveAll();
//
//    if ( !m_bMultipleSelect )
//    {
//        aSelectedItems.Add( GetSelectedItem() );
//        return;
//    }
//
//    // get all selected tree items (recursive)
//    GetSelectedItems( GetRootItem(), aSelectedItems );
//}

//HTREEITEM CMultiTree::GetSelectedItems( HTREEITEM hItem, CSimpleArray < HTREEITEM >& aSelectedItems )
//{
//    if ( hItem == NULL )
//        return NULL;
//
//    // first scan siblings
//    HTREEITEM hSelectedItem = GetNextSiblingItem( hItem );
//
//    if ( hSelectedItem != NULL )
//    {
//        hSelectedItem = GetSelectedItems( hSelectedItem, aSelectedItems );
//        if ( hSelectedItem != NULL )
//            return hSelectedItem;
//    }
//
//    // then scan next children
//    hSelectedItem = GetChildItem( hItem );
//
//    if ( hSelectedItem != NULL )
//    {
//        hSelectedItem = GetSelectedItems( hSelectedItem, aSelectedItems );
//        if ( hSelectedItem != NULL )
//            return hSelectedItem;
//    }
//
//    // add selected to list
//    if ( GetItemState( hItem, TVIS_SELECTED ) & TVIS_SELECTED )
//        aSelectedItems.Add( hItem );
//
//    // continue searching
//    return hSelectedItem;
//}

//void CMultiTree::ResetSelected( HTREEITEM hItem )
//{
//    for ( ; hItem != NULL; hItem = GetNextSiblingItem( hItem ) )
//    {
//        ResetSelected( GetChildItem( hItem ) );
//        WTL::CTreeViewCtrl::SetItemState( hItem, 0, TVIS_SELECTED );
//    }
//}

//BOOL CMultiTree::SelectItems( HTREEITEM hItemFrom, HTREEITEM hItemTo )
//{
//    BOOL bSelectItem = FALSE;
//
//    // select range of visible items
//    for ( HTREEITEM hItem = GetRootItem(); hItem != NULL; hItem = GetNextVisibleItem( hItem ) )
//    {
//        if ( hItemFrom == hItemTo )
//            bSelectItem = FALSE;
//        else if ( hItem == hItemFrom || hItem == hItemTo )
//            bSelectItem = !bSelectItem;
//        WTL::CTreeViewCtrl::SetItemState( hItem, hItem == hItemFrom || hItem == hItemTo || bSelectItem ? TVIS_SELECTED : 0, TVIS_SELECTED );
//    }
//
//    Invalidate();
//
//    return TRUE;
//}

BOOL CMultiTree::LoadSettings()
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

    WTL::CLogFont logFont;
    logFont.SetMessageBoxFont();
    return SetFont(logFont);

}
BOOL CMultiTree::SetFont(LOGFONT ft)
{
    if ( !m_fntTreeFont.IsNull() )
        m_fntTreeFont.DeleteObject();
    if ( m_fntTreeFont.CreateFontIndirect( &ft ) == NULL )
        return FALSE;
    return TRUE;
}
LRESULT CMultiTree::OnStateIconClick(LPNMHDR pNMHDR) 
{   
   
    if(m_uFlags&TVHT_ONITEMSTATEICON)
    {

        return TRUE;
    }
    SetMsgHandled( FALSE );
    return FALSE;
}
LRESULT CMultiTree::OnKeydown(LPNMHDR pNMHDR) 
{
    TV_KEYDOWN* pTVKeyDown = reinterpret_cast<TV_KEYDOWN*>(pNMHDR);

    SetMsgHandled( FALSE );

    return TRUE;
}
int CMultiTree::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    SetMsgHandled( FALSE );
    //if (Initialise())
    {
       

    }

    return 0;
}

void CMultiTree::OnSettingsChange( UINT nFlags, LPCTSTR lpszSection )
{
    OnSettingsChange();
}

void CMultiTree::OnSettingsChange()
{
    LoadSettings();
    Invalidate();
}

void CMultiTree::OnSetFocus( HWND hOldWnd )
{
    SetMsgHandled( FALSE );
    Invalidate();
}

void CMultiTree::OnKillFocus( HWND hNewWnd )
{
    SetMsgHandled( FALSE );
    Invalidate();
}

void CMultiTree::OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags )
{
    if(nChar==VK_SPACE)
    {
        HTREEITEM hItem =GetSelectedItem();
        UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
        if(nState!=0)
        {
            nState=(nState==3)?1:3;
            SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK, TRUE);
        }
    }
    //if ( m_bMultipleSelect && ( nChar == VK_UP || nChar == VK_DOWN ) )
    //{
    //	if ( GetKeyState( VK_SHIFT ) & 0x8000 )
    //	{
    //		// initialise the reference item if this is the first shift selection
    //		if ( m_hFirstSelected == NULL )
    //			m_hFirstSelected = GetSelectedItem();

    //		// find which item is currently selected
    //		HTREEITEM hPrevItem = GetSelectedItem();
    //		HTREEITEM hItemNext = nChar == VK_UP ? GetPrevVisibleItem( hPrevItem ) : GetNextVisibleItem( hPrevItem );
    //		
    //		if ( hItemNext != NULL )
    //		{
    //			BOOL bSelectItem = !( GetItemState( hItemNext, TVIS_SELECTED ) & TVIS_SELECTED );

    //			// select the next item - this will also deselect the previous item
    //			SelectItem( hItemNext );

    //			// reselect the previously selected item
    //			if ( bSelectItem )
    //				WTL::CTreeViewCtrl::SetItemState( hPrevItem, TVIS_SELECTED, TVIS_SELECTED );
    //		}
    //		return;
    //	}
    //	else // no shift key
    //	{
    //		HTREEITEM hSelectedItem = GetSelectedItem();
    //		m_hFirstSelected = NULL;
    //		ResetSelected( GetRootItem() );
    //		SelectItem( hSelectedItem );
    //	}
    //}
    //else if ( nChar == VK_SPACE && ( GetStyle() & TVS_CHECKBOXES ) == TVS_CHECKBOXES )
    //{
    //	HTREEITEM hSelectedItem = GetSelectedItem();
    //	BOOL bChecked = hSelectedItem == NULL ? FALSE : GetCheckState( hSelectedItem );
    //	
    //	CSimpleArray< HTREEITEM > aSelectedItems;
    //	GetSelectedItems( aSelectedItems );
    //	
    //	// set checkbox for all selected items
    //	for ( int nItem = 0; nItem < aSelectedItems.GetSize(); nItem++ )
    //	{
    //		if ( aSelectedItems[ nItem ] != hSelectedItem )
    //			SetCheckState( aSelectedItems[ nItem ], !bChecked );
    //	}
    //}
    //else if ( _istalnum( nChar ) )
    //{
    //	m_hFirstSelected = NULL;
    //	ResetSelected( GetRootItem() );
    //}

    SetMsgHandled( FALSE );
}

LRESULT CMultiTree::OnBeginDrag( LPNMHDR lpNMHDR )
{
    LPNMTREEVIEW pnmtv = reinterpret_cast<LPNMTREEVIEW>( lpNMHDR );

    // m_hFirstSelected = NULL;
    // ResetSelected( GetRootItem() );
    SelectItem( pnmtv->itemNew.hItem );
    Select(pnmtv->itemNew.hItem, TVGN_DROPHILITE);			
    // SetMsgHandled( FALSE );

    USES_CONVERSION;
    CComBSTR bstr;
    GetItemText(pnmtv->itemNew.hItem, bstr.m_str);

    CIDropSource* pdsrc = new CIDropSource;
    if(pdsrc == NULL)
        return 0;
    pdsrc->AddRef();

    CIDataObject* pdobj = new CIDataObject(pdsrc);
    if(pdobj == NULL)
        return 0;
    pdobj->AddRef();

    FORMATETC fmtetc = {0};
    fmtetc.cfFormat = CF_TEXT;
    fmtetc.dwAspect = DVASPECT_CONTENT;
    fmtetc.lindex = -1;
    fmtetc.tymed = TYMED_HGLOBAL;

    STGMEDIUM medium = {0};
    medium.tymed = TYMED_HGLOBAL;
    TCHAR* str = OLE2T(bstr.m_str);

    medium.hGlobal = GlobalAlloc(GMEM_MOVEABLE, strlen(str)+1); //for NULL
    TCHAR* pMem = (TCHAR*)GlobalLock(medium.hGlobal);
    strcpy(pMem,str);
    GlobalUnlock(medium.hGlobal);

    pdobj->SetData(&fmtetc,&medium,TRUE);

    CDragSourceHelper dragSrcHelper;
    // get drag image from the window through DI_GETDRAGIMAGE (treeview seems to already support it)
    dragSrcHelper.InitializeFromWindow(m_hWnd, pnmtv->ptDrag, pdobj);
    DWORD dwEffect;
    HRESULT hr = ::DoDragDrop(pdobj, pdsrc, DROPEFFECT_COPY, &dwEffect);
    pdsrc->Release();
    pdobj->Release();


    SendMessage(TVM_SELECTITEM, TVGN_DROPHILITE,0); 

    return TRUE;
}	
bool CMultiTree::InitDragDrop()
{
    m_pDropTarget = new CTreeDropTarget(m_hWnd, this);
    if(m_pDropTarget == NULL)
        return false;
    m_pDropTarget->AddRef();

    if(FAILED(RegisterDragDrop(m_hWnd,m_pDropTarget))) //calls addref
    {
        m_pDropTarget = NULL;
        return false;
    }
    else
        m_pDropTarget->Release(); //i decided to AddRef explicitly after new

    FORMATETC ftetc={0};
    ftetc.cfFormat = CF_TEXT;
    ftetc.dwAspect = DVASPECT_CONTENT;
    ftetc.lindex = -1;
    ftetc.tymed = TYMED_HGLOBAL;
    m_pDropTarget->AddSuportedFormat(ftetc);
    ftetc.cfFormat=CF_HDROP;
    m_pDropTarget->AddSuportedFormat(ftetc);
    return true;
}
//LRESULT CMultiTree::OnDblClick( LPNMHDR lpNMHDR )
//{
//	DWORD dwPoint = GetMessagePos();
//	WTL::CPoint ptMouse( GET_X_LPARAM( dwPoint ), GET_Y_LPARAM( dwPoint ) );
//	ScreenToClient( &ptMouse );
//	
//	// handle double-clicks (for drawing)
//	SendMessage( WM_LBUTTONDOWN, 0, MAKELPARAM( ptMouse.x, ptMouse.y ) );
//	SendMessage( WM_LBUTTONUP, 0, MAKELPARAM( ptMouse.x, ptMouse.y ) );
//
//	SetMsgHandled( FALSE );
//	
//	return TRUE;
//}

void CMultiTree::OnLButtonDown( UINT nFlags, WTL::CPoint point )
{
    HTREEITEM hItem =HitTest(point, &m_uFlags);
    if (hItem != NULL)
    {
        SelectItem (hItem);	
        if ( (m_uFlags&TVHT_ONITEMSTATEICON ))
        {

            //nState: 0->无选择钮 1->没有选择 2->部分选择 3->全部选择
            UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
            if (nState != 0) 
            {
                nState = (nState == 3) ? 1 : 3;
                SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK,TRUE );
                OnStateChange(hItem);
            }
        }
    }


    //=====================================//
    //if ( m_bMultipleSelect )
    //{
    //	m_bCtrlKey = ( ( GetKeyState( VK_CONTROL ) & 0x8000 ) != 0 );
    //	m_bShiftKey = ( ( GetKeyState( VK_SHIFT ) & 0x8000 ) != 0 );
    //	
    //	if ( m_bCtrlKey || m_bShiftKey )
    //		return;
    //	
    //	// reset selected item if click on a single item
    //	HTREEITEM hNewItem = HitTest( point, NULL );
    //	if ( hNewItem != NULL )
    //	{
    //		UINT nNewSelectState = ( GetItemState( hNewItem, TVIS_SELECTED ) & TVIS_SELECTED );
    //		ResetSelected( GetRootItem() );
    //		WTL::CTreeViewCtrl::SetItemState( hNewItem, nNewSelectState, TVIS_SELECTED );
    //		m_hFirstSelected = hNewItem;
    //	}
    //}

    SetMsgHandled( FALSE );
}

void CMultiTree::OnLButtonUp( UINT nFlags, WTL::CPoint point )
{
    SetMsgHandled( FALSE );

    //if ( !m_bMultipleSelect )
    //	return;
    //	
    //HTREEITEM hNewItem = HitTest( point, NULL );
    //HTREEITEM hOldItem = GetSelectedItem();
    //
    //if ( m_bCtrlKey )
    //{
    //	if ( hNewItem != NULL )
    //	{
    //		UINT nNewSelectState = GetItemState( hNewItem, TVIS_SELECTED ) & TVIS_SELECTED ? 0 : TVIS_SELECTED;
    //		UINT nOldSelectState = hOldItem == NULL ? 0 : GetItemState( hOldItem, TVIS_SELECTED );
    //		
    //		// select new item (to get focus)
    //		SelectItem( hNewItem );
    //		
    //		// set highlight state for new item
    //		if ( GetItemState( hNewItem, TVIS_SELECTED ) != nNewSelectState )
    //			WTL::CTreeViewCtrl::SetItemState( hNewItem, nNewSelectState, TVIS_SELECTED );
    //		
    //		// restore state of old selected item
    //		if ( hOldItem != NULL && hOldItem != hNewItem && GetItemState( hOldItem, TVIS_SELECTED ) != nOldSelectState )
    //			WTL::CTreeViewCtrl::SetItemState( hOldItem, nOldSelectState, TVIS_SELECTED );
    //		
    //		m_hFirstSelected = NULL;
    //	}
    //}
    //else if ( m_bShiftKey )
    //{
    //	// initialise the reference item if this is the first shift selection
    //	if ( m_hFirstSelected == NULL )
    //		m_hFirstSelected = GetSelectedItem();
    //		
    //	// select new item (to get focus)
    //	if ( hOldItem == hNewItem )
    //		SelectItem( NULL ); // to prevent edit
    //
    //	if ( m_hFirstSelected != NULL )
    //		SelectItems( m_hFirstSelected, hNewItem );
    //}
    //
    //m_bCtrlKey = FALSE;
    //m_bShiftKey = FALSE;
}

//void CMultiTree::DoPaint( WTL::CDCHandle dcPaint )
//{
//    // default paint handlers will call custom draw
//    DefWindowProc( WM_ERASEBKGND, (WPARAM)dcPaint.m_hDC, 0 );
//    DefWindowProc( WM_PAINT, (WPARAM)dcPaint.m_hDC, 0 );
//}

//DWORD CMultiTree::OnPrePaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw )
//{		
//    return m_bShowThemed ? CDRF_NOTIFYITEMDRAW : CDRF_DODEFAULT;
//}
//
//DWORD CMultiTree::OnItemPrePaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw )
//{
//    return m_bShowThemed ? CDRF_NOTIFYPOSTPAINT : CDRF_DODEFAULT;
//}
//
//DWORD CMultiTree::OnItemPostPaint( int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw )
//{
//    LPNMLVCUSTOMDRAW lpCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>( lpNMCustomDraw );
//
//    WTL::CRect rcItem;
//    if ( !GetItemRect( (HTREEITEM)lpCustomDraw->nmcd.dwItemSpec, rcItem, TRUE ) )
//        return CDRF_DODEFAULT;
//
//    WTL::CDCHandle dcPaint( lpCustomDraw->nmcd.hdc );
//    int nContextState = dcPaint.SaveDC();
//
//    dcPaint.SetBkColor( m_rgbBackground );
//    dcPaint.ExtTextOut( rcItem.left, rcItem.top, ETO_OPAQUE, rcItem, _T( "" ), 0, NULL );
//
//    // only one item is selected at any one time
//    BOOL bSelected = ( GetItemState( (HTREEITEM)lpCustomDraw->nmcd.dwItemSpec, TVIS_SELECTED | TVIS_DROPHILITED ) & ( TVIS_SELECTED | TVIS_DROPHILITED ) );
//    HTREEITEM hHighlightItem = GetDropHilightItem();
//    if ( hHighlightItem != NULL && hHighlightItem != (HTREEITEM)lpCustomDraw->nmcd.dwItemSpec )
//        bSelected = FALSE;
//
//    // draw selected background and border
//    if ( bSelected )
//    {
//        BOOL bControlFocus = ( GetFocus() == m_hWnd );
//        WTL::CRect rcSelect( rcItem );
//
//        WTL::CPen penBorder;
//        penBorder.CreatePen( PS_SOLID, 1, bControlFocus ? m_rgbSelectOuter : m_rgbNoFocusOuter );
//        WTL::CBrush bshInterior;
//        bshInterior.CreateSolidBrush( m_rgbBackground );
//
//        dcPaint.SelectPen( penBorder );
//        dcPaint.SelectBrush( bshInterior );
//
//        dcPaint.RoundRect( rcSelect, WTL::CPoint( 5, 5 ) );
//        rcSelect.DeflateRect( 1, 1 );
//
//        WTL::CPen penInnerBorder;
//        penInnerBorder.CreatePen( PS_SOLID, 1, bControlFocus ? m_rgbSelectInner : m_rgbNoFocusInner );
//        dcPaint.SelectPen( penInnerBorder );
//
//        dcPaint.RoundRect( rcSelect, CPoint( 2, 2 ) );
//        rcSelect.DeflateRect( 1, 1 );
//
//        GRADIENT_RECT grdRect = { 0, 1 };
//        TRIVERTEX triVertext[ 2 ] = {
//            rcSelect.left,
//            rcSelect.top,
//            GetRValue( bControlFocus ? m_rgbSelectTop : m_rgbNoFocusTop ) << 8,
//            GetGValue( bControlFocus ? m_rgbSelectTop : m_rgbNoFocusTop ) << 8,
//            GetBValue( bControlFocus ? m_rgbSelectTop : m_rgbNoFocusTop ) << 8,
//            0x0000,			
//            rcSelect.right,
//            rcSelect.bottom,
//            GetRValue( bControlFocus ? m_rgbSelectBottom : m_rgbNoFocusBottom ) << 8,
//            GetGValue( bControlFocus ? m_rgbSelectBottom : m_rgbNoFocusBottom ) << 8,
//            GetBValue( bControlFocus ? m_rgbSelectBottom : m_rgbNoFocusBottom ) << 8,
//            0x0000
//        };
//
//        dcPaint.GradientFill( triVertext, 2, &grdRect, 1, GRADIENT_FILL_RECT_V );
//    }
//
//    ATL::CString strItemText;
//    //TCHAR strText[MAX_PATH];
//    //memset(strText, 0, MAX_PATH);
//    GetItemText( (HTREEITEM)lpCustomDraw->nmcd.dwItemSpec, strItemText);//strText, MAX_PATH
//    //strItemText=strText;
//    if ( !strItemText.IsEmpty() )
//    {
//        WTL::CRect rcItemText( rcItem );
//        rcItemText.DeflateRect( 3, 0, 2, 0 );
//
//        dcPaint.SelectFont( m_fntTreeFont );
//        dcPaint.SetTextColor( m_rgbItemText );
//        dcPaint.SetBkMode( TRANSPARENT );
//        dcPaint.DrawText( strItemText, strItemText.GetLength(), rcItemText, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER );
//    }
//
//    dcPaint.RestoreDC( nContextState );
//
//    return CDRF_DODEFAULT;
//}
//====================================//
bool CMultiTree::IsFullCheck(HTREEITEM hItem)
{
    UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
    return nState > 2;
}
bool CMultiTree::IsCheck(HTREEITEM hItem)
{
    UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
    return nState > 1;
}
void CMultiTree::CheckItem(HTREEITEM hItem,BOOL bCheck)
{
    if(bCheck)
    {
        UINT nState = 3;
        SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK, TRUE );
    }
    else
    {
        UINT nState = 1;
        SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK, TRUE );
    }
}
void CMultiTree::TravelSiblingAndParent(HTREEITEM hItem, int nState)
{
    HTREEITEM hNextSiblingItem,hPrevSiblingItem,hParentItem;

    //查找父节点，没有就结束
    hParentItem=GetParentItem(hItem);
    if(hParentItem!=NULL)
    {
        int nState1=nState;//设初始值，防止没有兄弟节点时出错

        //查找当前节点下面的兄弟节点的状态
        hNextSiblingItem=GetNextSiblingItem(hItem);
        while(hNextSiblingItem!=NULL)
        {
            nState1 = GetItemState( hNextSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
            if(nState1!=nState && nState1!=0) break;
            else hNextSiblingItem=GetNextSiblingItem(hNextSiblingItem);
        }

        if(nState1==nState)
        {
            //查找当前节点上面的兄弟节点的状态
            hPrevSiblingItem=GetPrevSiblingItem(hItem);
            while(hPrevSiblingItem!=NULL)
            {
                nState1 = GetItemState( hPrevSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
                if(nState1!=nState && nState1!=0) break;
                else hPrevSiblingItem=GetPrevSiblingItem(hPrevSiblingItem);
            }
        }

        if(nState1==nState || nState1==0)
        {
            nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
            if(nState1!=0)
            {
                //如果状态一致，则父节点的状态与当前节点的状态一致
                WTL::CTreeViewCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
            }
            //再递归处理父节点的兄弟节点和其父节点
            TravelSiblingAndParent(hParentItem,nState);
        }
        else
        {
            //状态不一致，则当前节点的父节点、父节点的父节点……状态均为第三态
            hParentItem=GetParentItem(hItem);
            while(hParentItem!=NULL)
            {
                nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
                if(nState1!=0)
                {
                    WTL::CTreeViewCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
                }
                hParentItem=GetParentItem(hParentItem);
            }
        }
    }	
}
BOOL CMultiTree::GetItemBold(HTREEITEM hItem)
{
    return GetItemState(hItem, TVIS_BOLD) & TVIS_BOLD;
}

BOOL CMultiTree::SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch)// = TRUE
{
    BOOL bReturn=WTL::CTreeViewCtrl::SetItemState( hItem, nState, nStateMask );

    UINT iState = nState >> 12;
    if(iState != 0)
    {
        if(bSearch) 
            TravelChild(hItem, iState);
        TravelSiblingAndParent(hItem,iState);
    }
    return bReturn;
}

void CMultiTree::TravelChild(HTREEITEM hItem, int nState)
{
    HTREEITEM hChildItem,hBrotherItem;

    //查找子节点，没有就结束
    hChildItem=GetChildItem(hItem);
    if(hChildItem!=NULL)
    {
        //设置子节点的状态与当前节点的状态一致
        WTL::CTreeViewCtrl::SetItemState( hChildItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
        //再递归处理子节点的子节点和兄弟节点
        TravelChild(hChildItem, nState);

        //处理子节点的兄弟节点和其子节点
        hBrotherItem=GetNextSiblingItem(hChildItem);
        while (hBrotherItem)
        {
            //设置子节点的兄弟节点状态与当前节点的状态一致
            int nState1 = GetItemState( hBrotherItem, TVIS_STATEIMAGEMASK ) >> 12;
            if(nState1!=0)
            {
                WTL::CTreeViewCtrl::SetItemState( hBrotherItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
            }
            //再递归处理子节点的兄弟节点的子节点和兄弟节点
            TravelChild(hBrotherItem, nState);
            hBrotherItem=GetNextSiblingItem(hBrotherItem);
        }
    }
}
HTREEITEM CMultiTree::MoveItem(HTREEITEM hItem, HTREEITEM hNewParent, HTREEITEM hAfter)
{
    HTREEITEM hNewItem = NULL;

    TVINSERTSTRUCT tvis;
    ATL::CString strText = _T("");

    // get information of the source item
    tvis.item.hItem = hItem;
    tvis.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_PARAM |
        TVIF_IMAGE | TVIF_SELECTEDIMAGE;
    GetItem(&tvis.item);  
    GetItemText(hItem, strText);

    tvis.item.cchTextMax = strText.GetLength();
    tvis.item.pszText = strText.LockBuffer();

    // insert the item at proper location
    tvis.hParent = hNewParent;
    tvis.hInsertAfter = hAfter;
    tvis.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;

    hNewItem = InsertItem(&tvis);

    UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
    SetItemState( hNewItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK, TRUE );

    strText.UnlockBuffer();
    return hNewItem;
}
HTREEITEM CMultiTree::MoveBranch(HTREEITEM hBranch, HTREEITEM hNewParent, HTREEITEM hAfter)
{
    HTREEITEM hChild;

    HTREEITEM hNewItem = MoveItem(hBranch, hNewParent, hAfter);
    HTREEITEM hNext = GetChildItem(hBranch);
    hChild = hNext;
    while (hChild)
    {
        // recursively transfer all the items
        MoveBranch(hChild, hNewItem);
        hNext = GetNextSiblingItem(hChild);
        hChild = hNext;
    }
    return hNewItem;
}

void CMultiTree::DeleteBranch(HTREEITEM hItem)
{
    if (hItem)
    {
        HTREEITEM hChild = GetChildItem(hItem);
        while (hChild)
        {
            // recursively delete all the items
            HTREEITEM hNext = GetNextSiblingItem(hChild);
            DeleteBranch(hChild);
            hChild = hNext;
        }
        DeleteItem(hItem);
    }
}

LRESULT CMultiTree::OnDestroy( )
{
    if (m_bEnableDrag)
    {
        RevokeDragDrop(m_hWnd); //calls release
        m_pDropTarget=NULL;
    }

    return 0;
}
//void CMultiTree::DoPaint(WTL::CDCHandle dc) 
//{
//    // First let the control do its default drawing.
//    DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
//
//    HTREEITEM hItem = GetFirstVisibleItem();
//
//    int iItemCount = GetVisibleCount() + 1;
//    while(hItem && iItemCount--)
//    {	
//        OnItemDraw(dc.m_hDC,hItem);
//        hItem = GetNextVisibleItem(hItem);
//    }
//}

LRESULT CMultiTree::OnCustomDraw(LPNMHDR pNMHDR)
{
	NMTVCUSTOMDRAW* pCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);

	CDCHandle pDC(pCD->nmcd.hdc);

	HTREEITEM hItem = reinterpret_cast<HTREEITEM> (pCD->nmcd.dwItemSpec);

	// Take the default processing unless we set this to something else below.
	LRESULT pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.

	//=========================================================================
	if (pCD->nmcd.dwDrawStage == CDDS_PREPAINT)	// before the painting cycle begins
	//=========================================================================
	{
		pResult = CDRF_NOTIFYITEMDRAW /*| CDRF_NOTIFYPOSTPAINT*/;
	}
	//=========================================================================
	else if (pCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)	// before an item is drawn
	//=========================================================================
	{
		pCD->clrText = pCD->clrTextBk;	// don't want default drawing -
										// set text color = background color
		if (hItem)
		{
			CRect rectItem1;
			GetItemRect(hItem, &rectItem1, FALSE);	// get rect for item
			
			{
				WTL::CBrush brush;
                brush.CreateSolidBrush(m_rgbBackground);
				pDC.FillRect(&rectItem1, brush);		// erase entire background
			}
		}
		pResult = CDRF_NOTIFYPOSTPAINT | CDRF_NEWFONT;
	}
	//=========================================================================
	else if (pCD->nmcd.dwDrawStage == CDDS_ITEMPOSTPAINT)	// after an item has been drawn
	//=========================================================================
	{
		// by doing the drawing at this stage we avoid having to draw lines, etc.

		  OnItemDraw(pDC,hItem);
	 
	
		pResult = CDRF_SKIPDEFAULT;	// We've painted everything.
	}
    return pResult;
}
