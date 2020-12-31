// ex04aDoc.cpp : implementation of the CEx04aDoc class
//

#include "stdafx.h"
#include "ex04a.h"

#include "ex04aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04aDoc

IMPLEMENT_DYNCREATE(CEx04aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx04aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx04aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04aDoc construction/destruction

CEx04aDoc::CEx04aDoc()
{
	// TODO: add one-time construction code here

}

CEx04aDoc::~CEx04aDoc()
{
}

BOOL CEx04aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx04aDoc serialization

void CEx04aDoc::Serialize(CArchive& ar)
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
// CEx04aDoc diagnostics

#ifdef _DEBUG
void CEx04aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx04aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04aDoc commands
