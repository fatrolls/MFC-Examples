// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Roll32.h"

#include "mainfrm.h"
#include "oxrollup.h"
#include "example.h"
#include "UTBStrOp.h"

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
	ON_COMMAND(ID_VIEW_ROLLUPTEST, OnRollupTest)
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
	ON_ROLLUP_NOTIFICATION()
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
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
	CExample* pExample = ((CRoll32App*)AfxGetApp())->GetExampleRollup();
//	if (pExample->GetSafeHwnd() != 0)
//		pExample->DestroyWindow();
	delete pExample;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// create the new dialog
	((CRoll32App *)AfxGetApp())->GetExampleRollup() = new CExample(this);
	return 0;
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

BOOL CMainFrame::OnRollupMessage(CWnd* pWndRollup,UINT message,UINT rollupID)
{
	UNREFERENCED_PARAMETER(rollupID);
	if (message == IDCANCEL)
		pWndRollup->DestroyWindow();	
    return TRUE;
}


void CMainFrame::OnRollupTest() 
{
	CExample* pExample = ((CRoll32App*)AfxGetApp())->GetExampleRollup();
	
	TCHAR szTitle[20];
	UTBStr::tcscpy(szTitle,20,_T("MFC 2.5/3.0/4.0"));
	
	pExample->CreateRollUp(this, 6458, szTitle);
	pExample->ShowWindow(SW_SHOWNORMAL);

	pExample->SendMessage(IDM_OX_RU_ARRANGE);

	GetActiveFrame()->SetFocus();
}

void CMainFrame::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CMDIFrameWnd::OnWindowPosChanged(lpwndpos);
	
	COXRollup::ReArrangeArranged();	
}
