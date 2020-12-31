#if !defined(AFX_BLUEUI_H__20050424_6E62_6B42_BC3F_0080AD509054__INCLUDED_)
#define AFX_BLUEUI_H__20050424_6E62_6B42_BC3F_0080AD509054__INCLUDED_

#pragma once


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRenderClip
{
public:
   ~CRenderClip();
   RECT rcItem;
   HDC hDC;
   HRGN hRgn;
   HRGN hOldRgn;
};

class UILIB_API CBlueRenderEngineUI
{
public:
   static void DoFillRect(HDC hDC, CPaintManagerUI* pManager, RECT rc, UITYPE_COLOR Color);
   static void DoFillRect(HDC hDC, CPaintManagerUI* pManager, RECT rc, COLORREF clrFill);
   static void DoPaintLine(HDC hDC, CPaintManagerUI* pManager, RECT rc, UITYPE_COLOR Color);
   static void DoPaintRectangle(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, UITYPE_COLOR Border, UITYPE_COLOR Fill);
   static void DoPaintPanel(HDC hDC, CPaintManagerUI* pManager, RECT rc);
   static void DoPaintFrame(HDC hDC, CPaintManagerUI* pManager, RECT rc, UITYPE_COLOR Light, UITYPE_COLOR Dark, UITYPE_COLOR Background = UICOLOR__INVALID, UINT uStyle = 0);
   static void DoPaintBitmap(HDC hDC, CPaintManagerUI* pManager, HBITMAP hBmp, RECT rcBitmap);
   static void DoPaintArcCaption(HDC hDC, CPaintManagerUI* pManager, RECT rc, LPCTSTR pstrText, UINT uStyle);
   static void DoPaintButton(HDC hDC, CPaintManagerUI* pManager, RECT rc, LPCTSTR pstrText, RECT rcPadding, UINT uState, UINT uDrawStyle);
   static void DoPaintEditBox(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, LPCTSTR pstrText, UINT uState, UINT uDrawStyle, bool bPaintFrameOnly);
   static void DoPaintOptionBox(HDC hDC, CPaintManagerUI* pManager, RECT rcItem, LPCTSTR pstrText, UINT uState, UINT uStyle);
   static void DoPaintTabFolder(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, UINT uState);
   static void DoPaintToolbarButton(HDC hDC, CPaintManagerUI* pManager, RECT rc, LPCTSTR pstrText, SIZE szPadding, UINT uState);
   static void DoPaintQuickText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCSTR pstrText, UITYPE_COLOR iTextColor, UITYPE_FONT iFont, UINT uStyle);
   static void DoPaintPrettyText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, UITYPE_COLOR iTextColor, UITYPE_COLOR iBackColor, RECT* pLinks, int& nLinkRects, UINT uStyle);
   static void DoPaintGradient(HDC hDC, CPaintManagerUI* pManager, RECT rc, COLORREF clrFirst, COLORREF clrSecond, bool bVertical, int nSteps);
   static void DoPaintAlphaBitmap(HDC hDC, CPaintManagerUI* pManager, HBITMAP hBitmap, RECT rc, BYTE iAlpha);
   static void DoAnimateWindow(HWND hWnd, UINT uStyle, DWORD dwTime = 200);
   static void GenerateClip(HDC hDC, RECT rcItem, CRenderClip& clip);
   static HBITMAP GenerateAlphaBitmap(CPaintManagerUI* pManager, CControlUI* pControl, RECT rc, UITYPE_COLOR Background);
};


#endif // !defined(AFX_BLUEUI_H__20050424_6E62_6B42_BC3F_0080AD509054__INCLUDED_)
