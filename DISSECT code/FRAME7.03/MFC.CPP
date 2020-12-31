#include "my.h"  // it should be mfc.h, but for CMyWinApp definition, so...

extern CMyWinApp theApp;

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

CWinApp* AfxGetApp()
{
  return theApp.m_pCurrentWinApp;
}

AFX_MSGMAP* CCmdTarget::GetMessageMap() const  // JJHOU: in MFC 40 cmdtarg.cpp
{
        return &CCmdTarget::messageMap;
}

AFX_MSGMAP CCmdTarget::messageMap =   // JJHOU: in MFC 40 cmdtarg.cpp
{
        NULL,
        &CCmdTarget::_messageEntries[0]
};

AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[] = // JJHOU: in in MFC 40 cmdtarg.cpp
{
     // { 0, 0, 0, 0, AfxSig_end, 0 }     // nothing here
        { 0, 0, CCmdTargetid, 0, AfxSig_end, 0 }

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
