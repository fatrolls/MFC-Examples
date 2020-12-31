// VirtualList.cpp : Implementation of CVirtualList

#include "stdafx.h"

#include "VirtualControls.h"
#include "VirtualList.h"


/////////////////////////////////////////////////////////////////////////////
// CVirtualList

LRESULT CVirtualList::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   m_ctlList.Attach( GetDlgItem(IDC_LIST) );
   m_ctlUp.Attach( GetDlgItem(IDC_UP) );
   m_ctlDown.Attach( GetDlgItem(IDC_DOWN) );
   m_ctlScrollbar.Attach( GetDlgItem(IDC_SCROLLBAR1) );

   CRect rc;
   m_ctlList.GetClientRect(rc);
   LVCOLUMN lvcol = { 0 };
   lvcol.mask = LVCF_TEXT | LVCF_WIDTH;
   lvcol.pszText = _T("Title");
   lvcol.cchTextMax = ::lstrlen(lvcol.pszText);
   lvcol.cx = rc.Width()-8;
   m_ctlList.InsertColumn(0, &lvcol);
   m_ctlList.SetCallbackMask(LVIS_SELECTED|LVIS_FOCUSED);
   
   DWORD dwListStyle = LVS_EX_FULLROWSELECT | LVS_EX_LABELTIP;
   if( m_bGridLines ) dwListStyle |= LVS_EX_GRIDLINES;
   if( m_bTrackSelect ) dwListStyle |= LVS_EX_TRACKSELECT;
   m_ctlList.SetExtendedListViewStyle(dwListStyle);

   m_bmpUp.LoadBitmap(IDB_UP);
   m_bmpDown.LoadBitmap(IDB_DOWN);
   m_ctlUp.SetBitmap(m_bmpUp);
   m_ctlDown.SetBitmap(m_bmpDown);

   return 0;
}

LRESULT CVirtualList::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   UINT nType =  (UINT) wParam;
   if( nType != SIZE_MINIMIZED ) {
      int cx = GET_X_LPARAM(lParam);
      int cy = GET_Y_LPARAM(lParam);
      m_ctlList.MoveWindow( 0, 0, cx - m_cxScroll, cy );
      m_ctlUp.MoveWindow( cx - m_cxScroll, 0, m_cxScroll, m_cyScroll );
      m_ctlDown.MoveWindow( cx - m_cxScroll,cy - m_cyScroll, m_cxScroll, m_cyScroll );
      m_ctlScrollbar.MoveWindow( cx - m_cxScroll,m_cyScroll, m_cxScroll, cy - (m_cyScroll * 2) );
      m_ctlList.SetColumnWidth(0, cx - m_cxScroll - 8);
   }
   return 0;
}

LRESULT CVirtualList::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   m_ctlList.SetFocus();
   return 0;
}

BOOL CVirtualList::DefineScrollRange()
{
   int iVal = m_dwCount - m_ctlList.GetCountPerPage();
   m_ctlScrollbar.SetScrollRange(0, (iVal > 0 ? iVal : 0), TRUE);
   return TRUE;
};

BOOL CVirtualList::EnsureVisible(long iIndex)
{
   int iScrollPos, iScrollLo, iScrollRange, iPageSize;
   iScrollPos = m_ctlScrollbar.GetScrollPos();
   iPageSize = m_ctlList.GetCountPerPage();
   m_ctlScrollbar.GetScrollRange( &iScrollLo, &iScrollRange );

   if( iIndex>=iScrollPos + iPageSize ) {
      int iNewScrollPos = iIndex - iPageSize + 1;
      if( iNewScrollPos < 0 ) iNewScrollPos=0;
      m_ctlScrollbar.SetScrollPos( iNewScrollPos, TRUE );
      m_ctlList.RedrawItems( 0, iPageSize );
   }
   else if( iIndex < (int)iScrollPos ) {
      int iNewScrollPos = iIndex;
      m_ctlScrollbar.SetScrollPos( iNewScrollPos, TRUE );
      m_ctlList.RedrawItems( 0, iPageSize );
   }

   return TRUE;
}

LRESULT CVirtualList::OnListChanged(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
   NMLISTVIEW *pnmv = (NMLISTVIEW *)pnmh;
   int iScrollPos = m_ctlScrollbar.GetScrollPos();
   if( pnmv->iItem >= 0 && pnmv->uNewState != 0 ) {
      m_dwListIndex = iScrollPos + pnmv->iItem;
      EnsureVisible(m_dwListIndex);
      Fire_SelChange( (LONG) pnmv->iItem );
   }
   FireViewChange();
   return 0;
};

LRESULT CVirtualList::OnListClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
   Fire_Click();
   return 0;
};

LRESULT CVirtualList::OnListDblClick(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
{
   Fire_DblClick();
   return 0;
};

LRESULT CVirtualList::OnListGetDispInfo(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
   const int MAX_TEXTLEN = 300;
   int iScrollPos = m_ctlScrollbar.GetScrollPos();

   NMLVDISPINFO *pnmv = (NMLVDISPINFO*) pnmh;
   DWORD dwPos = iScrollPos + pnmv->item.iItem;

   if( pnmv->item.mask & LVIF_TEXT ) {
      TCHAR szString[MAX_TEXTLEN];
      CComBSTR bstr;
      HRESULT Hr;
      Hr = Fire_GetItem(dwPos, &bstr);
      if( bstr.Length() < MAX_TEXTLEN ) {
         ::wsprintf(szString, _T("%ls"), bstr.m_str == NULL ? L"" : bstr );
      }
      else {
          szString[0] = _T('\0');
      }
      ::lstrcpyn(pnmv->item.pszText, szString, pnmv->item.cchTextMax);
   }
   if( pnmv->item.mask & LVIF_IMAGE ) {
      pnmv->item.iImage = 0;
   }
   if( pnmv->item.mask & LVIF_INDENT ) {
      pnmv->item.iIndent = 0;
   }    
   if( pnmv->item.mask & LVIF_STATE ) {
      pnmv->item.state = m_dwListIndex == dwPos ? LVIS_SELECTED|LVIS_FOCUSED : 0;
   }    
   bHandled = TRUE;
   return 1;
}

LRESULT CVirtualList::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   return 1;
}

LRESULT CVirtualList::OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   return DLGC_WANTARROWS;
}

LRESULT CVirtualList::OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   short nPos = HIWORD(wParam);
   short nSBCode = LOWORD(wParam);
   int iScrollPos;
   int iScrollLo, iScrollRange;
   int iScrollAmt;
   int iPageSize;

   CRect rectClient;
   GetClientRect(&rectClient);

   CRect rectItem;
   m_ctlList.GetItemRect( 0, &rectItem, LVIR_BOUNDS );
   iPageSize = m_ctlList.GetCountPerPage();

   iScrollPos = m_ctlScrollbar.GetScrollPos();
   m_ctlScrollbar.GetScrollRange( &iScrollLo, &iScrollRange );

   iScrollRange = m_dwCount - iPageSize + 1;

   switch( nSBCode ) { 
   case SB_LINEUP: 
     iScrollAmt = -1;
     break ; 
   case SB_LINEDOWN: 
     iScrollAmt = 1;
     break ; 
   case SB_PAGEUP:         
     iScrollAmt = -(rectClient.Height() / rectItem.Height() );
     break ; 
   case SB_PAGEDOWN: 
     iScrollAmt = rectClient.Height() / rectItem.Height();
     break ; 
   case SB_CHAPTERUP: 
     iScrollAmt = -(int)m_dwPageStep; 
     break ; 
   case SB_CHAPTERDOWN: 
     iScrollAmt = (int)m_dwPageStep;
     break ; 
   case SB_TOP: 
     iScrollAmt = -iScrollPos;
     break ; 
   case SB_BOTTOM: 
     iScrollAmt = iScrollRange-iScrollPos;
     break ; 
   case SB_THUMBPOSITION: 
     iScrollAmt = nPos - iScrollPos ; 
     break ; 
   default: 
     iScrollAmt = 0 ; 
   };

   if( iScrollAmt!=0 ) { 
      int iNewScrollPos = iScrollPos + iScrollAmt;
      if( iNewScrollPos < 0 ) iNewScrollPos = 0;
      if( iNewScrollPos > iScrollRange ) iNewScrollPos = iScrollRange;
      if( iScrollPos == iNewScrollPos ) return 0;

      // Set scrollbar position
      m_ctlScrollbar.SetScrollPos( iNewScrollPos, TRUE );
      m_ctlList.RedrawItems( 0, iPageSize );
   }

   return 0;
}

LRESULT CVirtualList::OnClickedDown(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
   LRESULT res =  OnVScroll( WM_VSCROLL, SB_CHAPTERDOWN, 0, bHandled);
   m_ctlList.SetFocus(); // force focus away from button (not pretty)
   return res;
}

LRESULT CVirtualList::OnClickedUp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
   LRESULT res = OnVScroll( WM_VSCROLL, SB_CHAPTERUP, 0, bHandled);
   m_ctlList.SetFocus(); // force focus away from button (not pretty)
   return res;
}

/////////////////////////////////////////////////////////////////////////////
// IVirtualControl

STDMETHODIMP CVirtualList::OnAmbientPropertyChange(DISPID dispid)
{
   if( dispid == DISPID_AMBIENT_BACKCOLOR ) {
      SetBackgroundColorFromAmbient();
      FireViewChange();
   }
   return IOleControlImpl<CVirtualList>::OnAmbientPropertyChange(dispid);
}

// Need to overload all keyboard cursor events, because we're
// handling the scrolling ourselves.
BOOL CVirtualList::PreTranslateAccelerator(LPMSG pMsg, HRESULT& /*hRet*/)
{   
   switch( pMsg->message ) {
   case WM_KEYDOWN:
      switch( LOWORD(pMsg->wParam) ) {
      case VK_UP:
         if( m_dwListIndex > 0 ) {
            m_dwListIndex--;
            EnsureVisible(m_dwListIndex);
         }
         FireViewChange();
         return TRUE;
      case VK_DOWN:
         m_dwListIndex++;
         if( m_dwListIndex >= m_dwCount ) m_dwListIndex = m_dwCount - 1;
         EnsureVisible(m_dwListIndex);
         FireViewChange();
         return TRUE;
      case VK_PRIOR:
         if( m_dwListIndex > (DWORD)m_dwPageStep ) m_dwListIndex -= m_dwPageStep; else m_dwListIndex=0;
         EnsureVisible(m_dwListIndex);
         FireViewChange();
         return TRUE;
      case VK_NEXT:
         m_dwListIndex += m_dwPageStep;
         if( m_dwListIndex >= m_dwCount ) m_dwListIndex = m_dwCount - 1;
         EnsureVisible(m_dwListIndex);
         FireViewChange();
         return TRUE;
      case VK_HOME:
         m_dwListIndex = 0;
         EnsureVisible(m_dwListIndex);
         FireViewChange();
         break;
      case VK_END:
         m_dwListIndex = m_dwCount - 1;
         EnsureVisible(m_dwListIndex);
         FireViewChange();
         break;
      }
      break;
   }
   return FALSE;
};

STDMETHODIMP CVirtualList::Clear()
{
   return put_ListCount(0);
}

STDMETHODIMP CVirtualList::get_ListCount(long *pVal)
{
   if( pVal == NULL ) return E_POINTER;
   *pVal = m_dwCount;
   return S_OK;
}

STDMETHODIMP CVirtualList::put_ListCount(long newVal)
{
   m_dwCount = newVal;
   m_dwListIndex = -1;
   int iPageCount = m_ctlList.GetCountPerPage();
   m_ctlList.SetItemCount(iPageCount);

   BOOL bEnabled = (newVal > 0);
   m_ctlUp.EnableWindow(bEnabled);
   m_ctlDown.EnableWindow(bEnabled);

   m_ctlScrollbar.SetScrollPos(SB_CTL, 0);
   m_ctlScrollbar.EnableScrollBar(newVal>0 ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH);
   DefineScrollRange();

   FireViewChange();       // Request redraw
   SetDirty(TRUE);
   return S_OK;
}

STDMETHODIMP CVirtualList::get_ListIndex(long *pVal)
{
   if( pVal == NULL ) return E_POINTER;
   *pVal = m_dwListIndex;
   return S_OK;
}

STDMETHODIMP CVirtualList::put_ListIndex(long newVal)
{
   m_dwListIndex = newVal;
   FireViewChange();
   return S_OK;
}

STDMETHODIMP CVirtualList::get_TopIndex(long *pVal)
{
   if( pVal == NULL ) return E_POINTER;
   *pVal = m_ctlScrollbar.GetScrollPos();
   return S_OK;
}

STDMETHODIMP CVirtualList::put_TopIndex(long newVal)
{
   RECT rcItem = { 0 };
   int iPageSize;
   iPageSize = m_ctlList.GetCountPerPage();
   m_ctlScrollbar.SetScrollPos( newVal, TRUE );
   m_ctlList.RedrawItems( 0, iPageSize );
   FireViewChange();
   return S_OK;
}

STDMETHODIMP CVirtualList::get_PageStep(long *pVal)
{
   if( pVal == NULL ) return E_POINTER;
   *pVal = m_dwPageStep;
   return S_OK;
}

STDMETHODIMP CVirtualList::put_PageStep(long newVal)
{
   if( newVal < 0 ) return E_INVALIDARG;
   m_dwPageStep = newVal;
   SetDirty(TRUE);
   return S_OK;
}

STDMETHODIMP CVirtualList::get_GridLines(VARIANT_BOOL *pVal)
{
   if( pVal == NULL ) return E_POINTER;
   *pVal = m_bGridLines ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

STDMETHODIMP CVirtualList::put_GridLines(VARIANT_BOOL newVal)
{
   m_bGridLines = newVal != VARIANT_FALSE;
   m_ctlList.SetExtendedListViewStyle((m_ctlList.GetExtendedListViewStyle() & LVS_EX_GRIDLINES) | (m_bGridLines ? LVS_EX_GRIDLINES : 0));
   FireViewChange();
   SetDirty(TRUE);
   return S_OK;
}

STDMETHODIMP CVirtualList::get_TrackSelect(VARIANT_BOOL *pVal)
{
   if( pVal == NULL ) return E_POINTER;
   *pVal = m_bTrackSelect ? VARIANT_TRUE : VARIANT_FALSE;
   return S_OK;
}

STDMETHODIMP CVirtualList::put_TrackSelect(VARIANT_BOOL newVal)
{
   m_bTrackSelect = newVal != VARIANT_FALSE;
   m_ctlList.SetExtendedListViewStyle((m_ctlList.GetExtendedListViewStyle() & LVS_EX_TRACKSELECT) | (m_bTrackSelect ? LVS_EX_TRACKSELECT : 0));
   FireViewChange();
   SetDirty(TRUE);
   return S_OK;
}

