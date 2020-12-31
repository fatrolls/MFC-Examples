// TabTestDoc.cpp : implementation of the CTabTestDoc class
//

#include "stdafx.h"
#include "TabTest.h"

#include "TabTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabTestDoc

IMPLEMENT_DYNCREATE(CTabTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabTestDoc, CDocument)
	//{{AFX_MSG_MAP(CTabTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabTestDoc construction/destruction

CTabTestDoc::CTabTestDoc()
{
	// TODO: add one-time construction code here

}

CTabTestDoc::~CTabTestDoc()
{
}

BOOL CTabTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTabTestDoc serialization

void CTabTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTabTestDoc diagnostics

#ifdef _DEBUG
void CTabTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabTestDoc commands
