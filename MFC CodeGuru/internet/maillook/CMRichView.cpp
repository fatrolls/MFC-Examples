// CMRichView.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "CMRichView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMRichView

IMPLEMENT_DYNCREATE(CMRichView, CRichEditView)

CMRichView::CMRichView()
{
}

CMRichView::~CMRichView()
{
}

BEGIN_MESSAGE_MAP(CMRichView, CRichEditView)
	//{{AFX_MSG_MAP(CMRichView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMRichView diagnostics

#ifdef _DEBUG
void CMRichView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CMRichView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMRichView message handlers
