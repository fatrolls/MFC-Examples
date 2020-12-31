// ex04cDoc.cpp : implementation of the CEx04cDoc class
//

#include "stdafx.h"
#include "ex04c.h"

#include "ex04cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04cDoc

IMPLEMENT_DYNCREATE(CEx04cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx04cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx04cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04cDoc construction/destruction

CEx04cDoc::CEx04cDoc()
{
	// TODO: add one-time construction code here

}

CEx04cDoc::~CEx04cDoc()
{
}

BOOL CEx04cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx04cDoc serialization

void CEx04cDoc::Serialize(CArchive& ar)
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
// CEx04cDoc diagnostics

#ifdef _DEBUG
void CEx04cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx04cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04cDoc commands
