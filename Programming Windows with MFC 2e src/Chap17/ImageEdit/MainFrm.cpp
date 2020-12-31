// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ImageEdit.h"
#include "ImageEditDoc.h"
#include "SpecialStatusBar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_USER_UPDATE_STATS, OnUpdateImageStats)
	ON_MESSAGE (WM_USER_THREAD_UPDATE, OnThreadUpdate)
	ON_MESSAGE (WM_USER_THREAD_FINISHED, OnThreadFinished)
	ON_MESSAGE (WM_USER_THREAD_ABORTED, OnThreadAborted)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nPercentDone = -1;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
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

BOOL CMainFrame::OnQueryNewPalette() 
{
    CDocument* pDoc = GetActiveDocument ();
    if (pDoc != NULL)
        GetActiveDocument ()->UpdateAllViews (NULL);
    return TRUE;
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
    if (pFocusWnd != this) {
        CDocument* pDoc = GetActiveDocument ();
        if (pDoc != NULL)
            GetActiveDocument ()->UpdateAllViews (NULL);
    }
}

LRESULT CMainFrame::OnUpdateImageStats (WPARAM wParam, LPARAM lParam)
{
    m_wndStatusBar.SetImageStats ((LPCTSTR) lParam);
	return 0;
}

LRESULT CMainFrame::OnThreadUpdate (WPARAM wParam, LPARAM lParam)
{
    int nPercentDone = ((int) wParam * 100) / (int) lParam;
    if (nPercentDone != m_nPercentDone) {
        m_wndStatusBar.SetProgress (nPercentDone);
        m_nPercentDone = nPercentDone;
    }
    return 0;
}

LRESULT CMainFrame::OnThreadFinished (WPARAM wParam, LPARAM lParam)
{
    CImageEditDoc* pDoc = (CImageEditDoc*) GetActiveDocument ();
    if (pDoc != NULL) {
	    pDoc->ThreadFinished ();
        m_wndStatusBar.SetProgress (0);
		m_nPercentDone = -1;
	}
    return 0;
}

LRESULT CMainFrame::OnThreadAborted (WPARAM wParam, LPARAM lParam)
{
    CImageEditDoc* pDoc = (CImageEditDoc*) GetActiveDocument ();
    if (pDoc != NULL) {
	    pDoc->ThreadAborted ();
        m_wndStatusBar.SetProgress (0);
		m_nPercentDone = -1;
	}
    return 0;
}
