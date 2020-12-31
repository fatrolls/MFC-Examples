// btncovw.cpp : implementation of the CBtncolorView class
//

#include "stdafx.h"
#include "btncolor.h"

#include "btncodoc.h"
#include "btncovw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBtncolorView

IMPLEMENT_DYNCREATE(CBtncolorView, CView)

BEGIN_MESSAGE_MAP(CBtncolorView, CView)
	//{{AFX_MSG_MAP(CBtncolorView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBtncolorView construction/destruction

CBtncolorView::CBtncolorView()
{
	// TODO: add construction code here
}

CBtncolorView::~CBtncolorView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CBtncolorView drawing

void CBtncolorView::OnDraw(CDC* pDC)
{
	CBtncolorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBtncolorView diagnostics

#ifdef _DEBUG
void CBtncolorView::AssertValid() const
{
	CView::AssertValid();
}

void CBtncolorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBtncolorDoc* CBtncolorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBtncolorDoc)));
	return (CBtncolorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBtncolorView message handlers
