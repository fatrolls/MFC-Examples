// msdifrm.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSDIFrame

IMPLEMENT_DYNCREATE(CMSDIFrame, CMDIChildWnd)

CMSDIFrame::CMSDIFrame()
{
}

CMSDIFrame::~CMSDIFrame()
{
}

BEGIN_MESSAGE_MAP(CMSDIFrame, CMDIChildWnd)
  //{{AFX_MSG_MAP(CMSDIFrame)
  ON_WM_SYSCOMMAND()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMSDIFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
  switch (nID & 0xFFF0)
  {
    case SC_CLOSE:
    {
      CMSDIWinApp* pApp = (CMSDIWinApp*)AfxGetApp();
      pApp->CloseDocument();
      break;
    }
    default:
      CFrameWnd::OnSysCommand(nID, lParam);
  }
} 

/////////////////////////////////////////////////////////////////////////////
// CMSDIFrame message handlers
