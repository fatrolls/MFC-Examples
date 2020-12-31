// ToolBarCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ToolBarCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbarCtrlEx

CToolBarCtrlEx::~CToolBarCtrlEx()
{
  DestroyWindow();
}


BEGIN_MESSAGE_MAP(CToolBarCtrlEx, CToolBarCtrl)
  //{{AFX_MSG_MAP(CToolBarCtrlEx)
  ON_WM_CREATE()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarCtrlEx message handlers

CToolBarCtrlEx::CToolBarCtrlEx()
{
  // initialize common controls
  INITCOMMONCONTROLSEX icex;
  icex.dwSize = sizeof(icex);
  icex.dwICC = ICC_BAR_CLASSES;
  VERIFY(InitCommonControlsEx(&icex));
}

BOOL CToolBarCtrlEx::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
                            UINT nID)
{
  CWnd* pWnd = this;
  BOOL bCreated = pWnd->Create(TOOLBARCLASSNAME, NULL, dwStyle, rect, pParentWnd, nID);

  return bCreated;
}

int CToolBarCtrlEx::OnCreate(LPCREATESTRUCT lpcs)
{
  if (CWnd::OnCreate(lpcs) == -1)
    return -1;
  SetButtonStructSize(sizeof(TBBUTTON));
  return 0;
}

HRESULT CToolBarCtrlEx::GetDropTarget(IDropTarget** ppDropTarget) const
{
  ASSERT(::IsWindow(m_hWnd));
  ASSERT(ppDropTarget);
  return (HRESULT) ::SendMessage(m_hWnd, TB_GETOBJECT, (WPARAM)&IID_IDropTarget, (LPARAM)ppDropTarget);
}
