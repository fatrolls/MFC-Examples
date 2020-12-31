// captionView.cpp : implementation of the CCaptionView class
//

#include "stdafx.h"
#include "caption.h"
#include "ChildFrm.h"
#include "captionDoc.h"
#include "captionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptionView

IMPLEMENT_DYNCREATE(CCaptionView, CView)

BEGIN_MESSAGE_MAP(CCaptionView, CView)
	//{{AFX_MSG_MAP(CCaptionView)
	ON_COMMAND(ID_SET_MODIFIED, OnSetModified)
	ON_COMMAND(ID_SETTEXT, OnSettext)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptionView construction/destruction

CCaptionView::CCaptionView()
{
	// TODO: add construction code here

}

CCaptionView::~CCaptionView()
{
}

BOOL CCaptionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCaptionView drawing

void CCaptionView::OnDraw(CDC* pDC)
{
	CCaptionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCaptionView printing

BOOL CCaptionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCaptionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCaptionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCaptionView diagnostics

#ifdef _DEBUG
void CCaptionView::AssertValid() const
{
	CView::AssertValid();
}

void CCaptionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCaptionDoc* CCaptionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCaptionDoc)));
	return (CCaptionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCaptionView message handlers

void CCaptionView::OnSetModified() 
{
  CDocument *pDoc = GetDocument();	
  pDoc->SetModifiedFlag(TRUE);	
}

void CCaptionView::OnSettext() 
{
  SetWindowText("hello world");	
  CChildFrame *pChild = (CChildFrame *)(((CMDIFrameWnd *)AfxGetMainWnd())->MDIGetActive());
  pChild->OnUpdateFrameTitle(TRUE);
}
