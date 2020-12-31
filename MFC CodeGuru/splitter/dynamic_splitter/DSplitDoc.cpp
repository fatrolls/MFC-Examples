// DSplitDoc.cpp : implementation of the CDSplitDoc class
//

#include "stdafx.h"
#include "DSplit.h"

#include "DSplitDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSplitDoc

IMPLEMENT_DYNCREATE(CDSplitDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSplitDoc, CDocument)
	//{{AFX_MSG_MAP(CDSplitDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSplitDoc construction/destruction

CDSplitDoc::CDSplitDoc()
{
	// TODO: add one-time construction code here

}

CDSplitDoc::~CDSplitDoc()
{
}

BOOL CDSplitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDSplitDoc serialization

void CDSplitDoc::Serialize(CArchive& ar)
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
// CDSplitDoc diagnostics

#ifdef _DEBUG
void CDSplitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSplitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSplitDoc commands
