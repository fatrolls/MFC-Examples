// ImageViewerView.cpp : implementation of the CImageViewerView class
//

#include "stdafx.h"
#include "ImageViewer.h"

#include "ImageViewerDoc.h"
#include "ImageViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageViewerView

IMPLEMENT_DYNCREATE(CImageViewerView, CView)

BEGIN_MESSAGE_MAP(CImageViewerView, CView)
	//{{AFX_MSG_MAP(CImageViewerView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageViewerView construction/destruction

CImageViewerView::CImageViewerView()
{
	// TODO: add construction code here

}

CImageViewerView::~CImageViewerView()
{
}

BOOL CImageViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImageViewerView drawing

void CImageViewerView::OnDraw(CDC* pDC)
{
	CImageViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	UNREFERENCED_PARAMETER(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CImageViewerView diagnostics

#ifdef _DEBUG
void CImageViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CImageViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageViewerDoc* CImageViewerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageViewerDoc)));
	return (CImageViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageViewerView message handlers

int CImageViewerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if(!m_imageViewer.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,
		CRect(0,0,0,0),this,1000))
	{
		TRACE(_T("CImageViewerView::OnCreate: Failed to create image viewer control\n"));
		return -1;
	}
	
	return 0;
}

void CImageViewerView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(::IsWindow(m_imageViewer.GetSafeHwnd()))
		m_imageViewer.MoveWindow(CRect(0,0,cx,cy));
	
}

BOOL CImageViewerView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;
}

void CImageViewerView::OnActivateView(BOOL bActivate, CView* pActivateView, 
									  CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if(::IsWindow(m_imageViewer.GetSafeHwnd()))
		m_imageViewer.DoRealizePalette(TRUE,TRUE);
}
