// dockdemoDoc.cpp : implementation of the CDockdemoDoc class
//

#include "stdafx.h"
#include "dockdemo.h"

#include "dockdemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockdemoDoc

IMPLEMENT_DYNCREATE(CDockdemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDockdemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDockdemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDockdemoDoc construction/destruction

CDockdemoDoc::CDockdemoDoc()
{
	// TODO: add one-time construction code here

}

CDockdemoDoc::~CDockdemoDoc()
{
}

BOOL CDockdemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDockdemoDoc serialization

void CDockdemoDoc::Serialize(CArchive& ar)
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
// CDockdemoDoc diagnostics

#ifdef _DEBUG
void CDockdemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDockdemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDockdemoDoc commands
