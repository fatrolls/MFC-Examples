// MSDIvFrm.cpp : implementation file
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "MSDIvFrm.h"
#include <afxpriv.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSDIFrame

IMPLEMENT_DYNCREATE(CMSDIViewFrame, CMDIChildWnd)

CMSDIViewFrame::CMSDIViewFrame()
{
}

CMSDIViewFrame::~CMSDIViewFrame()
{
}

BEGIN_MESSAGE_MAP(CMSDIViewFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMSDIViewFrame)
        ON_WM_CREATE()
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMSDIViewFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// By turning off the default MFC-defined FWS_ADDTOTITLE style,
	// the framework will use first string in the document template
	// STRINGTABLE resource instead of the document name.
	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIViewFrame diagnostics

#ifdef _DEBUG
void CMSDIViewFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CMSDIViewFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSDIViewFrame message handlers

int CMSDIViewFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  // if not exist, get shared menu & accelerator table from first doc template
  if (!m_hMenuShared || !m_hAccelTable)
  {
    CMSDIWinApp* pApp = (CMSDIWinApp*)AfxGetApp();
    POSITION pos = pApp->GetFirstDocTemplatePosition();
    CMSDITemplate* pTemplate =
      (CMSDITemplate*)pApp->GetNextDocTemplate(pos);
    if (pTemplate)
    {
      if (!m_hMenuShared)
	m_hMenuShared = pTemplate->m_hMenuShared;
      if (!m_hAccelTable)
	m_hAccelTable = pTemplate->m_hAccelTable;
    }
  }
  return 0;
}

void CMSDIViewFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
  // update our parent window first
  GetMDIFrame()->OnUpdateFrameTitle(bAddToTitle);

  if (bAddToTitle)
  {
    char szBuffer[256];
    char szOldTitle[256];
    GetWindowText(szOldTitle, sizeof(szOldTitle));

    CString strTitle;
    CMSDIWinApp* pApp = (CMSDIWinApp*)AfxGetApp();
    CMSDITemplate* pTemplate = pApp->GetDocTemplate(GetActiveView());
    pTemplate->GetDocString(strTitle, CDocTemplate::windowTitle);
    if (m_nWindow > 0)
      wsprintf(szBuffer, "%s:%d", (LPCSTR)strTitle, m_nWindow);
    else
      strcpy(szBuffer, strTitle);

    // set title if changed, but don't remove completely
    if (lstrcmp(szBuffer, szOldTitle) != 0)
      SetWindowText(szBuffer);
  }
}

LRESULT CMSDIViewFrame::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
{
  CMDIChildWnd::OnIdleUpdateCmdUI();	// pass to default handler
  OnUpdateFrameTitle(TRUE);
  return 0L;
}
