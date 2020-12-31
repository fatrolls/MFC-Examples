#include "stdafx.h"
#include "Spw.h"
#include "SpwEVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSpwEView, CEditView)

CSpwEView::CSpwEView()
{
}

CSpwEView::~CSpwEView()
{
}


BEGIN_MESSAGE_MAP(CSpwEView, CEditView)
	//{{AFX_MSG_MAP(CSpwEView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSpwEView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

#ifdef _DEBUG
void CSpwEView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSpwEView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
