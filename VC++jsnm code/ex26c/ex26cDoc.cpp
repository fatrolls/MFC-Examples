// ex26cDoc.cpp : implementation of the CEx26cDoc class
//

#include "stdafx.h"
#include "ex26c.h"

#include "ex26cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26cDoc

IMPLEMENT_DYNCREATE(CEx26cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx26cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx26cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26cDoc construction/destruction

CEx26cDoc::CEx26cDoc()
{
	// TODO: add one-time construction code here

}

CEx26cDoc::~CEx26cDoc()
{
}

BOOL CEx26cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx26cDoc serialization

void CEx26cDoc::Serialize(CArchive& ar)
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
// CEx26cDoc diagnostics

#ifdef _DEBUG
void CEx26cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx26cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26cDoc commands
