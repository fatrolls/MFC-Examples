// PrintTreeDoc.cpp : implementation of the CPrintTreeDoc class
//

#include "stdafx.h"
#include "PrintTree.h"

#include "PrintTreeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintTreeDoc

IMPLEMENT_DYNCREATE(CPrintTreeDoc, CDocument)

BEGIN_MESSAGE_MAP(CPrintTreeDoc, CDocument)
	//{{AFX_MSG_MAP(CPrintTreeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintTreeDoc construction/destruction

CPrintTreeDoc::CPrintTreeDoc()
{
	// TODO: add one-time construction code here

}

CPrintTreeDoc::~CPrintTreeDoc()
{
}

BOOL CPrintTreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPrintTreeDoc serialization

void CPrintTreeDoc::Serialize(CArchive& ar)
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
// CPrintTreeDoc diagnostics

#ifdef _DEBUG
void CPrintTreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPrintTreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrintTreeDoc commands
