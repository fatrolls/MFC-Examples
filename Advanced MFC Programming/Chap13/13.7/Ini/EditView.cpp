#include "stdafx.h"
#include "Ini.h"
#include "EditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CIniEditView, CEditView)

CIniEditView::CIniEditView()
{
}

CIniEditView::~CIniEditView()
{
}


BEGIN_MESSAGE_MAP(CIniEditView, CEditView)
	//{{AFX_MSG_MAP(CIniEditView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CIniEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

#ifdef _DEBUG
void CIniEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CIniEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
