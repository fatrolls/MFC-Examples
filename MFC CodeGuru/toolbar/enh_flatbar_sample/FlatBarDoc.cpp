// FlatBarDoc.cpp : implementation of the CFlatBarDoc class
//

#include "stdafx.h"
#include "FlatBar.h"

#include "FlatBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatBarDoc

IMPLEMENT_DYNCREATE(CFlatBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CFlatBarDoc, CDocument)
	//{{AFX_MSG_MAP(CFlatBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatBarDoc construction/destruction

CFlatBarDoc::CFlatBarDoc()
{
	// TODO: add one-time construction code here

}

CFlatBarDoc::~CFlatBarDoc()
{
}

BOOL CFlatBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFlatBarDoc serialization

void CFlatBarDoc::Serialize(CArchive& ar)
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
// CFlatBarDoc diagnostics

#ifdef _DEBUG
void CFlatBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlatBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlatBarDoc commands
