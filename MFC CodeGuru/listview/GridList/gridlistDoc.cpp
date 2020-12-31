// gridlistDoc.cpp : implementation of the CGridlistDoc class
//

#include "stdafx.h"
#include "gridlist.h"

#include "gridlistDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridlistDoc

IMPLEMENT_DYNCREATE(CGridlistDoc, CDocument)

BEGIN_MESSAGE_MAP(CGridlistDoc, CDocument)
	//{{AFX_MSG_MAP(CGridlistDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridlistDoc construction/destruction

CGridlistDoc::CGridlistDoc()
{
	// TODO: add one-time construction code here

}

CGridlistDoc::~CGridlistDoc()
{
}

BOOL CGridlistDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGridlistDoc serialization

void CGridlistDoc::Serialize(CArchive& ar)
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
// CGridlistDoc diagnostics

#ifdef _DEBUG
void CGridlistDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGridlistDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridlistDoc commands
