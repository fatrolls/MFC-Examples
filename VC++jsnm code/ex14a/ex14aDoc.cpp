// ex14aDoc.cpp : implementation of the CEx14aDoc class
//

#include "stdafx.h"
#include "ex14a.h"

#include "ex14aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14aDoc

IMPLEMENT_DYNCREATE(CEx14aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx14aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx14aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14aDoc construction/destruction

CEx14aDoc::CEx14aDoc()
{
	// TODO: add one-time construction code here

}

CEx14aDoc::~CEx14aDoc()
{
}

BOOL CEx14aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx14aDoc serialization

void CEx14aDoc::Serialize(CArchive& ar)
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
// CEx14aDoc diagnostics

#ifdef _DEBUG
void CEx14aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx14aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14aDoc commands
