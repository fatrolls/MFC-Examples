// FastTestDoc.cpp : implementation of the CFastTestDoc class
//

#include "stdafx.h"
#include "FastTest.h"

#include "FastTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFastTestDoc

IMPLEMENT_DYNCREATE(CFastTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CFastTestDoc, CDocument)
	//{{AFX_MSG_MAP(CFastTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFastTestDoc construction/destruction

CFastTestDoc::CFastTestDoc()
{
	// TODO: add one-time construction code here

}

CFastTestDoc::~CFastTestDoc()
{
}

BOOL CFastTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFastTestDoc serialization

void CFastTestDoc::Serialize(CArchive& ar)
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
// CFastTestDoc diagnostics

#ifdef _DEBUG
void CFastTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFastTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFastTestDoc commands
