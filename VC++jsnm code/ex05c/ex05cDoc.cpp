// ex05cDoc.cpp : implementation of the CEx05cDoc class
//

#include "stdafx.h"
#include "ex05c.h"

#include "ex05cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx05cDoc

IMPLEMENT_DYNCREATE(CEx05cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx05cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx05cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx05cDoc construction/destruction

CEx05cDoc::CEx05cDoc()
{
	// TODO: add one-time construction code here

}

CEx05cDoc::~CEx05cDoc()
{
}

BOOL CEx05cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx05cDoc serialization

void CEx05cDoc::Serialize(CArchive& ar)
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
// CEx05cDoc diagnostics

#ifdef _DEBUG
void CEx05cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx05cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx05cDoc commands
