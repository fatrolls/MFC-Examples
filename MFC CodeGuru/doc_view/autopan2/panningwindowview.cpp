// PanningWindowView.cpp : implementation of the CPanningWindowView class
//

#include "stdafx.h"
#include "PanningWindow.h"

#include "PanningWindowDoc.h"
#include "PanningWindowView.h"
#include "OWnd\OWndDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const UINT uOriginWindowUpdateMessage = ::RegisterWindowMessage( OWND_WINDOW_UPDATE );

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowView

IMPLEMENT_DYNCREATE(CPanningWindowView, CScrollView)

BEGIN_MESSAGE_MAP(CPanningWindowView, CScrollView)
	//{{AFX_MSG_MAP(CPanningWindowView)
	ON_WM_MBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE( uOriginWindowUpdateMessage, OnOriginWindowUpdate )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowView construction/destruction

CPanningWindowView::CPanningWindowView()
{
	// TODO: add construction code here

}


CPanningWindowView::~CPanningWindowView()
{
}


BOOL CPanningWindowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowView drawing

void CPanningWindowView::OnDraw(CDC* pDC)
{
	CPanningWindowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	for( int n = 0; n < pDoc->m_arrShapes.GetSize(); n++ )
	{
		pDoc->m_arrShapes[ n ]->Draw( pDC );
	}
}


void CPanningWindowView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	const CPanningWindowDoc* pDoc = GetDocument();

	SetScrollSizes(MM_TEXT, pDoc->GetDrawingSize() );
}

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowView diagnostics

#ifdef _DEBUG
void CPanningWindowView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPanningWindowView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPanningWindowDoc* CPanningWindowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPanningWindowDoc)));
	return (CPanningWindowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPanningWindowView message handlers

void CPanningWindowView::OnMButtonDown(UINT nFlags, CPoint point) 
{
	//
	//	Quick way to determine whether we are scrollable in either direction
	//	If we cannot scroll in either direction then do nothing.
	BOOL bVert = GetStyle() & WS_VSCROLL;
	BOOL bHorz = GetStyle() & WS_HSCROLL;

	if( bVert || bHorz )
	{
		VERIFY( StartPanning( this, bVert, bHorz, point ) );
	}

	CScrollView::OnMButtonDown(nFlags, point);
}


LRESULT CPanningWindowView::OnOriginWindowUpdate(WPARAM , LPARAM lParam)
// 
//	Process the update message sent by the origin window.
// You only need to respond to this message if you want to do extra or different scrolling
{
	// 
	// psizeDistance will contain the distance the cursor is from the origin. We then use 
	// this to calculate the new scroll position and the amount to scroll our window. 
	const CSize *psizeDistance = reinterpret_cast<const CSize *>( lParam );
#ifdef _DEBUG
	afxDump<<_T("CPanningWindowView::OnOriginWindowUpdate size")<<*psizeDistance<<_T("\n");
#endif	//	_DEBUG
	// 
	//    Return 1 to signal to COriginWnd that you have handled the scrolling, return 0 if you 
	//    want COriginWnd to perform the scrolling. 
	return 0;
}
