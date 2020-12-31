
#include "StdAfx.h"
#include "UIBlue.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

LPCTSTR CStatusbarUI::GetClass() const
{
   return _T("StatusbarUI");
}

SIZE CStatusbarUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(0, 10 + m_pManager->GetThemeFontInfo(UIFONT_CAPTION).tmHeight);
}

void CStatusbarUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   CBlueRenderEngineUI::DoPaintPanel(hDC, m_pManager, m_rcItem);
   RECT rcMessage = m_rcItem;
   ::InflateRect(&rcMessage, -8, -2);
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcMessage, m_sText, UICOLOR_TITLE_TEXT, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | DT_VCENTER);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CToolbarTitlePanelUI::CToolbarTitlePanelUI() : m_iPadding(6)
{
}

LPCTSTR CToolbarTitlePanelUI::GetClass() const
{
   return _T("ToolbarTitlePanelUI");
}

SIZE CToolbarTitlePanelUI::EstimateSize(SIZE szAvailable)
{
   SIZE sz = { 0 };
   RECT rcText = { 0, 0, szAvailable.cx, szAvailable.cy };
   ::InflateRect(&rcText, -m_iPadding, -m_iPadding);
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(m_pManager->GetPaintDC(), m_pManager, rcText, m_sText, UICOLOR_EDIT_TEXT_NORMAL, UICOLOR__INVALID, NULL, nLinks, DT_WORDBREAK | DT_CALCRECT);
   sz.cy = (rcText.bottom - rcText.top) + (m_iPadding * 2);
   return sz;
}

void CToolbarTitlePanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   CBlueRenderEngineUI::DoPaintPanel(hDC, m_pManager, m_rcItem);
   RECT rcText = m_rcItem;
   ::InflateRect(&rcText, -m_iPadding, -m_iPadding);
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcText, m_sText, UICOLOR_TITLE_TEXT, UICOLOR__INVALID, NULL, nLinks, DT_WORDBREAK | DT_NOPREFIX);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CToolbarUI::CToolbarUI()
{
   SetInset(CSize(2, 2));
   SetPadding(2);
}

LPCTSTR CToolbarUI::GetClass() const
{
   return _T("ToolbarUI");
}

SIZE CToolbarUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(0, 10 + m_pManager->GetThemeFontInfo(UIFONT_CAPTION).tmHeight);
}

void CToolbarUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   CBlueRenderEngineUI::DoPaintPanel(hDC, m_pManager, m_rcItem);
   CContainerUI::DoPaint(hDC, rcPaint);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CToolButtonUI::CToolButtonUI()
{
}

LPCTSTR CToolButtonUI::GetClass() const
{
   return _T("ToolButtonUI");
}

void CToolButtonUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   UINT uState = 0;
   if( IsFocused() ) uState |= UISTATE_FOCUSED;
   if( !IsEnabled() ) uState |= UISTATE_DISABLED;
   CBlueRenderEngineUI::DoPaintToolbarButton(hDC, m_pManager, m_rcItem, m_sText, m_szPadding, m_uButtonState | uState);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

LPCTSTR CToolSeparatorUI::GetClass() const
{
   return _T("ToolSeparatorUI");
}

SIZE CToolSeparatorUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(4, 0);
}

void CToolSeparatorUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   RECT rc1 = { m_rcItem.left + 1, m_rcItem.top + 2, m_rcItem.left + 1, m_rcItem.bottom - 3 };
   CBlueRenderEngineUI::DoPaintLine(hDC, m_pManager, rc1, UICOLOR_TITLE_BORDER_DARK);
   RECT rc2 = { m_rcItem.left + 2, m_rcItem.top + 2, m_rcItem.left + 2, m_rcItem.bottom - 3 };
   CBlueRenderEngineUI::DoPaintLine(hDC, m_pManager, rc2, UICOLOR_TITLE_BORDER_LIGHT);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

LPCTSTR CToolGripperUI::GetClass() const
{
   return _T("ToolGripperUI");
}

SIZE CToolGripperUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(12, 0);
}

void CToolGripperUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   RECT rcLine = { m_rcItem.left + 5, m_rcItem.top + 6, m_rcItem.left + 5 + 3, m_rcItem.top + 6 };
   for( int i = m_rcItem.top + 6; i <= m_rcItem.bottom - 6; i += 2 ) {
      CBlueRenderEngineUI::DoPaintLine(hDC, m_pManager, rcLine, UICOLOR_TITLE_BORDER_DARK);
      ::OffsetRect(&rcLine, 0, 2);
   }
}

