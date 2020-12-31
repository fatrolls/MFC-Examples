
#include "StdAfx.h"
#include "UIlist.h"

#include "UILabel.h"
#include "UIPanel.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListElementUI::CListElementUI() : 
   m_iIndex(-1),
   m_pOwner(NULL), 
   m_bSelected(false)
{
}

UINT CListElementUI::GetControlFlags() const
{
   return UIFLAG_WANTRETURN;
}

LPVOID CListElementUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("ListItem")) == 0 ) return static_cast<IListItemUI*>(this);
   return CControlUI::GetInterface(pstrName);
}

void CListElementUI::SetOwner(CControlUI* pOwner)
{
   m_pOwner = static_cast<IListOwnerUI*>(pOwner->GetInterface(_T("ListOwner")));
}

int CListElementUI::GetIndex() const
{
   return m_iIndex;
}

void CListElementUI::SetIndex(int iIndex)
{
   m_iIndex = iIndex;
}

bool CListElementUI::Activate()
{
   if( !CControlUI::Activate() ) return false;
   if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemactivate"));
   return true;
}

bool CListElementUI::IsSelected() const
{
   return m_bSelected;
}

bool CListElementUI::Select(bool bSelect)
{
   if( !IsEnabled() ) return false;
   if( bSelect == m_bSelected ) return true;
   m_bSelected = bSelect;
   if( bSelect && m_pOwner != NULL ) m_pOwner->SelectItem(m_iIndex);
   Invalidate();
   return true;
}

bool CListElementUI::IsExpanded() const
{
   return false;
}

bool CListElementUI::Expand(bool /*bExpand = true*/)
{
   return false;
}

void CListElementUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_DBLCLICK && IsEnabled() )
   {
      Activate();
      Invalidate();
      return;
   }
   if( event.Type == UIEVENT_KEYDOWN && IsEnabled() )
   {
      if( event.chKey == VK_RETURN ) {
         Activate();
         Invalidate();
         return;
      }
   }
   // An important twist: The list-item will send the event not to its immediate
   // parent but to the "attached" list. A list may actually embed several components
   // in its path to the item, but key-presses etc. needs to go to the actual list.
   if( m_pOwner != NULL ) m_pOwner->Event(event); else CControlUI::Event(event);
}

void CListElementUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("selected")) == 0 ) Select();
   else CControlUI::SetAttribute(pstrName, pstrValue);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListHeaderUI::CListHeaderUI()
{
   SetInset(CSize(0, 0));
}

LPCTSTR CListHeaderUI::GetClass() const
{
   return _T("ListHeaderUI");
}

LPVOID CListHeaderUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("ListHeader")) == 0 ) return this;
   return CHorizontalLayoutUI::GetInterface(pstrName);
}

SIZE CListHeaderUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(0, 6 + m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight);
}

void CListHeaderUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   // Draw background
   COLORREF clrBack1, clrBack2;
   m_pManager->GetThemeColorPair(UICOLOR_HEADER_BACKGROUND, clrBack1, clrBack2);
   CBlueRenderEngineUI::DoPaintFrame(hDC, m_pManager, m_rcItem, UICOLOR_HEADER_BORDER, UICOLOR_HEADER_BORDER, UICOLOR_HEADER_BACKGROUND, 0);
   RECT rcBottom = { m_rcItem.left + 1, m_rcItem.bottom - 3, m_rcItem.right - 1, m_rcItem.bottom };
   CBlueRenderEngineUI::DoPaintGradient(hDC, m_pManager, rcBottom, clrBack1, clrBack2, true, 4);
   // Draw headers too...
   CHorizontalLayoutUI::DoPaint(hDC, rcPaint);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListHeaderItemUI::CListHeaderItemUI() : m_uDragState(0)
{
}

LPCTSTR CListHeaderItemUI::GetClass() const
{
   return _T("ListHeaderItemUI");
}

void CListHeaderItemUI::SetText(LPCTSTR pstrText)
{
   m_sText = pstrText;
   UpdateLayout();
}

void CListHeaderItemUI::SetWidth(int cxWidth)
{
   m_cxWidth = cxWidth;
   UpdateLayout();
}

void CListHeaderItemUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("width")) == 0 ) SetWidth(_ttol(pstrValue));
   else CControlUI::SetAttribute(pstrName, pstrValue);
}

UINT CListHeaderItemUI::GetControlFlags() const
{
   return UIFLAG_SETCURSOR;
}

void CListHeaderItemUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_BUTTONDOWN && IsEnabled() )
   {
      RECT rcSeparator = GetThumbRect(m_rcItem);
      if( ::PtInRect(&rcSeparator, event.ptMouse) ) {
         m_uDragState |= UISTATE_CAPTURED;
         ptLastMouse = event.ptMouse;
         m_pManager->SendNotify(this, _T("headerdragging"));
      }
      else {
         m_pManager->SendNotify(this, _T("headerclick"));
      }
   }
   if( event.Type == UIEVENT_BUTTONUP )
   {
      if( (m_uDragState & UISTATE_CAPTURED) != 0 ) {
         m_uDragState &= ~UISTATE_CAPTURED;
         m_pManager->SendNotify(this, _T("headerdragged"));
         m_pManager->UpdateLayout();
      }
   }
   if( event.Type == UIEVENT_MOUSEMOVE )
   {
      if( (m_uDragState & UISTATE_CAPTURED) != 0 ) {
         RECT rc = m_rcItem;
         rc.right -= ptLastMouse.x - event.ptMouse.x;
         const int MIN_DRAGSIZE = 40;
         if( rc.right - rc.left > MIN_DRAGSIZE ) {
            m_rcItem = rc;
            m_cxWidth = rc.right - rc.left;
            ptLastMouse = event.ptMouse;
            m_pParent->Invalidate();
         }
      }
   }
   if( event.Type == UIEVENT_SETCURSOR )
   {
      RECT rcSeparator = GetThumbRect(m_rcItem);
      if( IsEnabled() && ::PtInRect(&rcSeparator, event.ptMouse) ) {
         ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
         return;
      }
   }
   CControlUI::Event(event);
}

SIZE CListHeaderItemUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(m_cxWidth, 14 + m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight);
}

void CListHeaderItemUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   // Paint text (with some indent)
   RECT rcMessage = m_rcItem;
   rcMessage.left += 6;
   rcMessage.bottom -= 1;
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcMessage, m_sText, UICOLOR_HEADER_TEXT, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | DT_VCENTER);
   // Draw gripper
   POINT ptTemp = { 0 };
   RECT rcThumb = GetThumbRect(m_rcItem);
   RECT rc1 = { rcThumb.left + 2, rcThumb.top + 4, rcThumb.left + 2, rcThumb.bottom - 1 };
   CBlueRenderEngineUI::DoPaintLine(hDC, m_pManager, rc1, UICOLOR_HEADER_SEPARATOR);
   RECT rc2 = { rcThumb.left + 3, rcThumb.top + 4, rcThumb.left + 3, rcThumb.bottom - 1 };
   CBlueRenderEngineUI::DoPaintLine(hDC, m_pManager, rc2, UICOLOR_STANDARD_WHITE);
}

RECT CListHeaderItemUI::GetThumbRect(RECT rc) const
{
   return CRect(rc.right - 4, rc.top, rc.right, rc.bottom - 3);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListFooterUI::CListFooterUI()
{
   CLabelPanelUI* pLabel = new CLabelPanelUI;
   Add(pLabel);
   CPaddingPanelUI* pPadding = new CPaddingPanelUI;
   Add(pPadding);
}

LPCTSTR CListFooterUI::GetClass() const
{
   return _T("ListFooterUI");
}

LPVOID CListFooterUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("ListFooter")) == 0 ) return this;
   return CHorizontalLayoutUI::GetInterface(pstrName);
}

SIZE CListFooterUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(0, 8 + m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight);
}

void CListFooterUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   COLORREF clrBack1, clrBack2;
   m_pManager->GetThemeColorPair(UICOLOR_HEADER_BACKGROUND, clrBack1, clrBack2);
   CBlueRenderEngineUI::DoPaintFrame(hDC, m_pManager, m_rcItem, UICOLOR_HEADER_BORDER, UICOLOR_HEADER_BORDER, UICOLOR_HEADER_BACKGROUND, 0);
   RECT rcTop = { m_rcItem.left + 1, m_rcItem.top, m_rcItem.right - 1, m_rcItem.top + 1 };
   CBlueRenderEngineUI::DoPaintGradient(hDC, m_pManager, rcTop, clrBack2, clrBack1, true, 2);
   RECT rcBottom = { m_rcItem.left + 1, m_rcItem.bottom - 3, m_rcItem.right - 1, m_rcItem.bottom };
   CBlueRenderEngineUI::DoPaintGradient(hDC, m_pManager, rcBottom, clrBack1, clrBack2, true, 4);
   // Paint items as well...
   CHorizontalLayoutUI::DoPaint(hDC, rcPaint);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListUI::CListUI() : m_pCallback(NULL), m_iCurSel(-1), m_iExpandedItem(-1)
{
   m_pList = new CVerticalLayoutUI;
   m_pHeader = new CListHeaderUI;
   m_pFooter = new CListFooterUI;

   CWhiteCanvasUI* pWhite = new CWhiteCanvasUI;
   pWhite->Add(m_pList);

   m_pFooter->Add(new CLabelPanelUI);
   m_pFooter->Add(new CPaddingPanelUI);

   Add(m_pHeader);
   CVerticalLayoutUI::Add(pWhite);
   Add(m_pFooter);

   m_pList->EnableScrollBar();

   ::ZeroMemory(&m_ListInfo, sizeof(TListInfoUI));
}

LPCTSTR CListUI::GetClass() const
{
   return _T("ListUI");
}

UINT CListUI::GetControlFlags() const
{
   return UIFLAG_TABSTOP;
}

LPVOID CListUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("List")) == 0 ) return static_cast<IListUI*>(this);
   if( _tcscmp(pstrName, _T("ListOwner")) == 0 ) return static_cast<IListOwnerUI*>(this);
   return CVerticalLayoutUI::GetInterface(pstrName);
}

bool CListUI::Add(CControlUI* pControl)
{
   // Override the Add() method so we can add items specifically to
   // the intended widgets. Headers and footers are assumed to be
   // answer the correct interface so we can add multiple list headers/footers.
   if( pControl->GetInterface(_T("ListHeader")) != NULL ) return CVerticalLayoutUI::Add(pControl);
   if( pControl->GetInterface(_T("ListFooter")) != NULL ) return CVerticalLayoutUI::Add(pControl);
   // We also need to recognize header sub-items
   if( _tcsstr(pControl->GetClass(), _T("Header")) != NULL ) return m_pHeader->Add(pControl);
   if( _tcsstr(pControl->GetClass(), _T("Footer")) != NULL ) return m_pFooter->Add(pControl);
   // The list items should know about us
   IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
   if( pListItem != NULL ) {
      pListItem->SetOwner(this);
      pListItem->SetIndex(GetCount());
   }
   return m_pList->Add(pControl);
}

bool CListUI::Remove(CControlUI* pControl)
{
   ASSERT(!"Not supported yet");
   return false; 
}

void CListUI::RemoveAll()
{
   m_iCurSel = -1;
   m_iExpandedItem = -1;
   m_pList->RemoveAll();
}

CControlUI* CListUI::GetItem(int iIndex) const
{
   return m_pList->GetItem(iIndex);
}

int CListUI::GetCount() const
{
   return m_pList->GetCount();
}

void CListUI::SetPos(RECT rc)
{
   CVerticalLayoutUI::SetPos(rc);
   if( m_pHeader == NULL ) return;
   // Determine general list information and the size of header columns
   m_ListInfo.Text = UICOLOR_CONTROL_TEXT_NORMAL;
   m_ListInfo.Background = UICOLOR__INVALID;
   m_ListInfo.SelText = UICOLOR_CONTROL_TEXT_SELECTED;
   m_ListInfo.SelBackground = UICOLOR_CONTROL_BACKGROUND_SELECTED;
   m_ListInfo.HotText = UICOLOR_CONTROL_TEXT_NORMAL;
   m_ListInfo.HotBackground = UICOLOR_CONTROL_BACKGROUND_HOVER;   
   m_ListInfo.nColumns = MIN(m_pHeader->GetCount(), UILIST_MAX_COLUMNS);
   // The header/columns may or may not be visible at runtime. In either case
   // we should determine the correct dimensions...
   if( m_pHeader->IsVisible() ) {
      for( int i = 0; i < m_ListInfo.nColumns; i++ ) m_ListInfo.rcColumn[i] = m_pHeader->GetItem(i)->GetPos();
   }
   else {
      RECT rcCol = { rc.left, 0, rc.left, 0 };
      for( int i = 0; i < m_ListInfo.nColumns; i++ ) {
         SIZE sz = m_pHeader->GetItem(i)->EstimateSize(CSize(rc.right - rc.left, rc.bottom - rc.top));
         rcCol.right += sz.cx;
         m_ListInfo.rcColumn[i] = rcCol;
         ::OffsetRect(&rcCol, sz.cx, 0);
      }
   }
}

void CListUI::Event(TEventUI& event)
{
   switch( event.Type ) {
   case UIEVENT_KEYDOWN:
      switch( event.chKey ) {
      case VK_UP:
         SelectItem(FindSelectable(m_iCurSel - 1, false));
         EnsureVisible(m_iCurSel);
         return;
      case VK_DOWN:
         SelectItem(FindSelectable(m_iCurSel + 1, true));
         EnsureVisible(m_iCurSel);
         return;
      case VK_PRIOR:
         SelectItem(FindSelectable(m_iCurSel - 10, false));
         EnsureVisible(m_iCurSel);
         return;
      case VK_NEXT:
         SelectItem(FindSelectable(m_iCurSel + 10, true));
         EnsureVisible(m_iCurSel);
         return;
      case VK_HOME:
         SelectItem(FindSelectable(0, false));
         EnsureVisible(m_iCurSel);
         return;
      case VK_END:
         SelectItem(FindSelectable(GetCount() - 1, true));
         EnsureVisible(m_iCurSel);
         return;
      case VK_RETURN:
         if( m_iCurSel != -1 ) GetItem(m_iCurSel)->Activate();
         return;
      }
      break;
   case UIEVENT_SCROLLWHEEL:
      {
         switch( LOWORD(event.wParam) ) {
         case SB_LINEUP:
            SelectItem(FindSelectable(m_iCurSel - 1, false));
            EnsureVisible(m_iCurSel);
            return;
         case SB_LINEDOWN:
            SelectItem(FindSelectable(m_iCurSel + 1, true));
            EnsureVisible(m_iCurSel);
            return;
         }
      }
      break;
   }
   CControlUI::Event(event);
}

CListHeaderUI* CListUI::GetHeader() const
{
   return m_pHeader;
}

CListFooterUI* CListUI::GetFooter() const
{
   return m_pFooter;
}

CContainerUI* CListUI::GetList() const
{
   return m_pList;
}

int CListUI::GetCurSel() const
{
   return m_iCurSel;
}

bool CListUI::SelectItem(int iIndex)
{
   if( iIndex == m_iCurSel ) return true;
   // We should first unselect the currently selected item
   if( m_iCurSel >= 0 ) {
      CControlUI* pControl = GetItem(m_iCurSel);
      if( pControl != NULL ) {
         IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
         if( pListItem != NULL ) pListItem->Select(false);
      }
   }
   // Now figure out if the control can be selected
   // TODO: Redo old selected if failure
   CControlUI* pControl = GetItem(iIndex);
   if( pControl == NULL ) return false;
   if( !pControl->IsVisible() ) return false;
   if( !pControl->IsEnabled() ) return false;
   IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
   if( pListItem == NULL ) return false;
   m_iCurSel = iIndex;
   if( !pListItem->Select(true) ) {
      m_iCurSel = -1;
      return false;
   }
   pControl->SetFocus();
   if( m_pManager != NULL ) {
      m_pManager->SendNotify(pControl, _T("itemclick"));
      m_pManager->SendNotify(this, _T("itemselect"));
   }
   Invalidate();
   return true;
}

const TListInfoUI* CListUI::GetListInfo() const
{
   return &m_ListInfo;
}

void CListUI::SetExpanding(bool bExpandable)
{
   m_ListInfo.bExpandable = bExpandable;
}

bool CListUI::ExpandItem(int iIndex, bool bExpand /*= true*/)
{
   if( !m_ListInfo.bExpandable ) return false;
   if( m_iExpandedItem >= 0 ) {
      CControlUI* pControl = GetItem(m_iExpandedItem);
      if( pControl != NULL ) {
         IListItemUI* pItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
         if( pItem != NULL ) pItem->Expand(false);
      }
      m_iExpandedItem = -1;
   }
   if( bExpand ) {
      CControlUI* pControl = GetItem(iIndex);
      if( pControl == NULL ) return false;
      if( !pControl->IsVisible() ) return false;
      IListItemUI* pItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
      if( pItem == NULL ) return false;
      m_iExpandedItem = iIndex;
      if( !pItem->Expand(true) ) {
         m_iExpandedItem = -1;
         return false;
      }
   }
   UpdateLayout();
   return true;
}

int CListUI::GetExpandedItem() const
{
   return m_iExpandedItem;
}

void CListUI::EnsureVisible(int iIndex)
{
   if( m_iCurSel < 0 ) return;
   RECT rcItem = m_pList->GetItem(iIndex)->GetPos();
   RECT rcList = m_pList->GetPos();
   int iPos = m_pList->GetScrollPos();
   if( rcItem.top >= rcList.top && rcItem.bottom < rcList.bottom ) return;
   int dx = 0;
   if( rcItem.top < rcList.top ) dx = rcItem.top - rcList.top;
   if( rcItem.bottom > rcList.bottom ) dx = rcItem.bottom - rcList.bottom;
   Scroll(0, dx);
}

void CListUI::Scroll(int dx, int dy)
{
   if( dx == 0 && dy == 0 ) return;
   m_pList->SetScrollPos(m_pList->GetScrollPos() + dy);
}

void CListUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("header")) == 0 ) GetHeader()->SetVisible(_tcscmp(pstrValue, _T("hidden")) != 0);
   else if( _tcscmp(pstrName, _T("footer")) == 0 ) GetFooter()->SetVisible(_tcscmp(pstrValue, _T("hidden")) != 0);
   else if( _tcscmp(pstrName, _T("expanding")) == 0 ) SetExpanding(_tcscmp(pstrValue, _T("true")) == 0);
   else CVerticalLayoutUI::SetAttribute(pstrName, pstrValue);
}

IListCallbackUI* CListUI::GetTextCallback() const
{
   return m_pCallback;
}

void CListUI::SetTextCallback(IListCallbackUI* pCallback)
{
   m_pCallback = pCallback;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListLabelElementUI::CListLabelElementUI() : m_cxWidth(0), m_uTextStyle(DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS), m_uButtonState(0)
{
}

LPCTSTR CListLabelElementUI::GetClass() const
{
   return _T("ListLabelElementUI");
}

void CListLabelElementUI::SetWidth(int cx)
{
   m_cxWidth = cx;
   Invalidate();
}

void CListLabelElementUI::SetTextStyle(UINT uStyle)
{
   m_uTextStyle = uStyle;
   Invalidate();
}

void CListLabelElementUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_BUTTONDOWN && IsEnabled() )
   {
      Select();
      Invalidate();
   }
   if( event.Type == UIEVENT_MOUSEENTER )
   {
      m_uButtonState |= UISTATE_HOT;
      Invalidate();
   }
   if( event.Type == UIEVENT_MOUSELEAVE )
   {
      if( (m_uButtonState & UISTATE_HOT) != 0 ) {
         m_uButtonState &= ~UISTATE_HOT;
         Invalidate();
      }
   }
   CListElementUI::Event(event);
}

void CListLabelElementUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("width")) == 0 ) {
      SetWidth(_ttoi(pstrValue));
   }
   else if( _tcscmp(pstrName, _T("align")) == 0 ) {
      if( _tcsstr(pstrValue, _T("center")) != NULL ) m_uTextStyle |= DT_CENTER;
      if( _tcsstr(pstrValue, _T("right")) != NULL ) m_uTextStyle |= DT_RIGHT;
   }
   else CListElementUI::SetAttribute(pstrName, pstrValue);
}

SIZE CListLabelElementUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(m_cxWidth, m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight + 8);
}

void CListLabelElementUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   DrawItem(hDC, GetPos(), 0);
}

void CListLabelElementUI::DrawItem(HDC hDC, const RECT& rcItem, UINT uDrawStyle)
{
   UITYPE_COLOR iTextColor = UICOLOR_CONTROL_TEXT_NORMAL;
   UITYPE_COLOR iBackColor = UICOLOR__INVALID;
   if( (m_uButtonState & UISTATE_HOT) != 0 ) {
      iTextColor = UICOLOR_CONTROL_TEXT_NORMAL;
      iBackColor = UICOLOR_CONTROL_BACKGROUND_HOVER;
   }
   if( m_bSelected ) {
      iTextColor = UICOLOR_CONTROL_TEXT_SELECTED;
      iBackColor = UICOLOR_CONTROL_BACKGROUND_SELECTED;
   }
   if( (uDrawStyle & UIDRAWSTYLE_INPLACE) != 0 )
   {
      iTextColor = UICOLOR_CONTROL_TEXT_NORMAL;
      iBackColor = UICOLOR_CONTROL_BACKGROUND_NORMAL;
   }
   if( (uDrawStyle & UIDRAWSTYLE_FOCUS) != 0 )
   {
      iTextColor = UICOLOR_CONTROL_TEXT_NORMAL;
      iBackColor = UICOLOR_CONTROL_BACKGROUND_HOVER;
   }
   if( !m_bEnabled ) {
      iTextColor = UICOLOR_CONTROL_TEXT_DISABLED;
      iBackColor = UICOLOR_CONTROL_BACKGROUND_DISABLED;
   }
   // Paint background (because we're vertically centering the text area
   // so it cannot paint the entire item rectangle)
   if( iBackColor != UICOLOR__INVALID ) {
      CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcItem, iBackColor);
   }
   // Paint text
   RECT rcText = rcItem;
   ::InflateRect(&rcText, -4, 0);
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcText, m_sText, iTextColor, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | m_uTextStyle);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListTextElementUI::CListTextElementUI() : m_cyItem(0), m_nLinks(0), m_pOwner(NULL)
{
   ::ZeroMemory(&m_rcLinks, sizeof(m_rcLinks));
}

LPCTSTR CListTextElementUI::GetClass() const
{
   return _T("ListTextElementUI");
}

UINT CListTextElementUI::GetControlFlags() const
{
   return UIFLAG_WANTRETURN | (m_nLinks > 0 ? UIFLAG_SETCURSOR : 0);
}

void CListTextElementUI::SetOwner(CControlUI* pOwner)
{
   CListElementUI::SetOwner(pOwner);
   m_pOwner = static_cast<IListUI*>(pOwner->GetInterface("List"));
}

void CListTextElementUI::Event(TEventUI& event)
{
   // When you hover over a link
   if( event.Type == UIEVENT_SETCURSOR ) {
      for( int i = 0; i < m_nLinks; i++ ) {
         if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) {
            ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
            return;
         }
      }      
   }
   if( m_nLinks > 0 && event.Type == UIEVENT_MOUSEMOVE ) Invalidate();
   if( m_nLinks > 0 && event.Type == UIEVENT_MOUSELEAVE ) Invalidate();
   CListLabelElementUI::Event(event);
}

SIZE CListTextElementUI::EstimateSize(SIZE szAvailable)
{
   if( m_pOwner == NULL ) return CSize();
   // We calculate the item height only once, because it will not wrap on the
   // line anyway when the screen is resized.
   if( m_cyItem == 0 ) {
      LPCTSTR pstrText = _T("XXX");
      RECT rcText = { 0, 0, 9999, 9999 };
      int nLinks = 0;
      CBlueRenderEngineUI::DoPaintPrettyText(m_pManager->GetPaintDC(), m_pManager, rcText, pstrText, UICOLOR__INVALID, UICOLOR__INVALID, NULL, nLinks, DT_CALCRECT | m_uTextStyle);
      m_cyItem = rcText.bottom - rcText.top;
   }
   return CSize(m_cxWidth, m_cyItem + 9);
}

void CListTextElementUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   DrawItem(hDC, m_rcItem, 0);
}

void CListTextElementUI::DrawItem(HDC hDC, const RECT& rcItem, UINT uStyle)
{
   ASSERT(m_pOwner);
   if( m_pOwner == NULL ) return;
   const TListInfoUI* pInfo = m_pOwner->GetListInfo();
   UITYPE_COLOR iTextColor = pInfo->Text;
   UITYPE_COLOR iBackColor = pInfo->Background;
   if( (m_uButtonState & UISTATE_HOT) != 0 ) {
      iBackColor = pInfo->HotBackground;
      iTextColor = pInfo->HotText;
   }
   if( IsSelected() ) {
      iTextColor = pInfo->SelText;
      iBackColor = pInfo->SelBackground;
   }
   if( !IsEnabled() ) {
      iTextColor = UICOLOR_CONTROL_TEXT_DISABLED;
      iBackColor = UICOLOR_CONTROL_BACKGROUND_DISABLED;
   }
   if( iBackColor != UICOLOR__INVALID ) {
      CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, m_rcItem, iBackColor);
   }
   IListCallbackUI* pCallback = m_pOwner->GetTextCallback();
   ASSERT(pCallback);
   if( pCallback == NULL ) return;
   m_nLinks = 0;
   int nLinks = lengthof(m_rcLinks);
   for( int i = 0; i < pInfo->nColumns; i++ )
   {
      // Paint text
      RECT rcItem = { pInfo->rcColumn[i].left, m_rcItem.top, pInfo->rcColumn[i].right, m_rcItem.bottom - 1 };
      LPCTSTR pstrText = pCallback->GetItemText(this, m_iIndex, i);
      ::InflateRect(&rcItem, -4, 0);
      CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcItem, pstrText, iTextColor, UICOLOR__INVALID, m_rcLinks, nLinks, DT_SINGLELINE | m_uTextStyle);
      if( nLinks > 0 ) m_nLinks = nLinks, nLinks = 0; else nLinks = lengthof(m_rcLinks);
   }
   RECT rcLine = { m_rcItem.left, m_rcItem.bottom - 1, m_rcItem.right, m_rcItem.bottom - 1 };
   CBlueRenderEngineUI::DoPaintLine(hDC, m_pManager, rcLine, UICOLOR_DIALOG_BACKGROUND);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListExpandElementUI::CListExpandElementUI() : m_bExpanded(false), m_cyExpanded(0), m_pContainer(NULL)
{
}

CListExpandElementUI::~CListExpandElementUI()
{
   delete m_pContainer;
}

LPCTSTR CListExpandElementUI::GetClass() const
{
   return _T("ListExpandElementUI");
}

bool CListExpandElementUI::Expand(bool bExpand)
{
   ASSERT(m_pOwner);
   if( m_pOwner == NULL ) return false;  
   if( bExpand == m_bExpanded ) return true;
   m_bExpanded = bExpand;
   if( !m_pOwner->ExpandItem(m_iIndex, bExpand) ) return false;
   // We need to manage the "expanding items", which are actually embedded controls
   // that we selectively display or not.
   if( bExpand ) 
   {
      delete m_pContainer;
      CTileLayoutUI* pTile = new CTileLayoutUI;
      pTile->SetPadding(4);
      m_pContainer = pTile;
      if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemexpand"));
      m_pManager->InitControls(m_pContainer, this);
   }
   else
   {
      if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemcollapse"));
   }
   m_cyExpanded = 0;
   return true;
}

bool CListExpandElementUI::IsExpanded() const
{
   return m_bExpanded;
}

void CListExpandElementUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_BUTTONUP )
   {
      if( m_pOwner == NULL ) return;
      const TListInfoUI* pInfo = m_pOwner->GetListInfo();
      RECT rcExpander = { m_rcItem.left, m_rcItem.top, m_rcItem.left + 20, m_rcItem.bottom };;
      if( pInfo->bExpandable && ::PtInRect(&rcExpander, event.ptMouse) ) Expand(!m_bExpanded);
   }
   if( event.Type == UIEVENT_KEYDOWN )
   {
      switch( event.chKey ) {
      case VK_LEFT:
         Expand(false);
         return;
      case VK_RIGHT:
         Expand(true);
         return;
      }
   }
   CListTextElementUI::Event(event);
}

SIZE CListExpandElementUI::EstimateSize(SIZE szAvailable)
{
   if( m_pOwner == NULL ) return CSize();
   // We calculate the item height only once, because it will not wrap on the
   // line anyway when the screen is resized.
   if( m_cyItem == 0 ) {
      LPCTSTR pstrText = _T("XXX");
      RECT rcText = { 0, 0, 9999, 9999 };
      int nLinks = 0;
      CBlueRenderEngineUI::DoPaintPrettyText(m_pManager->GetPaintDC(), m_pManager, rcText, pstrText, UICOLOR__INVALID, UICOLOR__INVALID, NULL, nLinks, DT_CALCRECT | m_uTextStyle);
      m_cyItem = (rcText.bottom - rcText.top) + 8;
   }
   int cyItem = m_cyItem;
   if( m_bExpanded && m_cyExpanded == 0 && m_pContainer != NULL && m_pContainer->GetCount() > 0 ) {
      RECT rcItem = m_pContainer->GetItem(0)->GetPos();
      // HACK: Here we boldy assume that the item height is the same as the listitem.
      m_cyExpanded = ((rcItem.bottom - rcItem.top) + 14) * ((m_pContainer->GetCount() + 1) / 2);
      m_cyExpanded += 4 * ((m_pContainer->GetCount() - 1) / 2);
      m_cyExpanded += 26;
   }
   return CSize(m_cxWidth, cyItem + m_cyExpanded + 1);
}

void CListExpandElementUI::SetPos(RECT rc)
{
   if( m_pContainer != NULL ) {
      RECT rcSubItems = { rc.left + 14, rc.top + m_cyItem, rc.right - 8, rc.bottom - 6 };
      m_pContainer->SetPos(rcSubItems);
   }
   CListTextElementUI::SetPos(rc);
}

bool CListExpandElementUI::Add(CControlUI* pControl)
{
   ASSERT(m_pContainer);
   if( m_pContainer == NULL ) return false;
   return m_pContainer->Add(pControl);
}

bool CListExpandElementUI::Remove(CControlUI* pControl)
{
   ASSERT(!"Not supported yet");
   return false; 
}

void CListExpandElementUI::RemoveAll()
{
   if( m_pContainer != NULL ) m_pContainer->RemoveAll();
}

CControlUI* CListExpandElementUI::GetItem(int iIndex) const
{
   if( m_pContainer == NULL ) return NULL;
   return m_pContainer->GetItem(iIndex);
}

int CListExpandElementUI::GetCount() const
{
   if( m_pContainer == NULL ) return 0;
   return m_pContainer->GetCount();
}

void CListExpandElementUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   CListTextElementUI::DoPaint(hDC, rcPaint);
   // Paint the expanded items?
   if( m_bExpanded && m_pContainer != NULL ) {
      // Paint gradient box for the items
      RECT rcFrame = m_pContainer->GetPos();
      COLORREF clr1, clr2;
      m_pManager->GetThemeColorPair(UICOLOR_CONTROL_BACKGROUND_EXPANDED, clr1, clr2);
      CBlueRenderEngineUI::DoPaintGradient(hDC, m_pManager, rcFrame, clr1, clr2, true, 64);
      CBlueRenderEngineUI::DoPaintRectangle(hDC, m_pManager, rcFrame, UICOLOR_HEADER_BORDER, UICOLOR__INVALID);
      RECT rcLine = { m_rcItem.left, rcFrame.top, m_rcItem.right, rcFrame.top };
      CBlueRenderEngineUI::DoPaintLine(hDC, m_pManager, rcLine, UICOLOR_STANDARD_BLACK);
      // We'll draw the items then...
      m_pContainer->DoPaint(hDC, rcPaint);
   }
}

void CListExpandElementUI::SetManager(CPaintManagerUI* pManager, CControlUI* pParent)
{
   if( m_pContainer != NULL ) m_pContainer->SetManager(pManager, pParent);
   CListTextElementUI::SetManager(pManager, pParent);
}

CControlUI* CListExpandElementUI::FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)
{
   CControlUI* pResult = NULL;
   if( m_pContainer != NULL ) pResult = m_pContainer->FindControl(Proc, pData, uFlags);
   if( pResult == NULL ) pResult = CListTextElementUI::FindControl(Proc, pData, uFlags);
   return pResult;
}

void CListExpandElementUI::DrawItem(HDC hDC, const RECT& rcItem, UINT uStyle)
{
   ASSERT(m_pOwner);
   if( m_pOwner == NULL ) return;
   const TListInfoUI* pInfo = m_pOwner->GetListInfo();
   UITYPE_COLOR iTextColor = pInfo->Text;
   UITYPE_COLOR iBackColor = pInfo->Background;
   if( (m_uButtonState & UISTATE_HOT) != 0 ) {
      iBackColor = pInfo->HotBackground;
      iTextColor = pInfo->HotText;
   }
   if( IsSelected() ) {
      iTextColor = pInfo->SelText;
      iBackColor = pInfo->SelBackground;
   }
   if( !IsEnabled() ) {
      iTextColor = UICOLOR_CONTROL_TEXT_DISABLED;
      iBackColor = UICOLOR_CONTROL_BACKGROUND_DISABLED;
   }
   if( iBackColor != UICOLOR__INVALID ) {
      RECT rcItem = { m_rcItem.left, m_rcItem.top, m_rcItem.right, m_rcItem.top + m_cyItem };
      CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcItem, iBackColor);
   }
   IListCallbackUI* pCallback = m_pOwner->GetTextCallback();
   ASSERT(pCallback);
   if( pCallback == NULL ) return;
   m_nLinks = 0;
   CStdString sColText;
   int nLinks = lengthof(m_rcLinks);
   for( int i = 0; i < pInfo->nColumns; i++ )
   {
      // Paint text
      RECT rcItem = { pInfo->rcColumn[i].left, m_rcItem.top, pInfo->rcColumn[i].right, m_rcItem.top + m_cyItem };
      LPCTSTR pstrText = pCallback->GetItemText(this, m_iIndex, i);
      // If list control is expandable then we'll automaticially draw
      // the expander-box at the first column.
      if( i == 0 && pInfo->bExpandable ) {
         sColText = (m_bExpanded ? _T("<i 14> ") : _T("<i 13> "));
         sColText += pstrText;
         pstrText = sColText;
      }
      ::InflateRect(&rcItem, -4, 0);
      CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcItem, pstrText, iTextColor, UICOLOR__INVALID, m_rcLinks, nLinks, DT_SINGLELINE | m_uTextStyle);
      if( nLinks > 0 ) m_nLinks = nLinks, nLinks = 0; else nLinks = lengthof(m_rcLinks);
   }
   RECT rcLine = { m_rcItem.left, m_rcItem.bottom - 1, m_rcItem.right, m_rcItem.bottom - 1 };
   CBlueRenderEngineUI::DoPaintLine(hDC, m_pManager, rcLine, UICOLOR_DIALOG_BACKGROUND);
}
