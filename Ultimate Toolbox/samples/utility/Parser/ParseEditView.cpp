// ParseEditView.cpp : implementation file
//

#include "stdafx.h"
#include "ParserView.h"
#include "ParseEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParseEditView

IMPLEMENT_DYNCREATE(CParseEditView, CEditView)

CParseEditView::CParseEditView()
{
}

CParseEditView::~CParseEditView()
{
}


BEGIN_MESSAGE_MAP(CParseEditView, CEditView)
	//{{AFX_MSG_MAP(CParseEditView)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParseEditView drawing

void CParseEditView::OnDraw(CDC* /*pDC*/)
{
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CParseEditView diagnostics

#ifdef _DEBUG
void CParseEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CParseEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CParseEditView message handlers

HBRUSH CParseEditView::CtlColor(CDC* /*pDC*/, UINT nCtlColor) 
{
    if (CTLCOLOR_STATIC == nCtlColor)
        return (HBRUSH) GetStockObject(WHITE_BRUSH);
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}

BOOL CParseEditView::PreCreateWindow(CREATESTRUCT& cs) 
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);

	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping
    cs.style |= ES_READONLY;

	return bPreCreated;
}
