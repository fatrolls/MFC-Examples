// MessengerEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MessengerEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessengerEdit

IMPLEMENT_DYNCREATE(CMessengerEdit, CEditView)

CMessengerEdit::CMessengerEdit()
{
}

CMessengerEdit::~CMessengerEdit()
{
}


BEGIN_MESSAGE_MAP(CMessengerEdit, CEditView)
	//{{AFX_MSG_MAP(CMessengerEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessengerEdit drawing

void CMessengerEdit::OnDraw(CDC* pDC)
{
	pDC;
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMessengerEdit diagnostics

#ifdef _DEBUG
void CMessengerEdit::AssertValid() const
{
	CEditView::AssertValid();
}

void CMessengerEdit::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMessengerEdit message handlers
