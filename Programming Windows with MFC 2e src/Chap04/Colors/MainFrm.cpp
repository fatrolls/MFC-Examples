// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Colors.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_WM_MEASUREITEM ()
	ON_WM_DRAWITEM ()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
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
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	return 0;
}

void CMainFrame::OnMeasureItem (int nIDCtl, LPMEASUREITEMSTRUCT lpmis)
{
    lpmis->itemWidth = ::GetSystemMetrics (SM_CYMENU) * 4;
    lpmis->itemHeight = ::GetSystemMetrics (SM_CYMENU);
}

void CMainFrame::OnDrawItem (int nIDCtl, LPDRAWITEMSTRUCT lpdis)
{
    BITMAP bm;
    CBitmap bitmap;
    bitmap.LoadOEMBitmap (OBM_CHECK);
    bitmap.GetObject (sizeof (bm), &bm);

    CDC dc;
    dc.Attach (lpdis->hDC);

    CBrush* pBrush = new CBrush (::GetSysColor ((lpdis->itemState &
        ODS_SELECTED) ? COLOR_HIGHLIGHT : COLOR_MENU));
    dc.FrameRect (&(lpdis->rcItem), pBrush);
    delete pBrush;

    if (lpdis->itemState & ODS_CHECKED) {
        CDC dcMem;
        dcMem.CreateCompatibleDC (&dc);
        CBitmap* pOldBitmap = dcMem.SelectObject (&bitmap);

        dc.BitBlt (lpdis->rcItem.left + 4, lpdis->rcItem.top +
            (((lpdis->rcItem.bottom - lpdis->rcItem.top) -
            bm.bmHeight) / 2), bm.bmWidth, bm.bmHeight, &dcMem,
            0, 0, SRCCOPY);

        dcMem.SelectObject (pOldBitmap);
    }

	UINT itemID = lpdis->itemID & 0xFFFF; // Fix for Win95/98 bug
    pBrush = new CBrush (m_wndView.m_clrColors[itemID - ID_COLOR_RED]);
    CRect rect = lpdis->rcItem;
    rect.DeflateRect (6, 4);
    rect.left += bm.bmWidth;
    dc.FillRect (rect, pBrush);
    delete pBrush;

    dc.Detach ();
}
