// TblFrame.cpp : implementation file
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoSet.h"
#include "DaoDoc.h"

#include "MSDIvFrm.h"
#include "TblFrame.h"
#include "TblView.h"

#include <afxpriv.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoTableFrame

IMPLEMENT_DYNCREATE(CDaoTableFrame, CMSDIViewFrame)

CDaoTableFrame::CDaoTableFrame()
{
}

CDaoTableFrame::~CDaoTableFrame()
{
}

BEGIN_MESSAGE_MAP(CDaoTableFrame, CMSDIViewFrame)
	//{{AFX_MSG_MAP(CDaoTableFrame)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDaoTableFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CMSDIViewFrame::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIFrame diagnostics

#ifdef _DEBUG
void CDaoTableFrame::AssertValid() const
{
	CMSDIViewFrame::AssertValid();
}

void CDaoTableFrame::Dump(CDumpContext& dc) const
{
	CMSDIViewFrame::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDaoTableFrame message handlers

// this function is to notify the view with the HeaderCtrl messages
// the HeaderCtrl messages notifications are send to the frame

BOOL CDaoTableFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
  CView* pView = GetActiveView();
  if (pView)
  {
    ASSERT(pView->IsKindOf(RUNTIME_CLASS(CDaoTableView)));

    // reflect the message through the message map as OCM_NOTIFY
    NMHDR* pNMHDR = (NMHDR*)lParam;
    int nCode = pNMHDR->code;
    AFX_NOTIFY notify;
    notify.pResult = pResult;
    notify.pNMHDR = pNMHDR;
    return ((CWnd*)pView)->OnCmdMsg(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, NULL);
  }
  return CMSDIViewFrame::OnNotify(wParam, lParam, pResult);
}
