// ex10bDoc.cpp : implementation of the CEx10bDoc class
//

#include "stdafx.h"
#include "ex10b.h"

#include "ex10bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10bDoc

IMPLEMENT_DYNCREATE(CEx10bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx10bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx10bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10bDoc construction/destruction

CEx10bDoc::CEx10bDoc()
{
	// TODO: add one-time construction code here

}

CEx10bDoc::~CEx10bDoc()
{
}

BOOL CEx10bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx10bDoc serialization

void CEx10bDoc::Serialize(CArchive& ar)
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
// CEx10bDoc diagnostics

#ifdef _DEBUG
void CEx10bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx10bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10bDoc commands
