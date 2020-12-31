// OutlookFormView.cpp : implementation file
//

#include "stdafx.h"
#include "Outlook.h"
#include "OutlookFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookFormView

IMPLEMENT_DYNCREATE(COutlookFormView, CFormView)

COutlookFormView::COutlookFormView()
	: CFormView(COutlookFormView::IDD)
{
	//{{AFX_DATA_INIT(COutlookFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COutlookFormView::~COutlookFormView()
{
}

void COutlookFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutlookFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutlookFormView, CFormView)
	//{{AFX_MSG_MAP(COutlookFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookFormView diagnostics

#ifdef _DEBUG
void COutlookFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void COutlookFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookFormView message handlers
