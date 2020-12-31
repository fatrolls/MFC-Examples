// ex24dDoc.cpp : implementation of the CEx24dDoc class
//

#include "stdafx.h"
#include "ex24d.h"

#include "ex24dDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24dDoc

IMPLEMENT_DYNCREATE(CEx24dDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx24dDoc, CDocument)
	//{{AFX_MSG_MAP(CEx24dDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24dDoc construction/destruction

CEx24dDoc::CEx24dDoc()
{
	// TODO: add one-time construction code here

}

CEx24dDoc::~CEx24dDoc()
{
}

BOOL CEx24dDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx24dDoc serialization

void CEx24dDoc::Serialize(CArchive& ar)
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
// CEx24dDoc diagnostics

#ifdef _DEBUG
void CEx24dDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx24dDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx24dDoc commands
