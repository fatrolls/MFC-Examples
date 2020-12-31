// PreviewView.cpp : implementation of the CMyPreviewView class
//

#include "stdafx.h"
#include "Preview.h"

#include "PreviewDoc.h"
#include "PreviewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView

IMPLEMENT_DYNCREATE(CMyPreviewView, CView)

BEGIN_MESSAGE_MAP(CMyPreviewView, CView)
	//{{AFX_MSG_MAP(CMyPreviewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView construction/destruction

CMyPreviewView::CMyPreviewView()
{
	// TODO: add construction code here

}

CMyPreviewView::~CMyPreviewView()
{
}

BOOL CMyPreviewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView drawing

void CMyPreviewView::OnDraw(CDC* pDC)
{
	CPreviewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->TextOut(10,20,"Select Open from File Menu option To Preview a BMP file without opening it ");
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView printing



/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView diagnostics

#ifdef _DEBUG
void CMyPreviewView::AssertValid() const
{
	CView::AssertValid();
}

void CMyPreviewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPreviewDoc* CMyPreviewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPreviewDoc)));
	return (CPreviewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView message handlers
