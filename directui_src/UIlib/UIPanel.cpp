
#include "StdAfx.h"
#include "UIPanel.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

CNavigatorPanelUI::CNavigatorPanelUI() : m_iCurSel(-1)
{
}

LPCTSTR CNavigatorPanelUI::GetClass() const
{
   return _T("NavigatorPanelUI");
}

LPVOID CNavigatorPanelUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("ListOwner")) == 0 ) return static_cast<IListOwnerUI*>(this);
   return CVerticalLayoutUI::GetInterface(pstrName);
}

int CNavigatorPanelUI::GetCurSel() const
{
   return m_iCurSel;
}

void CNavigatorPanelUI::Event(TEventUI& event)
{
   CVerticalLayoutUI::Event(event);
}

bool CNavigatorPanelUI::SelectItem(int iIndex)
{
   if( iIndex == m_iCurSel ) return true;
   if( m_iCurSel >= 0 ) {
      CControlUI* pControl = GetItem(m_iCurSel);
      IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
      if( pListItem != NULL ) pListItem->Select(false);
   }
   m_iCurSel = iIndex;
   if( m_iCurSel >= 0 ) {
      CControlUI* pControl = GetItem(m_iCurSel);
      IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
      if( pListItem == NULL ) return false;
      pListItem->Select(true);
      if( m_pManager != NULL ) m_pManager->SendNotify(pControl, _T("itemclick"));
   }
   if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemselect"));
   Invalidate();
   return true;
}

bool CNavigatorPanelUI::Add(CControlUI* pControl)
{
   IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
   if( pListItem != NULL ) {
      pListItem->SetOwner(this);
      pListItem->SetIndex(m_items.GetSize());
   }
   return CContainerUI::Add(pControl);
}

SIZE CNavigatorPanelUI::EstimateSize(SIZE szAvailable)
{
   return CSize(0, 0);
}

void CNavigatorPanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   COLORREF clrFirst, clrSecond;
   m_pManager->GetThemeColorPair(UICOLOR_NAVIGATOR_BACKGROUND, clrFirst, clrSecond);
   CBlueRenderEngineUI::DoPaintGradient(hDC, m_pManager, m_rcItem, clrFirst, clrSecond, false, 64);
   CVerticalLayoutUI::DoPaint(hDC, rcPaint);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CNavigatorButtonUI::CNavigatorButtonUI() : m_uButtonState(0)
{
}

LPCTSTR CNavigatorButtonUI::GetClass() const
{
   return _T("NavigatorButton");
}

void CNavigatorButtonUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_BUTTONDOWN && IsEnabled() )
   {
      RECT rcButton = GetButtonRect(m_rcItem);
      if( ::PtInRect(&rcButton, event.ptMouse) ) {
         m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
         Invalidate();
      }
   }
   if( event.Type == UIEVENT_MOUSEMOVE )
   {
      if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
         RECT rcButton = GetButtonRect(m_rcItem);
         if( ::PtInRect(&rcButton, event.ptMouse) ) m_uButtonState |= UISTATE_PUSHED;
         else m_uButtonState &= ~UISTATE_PUSHED;
         Invalidate();
      }
   }
   if( event.Type == UIEVENT_BUTTONUP )
   {
      if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
         RECT rcButton = GetButtonRect(m_rcItem);
         if( ::PtInRect(&rcButton, event.ptMouse) ) {
            m_pManager->SendNotify(this, _T("link"));
            Select();
         }
         m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
         Invalidate();
      }
   }
}

SIZE CNavigatorButtonUI::EstimateSize(SIZE szAvailable)
{
   return CSize(0, 18 + m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight);
}

void CNavigatorButtonUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   DrawItem(hDC, m_rcItem, 0);
}

void CNavigatorButtonUI::DrawItem(HDC hDC, const RECT& rcItem, UINT uStyle)
{
   RECT rcButton = GetButtonRect(m_rcItem);

   if( (m_uButtonState & UISTATE_PUSHED) != 0 ) {
      CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcButton, UICOLOR_NAVIGATOR_BUTTON_PUSHED);
   }
   else if( m_bSelected ) {
      CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcButton, UICOLOR_NAVIGATOR_BUTTON_SELECTED);
   }
   else if( (m_uButtonState & UISTATE_PUSHED) != 0 ) {
      CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcButton, UICOLOR_NAVIGATOR_BUTTON_HOVER);
   }
   ::SelectObject(hDC, m_pManager->GetThemePen(m_bSelected ? UICOLOR_NAVIGATOR_BORDER_SELECTED : UICOLOR_NAVIGATOR_BORDER_NORMAL));
   POINT ptTemp = { 0 };
   ::MoveToEx(hDC, rcButton.left, rcButton.top, &ptTemp);
   ::LineTo(hDC, rcButton.left, rcButton.bottom);
   ::LineTo(hDC, rcButton.right, rcButton.bottom);

   UITYPE_COLOR iTextColor = UICOLOR_NAVIGATOR_TEXT_NORMAL;
   if( (m_uButtonState & UISTATE_PUSHED) != 0 ) iTextColor = UICOLOR_NAVIGATOR_TEXT_PUSHED;
   else if( m_bSelected ) iTextColor = UICOLOR_NAVIGATOR_TEXT_SELECTED;

   RECT rcText = rcButton;
   ::OffsetRect(&rcText, 0, 1);
   ::InflateRect(&rcText, -8, 0);
   if( (m_uButtonState & UISTATE_PUSHED) != 0 ) {
      rcText.left++; 
      rcText.top += 2;
   }
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcText, m_sText, iTextColor, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | DT_VCENTER);
}

RECT CNavigatorButtonUI::GetButtonRect(RECT rc) const
{
   int cy = m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight + 8;
   return CRect(rc.left + 10, rc.top, rc.right, rc.top + cy);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CTaskPanelUI::CTaskPanelUI() : m_hFadeBitmap(NULL)
{
   SetInset(CSize(8, 8));
   SetPadding(10);
   SetWidth(165);  // By default it gets a fixed 165 pixel width
}

CTaskPanelUI::~CTaskPanelUI()
{
   if( m_hFadeBitmap != NULL ) ::DeleteObject(m_hFadeBitmap);
   if( m_pManager != NULL ) m_pManager->KillTimer(this, FADE_TIMERID);
}

LPCTSTR CTaskPanelUI::GetClass() const
{
   return _T("TaskPanelUI");
}

SIZE CTaskPanelUI::EstimateSize(SIZE szAvailable)
{
   // The TaskPanel dissapears if the windows size becomes too small
   // Currently it is set to vasnish when its width gets below 1/4 of window.
   SIZE sz = m_cxyFixed;
   if( m_pManager->GetClientSize().cx <= m_cxyFixed.cx * 4 ) {
      // Generate a bitmap so we can paint this panel as slowly fading out.
      // Only do this when the control's size suddenly go below the threshold.
      if( m_rcItem.right - m_rcItem.left > 1 && m_hFadeBitmap == NULL ) {
         if( m_hFadeBitmap != NULL ) ::DeleteObject(m_hFadeBitmap);
         m_hFadeBitmap = CBlueRenderEngineUI::GenerateAlphaBitmap(m_pManager, this, m_rcItem, UICOLOR_DIALOG_BACKGROUND);
         // If we successfully created the 32bpp bitmap we'll set off the
         // timer so we can get animating...
         if( m_hFadeBitmap != NULL ) m_pManager->SetTimer(this, FADE_TIMERID, 50U);
         m_dwFadeTick = ::timeGetTime();
         m_rcFade = m_rcItem;
      }
      sz.cx = 1;
   }
   return sz;
}

void CTaskPanelUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_TIMER && event.wParam == FADE_TIMERID )
   {
      // The fading animation runs for 500ms. Then we kill
      // the bitmap which in turn disables the animation.
      if( event.dwTimestamp - m_dwFadeTick > FADE_DELAY ) {
         m_pManager->KillTimer(this, FADE_TIMERID);
         ::DeleteObject(m_hFadeBitmap);
         m_hFadeBitmap = NULL;
      }
      m_pManager->Invalidate(m_rcFade);
      return;
   }
   CVerticalLayoutUI::Event(event);
}

void CTaskPanelUI::SetPos(RECT rc)
{
   int cyFont = m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight;
   RECT rcClient = { rc.left, rc.top + cyFont + 6, rc.right, rc.bottom };
   CVerticalLayoutUI::SetPos(rcClient);
   m_rcItem = rc;
}

void CTaskPanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   // Handling gracefull fading of panel
   if( m_hFadeBitmap != NULL ) {
      DWORD dwTimeDiff = ::timeGetTime() - m_dwFadeTick;
      TPostPaintUI job;
      job.rc = m_rcFade;
      job.hBitmap = m_hFadeBitmap;
      job.iAlpha = (BYTE) CLAMP(255 - (long)(dwTimeDiff / (FADE_DELAY / 255.0)), 0, 255);
      m_pManager->AddPostPaintBlit(job);
   }
   // A tiny panel (see explaination in EstimateSize()) is invisible
   if( m_rcItem.right - m_rcItem.left < 2) return;
   // Paint caption
   int cyFont = m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight;
   RECT rcArc = { m_rcItem.left, m_rcItem.top, m_rcItem.right, m_rcItem.top + cyFont + 6 };
   CBlueRenderEngineUI::DoPaintArcCaption(hDC, m_pManager, rcArc, m_sText, UIARC_GRIPPER);
   // Paint background
   RECT rcClient = { m_rcItem.left, rcArc.bottom, m_rcItem.right, m_rcItem.bottom };
   COLORREF clrFirst, clrSecond;
   m_pManager->GetThemeColorPair(UICOLOR_TASK_BACKGROUND, clrFirst, clrSecond);
   CBlueRenderEngineUI::DoPaintGradient(hDC, m_pManager, rcClient, clrFirst, clrSecond, false, 128);
   CBlueRenderEngineUI::DoPaintFrame(hDC, m_pManager, rcClient, UICOLOR_TASK_CAPTION, UICOLOR_TASK_CAPTION, UICOLOR__INVALID, 0);
   // Paint elements
   CVerticalLayoutUI::DoPaint(hDC, rcPaint);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CSearchTitlePanelUI::CSearchTitlePanelUI() : m_iIconIndex(-1)
{
   SetInset(CSize(0, 0));
}

LPCTSTR CSearchTitlePanelUI::GetClass() const
{
   return _T("SearchTitlePanelUI");
}

void CSearchTitlePanelUI::SetImage(int iIndex)
{
   m_iIconIndex = iIndex;
}

void CSearchTitlePanelUI::SetPos(RECT rc)
{
   RECT rcClient = { rc.left + 1, rc.top + 35, rc.right - 1, rc.bottom - 1 };
   CHorizontalLayoutUI::SetPos(rcClient);
   m_rcItem = rc;
}

void CSearchTitlePanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   RECT rcFrame = { m_rcItem.left, m_rcItem.top + 34, m_rcItem.right, m_rcItem.bottom };
   CBlueRenderEngineUI::DoPaintFrame(hDC, m_pManager, rcFrame, UICOLOR_HEADER_SEPARATOR, UICOLOR_HEADER_SEPARATOR, UICOLOR_HEADER_BACKGROUND);
   RECT rcArc = { m_rcItem.left, m_rcItem.top + 14, m_rcItem.right, m_rcItem.top + 34 };
   RECT rcTemp = { 0 };
   if( ::IntersectRect(&rcTemp, &rcPaint, &rcArc) ) {
      CBlueRenderEngineUI::DoPaintArcCaption(hDC, m_pManager, rcArc, _T(""), 0);
   }
   if( m_iIconIndex >= 0 ) {
      HICON hIcon = m_pManager->GetThemeIcon(m_iIconIndex, 50);
      ::DrawIconEx(hDC, m_rcItem.left + 5, m_rcItem.top, hIcon, 50, 50, 0, NULL, DI_NORMAL);
      ::DestroyIcon(hIcon);
   }
   CHorizontalLayoutUI::DoPaint(hDC, rcPaint);
}

void CSearchTitlePanelUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("image")) == 0 ) SetImage(_ttoi(pstrValue));
   else CHorizontalLayoutUI::SetAttribute(pstrName, pstrValue);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CPaddingPanelUI::CPaddingPanelUI()
{
   m_cxyFixed.cx = m_cxyFixed.cy = 0;
}

CPaddingPanelUI::CPaddingPanelUI(int cx, int cy)
{
   m_cxyFixed.cx = cx;
   m_cxyFixed.cy = cy;
}

void CPaddingPanelUI::SetWidth(int cxWidth)
{
   m_cxyFixed.cx = cxWidth;
   UpdateLayout();
}

void CPaddingPanelUI::SetHeight(int cyHeight)
{
   m_cxyFixed.cy = cyHeight;
   UpdateLayout();
}

void CPaddingPanelUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("width")) == 0 ) SetWidth(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("height")) == 0 ) SetHeight(_ttoi(pstrValue));
   else CControlUI::SetAttribute(pstrName, pstrValue);
}

LPCTSTR CPaddingPanelUI::GetClass() const
{
   return _T("PaddingPanel");
}

SIZE CPaddingPanelUI::EstimateSize(SIZE szAvailable)
{
   return m_cxyFixed;
}

void CPaddingPanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CImagePanelUI::CImagePanelUI() : m_hBitmap(NULL)
{
   m_cxyFixed.cx = m_cxyFixed.cy = 0;
}

CImagePanelUI::~CImagePanelUI()
{
   if( m_hBitmap != NULL ) ::DeleteObject(m_hBitmap);
}

bool CImagePanelUI::SetImage(LPCTSTR pstrBitmap)
{
   if( m_hBitmap != NULL ) ::DeleteObject(m_hBitmap);
   m_hBitmap = (HBITMAP) ::LoadImage(m_pManager->GetResourceInstance(), pstrBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
   ASSERT(m_hBitmap);
   if( m_hBitmap == NULL ) return false;
   BITMAP bm = { 0 };
   ::GetObject(m_hBitmap, sizeof(BITMAP), &bm);
   SetWidth(bm.bmWidth);
   SetHeight(bm.bmHeight);
   return true;
}

void CImagePanelUI::SetWidth(int cxWidth)
{
   m_cxyFixed.cx = cxWidth;
   UpdateLayout();
}

void CImagePanelUI::SetHeight(int cyHeight)
{
   m_cxyFixed.cy = cyHeight;
   UpdateLayout();
}

void CImagePanelUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("width")) == 0 ) SetWidth(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("height")) == 0 ) SetHeight(_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("image")) == 0 ) SetImage(pstrValue);
   else CControlUI::SetAttribute(pstrName, pstrValue);
}

LPCTSTR CImagePanelUI::GetClass() const
{
   return _T("ImagePanel");
}

SIZE CImagePanelUI::EstimateSize(SIZE szAvailable)
{
   return m_cxyFixed;
}

void CImagePanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   CBlueRenderEngineUI::DoPaintBitmap(hDC, m_pManager, m_hBitmap, m_rcItem);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CTextPanelUI::CTextPanelUI() : m_nLinks(0), m_uButtonState(0), m_TextColor(UICOLOR_EDIT_TEXT_NORMAL), m_BackColor(UICOLOR__INVALID)
{
   m_uTextStyle = DT_WORDBREAK;
   ::ZeroMemory(m_rcLinks, sizeof(m_rcLinks));
}

LPCTSTR CTextPanelUI::GetClass() const
{
   return _T("TextPanelUI");
}

bool CTextPanelUI::Activate()
{
   if( !CLabelPanelUI::Activate() ) return false;
   if( m_nLinks > 0 ) m_pManager->SendNotify(this, _T("link"));
   return true;
}

void CTextPanelUI::SetTextColor(UITYPE_COLOR TextColor)
{
   m_TextColor = TextColor;
   Invalidate();
}

void CTextPanelUI::SetBkColor(UITYPE_COLOR BackColor)
{
   m_BackColor = BackColor;
   Invalidate();
}

UINT CTextPanelUI::GetControlFlags() const
{
   return m_nLinks > 0 ? UIFLAG_SETCURSOR : 0;
}

void CTextPanelUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_SETCURSOR ) {
      for( int i = 0; i < m_nLinks; i++ ) {
         if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) {
            ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
            return;
         }
      }      
   }
   if( event.Type == UIEVENT_BUTTONDOWN && IsEnabled() ) {
      for( int i = 0; i < m_nLinks; i++ ) {
         if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) {
            m_uButtonState |= UISTATE_PUSHED;
            Invalidate();
            return;
         }
      }      
   }
   if( event.Type == UIEVENT_BUTTONUP ) {
      for( int i = 0; i < m_nLinks; i++ ) {
         if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) Activate();
      }      
      m_uButtonState &= ~UISTATE_PUSHED;
      Invalidate();
      return;
   }
   // When you move over a link
   if( m_nLinks > 0 && event.Type == UIEVENT_MOUSEMOVE ) Invalidate();
   if( m_nLinks > 0 && event.Type == UIEVENT_MOUSELEAVE ) Invalidate();
   CLabelPanelUI::Event(event);
}

void CTextPanelUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("textColor")) == 0 ) SetTextColor((UITYPE_COLOR)_ttoi(pstrValue));
   else if( _tcscmp(pstrName, _T("backColor")) == 0 ) SetBkColor((UITYPE_COLOR)_ttoi(pstrValue));
   else CLabelPanelUI::SetAttribute(pstrName, pstrValue);
}

SIZE CTextPanelUI::EstimateSize(SIZE szAvailable)
{
   RECT rcText = { 0, 0, MAX(szAvailable.cx, m_cxWidth), 9999 };
   m_nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(m_pManager->GetPaintDC(), m_pManager, rcText, m_sText, UICOLOR_EDIT_TEXT_NORMAL, UICOLOR__INVALID, NULL, m_nLinks, DT_CALCRECT | m_uTextStyle);
   return CSize(rcText.right - rcText.left, rcText.bottom - rcText.left);
}

void CTextPanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   RECT rcText = m_rcItem;
   m_nLinks = lengthof(m_rcLinks);
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcText, m_sText, m_TextColor, m_BackColor, m_rcLinks, m_nLinks, m_uTextStyle);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CWarningPanelUI::CWarningPanelUI() : m_BackColor(UICOLOR_STANDARD_YELLOW)
{
}

LPCTSTR CWarningPanelUI::GetClass() const
{
   return _T("WarningPanelUI");
}

void CWarningPanelUI::SetWarningType(UINT uType)
{
   switch( uType ) {
   case MB_ICONERROR:
      m_BackColor = UICOLOR_STANDARD_RED;
      break;
   case MB_ICONWARNING:
      m_BackColor = UICOLOR_STANDARD_YELLOW;
      break;
   default:
      m_BackColor = UICOLOR_WINDOW_BACKGROUND;
      break;
   }
}

void CWarningPanelUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("type")) == 0 ) {
      if( _tcscmp(pstrValue, _T("error")) == 0 ) SetWarningType(MB_ICONERROR);
      if( _tcscmp(pstrValue, _T("warning")) == 0 ) SetWarningType(MB_ICONWARNING);
   }
   else CTextPanelUI::SetAttribute(pstrName, pstrValue);
}

SIZE CWarningPanelUI::EstimateSize(SIZE szAvailable)
{
   RECT rcText = { 0, 0, szAvailable.cx, szAvailable.cy };
   ::InflateRect(&rcText, -6, -4);
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(m_pManager->GetPaintDC(), m_pManager, rcText, m_sText, UICOLOR_EDIT_TEXT_NORMAL, UICOLOR__INVALID, NULL, nLinks, DT_WORDBREAK | DT_CALCRECT);
   return CSize(0, (rcText.bottom - rcText.top) + 16);
}

void CWarningPanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   RECT rcSign = m_rcItem;
   rcSign.bottom -= 8;
   CBlueRenderEngineUI::DoPaintFrame(hDC, m_pManager, rcSign, UICOLOR_STANDARD_GREY, UICOLOR_STANDARD_GREY, m_BackColor);
   RECT rcText = rcSign;
   ::InflateRect(&rcText, -6, -4);
   m_nLinks = lengthof(m_rcLinks);
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcText, m_sText, UICOLOR_BUTTON_TEXT_NORMAL, UICOLOR__INVALID, m_rcLinks, m_nLinks, DT_WORDBREAK);
}
