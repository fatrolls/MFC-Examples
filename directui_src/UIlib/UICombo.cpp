
#include "StdAfx.h"
#include "UICombo.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

CSingleLinePickUI::CSingleLinePickUI() : m_cxWidth(0), m_nLinks(0), m_uButtonState(0)
{
   ::ZeroMemory(&m_rcLinks, sizeof(m_rcLinks));
   ::ZeroMemory(&m_rcButton, sizeof(m_rcButton));
}

LPCTSTR CSingleLinePickUI::GetClass() const
{
   return _T("SinglePrettyEditUI");
}

UINT CSingleLinePickUI::GetControlFlags() const
{
   return UIFLAG_SETCURSOR | UIFLAG_TABSTOP;
}

void CSingleLinePickUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_SETCURSOR )
   {
      for( int i = 0; i < m_nLinks; i++ ) {
         if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) {
            ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
            return;
         }
      }      
   }
   if( event.Type == UIEVENT_BUTTONDOWN && IsEnabled() )
   {
      if( ::PtInRect(&m_rcButton, event.ptMouse) ) {
         m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
         Invalidate();
      }
      else {
         // Check for link press
         for( int i = 0; i < m_nLinks; i++ ) {
            if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) {
               m_pManager->SendNotify(this, _T("link"));
               return;
            }
         }      
      }
      return;
   }
   if( event.Type == UIEVENT_MOUSEMOVE )
   {
      if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
         if( ::PtInRect(&m_rcButton, event.ptMouse) ) m_uButtonState |= UISTATE_PUSHED;
         else m_uButtonState &= ~UISTATE_PUSHED;
         Invalidate();
      }
   }
   if( event.Type == UIEVENT_BUTTONUP )
   {
      if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
         if( ::PtInRect(&m_rcButton, event.ptMouse) ) m_pManager->SendNotify(this, _T("browse"));
         m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
         Invalidate();
      }
   }
   if( event.Type == UIEVENT_KEYDOWN ) 
   {
      if( event.chKey == VK_SPACE && m_nLinks > 0 ) m_pManager->SendNotify(this, _T("link"));
      if( event.chKey == VK_F4 && IsEnabled() ) m_pManager->SendNotify(this, _T("browse"));
   }
   CControlUI::Event(event);
}

void CSingleLinePickUI::SetWidth(int cxWidth)
{
   m_cxWidth = cxWidth;
   UpdateLayout();
}

SIZE CSingleLinePickUI::EstimateSize(SIZE /*szAvailable*/)
{
   SIZE sz = { 0, 12 + m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight };
   if( m_cxWidth > 0 ) {
      sz.cx = m_cxWidth;
      RECT rcText = m_rcItem;
      ::InflateRect(&rcText, -4, -2);
      m_nLinks = lengthof(m_rcLinks);
      CBlueRenderEngineUI::DoPaintPrettyText(m_pManager->GetPaintDC(), m_pManager, rcText, m_sText, UICOLOR_EDIT_TEXT_NORMAL, UICOLOR__INVALID, m_rcLinks, m_nLinks, DT_SINGLELINE | DT_CALCRECT);
      sz.cy = rcText.bottom - rcText.top;
   }
   return sz;
}

void CSingleLinePickUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   int cy = m_rcItem.bottom - m_rcItem.top;
   ::SetRect(&m_rcButton, m_rcItem.right - cy, m_rcItem.top, m_rcItem.right, m_rcItem.bottom);
   RECT rcText = { m_rcItem.left, m_rcItem.top, m_rcButton.left - 4, m_rcItem.bottom };
   UITYPE_COLOR iTextColor = UICOLOR_EDIT_TEXT_NORMAL;
   UITYPE_COLOR iBorderColor = UICOLOR_CONTROL_BORDER_NORMAL;
   UITYPE_COLOR iBackColor = UICOLOR_CONTROL_BACKGROUND_NORMAL;
   if( IsFocused() ) {
      iTextColor = UICOLOR_EDIT_TEXT_NORMAL;
      iBorderColor = UICOLOR_CONTROL_BORDER_NORMAL;
      iBackColor = UICOLOR_CONTROL_BACKGROUND_HOVER;
   }
   if( !IsEnabled() ) {
      iTextColor = UICOLOR_EDIT_TEXT_DISABLED;
      iBorderColor = UICOLOR_CONTROL_BORDER_DISABLED;
      iBackColor = UICOLOR__INVALID;
   }
   CBlueRenderEngineUI::DoPaintFrame(hDC, m_pManager, rcText, iBorderColor, iBorderColor, iBackColor);
   ::InflateRect(&rcText, -4, -2);
   m_nLinks = lengthof(m_rcLinks);
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcText, m_sText, iTextColor, UICOLOR__INVALID, m_rcLinks, m_nLinks, DT_SINGLELINE);
   RECT rcPadding = { 0 };
   CBlueRenderEngineUI::DoPaintButton(hDC, m_pManager, m_rcButton, _T("<i 4>"), rcPadding, m_uButtonState, 0);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

class CDropDownWnd : public CWindowWnd
{
public:
   void Init(CDropDownUI* pOwner);
   LPCTSTR GetWindowClassName() const;
   void OnFinalMessage(HWND hWnd);

   LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
   CPaintManagerUI m_pm;
   CDropDownUI* m_pOwner;
   int m_iOldSel;
};


void CDropDownWnd::Init(CDropDownUI* pOwner)
{
   m_pOwner = pOwner;
   m_iOldSel = m_pOwner->GetCurSel();
   // Position the popup window in absolute space
   SIZE szDrop = m_pOwner->GetDropDownSize();
   RECT rc = pOwner->GetPos();
   rc.top = rc.bottom;
   rc.bottom = rc.top + szDrop.cy;
   if( szDrop.cx > 0 ) rc.right = rc.left + szDrop.cx;
   MapWindowRect(pOwner->GetManager()->GetPaintWindow(), HWND_DESKTOP, &rc);
   Create(pOwner->GetManager()->GetPaintWindow(), NULL, WS_POPUP | WS_BORDER, WS_EX_TOOLWINDOW, rc);
   // HACK: Don't deselect the parent's caption
   HWND hWndParent = m_hWnd;
   while( ::GetParent(hWndParent) != NULL ) hWndParent = ::GetParent(hWndParent);
   ::ShowWindow(m_hWnd, SW_SHOW);
   ::SendMessage(hWndParent, WM_NCACTIVATE, TRUE, 0L);
}

LPCTSTR CDropDownWnd::GetWindowClassName() const
{
   return _T("DropDownWnd");
}

void CDropDownWnd::OnFinalMessage(HWND hWnd)
{
   delete this;
}

LRESULT CDropDownWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   if( uMsg == WM_CREATE ) {     
      m_pm.Init(m_hWnd);
      // The trick is to add the items to the new container. Their owner gets
      // reassigned by this operation - which is why it is important to reassign
      // the items back to the righfull owner/manager when the window closes.
      CControlCanvasUI* pWindow = new CControlCanvasUI;
      CVerticalLayoutUI* pLayout = new CVerticalLayoutUI;
      for( int i = 0; i < m_pOwner->GetCount(); i++ ) pLayout->Add(static_cast<CControlUI*>(m_pOwner->GetItem(i)));
      pLayout->SetAutoDestroy(false);
      pLayout->EnableScrollBar();
      pWindow->Add(pLayout);
      m_pm.AttachDialog(pWindow);
      return 0;
   }
   else if( uMsg == WM_CLOSE ) {
      m_pOwner->SetManager(m_pOwner->GetManager(), m_pOwner->GetParent());
      m_pOwner->SetPos(m_pOwner->GetPos());
      m_pOwner->SetFocus();
   }
   else if( uMsg == WM_LBUTTONUP ) {
      PostMessage(WM_KILLFOCUS);
   }
   else if( uMsg == WM_KEYDOWN ) {
      switch( wParam ) {
      case VK_ESCAPE:
         m_pOwner->SelectItem(m_iOldSel);
         // FALL THROUGH...
      case VK_RETURN:
         PostMessage(WM_KILLFOCUS);
         break;
      default:
         TEventUI event;
         event.Type = UIEVENT_KEYDOWN;
         event.chKey = wParam;
         m_pOwner->Event(event);
         return 0;
      }
   }
   else if( uMsg == WM_KILLFOCUS ) {
      if( m_hWnd != (HWND) wParam ) PostMessage(WM_CLOSE);
   }
   LRESULT lRes = 0;
   if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
   return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}


////////////////////////////////////////////////////////


CDropDownUI::CDropDownUI() : 
   m_iCurSel(-1), 
   m_uButtonState(0)
{
   m_szDropBox = CSize(0, 150);
   ::ZeroMemory(&m_rcButton, sizeof(RECT));
}

LPCTSTR CDropDownUI::GetClass() const
{
   return _T("DropDownUI");
}

LPVOID CDropDownUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("ListOwner")) == 0 ) return static_cast<IListOwnerUI*>(this);
   return CContainerUI::GetInterface(pstrName);
}

UINT CDropDownUI::GetControlFlags() const
{
   return UIFLAG_TABSTOP;
}

void CDropDownUI::Init()
{
   if( m_iCurSel < 0 ) SelectItem(0);
}

int CDropDownUI::GetCurSel() const
{
   return m_iCurSel;
}

bool CDropDownUI::SelectItem(int iIndex)
{
   if( iIndex == m_iCurSel ) return true;
   if( m_iCurSel >= 0 ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[m_iCurSel]);
      IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
      if( pListItem != NULL ) pListItem->Select(false);
      m_iCurSel = -1;
   }
   if( m_items.GetSize() == 0 ) return false;
   if( iIndex < 0 ) iIndex = 0;
   if( iIndex >= m_items.GetSize() ) iIndex = m_items.GetSize() - 1;
   CControlUI* pControl = static_cast<CControlUI*>(m_items[iIndex]);
   if( !pControl->IsVisible() ) return false;
   if( !pControl->IsEnabled() ) return false;
   IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
   if( pListItem == NULL ) return false;
   m_iCurSel = iIndex;
   pControl->SetFocus();
   pListItem->Select(true);
   if( m_pManager != NULL ) m_pManager->SendNotify(pControl, _T("itemclick"));
   if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemselect"));
   Invalidate();
   return true;
}

bool CDropDownUI::Add(CControlUI* pControl)
{
   IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
   if( pListItem != NULL ) {
      pListItem->SetOwner(this);
      pListItem->SetIndex(m_items.GetSize());
   }
   return CContainerUI::Add(pControl);
}

bool CDropDownUI::Remove(CControlUI* pControl)
{
   ASSERT(!"Not supported");
   return false;
}

void CDropDownUI::RemoveAll()
{
   m_iCurSel = -1;
   CContainerUI::RemoveAll();
}

void CDropDownUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_BUTTONDOWN && IsEnabled() )
   {
      Activate();
      m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
   }
   if( event.Type == UIEVENT_MOUSEMOVE )
   {
      if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
         if( ::PtInRect(&m_rcButton, event.ptMouse) ) m_uButtonState |= UISTATE_PUSHED;
         else m_uButtonState &= ~UISTATE_PUSHED;
         Invalidate();
      }
   }
   if( event.Type == UIEVENT_BUTTONUP )
   {
      if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
         m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
         Invalidate();
      }
   }
   if( event.Type == UIEVENT_KEYDOWN )
   {
      switch( event.chKey ) {
      case VK_F4:
         Activate();
         return;
      case VK_UP:
         SelectItem(FindSelectable(m_iCurSel - 1, false));
         return;
      case VK_DOWN:
         SelectItem(FindSelectable(m_iCurSel + 1, true));
         return;
      case VK_PRIOR:
         SelectItem(FindSelectable(m_iCurSel - 10, false));
         return;
      case VK_NEXT:
         SelectItem(FindSelectable(m_iCurSel + 10, true));
         return;
      case VK_HOME:
         SelectItem(FindSelectable(0, false));
         return;
      case VK_END:
         SelectItem(FindSelectable(GetCount() - 1, true));
         return;
      }
   }
   if( event.Type == UIEVENT_SCROLLWHEEL )
   {
      bool bDownward = LOWORD(event.wParam) == SB_LINEDOWN;
      SelectItem(FindSelectable(m_iCurSel + (bDownward ? 1 : -1), bDownward));
      return;
   }
   CControlUI::Event(event);
}

bool CDropDownUI::Activate()
{
   if( !CControlUI::Activate() ) return false;
   CDropDownWnd* pWindow = new CDropDownWnd;
   pWindow->Init(this);
   if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("dropdown"));
   Invalidate();
   return true;
}

CStdString CDropDownUI::GetText() const
{
   if( m_iCurSel < 0 ) return _T("");
   CControlUI* pControl = static_cast<CControlUI*>(m_items[m_iCurSel]);
   return pControl->GetText();
}

SIZE CDropDownUI::GetDropDownSize() const
{
   return m_szDropBox;
}

void CDropDownUI::SetDropDownSize(SIZE szDropBox)
{
   m_szDropBox = szDropBox;
}

void CDropDownUI::SetPos(RECT rc)
{
   // Put all elements out of sight
   RECT rcNull = { 0 };
   for( int i = 0; i < m_items.GetSize(); i++ ) static_cast<CControlUI*>(m_items[i])->SetPos(rcNull);
   // Position this control
   CControlUI::SetPos(rc);
}

SIZE CDropDownUI::EstimateSize(SIZE /*szAvailable*/)
{
   SIZE sz = { 0, 12 + m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight };
   // Once there is an element in the list, we'll use the first one to
   // determine the size of the dropdown base control.
   if( m_cxyFixed.cx > 0 && !m_items.IsEmpty() ) {
      RECT rcText = m_rcItem;
      ::InflateRect(&rcText, -4, -2);
      sz = static_cast<CControlUI*>(m_items[0])->EstimateSize(CSize(rcText.right - rcText.left, 0));
   }
   return sz;
}

void CDropDownUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   // Paint the nice frame
   int cy = m_rcItem.bottom - m_rcItem.top;
   ::SetRect(&m_rcButton, m_rcItem.right - cy, m_rcItem.top, m_rcItem.right, m_rcItem.bottom);
   RECT rcText = { m_rcItem.left, m_rcItem.top, m_rcButton.left + 1, m_rcItem.bottom };
   if( !IsEnabled() ) {
      CBlueRenderEngineUI::DoPaintFrame(hDC, m_pManager, rcText, UICOLOR_CONTROL_BORDER_DISABLED, UICOLOR__INVALID, UICOLOR__INVALID);
   }
   else {
      CBlueRenderEngineUI::DoPaintFrame(hDC, m_pManager, rcText, UICOLOR_CONTROL_BORDER_NORMAL, UICOLOR_CONTROL_BORDER_NORMAL, UICOLOR__INVALID);
   }
   // Paint dropdown edit box
   ::InflateRect(&rcText, -1, -1);
   if( m_iCurSel >= 0 ) {
      CControlUI* pControl = static_cast<CControlUI*>(m_items[m_iCurSel]);
      IListItemUI* pElement = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
      if( pElement != NULL ) {
         // Render item with specific draw-style
         pElement->DrawItem(hDC, rcText, UIDRAWSTYLE_INPLACE | (m_bFocused ? UIDRAWSTYLE_FOCUS : 0));
      }
      else {
         // Allow non-listitems to render as well.
         RECT rcOldPos = pControl->GetPos();
         pControl->SetPos(rcText);
         pControl->DoPaint(hDC, rcText);
         pControl->SetPos(rcOldPos);
      }
   }
   else {
      CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcText, UICOLOR_CONTROL_BACKGROUND_NORMAL);
   }
   // Paint dropdown button
   RECT rcPadding = { 0 };
   CBlueRenderEngineUI::DoPaintButton(hDC, m_pManager, m_rcButton, _T("<i 6>"), rcPadding, m_uButtonState, 0);
}

