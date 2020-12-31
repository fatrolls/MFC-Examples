
#include "StdAfx.h"
#include "UIBlue.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

#ifndef BlendRGB
   #define BlendRGB(c1, c2, factor) \
      RGB( GetRValue(c1) + ((GetRValue(c2) - GetRValue(c1)) * factor / 100L), \
           GetGValue(c1) + ((GetGValue(c2) - GetGValue(c1)) * factor / 100L), \
           GetBValue(c1) + ((GetBValue(c2) - GetBValue(c1)) * factor / 100L) )
#endif


/////////////////////////////////////////////////////////////////////////////////////
//
//

CRenderClip::~CRenderClip()
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   ASSERT(::GetObjectType(hRgn)==OBJ_REGION);
   ASSERT(::GetObjectType(hOldRgn)==OBJ_REGION);
   ::SelectClipRgn(hDC, hOldRgn);
   ::DeleteObject(hOldRgn);
   ::DeleteObject(hRgn);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

void CBlueRenderEngineUI::GenerateClip(HDC hDC, RECT rcItem, CRenderClip& clip)
{
   RECT rcClip = { 0 };
   ::GetClipBox(hDC, &rcClip);
   clip.hOldRgn = ::CreateRectRgnIndirect(&rcClip);
   clip.hRgn = ::CreateRectRgnIndirect(&rcItem);
   ::ExtSelectClipRgn(hDC, clip.hRgn, RGN_AND);
   clip.hDC = hDC;
   clip.rcItem = rcItem;
}

void CBlueRenderEngineUI::DoFillRect(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, UITYPE_COLOR Color)
{
   DoFillRect(hDC, pManager, rcItem, pManager->GetThemeColor(Color));
}

void CBlueRenderEngineUI::DoFillRect(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, COLORREF clrFill)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   ::SetBkColor(hDC, clrFill);
   ::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rcItem, NULL, 0, NULL);
}

void CBlueRenderEngineUI::DoPaintLine(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, UITYPE_COLOR Color)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   POINT ptTemp = { 0 };
   ::SelectObject(hDC, pManager->GetThemePen(Color));
   ::MoveToEx(hDC, rcItem.left, rcItem.top, &ptTemp);
   ::LineTo(hDC, rcItem.right, rcItem.bottom);
}

void CBlueRenderEngineUI::DoPaintRectangle(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, UITYPE_COLOR Border, UITYPE_COLOR Fill)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   ::SelectObject(hDC, pManager->GetThemePen(Border));
   ::SelectObject(hDC, Fill == UICOLOR__INVALID ? ::GetStockObject(HOLLOW_BRUSH) : pManager->GetThemeBrush(Fill));
   ::Rectangle(hDC, rcItem.left, rcItem.top, rcItem.right, rcItem.bottom);
}

void CBlueRenderEngineUI::DoPaintPanel(HDC hDC, CPaintManagerUI* pManager, RECT rcItem)
{
   DoPaintFrame(hDC, pManager, rcItem, UICOLOR_TITLE_BORDER_LIGHT, UICOLOR_TITLE_BORDER_DARK, UICOLOR_TITLE_BACKGROUND);
}

void CBlueRenderEngineUI::DoPaintFrame(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, UITYPE_COLOR Light, UITYPE_COLOR Dark, UITYPE_COLOR Background, UINT uStyle)
{
   if( Background != UICOLOR__INVALID ) {
      DoFillRect(hDC, pManager, rcItem, Background);
   }
   if( (uStyle & UIFRAME_ROUND) != 0 )
   {
      POINT ptTemp;
      ::SelectObject(hDC, pManager->GetThemePen(Light));
      ::MoveToEx(hDC, rcItem.left, rcItem.bottom - 2, &ptTemp);
      ::LineTo(hDC, rcItem.left, rcItem.top + 1);
      ::LineTo(hDC, rcItem.left + 1, rcItem.top);
      ::LineTo(hDC, rcItem.right - 2, rcItem.top);
      ::SelectObject(hDC, pManager->GetThemePen(Dark));
      ::LineTo(hDC, rcItem.right - 1, rcItem.top + 1);
      ::LineTo(hDC, rcItem.right - 1, rcItem.bottom - 2);
      ::LineTo(hDC, rcItem.right - 2, rcItem.bottom - 1);
      ::LineTo(hDC, rcItem.left, rcItem.bottom - 1);
   }
   if( (uStyle & UIFRAME_FOCUS) != 0 )
   {
      HPEN hPen = ::CreatePen(PS_DOT, 1, pManager->GetThemeColor(UICOLOR_BUTTON_BORDER_FOCUS));
      HPEN hOldPen = (HPEN) ::SelectObject(hDC, hPen);
      POINT ptTemp;
      ::MoveToEx(hDC, rcItem.left, rcItem.bottom - 1, &ptTemp);
      ::LineTo(hDC, rcItem.left, rcItem.top);
      ::LineTo(hDC, rcItem.right - 1, rcItem.top);
      ::LineTo(hDC, rcItem.right - 1, rcItem.bottom - 1);
      ::LineTo(hDC, rcItem.left, rcItem.bottom - 1);
      ::SelectObject(hDC, hOldPen);
      ::DeleteObject(hPen);
   }
   else
   {
      POINT ptTemp;
      ::SelectObject(hDC, pManager->GetThemePen(Light));
      ::MoveToEx(hDC, rcItem.left, rcItem.bottom - 1, &ptTemp);
      ::LineTo(hDC, rcItem.left, rcItem.top);
      ::LineTo(hDC, rcItem.right - 1, rcItem.top);
      ::SelectObject(hDC, pManager->GetThemePen(Dark));
      ::LineTo(hDC, rcItem.right - 1, rcItem.bottom - 1);
      ::LineTo(hDC, rcItem.left, rcItem.bottom - 1);
   }
}

void CBlueRenderEngineUI::DoPaintBitmap(HDC hDC, CPaintManagerUI* pManager, HBITMAP hBmp, RECT rcBitmap)
{
   ASSERT(::GetObjectType(hBmp)==OBJ_BITMAP);
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   // Paint image
   HDC hdcBmp = ::CreateCompatibleDC(hDC);
   HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(hdcBmp, hBmp);
   ::BitBlt(hDC, rcBitmap.left, rcBitmap.top, rcBitmap.right - rcBitmap.left, rcBitmap.bottom - rcBitmap.top, hdcBmp, 0, 0, SRCCOPY);
   ::SelectObject(hdcBmp, hOldBitmap);
}

void CBlueRenderEngineUI::DoPaintArcCaption(HDC hDC, CPaintManagerUI* pManager, RECT rc, LPCTSTR pstrText, UINT uStyle)
{
   CRenderClip clip;
   GenerateClip(hDC, rc, clip);

   ::SelectObject(hDC, pManager->GetThemePen(UICOLOR_TASK_CAPTION));
   ::SelectObject(hDC, pManager->GetThemeBrush(UICOLOR_TASK_CAPTION));
   ::RoundRect(hDC, rc.left, rc.top, rc.right, rc.bottom + 15, 5, 5);

   RECT rcText = { rc.left, rc.top + 3, rc.right, rc.bottom };

   if( (uStyle & UIARC_GRIPPER) != 0 ) {
      RECT rcButton1 = { rc.left + 10, rc.top + 4, rc.left + 14, rc.top + 7 };
      DoPaintFrame(hDC, pManager, rcButton1, UICOLOR_TITLE_BORDER_LIGHT, UICOLOR_TITLE_BORDER_DARK, UICOLOR__INVALID, 0);
      RECT rcButton2 = { rc.left + 6, rc.top + 8, rc.left + 10, rc.top + 11 };
      DoPaintFrame(hDC, pManager, rcButton2, UICOLOR_TITLE_BORDER_LIGHT, UICOLOR_TITLE_BORDER_DARK, UICOLOR__INVALID, 0);
      RECT rcButton3 = { rc.left + 10, rc.top + 12, rc.left + 14, rc.top + 15 };
      DoPaintFrame(hDC, pManager, rcButton3, UICOLOR_TITLE_BORDER_LIGHT, UICOLOR_TITLE_BORDER_DARK, UICOLOR__INVALID, 0);
      rcText.left += 12;
   }
   rcText.left += 8;

   if( pstrText != NULL && _tcslen(pstrText) > 0 ) {
      int nLinks = 0;
      DoPaintPrettyText(hDC, pManager, rcText, pstrText, UICOLOR_TITLE_TEXT, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE);
   }
}

void CBlueRenderEngineUI::DoPaintButton(HDC hDC, CPaintManagerUI* pManager, RECT rc, LPCTSTR pstrText, RECT rcPadding, UINT uState, UINT uStyle)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   // Draw focus rectangle
   if( ((uState & UISTATE_FOCUSED) != 0) && pManager->GetSystemSettings().bShowKeyboardCues ) {
      CBlueRenderEngineUI::DoPaintFrame(hDC, pManager, rc, UICOLOR_BUTTON_BORDER_FOCUS, UICOLOR_BUTTON_BORDER_FOCUS, UICOLOR__INVALID, UIFRAME_ROUND);
      ::InflateRect(&rc, -1, -1);
   }
   // Draw frame and body
   COLORREF clrColor1, clrColor2;
   UITYPE_COLOR clrBorder1, clrBorder2, clrText, clrBack;
   if( (uState & UISTATE_DISABLED) != 0 ) {
      clrBorder1 = UICOLOR_BUTTON_BORDER_DISABLED;
      clrBorder2 = UICOLOR_BUTTON_BORDER_DISABLED;
      clrText = UICOLOR_BUTTON_TEXT_DISABLED;
      clrBack = UICOLOR_BUTTON_BACKGROUND_DISABLED;
   }
   else if( (uState & UISTATE_PUSHED) != 0 ) {
      clrBorder1 = UICOLOR_BUTTON_BORDER_DARK;
      clrBorder2 = UICOLOR_BUTTON_BORDER_LIGHT;
      clrText = UICOLOR_BUTTON_TEXT_PUSHED;
      clrBack = UICOLOR_BUTTON_BACKGROUND_PUSHED;
   }
   else {
      clrBorder1 = UICOLOR_BUTTON_BORDER_LIGHT;
      clrBorder2 = UICOLOR_BUTTON_BORDER_DARK;
      clrText = UICOLOR_BUTTON_TEXT_NORMAL;
      clrBack = UICOLOR_BUTTON_BACKGROUND_NORMAL;
   }
   // Draw button
   DoPaintFrame(hDC, pManager, rc, clrBorder1, clrBorder2, UICOLOR__INVALID, UIFRAME_ROUND);
   ::InflateRect(&rc, -1, -1);
   // The pushed button has an inner light shade
   if( (uState & UISTATE_PUSHED) != 0 ) {
      DoPaintFrame(hDC, pManager, rc, UICOLOR_STANDARD_LIGHTGREY, UICOLOR_STANDARD_LIGHTGREY, UICOLOR__INVALID);
      rc.top += 1;
      rc.left += 1;
   }
   // Gradient background
   pManager->GetThemeColorPair(clrBack, clrColor1, clrColor2);
   DoPaintGradient(hDC, pManager, rc, clrColor1, clrColor2, true, 32);
   // Draw hightlight inside button
   ::SelectObject(hDC, pManager->GetThemePen(UICOLOR_DIALOG_BACKGROUND));
   POINT ptTemp;
   ::MoveToEx(hDC, rc.left, rc.top, &ptTemp);
   ::LineTo(hDC, rc.left, rc.bottom - 1);
   ::LineTo(hDC, rc.right - 2, rc.bottom - 1);
   ::LineTo(hDC, rc.right - 2, rc.top);
   // Draw text
   RECT rcText = rc;
   ::InflateRect(&rcText, -1, -1);
   rcText.left += rcPadding.left;
   rcText.top += rcPadding.top;
   rcText.right -= rcPadding.right;
   rcText.bottom -= rcPadding.bottom;
   int nLinks = 0;
   DoPaintPrettyText(hDC, pManager, rcText, pstrText, clrText, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | uStyle);
}

void CBlueRenderEngineUI::DoPaintEditBox(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, LPCTSTR pstrText, UINT uState, UINT uDrawStyle, bool bPaintFrameOnly)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   if( (uState & UISTATE_DISABLED) != 0 ) {
      DoPaintFrame(hDC, pManager, rcItem, UICOLOR_CONTROL_BORDER_DISABLED, UICOLOR_CONTROL_BORDER_DISABLED, UICOLOR_EDIT_BACKGROUND_DISABLED);
   }
   else if( (uState & UISTATE_READONLY) != 0 ) {
      DoPaintFrame(hDC, pManager, rcItem, UICOLOR_CONTROL_BORDER_DISABLED, UICOLOR_CONTROL_BORDER_DISABLED, UICOLOR_EDIT_BACKGROUND_READONLY);
   }
   else {
      DoPaintFrame(hDC, pManager, rcItem, UICOLOR_CONTROL_BORDER_NORMAL, UICOLOR_CONTROL_BORDER_NORMAL, UICOLOR_EDIT_BACKGROUND_NORMAL);
   }
   if( bPaintFrameOnly ) return;
   // We should also draw the actual text
   COLORREF clrText = pManager->GetThemeColor(UICOLOR_EDIT_TEXT_NORMAL);
   if( (uState & UISTATE_READONLY) != 0 ) clrText = pManager->GetThemeColor(UICOLOR_EDIT_TEXT_READONLY);
   if( (uState & UISTATE_DISABLED) != 0 ) clrText = pManager->GetThemeColor(UICOLOR_EDIT_TEXT_DISABLED);
   ::SetBkMode(hDC, TRANSPARENT);
   ::SetTextColor(hDC, clrText);
   ::SelectObject(hDC, pManager->GetThemeFont(UIFONT_NORMAL));
   RECT rcEdit = rcItem;
   ::InflateRect(&rcEdit, -3, -2);
   ::DrawText(hDC, pstrText, -1, &rcEdit, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_EDITCONTROL | uDrawStyle);
}

void CBlueRenderEngineUI::DoPaintOptionBox(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, LPCTSTR pstrText, UINT uState, UINT uStyle)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   // Determine placement of elements
   RECT rcText = rcItem;
   RECT rcButton = rcItem;
   if( (uStyle & DT_RIGHT) != 0 ) {
      rcText.right -= 18;
      rcButton.left = rcButton.right - 18;
   }
   else {
      rcText.left += 18;
      rcButton.right = rcButton.left + 18;
   }
   bool bSelected = (uState & UISTATE_CHECKED) != 0;
   int iIcon = bSelected ? 8 : 9;
   if( (uState & UISTATE_PUSHED) != 0 ) iIcon = 10;
   if( (uState & UISTATE_DISABLED) != 0 ) iIcon = bSelected ? 10 : 11;
   HICON hIcon = pManager->GetThemeIcon(iIcon, 16);
   ::DrawIconEx(hDC, rcButton.left, rcButton.top, hIcon, 16, 16, 0, NULL, DI_NORMAL);
   ::DestroyIcon(hIcon);
   // Paint text
   UITYPE_COLOR iTextColor = ((uState & UISTATE_DISABLED) != 0) ? UICOLOR_EDIT_TEXT_DISABLED : UICOLOR_EDIT_TEXT_NORMAL;
   int nLinks = 0;
   CBlueRenderEngineUI::DoPaintPrettyText(hDC, pManager, rcText, pstrText, iTextColor, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE);
   // Paint focus rectangle
   if( ((uState & UISTATE_FOCUSED) != 0) && pManager->GetSystemSettings().bShowKeyboardCues ) {
      RECT rcFocus = { 0, 0, 9999, 9999 };;
      int nLinks = 0;
      CBlueRenderEngineUI::DoPaintPrettyText(hDC, pManager, rcFocus, pstrText, iTextColor, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | DT_CALCRECT);
      rcText.right = rcText.left + (rcFocus.right - rcFocus.left);
      rcText.bottom = rcText.top + (rcFocus.bottom - rcFocus.top);
      ::InflateRect(&rcText, 2, 0);
      CBlueRenderEngineUI::DoPaintFrame(hDC, pManager, rcText, UICOLOR_STANDARD_BLACK, UICOLOR_STANDARD_BLACK, UICOLOR__INVALID, UIFRAME_FOCUS);
   }
}

void CBlueRenderEngineUI::DoPaintTabFolder(HDC hDC, CPaintManagerUI* pManager, RECT& rcItem, LPCTSTR pstrText, UINT uState)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   ::SetBkMode(hDC, TRANSPARENT);
   ::SelectObject(hDC, pManager->GetThemeFont(UIFONT_NORMAL));
   CStdString sText = pstrText;
   sText.ProcessResourceTokens();
   int cchText = sText.GetLength();
   SIZE szText = { 0 };
   ::GetTextExtentPoint32(hDC, sText, cchText, &szText);
   RECT rcTab = { 0 };
   if( (uState & UISTATE_PUSHED) != 0 ) 
   {
      ::SetRect(&rcTab, rcItem.left, rcItem.top + 1, rcItem.left + szText.cx + 14, rcItem.bottom);
      DoFillRect(hDC, pManager, rcTab, UICOLOR_TAB_BACKGROUND_NORMAL);
      
      ::SelectObject(hDC, pManager->GetThemePen(UICOLOR_TAB_BORDER));
      POINT ptTemp;
      ::MoveToEx(hDC, rcTab.left, rcTab.bottom, &ptTemp);
      ::LineTo(hDC, rcTab.left, rcTab.top + 2);
      ::LineTo(hDC, rcTab.left + 1, rcTab.top + 1);
      ::LineTo(hDC, rcTab.right - 1, rcTab.top + 1);
      ::LineTo(hDC, rcTab.right, rcTab.top + 2);
      ::LineTo(hDC, rcTab.right, rcTab.bottom);
      ::SelectObject(hDC, pManager->GetThemePen(UICOLOR_TAB_BACKGROUND_NORMAL));
      ::LineTo(hDC, rcTab.left, rcTab.bottom);

      RECT rcText = { rcTab.left, rcTab.top + 1, rcTab.right, rcTab.bottom };
      int nLinks = 0;
      DoPaintPrettyText(hDC, pManager, rcText, pstrText, UICOLOR_TAB_TEXT_SELECTED, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

      RECT rcTop = { rcTab.left + 1, rcTab.top, rcTab.right - 1, rcTab.top + 3 };
      DoPaintGradient(hDC, pManager, rcTop, RGB(222,142,41), RGB(255,199,25), true, 4);
   }
   else if( (uState & UISTATE_DISABLED) != 0 )
   {
   }
   else
   {
      ::SetRect(&rcTab, rcItem.left, rcItem.top + 3, rcItem.left + szText.cx + 12, rcItem.bottom);
      
      COLORREF clrFolder1, clrFolder2;
      pManager->GetThemeColorPair(UICOLOR_TAB_FOLDER_NORMAL, clrFolder1, clrFolder2);
      DoPaintGradient(hDC, pManager, rcTab, clrFolder1, clrFolder2, true, 32);

      ::SelectObject(hDC, pManager->GetThemePen(UICOLOR_TAB_BORDER));
      POINT ptTemp;
      ::MoveToEx(hDC, rcTab.left, rcTab.bottom, &ptTemp);
      ::LineTo(hDC, rcTab.left, rcTab.top);
      ::LineTo(hDC, rcTab.right, rcTab.top);
      ::LineTo(hDC, rcTab.right, rcTab.bottom);

      RECT rcText = { rcTab.left, rcTab.top + 3, rcTab.right, rcTab.bottom };
      int nLinks = 0;
      DoPaintPrettyText(hDC, pManager, rcText, pstrText, UICOLOR_TAB_TEXT_NORMAL, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
   }
   rcItem = rcTab;
}

void CBlueRenderEngineUI::DoPaintToolbarButton(HDC hDC, CPaintManagerUI* pManager, RECT rc, LPCTSTR pstrText, SIZE szPadding, UINT uState)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   if( (uState & UISTATE_PUSHED) != 0 ) {
      DoPaintFrame(hDC, pManager, rc, UICOLOR_TOOL_BORDER_PUSHED, UICOLOR_TOOL_BORDER_PUSHED, UICOLOR_TOOL_BACKGROUND_PUSHED, 0);
      rc.top += 2;
      rc.left++;
   }
   else if( (uState & UISTATE_HOT) != 0 ) {
      DoPaintFrame(hDC, pManager, rc, UICOLOR_TOOL_BORDER_HOVER, UICOLOR_TOOL_BORDER_HOVER, UICOLOR_TOOL_BACKGROUND_HOVER, 0);
   }
   else if( (uState & UISTATE_DISABLED) != 0 ) {
      // TODO
   }
   RECT rcText = rc;
   int nLinks = 0;
   ::InflateRect(&rcText, -szPadding.cx, -szPadding.cy);
   DoPaintPrettyText(hDC, pManager, rcText, pstrText, UICOLOR_TITLE_TEXT, UICOLOR__INVALID, NULL, nLinks, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
}

void CBlueRenderEngineUI::DoPaintQuickText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCSTR pstrText, UITYPE_COLOR iTextColor, UITYPE_FONT iFont, UINT uStyle)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
   ::SetBkMode(hDC, TRANSPARENT);
   ::SetTextColor(hDC, pManager->GetThemeColor(iTextColor));
   ::SelectObject(hDC, pManager->GetThemeFont(iFont));
   ::DrawText(hDC, pstrText, -1, &rc, DT_SINGLELINE);
}

void CBlueRenderEngineUI::DoPaintPrettyText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, UITYPE_COLOR iTextColor, UITYPE_COLOR iBackColor, RECT* prcLinks, int& nLinkRects, UINT uStyle)
{
   ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);

   // The string formatter supports a kind of "mini-html" that consists of various short tags:
   //
   //   Link:             <a>text</a>
   //   Change font:      <f x>        where x = font id
   //   Bold:             <b>text</b>
   //   Indent:           <x i>        where i = indent in pixels
   //   Paragraph:        <p>
   //   Horizontal line:  <h>
   //   Icon:             <i x y>      where x = icon id and (optional) y = size (16/32/50)
   //                     <i x>        where x = icon resource name
   //   Color:            <c #xxxxxx>  where x = RGB in hex
   //                     <c x>        where x = color id
   //
   // In addition the standard string resource formats apply:
   //
   //   %{n}                           where n = resource-string-id
   //

   if( ::IsRectEmpty(&rc) ) return;

   bool bDraw = (uStyle & DT_CALCRECT) == 0;

   RECT rcClip = { 0 };
   ::GetClipBox(hDC, &rcClip);
   HRGN hOldRgn = ::CreateRectRgnIndirect(&rcClip);
   HRGN hRgn = ::CreateRectRgnIndirect(&rc);
   if( bDraw ) ::ExtSelectClipRgn(hDC, hRgn, RGN_AND);

   CStdString sText = pstrText;
   sText.ProcessResourceTokens();
   pstrText = sText;

   HFONT hOldFont = (HFONT) ::SelectObject(hDC, pManager->GetThemeFont(UIFONT_NORMAL));
   ::SetBkMode(hDC, TRANSPARENT);
   ::SetTextColor(hDC, pManager->GetThemeColor(iTextColor));

   // If the drawstyle includes an alignment, we'll need to first determine the text-size so
   // we can draw it at the correct position...
   if( (uStyle & DT_SINGLELINE) != 0 && (uStyle & DT_VCENTER) != 0 && (uStyle & DT_CALCRECT) == 0 ) {
      RECT rcText = { 0, 0, 9999, 100 };
      int nLinks = 0;
      DoPaintPrettyText(hDC, pManager, rcText, pstrText, iTextColor, iBackColor, NULL, nLinks, uStyle | DT_CALCRECT);
      rc.top = rc.top + ((rc.bottom - rc.top) / 2) - ((rcText.bottom - rcText.top) / 2);
      rc.bottom = rc.top + (rcText.bottom - rcText.top);
   }
   if( (uStyle & DT_SINGLELINE) != 0 && (uStyle & DT_CENTER) != 0 && (uStyle & DT_CALCRECT) == 0 ) {
      RECT rcText = { 0, 0, 9999, 100 };
      int nLinks = 0;
      DoPaintPrettyText(hDC, pManager, rcText, pstrText, iTextColor, iBackColor, NULL, nLinks, uStyle | DT_CALCRECT);
      ::OffsetRect(&rc, (rc.right - rc.left) / 2 - (rcText.right - rcText.left) / 2, 0);
   }
   if( (uStyle & DT_SINGLELINE) != 0 && (uStyle & DT_RIGHT) != 0 && (uStyle & DT_CALCRECT) == 0 ) {
      RECT rcText = { 0, 0, 9999, 100 };
      int nLinks = 0;
      DoPaintPrettyText(hDC, pManager, rcText, pstrText, iTextColor, iBackColor, NULL, nLinks, uStyle | DT_CALCRECT);
      rc.left = rc.right - (rcText.right - rcText.left);
   }

   // Paint backhground
   if( iBackColor != UICOLOR__INVALID ) DoFillRect(hDC, pManager, rc, iBackColor);

   // Determine if we're hovering over a link, because we would like to
   // indicate it by coloring the link text.
   // BUG: This assumes that the prcLink has already been filled once with
   //      link coordinates! That is usually not the case at first repaint. We'll clear
   //      the remanining entries at exit.
   int i;
   bool bHoverLink = false;
   POINT ptMouse = pManager->GetMousePos();
   for( i = 0; !bHoverLink && i < nLinkRects; i++ ) {
      if( ::PtInRect(prcLinks + i, ptMouse) ) bHoverLink = true;
   }

   TEXTMETRIC tm = pManager->GetThemeFontInfo(UIFONT_NORMAL);
   POINT pt = { rc.left, rc.top };
   int iLineIndent = 0;
   int iLinkIndex = 0;
   int cyLine = tm.tmHeight + tm.tmExternalLeading;
   int cyMinHeight = 0;
   POINT ptLinkStart = { 0 };
   bool bInLink = false;

   while( *pstrText != '\0' ) 
   {
      if( pt.x >= rc.right || *pstrText == '\n' ) 
      {
         // A new link was detected/requested. We'll adjust the line height
         // for the next line and expand the link hitbox (if any)
         if( bInLink && iLinkIndex < nLinkRects) ::SetRect(&prcLinks[iLinkIndex++], ptLinkStart.x, ptLinkStart.y, pt.x, pt.y + tm.tmHeight);
         if( (uStyle & DT_SINGLELINE) != 0 ) break;
         if( *pstrText == '\n' ) pstrText++;
         pt.x = rc.left + iLineIndent;
         pt.y += cyLine - tm.tmDescent;
         ptLinkStart = pt;
         cyLine = tm.tmHeight + tm.tmExternalLeading;
         if( pt.x >= rc.right ) break;
         while( *pstrText == ' ' ) pstrText++;
      }
      else if( *pstrText == '<' 
               && (pstrText[1] >= 'a' && pstrText[1] <= 'z')
               && (pstrText[2] == ' ' || pstrText[2] == '>') )
      {
         pstrText++;
         switch( *pstrText++ )
         {
         case 'a':  // Link
            {
               ::SetTextColor(hDC, pManager->GetThemeColor(bHoverLink ? UICOLOR_LINK_TEXT_HOVER : UICOLOR_LINK_TEXT_NORMAL));
               ::SelectObject(hDC, pManager->GetThemeFont(UIFONT_LINK));
               tm = pManager->GetThemeFontInfo(UIFONT_LINK);
               cyLine = MAX(cyLine, tm.tmHeight + tm.tmExternalLeading);
               ptLinkStart = pt;
               bInLink = true;
            }
            break;
         case 'f':  // Font
            {
               UITYPE_FONT iFont = (UITYPE_FONT) _tcstol(pstrText, const_cast<LPTSTR*>(&pstrText), 10);
               ::SelectObject(hDC, pManager->GetThemeFont(iFont));
               tm = pManager->GetThemeFontInfo(iFont);
               cyLine = MAX(cyLine, tm.tmHeight + tm.tmExternalLeading);
            }
            break;
         case 'b':  // Bold text
            {
               ::SelectObject(hDC, pManager->GetThemeFont(UIFONT_BOLD));
               tm = pManager->GetThemeFontInfo(UIFONT_BOLD);
               cyLine = MAX(cyLine, tm.tmHeight + tm.tmExternalLeading);
            }
            break;
         case 'x':  // Indent
            {
               iLineIndent = (int) _tcstol(pstrText, const_cast<LPTSTR*>(&pstrText), 10);
               if( pt.x < rc.left + iLineIndent ) pt.x = rc.left + iLineIndent;
            }
            break;
         case 'p':  // Paragraph
            {
               pt.x = rc.right;
               cyLine = MAX(cyLine, tm.tmHeight + tm.tmExternalLeading) + 5;
               iLineIndent = 0;
               ::SelectObject(hDC, pManager->GetThemeFont(UIFONT_NORMAL));
               ::SetTextColor(hDC, pManager->GetThemeColor(iTextColor));
               tm = pManager->GetThemeFontInfo(UIFONT_NORMAL);
            }
            break;
         case 'h':  // Horizontal line
            {
               ::SelectObject(hDC, pManager->GetThemePen(UICOLOR_STANDARD_GREY));
               if( bDraw ) {
                  POINT ptTemp = { 0 };
                  ::MoveToEx(hDC, pt.x, pt.y + 5, &ptTemp);
                  ::LineTo(hDC, rc.right - iLineIndent, pt.y + 5);
               }
               cyLine = 12;
            }
            break;
         case 'i':  // Icon
            {
               int iSize = 16;
               if( *pstrText == ' ' ) pstrText++;
               if( isdigit(*pstrText) ) {
                  int iIndex = (int) _tcstol(pstrText, const_cast<LPTSTR*>(&pstrText), 10);
                  iSize = MAX(16, _ttoi(pstrText));
                  if( bDraw ) {
                     HICON hIcon = pManager->GetThemeIcon(iIndex, iSize);
                     ASSERT(hIcon!=NULL);
                     ::DrawIconEx(hDC, pt.x, pt.y, hIcon, iSize, iSize, 0, NULL, DI_NORMAL);
                     ::DestroyIcon(hIcon);
                  }
               }
               else {
                  if( *pstrText == ' ' ) pstrText++;
                  CStdString sRes;
                  while( _istalnum(*pstrText) || *pstrText == '.' || *pstrText == '_' ) sRes += *pstrText++;
                  HICON hIcon = (HICON) ::LoadImage(pManager->GetResourceInstance(), sRes, IMAGE_ICON, 0, 0, LR_LOADTRANSPARENT | LR_SHARED);
                  ASSERT(hIcon!=NULL);
                  ICONINFO ii = { 0 };
                  ::GetIconInfo(hIcon, &ii);
                  BITMAP bi = { 0 };
                  ::GetObject(ii.hbmColor, sizeof(BITMAP), &bi);
                  iSize = bi.bmWidth;
                  if( bDraw ) ::DrawIconEx(hDC, pt.x, pt.y, hIcon, iSize, iSize, 0, NULL, DI_NORMAL);
                  ::DestroyIcon(hIcon);
               }
               // A special feature with an icon at the left edge is that it also sets
               // the paragraph indent.
               if( pt.x == rc.left ) iLineIndent = iSize + (iSize / 8); else cyLine = MAX(iSize, cyLine);
               pt.x += iSize + (iSize / 8);
               cyMinHeight = pt.y + iSize;
            }
            break;
         case 'c':  // Color
            {
               if( *pstrText == ' ' ) pstrText++;
               if( *pstrText == '#') {
                  pstrText++;
                  COLORREF clrColor = _tcstol(pstrText, const_cast<LPTSTR*>(&pstrText), 16);
                  clrColor = RGB(GetBValue(clrColor), GetGValue(clrColor), GetRValue(clrColor));
                  ::SetTextColor(hDC, clrColor);
               }
               else {
                  UITYPE_COLOR Color = (UITYPE_COLOR) _tcstol(pstrText, const_cast<LPTSTR*>(&pstrText), 10);
                  ::SetTextColor(hDC, pManager->GetThemeColor(Color));
               }
            }
            break;
         }
         while( *pstrText != '\0' && *pstrText != '>' ) pstrText++;
         pstrText++;
      }
      else if( *pstrText == '<' && pstrText[1] == '/' )
      {
         pstrText += 2;
         switch( *pstrText++ )
         {
         case 'a':
            if( iLinkIndex < nLinkRects ) ::SetRect(&prcLinks[iLinkIndex++], ptLinkStart.x, ptLinkStart.y, pt.x, pt.y + tm.tmHeight + tm.tmExternalLeading);
            ::SetTextColor(hDC, pManager->GetThemeColor(iTextColor));
            ::SelectObject(hDC, pManager->GetThemeFont(UIFONT_NORMAL));
            tm = pManager->GetThemeFontInfo(UIFONT_NORMAL);
            bInLink = false;
            break;
         case 'f':
         case 'b':
            // TODO: Use a context stack instead
            ::SelectObject(hDC, pManager->GetThemeFont(UIFONT_NORMAL));
            tm = pManager->GetThemeFontInfo(UIFONT_NORMAL);
            break;
         case 'c':
            ::SetTextColor(hDC, pManager->GetThemeColor(iTextColor));
            break;
         }
         while( *pstrText != '\0' && *pstrText != '>' ) pstrText++;
         pstrText++;
      }
      else if( *pstrText == '&' )
      {
         if( (uStyle & DT_NOPREFIX) == 0 ) {
            if( bDraw  && pManager->GetSystemSettings().bShowKeyboardCues ) ::TextOut(hDC, pt.x, pt.y, _T("_"), 1);
         }
         else {
            SIZE szChar = { 0 };
            ::GetTextExtentPoint32(hDC, _T("&"), 1, &szChar);
            if( bDraw ) ::TextOut(hDC, pt.x, pt.y, _T("&"), 1);
            pt.x += szChar.cx;
         }
         pstrText++;
      }
      else if( *pstrText == ' ' )
      {
         SIZE szSpace = { 0 };
         ::GetTextExtentPoint32(hDC, _T(" "), 1, &szSpace);
         // Still need to paint the space because the font might have
         // underline formatting.
         if( bDraw ) ::TextOut(hDC, pt.x, pt.y, _T(" "), 1);
         pt.x += szSpace.cx;
         pstrText++;
      }
      else
      {
         POINT ptPos = pt;
         int cchChars = 0;
         int cchLastGoodWord = 0;
         LPCTSTR p = pstrText;
         SIZE szText = { 0 };
         if( *p == '<' ) p++, cchChars++;
         while( *p != '\0' && *p != '<' && *p != '\n' && *p != '&' ) {
            // This part makes sure that we're word-wrapping if needed or providing support
            // for DT_END_ELLIPSIS. Unfortunately the GetTextExtentPoint32() call is pretty
            // slow when repeated so often.
            // TODO: Rewrite and use GetTextExtentExPoint() instead!
            cchChars++;
            szText.cx = cchChars * tm.tmMaxCharWidth;
            if( pt.x + szText.cx >= rc.right ) {
               ::GetTextExtentPoint32(hDC, pstrText, cchChars, &szText);
            }
            if( pt.x + szText.cx >= rc.right ) {
               if( (uStyle & DT_WORDBREAK) != 0 && cchLastGoodWord > 0 ) {
                  cchChars = cchLastGoodWord;
                  pt.x = rc.right;
               }
               if( (uStyle & DT_END_ELLIPSIS) != 0 && cchChars > 2 ) {
                  cchChars -= 2;
                  pt.x = rc.right;
               }
               break;
            }
            if( *p == ' ' ) cchLastGoodWord = cchChars;
            p = ::CharNext(p);
         }
         if( cchChars > 0 ) {
            ::GetTextExtentPoint32(hDC, pstrText, cchChars, &szText);
            if( bDraw ) {
               ::TextOut(hDC, ptPos.x, ptPos.y, pstrText, cchChars);
               if( pt.x == rc.right && (uStyle & DT_END_ELLIPSIS) != 0 ) ::TextOut(hDC, rc.right - 10, ptPos.y, _T("..."), 3);
            }
            pt.x += szText.cx;
            pstrText += cchChars;
         }
      }
      ASSERT(iLinkIndex<=nLinkRects);
   }

   // Clear remaining link rects and return number of used rects
   for( i = iLinkIndex; i < nLinkRects; i++ ) ::ZeroMemory(prcLinks + i, sizeof(RECT));
   nLinkRects = iLinkIndex;

   // Return size of text when requested
   if( (uStyle & DT_CALCRECT) != 0 ) {
      rc.bottom = MAX(cyMinHeight, pt.y + cyLine);
      if( rc.right >= 9999 ) {
         if( _tcslen(pstrText) > 0 ) pt.x += 3;
         rc.right = pt.x;
      }
   }

   if( bDraw ) ::SelectClipRgn(hDC, hOldRgn);
   ::DeleteObject(hOldRgn);
   ::DeleteObject(hRgn);

   ::SelectObject(hDC, hOldFont);
}

void CBlueRenderEngineUI::DoPaintGradient(HDC hDC, CPaintManagerUI* pManager, RECT rc, COLORREF clrFirst, COLORREF clrSecond, bool bVertical, int nSteps)
{
   typedef BOOL (WINAPI *PGradientFill)(HDC, PTRIVERTEX, ULONG, PVOID, ULONG, ULONG);
   static PGradientFill lpGradientFill = (PGradientFill) ::GetProcAddress(::GetModuleHandle("msimg32.dll"), "GradientFill");
   if( lpGradientFill != NULL ) 
   {
      // Use Windows gradient function from msimg32.dll
      // It may be slower than the code below but makes really pretty gradients on 16bit colors.
      TRIVERTEX triv[2] = 
      {
         { rc.left, rc.top, GetRValue(clrFirst) << 8, GetGValue(clrFirst) << 8, GetBValue(clrFirst) << 8, 0xFF00 },
         { rc.right, rc.bottom, GetRValue(clrSecond) << 8, GetGValue(clrSecond) << 8, GetBValue(clrSecond) << 8, 0xFF00 }
      };
      GRADIENT_RECT grc = { 0, 1 };
      lpGradientFill(hDC, triv, 2, &grc, 1, bVertical ? GRADIENT_FILL_RECT_V : GRADIENT_FILL_RECT_H);
   }
   else 
   {
      // Determine how many shades
      int nShift = 1;
      if( nSteps >= 64 ) nShift = 6;
      else if( nSteps >= 32 ) nShift = 5;
      else if( nSteps >= 16 ) nShift = 4;
      else if( nSteps >= 8 ) nShift = 3;
      else if( nSteps >= 4 ) nShift = 2;
      int nLines = 1 << nShift;
      for( int i = 0; i < nLines; i++ ) {
         // Do a little alpha blending
         BYTE bR = (BYTE) ((GetRValue(clrSecond) * (nLines - i) + GetRValue(clrFirst) * i) >> nShift);
         BYTE bG = (BYTE) ((GetGValue(clrSecond) * (nLines - i) + GetGValue(clrFirst) * i) >> nShift);
         BYTE bB = (BYTE) ((GetBValue(clrSecond) * (nLines - i) + GetBValue(clrFirst) * i) >> nShift);
         // ... then paint with the resulting color
         HBRUSH hBrush = ::CreateSolidBrush(RGB(bR,bG,bB));
         RECT r2 = rc;
         if( bVertical ) {
            r2.bottom = rc.bottom - ((i * (rc.bottom - rc.top)) >> nShift);
            r2.top = rc.bottom - (((i + 1) * (rc.bottom - rc.top)) >> nShift);
            if( (r2.bottom - r2.top) > 0 ) ::FillRect(hDC, &r2, hBrush);
         }
         else {
            r2.left = rc.right - (((i + 1) * (rc.right - rc.left)) >> nShift);
            r2.right = rc.right - ((i * (rc.right - rc.left)) >> nShift);
            if( (r2.right - r2.left) > 0 ) ::FillRect(hDC, &r2, hBrush);
         }
         ::DeleteObject(hBrush);
      }
   }
}

void CBlueRenderEngineUI::DoPaintAlphaBitmap(HDC hDC, CPaintManagerUI* pManager, HBITMAP hBitmap, RECT rc, BYTE iAlpha)
{
   // Alpha blitting is only supported of the msimg32.dll library is located on the machine.
   typedef BOOL (WINAPI *LPALPHABLEND)(HDC, int, int, int, int,HDC, int, int, int, int, BLENDFUNCTION);
   static LPALPHABLEND lpAlphaBlend = (LPALPHABLEND) ::GetProcAddress(::GetModuleHandle("msimg32.dll"), "AlphaBlend");
   if( lpAlphaBlend == NULL ) return;
   if( hBitmap == NULL ) return;
   HDC hCloneDC = ::CreateCompatibleDC(pManager->GetPaintDC());
   HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(hCloneDC, hBitmap);
   int cx = rc.right - rc.left;
   int cy = rc.bottom - rc.top;
   ::SetStretchBltMode(hDC, COLORONCOLOR);
   BLENDFUNCTION bf = { 0 };
   bf.BlendOp = AC_SRC_OVER; 
   bf.BlendFlags = 0; 
   bf.AlphaFormat = AC_SRC_ALPHA;
   bf.SourceConstantAlpha = iAlpha;
   lpAlphaBlend(hDC, rc.left, rc.top, cx, cy, hCloneDC, 0, 0, cx, cy, bf);
   ::SelectObject(hCloneDC, hOldBitmap);
   ::DeleteDC(hCloneDC);
}

void CBlueRenderEngineUI::DoAnimateWindow(HWND hWnd, UINT uStyle, DWORD dwTime /*= 200*/)
{
   typedef BOOL (CALLBACK* PFNANIMATEWINDOW)(HWND, DWORD, DWORD);
#ifndef AW_HIDE
   const DWORD AW_HIDE = 0x00010000;
   const DWORD AW_BLEND = 0x00080000;
#endif
   // Mix flags
   DWORD dwFlags = 0;
   if( (uStyle & UIANIM_HIDE) != 0 ) dwFlags |= AW_HIDE;
   if( (uStyle & UIANIM_FADE) != 0 ) dwFlags |= AW_BLEND;
   PFNANIMATEWINDOW pfnAnimateWindow = (PFNANIMATEWINDOW) ::GetProcAddress(::GetModuleHandle(_T("user32.dll")), "AnimateWindow");
   if( pfnAnimateWindow != NULL ) pfnAnimateWindow(hWnd, dwTime, dwFlags);
}

HBITMAP CBlueRenderEngineUI::GenerateAlphaBitmap(CPaintManagerUI* pManager, CControlUI* pControl, RECT rc, UITYPE_COLOR Background)
{
   typedef BOOL (WINAPI *LPALPHABLEND)(HDC, int, int, int, int,HDC, int, int, int, int, BLENDFUNCTION);
   static FARPROC lpAlphaBlend = ::GetProcAddress(::GetModuleHandle("msimg32.dll"), "AlphaBlend");
   if( lpAlphaBlend == NULL ) return NULL;
   int cx = rc.right - rc.left;
   int cy = rc.bottom - rc.top;

   // Let the control paint itself onto an offscreen bitmap
   HDC hPaintDC = ::CreateCompatibleDC(pManager->GetPaintDC());
   HBITMAP hPaintBitmap = ::CreateCompatibleBitmap(pManager->GetPaintDC(), rc.right, rc.bottom);
   ASSERT(hPaintDC);
   ASSERT(hPaintBitmap);
   HBITMAP hOldPaintBitmap = (HBITMAP) ::SelectObject(hPaintDC, hPaintBitmap);
   DoFillRect(hPaintDC, pManager, rc, Background);
   pControl->DoPaint(hPaintDC, rc);

   // Create a new 32bpp bitmap with room for an alpha channel
   BITMAPINFO bmi = { 0 };
   bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bmi.bmiHeader.biWidth = cx;
   bmi.bmiHeader.biHeight = cy;
   bmi.bmiHeader.biPlanes = 1;
   bmi.bmiHeader.biBitCount = 32;
   bmi.bmiHeader.biCompression = BI_RGB;
   bmi.bmiHeader.biSizeImage = cx * cy * sizeof(DWORD);
   LPDWORD pDest = NULL;
   HDC hCloneDC = ::CreateCompatibleDC(pManager->GetPaintDC());
   HBITMAP hBitmap = ::CreateDIBSection(pManager->GetPaintDC(), &bmi, DIB_RGB_COLORS, (LPVOID*) &pDest, NULL, 0);
   ASSERT(hCloneDC);
   ASSERT(hBitmap);
   if( hBitmap != NULL )
   {
      // Copy offscreen bitmap to our new 32bpp bitmap
      HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(hCloneDC, hBitmap);
      ::BitBlt(hCloneDC, 0, 0, cx, cy, hPaintDC, rc.left, rc.top, SRCCOPY);
      ::SelectObject(hCloneDC, hOldBitmap);
      ::DeleteDC(hCloneDC);  
      ::GdiFlush();

      // Make the background color transparent
      COLORREF clrBack = pManager->GetThemeColor(Background);
      DWORD dwKey = RGB(GetBValue(clrBack), GetGValue(clrBack), GetRValue(clrBack));
      DWORD dwShowColor = 0xFF000000;
      for( int y = 0; y < abs(bmi.bmiHeader.biHeight); y++ ) {
         for( int x = 0; x < bmi.bmiHeader.biWidth; x++ ) {
            if( *pDest != dwKey ) *pDest = *pDest | dwShowColor; 
            else *pDest = 0x00000000;
            pDest++;
         }
      }
   }

   // Cleanup
   ::SelectObject(hPaintDC, hOldPaintBitmap);
   ::DeleteObject(hPaintBitmap);
   ::DeleteDC(hPaintDC);

   return hBitmap;
}

