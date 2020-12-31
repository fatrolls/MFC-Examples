// DIBView.cpp : implementation file
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DIBApi.h"
#include "DIBView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBView

IMPLEMENT_DYNCREATE(CDIBView, CView)

CDIBView::CDIBView()
{
  m_hDIB = NULL;
  m_palDIB = NULL;
}

CDIBView::~CDIBView()
{
  if (m_hDIB != NULL)
  {
    ::GlobalFree((HGLOBAL)m_hDIB);
  }
  if (m_palDIB != NULL)
  {
    delete m_palDIB;
  }
}

BEGIN_MESSAGE_MAP(CDIBView, CView)
  //{{AFX_MSG_MAP(CDIBView)
  ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
  ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
  ON_MESSAGE(WM_DOREALIZE, OnDoRealize)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIBView drawing

void CDIBView::OnDraw(CDC* pDC)
{
  if (m_hDIB != NULL)
  {
    LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);
    int cxDIB = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
    int cyDIB = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
    ::GlobalUnlock((HGLOBAL)m_hDIB);
    CRect rcDIB;
    rcDIB.top = rcDIB.left = 0;
    rcDIB.right = cxDIB;
    rcDIB.bottom = cyDIB;
    CRect rcDest;
    if (pDC->IsPrinting())   // printer DC
    {
      // get size of printer page (in pixels)
      int cxPage = pDC->GetDeviceCaps(HORZRES);
      int cyPage = pDC->GetDeviceCaps(VERTRES);
      // get printer pixels per inch
      int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
      int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);
      
      // Best Fit case -- create a rectangle which preserves
      // the DIB's aspect ratio, and fills the page horizontally.
      //
      // The formula in the "->bottom" field below calculates the Y
      // position of the printed bitmap, based on the size of the
      // bitmap, the width of the page, and the relative size of
      // a printed pixel (cyInch / cxInch).
      //
      rcDest.top = rcDest.left = 0;
      rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch) / ((double)cxDIB * cxInch));
      rcDest.right = cxPage;
    }
    else   // not printer DC
    {
      rcDest = rcDIB;
    }
    ::PaintDIB(pDC->m_hDC, &rcDest, m_hDIB, &rcDIB, m_palDIB);
  }
}

LRESULT CDIBView::OnDoRealize(WPARAM wParam, LPARAM)
{
  ASSERT(wParam != NULL);

  if (m_hDIB == NULL) return 0L;

  CPalette* pPal = m_palDIB;
  if (pPal != NULL)
  {
    CMainFrame* pAppFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
    ASSERT_KINDOF(CMainFrame, pAppFrame);

    CClientDC appDC(pAppFrame);
    // All views but one should be a background palette.
    // wParam contains a handle to the active view, so the SelectPalette
    // bForceBackground flag is FALSE only if wParam == m_hWnd (this view)
    CPalette* oldPalette = appDC.SelectPalette(pPal, ((HWND)wParam) != m_hWnd);

    if (oldPalette != NULL)
    {
      UINT nColorsChanged = appDC.RealizePalette();
      appDC.SelectPalette(oldPalette, TRUE);
    }
    else
    {
      TRACE0("\tSelectPalette failed in CDibView::OnPaletteChanged\n");
    }
  }
  return 0L;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBView diagnostics

#ifdef _DEBUG
void CDIBView::AssertValid() const
{
	CView::AssertValid();
}

void CDIBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIBView message handlers

void CDIBView::ReplaceHDIB(HDIB hNewDIB)
{
  if (m_hDIB != NULL)
  {
    ::GlobalFree((HGLOBAL) m_hDIB);
  }
  m_hDIB = hNewDIB;
}

void CDIBView::InitDIBData()
{
  if (m_palDIB != NULL)
  {
    delete m_palDIB;
    m_palDIB = NULL;
  }
  if (m_hDIB == NULL)
  {
    return;
  }
  // Set up document size
  LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);
  if (::DIBWidth(lpDIB) > INT_MAX ||::DIBHeight(lpDIB) > INT_MAX)
  {
    ::GlobalUnlock((HGLOBAL)m_hDIB);
    ::GlobalFree((HGLOBAL)m_hDIB);
    m_hDIB = NULL;
    AfxMessageBox("DIB is too large");
    return;
  }
  m_sizeDoc = CSize((int)::DIBWidth(lpDIB), (int)::DIBHeight(lpDIB));
  ::GlobalUnlock((HGLOBAL)m_hDIB);

  // Create copy of palette
  m_palDIB = new CPalette;
  if (m_palDIB == NULL)
  {
    // we must be really low on memory
    ::GlobalFree((HGLOBAL)m_hDIB);
    m_hDIB = NULL;
    return;
  }
  if (::CreateDIBPalette(m_hDIB, m_palDIB) == NULL)
  {
    // DIB may not have a palette
    delete m_palDIB;
    m_palDIB = NULL;
    return;
  }
}

void CDIBView::OnEditPaste()
{
  HDIB hNewDIB = NULL;

  if (OpenClipboard())
  {
    BeginWaitCursor();

    hNewDIB = (HDIB)CopyHandle(::GetClipboardData(CF_DIB));
    CloseClipboard();

    if (hNewDIB != NULL)
    {
      ReplaceHDIB(hNewDIB);		// and free the old DIB
      InitDIBData();			// set up new size & palette
      OnDoRealize((WPARAM)m_hWnd, 0);	// realize the new palette
      Invalidate();
    }
    EndWaitCursor();
  }
}

void CDIBView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
  OpenClipboard();
  pCmdUI->Enable(EnumClipboardFormats(CF_DIB) != 0); 
  CloseClipboard();
}
