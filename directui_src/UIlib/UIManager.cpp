
#include "StdAfx.h"
#include "UIManager.h"
#include "UIAnim.h"

#include <zmouse.h>


/////////////////////////////////////////////////////////////////////////////////////
//
//

static UINT GetNameHash(LPCTSTR pstrName)
{
   UINT i = 0;
   SIZE_T len = _tcslen(pstrName);
   while( len-- > 0 ) i = (i << 5) + i + pstrName[len];
   return i;
}

static UINT MapKeyState()
{
   UINT uState = 0;
   if( ::GetKeyState(VK_CONTROL) < 0 ) uState |= MK_CONTROL;
   if( ::GetKeyState(VK_RBUTTON) < 0 ) uState |= MK_LBUTTON;
   if( ::GetKeyState(VK_LBUTTON) < 0 ) uState |= MK_RBUTTON;
   if( ::GetKeyState(VK_SHIFT) < 0 ) uState |= MK_SHIFT;
   if( ::GetKeyState(VK_MENU) < 0 ) uState |= MK_ALT;
   return uState;
}


/////////////////////////////////////////////////////////////////////////////////////
//

#define IDB_ICONS16 200
#define IDB_ICONS24 201
#define IDB_ICONS32 202
#define IDB_ICONS50 203


typedef struct tagFINDTABINFO
{
   CControlUI* pFocus;
   CControlUI* pLast;
   bool bForward;
   bool bNextIsIt;
} FINDTABINFO;

typedef struct tagFINDSHORTCUT
{
   TCHAR ch;
   bool bPickNext;
} FINDSHORTCUT;

typedef struct tagTIMERINFO
{
   CControlUI* pSender;
   UINT nLocalID;
   HWND hWnd;
   UINT uWinTimer;
} TIMERINFO;


/////////////////////////////////////////////////////////////////////////////////////
//

CAnimationSpooler m_anim;
HPEN m_hPens[UICOLOR__LAST] = { 0 };
HFONT m_hFonts[UIFONT__LAST] = { 0 };
HBRUSH m_hBrushes[UICOLOR__LAST] = { 0 };
LOGFONT m_aLogFonts[UIFONT__LAST] = { 0 };
COLORREF m_clrColors[UICOLOR__LAST][2] = { 0 };
TEXTMETRIC m_aTextMetrics[UIFONT__LAST] = { 0 };
HIMAGELIST m_himgIcons16 = NULL;
HIMAGELIST m_himgIcons24 = NULL;
HIMAGELIST m_himgIcons32 = NULL;
HIMAGELIST m_himgIcons50 = NULL;


/////////////////////////////////////////////////////////////////////////////////////


HINSTANCE CPaintManagerUI::m_hInstance = NULL;
HINSTANCE CPaintManagerUI::m_hLangInst = NULL;
CStdPtrArray CPaintManagerUI::m_aPreMessages;


CPaintManagerUI::CPaintManagerUI() :
   m_hWndPaint(NULL),
   m_hDcPaint(NULL),
   m_hDcOffscreen(NULL),
   m_hbmpOffscreen(NULL),
   m_hwndTooltip(NULL),
   m_uTimerID(0x1000),
   m_pRoot(NULL),
   m_pFocus(NULL),
   m_pEventHover(NULL),
   m_pEventClick(NULL),
   m_pEventKey(NULL),
   m_bFirstLayout(true),
   m_bFocusNeeded(false),
   m_bResizeNeeded(false),
   m_bMouseTracking(false),
   m_bOffscreenPaint(true),
   m_aPostPaint(sizeof(TPostPaintUI))
{
   if( m_hFonts[1] == NULL ) 
   {
      // Fill in default font information
      LOGFONT lf = { 0 };
      ::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
      _tcscpy(lf.lfFaceName, _T("Tahoma"));
      // TODO: Handle "large fonts" or other font sizes when
      //       screen resolution changes!!!
      lf.lfHeight = -12;
      m_aLogFonts[UIFONT_NORMAL] = lf;
      m_aLogFonts[UIFONT_CAPTION] = lf;
      LOGFONT lfBold = lf;
      lfBold.lfWeight += FW_BOLD;
      m_aLogFonts[UIFONT_BOLD] = lfBold;
      lfBold.lfHeight -= 2;
      m_aLogFonts[UIFONT_TITLE] = lfBold;
      lfBold.lfHeight -= 4;
      m_aLogFonts[UIFONT_HEADLINE] = lfBold;
      LOGFONT lfSubscript = lf;
      lfSubscript.lfHeight -= 4;
      m_aLogFonts[UIFONT_SUBSCRIPT] = lfSubscript;
      LOGFONT lfLink = lf;
      lfLink.lfUnderline = TRUE;
      m_aLogFonts[UIFONT_LINK] = lfLink;

      // Fill the color table
      m_clrColors[UICOLOR_WINDOW_BACKGROUND][0]            = RGB(239,239,235);
      m_clrColors[UICOLOR_DIALOG_BACKGROUND][0]            = RGB(238,238,238);
      m_clrColors[UICOLOR_DIALOG_TEXT_NORMAL][0]           = RGB(0,0,0);
      m_clrColors[UICOLOR_DIALOG_TEXT_DARK][0]             = RGB(96,96,80);
      m_clrColors[UICOLOR_TITLE_BACKGROUND][0]             = RGB(114,136,172);
      m_clrColors[UICOLOR_TITLE_TEXT][0]                   = RGB(255,255,255);
      m_clrColors[UICOLOR_TITLE_BORDER_LIGHT][0]           = RGB(171,192,231);
      m_clrColors[UICOLOR_TITLE_BORDER_DARK][0]            = RGB(0,55,122);
      m_clrColors[UICOLOR_BUTTON_BACKGROUND_NORMAL][0]     = RGB(250,250,252);
       m_clrColors[UICOLOR_BUTTON_BACKGROUND_NORMAL][1]    = RGB(215,215,227);
      m_clrColors[UICOLOR_BUTTON_BACKGROUND_DISABLED][0]   = RGB(248,248,248);
       m_clrColors[UICOLOR_BUTTON_BACKGROUND_DISABLED][1]  = RGB(214,214,214);
      m_clrColors[UICOLOR_BUTTON_BACKGROUND_PUSHED][0]     = RGB(215,215,227);
       m_clrColors[UICOLOR_BUTTON_BACKGROUND_PUSHED][1]    = RGB(250,250,252);
      m_clrColors[UICOLOR_BUTTON_TEXT_NORMAL][0]           = RGB(0,0,0);
      m_clrColors[UICOLOR_BUTTON_TEXT_PUSHED][0]           = RGB(0,0,20);
      m_clrColors[UICOLOR_BUTTON_TEXT_DISABLED][0]         = RGB(204,204,204);
      m_clrColors[UICOLOR_BUTTON_BORDER_LIGHT][0]          = RGB(123,158,189);
      m_clrColors[UICOLOR_BUTTON_BORDER_DARK][0]           = RGB(123,158,189);
      m_clrColors[UICOLOR_BUTTON_BORDER_DISABLED][0]       = RGB(204,204,204);
      m_clrColors[UICOLOR_BUTTON_BORDER_FOCUS][0]          = RGB(140,140,140);
      m_clrColors[UICOLOR_TOOL_BACKGROUND_NORMAL][0]       = RGB(114,136,172);
      m_clrColors[UICOLOR_TOOL_BACKGROUND_DISABLED][0]     = RGB(100,121,156);
      m_clrColors[UICOLOR_TOOL_BACKGROUND_HOVER][0]        = RGB(100,121,156);
      m_clrColors[UICOLOR_TOOL_BACKGROUND_PUSHED][0]       = RGB(80,101,136);
      m_clrColors[UICOLOR_TOOL_BORDER_NORMAL][0]           = RGB(0,55,122);
      m_clrColors[UICOLOR_TOOL_BORDER_DISABLED][0]         = RGB(0,55,122);
      m_clrColors[UICOLOR_TOOL_BORDER_HOVER][0]            = RGB(0,55,122);
      m_clrColors[UICOLOR_TOOL_BORDER_PUSHED][0]           = RGB(0,55,122);
      m_clrColors[UICOLOR_EDIT_BACKGROUND_DISABLED][0]     = RGB(255,251,255);
      m_clrColors[UICOLOR_EDIT_BACKGROUND_READONLY][0]     = RGB(255,251,255);
      m_clrColors[UICOLOR_EDIT_BACKGROUND_NORMAL][0]       = RGB(255,255,255);
      m_clrColors[UICOLOR_EDIT_BACKGROUND_HOVER][0]        = RGB(255,251,255);
      m_clrColors[UICOLOR_EDIT_TEXT_NORMAL][0]             = RGB(0,0,0);
      m_clrColors[UICOLOR_EDIT_TEXT_DISABLED][0]           = RGB(167,166,170);
      m_clrColors[UICOLOR_EDIT_TEXT_READONLY][0]           = RGB(167,166,170);      
      m_clrColors[UICOLOR_NAVIGATOR_BACKGROUND][0]         = RGB(229,217,213);
       m_clrColors[UICOLOR_NAVIGATOR_BACKGROUND][1]        = RGB(201,199,187);
      m_clrColors[UICOLOR_NAVIGATOR_TEXT_NORMAL][0]        = RGB(102,102,102);
      m_clrColors[UICOLOR_NAVIGATOR_TEXT_SELECTED][0]      = RGB(0,0,0);
      m_clrColors[UICOLOR_NAVIGATOR_TEXT_PUSHED][0]        = RGB(0,0,0);       
      m_clrColors[UICOLOR_NAVIGATOR_BORDER_NORMAL][0]      = RGB(131,133,116);
      m_clrColors[UICOLOR_NAVIGATOR_BORDER_SELECTED][0]    = RGB(159,160,144);
      m_clrColors[UICOLOR_NAVIGATOR_BUTTON_HOVER][0]       = RGB(200,200,200);
      m_clrColors[UICOLOR_NAVIGATOR_BUTTON_PUSHED][0]      = RGB(184,184,183);
      m_clrColors[UICOLOR_NAVIGATOR_BUTTON_SELECTED][0]    = RGB(238,238,238);
      m_clrColors[UICOLOR_TAB_BACKGROUND_NORMAL][0]        = RGB(255,251,255);
      m_clrColors[UICOLOR_TAB_FOLDER_NORMAL][0]            = RGB(255,251,255);
       m_clrColors[UICOLOR_TAB_FOLDER_NORMAL][1]           = RGB(233,231,215);
      m_clrColors[UICOLOR_TAB_FOLDER_SELECTED][0]          = RGB(255,251,255);
      m_clrColors[UICOLOR_TAB_BORDER][0]                   = RGB(148,166,181);
      m_clrColors[UICOLOR_TAB_TEXT_NORMAL][0]              = RGB(0,0,0);
      m_clrColors[UICOLOR_TAB_TEXT_SELECTED][0]            = RGB(0,0,0);
      m_clrColors[UICOLOR_TAB_TEXT_DISABLED][0]            = RGB(0,0,0);      
      m_clrColors[UICOLOR_HEADER_BACKGROUND][0]            = RGB(233,231,215);
       m_clrColors[UICOLOR_HEADER_BACKGROUND][1]           = RGB(150,150,147);
      m_clrColors[UICOLOR_HEADER_BORDER][0]                = RGB(218,219,201);
      m_clrColors[UICOLOR_HEADER_SEPARATOR][0]             = RGB(197,193,177);
      m_clrColors[UICOLOR_HEADER_TEXT][0]                  = RGB(0,0,0);
      m_clrColors[UICOLOR_TASK_BACKGROUND][0]              = RGB(230,243,255);
       m_clrColors[UICOLOR_TASK_BACKGROUND][1]             = RGB(255,255,255);
      m_clrColors[UICOLOR_TASK_BORDER][0]                  = RGB(140,158,198);
      m_clrColors[UICOLOR_TASK_CAPTION][0]                 = RGB(140,158,198);
      m_clrColors[UICOLOR_TASK_TEXT][0]                    = RGB(65,65,110);
      m_clrColors[UICOLOR_LINK_TEXT_NORMAL][0]             = RGB(0,0,255);
      m_clrColors[UICOLOR_LINK_TEXT_HOVER][0]              = RGB(0,0,100);
      m_clrColors[UICOLOR_CONTROL_BACKGROUND_NORMAL][0]    = RGB(255,255,255);
      m_clrColors[UICOLOR_CONTROL_BACKGROUND_SELECTED][0]  = RGB(173,195,231);
      m_clrColors[UICOLOR_CONTROL_BACKGROUND_READONLY][0]  = RGB(255,255,255);
      m_clrColors[UICOLOR_CONTROL_BACKGROUND_DISABLED][0]  = RGB(255,255,255);
      m_clrColors[UICOLOR_CONTROL_BACKGROUND_HOVER][0]     = RGB(233,245,255);
      m_clrColors[UICOLOR_CONTROL_BACKGROUND_SORTED][0]    = RGB(242,242,246);
      m_clrColors[UICOLOR_CONTROL_BACKGROUND_EXPANDED][0]  = RGB(255,255,255);
       m_clrColors[UICOLOR_CONTROL_BACKGROUND_EXPANDED][1] = RGB(236,242,255);
      m_clrColors[UICOLOR_CONTROL_BORDER_NORMAL][0]        = RGB(123,158,189);
      m_clrColors[UICOLOR_CONTROL_BORDER_SELECTED][0]      = RGB(123,158,189);
      m_clrColors[UICOLOR_CONTROL_BORDER_DISABLED][0]      = RGB(204,204,204);
      m_clrColors[UICOLOR_CONTROL_TEXT_NORMAL][0]          = RGB(0,0,0);
      m_clrColors[UICOLOR_CONTROL_TEXT_SELECTED][0]        = RGB(0,0,0);
      m_clrColors[UICOLOR_CONTROL_TEXT_DISABLED][0]        = RGB(204,204,204);
      m_clrColors[UICOLOR_STANDARD_BLACK][0]               = RGB(0,0,0);
      m_clrColors[UICOLOR_STANDARD_YELLOW][0]              = RGB(255,255,204);
      m_clrColors[UICOLOR_STANDARD_RED][0]                 = RGB(255,204,204);
      m_clrColors[UICOLOR_STANDARD_GREY][0]                = RGB(145,146,119);
      m_clrColors[UICOLOR_STANDARD_LIGHTGREY][0]           = RGB(195,196,179);
      m_clrColors[UICOLOR_STANDARD_WHITE][0]               = RGB(255,255,255);

      // Boot Windows Common Controls (for the ToolTip control)
      ::InitCommonControls();

      // We need the image library for effects. It is however optional in Windows so
      // we'll also need to provide a gracefull fallback.
      ::LoadLibrary("msimg32.dll");
   }
   m_szMinWindow.cx = 140;
   m_szMinWindow.cy = 200;
   m_ptLastMousePos.x = m_ptLastMousePos.y = -1;
   m_uMsgMouseWheel = ::RegisterWindowMessage(MSH_MOUSEWHEEL);
   // System Config
   m_SystemConfig.bShowKeyboardCues = false;
   m_SystemConfig.bScrollLists = false;
   // System Metrics
   m_SystemMetrics.cxvscroll = (INT) ::GetSystemMetrics(SM_CXVSCROLL);
}

CPaintManagerUI::~CPaintManagerUI()
{
   // Delete the control-tree structures
   int i;
   for( i = 0; i < m_aDelayedCleanup.GetSize(); i++ ) delete static_cast<CControlUI*>(m_aDelayedCleanup[i]);
   delete m_pRoot;
   // Release other collections
   for( i = 0; i < m_aTimers.GetSize(); i++ ) delete static_cast<TIMERINFO*>(m_aTimers[i]);
   // Reset other parts...
   if( m_hwndTooltip != NULL ) ::DestroyWindow(m_hwndTooltip);
   if( m_hDcOffscreen != NULL ) ::DeleteDC(m_hDcOffscreen);
   if( m_hbmpOffscreen != NULL ) ::DeleteObject(m_hbmpOffscreen);
   if( m_hDcPaint != NULL ) ::ReleaseDC(m_hWndPaint, m_hDcPaint);
   m_aPreMessages.Remove(m_aPreMessages.Find(this));
}

void CPaintManagerUI::Init(HWND hWnd)
{
   ASSERT(::IsWindow(hWnd));
   // Remember the window context we came from
   m_hWndPaint = hWnd;
   m_hDcPaint = ::GetDC(hWnd);
   // We'll want to filter messages globally too
   m_aPreMessages.Add(this);
}

HINSTANCE CPaintManagerUI::GetResourceInstance()
{
   return m_hInstance;
}

HINSTANCE CPaintManagerUI::GetLanguageInstance()
{
   return m_hLangInst;
}

void CPaintManagerUI::SetResourceInstance(HINSTANCE hInst)
{
   m_hInstance = hInst;
   if( m_hLangInst == NULL ) m_hLangInst = hInst;
}

void CPaintManagerUI::SetLanguageInstance(HINSTANCE hInst)
{
   m_hLangInst = hInst;
}

HWND CPaintManagerUI::GetPaintWindow() const
{
   return m_hWndPaint;
}

HDC CPaintManagerUI::GetPaintDC() const
{
   return m_hDcPaint;
}

POINT CPaintManagerUI::GetMousePos() const
{
   return m_ptLastMousePos;
}

SIZE CPaintManagerUI::GetClientSize() const
{
   RECT rcClient = { 0 };
   ::GetClientRect(m_hWndPaint, &rcClient);
   return CSize(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
}

void CPaintManagerUI::SetMinMaxInfo(int cx, int cy)
{
   ASSERT(cx>=0 && cy>=0);
   m_szMinWindow.cx = cx;
   m_szMinWindow.cy = cy;
}

bool CPaintManagerUI::PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& /*lRes*/)
{
   switch( uMsg ) {
   case WM_KEYDOWN:
      {
         // Tabbing between controls
         if( wParam == VK_TAB ) {
            SetNextTabControl(::GetKeyState(VK_SHIFT) >= 0);
            m_SystemConfig.bShowKeyboardCues = true;
            ::InvalidateRect(m_hWndPaint, NULL, FALSE);
            return true;
         }
         // Handle default dialog controls OK and CANCEL.
         // If there are controls named "ok" or "cancel" they
         // will be activated on keypress.
         if( wParam == VK_RETURN ) {
            CControlUI* pControl = FindControl(_T("ok"));
            if( pControl != NULL && m_pFocus != pControl ) {
               if( m_pFocus == NULL || (m_pFocus->GetControlFlags() & UIFLAG_WANTRETURN) == 0 ) {
                  pControl->Activate();
                  return true;
               }
            }
         }
         if( wParam == VK_ESCAPE ) {
            CControlUI* pControl = FindControl(_T("cancel"));
            if( pControl != NULL ) {
               pControl->Activate();
               return true;
            }
         }
      }
      break;
   case WM_SYSCHAR:
      {
         // Handle ALT-shortcut key-combinations
         FINDSHORTCUT fs = { 0 };
         fs.ch = toupper(wParam);
         CControlUI* pControl = m_pRoot->FindControl(__FindControlFromShortcut, &fs, UIFIND_VISIBLE | UIFIND_ENABLED | UIFIND_ME_FIRST);
         if( pControl != NULL ) {
            pControl->SetFocus();
            pControl->Activate();
            return true;
         }
      }
      break;
   case WM_SYSKEYDOWN:
      {
         // Press ALT once and the shortcuts will be shown in view
         if( wParam == VK_MENU && !m_SystemConfig.bShowKeyboardCues ) {
            m_SystemConfig.bShowKeyboardCues = true;
            ::InvalidateRect(m_hWndPaint, NULL, FALSE);
         }
         if( m_pFocus != NULL ) {
            TEventUI event = { 0 };
            event.Type = UIEVENT_SYSKEY;
            event.chKey = wParam;
            event.ptMouse = m_ptLastMousePos;
            event.wKeyState = MapKeyState();
            event.dwTimestamp = ::GetTickCount();
            m_pFocus->Event(event);
         }
      }
      break;
   }
   return false;
}

bool CPaintManagerUI::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes)
{
#ifdef _DEBUG
   switch( uMsg ) {
   case WM_NCPAINT:
   case WM_NCHITTEST:
   case WM_SETCURSOR:
      break;
   default:
      TRACE(_T("MSG: %-20s (%08ld)"), TRACEMSG(uMsg), ::GetTickCount());
   }
#endif
   // Not ready yet?
   if( m_hWndPaint == NULL ) return false;
   // Cycle through listeners
   for( int i = 0; i < m_aMessageFilters.GetSize(); i++ ) 
   {
      bool bHandled = false;
      LRESULT lResult = static_cast<IMessageFilterUI*>(m_aMessageFilters[i])->MessageHandler(uMsg, wParam, lParam, bHandled);
      if( bHandled ) {
         lRes = lResult;
         return true;
      }
   }
   // Custom handling of events
   switch( uMsg ) {
   case WM_APP + 1:
      {
         // Delayed control-tree cleanup. See AttachDialog() for details.
         for( int i = 0; i < m_aDelayedCleanup.GetSize(); i++ ) delete static_cast<CControlUI*>(m_aDelayedCleanup[i]);
         m_aDelayedCleanup.Empty();
      }
      break;
   case WM_CLOSE:
      {
         // Make sure all matching "closing" events are sent
         TEventUI event = { 0 };
         event.ptMouse = m_ptLastMousePos;
         event.dwTimestamp = ::GetTickCount();
         if( m_pEventHover != NULL ) {
            event.Type = UIEVENT_MOUSELEAVE;
            event.pSender = m_pEventHover;
            m_pEventHover->Event(event);
         }
         if( m_pEventClick != NULL ) {
            event.Type = UIEVENT_BUTTONUP;
            event.pSender = m_pEventClick;
            m_pEventClick->Event(event);
         }
         SetFocus(NULL);
         // Hmmph, the usual Windows tricks to avoid
         // focus loss...
         HWND hwndParent = GetWindowOwner(m_hWndPaint);
         if( hwndParent != NULL ) ::SetFocus(hwndParent);
      }
      break;
   case WM_ERASEBKGND:
      {
         // We'll do the painting here...
         lRes = 1;
      }
      return true;
   case WM_PAINT:
      {
         // Should we paint?
         RECT rcPaint = { 0 };
         if( !::GetUpdateRect(m_hWndPaint, &rcPaint, FALSE) ) return true;
         // Do we need to resize anything?
         // This is the time where we layout the controls on the form.
         // We delay this even from the WM_SIZE messages since resizing can be
         // a very expensize operation.
         if( m_bResizeNeeded ) {
            RECT rcClient = { 0 };
            ::GetClientRect(m_hWndPaint, &rcClient);
            if( !::IsRectEmpty(&rcClient) ) {
               HDC hDC = ::CreateCompatibleDC(m_hDcPaint);
               m_pRoot->SetPos(rcClient);
               ::DeleteDC(hDC);
               m_bResizeNeeded = false;
               // We'll want to notify the window when it is first initialized
               // with the correct layout. The window form would take the time
               // to submit swipes/animations.
               if( m_bFirstLayout ) {
                  m_bFirstLayout = false;
                  SendNotify(m_pRoot, _T("windowinit"));
               }
            }
            // Reset offscreen device
            if( m_hDcOffscreen != NULL ) ::DeleteDC(m_hDcOffscreen);
            if( m_hbmpOffscreen != NULL ) ::DeleteObject(m_hbmpOffscreen);
            m_hDcOffscreen = NULL;
            m_hbmpOffscreen = NULL;
         }
         // Set focus to first control?
         if( m_bFocusNeeded ) {
            SetNextTabControl();
         }
         //
         // Render screen
         //
         if( m_anim.IsAnimating() )
         {
            // 3D animation in progress
            m_anim.Render();
            // Do a minimum paint loop
            // Keep the client area invalid so we generate lots of
            // WM_PAINT messages. Cross fingers that Windows doesn't
            // batch these somehow in the future.
            PAINTSTRUCT ps = { 0 };
            ::BeginPaint(m_hWndPaint, &ps);
            ::EndPaint(m_hWndPaint, &ps);
            ::InvalidateRect(m_hWndPaint, NULL, FALSE);
         }
         else if( m_anim.IsJobScheduled() ) {
            // Animation system needs to be initialized
            m_anim.Init(m_hWndPaint);
            // A 3D animation was scheduled; allow the render engine to
            // capture the window content and repaint some other time
            if( !m_anim.PrepareAnimation(m_hWndPaint) ) m_anim.CancelJobs();
            ::InvalidateRect(m_hWndPaint, NULL, TRUE);
         }
         else
         {
            // Standard painting of control-tree - no 3D animation now.
            // Prepare offscreen bitmap?
            if( m_bOffscreenPaint && m_hbmpOffscreen == NULL )
            {
               RECT rcClient = { 0 };
               ::GetClientRect(m_hWndPaint, &rcClient);
               m_hDcOffscreen = ::CreateCompatibleDC(m_hDcPaint);
               m_hbmpOffscreen = ::CreateCompatibleBitmap(m_hDcPaint, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top); 
               ASSERT(m_hDcOffscreen);
               ASSERT(m_hbmpOffscreen);
            }
            // Begin Windows paint
            PAINTSTRUCT ps = { 0 };
            ::BeginPaint(m_hWndPaint, &ps);
            if( m_bOffscreenPaint )
            {
               // We have an offscreen device to paint on for flickerfree display.
               HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(m_hDcOffscreen, m_hbmpOffscreen);
               // Paint the image on the offscreen bitmap
               int iSaveDC = ::SaveDC(m_hDcOffscreen);
               m_pRoot->DoPaint(m_hDcOffscreen, ps.rcPaint);
               ::RestoreDC(m_hDcOffscreen, iSaveDC);
               // Draw alpha bitmaps on top?
               for( int i = 0; i < m_aPostPaint.GetSize(); i++ ) {
                  TPostPaintUI* pBlit = static_cast<TPostPaintUI*>(m_aPostPaint[i]);
                  CBlueRenderEngineUI::DoPaintAlphaBitmap(m_hDcOffscreen, this, pBlit->hBitmap, pBlit->rc, pBlit->iAlpha);
               }
               m_aPostPaint.Empty();
               // Blit offscreen bitmap back to display
               ::BitBlt(ps.hdc, 
                  ps.rcPaint.left, 
                  ps.rcPaint.top, 
                  ps.rcPaint.right - ps.rcPaint.left,
                  ps.rcPaint.bottom - ps.rcPaint.top,
                  m_hDcOffscreen,
                  ps.rcPaint.left,
                  ps.rcPaint.top,
                  SRCCOPY);
               ::SelectObject(m_hDcOffscreen, hOldBitmap);
            }
            else
            {
               // A standard paint job
               int iSaveDC = ::SaveDC(ps.hdc);
               m_pRoot->DoPaint(ps.hdc, ps.rcPaint);
               ::RestoreDC(ps.hdc, iSaveDC);
            }
            // All Done!
            ::EndPaint(m_hWndPaint, &ps);
         }
      }
      // If any of the painting requested a resize again, we'll need
      // to invalidate the entire window once more.
      if( m_bResizeNeeded ) ::InvalidateRect(m_hWndPaint, NULL, FALSE);
      return true;
   case WM_PRINTCLIENT:
      {
         RECT rcClient;
         ::GetClientRect(m_hWndPaint, &rcClient);
         HDC hDC = (HDC) wParam;
         int save = ::SaveDC(hDC);
         m_pRoot->DoPaint(hDC, rcClient);
         // Check for traversing children. The crux is that WM_PRINT will assume
         // that the DC is positioned at frame coordinates and will paint the child
         // control at the wrong position. We'll simulate the entire thing instead.
         if( (lParam & PRF_CHILDREN) != 0 ) {
            HWND hWndChild = ::GetWindow(m_hWndPaint, GW_CHILD);
            while( hWndChild != NULL ) {
               RECT rcPos = { 0 };
               ::GetWindowRect(hWndChild, &rcPos);
               ::MapWindowPoints(HWND_DESKTOP, m_hWndPaint, reinterpret_cast<LPPOINT>(&rcPos), 2);
               ::SetWindowOrgEx(hDC, -rcPos.left, -rcPos.top, NULL);
               // NOTE: We use WM_PRINT here rather than the expected WM_PRINTCLIENT
               //       since the latter will not print the nonclient correctly for
               //       EDIT controls.
               ::SendMessage(hWndChild, WM_PRINT, wParam, lParam | PRF_NONCLIENT);
               hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
            }
         }
         ::RestoreDC(hDC, save);
      }
      break;
   case WM_GETMINMAXINFO:
      {
         LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
         lpMMI->ptMinTrackSize.x = m_szMinWindow.cx;
         lpMMI->ptMinTrackSize.y = m_szMinWindow.cy;
      }
      break;
   case WM_SIZE:
      {
         if( m_pFocus != NULL ) {
            TEventUI event = { 0 };
            event.Type = UIEVENT_WINDOWSIZE;
            event.dwTimestamp = ::GetTickCount();
            m_pFocus->Event(event);
         }
         if( m_anim.IsAnimating() ) m_anim.CancelJobs();
         m_bResizeNeeded = true;
      }
      return true;
   case WM_TIMER:
      {
         for( int i = 0; i < m_aTimers.GetSize(); i++ ) {
            const TIMERINFO* pTimer = static_cast<TIMERINFO*>(m_aTimers[i]);
            if( pTimer->hWnd == m_hWndPaint && pTimer->uWinTimer == LOWORD(wParam) ) {
               TEventUI event = { 0 };
               event.Type = UIEVENT_TIMER;
               event.wParam = pTimer->nLocalID;
               event.dwTimestamp = ::GetTickCount();
               pTimer->pSender->Event(event);
               break;
            }
         }
      }
      break;
   case WM_MOUSEHOVER:
      {
         m_bMouseTracking = false;
         POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
         CControlUI* pHover = FindControl(pt);
         if( pHover == NULL ) break;
         // Generate mouse hover event
         if( m_pEventHover != NULL ) {
            TEventUI event = { 0 };
            event.ptMouse = pt;
            event.Type = UIEVENT_MOUSEHOVER;
            event.pSender = pHover;
            event.dwTimestamp = ::GetTickCount();
            m_pEventHover->Event(event);
         }
         // Create tooltip information
         CStdString sToolTip = pHover->GetToolTip();
         if( sToolTip.IsEmpty() ) return true;
         sToolTip.ProcessResourceTokens();
         ::ZeroMemory(&m_ToolTip, sizeof(TOOLINFO));
         m_ToolTip.cbSize = sizeof(TOOLINFO);
         m_ToolTip.uFlags = TTF_IDISHWND;
         m_ToolTip.hwnd = m_hWndPaint;
         m_ToolTip.uId = (UINT) m_hWndPaint;
         m_ToolTip.hinst = m_hInstance;
         m_ToolTip.lpszText = const_cast<LPTSTR>( (LPCTSTR) sToolTip );
         m_ToolTip.rect = pHover->GetPos();
         if( m_hwndTooltip == NULL ) {
            m_hwndTooltip = ::CreateWindowEx(0, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_hWndPaint, NULL, m_hInstance, NULL);
            ::SendMessage(m_hwndTooltip, TTM_ADDTOOL, 0, (LPARAM) &m_ToolTip);
         }
         ::SendMessage(m_hwndTooltip, TTM_SETTOOLINFO, 0, (LPARAM) &m_ToolTip);
         ::SendMessage(m_hwndTooltip, TTM_TRACKACTIVATE, TRUE, (LPARAM) &m_ToolTip);
      }
      return true;
   case WM_MOUSELEAVE:
      {
         if( m_hwndTooltip != NULL ) ::SendMessage(m_hwndTooltip, TTM_TRACKACTIVATE, FALSE, (LPARAM) &m_ToolTip);
         if( m_bMouseTracking ) ::SendMessage(m_hWndPaint, WM_MOUSEMOVE, 0, (LPARAM) -1);
         m_bMouseTracking = false;
      }
      break;
   case WM_MOUSEMOVE:
      {
         // Start tracking this entire window again...
         if( !m_bMouseTracking ) {
            TRACKMOUSEEVENT tme = { 0 };
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_HOVER | TME_LEAVE;
            tme.hwndTrack = m_hWndPaint;
            tme.dwHoverTime = m_hwndTooltip == NULL ? 1000UL : (DWORD) ::SendMessage(m_hwndTooltip, TTM_GETDELAYTIME, TTDT_INITIAL, 0L);
            _TrackMouseEvent(&tme);
            m_bMouseTracking = true;
         }
         // Generate the appropriate mouse messages
         POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
         m_ptLastMousePos = pt;
         CControlUI* pNewHover = FindControl(pt);
         if( pNewHover != NULL && pNewHover->GetManager() != this ) break;
         TEventUI event = { 0 };
         event.ptMouse = pt;
         event.dwTimestamp = ::GetTickCount();
         if( pNewHover != m_pEventHover && m_pEventHover != NULL ) {
            event.Type = UIEVENT_MOUSELEAVE;
            event.pSender = pNewHover;
            m_pEventHover->Event(event);
            m_pEventHover = NULL;
            if( m_hwndTooltip != NULL ) ::SendMessage(m_hwndTooltip, TTM_TRACKACTIVATE, FALSE, (LPARAM) &m_ToolTip);
         }
         if( pNewHover != m_pEventHover && pNewHover != NULL ) {
            event.Type = UIEVENT_MOUSEENTER;
            event.pSender = m_pEventHover;
            pNewHover->Event(event);
            m_pEventHover = pNewHover;
         }
         if( m_pEventClick != NULL ) {
            event.Type = UIEVENT_MOUSEMOVE;
            event.pSender = NULL;
            m_pEventClick->Event(event);
         }
         else if( pNewHover != NULL ) {
            event.Type = UIEVENT_MOUSEMOVE;
            event.pSender = NULL;
            pNewHover->Event(event);
         }
      }
      break;
   case WM_LBUTTONDOWN:
      {
         // We alway set focus back to our app (this helps
         // when Win32 child windows are placed on the dialog
         // and we need to remove them on focus change).
         ::SetFocus(m_hWndPaint);
         POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
         m_ptLastMousePos = pt;
         CControlUI* pControl = FindControl(pt);
         if( pControl == NULL ) break;
         if( pControl->GetManager() != this ) break;
         m_pEventClick = pControl;
         pControl->SetFocus();
         TEventUI event = { 0 };
         event.Type = UIEVENT_BUTTONDOWN;
         event.wParam = wParam;
         event.lParam = lParam;
         event.ptMouse = pt;
         event.wKeyState = wParam;
         event.dwTimestamp = ::GetTickCount();
         pControl->Event(event);
         // No need to burden user with 3D animations
         m_anim.CancelJobs();
         // We always capture the mouse
         ::SetCapture(m_hWndPaint);
      }
      break;
   case WM_LBUTTONUP:
      {
         POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
         m_ptLastMousePos = pt;
         if( m_pEventClick == NULL ) break;
         ::ReleaseCapture();
         TEventUI event = { 0 };
         event.Type = UIEVENT_BUTTONUP;
         event.wParam = wParam;
         event.lParam = lParam;
         event.ptMouse = pt;
         event.wKeyState = wParam;
         event.dwTimestamp = ::GetTickCount();
         m_pEventClick->Event(event);
         m_pEventClick = NULL;
      }
      break;
   case WM_LBUTTONDBLCLK:
      {
         POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
         m_ptLastMousePos = pt;
         CControlUI* pControl = FindControl(pt);
         if( pControl == NULL ) break;
         if( pControl->GetManager() != this ) break;
         TEventUI event = { 0 };
         event.Type = UIEVENT_DBLCLICK;
         event.ptMouse = pt;
         event.wKeyState = wParam;
         event.dwTimestamp = ::GetTickCount();
         pControl->Event(event);
         m_pEventClick = pControl;
         // We always capture the mouse
         ::SetCapture(m_hWndPaint);
      }
      break;
   case WM_CHAR:
      {
         if( m_pFocus == NULL ) break;
         TEventUI event = { 0 };
         event.Type = UIEVENT_CHAR;
         event.chKey = wParam;
         event.ptMouse = m_ptLastMousePos;
         event.wKeyState = MapKeyState();
         event.dwTimestamp = ::GetTickCount();
         m_pFocus->Event(event);
      }
      break;
   case WM_KEYDOWN:
      {
         if( m_pFocus == NULL ) break;
         TEventUI event = { 0 };
         event.Type = UIEVENT_KEYDOWN;
         event.chKey = wParam;
         event.ptMouse = m_ptLastMousePos;
         event.wKeyState = MapKeyState();
         event.dwTimestamp = ::GetTickCount();
         m_pFocus->Event(event);
         m_pEventKey = m_pFocus;
      }
      break;
   case WM_KEYUP:
      {
         if( m_pEventKey == NULL ) break;
         TEventUI event = { 0 };
         event.Type = UIEVENT_KEYUP;
         event.chKey = wParam;
         event.ptMouse = m_ptLastMousePos;
         event.wKeyState = MapKeyState();
         event.dwTimestamp = ::GetTickCount();
         m_pEventKey->Event(event);
         m_pEventKey = NULL;
      }
      break;
   case WM_SETCURSOR:
      {
         POINT pt = { 0 };
         ::GetCursorPos(&pt);
         ::ScreenToClient(m_hWndPaint, &pt);
         CControlUI* pControl = FindControl(pt);
         if( pControl == NULL ) break;
         if( (pControl->GetControlFlags() & UIFLAG_SETCURSOR) == 0 ) break;
         TEventUI event = { 0 };
         event.Type = UIEVENT_SETCURSOR;
         event.wParam = wParam;
         event.lParam = lParam;
         event.ptMouse = pt;
         event.wKeyState = MapKeyState();
         event.dwTimestamp = ::GetTickCount();
         pControl->Event(event);
      }
      return true;
   case WM_CTLCOLOREDIT:
      {
         ::DefWindowProc(m_hWndPaint, uMsg, wParam, lParam);
         HDC hDC = (HDC) wParam;
         ::SetTextColor(hDC, GetThemeColor(UICOLOR_EDIT_TEXT_NORMAL));
         ::SetBkColor(hDC, GetThemeColor(UICOLOR_EDIT_BACKGROUND_NORMAL));
         lRes = (LRESULT) GetThemeBrush(UICOLOR_EDIT_BACKGROUND_NORMAL);
      }
      return true;
   case WM_MEASUREITEM:
      {
         if( wParam == 0 ) break;
         HWND hWndChild = ::GetDlgItem(m_hWndPaint, ((LPMEASUREITEMSTRUCT) lParam)->CtlID);
         lRes = ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
         return true;
      }
      break;
   case WM_DRAWITEM:
      {
         if( wParam == 0 ) break;
         HWND hWndChild = ((LPDRAWITEMSTRUCT) lParam)->hwndItem;
         lRes = ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
         return true;
      }
      break;
   case WM_VSCROLL:
      {
         if( lParam == NULL ) break;
         CContainerUI* pContainer = static_cast<CContainerUI*>(::GetProp((HWND) lParam, "WndX"));
         if( pContainer == NULL ) break;
         TEventUI event = { 0 };
         event.Type = UIEVENT_VSCROLL;
         event.wParam = wParam;
         event.lParam = lParam;
         event.dwTimestamp = ::GetTickCount();
         pContainer->Event(event);
      }
      break;
   case WM_NOTIFY:
      {
         LPNMHDR lpNMHDR = (LPNMHDR) lParam;
         if( lpNMHDR != NULL ) lRes = ::SendMessage(lpNMHDR->hwndFrom, OCM__BASE + uMsg, wParam, lParam);
         return true;
      }
      break;
   case WM_COMMAND:
      {
         if( lParam == 0 ) break;
         HWND hWndChild = (HWND) lParam;
         lRes = ::SendMessage(hWndChild, OCM__BASE + uMsg, wParam, lParam);
         return true;
      }
      break;
   default:
      // Handle WM_MOUSEWHEEL
      if( (uMsg == m_uMsgMouseWheel || uMsg == 0x020A) && m_pFocus != NULL )
      {
         int zDelta = (int) (short) HIWORD(wParam);
         TEventUI event = { 0 };
         event.Type = UIEVENT_SCROLLWHEEL;
         event.wParam = MAKELPARAM(zDelta < 0 ? SB_LINEDOWN : SB_LINEUP, 0);
         event.lParam = lParam;
         event.dwTimestamp = ::GetTickCount();
         m_pFocus->Event(event);
         // Simulate regular scrolling by sending scroll events
         event.Type = UIEVENT_VSCROLL;
         for( int i = 0; i < abs(zDelta); i += 40 ) m_pFocus->Event(event);
         // Let's make sure that the scroll item below the cursor is the same as before...
         ::SendMessage(m_hWndPaint, WM_MOUSEMOVE, 0, (LPARAM) MAKELPARAM(m_ptLastMousePos.x, m_ptLastMousePos.y));
      }
      break;
   }
   return false;
}

void CPaintManagerUI::UpdateLayout()
{
   m_bResizeNeeded = true;
   ::InvalidateRect(m_hWndPaint, NULL, FALSE);
}

void CPaintManagerUI::Invalidate(RECT rcItem)
{
   ::InvalidateRect(m_hWndPaint, &rcItem, FALSE);
}

bool CPaintManagerUI::AttachDialog(CControlUI* pControl)
{
   ASSERT(::IsWindow(m_hWndPaint));
   // Reset any previous attachment
   SetFocus(NULL);
   m_pEventKey = NULL;
   m_pEventHover = NULL;
   m_pEventClick = NULL;
   m_aNameHash.Empty();
   // Remove the existing control-tree. We might have gotten inside this function as
   // a result of an event fired or similar, so we cannot just delete the objects and
   // pull the internal memory of the calling code. We'll delay the cleanup.
   if( m_pRoot != NULL ) {
      m_aDelayedCleanup.Add(m_pRoot);
      ::PostMessage(m_hWndPaint, WM_APP + 1, 0, 0L);
   }
   // Set the dialog root element
   m_pRoot = pControl;
   // Go ahead...
   m_bResizeNeeded = true;
   m_bFirstLayout = true;
   m_bFocusNeeded = true;
   // Initiate all control
   return InitControls(pControl);
}

bool CPaintManagerUI::InitControls(CControlUI* pControl, CControlUI* pParent /*= NULL*/)
{
   ASSERT(pControl);
   if( pControl == NULL ) return false;
   pControl->SetManager(this, pParent != NULL ? pParent : pControl->GetParent());
   // We're usually initializing the control after adding some more of them to the tree,
   // and thus this would be a good time to request the name-map rebuilt.
   m_aNameHash.Empty();
   return true;
}

void CPaintManagerUI::ReapObjects(CControlUI* pControl)
{
   if( pControl == m_pEventKey ) m_pEventKey = NULL;
   if( pControl == m_pEventHover ) m_pEventHover = NULL;
   if( pControl == m_pEventClick ) m_pEventClick = NULL;
   // TODO: Do something with name-hash-map
   //m_aNameHash.Empty();
}

void CPaintManagerUI::MessageLoop()
{
   MSG msg = { 0 };
   while( ::GetMessage(&msg, NULL, 0, 0) ) {
      if( !CPaintManagerUI::TranslateMessage(&msg) ) {
         ::TranslateMessage(&msg);
         ::DispatchMessage(&msg);
      }
   }
}

bool CPaintManagerUI::TranslateMessage(const LPMSG pMsg)
{
   // Pretranslate Message takes care of system-wide messages, such as
   // tabbing and shortcut key-combos. We'll look for all messages for
   // each window and any child control attached.
   HWND hwndParent = ::GetParent(pMsg->hwnd);
   UINT uStyle = GetWindowStyle(pMsg->hwnd);
   LRESULT lRes = 0;
   for( int i = 0; i < m_aPreMessages.GetSize(); i++ ) {
      CPaintManagerUI* pT = static_cast<CPaintManagerUI*>(m_aPreMessages[i]);
      if( pMsg->hwnd == pT->GetPaintWindow()
         || (hwndParent == pT->GetPaintWindow() && ((uStyle & WS_CHILD) != 0)) )
      {
         if( pT->PreMessageHandler(pMsg->message, pMsg->wParam, pMsg->lParam, lRes) ) return true;
      }
   }
   return false;
}

bool CPaintManagerUI::AddAnimJob(const CAnimJobUI& job)
{
   CAnimJobUI* pJob = new CAnimJobUI(job);
   if( pJob == NULL ) return false;
   ::InvalidateRect(m_hWndPaint, NULL, FALSE);
   return m_anim.AddJob(pJob);
}

bool CPaintManagerUI::AddPostPaintBlit(const TPostPaintUI& job)
{
   return m_aPostPaint.Add(&job);
}

CControlUI* CPaintManagerUI::GetFocus() const
{
   return m_pFocus;
}

void CPaintManagerUI::SetFocus(CControlUI* pControl)
{
   // Paint manager window has focus?
   if( ::GetFocus() != m_hWndPaint ) ::SetFocus(m_hWndPaint);
   // Already has focus?
   if( pControl == m_pFocus ) return;
   // Remove focus from old control
   if( m_pFocus != NULL ) 
   {
      TEventUI event = { 0 };
      event.Type = UIEVENT_KILLFOCUS;
      event.pSender = pControl;
      event.dwTimestamp = ::GetTickCount();
      m_pFocus->Event(event);
      SendNotify(m_pFocus, _T("killfocus"));
      m_pFocus = NULL;
   }
   // Set focus to new control
   if( pControl != NULL 
       && pControl->GetManager() == this 
       && pControl->IsVisible() 
       && pControl->IsEnabled() ) 
   {
      m_pFocus = pControl;
      TEventUI event = { 0 };
      event.Type = UIEVENT_SETFOCUS;
      event.pSender = pControl;
      event.dwTimestamp = ::GetTickCount();
      m_pFocus->Event(event);
      SendNotify(m_pFocus, _T("setfocus"));
   }
}

bool CPaintManagerUI::SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse)
{
   ASSERT(pControl!=NULL);
   ASSERT(uElapse>0);
   m_uTimerID = (++m_uTimerID) % 0xFF;
   if( !::SetTimer(m_hWndPaint, m_uTimerID, uElapse, NULL) ) return FALSE;
   TIMERINFO* pTimer = new TIMERINFO;
   if( pTimer == NULL ) return FALSE;
   pTimer->hWnd = m_hWndPaint;
   pTimer->pSender = pControl;
   pTimer->nLocalID = nTimerID;
   pTimer->uWinTimer = m_uTimerID;
   return m_aTimers.Add(pTimer);
}

bool CPaintManagerUI::KillTimer(CControlUI* pControl, UINT nTimerID)
{
   ASSERT(pControl!=NULL);
   for( int i = 0; i< m_aTimers.GetSize(); i++ ) {
      TIMERINFO* pTimer = static_cast<TIMERINFO*>(m_aTimers[i]);
      if( pTimer->pSender == pControl
          && pTimer->hWnd == m_hWndPaint
          && pTimer->nLocalID == nTimerID )
      {
         ::KillTimer(pTimer->hWnd, pTimer->uWinTimer);
         delete pTimer;
         return m_aTimers.Remove(i);
      }
   }
   return false;
}

bool CPaintManagerUI::SetNextTabControl(bool bForward)
{
   // If we're in the process of restructuring the layout we can delay the
   // focus calulation until the next repaint.
   if( m_bResizeNeeded && bForward ) {
      m_bFocusNeeded = true;
      ::InvalidateRect(m_hWndPaint, NULL, FALSE);
      return true;
   }
   // Find next/previous tabbable control
   FINDTABINFO info1 = { 0 };
   info1.pFocus = m_pFocus;
   info1.bForward = bForward;
   CControlUI* pControl = m_pRoot->FindControl(__FindControlFromTab, &info1, UIFIND_VISIBLE | UIFIND_ENABLED | UIFIND_ME_FIRST);
   if( pControl == NULL ) {  
      if( bForward ) {
         // Wrap around
         FINDTABINFO info2 = { 0 };
         info2.pFocus = bForward ? NULL : info1.pLast;
         info2.bForward = bForward;
         pControl = m_pRoot->FindControl(__FindControlFromTab, &info2, UIFIND_VISIBLE | UIFIND_ENABLED | UIFIND_ME_FIRST);
      }
      else {
         pControl = info1.pLast;
      }
   }
   if( pControl != NULL ) SetFocus(pControl);
   m_bFocusNeeded = false;
   return true;
}

TSystemSettingsUI CPaintManagerUI::GetSystemSettings() const
{
   return m_SystemConfig;
}

void CPaintManagerUI::SetSystemSettings(const TSystemSettingsUI Config)
{
   m_SystemConfig = Config;
}

TSystemMetricsUI CPaintManagerUI::GetSystemMetrics() const
{
   return m_SystemMetrics;
}

bool CPaintManagerUI::AddNotifier(INotifyUI* pNotifier)
{
   ASSERT(m_aNotifiers.Find(pNotifier)<0);
   return m_aNotifiers.Add(pNotifier);
}

bool CPaintManagerUI::RemoveNotifier(INotifyUI* pNotifier)
{
   for( int i = 0; i < m_aNotifiers.GetSize(); i++ ) {
      if( static_cast<INotifyUI*>(m_aNotifiers[i]) == pNotifier ) {
         return m_aNotifiers.Remove(i);
      }
   }
   return false;
}

bool CPaintManagerUI::AddMessageFilter(IMessageFilterUI* pFilter)
{
   ASSERT(m_aMessageFilters.Find(pFilter)<0);
   return m_aMessageFilters.Add(pFilter);
}

bool CPaintManagerUI::RemoveMessageFilter(IMessageFilterUI* pFilter)
{
   for( int i = 0; i < m_aMessageFilters.GetSize(); i++ ) {
      if( static_cast<IMessageFilterUI*>(m_aMessageFilters[i]) == pFilter ) {
         return m_aMessageFilters.Remove(i);
      }
   }
   return false;
}

void CPaintManagerUI::SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/)
{
   TNotifyUI Msg;
   Msg.pSender = pControl;
   Msg.sType = pstrMessage;
   Msg.wParam = 0;
   Msg.lParam = 0;
   SendNotify(Msg);
}

void CPaintManagerUI::SendNotify(TNotifyUI& Msg)
{
   // Pre-fill some standard members
   Msg.ptMouse = m_ptLastMousePos;
   Msg.dwTimestamp = ::GetTickCount();
   // Allow sender control to react
   Msg.pSender->Notify(Msg);
   // Send to all listeners
   for( int i = 0; i < m_aNotifiers.GetSize(); i++ ) {
      static_cast<INotifyUI*>(m_aNotifiers[i])->Notify(Msg);
   }
}

HFONT CPaintManagerUI::GetThemeFont(UITYPE_FONT Index) const
{
   if( Index <= UIFONT__FIRST || Index >= UIFONT__LAST ) return NULL;
   if( m_hFonts[Index] == NULL ) m_hFonts[Index] = ::CreateFontIndirect(&m_aLogFonts[Index]);
   return m_hFonts[Index];
}

HICON CPaintManagerUI::GetThemeIcon(int iIndex, int cxySize) const
{
   if( m_himgIcons16 == NULL ) {
      m_himgIcons16 = ImageList_LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_ICONS16), 16, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
      m_himgIcons24 = ImageList_LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_ICONS16), 16, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
      m_himgIcons32 = ImageList_LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_ICONS16), 16, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
      m_himgIcons50 = ImageList_LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_ICONS50), 50, 0, RGB(255,0,255), IMAGE_BITMAP, LR_CREATEDIBSECTION);
   }
   if( cxySize == 16 ) return ImageList_GetIcon(m_himgIcons16, iIndex, ILD_NORMAL);
   else if( cxySize == 24 ) return ImageList_GetIcon(m_himgIcons24, iIndex, ILD_NORMAL);
   else if( cxySize == 32 ) return ImageList_GetIcon(m_himgIcons32, iIndex, ILD_NORMAL);
   else if( cxySize == 50 ) return ImageList_GetIcon(m_himgIcons50, iIndex, ILD_NORMAL);
   return NULL;
}

HPEN CPaintManagerUI::GetThemePen(UITYPE_COLOR Index) const
{
   if( Index <= UICOLOR__FIRST || Index >= UICOLOR__LAST ) return NULL;
   if( m_hPens[Index] == NULL ) m_hPens[Index] = ::CreatePen(PS_SOLID, 1, m_clrColors[Index][0]);
   return m_hPens[Index];
}

HBRUSH CPaintManagerUI::GetThemeBrush(UITYPE_COLOR Index) const
{
   if( Index <= UICOLOR__FIRST || Index >= UICOLOR__LAST ) return NULL;
   if( m_hBrushes[Index] == NULL ) m_hBrushes[Index] = ::CreateSolidBrush(m_clrColors[Index][0]);
   return m_hBrushes[Index];
}

const TEXTMETRIC& CPaintManagerUI::GetThemeFontInfo(UITYPE_FONT Index) const
{
   if( Index <= UIFONT__FIRST || Index >= UIFONT__LAST ) return m_aTextMetrics[0];
   if( m_aTextMetrics[Index].tmHeight == 0 ) {
      HFONT hOldFont = (HFONT) ::SelectObject(m_hDcPaint, GetThemeFont(Index));
      ::GetTextMetrics(m_hDcPaint, &m_aTextMetrics[Index]);
      ::SelectObject(m_hDcPaint, hOldFont);
   }
   return m_aTextMetrics[Index];
}

COLORREF CPaintManagerUI::GetThemeColor(UITYPE_COLOR Index) const
{
   if( Index <= UICOLOR__FIRST || Index >= UICOLOR__LAST ) return RGB(0,0,0);
   return m_clrColors[Index][0];
}

bool CPaintManagerUI::GetThemeColorPair(UITYPE_COLOR Index, COLORREF& clr1, COLORREF& clr2) const
{
   if( Index <= UICOLOR__FIRST || Index >= UICOLOR__LAST ) return false;
   clr1 = m_clrColors[Index][0];
   clr2 = m_clrColors[Index][1];
   return true;
}

CControlUI* CPaintManagerUI::FindControl(LPCTSTR pstrName)
{
   ASSERT(m_pRoot);
   // First time here? Build hash array...
   if( m_aNameHash.GetSize() == 0 ) {
      int nCount = 0;
      m_pRoot->FindControl(__FindControlFromCount, &nCount, UIFIND_ALL);
      m_aNameHash.Resize(nCount + (nCount / 10));
      m_pRoot->FindControl(__FindControlFromNameHash, this, UIFIND_ALL);
   }
   // Find name in the hash array
   int nCount = 0;
   int nSize = m_aNameHash.GetSize();
   int iNameHash = (int) (GetNameHash(pstrName) % nSize);
   while( m_aNameHash[iNameHash] != NULL ) {
      if( static_cast<CControlUI*>(m_aNameHash[iNameHash])->GetName() == pstrName ) return static_cast<CControlUI*>(m_aNameHash[iNameHash]);
      iNameHash = (iNameHash + 1) % nSize;
      if( ++nCount >= nSize ) break;
   }
   return NULL;
}

CControlUI* CPaintManagerUI::FindControl(POINT pt) const
{
   ASSERT(m_pRoot);
   return m_pRoot->FindControl(__FindControlFromPoint, &pt, UIFIND_VISIBLE | UIFIND_HITTEST);
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromCount(CControlUI* /*pThis*/, LPVOID pData)
{
   int* pnCount = static_cast<int*>(pData);
   (*pnCount)++;
   return NULL;  // Count all controls
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromTab(CControlUI* pThis, LPVOID pData)
{
   FINDTABINFO* pInfo = static_cast<FINDTABINFO*>(pData);
   if( pInfo->pFocus == pThis ) {
      if( pInfo->bForward ) pInfo->bNextIsIt = true;
      return pInfo->bForward ? NULL : pInfo->pLast;
   }
   if( (pThis->GetControlFlags() & UIFLAG_TABSTOP) == 0 ) return NULL;
   pInfo->pLast = pThis;
   if( pInfo->bNextIsIt ) return pThis;
   if( pInfo->pFocus == NULL ) return pThis;
   return NULL;  // Examine all controls
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromNameHash(CControlUI* pThis, LPVOID pData)
{
   CPaintManagerUI* pManager = static_cast<CPaintManagerUI*>(pData);
   // No name?
   const CStdString& sName = pThis->GetName();
   if( sName.IsEmpty() ) return NULL;
   // Add this control to the hash list
   int nCount = 0;
   int nSize = pManager->m_aNameHash.GetSize();
   int iNameHash = (int) (GetNameHash(sName) % nSize);
   while( pManager->m_aNameHash[iNameHash] != NULL ) {
      iNameHash = (iNameHash + 1) % nSize;
      if( ++nCount == nSize ) return NULL;
   }
   pManager->m_aNameHash.SetAt(iNameHash, pThis);
   return NULL; // Attempt to add all controls
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromShortcut(CControlUI* pThis, LPVOID pData)
{
   FINDSHORTCUT* pFS = static_cast<FINDSHORTCUT*>(pData);
   if( pFS->ch == toupper(pThis->GetShortcut()) ) pFS->bPickNext = true;
   if( _tcsstr(pThis->GetClass(), _T("Label")) != NULL ) return NULL;   // Labels never get focus!
   return pFS->bPickNext ? pThis : NULL;
}

CControlUI* CALLBACK CPaintManagerUI::__FindControlFromPoint(CControlUI* pThis, LPVOID pData)
{
   LPPOINT pPoint = static_cast<LPPOINT>(pData);
   return ::PtInRect(&pThis->GetPos(), *pPoint) ? pThis : NULL;
}



/////////////////////////////////////////////////////////////////////////////////////
//
//

CControlUI::CControlUI() : 
   m_pManager(NULL), 
   m_pParent(NULL), 
   m_pTag(NULL),
   m_chShortcut('\0'),
   m_bVisible(true), 
   m_bFocused(false),
   m_bEnabled(true)
{
   ::ZeroMemory(&m_rcItem, sizeof(RECT));
}

CControlUI::~CControlUI()
{
   if( m_pManager != NULL ) m_pManager->ReapObjects(this);
}

bool CControlUI::IsVisible() const
{
   return m_bVisible;
}

bool CControlUI::IsEnabled() const
{
   return m_bEnabled;
}

bool CControlUI::IsFocused() const
{
   return m_bFocused;
}

UINT CControlUI::GetControlFlags() const
{
   return 0;
}

void CControlUI::SetVisible(bool bVisible)
{
   if( m_bVisible == bVisible ) return;
   m_bVisible = bVisible;
   if( m_pManager != NULL ) m_pManager->UpdateLayout();
}

void CControlUI::SetEnabled(bool bEnabled)
{
   m_bEnabled = bEnabled;
   Invalidate();
}

bool CControlUI::Activate()
{
   if( !IsVisible() ) return false;
   if( !IsEnabled() ) return false;
   return true;
}

CControlUI* CControlUI::GetParent() const
{
   return m_pParent;
}

void CControlUI::SetFocus()
{
   if( m_pManager != NULL ) m_pManager->SetFocus(this);
}

void CControlUI::SetShortcut(TCHAR ch)
{
   m_chShortcut = ch;
}

TCHAR CControlUI::GetShortcut() const
{
   return m_chShortcut;
}

CStdString CControlUI::GetText() const
{
   return m_sText;
}

void CControlUI::SetText(LPCTSTR pstrText)
{
   m_sText = pstrText;
   Invalidate();
}

UINT_PTR CControlUI::GetTag() const
{
   return m_pTag;
}

void CControlUI::SetTag(UINT_PTR pTag)
{
   m_pTag = pTag;
}

void CControlUI::SetToolTip(LPCTSTR pstrText)
{
   m_sToolTip = pstrText;
}

CStdString CControlUI::GetToolTip() const
{
   return m_sToolTip;
}

void CControlUI::Init()
{
}

CPaintManagerUI* CControlUI::GetManager() const
{
   return m_pManager;
}

void CControlUI::SetManager(CPaintManagerUI* pManager, CControlUI* pParent)
{
   bool bInit = m_pManager == NULL;
   m_pManager = pManager;
   m_pParent = pParent;
   if( bInit ) Init();
}

CStdString CControlUI::GetName() const
{
   return m_sName;
}

void CControlUI::SetName(LPCTSTR pstrName)
{
   m_sName = pstrName;
}

LPVOID CControlUI::GetInterface(LPCTSTR pstrName)
{
   if( _tcscmp(pstrName, _T("Control")) == 0 ) return this;
   return NULL;
}

CControlUI* CControlUI::FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)
{
   if( (uFlags & UIFIND_VISIBLE) != 0 && !IsVisible() ) return NULL;
   if( (uFlags & UIFIND_ENABLED) != 0 && !IsEnabled() ) return NULL;
   if( (uFlags & UIFIND_HITTEST) != 0 && !::PtInRect(&m_rcItem, * static_cast<LPPOINT>(pData)) ) return NULL;
   return Proc(this, pData);
}

RECT CControlUI::GetPos() const
{
   return m_rcItem;
}

void CControlUI::SetPos(RECT rc)
{
   m_rcItem = rc;
   // NOTE: SetPos() is usually called during the WM_PAINT cycle where all controls are
   //       being laid out. Calling UpdateLayout() again would be wrong. Refreshing the
   //       window won't hurt (if we're already inside WM_PAINT we'll just validate it out).
   Invalidate();
}

void CControlUI::Invalidate()
{
   if( m_pManager != NULL ) m_pManager->Invalidate(m_rcItem);
}

void CControlUI::UpdateLayout()
{
   if( m_pManager != NULL ) m_pManager->UpdateLayout();
}

void CControlUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_SETCURSOR )
   {
      ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
      return;
   }
   if( event.Type == UIEVENT_SETFOCUS ) 
   {
      m_bFocused = true;
      Invalidate();
      return;
   }
   if( event.Type == UIEVENT_KILLFOCUS ) 
   {
      m_bFocused = false;
      Invalidate();
      return;
   }
   if( event.Type == UIEVENT_TIMER )
   {
      m_pManager->SendNotify(this, _T("timer"), event.wParam, event.lParam);
      return;
   }
   if( m_pParent != NULL ) m_pParent->Event(event);
}

void CControlUI::Notify(TNotifyUI& /*msg*/)
{
}

void CControlUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
   if( _tcscmp(pstrName, _T("pos")) == 0 ) {
      RECT rcPos = { 0 };
      LPTSTR pstr = NULL;
      rcPos.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
      rcPos.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
      rcPos.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
      rcPos.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
      SetPos(rcPos);
   }
   else if( _tcscmp(pstrName, _T("name")) == 0 ) SetName(pstrValue);
   else if( _tcscmp(pstrName, _T("text")) == 0 ) SetText(pstrValue);
   else if( _tcscmp(pstrName, _T("tooltip")) == 0 ) SetToolTip(pstrValue);
   else if( _tcscmp(pstrName, _T("enabled")) == 0 ) SetEnabled(_tcscmp(pstrValue, _T("true")) == 0);
   else if( _tcscmp(pstrName, _T("visible")) == 0 ) SetVisible(_tcscmp(pstrValue, _T("true")) == 0);
   else if( _tcscmp(pstrName, _T("shortcut")) == 0 ) SetShortcut(pstrValue[0]);
}

CControlUI* CControlUI::ApplyAttributeList(LPCTSTR pstrList)
{
   CStdString sItem;
   CStdString sValue;
   while( *pstrList != '\0' ) {
      sItem.Empty();
      sValue.Empty();
      while( *pstrList != '\0' && *pstrList != '=' ) sItem += *pstrList++;
      ASSERT(*pstrList=='=');
      if( *pstrList++ != '=' ) return this;
      ASSERT(*pstrList=='\"');
      if( *pstrList++ != '\"' ) return this;
      while( *pstrList != '\0' && *pstrList != '\"' ) sValue += *pstrList++;
      ASSERT(*pstrList=='\"');
      if( *pstrList++ != '\"' ) return this;
      SetAttribute(sItem, sValue);
      if( *pstrList++ != ',' ) return this;
   }
   return this;
}
