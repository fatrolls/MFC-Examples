// ex08bDoc.cpp : implementation of the CEx08bDoc class
//

#include "stdafx.h"
#include "ex08b.h"

#include "ex08bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx08bDoc

IMPLEMENT_DYNCREATE(CEx08bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx08bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx08bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx08bDoc construction/destruction

CEx08bDoc::CEx08bDoc()
{
	// TODO: add one-time construction code here

}

CEx08bDoc::~CEx08bDoc()
{
}

BOOL CEx08bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx08bDoc serialization

void CEx08bDoc::Serialize(CArchive& ar)
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
// CEx08bDoc diagnostics

#ifdef _DEBUG
void CEx08bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx08bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx08bDoc commands
