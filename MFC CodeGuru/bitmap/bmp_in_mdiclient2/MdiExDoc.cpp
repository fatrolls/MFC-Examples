// MdiExDoc.cpp : implementation of the CMdiExDoc class
//

#include "stdafx.h"
#include "MdiEx.h"

#include "MdiExDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdiExDoc

IMPLEMENT_DYNCREATE(CMdiExDoc, CDocument)

BEGIN_MESSAGE_MAP(CMdiExDoc, CDocument)
	//{{AFX_MSG_MAP(CMdiExDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdiExDoc construction/destruction

CMdiExDoc::CMdiExDoc()
{
	// TODO: add one-time construction code here

}

CMdiExDoc::~CMdiExDoc()
{
}

BOOL CMdiExDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMdiExDoc serialization

void CMdiExDoc::Serialize(CArchive& ar)
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
// CMdiExDoc diagnostics

#ifdef _DEBUG
void CMdiExDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMdiExDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMdiExDoc commands
