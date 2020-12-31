// RegExpressionDoc.cpp : implementation of the CRegExpressionDoc class
//

#include "stdafx.h"
#include "RegExpression.h"

#include "RegExpressionDoc.h"
#include "FindDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionDoc

IMPLEMENT_DYNCREATE(CRegExpressionDoc, CDocument)

BEGIN_MESSAGE_MAP(CRegExpressionDoc, CDocument)
	//{{AFX_MSG_MAP(CRegExpressionDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionDoc construction/destruction

CRegExpressionDoc::CRegExpressionDoc()
{
	// TODO: add one-time construction code here

}

CRegExpressionDoc::~CRegExpressionDoc()
{
}

BOOL CRegExpressionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	POSITION pos=this->GetFirstViewPosition();
	CEditView* pEditView=(CEditView*) this->GetNextView(pos);
	pEditView->SetWindowText(_T(""));
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRegExpressionDoc serialization

void CRegExpressionDoc::Serialize(CArchive& ar)
{

		POSITION pos=this->GetFirstViewPosition();
		CEditView* pEditView=(CEditView*) this->GetNextView(pos);
		pEditView->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionDoc diagnostics

#ifdef _DEBUG
void CRegExpressionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRegExpressionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionDoc commands



