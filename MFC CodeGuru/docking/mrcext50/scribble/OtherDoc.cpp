// OtherDoc.cpp : implementation of the COtherDoc class
//

#include "stdafx.h"
#include "Scribble.h"

#include "OtherDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherDoc

IMPLEMENT_DYNCREATE(COtherDoc, CDocument)

BEGIN_MESSAGE_MAP(COtherDoc, CDocument)
	//{{AFX_MSG_MAP(COtherDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherDoc construction/destruction

COtherDoc::COtherDoc()
{
	// TODO: add one-time construction code here

}

COtherDoc::~COtherDoc()
{
}

BOOL COtherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COtherDoc serialization

void COtherDoc::Serialize(CArchive& ar)
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
// COtherDoc diagnostics

#ifdef _DEBUG
void COtherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COtherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COtherDoc commands
