// ex21bDoc.cpp : implementation of the CEx21bDoc class
//

#include "stdafx.h"
#include "ex21b.h"

#include "ex21bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx21bDoc

IMPLEMENT_DYNCREATE(CEx21bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx21bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx21bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx21bDoc construction/destruction

CEx21bDoc::CEx21bDoc()
{
	// TODO: add one-time construction code here

}

CEx21bDoc::~CEx21bDoc()
{
}

BOOL CEx21bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx21bDoc serialization

void CEx21bDoc::Serialize(CArchive& ar)
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
// CEx21bDoc diagnostics

#ifdef _DEBUG
void CEx21bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx21bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx21bDoc commands
