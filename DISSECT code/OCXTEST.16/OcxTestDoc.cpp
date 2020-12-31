// OcxTestDoc.cpp : implementation of the COcxTestDoc class
//

#include "stdafx.h"
#include "OcxTest.h"

#include "OcxTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COcxTestDoc

IMPLEMENT_DYNCREATE(COcxTestDoc, CDocument)

BEGIN_MESSAGE_MAP(COcxTestDoc, CDocument)
	//{{AFX_MSG_MAP(COcxTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COcxTestDoc construction/destruction

COcxTestDoc::COcxTestDoc()
{
	// TODO: add one-time construction code here

}

COcxTestDoc::~COcxTestDoc()
{
}

BOOL COcxTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COcxTestDoc serialization

void COcxTestDoc::Serialize(CArchive& ar)
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
// COcxTestDoc diagnostics

#ifdef _DEBUG
void COcxTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COcxTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COcxTestDoc commands
