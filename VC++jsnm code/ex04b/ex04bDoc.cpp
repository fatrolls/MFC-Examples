// ex04bDoc.cpp : implementation of the CEx04bDoc class
//

#include "stdafx.h"
#include "ex04b.h"

#include "ex04bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04bDoc

IMPLEMENT_DYNCREATE(CEx04bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx04bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx04bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04bDoc construction/destruction

CEx04bDoc::CEx04bDoc()
{
	// TODO: add one-time construction code here

}

CEx04bDoc::~CEx04bDoc()
{
}

BOOL CEx04bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx04bDoc serialization

void CEx04bDoc::Serialize(CArchive& ar)
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
// CEx04bDoc diagnostics

#ifdef _DEBUG
void CEx04bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx04bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04bDoc commands
