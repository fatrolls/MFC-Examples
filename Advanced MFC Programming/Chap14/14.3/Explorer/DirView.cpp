#include "stdafx.h"
#include "Explorer.h"
#include "DirView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDirView, CTreeView)

CDirView::CDirView()
{
}

CDirView::~CDirView()
{
}


BEGIN_MESSAGE_MAP(CDirView, CTreeView)
	//{{AFX_MSG_MAP(CDirView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDirView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

#ifdef _DEBUG
void CDirView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDirView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
