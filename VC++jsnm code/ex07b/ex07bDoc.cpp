// ex07bDoc.cpp : implementation of the CEx07bDoc class
//

#include "stdafx.h"
#include "ex07b.h"

#include "ex07bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx07bDoc

IMPLEMENT_DYNCREATE(CEx07bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx07bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx07bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx07bDoc construction/destruction

CEx07bDoc::CEx07bDoc()
{
	// TODO: add one-time construction code here

}

CEx07bDoc::~CEx07bDoc()
{
}

BOOL CEx07bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx07bDoc serialization

void CEx07bDoc::Serialize(CArchive& ar)
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
// CEx07bDoc diagnostics

#ifdef _DEBUG
void CEx07bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx07bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx07bDoc commands
