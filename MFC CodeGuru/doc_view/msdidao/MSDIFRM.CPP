// msdifrm.cpp : implementation file
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"
#include "MSDIFrm.h"

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

BOOL CMSDIFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= WS_MINIMIZE;  // MSDIDAO: minimize the database view

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIFrame diagnostics

#ifdef _DEBUG
void CMSDIFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CMSDIFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSDIFrame message handlers

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
