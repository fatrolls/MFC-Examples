#include "my.h"  // 原該含入 mfc.h 就好，但為了 extern CMyWinApp 所以...

extern CMyWinApp theApp;
extern void printlpEntries(AFX_MSGMAP_ENTRY* lpEntry);

BOOL CCmdTarget::OnCmdMsg(UINT nID, int nCode)
{
    cout << "CCmdTarget::OnCmdMsg()" << endl;
    // Now look through message map to see if it applies to us
    AFX_MSGMAP* pMessageMap;
    AFX_MSGMAP_ENTRY* lpEntry;
    for (pMessageMap = GetMessageMap(); pMessageMap != NULL;
         pMessageMap = pMessageMap->pBaseMessageMap)
    {
            lpEntry = pMessageMap->lpEntries;
            printlpEntries(lpEntry);
    }

    return FALSE;   // not handled
}

BOOL CWnd::Create()
{
    cout << "CWnd::Create \n";
    return TRUE;
}

BOOL CWnd::CreateEx()
{
    cout << "CWnd::CreateEx \n";
    PreCreateWindow();
    return TRUE;
}

BOOL CWnd::PreCreateWindow()
{
  cout << "CWnd::PreCreateWindow \n";
  return TRUE;
}

LRESULT CWnd::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    AFX_MSGMAP* pMessageMap;
    AFX_MSGMAP_ENTRY* lpEntry;

    cout << "CWnd::WindowProc()" << endl;
    if (nMsg == WM_COMMAND) // special case for commands
    {
        if (OnCommand(wParam, lParam))
            return 1L; // command handled
        else
            return (LRESULT)DefWindowProc(nMsg, wParam, lParam);
    }

    pMessageMap = GetMessageMap();

    for (; pMessageMap != NULL;
         pMessageMap = pMessageMap->pBaseMessageMap)
    {
            lpEntry = pMessageMap->lpEntries;
            printlpEntries(lpEntry);
    }
    return 0;  // J.J.Hou: if find, should call lpEntry->pfn,
               // otherwise should call DefWindowProc.
               // for simplization， we just return 0.
}

LRESULT CWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    cout << "CWnd::DefWindowProc()" << endl;
    return TRUE;
}

BOOL CWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
    cout << "CWnd::OnCommand()" << endl;
    // ...
    return OnCmdMsg(0, 0);
}

BOOL CFrameWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
    cout << "CFrameWnd::OnCommand()" << endl;
    // ...
    // route as normal command
    return CWnd::OnCommand(wParam, lParam);
}

BOOL CFrameWnd::Create()
{
    cout << "CFrameWnd::Create \n";
    CreateEx();
    return TRUE;
}

BOOL CFrameWnd::PreCreateWindow()
{
    cout << "CFrameWnd::PreCreateWindow \n";
    return TRUE;
}

CView* CFrameWnd::GetActiveView() const
{
    cout << "CFrameWnd::GetActiveView()" << endl;
    return m_pViewActive;
}

BOOL CFrameWnd::OnCmdMsg(UINT nID, int nCode)
{
    cout << "CFrameWnd::OnCmdMsg()" << endl;
    // pump through current view FIRST
    CView* pView = GetActiveView();
    if (pView->OnCmdMsg(nID, nCode))
            return TRUE;

    // then pump through frame
    if (CWnd::OnCmdMsg(nID, nCode))
            return TRUE;

    // last but not least, pump through app
    CWinApp* pApp = AfxGetApp();
    if (pApp->OnCmdMsg(nID, nCode))
            return TRUE;

    return FALSE;
}

BOOL CDocument::OnCmdMsg(UINT nID, int nCode)
{
    cout << "CDocument::OnCmdMsg()" << endl;
    if (CCmdTarget::OnCmdMsg(nID, nCode))
        return TRUE;

    return FALSE;
}

BOOL CView::OnCmdMsg(UINT nID, int nCode)
{
    cout << "CView::OnCmdMsg()" << endl;
    if (CWnd::OnCmdMsg(nID, nCode))
        return TRUE;

    BOOL bHandled = FALSE;
    bHandled = m_pDocument->OnCmdMsg(nID, nCode);
    return bHandled;
}

AFX_MSGMAP* CCmdTarget::GetMessageMap() const  // JJHou: in MFC 40 cmdtarg.cpp
{
    return &CCmdTarget::messageMap;
}

AFX_MSGMAP CCmdTarget::messageMap =   // JJHou: in in MFC 40 cmdtarg.cpp
{
    NULL,
    &CCmdTarget::_messageEntries[0]
};

AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[] = // JJHou: in in MFC 40 cmdtarg.cpp
{
    { 0, 0, CCmdTargetid, 0, AfxSig_end, 0 }  // nothing here
};

BEGIN_MESSAGE_MAP(CWnd, CCmdTarget)
ON_COMMAND(CWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CFrameWnd, CWnd)
ON_COMMAND(CFrameWndid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDocument, CCmdTarget)
ON_COMMAND(CDocumentid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CView, CWnd)
ON_COMMAND(CViewid, 0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CWinApp, CCmdTarget)
ON_COMMAND(CWinAppid, 0)
END_MESSAGE_MAP()

CWinApp* AfxGetApp()
{
  return theApp.m_pCurrentWinApp;
}

LRESULT AfxWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam,
                   CWnd *pWnd)  // last param. pWnd is added by JJHou.
{
  cout << "AfxWndProc()" << endl;
  return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);
}

LRESULT AfxCallWndProc(CWnd* pWnd, HWND hWnd, UINT nMsg,
                       WPARAM wParam, LPARAM lParam)
{
  cout << "AfxCallWndProc()" << endl;
  LRESULT lResult = pWnd->WindowProc(nMsg, wParam, lParam);
  return lResult;
}
