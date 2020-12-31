// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FlatBar.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_VIEW_FLATBAR, OnUpdateViewFlatbar)
	ON_COMMAND(ID_VIEW_FLATBAR, OnViewFlatbar)
	ON_UPDATE_COMMAND_UI(ID_ToggleCase, OnUpdateToggleCase)
	ON_COMMAND(ID_ToggleCase, OnToggleCase)
	//}}AFX_MSG_MAP

	// required handlers for adjusting toolbar-buttons
	ON_NOTIFY(TBN_QUERYDELETE, AFX_IDW_TOOLBAR, OnQueryDelete)
    ON_NOTIFY(TBN_QUERYINSERT, AFX_IDW_TOOLBAR, OnQueryInsert)
	ON_NOTIFY(TBN_QUERYDELETE, AFX_IDW_TOOLBAR+5, OnQueryDelete)
    ON_NOTIFY(TBN_QUERYINSERT, AFX_IDW_TOOLBAR+5, OnQueryInsert)

#if _MFC_VER >= 0x0420
	ON_NOTIFY( NM_CUSTOMDRAW, AFX_IDW_TOOLBAR, OnCustomToolbarDraw )
	ON_NOTIFY( NM_CUSTOMDRAW, AFX_IDW_TOOLBAR+5, OnCustomToolbarDraw )
#endif

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: m_bCaseCheck(FALSE)
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndTextBar.Create(this,WS_CHILD | WS_VISIBLE | CBRS_TOP,AFX_IDW_TOOLBAR+5) ||
		!m_wndTextBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndTextBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// Let the user adjust the buttons by Shift-LeftClick.
	// This requires to install handlers for TBN_QUERYDELETE
	// and TBN_QUERYINSERT notifications (see above and below).
	m_wndToolBar.GetToolBarCtrl().ModifyStyle(0,CCS_ADJUSTABLE,0);
	m_wndTextBar.GetToolBarCtrl().ModifyStyle(0,CCS_ADJUSTABLE,0);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndTextBar.EnableDocking(CBRS_ALIGN_ANY);

	m_wndTextBar.SetSizes(CSize(42,40), CSize(16,15));
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_FILE_NEW), "New");
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_FILE_OPEN), "Open");
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_FILE_SAVE), "Save");
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_EDIT_CUT), "Cut");
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_EDIT_COPY), "Copy");
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_EDIT_PASTE), "Paste");
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_ToggleCase), "Case");
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_FILE_PRINT), "Print");
	m_wndTextBar.SetButtonText(m_wndTextBar.CommandToIndex(ID_APP_ABOUT), "About");

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndTextBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
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

void CMainFrame::OnUpdateViewFlatbar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndToolBar.IsFlatLook());
}


void CMainFrame::OnViewFlatbar() 
{
	m_wndToolBar.SetFlatLook(!m_wndToolBar.IsFlatLook());
	m_wndTextBar.SetFlatLook(!m_wndTextBar.IsFlatLook());
}


void CMainFrame::OnQueryDelete(NMHDR*, LRESULT* pResult) {
  *pResult = TRUE;		// allow deletion of a button
}


void CMainFrame::OnQueryInsert(NMHDR*, LRESULT* pResult) {
  *pResult = TRUE;		// allow insertion of a button
}


#if _MFC_VER >= 0x0420

// custom draw of a toolbar is available since VC++ 4.2

void CMainFrame :: OnCustomToolbarDraw( NMHDR * pNotify, LRESULT * pResult ) {
	LPNMCUSTOMDRAW pCDRW = (LPNMCUSTOMDRAW) pNotify;

	*pResult = CDRF_DODEFAULT;

	CToolBarEx * pBar = (pNotify->idFrom == AFX_IDW_TOOLBAR) ?
						&m_wndToolBar : &m_wndTextBar;

	switch( pCDRW->dwDrawStage ) {
		case CDDS_PREPAINT:
			TRACE0("receiving PREPAINT\n");
			*pResult = CDRF_NOTIFYPOSTPAINT | CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			TRACE1("receiving ITEMPREPAINT for index %d\n",pBar->CommandToIndex(pCDRW->dwItemSpec));
			if( pBar->IsFlatLook() ) {
				// if the cursor is on this button, then draw it with blue
				// text instead of black:
				CRect rect;
				pBar->GetItemRect(pBar->CommandToIndex(pCDRW->dwItemSpec), rect);
				CPoint pt;
				::GetCursorPos(&pt);
				pBar->ScreenToClient(&pt);
				if( rect.PtInRect(pt) )
					::SetTextColor(pCDRW->hdc, RGB(0,0,255));
			}

			*pResult = CDRF_NOTIFYPOSTPAINT;	// request for ITEMPOSTPAINT
			break;

		case CDDS_ITEMPOSTPAINT:
			TRACE1("receiving ITEMPOSTPAINT for index %d\n",pBar->CommandToIndex(pCDRW->dwItemSpec));
			break;

		case CDDS_POSTPAINT:
			TRACE0("receiving POSTPAINT\n");
			break;

		default:
			// CToolBar does not send other draw-stages than the above.
			TRACE0("unknown draw stage ...\n");
			break;
	}
}
#endif	// _MFC_VER >= 0x0420

void CMainFrame::OnUpdateToggleCase(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bCaseCheck);
}

void CMainFrame::OnToggleCase() 
{
	m_bCaseCheck = ! m_bCaseCheck;
}
