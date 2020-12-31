// PCTestDoc.cpp : implementation of the CPCTestDoc class
//

#include "stdafx.h"
#include "PCTest.h"

#include "PCTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCTestDoc

IMPLEMENT_DYNCREATE(CPCTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CPCTestDoc, CDocument)
	//{{AFX_MSG_MAP(CPCTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCTestDoc construction/destruction

CPCTestDoc::CPCTestDoc()
{
	// TODO: add one-time construction code here

}

CPCTestDoc::~CPCTestDoc()
{
}

BOOL CPCTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPCTestDoc serialization

void CPCTestDoc::Serialize(CArchive& ar)
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
// CPCTestDoc diagnostics

#ifdef _DEBUG
void CPCTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPCTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPCTestDoc commands
