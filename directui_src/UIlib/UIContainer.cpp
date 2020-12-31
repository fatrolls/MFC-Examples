
#include "StdAfx.h"
#include "UIContainer.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

CContainerUI::CContainerUI() : 
   m_hwndScroll(NULL), 
   m_iPadding(0),
   m_iScrollPos(0),
   m_bAutoDestroy(true),
   m_bAllowScrollbars(false)
{
   m_cxyFixed.cx = m_cxyFixed.cy = 0;
   ::ZeroMemory(&m_rcInset, sizeof(m_rcInset));
}

CContainerUI::~CContainerUI()
{
   RemoveAll();
}

LPCTSTR CContainerUI::GetClass() const
{
   return _T("ContainerUI");
}

LPVOID CContainerUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("Container")) == 0 ) return static_cast<IContainerUI*>(this);
   return CControlUI::GetInterface(pstrName);
}

CControlUI* CContainerUI::GetItem(int iIndex) const
{
   if( iIndex < 0 || iIndex >= m_items.GetSize() ) return NULL;
   return static_cast<CControlUI*>(m_items[iIndex]);
}

int CContainerUI::GetCount() const
{
   return m_items.GetSize();
}

bool CContainerUI::Add(CControlUI* pControl)
{
   if( m_pManager != NULL ) m_pManager->InitControls(pControl, this);
   if( m_pManager != NULL ) m_pManager->UpdateLayout();
   return m_items.Add(pControl);
}

bool CContainerUI::Remove(CControlUI* pControl)
{
   for( int it = 0; m_bAutoDestroy && it < m_items.GetSize(); it++ ) {
      if( static_cast<CControlUI*>(m_items[it]) == pControl ) {
         if( m_pManager != NULL ) m_pManager->UpdateLayout();
         delete pControl;
         return m_items.Remove(it);
      }
   }
   return false;
}

void CContainerUI::RemoveAll()
{
   for( int it = 0; m_bAutoDestroy && it < m_items.GetSize(); it++ ) delete static_cast<CControlUI*>(m_items[it]);
   m_items.Empty();
   m_iScrollPos = 0;
   if( m_pManager != NULL ) m_pManager->UpdateLayout();
}

void CContainerUI::SetAutoDestroy(bool bAuto)
{
   m_bAutoDestroy = bAuto;
}

void CContainerUI::SetInset(SIZE szInset)
{
   m_rcInset.left = m_rcInset.right = szInset.cx;
   m_rcInset.top = m_rcInset.bottom = szInset.cy;
}

void CContainerUI::SetInset(RECT rcInset)
{
   m_rcInset = rcInset;
}

void CContainerUI::SetPadding(int iPadding)
{
   m_iPadding = iPadding;
}

void CContainerUI::SetWidth(int cx)
{
   m_cxyFixed.cx = cx;
}

void CContainerUI::SetHeight(int cy)
{
   m_cxyFixed.cy = cy;
}

void CContainerUI::SetVisible(bool bVisible)
{
   // Hide possible scrollbar control
   if( m_hwndScroll != NULL ) ::ShowScrollBar(m_hwndScroll, SB_CTL, bVisible);
   // Hide children as well
   for( int it = 0; it < m_items.GetSize(); it++ ) {
      static_cast<CControlUI*>(m_items[it])->SetVisible(bVisible);
   }
   CControlUI::SetVisible(bVisible);
}

void CContainerUI::Event(TEventUI& event)
{
   if( m_hwndScroll != NULL ) 
   {
      if( event.Type == UIEVENT_VSCROLL ) 
      {
         switch( LOWORD(event.wParam) ) {
         case SB_THUMBPOSITION:
         case SB_THUMBTRACK:
            {
               SCROLLINFO si = { 0 };
               si.cbSize = sizeof(SCROLLINFO);
               si.fMask = SIF_TRACKPOS;
               ::GetScrollInfo(m_hwndScroll, SB_CTL, &si);
               SetScrollPos(si.nTrackPos);
            }
            break;
         case SB_LINEUP:
            SetScrollPos(GetScrollPos() - 5);
            break;
         case SB_LINEDOWN:
            SetScrollPos(GetScrollPos() + 5);
            break;
         case SB_PAGEUP:
            SetScrollPos(GetScrollPos() - GetScrollPage());
            break;
         case SB_PAGEDOWN:
            SetScrollPos(GetScrollPos() + GetScrollPage());
            break;
         }
      }
      if( event.Type == UIEVENT_KEYDOWN ) 
      {
         switch( event.chKey ) {
         case VK_DOWN:
            SetScrollPos(GetScrollPos() + 5);
            return;
         case VK_UP:
            SetScrollPos(GetScrollPos() - 5);
            return;
         case VK_NEXT:
            SetScrollPos(GetScrollPos() + GetScrollPage());
            return;
         case VK_PRIOR:
            SetScrollPos(GetScrollPos() - GetScrollPage());
            return;
         case VK_HOME:
            SetScrollPos(0);
            return;
         case VK_END:
            SetScrollPos(9999);
            return;
         }
      }
   }
   CControlUI::Event(event);
}

int CContainerUI::GetScrollPos() const
{
   return m_iScrollPos;
}

int CContainerUI::GetScrollPage() const
{
   // TODO: Determine this dynamically
   return 40;
}

SIZE CContainerUI::GetScrollRange() const
{
   if( m_hwndScroll == NULL ) return CSize();
   int cx = 0, cy = 0;
   ::GetScrollRange(m_hwndScroll, SB_CTL, &cx, &cy);
   return CSize(cx, cy);
}

void CContainerUI::SetScrollPos(int iScrollPos)
{
   if( m_hwndScroll == NULL ) return;
   int iRange1 = 0, iRange2 = 0;
   ::GetScrollRange(m_hwndScroll, SB_CTL, &iRange1, &iRange2);
   iScrollPos = CLAMP(iScrollPos, iRange1, iRange2);
   ::SetScrollPos(m_hwndScroll, SB_CTL, iScrollPos, TRUE);
   m_iScrollPos = ::GetScrollPos(m_hwndScroll, SB_CTL);
   // Reposition children to the new viewport.
   SetPos(m_rcItem);
   Invalidate();
}

void CContainerUI::EnableScrollBar(bool bEnable)
{
   if( m_bAllowScrollbars == bEnable ) return;
   m_iScrollPos = 0;
   m_bAllowScrollbars = bEnable;
}

int CContainerUI::FindSelectable(int iIndex, bool bForward /*= true*/) const
{
   // NOTE: This is actually a helper-function for the list/combo/ect controls
   //       that allow them to find the next enabled/available selectable item
   if( GetCount() == 0 ) return -1;
   iIndex = CLAMP(iIndex, 0, GetCount() - 1);
   if( bForward ) {
      for( int i = iIndex; i < GetCount(); i++ ) {
         if( GetItem(i)->GetInterface(_T("ListItem")) != NULL 
             && GetItem(i)->IsVisible()
             && GetItem(i)->IsEnabled() ) return i;
      }
      return -1;
   }
   else {
      for( int i = iIndex; i >= 0; --i ) {
         if( GetItem(i)->GetInterface(_T("ListItem")) != NULL 
             && GetItem(i)->IsVisible()
             && GetItem(i)->IsEnabled() ) return i;
      }
      return FindSelectable(0, true);
   }
}

void CContainerUI::SetPos(RECT rc)
{
   CControlUI::SetPos(rc);
   if( m_items.IsEmpty() ) return;
   rc.left += m_rcInset.left;
   rc.top += m_rcInset.top;
   rc.right -= m_rcInset.right;
   rc.bottom -= m_rcInset.bottom;
   // We'll position the first child in the entire client area.
   // Do not leave a container empty.
   ASSERT(m_items.GetSize()==1);
   static_cast<CControlUI*>(m_items[0])->SetPos(rc);
}

SIZE CContainerUI::EstimateSize(SIZE /*szAvailable*/)
{
   return m_cxyFixed;
}

void CContainerUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("inset")) == 0 ) SetInset(CSize(_ttoi(pstrValue), _ttoi(pstrValue)));
   else if( _tcscmp(pstrName, _T("padding")) == 0 ) SetPadding(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("width")) == 0 ) SetWidth(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("height")) == 0 ) SetHeight(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("scrollbar")) == 0 ) EnableScrollBar(_tcscmp(pstrValue, _T("true")) == 0);
   else CControlUI::SetAttribute(pstrName, pstrValue);
}

void CContainerUI::SetManager(CPaintManagerUI* pManager, CControlUI* pParent)
{
   for( int it = 0; it < m_items.GetSize(); it++ ) {
      static_cast<CControlUI*>(m_items[it])->SetManager(pManager, this);
   }
   CControlUI::SetManager(pManager, pParent);
}

CControlUI* CContainerUI::FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)
{
   // Check if this guy is valid
   if( (uFlags & UIFIND_VISIBLE) != 0 && !IsVisible() ) return NULL;
   if( (uFlags & UIFIND_ENABLED) != 0 && !IsEnabled() ) return NULL;
   if( (uFlags & UIFIND_HITTEST) != 0 && !::PtInRect(&m_rcItem, *(static_cast<LPPOINT>(pData))) ) return NULL;
   if( (uFlags & UIFIND_ME_FIRST) != 0 ) {
      CControlUI* pControl = CControlUI::FindControl(Proc, pData, uFlags);
      if( pControl != NULL ) return pControl;
   }
   for( int it = 0; it != m_items.GetSize(); it++ ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[it])->FindControl(Proc, pData, uFlags);
      if( pControl != NULL ) return pControl;
   }
   return CControlUI::FindControl(Proc, pData, uFlags);
}

void CContainerUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   RECT rcTemp = { 0 };
   if( !::IntersectRect(&rcTemp, &rcPaint, &m_rcItem) ) return;

   CRenderClip clip;
   CBlueRenderEngineUI::GenerateClip(hDC, m_rcItem, clip);

   for( int it = 0; it < m_items.GetSize(); it++ ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[it]);
      if( !pControl->IsVisible() ) continue;
      if( !::IntersectRect(&rcTemp, &rcPaint, &pControl->GetPos()) ) continue;
      if( !::IntersectRect(&rcTemp, &m_rcItem, &pControl->GetPos()) ) continue;
      pControl->DoPaint(hDC, rcPaint);
   }
}

void CContainerUI::ProcessScrollbar(RECT rc, int cyRequired)
{
   // Need the scrollbar control, but it's been created already?
   if( cyRequired > rc.bottom - rc.top && m_hwndScroll == NULL && m_bAllowScrollbars ) {
      m_hwndScroll = ::CreateWindowEx(0, WC_SCROLLBAR, NULL, WS_CHILD | SBS_VERT, 0, 0, 0, 0, m_pManager->GetPaintWindow(), NULL, m_pManager->GetResourceInstance(), NULL);
      ASSERT(::IsWindow(m_hwndScroll));
      ::SetProp(m_hwndScroll, "WndX", static_cast<HANDLE>(this));
      ::SetScrollPos(m_hwndScroll, SB_CTL, 0, TRUE);
      ::ShowWindow(m_hwndScroll, SW_SHOWNOACTIVATE);
      SetPos(m_rcItem);
      return;
   }
   // No scrollbar required
   if( m_hwndScroll == NULL ) return;
   // Move it into place
   int cxScroll = m_pManager->GetSystemMetrics().cxvscroll;
   ::MoveWindow(m_hwndScroll, rc.right, rc.top, cxScroll, rc.bottom - rc.top, TRUE);
   // Scroll not needed anymore?
   int cyScroll = cyRequired - (rc.bottom - rc.top);
   if( cyScroll < 0 ) {
      if( m_iScrollPos != 0 ) SetScrollPos(0);
      cyScroll = 0;
   }
   // Scroll range changed?
   int cyOld1, cyOld2;
   ::GetScrollRange(m_hwndScroll, SB_CTL, &cyOld1, &cyOld2);
   if( cyOld2 != cyScroll ) {
      ::SetScrollRange(m_hwndScroll, SB_CTL, 0, cyScroll, FALSE);
      ::EnableScrollBar(m_hwndScroll, SB_CTL, cyScroll == 0 ? ESB_DISABLE_BOTH : ESB_ENABLE_BOTH);
   }
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CCanvasUI::CCanvasUI() : m_hBitmap(NULL), m_iOrientation(HTBOTTOMRIGHT)
{
}

CCanvasUI::~CCanvasUI()
{
   if( m_hBitmap != NULL ) ::DeleteObject(m_hBitmap);
}

LPCTSTR CCanvasUI::GetClass() const
{
   return _T("CanvasUI");
}

bool CCanvasUI::SetWatermark(UINT iBitmapRes, int iOrientation)
{
   return SetWatermark(MAKEINTRESOURCE(iBitmapRes), iOrientation);
}

bool CCanvasUI::SetWatermark(LPCTSTR pstrBitmap, int iOrientation)
{
   if( m_hBitmap != NULL ) ::DeleteObject(m_hBitmap);
   m_hBitmap = (HBITMAP) ::LoadImage(m_pManager->GetResourceInstance(), pstrBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
   ASSERT(m_hBitmap!=NULL);
   if( m_hBitmap == NULL ) return false;
   ::GetObject(m_hBitmap, sizeof(BITMAP), &m_BitmapInfo);
   m_iOrientation = iOrientation;
   Invalidate();
   return true;
}

void CCanvasUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   // Fill background
   RECT rcFill = { 0 };
   if( ::IntersectRect(&rcFill, &rcPaint, &m_rcItem) ) {
      CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcFill, m_clrBack);
   }
   // Paint watermark bitmap
   if( m_hBitmap != NULL ) {
      RECT rcBitmap = { 0 };
      switch( m_iOrientation ) {
      case HTTOPRIGHT:
         ::SetRect(&rcBitmap, m_rcItem.right - m_BitmapInfo.bmWidth, m_rcItem.top, m_rcItem.right, m_rcItem.top + m_BitmapInfo.bmHeight);
         break;
      case HTBOTTOMRIGHT:
         ::SetRect(&rcBitmap, m_rcItem.right - m_BitmapInfo.bmWidth, m_rcItem.bottom - m_BitmapInfo.bmHeight, m_rcItem.right, m_rcItem.bottom);
         break;
      default:
         ::SetRect(&rcBitmap, m_rcItem.right - m_BitmapInfo.bmWidth, m_rcItem.bottom - m_BitmapInfo.bmHeight, m_rcItem.right, m_rcItem.bottom);
         break;
      }
      RECT rcTemp = { 0 };
      if( ::IntersectRect(&rcTemp, &rcPaint, &rcBitmap) ) {
         CRenderClip clip;
         CBlueRenderEngineUI::GenerateClip(hDC, m_rcItem, clip);
         CBlueRenderEngineUI::DoPaintBitmap(hDC, m_pManager, m_hBitmap, rcBitmap);
      }
   }
   CContainerUI::DoPaint(hDC, rcPaint);
}

void CCanvasUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("watermark")) == 0 ) SetWatermark(pstrValue);
   else CContainerUI::SetAttribute(pstrName, pstrValue);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CWindowCanvasUI::CWindowCanvasUI()
{
   SetInset(CSize(10, 10));
   m_clrBack = m_pManager->GetThemeColor(UICOLOR_WINDOW_BACKGROUND);
}

LPCTSTR CWindowCanvasUI::GetClass() const
{
   return _T("WindowCanvasUI");
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CControlCanvasUI::CControlCanvasUI()
{
   SetInset(CSize(0, 0));
   m_clrBack = m_pManager->GetThemeColor(UICOLOR_CONTROL_BACKGROUND_NORMAL);
}

LPCTSTR CControlCanvasUI::GetClass() const
{
   return _T("ControlCanvasUI");
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CWhiteCanvasUI::CWhiteCanvasUI()
{
   SetInset(CSize(0, 0));
   m_clrBack = m_pManager->GetThemeColor(UICOLOR_STANDARD_WHITE);
}

LPCTSTR CWhiteCanvasUI::GetClass() const
{
   return _T("WhiteCanvasUI");
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CDialogCanvasUI::CDialogCanvasUI()
{
   SetInset(CSize(10, 10));
   m_clrBack = m_pManager->GetThemeColor(UICOLOR_DIALOG_BACKGROUND);
}

LPCTSTR CDialogCanvasUI::GetClass() const
{
   return _T("DialogCanvasUI");
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CTabFolderCanvasUI::CTabFolderCanvasUI()
{
   SetInset(CSize(0, 0));
   COLORREF clrColor1;
   m_pManager->GetThemeColorPair(UICOLOR_TAB_FOLDER_NORMAL, clrColor1, m_clrBack);
}

LPCTSTR CTabFolderCanvasUI::GetClass() const
{
   return _T("TabFolderCanvasUI");
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CVerticalLayoutUI::CVerticalLayoutUI() : m_cyNeeded(0)
{
}

LPCTSTR CVerticalLayoutUI::GetClass() const
{
   return _T("VertialLayoutUI");
}

void CVerticalLayoutUI::SetPos(RECT rc)
{
   m_rcItem = rc;
   // Adjust for inset
   rc.left += m_rcInset.left;
   rc.top += m_rcInset.top;
   rc.right -= m_rcInset.right;
   rc.bottom -= m_rcInset.bottom;
   if( m_hwndScroll != NULL ) rc.right -= m_pManager->GetSystemMetrics().cxvscroll;
   // Determine the minimum size
   SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };
   int nAdjustables = 0;
   int cyFixed = 0;
   for( int it1 = 0; it1 < m_items.GetSize(); it1++ ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[it1]);
      if( !pControl->IsVisible() ) continue;
      SIZE sz = pControl->EstimateSize(szAvailable);
      if( sz.cy == 0 ) nAdjustables++;
      cyFixed += sz.cy + m_iPadding;
   }
   // Place elements
   int cyNeeded = 0;
   int cyExpand = 0;
   if( nAdjustables > 0 ) cyExpand = MAX(0, (szAvailable.cy - cyFixed) / nAdjustables);
   // Position the elements
   SIZE szRemaining = szAvailable;
   int iPosY = rc.top - m_iScrollPos;
   int iAdjustable = 0;
   for( int it2 = 0; it2 < m_items.GetSize(); it2++ ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[it2]);
      if( !pControl->IsVisible() ) continue;
      SIZE sz = pControl->EstimateSize(szRemaining);
      if( sz.cy == 0 ) {
         iAdjustable++;
         sz.cy = cyExpand;
         // Distribute remaining to last element (usually round-off left-overs)
         if( iAdjustable == nAdjustables ) sz.cy += MAX(0, szAvailable.cy - (cyExpand * nAdjustables) - cyFixed);
      }
      RECT rcCtrl = { rc.left, iPosY, rc.right, iPosY + sz.cy };
      pControl->SetPos(rcCtrl);
      iPosY += sz.cy + m_iPadding;
      cyNeeded += sz.cy + m_iPadding;
      szRemaining.cy -= sz.cy + m_iPadding;
   }
   // Handle overflow with scrollbars
   ProcessScrollbar(rc, cyNeeded);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CHorizontalLayoutUI::CHorizontalLayoutUI()
{
}

LPCTSTR CHorizontalLayoutUI::GetClass() const
{
   return _T("HorizontalLayoutUI");
}

void CHorizontalLayoutUI::SetPos(RECT rc)
{
   m_rcItem = rc;
   // Adjust for inset
   rc.left += m_rcInset.left;
   rc.top += m_rcInset.top;
   rc.right -= m_rcInset.right;
   rc.bottom -= m_rcInset.bottom;
   // Determine the width of elements that are sizeable
   SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };
   int nAdjustables = 0;
   int cxFixed = 0;
   for( int it1 = 0; it1 < m_items.GetSize(); it1++ ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[it1]);
      if( !pControl->IsVisible() ) continue;
      SIZE sz = pControl->EstimateSize(szAvailable);
      if( sz.cx == 0 ) nAdjustables++;
      cxFixed += sz.cx + m_iPadding;
   }
   int cxExpand = 0;
   if( nAdjustables > 0 ) cxExpand = MAX(0, (szAvailable.cx - cxFixed) / nAdjustables);
   // Position the elements
   SIZE szRemaining = szAvailable;
   int iPosX = rc.left;
   int iAdjustable = 0;
   for( int it2 = 0; it2 < m_items.GetSize(); it2++ ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[it2]);
      if( !pControl->IsVisible() ) continue;
      SIZE sz = pControl->EstimateSize(szRemaining);
      if( sz.cx == 0 ) {
         iAdjustable++;
         sz.cx = cxExpand;
         if( iAdjustable == nAdjustables ) sz.cx += MAX(0, szAvailable.cx - (cxExpand * nAdjustables) - cxFixed);
      }
      RECT rcCtrl = { iPosX, rc.top, iPosX + sz.cx, rc.bottom };
      pControl->SetPos(rcCtrl);
      iPosX += sz.cx + m_iPadding;
      szRemaining.cx -= sz.cx + m_iPadding;
   }
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CTileLayoutUI::CTileLayoutUI() : m_nColumns(2), m_cyNeeded(0)
{
   SetPadding(10);
   SetInset(CSize(10, 10));
}

LPCTSTR CTileLayoutUI::GetClass() const
{
   return _T("TileLayoutUI");
}

void CTileLayoutUI::SetColumns(int nCols)
{
   if( nCols <= 0 ) return;
   m_nColumns = nCols;
   UpdateLayout();
}

void CTileLayoutUI::SetPos(RECT rc)
{
   m_rcItem = rc;
   // Adjust for inset
   rc.left += m_rcInset.left;
   rc.top += m_rcInset.top;
   rc.right -= m_rcInset.right;
   rc.bottom -= m_rcInset.bottom;
   if( m_hwndScroll != NULL ) rc.right -= m_pManager->GetSystemMetrics().cxvscroll;
   // Position the elements
   int cxWidth = (rc.right - rc.left) / m_nColumns;
   int cyHeight = 0;
   int iCount = 0;
   POINT ptTile = { rc.left, rc.top - m_iScrollPos };
   for( int it1 = 0; it1 < m_items.GetSize(); it1++ ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[it1]);
      if( !pControl->IsVisible() ) continue;
      // Determine size
      RECT rcTile = { ptTile.x, ptTile.y, ptTile.x + cxWidth, ptTile.y };
      // Adjust with element padding
      if( (iCount % m_nColumns) == 0 ) rcTile.right -= m_iPadding / 2;
      else if( (iCount % m_nColumns) == m_nColumns - 1 ) rcTile.left += m_iPadding / 2;
      else ::InflateRect(&rcTile, -(m_iPadding / 2), 0);
      // If this panel expands vertically
      if( m_cxyFixed.cy == 0) {
         SIZE szAvailable = { rcTile.right - rcTile.left, 9999 };
         int iIndex = iCount;
         for( int it2 = it1; it2 < m_items.GetSize(); it2++ ) {
            SIZE szTile = static_cast<CControlUI*>(m_items[it2])->EstimateSize(szAvailable);
            cyHeight = MAX(cyHeight, szTile.cy);
            if( (++iIndex % m_nColumns) == 0) break;
         }
      }
      // Set position
      rcTile.bottom = rcTile.top + cyHeight;
      pControl->SetPos(rcTile);
      // Move along...
      if( (++iCount % m_nColumns) == 0 ) {
         ptTile.x = rc.left;
         ptTile.y += cyHeight + m_iPadding;
         cyHeight = 0;
      }
      else {
         ptTile.x += cxWidth;
      }
      m_cyNeeded = rcTile.bottom - (rc.top - m_iScrollPos);
   }
   // Process the scrollbar
   ProcessScrollbar(rc, m_cyNeeded);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CDialogLayoutUI::CDialogLayoutUI() : m_bFirstResize(true), m_aModes(sizeof(STRETCHMODE))
{
   ::ZeroMemory(&m_rcDialog, sizeof(m_rcDialog));
}

LPCTSTR CDialogLayoutUI::GetClass() const
{
   return _T("DialogLayoutUI");
}

LPVOID CDialogLayoutUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("DialogLayout")) == 0 ) return this;
   return CContainerUI::GetInterface(pstrName);
}

void CDialogLayoutUI::SetStretchMode(CControlUI* pControl, UINT uMode)
{
   STRETCHMODE mode;
   mode.pControl = pControl;
   mode.uMode = uMode;
   mode.rcItem = pControl->GetPos();
   m_aModes.Add(&mode);
}

SIZE CDialogLayoutUI::EstimateSize(SIZE szAvailable)
{
   RecalcArea();
   return CSize(m_rcDialog.right - m_rcDialog.left, m_rcDialog.bottom - m_rcDialog.top);
}

void CDialogLayoutUI::SetPos(RECT rc)
{
   m_rcItem = rc;
   RecalcArea();
   // Do Scrollbar
   ProcessScrollbar(rc, m_rcDialog.bottom - m_rcDialog.top);
   if( m_hwndScroll != NULL ) rc.right -= m_pManager->GetSystemMetrics().cxvscroll;
   // Determine how "scaled" the dialog is compared to the original size
   int cxDiff = (rc.right - rc.left) - (m_rcDialog.right - m_rcDialog.left);
   int cyDiff = (rc.bottom - rc.top) - (m_rcDialog.bottom - m_rcDialog.top);
   if( cxDiff < 0 ) cxDiff = 0;
   if( cyDiff < 0 ) cyDiff = 0;
   // Stretch each control
   // Controls are coupled in "groups", which determine a scaling factor.
   // A "line" indicator is used to apply the same scaling to a new group of controls.
   int nCount, cxStretch, cyStretch, cxMove, cyMove;
   for( int i = 0; i < m_aModes.GetSize(); i++ ) {
      STRETCHMODE* pItem = static_cast<STRETCHMODE*>(m_aModes[i]);
      if( i == 0 || (pItem->uMode & UISTRETCH_NEWGROUP) != 0 ) {
         nCount = 0;
         for( int j = i + 1; j < m_aModes.GetSize(); j++ ) {
            STRETCHMODE* pNext = static_cast<STRETCHMODE*>(m_aModes[j]);
            if( (pNext->uMode & (UISTRETCH_NEWGROUP | UISTRETCH_NEWLINE)) != 0 ) break;
            if( (pNext->uMode & (UISTRETCH_SIZE_X | UISTRETCH_SIZE_Y)) != 0 ) nCount++;
         }
         if( nCount == 0 ) nCount = 1;
         cxStretch = cxDiff / nCount;
         cyStretch = cyDiff / nCount;
         cxMove = 0;
         cyMove = 0;
      }
      if( (pItem->uMode & UISTRETCH_NEWLINE) != 0 ) {
         cxMove = 0;
         cyMove = 0;
      }
      RECT rcPos = pItem->rcItem;
      ::OffsetRect(&rcPos, rc.left, rc.top - m_iScrollPos);
      if( (pItem->uMode & UISTRETCH_MOVE_X) != 0 ) ::OffsetRect(&rcPos, cxMove, 0);
      if( (pItem->uMode & UISTRETCH_MOVE_Y) != 0 ) ::OffsetRect(&rcPos, 0, cyMove);
      if( (pItem->uMode & UISTRETCH_SIZE_X) != 0 ) rcPos.right += cxStretch;
      if( (pItem->uMode & UISTRETCH_SIZE_Y) != 0 ) rcPos.bottom += cyStretch;
      if( (pItem->uMode & (UISTRETCH_SIZE_X | UISTRETCH_SIZE_Y)) != 0 ) {
         cxMove += cxStretch;
         cyMove += cyStretch;
      }      
      pItem->pControl->SetPos(rcPos);
   }
}

void CDialogLayoutUI::RecalcArea()
{
   if( !m_bFirstResize ) return;
   // Add the remaining control to the list
   // Controls that have specific stretching needs will define them in the XML resource
   // and by calling SetStretchMode(). Other controls needs to be added as well now...
   for( int it = 0; it < m_items.GetSize(); it++ ) {         
      CControlUI* pControl = static_cast<CControlUI*>(m_items[it]);
      bool bFound = false;
      for( int i = 0; !bFound && i < m_aModes.GetSize(); i++ ) {
         if( static_cast<STRETCHMODE*>(m_aModes[i])->pControl == pControl ) bFound = true;
      }
      if( !bFound ) {
         STRETCHMODE mode;
         mode.pControl = pControl;
         mode.uMode = UISTRETCH_NEWGROUP;
         mode.rcItem = pControl->GetPos();
         m_aModes.Add(&mode);
      }
   }
   // Figure out the actual size of the dialog so we can add proper scrollbars later
   CRect rcDialog(9999, 9999, 0,0);
   for( int i = 0; i < m_items.GetSize(); i++ ) {
      const RECT& rcPos = static_cast<CControlUI*>(m_items[i])->GetPos();
      rcDialog.Join(rcPos);
   }
   for( int j = 0; j < m_aModes.GetSize(); j++ ) {
      RECT& rcPos = static_cast<STRETCHMODE*>(m_aModes[j])->rcItem;
      ::OffsetRect(&rcPos, -rcDialog.left, -rcDialog.top);
   }
   m_rcDialog = rcDialog;
   // We're done with initialization
   m_bFirstResize = false;
}

