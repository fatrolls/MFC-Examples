// ex25bView.cpp : implementation of the CEx25bView class
//

#include "stdafx.h"
#include "ex25b.h"

#include "cdib.h"
#include "ex25bDoc.h"
#include "ex25bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// CEx25bView

IMPLEMENT_DYNCREATE(CEx25bView, CScrollView)

BEGIN_MESSAGE_MAP(CEx25bView, CScrollView)
    //{{AFX_MSG_MAP(CEx25bView)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_COMMAND(ID_EDIT_COPYTO, OnEditCopyto)
    ON_COMMAND(ID_EDIT_CUT, OnEditCut)
    ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
    ON_COMMAND(ID_EDIT_PASTEFROM, OnEditPastefrom)
    ON_WM_LBUTTONDOWN()
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPYTO, OnUpdateEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopy)
    ON_WM_SETCURSOR()
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// CEx25bView construction/destruction

CEx25bView::CEx25bView() : m_sizeTotal(800, 1050), // 8-by-10.5 inches
                                                   //  when printed
    m_rectTracker(50, 50, 250, 250),
    m_dragOffset(0, 0), 
	m_rectTrackerEnter(50, 50, 250, 250) 
{
}

CEx25bView::~CEx25bView()
{
}

BOOL CEx25bView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CScrollView::PreCreateWindow(cs);
}

//////////////////////////////////////////////////////////////////////
// CEx25bView drawing

void CEx25bView::OnDraw(CDC* pDC)
{
    CDib& dib = GetDocument()->m_dib;
    m_tracker.m_rect = m_rectTracker;
    pDC->LPtoDP(m_tracker.m_rect);    // tracker wants device coords
    m_tracker.Draw(pDC);
    dib.UsePalette(pDC);
    dib.Draw(pDC, m_rectTracker.TopLeft(), m_rectTracker.Size());
}

//////////////////////////////////////////////////////////////////////
// CEx25bView printing

BOOL CEx25bView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

void CEx25bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CEx25bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

//////////////////////////////////////////////////////////////////////
// CEx25bView diagnostics

#ifdef _DEBUG
void CEx25bView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CEx25bView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CEx25bDoc* CEx25bView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx25bDoc)));
    return (CEx25bDoc*)m_pDocument;
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////
// helper functions used for clipboard and drag-drop 
BOOL CEx25bView::DoPasteDib(COleDataObject* pDataObject)
{
    // update command UI should keep us out of here if not CF_DIB
    if (!pDataObject->IsDataAvailable(CF_DIB)) {
      TRACE("CF_DIB format is unavailable\n");
      return FALSE;
    }
    CEx25bDoc* pDoc = GetDocument();
    // seems to be MOVEABLE memory, so we must use GlobalLock!
    //  (hDib != lpDib) GetGlobalData copies the memory, so we can
    //  hang onto it until we delete the CDib
    HGLOBAL hDib = pDataObject->GetGlobalData(CF_DIB);
    ASSERT(hDib != NULL);
    LPVOID lpDib = ::GlobalLock(hDib);
    ASSERT(lpDib != NULL);
    pDoc->m_dib.AttachMemory(lpDib, TRUE, hDib);
    GetDocument()->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
    return TRUE;
}

COleDataSource* CEx25bView::SaveDib()
{
    CDib& dib = GetDocument()->m_dib;
    if (dib.GetSizeImage() > 0) {
      COleDataSource* pSource = new COleDataSource();
      int nHeaderSize =  dib.GetSizeHeader();
      int nImageSize = dib.GetSizeImage();
      HGLOBAL hHeader = ::GlobalAlloc(GMEM_SHARE,
          nHeaderSize + nImageSize);
      LPVOID pHeader = ::GlobalLock(hHeader);
      ASSERT(pHeader != NULL);
      LPVOID pImage = (LPBYTE) pHeader + nHeaderSize;
      memcpy(pHeader, dib.m_lpBMIH, nHeaderSize); 
      memcpy(pImage, dib.m_lpImage, nImageSize);
      // receiver is supposed to free the global memory 
      ::GlobalUnlock(hHeader);
      pSource->CacheGlobalData(CF_DIB, hHeader);
      return pSource;
    }
    return NULL;
}

void CEx25bView::MoveTrackRect(CPoint point)
{
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DrawFocusRect(m_rectTracker);
    dc.LPtoDP(m_rectTracker);
    CSize sizeTrack = m_rectTracker.Size();
    CPoint newTopleft = point - m_dragOffset;  // still device
    m_rectTracker = CRect(newTopleft, sizeTrack);
    m_tracker.m_rect = m_rectTracker;
    dc.DPtoLP(m_rectTracker);
    dc.DrawFocusRect(m_rectTracker);
}

//////////////////////////////////////////////////////////////////////
// drag-and-drop functions
DROPEFFECT CEx25bView::OnDragEnter(COleDataObject* pDataObject,
        DWORD dwKeyState, CPoint point)
{
    TRACE("Entering CEx25bView::OnDragEnter, point = (%d, %d)\n",
        point.x, point.y);

    m_rectTrackerEnter = m_rectTracker; // Save original coordinates
                                        //  for cursor leaving
                                        //  rectangle
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DrawFocusRect(m_rectTracker); // will be erased in OnDragOver
    return OnDragOver(pDataObject, dwKeyState, point);
}

DROPEFFECT CEx25bView::OnDragOver(COleDataObject* pDataObject,
        DWORD dwKeyState, CPoint point)
{
    if (!pDataObject->IsDataAvailable(CF_DIB)) {
        return DROPEFFECT_NONE;
    }
    MoveTrackRect(point);
    if((dwKeyState & MK_CONTROL) == MK_CONTROL) {
        return DROPEFFECT_COPY;
    }
    // Check for force move
    if ((dwKeyState & MK_ALT) == MK_ALT) {
        return DROPEFFECT_MOVE;
    }
    // default -- recommended action is move
    return DROPEFFECT_MOVE;
}

void CEx25bView::OnDragLeave()
{
    TRACE("Entering CEx25bView::OnDragLeave\n");
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.DrawFocusRect(m_rectTracker);
    m_rectTracker = m_rectTrackerEnter; // Forget it ever happened
}

BOOL CEx25bView::OnDrop(COleDataObject* pDataObject, 
    DROPEFFECT dropEffect, CPoint point)
{
    TRACE("Entering CEx25bView::OnDrop -- dropEffect = %d\n", dropEffect);
    BOOL bRet;
    CEx25bDoc* pDoc = GetDocument();
    MoveTrackRect(point);
    if(pDoc->m_bDragHere) {
        pDoc->m_bDragHere = FALSE;
        bRet = TRUE;
    }
    else {
        bRet = DoPasteDib(pDataObject);
    }
    return bRet;
}

//////////////////////////////////////////////////////////////////////
// CEx25bView message handlers

void CEx25bView::OnEditCopy() 
{
    COleDataSource* pSource = SaveDib();
    if(pSource) {
        pSource->SetClipboard(); // OLE deletes data source 
    }
}

void CEx25bView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
    // serves Copy, Cut, and Copy To
    CDib& dib = GetDocument()->m_dib;
    pCmdUI->Enable(dib.GetSizeImage() > 0L);
}

void CEx25bView::OnEditCopyto() 
{
    CDib& dib = GetDocument()->m_dib;
    CFileDialog dlg(FALSE, "bmp", "*.bmp");
    if(dlg.DoModal() != IDOK) return;

    BeginWaitCursor();
    dib.CopyToMapFile(dlg.GetPathName());
    EndWaitCursor();
}

void CEx25bView::OnEditCut() 
{
    OnEditCopy();
    GetDocument()->OnEditClearAll();
}

void CEx25bView::OnEditPaste() 
{
    CEx25bDoc* pDoc = GetDocument();
    COleDataObject dataObject;
    VERIFY(dataObject.AttachClipboard());
    DoPasteDib(&dataObject);
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
}

void CEx25bView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    COleDataObject dataObject;
    BOOL bAvail = dataObject.AttachClipboard() && dataObject.IsDataAvailable(CF_DIB);
    pCmdUI->Enable(bAvail);
}

void CEx25bView::OnEditPastefrom() 
{
    CEx25bDoc* pDoc = GetDocument();
    CFileDialog dlg(TRUE, "bmp", "*.bmp");
    if(dlg.DoModal() != IDOK) return;
    if(pDoc->m_dib.AttachMapFile(dlg.GetPathName(), TRUE)) { // share
	    CClientDC dc(this);
	    pDoc->m_dib.SetSystemPalette(&dc);
        pDoc->SetModifiedFlag();
        pDoc->UpdateAllViews(NULL);
    }
}

void CEx25bView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
    // custom MM_LOENGLISH with positive y down
    if(pDC->IsPrinting()) {
        int nHsize = pDC->GetDeviceCaps(HORZSIZE) * 1000 / 254;
        int nVsize = pDC->GetDeviceCaps(VERTSIZE) * 1000 / 254;
        pDC->SetMapMode(MM_ANISOTROPIC);
        pDC->SetWindowExt(nHsize, nVsize);
        pDC->SetViewportExt(pDC->GetDeviceCaps(HORZRES),
                            pDC->GetDeviceCaps(VERTRES));
    }
    else {
        CScrollView::OnPrepareDC(pDC, pInfo);
    }
}

void CEx25bView::OnInitialUpdate() 
{
    m_dropTarget.Register(this); // IMPORTANT
    SetScrollSizes(MM_TEXT, m_sizeTotal);
    m_tracker.m_nStyle = CRectTracker::solidLine | CRectTracker::resizeOutside;
    CScrollView::OnInitialUpdate();
}

void CEx25bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CEx25bDoc* pDoc = GetDocument();
    if(m_tracker.HitTest(point) == CRectTracker::hitMiddle) {
        COleDataSource* pSource = SaveDib();
        if(pSource) {
            // DoDragDrop returns only after drop is complete
            CClientDC dc(this);
            OnPrepareDC(&dc);
            CPoint topleft = m_rectTracker.TopLeft();
            dc.LPtoDP(&topleft);
            // 'point' here is not the same as the point parameter in 
            //  OnDragEnter, so we use this one to compute the offset
            m_dragOffset = point - topleft;  // device coordinates
            pDoc->m_bDragHere = TRUE;
            DROPEFFECT dropEffect = pSource->DoDragDrop(
                DROPEFFECT_MOVE|DROPEFFECT_COPY, CRect(0, 0, 0, 0));
            TRACE("after DoDragDrop -- dropEffect = %ld\n", dropEffect);
            if (dropEffect == DROPEFFECT_MOVE && pDoc->m_bDragHere) {
                pDoc->OnEditClearAll();
            }
            pDoc->m_bDragHere = FALSE;
            delete pSource;
        }
    }
    else {
        if(m_tracker.Track(this, point, FALSE, NULL)) {
            CClientDC dc(this);
            OnPrepareDC(&dc);
            // should have some way to prevent it going out of bounds
            m_rectTracker = m_tracker.m_rect;
            dc.DPtoLP(m_rectTracker); // Update logical coords
        }
    }
    Invalidate();
}

BOOL CEx25bView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if(m_tracker.SetCursor(pWnd, nHitTest)) {
        return TRUE;
    }
    else {
        return CScrollView::OnSetCursor(pWnd, nHitTest, message);
    }
}
