// browserView.cpp : implementation of the CBrowserView class
//

#include "stdafx.h"
#include "browser.h"

#include "browserDoc.h"
#include "browserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserView

IMPLEMENT_DYNCREATE(CBrowserView, CView)

BEGIN_MESSAGE_MAP(CBrowserView, CView)
	//{{AFX_MSG_MAP(CBrowserView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserView construction/destruction

CBrowserView::CBrowserView()
{
	// TODO: add construction code here

}

CBrowserView::~CBrowserView()
{
}

BOOL CBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserView drawing

void CBrowserView::OnDraw(CDC* pDC)
{
	CBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserView printing

BOOL CBrowserView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBrowserView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBrowserView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserView diagnostics

#ifdef _DEBUG
void CBrowserView::AssertValid() const
{
	CView::AssertValid();
}

void CBrowserView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBrowserDoc* CBrowserView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBrowserDoc)));
	return (CBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserView message handlers

void CBrowserView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	m_WebBrowser2.Create("",WS_VISIBLE|WS_CHILD,CRect(0,0,1020,650),this,ID_BROWSER);
	m_WebBrowser2.Navigate( "http://www.codeguru.com", NULL, NULL, NULL, NULL);	
}

void CBrowserView::NavigateURL(LPCTSTR lpszName)
{
		m_WebBrowser2.Navigate( lpszName, NULL, NULL, NULL, NULL);	


}
