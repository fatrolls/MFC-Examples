// LayoutDoc.cpp : implementation of the CLayoutDoc class
//

#include "stdafx.h"
#include "Layout.h"

#include "LayoutDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayoutDoc

IMPLEMENT_DYNCREATE(CLayoutDoc, CDocument)

BEGIN_MESSAGE_MAP(CLayoutDoc, CDocument)
	//{{AFX_MSG_MAP(CLayoutDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayoutDoc construction/destruction

CLayoutDoc::CLayoutDoc()
{
	// TODO: add one-time construction code here

}

CLayoutDoc::~CLayoutDoc()
{
}

BOOL CLayoutDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLayoutDoc serialization

void CLayoutDoc::Serialize(CArchive& ar)
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
// CLayoutDoc diagnostics

#ifdef _DEBUG
void CLayoutDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLayoutDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLayoutDoc commands
