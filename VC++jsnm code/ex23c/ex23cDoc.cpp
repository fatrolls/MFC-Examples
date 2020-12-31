// ex23cDoc.cpp : implementation of the CEx23cDoc class
//

#include "stdafx.h"
#include "ex23c.h"

#include "ex23cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx23cDoc

IMPLEMENT_DYNCREATE(CEx23cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx23cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx23cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx23cDoc construction/destruction

CEx23cDoc::CEx23cDoc()
{
	// TODO: add one-time construction code here

}

CEx23cDoc::~CEx23cDoc()
{
}

BOOL CEx23cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx23cDoc serialization

void CEx23cDoc::Serialize(CArchive& ar)
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
// CEx23cDoc diagnostics

#ifdef _DEBUG
void CEx23cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx23cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx23cDoc commands
