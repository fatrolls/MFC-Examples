// CMFormView.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "CMFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFormView

IMPLEMENT_DYNCREATE(CMFormView, CFormView)

CMFormView::CMFormView()
	: CFormView(CMFormView::IDD)
{
	//{{AFX_DATA_INIT(CMFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMFormView::~CMFormView()
{
}

void CMFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMFormView, CFormView)
	//{{AFX_MSG_MAP(CMFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFormView diagnostics

#ifdef _DEBUG
void CMFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFormView message handlers
