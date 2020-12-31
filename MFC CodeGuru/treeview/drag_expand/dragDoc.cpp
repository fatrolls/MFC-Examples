// dragDoc.cpp : implementation of the CDragDoc class
//

#include "stdafx.h"
#include "drag.h"

#include "dragDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragDoc

IMPLEMENT_DYNCREATE(CDragDoc, CDocument)

BEGIN_MESSAGE_MAP(CDragDoc, CDocument)
	//{{AFX_MSG_MAP(CDragDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragDoc construction/destruction

CDragDoc::CDragDoc()
{
	// TODO: add one-time construction code here

}

CDragDoc::~CDragDoc()
{
}

BOOL CDragDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDragDoc serialization

void CDragDoc::Serialize(CArchive& ar)
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
// CDragDoc diagnostics

#ifdef _DEBUG
void CDragDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDragDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDragDoc commands
