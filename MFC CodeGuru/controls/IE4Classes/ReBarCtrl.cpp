#include "stdafx.h"
#include "ReBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReBarCtrlEx

CReBarCtrl::CReBarCtrl()
{
  // initialize common controls
  INITCOMMONCONTROLSEX icex;
  icex.dwSize = sizeof(icex);
  icex.dwICC = ICC_COOL_CLASSES;
  VERIFY(InitCommonControlsEx(&icex));
}

BOOL CReBarCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
                        UINT nID)
{
  CWnd* pWnd = this;
  return pWnd->Create(REBARCLASSNAME, NULL, dwStyle, rect, pParentWnd, nID);
}

CImageList* CReBarCtrl::GetImageList() const
{
  REBARINFO rbi;
  rbi.cbSize = sizeof(rbi);
  rbi.fMask = RBIM_IMAGELIST;
  return GetBarInfo(&rbi) ? CImageList::FromHandle(rbi.himl) : NULL;
}

BOOL CReBarCtrl::SetImageList(CImageList* pImageList)
{
  REBARINFO rbi;
  rbi.cbSize = sizeof(rbi);
  rbi.fMask = RBIM_IMAGELIST;
  rbi.himl = (HIMAGELIST)pImageList->GetSafeHandle();
  return SetBarInfo(&rbi);
}

BOOL CReBarCtrl::GetColorScheme(COLORSCHEME* lpcs)
{
  lpcs->dwSize = sizeof(COLORSCHEME);
  return SendMessage(RB_GETCOLORSCHEME, 0, (LPARAM)lpcs);
}

void CReBarCtrl::SetColorScheme(const COLORSCHEME* lpcs)
{
  ((COLORSCHEME*)lpcs)->dwSize = sizeof(COLORSCHEME);
  SendMessage(RB_SETCOLORSCHEME, 0, (LPARAM)lpcs);
}

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CReBarCtrl, CWnd)

/////////////////////////////////////////////////////////////////////////////
