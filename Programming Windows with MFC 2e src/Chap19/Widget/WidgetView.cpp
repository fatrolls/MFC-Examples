// WidgetView.cpp : implementation of the CWidgetView class
//

#include "stdafx.h"
#include "Widget.h"

#include "WidgetDoc.h"
#include "WidgetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWidgetView

IMPLEMENT_DYNCREATE(CWidgetView, CScrollView)

BEGIN_MESSAGE_MAP(CWidgetView, CScrollView)
	//{{AFX_MSG_MAP(CWidgetView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWidgetView construction/destruction

CWidgetView::CWidgetView()
{
}

CWidgetView::~CWidgetView()
{
}

BOOL CWidgetView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWidgetView drawing

void CWidgetView::OnDraw(CDC* pDC)
{
	CWidgetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int nCount = pDoc->GetWidgetCount ();
	if (nCount) {
		//
		// Draw all widgets.
		//
		for (int i=0; i<nCount; i++)
			pDoc->GetWidget (i)->Draw (pDC);

		//
		// Draw the selected widget if this view has the input focus.
		//
		if (m_nSel != -1 && CWnd::GetFocus () == this)
			pDoc->GetWidget (m_nSel)->DrawSelected (pDC);
	}
}

void CWidgetView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize (1280, 1024));
	m_pTempWidget = NULL;
	m_nSel = -1;
}

/////////////////////////////////////////////////////////////////////////////
// CWidgetView diagnostics

#ifdef _DEBUG
void CWidgetView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWidgetView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWidgetDoc* CWidgetView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWidgetDoc)));
	return (CWidgetDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWidgetView message handlers

DROPEFFECT CWidgetView::OnDragEnter(COleDataObject* pDataObject,
	DWORD dwKeyState, CPoint point) 
{
	CScrollView::OnDragEnter(pDataObject, dwKeyState, point);

	//
	// If a widget is available from the drop source, create a temporary
	// widget for drag imaging.
	//
	UINT nFormat = ((CWidgetApp*) AfxGetApp ())->GetClipboardFormat ();
	HGLOBAL hData = pDataObject->GetGlobalData (nFormat);

	if (hData != NULL) {
		WIDGETINFO* pWidgetInfo = (WIDGETINFO*) ::GlobalLock (hData);
		int x = point.x - pWidgetInfo->cx;
		int y = point.y - pWidgetInfo->cy;
		m_offset.cx = pWidgetInfo->cx;
		m_offset.cy = pWidgetInfo->cy;
		COLORREF color = pWidgetInfo->color;
		::GlobalUnlock (hData);
		::GlobalFree (hData);

		m_pTempWidget = new CWidget (x, y, color);
		m_pointLastImage.x = m_pointLastImage.y = -32000;
		m_pointLastMsg = point;

		//
		// Return DROPEFFECT_COPY if the Ctrl key is down, or DROPEFFECT_MOVE
		// if it is not.
		//
	    return (dwKeyState & MK_CONTROL) ?
			DROPEFFECT_COPY : DROPEFFECT_MOVE;
	}
	//
	// The cursor isn't carrying a widget. Indicate that the drop target will
	// not accept a drop.
	//
	m_pTempWidget = NULL;
	return DROPEFFECT_NONE;
}

DROPEFFECT CWidgetView::OnDragOver(COleDataObject* pDataObject,
	DWORD dwKeyState, CPoint point) 
{
	CScrollView::OnDragOver(pDataObject, dwKeyState, point);

	//
	// Return now if the object being dragged is not a widget.
	//
    if (m_pTempWidget == NULL)
        return DROPEFFECT_NONE;

	//
	// Convert the drag point to logical coordinates.
	//
	CClientDC dc (this);
	OnPrepareDC (&dc);
	dc.DPtoLP (&point);

	//
	// If the cursor has moved, erase the old drag image and draw a new one.
	//
	if (point != m_pointLastMsg) {
		CPoint pt (point.x - m_offset.cx, point.y - m_offset.cy);
		m_pTempWidget->DrawDragImage (&dc, m_pointLastImage);
		m_pTempWidget->DrawDragImage (&dc, pt);
		m_pointLastImage = pt;
		m_pointLastMsg = point;
	}

	//
	// Return DROPEFFECT_COPY if the Ctrl key is down, or DROPEFFECT_MOVE
	// if it is not.
	//
    return (dwKeyState & MK_CONTROL) ?
        DROPEFFECT_COPY : DROPEFFECT_MOVE;
}

void CWidgetView::OnDragLeave() 
{
	CScrollView::OnDragLeave();

	//
	// Erase the last drag image and delete the temporary widget.
	//
	if (m_pTempWidget != NULL) {
		CClientDC dc (this);
		OnPrepareDC (&dc);
		m_pTempWidget->DrawDragImage (&dc, m_pointLastImage);
		delete m_pTempWidget;
		m_pTempWidget = NULL;
	}
}

BOOL CWidgetView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect,
	CPoint point) 
{
	CScrollView::OnDrop(pDataObject, dropEffect, point);

	//
	// Convert the drop point to logical coordinates.
	//
	CClientDC dc (this);
	OnPrepareDC (&dc);
	dc.DPtoLP (&point);

	//
	// Erase the last drag image and delete the temporary widget.
	//
	if (m_pTempWidget != NULL) {
		m_pTempWidget->DrawDragImage (&dc, m_pointLastImage);
		delete m_pTempWidget;
		m_pTempWidget = NULL;
	}

	//
	// Retrieve the HGLOBAL from the data object and create a widget.
	//
	UINT nFormat = ((CWidgetApp*) AfxGetApp ())->GetClipboardFormat ();
	HGLOBAL hData = pDataObject->GetGlobalData (nFormat);

	if (hData != NULL) {
		WIDGETINFO* pWidgetInfo = (WIDGETINFO*) ::GlobalLock (hData);
		int x = point.x - pWidgetInfo->cx;
		int y = point.y - pWidgetInfo->cy;
		COLORREF color = pWidgetInfo->color;
		::GlobalUnlock (hData);
		::GlobalFree (hData);

		CWidgetDoc* pDoc = GetDocument ();
		m_nSel = pDoc->AddWidget (x, y, color);
		pDoc->UpdateAllViews (NULL);
		return TRUE;
	}
	return FALSE;
}

int CWidgetView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_oleDropTarget.Register (this);	
	return 0;
}

void CWidgetView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CScrollView::OnLButtonDown(nFlags, point);

	CWidgetDoc* pDoc = GetDocument ();
	int nCount = pDoc->GetWidgetCount ();

	if (nCount) {
		//
		// Convert the click point to logical coordinates.
		//
		CClientDC dc (this);
		OnPrepareDC (&dc);
		dc.DPtoLP (&point);

		//
		// Find out whether a widget was clicked.
		//
		int i;
		BOOL bHit = FALSE;
		for (i=nCount - 1; i>=0 && !bHit; i--) {
			CWidget* pWidget = pDoc->GetWidget (i);
			if (pWidget->PtInWidget (point)) {
				bHit = TRUE;
			}
		}

		//
		// If no widget was clicked, change the selection to NULL and exit.
		//
		if (!bHit) {
			m_nSel = -1;
			InvalidateRect (NULL, FALSE);
			return;
		}

		//
		// Select the widget that was clicked.
		//
		int nWidgetIndex = i + 1;

		if (m_nSel != nWidgetIndex) {
			m_nSel = nWidgetIndex;
			InvalidateRect (NULL, FALSE);
			UpdateWindow ();
		}

		//
		// Begin a drag-and-drop operation involving the selected widget.
		//
		HANDLE hData = ::GlobalAlloc (GMEM_MOVEABLE, sizeof (WIDGETINFO));

		WIDGETINFO* pWidgetInfo = (WIDGETINFO*) ::GlobalLock (hData);
		CWidget* pWidget = pDoc->GetWidget (nWidgetIndex);
		ASSERT (pWidget != NULL);
		CRect rect = pWidget->GetRect ();
		pWidgetInfo->cx = point.x - rect.left;
		pWidgetInfo->cy = point.y - rect.top;
		pWidgetInfo->color = pWidget->GetColor ();
		::GlobalUnlock (hData);

		COleDataSource ods;
		UINT nFormat = ((CWidgetApp*) AfxGetApp ())->GetClipboardFormat ();
		ods.CacheGlobalData (nFormat, hData);

		int nOldSel = m_nSel;
		DROPEFFECT de = ods.DoDragDrop (DROPEFFECT_COPY | DROPEFFECT_MOVE);

		if (de == DROPEFFECT_MOVE) {
			pDoc->RemoveWidget (nWidgetIndex);
			int nCount = pDoc->GetWidgetCount ();
			if (nOldSel == m_nSel || nCount == 0)
				m_nSel = -1;
			else if (m_nSel >= nCount)
				m_nSel = nCount - 1;
			pDoc->UpdateAllViews (NULL);
		}
	}
}

void CWidgetView::OnEditCut() 
{
	if (m_nSel != -1) {
		OnEditCopy ();
		OnEditDelete ();
	}
}

void CWidgetView::OnEditCopy() 
{
	if (m_nSel != -1) {
		//
		// Copy data describing the currently selected widget to a
		// global memory block.
		//
		HANDLE hData = ::GlobalAlloc (GMEM_MOVEABLE, sizeof (WIDGETINFO));

		WIDGETINFO* pWidgetInfo = (WIDGETINFO*) ::GlobalLock (hData);
		CWidgetDoc* pDoc = GetDocument ();
		CWidget* pWidget = pDoc->GetWidget (m_nSel);
		ASSERT (pWidget != NULL);
		CRect rect = pWidget->GetRect ();
		pWidgetInfo->x = rect.left;
		pWidgetInfo->y = rect.top;
		pWidgetInfo->color = pWidget->GetColor ();
		::GlobalUnlock (hData);

		//
		// Place the widget on the clipboard.
		//
		COleDataSource* pods = new COleDataSource;
		UINT nFormat = ((CWidgetApp*) AfxGetApp ())->GetClipboardFormat ();
		pods->CacheGlobalData (nFormat, hData);
		pods->SetClipboard ();
	}
}

void CWidgetView::OnEditPaste() 
{
	//
	// Create a COleDataObject and attach it to the clipboard.
	//
	COleDataObject odo;
	odo.AttachClipboard ();

	//
	// Retrieve the HGLOBAL from the clipboard and create a widget.
	//
	UINT nFormat = ((CWidgetApp*) AfxGetApp ())->GetClipboardFormat ();
	HGLOBAL hData = odo.GetGlobalData (nFormat);

	if (hData != NULL) {
		WIDGETINFO* pWidgetInfo = (WIDGETINFO*) ::GlobalLock (hData);
		int x = pWidgetInfo->x;
		int y = pWidgetInfo->y;
		COLORREF color = pWidgetInfo->color;
		::GlobalUnlock (hData);
		::GlobalFree (hData);

		CWidgetDoc* pDoc = GetDocument ();
		m_nSel = pDoc->AddWidget (x, y, color);
		pDoc->UpdateAllViews (NULL);
	}
}

void CWidgetView::OnEditDelete() 
{
	if (m_nSel != -1) {
		CWidgetDoc* pDoc = GetDocument ();
		pDoc->RemoveWidget (m_nSel);
		m_nSel = -1;
		pDoc->UpdateAllViews (NULL);
	}	
}

void CWidgetView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_nSel != -1);	
}

void CWidgetView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_nSel != -1);	
}

void CWidgetView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	UINT nFormat = ((CWidgetApp*) AfxGetApp ())->GetClipboardFormat ();
	pCmdUI->Enable (::IsClipboardFormatAvailable (nFormat));	
}

void CWidgetView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_nSel != -1);	
}

void CWidgetView::OnKillFocus(CWnd* pNewWnd) 
{
	CScrollView::OnKillFocus(pNewWnd);
	InvalidateRect (NULL, FALSE);	
}

void CWidgetView::OnSetFocus(CWnd* pOldWnd) 
{
	CScrollView::OnSetFocus(pOldWnd);
	InvalidateRect (NULL, FALSE);	
}
