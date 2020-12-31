#include "stdafx.h"
#include "Spw.h"
#include "SpwFVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSpwFView, CFormView)

CSpwFView::CSpwFView() : CFormView(CSpwFView::IDD)
{
	//{{AFX_DATA_INIT(CSpwFView)
	//}}AFX_DATA_INIT
}

CSpwFView::~CSpwFView()
{
}

void CSpwFView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpwFView)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpwFView, CFormView)
	//{{AFX_MSG_MAP(CSpwFView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#ifdef _DEBUG
void CSpwFView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSpwFView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
