// CXMLExplorerView.cpp : implementation of the CXMLExplorerView class
//

#include "stdafx.h"
#include "XMLExplorer.h"

#include "CXMLExplorerDocument.h"
#include "CXMLExplorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerView

IMPLEMENT_DYNCREATE(CXMLExplorerView, CView)

BEGIN_MESSAGE_MAP(CXMLExplorerView, CView)
	//{{AFX_MSG_MAP(CXMLExplorerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerView construction/destruction

CXMLExplorerView::CXMLExplorerView()
{
	// TODO: add construction code here

}

CXMLExplorerView::~CXMLExplorerView()
{
}

BOOL CXMLExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerView drawing

void CXMLExplorerView::OnDraw(CDC* /* pDC */ )
{
	//CXMLExplorerDocument* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerView printing

BOOL CXMLExplorerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXMLExplorerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXMLExplorerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerView diagnostics

#ifdef _DEBUG
void CXMLExplorerView::AssertValid() const
{
	CView::AssertValid();
}

void CXMLExplorerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXMLExplorerDocument* CXMLExplorerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXMLExplorerDocument)));
	return (CXMLExplorerDocument*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXMLExplorerView message handlers
