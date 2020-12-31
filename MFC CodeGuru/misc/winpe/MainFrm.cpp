// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include <AFXPRIV.H>

#include "winpe.h"

#include "MainFrm.h"
#include "winpedoc.h"
#include "dumpxview.h"
#include "ImportView.h"
#include "headerview.h"
#include "sectiontblview.h"
#include "debugdirview.h"
#include "resourcesview.h"
#include "exportview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_MESSAGE(WM_RESET_FRAMEVIEW,OnFrameView) 
	ON_COMMAND_RANGE(ID_VIEWS_IMPORTS,ID_VIEWS_RESOURCES,OnViewChange)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FONTS_PRINTER, OnFontsPrinter)
	ON_COMMAND(ID_FONTS_DISPLAY, OnFontsDisplay)
	//}}AFX_MSG_MAP
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
{
	// TODO: add member initialization code here
	m_pImportView = NULL;
	m_nCurrentView = 0;
	
}

CMainFrame::~CMainFrame()
{
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
LRESULT CMainFrame::OnFrameView(WPARAM wParam,LPARAM lParam) 
{
	OnViewChange((UINT)wParam);
	return 0;
}


void CMainFrame::OnViewChange(UINT nCmdID) 
{


	if (nCmdID == m_nCurrentView)
		return; // its showing!

	
	// Set the child window ID of the active view to AFX_IDW_PANE_FIRST.
	// This is necessary so that CFrameWnd::RecalcLayout will allocate
	// this "first pane" to that portion of the frame window's client
	// area not allocated to control bars.  Set the child ID of
	// the previously active view to some other ID; we will use the
	// command ID as the child ID.
	CView* pOldActiveView = GetActiveView();
		::SetWindowLong(pOldActiveView->m_hWnd,
						GWL_ID,
						m_nCurrentView);

	CRuntimeClass* pNewViewClass;
	switch (nCmdID)
	{
		
		case ID_VIEWS_IMPORTS:
			pNewViewClass = RUNTIME_CLASS(CImportView);
			
			break;
        case ID_VIEWS_DUMP:
			pNewViewClass = RUNTIME_CLASS(CDumpXView);
			
			break;
		case ID_VIEWS_HEADERS:
			pNewViewClass = RUNTIME_CLASS(CHeaderView);
		
			break;
		case ID_VIEWS_SECTNTBL:
			pNewViewClass = RUNTIME_CLASS(CSectionTblView);
			
			break;
		case ID_VIEWS_DEBUGDIR:
			pNewViewClass = RUNTIME_CLASS(CDebugDirView);
		
			break;	
		case ID_VIEWS_RESOURCES:
			pNewViewClass = RUNTIME_CLASS(CResourceSView);
			
			break;	
		case ID_VIEWS_EXPORTS:
			pNewViewClass = RUNTIME_CLASS(CExportView);
			
			break;	
		default:
			ASSERT(0);
			return;
	}

	// create the new view
	CCreateContext context;
	context.m_pNewViewClass = pNewViewClass;
	context.m_pCurrentDoc = GetActiveDocument();
	CView* pNewView = STATIC_DOWNCAST(CView, CreateView(&context));
	if (pNewView != NULL)
	{
		// the new view is there, but invisible and not active...
		pNewView->ShowWindow(SW_SHOW);
		pNewView->OnInitialUpdate();
		SetActiveView(pNewView);
		RecalcLayout();
		m_nCurrentView = nCmdID;

		// finally destroy the old view...
		pOldActiveView->DestroyWindow();
	}
	return;

	
}


void CMainFrame::OnFontsPrinter() 
{
	// TODO: Add your command handler code here
	LOGFONT mlf;
	CPrintDialog printDialog(FALSE);
	if (printDialog.DoModal() == IDCANCEL)
		return;

	

	CWinpeDoc* pDoc = (CWinpeDoc*)GetActiveDocument();

	pDoc->m_printerFont->GetLogFont(&mlf);

	CFontDialog my_fdlg(&mlf);
	if (my_fdlg.DoModal() == IDCANCEL)
		return;

	CClientDC dc (AfxGetMainWnd());
	pDoc->SetDocPrtFont(&mlf);

	//pOldFont = dc.SelectObject(&m_printerFont);
	return;



	
}

void CMainFrame::OnFontsDisplay() 
{
	// TODO: Add your command handler code here
	LOGFONT mlf;
	
	CWinpeDoc* pDoc = (CWinpeDoc*)GetActiveDocument();

	pDoc->m_screenFont->GetLogFont(&mlf);

	CFontDialog my_fdlg(&mlf);
	if (my_fdlg.DoModal() == IDCANCEL)
		return;

	CClientDC dc (AfxGetMainWnd());
	pDoc->SetDocScrnFont(&mlf);

	dc.SelectObject(pDoc->m_screenFont);
	pDoc->UpdateAllViews(FALSE);
	return;

}
