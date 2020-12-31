#include "stdafx.h"
#include "Chart.h"
#include "TextDoc.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTextView, CEditView)

CTextView::CTextView()
{
}

CTextView::~CTextView()
{
}


BEGIN_MESSAGE_MAP(CTextView, CEditView)
	//{{AFX_MSG_MAP(CTextView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTextView::OnDraw(CDC* pDC)
{
	CTextDoc *pDoc=(CTextDoc *)GetDocument();
}

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTextView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
