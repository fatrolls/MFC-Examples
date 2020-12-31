
#include "StdAfx.h"
#include "UIEdit.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

class CSingleLineEditWnd : public CWindowWnd
{
public:
   CSingleLineEditWnd();

   void Init(CSingleLineEditUI* pOwner);

   LPCTSTR GetWindowClassName() const;
   LPCTSTR GetSuperClassName() const;
   void OnFinalMessage(HWND hWnd);

   LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
   LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
   CSingleLineEditUI* m_pOwner;
};


CSingleLineEditWnd::CSingleLineEditWnd() : m_pOwner(NULL)
{
}

void CSingleLineEditWnd::Init(CSingleLineEditUI* pOwner)
{
   CRect rcPos = pOwner->GetPos();
   rcPos.Deflate(1, 3);
   Create(pOwner->GetManager()->GetPaintWindow(), NULL, WS_CHILD | pOwner->m_uEditStyle, 0, rcPos);
   SetWindowFont(m_hWnd, pOwner->GetManager()->GetThemeFont(UIFONT_NORMAL), TRUE);
   Edit_SetText(m_hWnd, pOwner->GetText());
   Edit_SetModify(m_hWnd, FALSE);
   SendMessage(EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(2, 2));
   Edit_SetSel(m_hWnd, 0, -1);
   Edit_Enable(m_hWnd, pOwner->IsEnabled() == true);
   Edit_SetReadOnly(m_hWnd, pOwner->IsReadOnly() == true);
   ::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
   ::SetFocus(m_hWnd);
   m_pOwner = pOwner;
}

LPCTSTR CSingleLineEditWnd::GetWindowClassName() const
{
   return _T("SingleLineEditWnd");
}

LPCTSTR CSingleLineEditWnd::GetSuperClassName() const
{
   return WC_EDIT;
}

void CSingleLineEditWnd::OnFinalMessage(HWND /*hWnd*/)
{
   // Clear reference and die
   m_pOwner->m_pWindow = NULL;
   delete this;
}

LRESULT CSingleLineEditWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   LRESULT lRes = 0;
   BOOL bHandled = TRUE;
   if( uMsg == WM_KILLFOCUS ) lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
   else if( uMsg == OCM_COMMAND && GET_WM_COMMAND_CMD(wParam, lParam) == EN_CHANGE ) lRes = OnEditChanged(uMsg, wParam, lParam, bHandled);
   else bHandled = FALSE;
   if( !bHandled ) return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
   return lRes;
}

LRESULT CSingleLineEditWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
   PostMessage(WM_CLOSE);
   return lRes;
}

LRESULT CSingleLineEditWnd::OnEditChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
   if( m_pOwner == NULL ) return 0;
   // Copy text back
   int cchLen = ::GetWindowTextLength(m_hWnd) + 1;
   LPTSTR pstr = static_cast<LPTSTR>(_alloca(cchLen * sizeof(TCHAR)));
   ASSERT(pstr);
   if( pstr == NULL ) return 0;
   ::GetWindowText(m_hWnd, pstr, cchLen);
   m_pOwner->SetText(pstr);
   return 0;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CSingleLineEditUI::CSingleLineEditUI() : m_pWindow(NULL), m_uEditStyle(ES_AUTOHSCROLL), m_bReadOnly(false)
{
}

LPCTSTR CSingleLineEditUI::GetClass() const
{
   return _T("SingleLineEditUI");
}

UINT CSingleLineEditUI::GetControlFlags() const
{
   return UIFLAG_SETCURSOR | UIFLAG_TABSTOP;
}

void CSingleLineEditUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_SETCURSOR )
   {
      if( IsEnabled() ) {
         ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_IBEAM)));
         return;
      }
   }
   if( event.Type == UIEVENT_WINDOWSIZE )
   {
      if( m_pWindow != NULL ) m_pManager->SetFocus(NULL);
   }
   if( event.Type == UIEVENT_SETFOCUS ) 
   {
      if( IsEnabled() ) {
         m_pWindow = new CSingleLineEditWnd();
         ASSERT(m_pWindow);
         m_pWindow->Init(this);
      }
   }
   if( event.Type == UIEVENT_BUTTONDOWN && IsFocused() && m_pWindow == NULL ) 
   {
      // FIX: In the case of window having lost focus, editor is gone, but
      //      we don't get another SetFocus when we click on the control again.
      m_pWindow = new CSingleLineEditWnd();
      ASSERT(m_pWindow);
      m_pWindow->Init(this);
      return;
   }
   CControlUI::Event(event);
}

void CSingleLineEditUI::SetText(LPCTSTR pstrText)
{
   m_sText = pstrText;
   if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("changed"));
   Invalidate();
}

void CSingleLineEditUI::SetReadOnly(bool bReadOnly)
{
   m_bReadOnly = bReadOnly;
   Invalidate();
}

bool CSingleLineEditUI::IsReadOnly() const
{
   return m_bReadOnly;
}

void CSingleLineEditUI::SetEditStyle(UINT uStyle)
{
   m_uEditStyle = uStyle;
   Invalidate();
}

SIZE CSingleLineEditUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(0, 12 + m_pManager->GetThemeFontInfo(UIFONT_NORMAL).tmHeight);
}

void CSingleLineEditUI::DoPaint(HDC hDC, const RECT& /*rcPaint*/)
{
   UINT uState = 0;
   if( IsFocused() ) uState |= UISTATE_FOCUSED;
   if( IsReadOnly() ) uState |= UISTATE_READONLY;
   if( !IsEnabled() ) uState |= UISTATE_DISABLED;
   CBlueRenderEngineUI::DoPaintEditBox(hDC, m_pManager, m_rcItem, m_sText, uState, m_uEditStyle, false);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

class CMultiLineEditWnd : public CWindowWnd
{
public:
   void Init(CMultiLineEditUI* pOwner);

   LPCTSTR GetWindowClassName() const;
   LPCTSTR GetSuperClassName() const;
   void OnFinalMessage(HWND hWnd);

   LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
   LRESULT OnEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
   CMultiLineEditUI* m_pOwner;
};


void CMultiLineEditWnd::Init(CMultiLineEditUI* pOwner)
{
   RECT rcPos = pOwner->GetPos();
   ::InflateRect(&rcPos, -1, -3);
   Create(pOwner->m_pManager->GetPaintWindow(), NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 0, rcPos);
   SetWindowFont(m_hWnd, pOwner->m_pManager->GetThemeFont(UIFONT_NORMAL), TRUE);
   Edit_SetText(m_hWnd, pOwner->m_sText);
   Edit_SetModify(m_hWnd, FALSE);
   SendMessage(EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(2, 2));
   Edit_SetReadOnly(m_hWnd, pOwner->IsReadOnly() == true);
   Edit_Enable(m_hWnd, pOwner->IsEnabled() == true);
   if( pOwner->IsVisible() ) ::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
   m_pOwner = pOwner;
}

LPCTSTR CMultiLineEditWnd::GetWindowClassName() const
{
   return _T("MultiLineEditWnd");
}

LPCTSTR CMultiLineEditWnd::GetSuperClassName() const
{
   return WC_EDIT;
}

void CMultiLineEditWnd::OnFinalMessage(HWND /*hWnd*/)
{
   m_pOwner->m_pWindow = NULL;
   delete this;
}

LRESULT CMultiLineEditWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   LRESULT lRes = 0;
   BOOL bHandled = TRUE;
   if( uMsg == OCM_COMMAND && GET_WM_COMMAND_CMD(wParam, lParam) == EN_CHANGE ) lRes = OnEditChanged(uMsg, wParam, lParam, bHandled);
   else bHandled = FALSE;
   if( !bHandled ) return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
   return lRes;
}

LRESULT CMultiLineEditWnd::OnEditChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
   if( m_pOwner == NULL ) return 0;
   // Copy text back
   int cchLen = ::GetWindowTextLength(m_hWnd) + 1;
   LPTSTR pstr = static_cast<LPTSTR>(_alloca(cchLen * sizeof(TCHAR)));
   ASSERT(pstr);
   ::GetWindowText(m_hWnd, pstr, cchLen);
   m_pOwner->m_sText = pstr;
   m_pOwner->GetManager()->SendNotify(m_pOwner, _T("changed"));
   return 0;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CMultiLineEditUI::CMultiLineEditUI() : m_pWindow(NULL)
{
}

CMultiLineEditUI::~CMultiLineEditUI()
{
   if( m_pWindow != NULL && ::IsWindow(*m_pWindow) ) m_pWindow->Close();
}

void CMultiLineEditUI::Init()
{
   m_pWindow = new CMultiLineEditWnd();
   ASSERT(m_pWindow);
   m_pWindow->Init(this);
}

LPCTSTR CMultiLineEditUI::GetClass() const
{
   return _T("MultiLineEditUI");
}

UINT CMultiLineEditUI::GetControlFlags() const
{
   return UIFLAG_TABSTOP;
}

void CMultiLineEditUI::SetText(LPCTSTR pstrText)
{
   m_sText = pstrText;
   if( m_pWindow != NULL ) SetWindowText(*m_pWindow, pstrText);
   if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("changed"));
   Invalidate();
}

CStdString CMultiLineEditUI::GetText() const
{
   if( m_pWindow != NULL ) {
      int cchLen = ::GetWindowTextLength(*m_pWindow) + 1;
      LPTSTR pstr = static_cast<LPTSTR>(_alloca(cchLen * sizeof(TCHAR)));
      ASSERT(pstr);
      ::GetWindowText(*m_pWindow, pstr, cchLen);
      return CStdString(pstr);
   }
   return m_sText;
}

void CMultiLineEditUI::SetVisible(bool bVisible)
{
   CControlUI::SetVisible(bVisible);
   if( m_pWindow != NULL ) ::ShowWindow(*m_pWindow, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
}

void CMultiLineEditUI::SetEnabled(bool bEnabled)
{
   CControlUI::SetEnabled(bEnabled);
   if( m_pWindow != NULL ) ::EnableWindow(*m_pWindow, bEnabled == true);
}

void CMultiLineEditUI::SetReadOnly(bool bReadOnly)
{
   if( m_pWindow != NULL ) Edit_SetReadOnly(*m_pWindow, bReadOnly == true);
   Invalidate();
}

bool CMultiLineEditUI::IsReadOnly() const
{
   return (GetWindowStyle(*m_pWindow) & ES_READONLY) != 0;
}

SIZE CMultiLineEditUI::EstimateSize(SIZE /*szAvailable*/)
{
   return CSize(m_rcItem);
}

void CMultiLineEditUI::SetPos(RECT rc)
{
   if( m_pWindow != NULL ) {
      CRect rcEdit = rc;
      rcEdit.Deflate(3, 3);
      ::SetWindowPos(*m_pWindow, HWND_TOP, rcEdit.left, rcEdit.top, rcEdit.GetWidth(), rcEdit.GetHeight(), SWP_NOACTIVATE);
   }
   CControlUI::SetPos(rc);
}

void CMultiLineEditUI::SetPos(int left, int top, int right, int bottom)
{
   SetPos(CRect(left, top, right, bottom));
}

void CMultiLineEditUI::Event(TEventUI& event)
{
   if( event.Type == UIEVENT_WINDOWSIZE )
   {
      if( m_pWindow != NULL ) m_pManager->SetFocus(NULL);
   }
   if( event.Type == UIEVENT_SETFOCUS ) 
   {
      if( m_pWindow != NULL ) ::SetFocus(*m_pWindow);
   }
   CControlUI::Event(event);
}

void CMultiLineEditUI::DoPaint(HDC hDC, const RECT& /*rcPaint*/)
{
   UINT uState = 0;
   if( IsFocused() ) uState |= UISTATE_FOCUSED;
   if( IsReadOnly() ) uState |= UISTATE_READONLY;
   if( !IsEnabled() ) uState |= UISTATE_DISABLED;
   CBlueRenderEngineUI::DoPaintEditBox(hDC, m_pManager, m_rcItem, _T(""), uState, 0, true);
}

