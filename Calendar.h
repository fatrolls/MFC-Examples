#if !defined(AFX_CALENDAR_H__20030207_E174_DA0C_17E1_0080AD509054__INCLUDED_)
#define AFX_CALENDAR_H__20030207_E174_DA0C_17E1_0080AD509054__INCLUDED_

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CCalendarCtrl - A Simple Calendar that shows appointments
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// Copyright (c) 2003 Bjarke Viksoe
//
// NOTE:
//  The code detects if the WTL CString class is defined
//  and uses this for the tooltip text.
//
// This code may be used in compiled form in any way you desire. This
// source file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#ifndef __cplusplus
  #error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLAPP_H__
  #error Calendar.h requires atlapp.h to be included first
#endif

#ifndef __ATLCTRLS_H__
  #error Calendar.h requires atlctrls.h to be included first
#endif

#if (_WIN32_IE < 0x0400)
  #error Calendar.h requires _WIN32_IE >= 0x0400
#endif

#ifndef __ATLGDIX_H__
  #error Calendar.h requires my atlgdix.h file
#endif


// Control styles
#define CLS_NOSEL       0x00000001
#define CLS_NOSELECTOR  0x00000002
#define CLS_NOWEEKNUM   0x00000004
#define CLS_NOTODAY     0x00000008
#define CLS_REDWEEKENDS 0x00000010

// Control notifications (WM_COMMAND style)
#define CLN_SELCHANGE       1
#define CLN_CLICKED         2
#define CLN_DBLCLK          3
#define CLN_RETURN          4

// Appointment definition
typedef struct tagCALENDAR_APPOINTMENT
{
   SYSTEMTIME stDate;          // Date of appointment
   COLORREF clrText;           // Color of text
   TCHAR szText1[64];          // Upper line
   TCHAR szText2[64];          // Lower line (skipped if empty)
   TCHAR szTipText[128];       // Tooltip text
   UINT iText1Styles;          // ES_LEFT, ES_CENTER, ES_RIGHT styles
   UINT iText2Styles;          // ES_LEFT, ES_CENTER, ES_RIGHT style
   LPARAM lParam;              // Optional user-data
} CALENDAR_APPOINTMENT;


template< class T, class TBase = CWindow, class TWinTraits = CControlWinTraits >
class ATL_NO_VTABLE CCalendarImpl : 
   public CWindowImpl< T, TBase, TWinTraits >,
   public COffscreenDrawRect< T >,
   public CMouseHover< T >
{
public:
   DWORD m_dwExtStyle;
   SYSTEMTIME m_stNow;                                      // Currently shown month
   CSimpleValArray<RECT> m_aCells;                          // List of cell rectangles
   CSimpleValArray<CALENDAR_APPOINTMENT> m_aAppointments;   // List of appointments
   TCHAR m_szTitle[100];                                    // Title text
   int m_iCellFocus;                                        // Cell with focus (mousehover)
   //
   CMonthCalendarCtrl m_ctrlMonth;
   CToolTipCtrl m_ctrlTip;
   CFontHandle m_font;
   CFont m_fontBold;
   COLORREF m_clrWindow;
   COLORREF m_clrSelected;
#if defined(__ATLSTR_H__) || defined(_WTL_USE_CSTRING)
   CString m_sTip;
#endif // __ATLSTR_H__

   enum
   {
      WEEKDAYS = 7,                  // Number of weekdays in a week
      WEEKS = 6,                     // Number of weeks to display
      SELECTOR_CY = 30,              // Seems to be a hardcoded size in Windows Month control?
      ARROW_CXY = 12,                // "More"-arrow size
      PADDING_MONTH_CY = 16,
      PADDING_SELECTOR_CY = 12,
      PADDING_HEADER_CY = 8,
      LINE_GAP = 4,
   };

   // Constructor / destructor

   ~CCalendarImpl()
   {
      if( m_ctrlTip.IsWindow() ) 
         /* scary */ m_ctrlTip.DestroyWindow();
   }

   // Operations

   BOOL SubclassWindow(HWND hWnd)
   {
      ATLASSERT(m_hWnd==NULL);
      ATLASSERT(::IsWindow(hWnd));
      BOOL bRet = CWindowImpl< T, TBase, TWinTraits >::SubclassWindow(hWnd);
      if( bRet ) _Init();
      return bRet;
   }

   DWORD SetCalendarStyle(DWORD dwStyle)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      DWORD dwOldStyle = m_dwExtStyle;
      m_dwExtStyle = dwStyle;
      m_ctrlMonth.ShowWindow(m_dwExtStyle & CLS_NOSELECTOR ? SW_HIDE : SW_SHOW);
      Invalidate();
      return dwOldStyle;
   }

   BOOL DeleteAllItems()
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_aAppointments.RemoveAll();
      m_iCellFocus = -1;
      Invalidate();
      return TRUE;
   }
   int AddItem(const CALENDAR_APPOINTMENT* pItem)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(pItem);
      ATLASSERT(pItem->stDate.wYear>1900);
      ATLASSERT(!::IsBadStringPtr(pItem->szText1,-1));
      ATLASSERT(!::IsBadStringPtr(pItem->szText2,-1));
      ATLASSERT(!::IsBadStringPtr(pItem->szTipText,-1));
      if( pItem == NULL ) return -1;
      // Insert in sorted order
      CALENDAR_APPOINTMENT App = *pItem; // const thing!
      int nCount = m_aAppointments.GetSize();
      m_aAppointments.Add(App);
      int iIndex = nCount;
      for( int i = 0; i < nCount; i++ ) {
         SYSTEMTIME stDate = m_aAppointments[i].stDate;
         if( ::memcmp(&stDate, &pItem->stDate, sizeof(SYSTEMTIME)) > 0 ) {
            CALENDAR_APPOINTMENT* pData = m_aAppointments.GetData();
            ::MoveMemory(pData + i + 1, pData + i, sizeof(CALENDAR_APPOINTMENT) * (nCount - i));
            m_aAppointments.SetAtIndex(i, App);
            iIndex = i;
            break;
         }
      }
      Invalidate();
      return iIndex;
   }
   int GetItemCount() const
   {
      return m_aAppointments.GetSize();
   }
   BOOL GetItem(int iIndex, CALENDAR_APPOINTMENT* pItem) const
   {
      ATLASSERT(pItem);
      if( iIndex < 0 || iIndex >= m_aAppointments.GetSize() ) return FALSE;
      *pItem = m_aAppointments[i];
      return TRUE;
   }

   SYSTEMTIME GetCurSel() const
   {
      return m_stNow;
   }
   BOOL SetCurSel(const LPSYSTEMTIME pstDate)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(!::IsBadReadPtr(pstDate, sizeof(SYSTEMTIME)));
      ATLASSERT(pstDate->wYear>=1900);
      ATLASSERT(pstDate->wYear<=9000);
      // NOTE: This is for safety reasons, since some of our "Find Next Date" algorithms
      //       may go into an endless loop if SYSTEMTIME boundries are reached.
      if( pstDate->wYear < 1900 || pstDate->wYear > 9000 ) {
         ::MessageBeep((UINT)-1);
         return FALSE;
      }
      // Check if date is already set!
      // To repaint the contro, simply use Invalidate().
      if( pstDate->wYear == m_stNow.wYear &&
          pstDate->wMonth == m_stNow.wMonth &&
          pstDate->wDay == m_stNow.wDay )
      {
         return TRUE;
      }
      // Set date in selector and trigger control update!
      m_stNow = *pstDate;
      m_ctrlMonth.SetCurSel(&m_stNow);
      BOOL bDummy;
      OnDateChanging(0, NULL, bDummy);
      return TRUE;
   }
   BOOL HitTest(POINT pt, LPSYSTEMTIME pstDate) const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(m_aCells.GetSize()>0); // Too soon! Wait for control to paint first!
      ATLASSERT(!::IsBadWritePtr(pstDate, sizeof(SYSTEMTIME)));
      for( int i = 0; i < m_aCells.GetSize(); i++ ) {
         RECT rc = m_aCells[i];
         if( ::PtInRect(&rc, pt) ) {
            // Convert index to cell date...
            *pstDate = _FindCalendarStart();
            DATE dDate = 0.0;
            ::SystemTimeToVariantTime(pstDate, &dDate);
            dDate += i;
            ::VariantTimeToSystemTime(dDate, pstDate);
            return TRUE;
         }
      }
      return FALSE;
   }
   void GetCalendarRange(LPSYSTEMTIME pstStart, LPSYSTEMTIME pstEnd) const
   {
      ATLASSERT(::IsWindow(m_hWnd));
      if( pstStart ) *pstStart = _FindCalendarStart();
      if( pstEnd ) *pstEnd = _FindCalendarEnd();
   }

   void SetFont(HFONT hFont)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(hFont!=NULL);
      m_font = hFont;

      // Create bold version of font
      if( !m_fontBold.IsNull() ) m_fontBold.DeleteObject();
      CLogFont lf = m_font;
      lf.MakeBolder();
      m_fontBold.CreateFontIndirect(&lf);
      ATLASSERT(!m_fontBold.IsNull());

      Invalidate();
   }
   void SetTitle(LPCTSTR pstrTitle)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      ATLASSERT(!::IsBadStringPtr(pstrTitle,-1));
      ATLASSERT(::lstrlen(pstrTitle)<sizeof(m_szTitle)/sizeof(TCHAR));
      ::lstrcpy(m_szTitle, pstrTitle);
      Invalidate();
   }
   void SetBkColor(COLORREF clr)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_clrWindow = clr;
      Invalidate();
   }
   void SetSelColor(COLORREF clr)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      m_clrSelected = clr;
      Invalidate();
   }
   BOOL InvalidateCell(int iIndex)
   {
      ATLASSERT(::IsWindow(m_hWnd));
      if( !_IsValidCell(iIndex) ) return FALSE;
      RECT rc = m_aCells[iIndex];
      InvalidateRect(&rc, FALSE);
      return TRUE;
   }

   // Message map and handlers

   BEGIN_MSG_MAP(CCalendarImpl)
      CHAIN_MSG_MAP( COffscreenDrawRect<T > )
      CHAIN_MSG_MAP( CMouseHover<T> )
      MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      MESSAGE_HANDLER(WM_SIZE, OnSize)
      MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
      MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
      MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
      MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClick)
      MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
      MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
      NOTIFY_CODE_HANDLER(MCN_SELCHANGE, OnDateChanging)
      NOTIFY_CODE_HANDLER(TTN_GETDISPINFO, OnGetDispInfo);
   END_MSG_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      _Init();
      return 0;
   }
   LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
   {
      bHandled = FALSE;
      if( wParam == SIZE_MINIMIZED ) return 0;
      // Force the control to recalculate all its cell-positions!
      Invalidate();
      return 0;
   }
   LRESULT OnGetDlgCode(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      return DLGC_WANTARROWS | DLGC_WANTALLKEYS;
   }
   LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
   {
      bHandled = FALSE;
      if( m_dwExtStyle & CLS_NOSEL ) return 0;
      SYSTEMTIME stDate = GetCurSel();
      DATE dDate = 0.0;
      ::SystemTimeToVariantTime(&stDate, &dDate);
      bool bChanged = false;
      switch( wParam ) {
      case VK_RETURN:
         ::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CLN_RETURN), (LPARAM) m_hWnd);
         break;
      case VK_LEFT:
         dDate -= 1.0; 
         bChanged = true;
         break;
      case VK_RIGHT:
         dDate += 1.0; 
         bChanged = true;
         break;
      case VK_UP:
         dDate -= WEEKDAYS; 
         bChanged = true;
         break;
      case VK_DOWN:
         dDate += WEEKDAYS; 
         bChanged = true;
         break;
      case VK_PRIOR:
         stDate.wDay = 0; // Will find previous month according to the docs!
         ::SystemTimeToVariantTime(&stDate, &dDate);
         bChanged = true;
         break;
      case VK_NEXT:
         {
            stDate = _FindEndOfMonth(stDate);
            ::SystemTimeToVariantTime(&stDate, &dDate);
            dDate += 1.0;
            ::VariantTimeToSystemTime(dDate, &stDate);
            bChanged = true;
         }
         break;
      case VK_TAB:
         ::PostMessage(GetParent(), WM_NEXTDLGCTL, ::GetKeyState(VK_SHIFT) < 0 ? 1 : 0, (LPARAM) FALSE);
         return 0;
      }
      if( bChanged ) {
         ::VariantTimeToSystemTime(dDate, &stDate);
         SetCurSel(&stDate);
      }
      return 0;
   }
   LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      if( !IsWindowEnabled() ) return 0;
      SetFocus();
      ::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CLN_CLICKED), (LPARAM) m_hWnd);
      if( (m_dwExtStyle & CLS_NOSEL) == 0 ) {
         POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
         SYSTEMTIME stDate;
         if( HitTest(pt, &stDate) ) SetCurSel(&stDate);
      }
      return 0;
   }
   LRESULT OnLButtonDblClick(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      ::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CLN_DBLCLK), (LPARAM) m_hWnd);
      return 0;
   }
   LRESULT OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
   {
      // Feed tooltip with messages
      MSG msg = { m_hWnd, uMsg, wParam, lParam };
      if( m_ctrlTip.IsWindow() ) m_ctrlTip.RelayEvent(&msg);
      bHandled = FALSE;
      return 0;
   }
   LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
   {
      // Figure out if the mouse has moved onto another
      // cell, so we should redraw the focus-indicator.
      POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
      int iNewCell = -1;
      for( int i = 0; i < m_aCells.GetSize(); i++ ) {
         RECT rc = m_aCells[i];
         if( ::PtInRect(&rc, pt) ) {
            iNewCell = i;
            break;
         }
      }
      // Repaint cells (with/without focus) if changed
      if( iNewCell != m_iCellFocus ) {
         InvalidateCell(m_iCellFocus);
         InvalidateCell(iNewCell);
         m_iCellFocus = iNewCell;
      }
      return 0;
   }
   LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      // Repaint old item (now without focus)
      InvalidateCell(m_iCellFocus);
      m_iCellFocus = -1;
      return 0;
   }

   LRESULT OnDateChanging(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
   {
      // No time in selected date, please
      m_stNow.wHour = 0;
      m_stNow.wMinute = 0;
      m_stNow.wSecond = 0;
      m_stNow.wMilliseconds = 0;
      // Activate
      m_ctrlTip.Activate(FALSE);
      m_iCellFocus = -1;
      m_ctrlMonth.GetCurSel(&m_stNow);
      SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CLN_SELCHANGE), (LPARAM) m_hWnd);
      Invalidate();
      return 0;
   }
   LRESULT OnGetDispInfo(int /*idCtrl*/, LPNMHDR pnmh, BOOL& bHandled)
   {
      LPNMTTDISPINFO lpnmtdi = (LPNMTTDISPINFO) pnmh;

      ATLASSERT(_IsValidCell(m_iCellFocus));
      if( !_IsValidCell(m_iCellFocus) ) {
         bHandled = FALSE;
         return 0;
      }

      // Figure out from which date this tooltip comes from.
      SYSTEMTIME stDate = _FindCalendarStart();
      DATE dDate = 0.0;
      ::SystemTimeToVariantTime(&stDate, &dDate);
      dDate += m_iCellFocus;
      ::VariantTimeToSystemTime(dDate, &stDate);
      
      // Start off with the date text.
#if defined(__ATLSTR_H__) || defined(_WTL_USE_CSTRING)
      ::GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &stDate, NULL, m_sTip.GetBuffer(100), 100);
      m_sTip.ReleaseBuffer();
      m_sTip += _T("\r\n");
#else
      static TCHAR szText[2048] = { 0 };
      ::GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &stDate, NULL, szText, 100);
      ::lstrcat(szText, _T("\r\n"));
#endif // __ATLSTR_H__

      // Then list every appointment...
      bool bFound = false;
      for( int i = 0; i < m_aAppointments.GetSize(); i++ ) {
         const CALENDAR_APPOINTMENT& app = m_aAppointments[i];
         if( app.stDate.wDay == stDate.wDay && 
             app.stDate.wMonth == stDate.wMonth &&
             app.stDate.wYear == stDate.wYear ) 
         {
#if defined(__ATLSTR_H__) || defined(_WTL_USE_CSTRING)
            m_sTip += _T("\r\n");
            m_sTip += app.szTipText;
#else
            ::lstrcat(szText, _T("\r\n"));
            ::lstrcat(szText, app.szTipText);
            ATLASSERT(::lstrlen(szText)<sizeof(szText)/sizeof(TCHAR));
#endif // __ATLSTR_H__
            bFound = true;
         }
      }

#if defined(__ATLSTR_H__) || defined(_WTL_USE_CSTRING)
      if( !bFound ) m_sTip = _T(""); // No appointments, then no tip!
      lpnmtdi->lpszText = (LPTSTR) (LPCTSTR) m_sTip;
#else
      if( !bFound ) szText[0] = _T('\0'); // No appointments, then no tip!
      lpnmtdi->lpszText = szText;
#endif // __ATLSTR_H__

      return 0;
   }

   // Control painting

   void DoPaint(CDCHandle dc, const RECT& rcPaint)
   {
      RECT rc;
      GetClientRect(&rc);
      HFONT hOldFont = dc.SelectFont(m_font);
      dc.SetBkMode(TRANSPARENT);
      DoPaintSelector(dc, rcPaint, rc);
      DoPaintHeaders(dc, rcPaint, rc);
      DoPaintCells(dc, rc);
      UpdateToolTipCells();
      dc.SelectFont(hOldFont);
   }
   void DoPaintSelector(CDCHandle dc, const RECT& rcPaint, RECT& rc)
   {
      if( m_dwExtStyle & CLS_NOSELECTOR ) return;
      int iHeight = SELECTOR_CY + PADDING_SELECTOR_CY;
      if( rcPaint.top < rc.top + iHeight ) {
         // Draw edge
         RECT rcBar = { rc.left, rc.top, rc.right, rc.top + iHeight };
         dc.FillRect(&rcBar, ::GetSysColorBrush(COLOR_BTNFACE));
         dc.DrawEdge(&rcBar, BDR_RAISEDINNER, BF_RECT);      
         // Paint title if available
         if( m_szTitle[0] != _T('\0') ) {
            HFONT hOldFont = dc.SelectFont(m_fontBold);
            RECT rcMonth;
            m_ctrlMonth.GetWindowRect(&rcMonth);
            const UINT iStyle = DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS;
            RECT rcTitle = { rcBar.left + (rcMonth.right - rcMonth.left) + 30, rcBar.top + (PADDING_SELECTOR_CY / 2), rcBar.right - 10, rcBar.bottom - (PADDING_SELECTOR_CY / 2) };
            RECT rcLimits = rcTitle;
            dc.DrawText(m_szTitle, -1, &rcLimits, iStyle | DT_CALCRECT);
            rcTitle.left = rcTitle.right - (rcLimits.right - rcLimits.left) - 20;
            dc.FillRect(&rcTitle, ::GetSysColorBrush(COLOR_BTNSHADOW));
            dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
            dc.DrawText(m_szTitle, -1, &rcTitle, iStyle);
            dc.SelectFont(hOldFont);
         }
      }
      rc.top += iHeight;
   }
   void DoPaintHeaders(CDCHandle dc, const RECT& rcPaint, RECT& rc)
   {
      TEXTMETRIC tm;
      dc.GetTextMetrics(&tm);
      int iPos = rc.left;
      int iHeight = tm.tmHeight + PADDING_HEADER_CY;
      if( rcPaint.top < rc.top + iHeight ) {
         if( (m_dwExtStyle & CLS_NOWEEKNUM) == 0 ) {
            SIZE szWeekNum;
            dc.GetTextExtent(_T("99"), 2, &szWeekNum);
            int iWidth = szWeekNum.cx + 8;
            RECT rcHeader = { iPos, rc.top, iPos + iWidth, rc.top + iHeight }; 
            dc.FillRect(&rcHeader, ::GetSysColorBrush(COLOR_BTNFACE));
            dc.Draw3dRect(&rcHeader, ::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNSHADOW));                 
            iPos += iWidth;
         }
         HFONT hOldFont = dc.SelectFont(m_fontBold);
         int iWidth = (rc.right - iPos) / WEEKDAYS;
         for( int i = 0; i < WEEKDAYS; i++ ) {
            RECT rcHeader = { iPos, rc.top, iPos + iWidth, rc.top + iHeight };
            if( i == WEEKDAYS - 1 ) rcHeader.right = rc.right;
            TCHAR szText[64] = { 0 };
            LCTYPE lctype = LOCALE_SDAYNAME1;
            if( iWidth < 70 ) lctype += LOCALE_SABBREVDAYNAME1 - LOCALE_SDAYNAME1;
            ::GetLocaleInfo(LOCALE_USER_DEFAULT, lctype + i, szText, (sizeof(szText)/sizeof(TCHAR) - 1));
            dc.FillRect(&rcHeader, ::GetSysColorBrush(COLOR_BTNFACE));
            dc.Draw3dRect(&rcHeader, ::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNSHADOW));                 
            dc.SetTextColor(::GetSysColor(COLOR_BTNTEXT));         
            dc.DrawText(szText, -1, &rcHeader, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_END_ELLIPSIS);

            iPos += iWidth;
         }
         dc.SelectFont(hOldFont);
      }
      rc.top += iHeight;
   }
   void DoPaintCells(CDCHandle dc, RECT& rc)
   {      
      POINT pt = { rc.left, rc.top };      
      int iWidth = rc.right - rc.left;
      int iHeight = (rc.bottom - rc.top) / WEEKS;

      SYSTEMTIME stToday;
      ::GetLocalTime(&stToday);

      // When the view gets smaller we scale the view down
      // by using a smaller font...
      CLogFont lf = m_font;
      lf.MakeLarger(-1);
      if( iWidth < 85 ) lf.MakeLarger(-1);
      if( iWidth < 70 ) lf.MakeLarger(-1);
      CFont fontSmall;
      fontSmall.CreateFontIndirect(&lf);
      ATLASSERT(!fontSmall.IsNull());

      SYSTEMTIME stDate = _FindCalendarStart();
      DATE dDate = 0.0;
      ::SystemTimeToVariantTime(&stDate, &dDate);

      m_aCells.RemoveAll();

      COLORREF clrWindow = m_clrWindow;
      COLORREF clrBackInactive = BlendRGB(clrWindow, RGB(0,0,0), 8);
      COLORREF clrBackWeekend = BlendRGB(clrWindow, RGB(0,0,0), 4);

      // Prepare custom drawing session
      DRAWITEMSTRUCT dis = { 0 };
      dis.CtlID = GetDlgCtrlID();
      dis.CtlType = ODT_STATIC;
      dis.itemAction = ODA_DRAWENTIRE;
      dis.hwndItem = m_hWnd;
      dis.hDC = dc;

      HFONT hOldFont = dc.SelectFont(m_font);

      SIZE sizeWeekNum;
      dc.GetTextExtent(_T("99"), 2, &sizeWeekNum);

      // Travers all week in the display...
      int iIndex = 0;
      for( int i = 0; i < WEEKS; i++ ) {

         // Paint week number
         if( (m_dwExtStyle & CLS_NOWEEKNUM) == 0 ) {
            int iWidth = sizeWeekNum.cx + 8;
            RECT rcWeekNum = { pt.x, pt.y, pt.x + iWidth, pt.y + iHeight }; 
            if( i == WEEKS - 1 ) rcWeekNum.bottom = rc.bottom;
            dc.FillRect(&rcWeekNum, ::GetSysColorBrush(COLOR_BTNFACE));
            dc.Draw3dRect(&rcWeekNum, ::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNSHADOW));
            TCHAR szWeekNum[16];
            _GetWeekNum(stDate, szWeekNum);
            rcWeekNum.left += 2;
            rcWeekNum.top += 4;
            dc.SetTextColor(::GetSysColor(COLOR_BTNTEXT));
            dc.DrawText(szWeekNum, -1, &rcWeekNum, DT_SINGLELINE | DT_NOPREFIX | DT_CENTER);
            pt.x += iWidth;
         }
         int iCellWidth = (rc.right - pt.x) / WEEKDAYS;

         // For each week, traverse weekdays...
         for( int j = 0; j < WEEKDAYS; j++ ) {

            RECT rcBar = { pt.x, pt.y, pt.x + iCellWidth, pt.y + iHeight };
            if( i == WEEKS - 1 ) rcBar.bottom = rc.bottom;
            if( j == WEEKDAYS - 1 ) rcBar.right = rc.right;

            m_aCells.Add(rcBar);

            bool bSelected = ((m_dwExtStyle & CLS_NOSEL)==0 &&
                              m_stNow.wDay == stDate.wDay &&
                              m_stNow.wMonth == stDate.wMonth &&
                              m_stNow.wYear == stDate.wYear);
            bool bToday = ((m_dwExtStyle & CLS_NOTODAY)==0 &&
                           stDate.wDay == stToday.wDay &&
                           stDate.wMonth == stToday.wMonth &&
                           stDate.wYear == stToday.wYear);
            bool bHotlight = iIndex == m_iCellFocus;
            bool bGrayed = m_stNow.wMonth != stDate.wMonth;
            bool bWeekend = stDate.wDayOfWeek == 0 || 
                            stDate.wDayOfWeek == 6;

            // Allow owner window to custom draw cells by reflecting on WM_DRAWITEM.
            dis.itemID = iIndex;
            dis.itemState = 0;
            if( bSelected ) dis.itemState |= ODS_SELECTED;
#if(WINVER < 0x0500)
            const UINT ODS_HOTLIGHT = 0x0040;
#endif
            if( bHotlight ) dis.itemState |= ODS_HOTLIGHT;
            if( bGrayed ) dis.itemState |= ODS_GRAYED;
            dis.itemData = (LPARAM) &stDate;
            dis.rcItem = rcBar;
            if( ::SendMessage(GetParent(), WM_DRAWITEM, (WPARAM) dis.CtlID, (LPARAM) &dis) == 0 ) 
            {
               //
               // Ok, we're going to draw the cell ourselves.
               //

               // Draw cell-frame.
               dc.Draw3dRect(&rcBar, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));

               RECT rcCell = rcBar;
               ::InflateRect(&rcCell, -1, -1);

               // Paint the different backgrounds.
               COLORREF clrBack;
               if( bSelected ) clrBack = m_clrSelected;
               else if( bGrayed ) clrBack = clrBackInactive;
               else if( bWeekend ) clrBack = clrBackWeekend;
               else clrBack = clrWindow;
               dc.FillSolidRect(&rcCell, clrBack);

               // Prepare to paint the day-number text.
               RECT rcDay = rcBar;
               TCHAR szDay[32];
               ::wsprintf(szDay, _T("%ld"), (long) stDate.wDay);
               dc.DrawText(szDay, -1, &rcDay, DT_SINGLELINE | DT_RIGHT | DT_NOPREFIX | DT_CALCRECT);

               // If the cell is "today", then paint it a with a little
               // circle around the day-number text.
               if( bToday ) {
                  COLORREF clrRed = BlendRGB(clrBack, RGB(250,100,100), 40);
                  CPen pen;
                  CBrush brush;
                  pen.CreatePen(PS_SOLID, iCellWidth < 85 ? 2 : 3, clrRed);
                  brush.CreateSolidBrush(clrBack);
                  HPEN hOldPen = dc.SelectPen(pen);
                  HBRUSH hOldBrush = dc.SelectBrush(brush);
                  RECT rcRound = { rcCell.right - (rcDay.bottom - rcDay.top) - 2, rcCell.top + 4, rcCell.right, rcCell.top + (rcDay.right - rcDay.left) + 6 };
                  POINT pt = { 8, 8 };
                  dc.RoundRect(&rcRound, pt);
                  dc.SelectBrush(hOldBrush);
                  dc.SelectPen(hOldPen);
               }
            
               // Then paint the day-number text.
               rcDay = rcBar;
               ::InflateRect(&rcDay, -4, -5);
               COLORREF clrText = ::GetSysColor(COLOR_WINDOWTEXT);
               if( bWeekend && (m_dwExtStyle & CLS_REDWEEKENDS) ) clrText = RGB(140, 0, 0);
               dc.SetTextColor(clrText);
               dc.DrawText(szDay, -1, &rcDay, DT_SINGLELINE | DT_RIGHT | DT_NOPREFIX);
               ::OffsetRect(&rcDay, 1, 1);
               dc.SetTextColor(::GetSysColor(COLOR_BTNSHADOW));
               dc.DrawText(szDay, -1, &rcDay, DT_SINGLELINE | DT_RIGHT | DT_NOPREFIX);

               // A cell with focus (mousehover) gets a strong border.
               if( bHotlight ) {
                  dc.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
                  dc.DrawFocusRect(&rcBar);
               }

               if( bSelected ) {
                  HBRUSH hOldBrush = dc.SelectStockBrush(HOLLOW_BRUSH);
                  HPEN hOldPen = dc.SelectStockPen(BLACK_PEN);
                  RECT rcFrame = { rcBar.left, rcBar.top + 1, rcBar.right, rcBar.bottom };
                  dc.Rectangle(&rcFrame);
                  dc.SelectPen(hOldPen);
                  dc.SelectBrush(hOldBrush);
               }

               // Adjust rectangle so we can paint the appointments.
               RECT rcTexts = rcCell;
               rcTexts.top += 8;
               rcTexts.bottom -= 2;
               rcTexts.left += 4;
               rcTexts.right -= 4 + 8;

               // Finally we can start painting appointments...
               bool bMore = false;
               // NOTE: Hehe, try to comment out the following 2 lines and reinsert
               //       the line after to observe a MSVC++ 6 compiler/optimization bug.
               //       Compile the code in Release mode and resize the control 
               //       heavily; now watch it slow to a crawl...
               int nAppointments = m_aAppointments.GetSize();
               for( int k = 0; k < nAppointments; k++ ) {
               /*for( int k = 0; k < m_aAppointments.GetSize(); k++ ) {*/
                  const CALENDAR_APPOINTMENT& app = m_aAppointments[k];
                  if( app.stDate.wDay == stDate.wDay && 
                      app.stDate.wMonth == stDate.wMonth &&
                      app.stDate.wYear == stDate.wYear ) 
                  {
                     // Prepare for painting...
                     HFONT hOldFont = dc.SelectFont(fontSmall);
                     RECT rcText = rcTexts;
                     dc.SetTextColor(app.clrText);
                     // First text line!
                     UINT iStyle = _GetDTStyle(app.iText1Styles) | DT_SINGLELINE | DT_TOP | DT_NOPREFIX;
                     RECT rcLimits = { 0 };
                     dc.DrawText(app.szText1, -1, &rcLimits, iStyle | DT_CALCRECT);
                     int iHeight = rcLimits.bottom - rcLimits.top;
                     dc.DrawText(app.szText1, -1, &rcText, iStyle);
                     rcText.top += iHeight;
                     rcTexts.top += iHeight;
                     // Allow painting on last few pixels at the right when 
                     // the day-number is now longer in sights...
                     rcText.right = rcTexts.right = rcBar.right - LINE_GAP;
                     // Second text line!
                     if( app.szText2[0] != _T('\0') ) {
                        iStyle = _GetDTStyle(app.iText2Styles) | DT_SINGLELINE | DT_TOP | DT_NOPREFIX;
                        RECT rcLimits = { 0 };
                        dc.DrawText(app.szText2, -1, &rcLimits, iStyle | DT_CALCRECT);
                        int iHeight = rcLimits.bottom - rcLimits.top;
                        dc.DrawText(app.szText2, -1, &rcText, iStyle);
                        rcText.top += iHeight;
                        rcTexts.top += iHeight + 2;
                     }
                     dc.SelectFont(hOldFont);
                     // There were too many items to show in the cell?
                     if( rcText.top + iHeight > rcCell.bottom ) bMore = true;
                     // No need to paint if it's outside the cell
                     if( rcText.top > rcCell.bottom ) break;
                  }
               }

               // Display a little arrow in the lower-right corner when
               // there were too many items to show in the cell...
               if( bMore ) {
                  RECT rcArrow = {rcBar.right - ARROW_CXY - 2, rcBar.bottom - ARROW_CXY - 3, rcBar.right - 2, rcBar.bottom - 3 };
                  dc.DrawFrameControl(&rcArrow, DFC_SCROLL, DFCS_SCROLLDOWN | DFCS_FLAT);
               }

            } // if not WM_DRAWITEM

            // Get the next day.
            dDate += 1.0;
            ::VariantTimeToSystemTime(dDate, &stDate);

            iIndex++;
            pt.x += iCellWidth;
         }
         pt.x = rc.left;
         pt.y += iHeight;
      }
      
      dc.SelectFont(hOldFont);
   }
   void UpdateToolTipCells()
   {
      // Destroy and recreate tooltip for all cells...
      TOOLINFO ti = { 0 };
      ti.cbSize = sizeof(ti);
      while( m_ctrlTip.EnumTools(0, &ti) ) m_ctrlTip.DelTool(&ti);
      ATLASSERT(!m_ctrlTip.EnumTools(0, &ti));
      for( int i = 0; i < m_aCells.GetSize(); i++ ) {
         ti.uFlags = 0;
         ti.hwnd = m_hWnd;
         ti.uId = (UINT) i;
         ti.rect = m_aCells[i];
         ti.hinst = _Module.GetResourceInstance();
         ti.lpszText = LPSTR_TEXTCALLBACK;
         m_ctrlTip.AddTool(&ti);
      }
      m_ctrlTip.Activate(TRUE);
   }

   // Implementation

   void _Init()
   {
      ATLASSERT(::IsWindow(m_hWnd));

      ModifyStyle(WS_CLIPCHILDREN, SS_NOTIFY);
      SetFont(AtlGetDefaultGuiFont());

      m_szTitle[0] = _T('\0');
      m_clrWindow = ::GetSysColor(COLOR_WINDOW);
      m_clrSelected = RGB(230,230,250);
      m_dwExtStyle = 0UL;
      m_fMouseForceUpdate = false;
      m_iCellFocus = -1;

      // Create our tooltip
      DWORD dwStyle = WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP;
      m_ctrlTip.Create(NULL, CWindow::rcDefault, NULL, dwStyle, WS_EX_TOPMOST);
      ATLASSERT(m_ctrlTip.IsWindow());
      m_ctrlTip.SetWindowPos(HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);      
      m_ctrlTip.SetMaxTipWidth(400); // HACK: Tooltip needs this to become multiline!
      // Set margins (look better)
      RECT rcMargin = { 3, 3, 3, 3 };
      m_ctrlTip.SetMargin(&rcMargin);
      // Check popup-delay (we like it small)
      int iInitial = m_ctrlTip.GetDelayTime(TTDT_INITIAL);
      m_ctrlTip.SetDelayTime(TTDT_INITIAL, min(iInitial, 500));

      // Create a Windows MonthCalender control and use it as the
      // selection-control.
      m_ctrlMonth.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE |  MCS_NOTODAY);
      ATLASSERT(::IsWindow(m_ctrlMonth));
      RECT rcMin;
      m_ctrlMonth.GetMinReqRect(&rcMin);
      m_ctrlMonth.MoveWindow(8, PADDING_SELECTOR_CY / 2, 3 + rcMin.right, SELECTOR_CY);
      m_ctrlMonth.SetColor(MCSC_BACKGROUND, ::GetSysColor(COLOR_BTNFACE));
      // Limit selection range (see comment in SetCurSel() member)
      SYSTEMTIME stMinMax[] = { { 1900, 1, 1, 1 }, { 9000, 1, 1, 1 } };
      m_ctrlMonth.SetRange(GDTR_MIN | GDTR_MAX, stMinMax);

      ::GetLocalTime(&m_stNow);
      m_stNow.wHour = 0;
      m_stNow.wMinute = 0;
      m_stNow.wSecond = 0;
      m_stNow.wMilliseconds = 0;

#ifdef _DEBUG
      // Ok, if you live in a wierd country, not having Monday as the first
      // day of the week could spell trouble when we try to determine which
      // days are weekend-days!
      TCHAR szInfo[3];
      ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IFIRSTDAYOFWEEK, szInfo, 2);
      ATLASSERT(_ttol(szInfo)==0);
#endif
   }

   inline bool _IsValidCell(int iIndex) const
   {
      return iIndex >= 0 && iIndex < m_aCells.GetSize();
   }
   SYSTEMTIME _FindCalendarStart() const
   {
      SYSTEMTIME stDate = m_stNow; // const thing!
      stDate.wDay = 1;
      DATE dDate = 0.0;
      ::SystemTimeToVariantTime(&stDate, &dDate);
      dDate -= 1.0;
      ::VariantTimeToSystemTime(dDate, &stDate);
      ATLASSERT(stDate.wMonth!=m_stNow.wMonth);
      while( stDate.wDayOfWeek != 1 ) {
         dDate -= 1.0;
         ::VariantTimeToSystemTime(dDate, &stDate);
      }
      return stDate;
   }
   SYSTEMTIME _FindCalendarEnd() const
   {
      SYSTEMTIME stDate = _FindCalendarStart();
      DATE dDate = 0.0;
      ::SystemTimeToVariantTime(&stDate, &dDate);
      dDate += (WEEKDAYS * WEEKS) - 1.0;
      ::VariantTimeToSystemTime(dDate, &stDate);
      return stDate;
   }
   SYSTEMTIME _FindEndOfMonth(SYSTEMTIME stDate) const
   {
      SYSTEMTIME stLast = stDate;
      while( true ) {
         DATE dDate = 0.0;
         ::SystemTimeToVariantTime(&stDate, &dDate);
         dDate += 1.0;
         ::VariantTimeToSystemTime(dDate, &stDate);
         if( stDate.wMonth != stLast.wMonth ) break;
         stLast = stDate;
      }
      return stLast;
   }
   bool _IsLeapYear(int iYear) const
   {
      return !(iYear % 4) && ((iYear % 100) || !(iYear % 400));
   }
   int _GetDayNum(SYSTEMTIME stDate) const
   {
      static int iNormYearAccum[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
      static int iLeapYearAccum[] = { 0,31,60,91,121,152,182,213,244,274,305,335,366 };
      const int* pAccum = _IsLeapYear(stDate.wYear) ? iLeapYearAccum : iNormYearAccum;
      return pAccum[stDate.wMonth - 1] + stDate.wDay;
   }
   void _GetWeekNum(SYSTEMTIME stDate, LPTSTR pstrDate) const
   {
      // Hmm, this is the ISO8601 standard for weeknumbers! Pheew, to think
      // that this would be the most difficult part of the control to get right!
      // Actually this calculation is stolen from L. Kirby, so don't hassle me
      // about it!!!
      const int firstDOW = 1; // First Day of Week = Monday
      const int tmp1 = firstDOW - stDate.wDayOfWeek;
      const int tmp2 = (_GetDayNum(stDate) - 1) + ((tmp1 > 0) ? 3 : 10) + tmp1;
      const int fourthdaynum = tmp2 % 7;
      long iWeekNum = tmp2 / 7;
      if( iWeekNum == 0 ) {
         const int year = stDate.wYear + (1900 % 400) - 1;
         const int isleap = !(year % 4) && ((year % 100) || !(year % 400));
         iWeekNum = (fourthdaynum + isleap >= 6) ? 53 : 52;
      } 
      else if( iWeekNum == 53 ) {
         const int year = stDate.wYear + 1900;
         const int isleap = !(year % 4) && ((year % 100) || !(year % 400));
         if( fourthdaynum > isleap ) iWeekNum = 1;
      }
      ::wsprintf(pstrDate, _T("%ld"), iWeekNum);
   }
   UINT _GetDTStyle(UINT iEditStyle) const
   {
      UINT iStyle = 0;
      if( iEditStyle & ES_CENTER ) iStyle |= DT_CENTER;
      else if( iEditStyle & ES_RIGHT ) iStyle |= DT_RIGHT;
      else iStyle |= DT_LEFT;
      return iStyle;
   }
};

class CCalendarCtrl : public CCalendarImpl<CCalendarCtrl>
{
public:
   DECLARE_WND_CLASS(_T("WTL_Calendar"))
};


#endif // !defined(AFX_CALENDAR_H__20030207_E174_DA0C_17E1_0080AD509054__INCLUDED_)
