// noteDoc.cpp : implementation of the CNoteDoc class
//

#include "stdafx.h"
#include "note.h"

#include "noteDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc

IMPLEMENT_DYNCREATE(CNoteDoc, CDocument)

BEGIN_MESSAGE_MAP(CNoteDoc, CDocument)
	//{{AFX_MSG_MAP(CNoteDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc construction/destruction

CNoteDoc::CNoteDoc()
{
	// TODO: add one-time construction code here

}

CNoteDoc::~CNoteDoc()
{
}

BOOL CNoteDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc serialization

void CNoteDoc::Serialize(CArchive& ar)
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
// CNoteDoc diagnostics

#ifdef _DEBUG
void CNoteDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNoteDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc commands
