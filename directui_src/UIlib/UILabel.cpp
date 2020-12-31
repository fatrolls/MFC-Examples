
#include "StdAfx.h"
#include "UILabel.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

CLabelPanelUI::CLabelPanelUI() : m_cxWidth(0), m_uTextStyle(DT_VCENTER)
{
}

LPCTSTR CLabelPanelUI::GetClass() const
{
   return _T("LabelPanelUI");
}

void CLabelPanelUI::SetText(LPCTSTR pstrText)
{
   // Automatic assignment of keyboard shortcut
   if( _tcschr(pstrText, '&') != NULL ) m_chShortcut = *(_tcschr(pstrText, '&') + 1);
   CControlUI::SetText(pstrText);
}

void CLabelPanelUI::SetWidth(int cx)
{
   m_cxWidth = cx;
   UpdateLayout();
}

void CLabelPanelUI::SetTextStyle(UINT uStyle)
{
   m_uTextStyle = uStyle;
   Invalidate();
}

void CLabelPanelUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("align")) == 0 ) {
      if( _tcsstr(pstrValue, _T("center")) != NULL ) m_uTextStyle |= DT_CENTER;
      if( _tcsstr(pstrValue, _T("right")) != NULL ) m_uTextStyle |= DT_RIGHT;
   }
   else if( _tcscmp(pstrName, _T("width")) == 0 ) SetWidth(_ttoi(pstrValue));
   else CControlUI::SetAttribute(pstrName, pstrValue);
}

SIZE CLabelPanelUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(m_cxWidth, m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight + 4);
}

void CLabelPanelUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
   RECT rcText = m_rcItem;
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, m_pManager, rcText, m_sText, UICOLOR_EDIT_TEXT_NORMAL, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | m_uTextStyle);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

LPCTSTR CGreyTextHeaderUI::GetClass() const
{
   return _T("GreyTextHeaderUI");
}

SIZE CGreyTextHeaderUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(0, 12 + m_pManager->GetThemeFontInfo(UIFONT_BOLD).tmHeight + 12);
}

void CGreyTextHeaderUI::DoPaint(HDC hDC, const RECT& /*rcPaint*/)
{
   COLORREF clrDarkText = m_pManager->GetThemeColor(UICOLOR_DIALOG_TEXT_DARK);
   RECT rcLine = { m_rcItem.left, m_rcItem.bottom - 6, m_rcItem.right, m_rcItem.bottom - 5 };
   CBlueRenderEngineUI::DoFillRect(hDC, m_pManager, rcLine, UICOLOR_DIALOG_TEXT_DARK);
   CBlueRenderEngineUI::DoPaintQuickText(hDC, m_pManager, m_rcItem, m_sText, UICOLOR_DIALOG_TEXT_DARK, UIFONT_BOLD, DT_SINGLELINE);
}

