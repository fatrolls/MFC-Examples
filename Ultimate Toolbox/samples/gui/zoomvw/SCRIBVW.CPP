// scribvw.cpp : implementation of the CScribView class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#include "stdafx.h"
#include "scribble.h"

#include "scribdoc.h"
#include "scribvw.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScribView

IMPLEMENT_DYNCREATE(CScribView, COXZoomView)


BEGIN_MESSAGE_MAP(CScribView, COXZoomView)
	//{{AFX_MSG_MAP(CScribView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ZOOM_100, OnZoom100)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_100, OnUpdateZoom100)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ZOOM_TOWINDOW, OnZoomToWindow)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ZOOM, OnUpdateZoom)
	ON_COMMAND(ID_ZOOM_UP, OnZoomUp)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_UP, OnUpdateZoomUp)
	ON_COMMAND(ID_ZOOM_DOWN, OnZoomDown)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_DOWN, OnUpdateZoomDown)
	ON_COMMAND(ID_WINDOW_DUPLICATE, OnWindowDuplicate)
	//}}AFX_MSG_MAP

	// Standard printing commands
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScribView construction/destruction

CScribView::CScribView()
{
	// TODO: add construction code here 
	action = IDLE;
}

CScribView::~CScribView()
{
}



/////////////////////////////////////////////////////////////////////////////
void CScribView::OnUpdate(CView*, LPARAM, CObject* pHint)
{
	// The document has informed this view that some data has changed.

	if (pHint != NULL)
	{
		if (pHint->IsKindOf(RUNTIME_CLASS(CStroke)))
		{
			// The hint is that a stroke as been added (or changed).
			// So, invalidate its rectangle.
			CStroke* pStroke = (CStroke*)pHint;
			CClientDC dc(this);
			OnPrepareDC(&dc);
			CRect rectInvalid = pStroke->GetBoundingRect();
			dc.LPtoDP(&rectInvalid);
			InvalidateRect(&rectInvalid);
			return;
		}
	}
	// We can't interpret the hint, so assume that anything might
	// have been updated.
	Invalidate(TRUE);
	return;
}

/////////////////////////////////////////////////////////////////////////////
//  A view's OnInitialUpdate() overrideable function is called immediately
//  after the frame window is created, and the view within the frame
//  window is attached to its document.  This provides the scroll view the
//  opportunity to set its size (m_totalSize) based on the document size.
void CScribView::OnInitialUpdate()
{
	SetDeviceScrollSizesRelative(MM_LOENGLISH, GetDocument()->GetDocRect());
	//SetDeviceScrollSizesRelative(CSize(600,400), GetDocument()->GetDocRect());
	SetAlignToBottom( TRUE );
	SetZoomAlign( ZV_CENTER );
}



/////////////////////////////////////////////////////////////////////////////
// CScribView drawing

void CScribView::OnDraw(CDC* pDC)
{
	CScribDoc* pDoc = GetDocument();


	// Get the invalidated rectangle of the view, or in the case
	// of printing, the clipping region of the printer dc.
	CRect rectClip;
	CRect rectStroke;
	pDC->GetClipBox(&rectClip);
	pDC->LPtoDP(&rectClip);
	if( !pDC->IsPrinting() )
		rectClip.InflateRect(1,1);

	// Note: COXZoomView::OnPaint() will have already adjusted the
	// viewport origin before calling OnDraw(), to reflect the
	// currently scrolled position.

	// The view delegates the drawing of individual strokes to
	// CStroke::DrawStroke().
	for (POSITION pos = pDoc->GetFirstStrokePos(); pos != NULL; )
	{
		CStroke* pStroke = pDoc->GetNextStroke(pos);
		rectStroke = pStroke->GetBoundingRect();
		pDC->LPtoDP(&rectStroke);
		if (!rectStroke.IntersectRect(&rectStroke, &rectClip))
			continue;
		pStroke->DrawStroke(pDC);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CScribView diagnostics

#ifdef _DEBUG
void CScribView::AssertValid() const
{
	COXZoomView::AssertValid();
}

void CScribView::Dump(CDumpContext& dc) const
{
	COXZoomView::Dump(dc);
}

CScribDoc* CScribView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScribDoc)));
	return (CScribDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScribView message handlers

void CScribView::OnLButtonDown(UINT, CPoint point)
{   // When the user presses the mouse button, she may be
	// starting a new stroke, or selecting or de-selecting a stroke.

	// COXZoomView changes the viewport origin and mapping mode.
	// It's necessary to convert the point from device coordinates
	// to logical coordinates, such as are stored in the document.
	if( action != IDLE ) return;
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CRect rcClip, rcClient;
	rcClip = GetDocument()->GetDocRect();
	dc.LPtoDP( rcClip );
	GetClientRect( rcClient );
	rcClip.IntersectRect( rcClip, rcClient );
	CRect rcPen( 0, 0, GetDocument()->m_nPenWidth, 0 );
	dc.LPtoDP( rcPen );
	int i = rcPen.Width();
	i++;
	i/=2;
	rcClip.InflateRect( -i, -i );
	if( !rcClip.PtInRect( point ) )
		return;
	ClientToScreen( rcClip );
	::ClipCursor( rcClip );
	action = DRAWING;
	dc.DPtoLP(&point);

	m_pStrokeCur = GetDocument()->NewStroke();
	m_pStrokeCur->AddPoint(point); // add first point to the new stroke

	SetCapture();       // Capture the mouse until button up.
	m_ptPrev = point;   // Serves as the MoveTo() anchor point for the
						// LineTo() the next point, as the user drags the
						// mouse.

	return;

}


/////////////////////////////////////////////////////////////////////////////
void CScribView::OnLButtonUp(UINT, CPoint point)
{
	// Mouse button up is interesting in the Scribble application
	// only if the user is currently drawing a new stroke by dragging
	// the captured mouse.

	if( action != DRAWING ) return;
	action = IDLE;
	::ClipCursor( NULL );
	CScribDoc* pDoc = GetDocument();

	CClientDC dc(this);

	// COXZoomView changes the viewport origin and mapping mode.
	// It's necessary to convert the point from device coordinates
	// to logical coordinates, such as are stored in the document.
	OnPrepareDC(&dc);  // set up mapping mode and viewport origin
	dc.DPtoLP(&point);

	CPen* pOldPen = dc.SelectObject(pDoc->GetCurrentPen());
	dc.MoveTo(m_ptPrev);
	dc.LineTo(point);
	dc.SelectObject(pOldPen);
	m_pStrokeCur->AddPoint(point);

	// Tell the stroke item that we're done adding points to it.
	// This is so it can finish computing its bounding rectangle.
	m_pStrokeCur->FinishStroke();

	// Tell the other views that this stroke has been added
	// so that they can invalidate this stroke's area in their
	// client area.
	pDoc->UpdateAllViews(this, 0L, m_pStrokeCur);

	ReleaseCapture();   // Release the mouse capture established at
						// the beginning of the mouse drag.
	return;
}


void CScribView::OnRButtonDown(UINT , CPoint point)
{
	if( action != IDLE ) return;
	action = ZOOMING;
	CRect rectZoom;
	CZoomRect zoom;
	if( zoom.TrackTheMouse( WM_RBUTTONUP, this, rectZoom, point ) )
		ZoomToRectangle( rectZoom );
	action = IDLE;
	return;
}

/////////////////////////////////////////////////////////////////////////////
void CScribView::OnMouseMove(UINT, CPoint point)
{
	// Mouse movement is interesting in the Scribble application
	// only if the user is currently drawing a new stroke by dragging
	// the captured mouse.

	switch( action )
	{
		case DRAWING:
		{	
			CClientDC dc(this);
			// COXZoomView changes the viewport origin and mapping mode.
			// It's necessary to convert the point from device coordinates
			// to logical coordinates, such as are stored in the document.
			OnPrepareDC(&dc);
			dc.DPtoLP(&point);
		
			m_pStrokeCur->AddPoint(point);
		
			// Draw a line from the previous detected point in the mouse
			// drag to the current point.
			CPen* pOldPen = dc.SelectObject(GetDocument()->GetCurrentPen());
			dc.MoveTo(m_ptPrev);
			dc.LineTo(point);
			dc.SelectObject(pOldPen);
			m_ptPrev = point;
		}
		break;
	}
	return;
}

void CScribView::OnZoom100()
{
	SetZoomLevel( 100 );
}

void CScribView::OnUpdateZoom100(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( 100 == GetZoomLevel() ? 1 : 0 );
}


void CScribView::OnZoomToWindow()
{
	ZoomToWindow();
}

void CScribView::OnUpdateZoom(CCmdUI* pCmdUI)
{
	TCHAR szBuf[10];
	UTBStr::stprintf(szBuf, 10, _T("%4i%%"), GetZoomLevel() );
	pCmdUI->Enable( TRUE );
	pCmdUI->SetText( szBuf );
}

void CScribView::OnZoomUp()
{
	int i = GetZoomLevel();
	i = MulDiv( 1000,i,707);
	SetZoomLevel( i );
}

void CScribView::OnUpdateZoomUp(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( 1000 > GetZoomLevel() );
}

void CScribView::OnZoomDown()
{
	int i = GetZoomLevel();
	i = MulDiv( 707,i,1000);
	SetZoomLevel( i );
}

void CScribView::OnUpdateZoomDown(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( 10 < GetZoomLevel() );
}

void CScribView::OnWindowDuplicate()
{
	CDocTemplate* pTempl = GetDocument()->GetDocTemplate();
	CFrameWnd* pFrame = pTempl->CreateNewFrame( GetDocument(), GetParentFrame() );
	pTempl->InitialUpdateFrame( pFrame, GetDocument() );
}
