// ex10cDoc.cpp : implementation of the CEx10cDoc class
//

#include "stdafx.h"
#include "ex10c.h"

#include "ex10cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10cDoc

IMPLEMENT_DYNCREATE(CEx10cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx10cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx10cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10cDoc construction/destruction

CEx10cDoc::CEx10cDoc()
{
	// TODO: add one-time construction code here

}

CEx10cDoc::~CEx10cDoc()
{
}

BOOL CEx10cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx10cDoc serialization

void CEx10cDoc::Serialize(CArchive& ar)
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
// CEx10cDoc diagnostics

#ifdef _DEBUG
void CEx10cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx10cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10cDoc commands
