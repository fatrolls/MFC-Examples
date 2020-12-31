// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "msdi.h"

#include "mainfrm.h"
#include "outview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
  //{{AFX_MSG_MAP(CMainFrame)
  ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_NEW, OnWindowNew)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, OnUpdateMDIWindowCmd)
  ON_COMMAND(ID_OUTPUT_TEXT, OnOutputText)
  ON_COMMAND(ID_OUTPUT_ERASE, OnOutputErase)
  ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
  ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
  // same order as in the bitmap 'toolbar.bmp'
  ID_FILE_NEW,
  ID_FILE_OPEN,
  ID_FILE_SAVE,
    ID_SEPARATOR,
  ID_EDIT_CUT,
  ID_EDIT_COPY,
  ID_EDIT_PASTE,
    ID_SEPARATOR,
  ID_FILE_PRINT,
  ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
  ID_SEPARATOR,     // status line indicator
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
  m_pOutView = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  if (!m_wndToolBar.Create(this) ||
    !m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
    !m_wndToolBar.SetButtons(buttons,
      sizeof(buttons)/sizeof(UINT)))
  {
    TRACE("Failed to create toolbar\n");
    return -1;      // fail to create
  }

  if (!m_wndStatusBar.Create(this) ||
    !m_wndStatusBar.SetIndicators(indicators,
      sizeof(indicators)/sizeof(UINT)))
  {
    TRACE("Failed to create status bar\n");
    return -1;      // fail to create
  }

  return 0;
}

void CMainFrame::OnDestroyView(CView* pView)
{
  // can handle multiple views if necessary
  if (pView->IsKindOf(RUNTIME_CLASS(COutView))) m_pOutView = NULL;
}

void CMainFrame::OnWindowNew()
{
	CMDIChildWnd* pActiveChild = MDIGetActive();
	CDocument* pDocument;
	if (pActiveChild == NULL ||
	  (pDocument = pActiveChild->GetActiveDocument()) == NULL)
	{
	  // the parent class do all user notifications
		CMDIFrameWnd::OnWindowNew();
  	return;   // command failed
	}

	// otherwise we have a new frame for the active view
	// a new frame is created only for view with document
	// for other view, make the necessary change here
  CMSDIWinApp* pApp = (CMSDIWinApp*)AfxGetApp();
	CView* pView = pActiveChild->GetActiveView();
	ASSERT(pView != NULL);
	
  CMSDITemplate* pTemplate = pApp->GetDocTemplate(pActiveChild->GetActiveView());
  if (pTemplate == NULL)
  {
		TRACE0("Warning: No valid view for WindowNew command\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
  	return;   // command failed
  }
	CFrameWnd* pFrame = pTemplate->CreateNewFrame(pDocument, pActiveChild);
	if (pFrame == NULL)
	{
		TRACE0("Warning: failed to create new frame\n");
		return;     // command failed
	}
	pTemplate->InitialUpdateFrame(pFrame, pDocument);
}

BOOL CMainFrame::OnMDIWindowCmd(UINT nID)
{
  return CMDIFrameWnd::OnMDIWindowCmd(nID);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
  CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
  CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewOutput()
{
  // create the output view
  CMDIChildWnd* pOutFrame;
  CMSDIWinApp* pApp = (CMSDIWinApp*)AfxGetApp();
  pOutFrame = pApp->CreateOrActivateFrame(RUNTIME_CLASS(COutView), NULL);
  m_pOutView = (COutView*)pOutFrame->GetActiveView();
  ASSERT(m_pOutView != NULL);
  ASSERT(m_pOutView->IsKindOf(RUNTIME_CLASS(COutView)));
}

void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(m_pOutView == NULL);
}

void CMainFrame::OnOutputText()
{
  ASSERT(m_pOutView != NULL); // the command exist only if an output view exist
  m_pOutView->WriteTTY("This view is not attached to a document.\r\n");
}

void CMainFrame::OnOutputErase()
{
  ASSERT(m_pOutView != NULL); // the command exist only if an output view exist
  m_pOutView->ClearTTY();
}
