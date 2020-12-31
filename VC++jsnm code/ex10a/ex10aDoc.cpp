// ex10aDoc.cpp : implementation of the CEx10aDoc class
//

#include "stdafx.h"
#include "ex10a.h"

#include "ex10aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10aDoc

IMPLEMENT_DYNCREATE(CEx10aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx10aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx10aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10aDoc construction/destruction

CEx10aDoc::CEx10aDoc()
{
	// TODO: add one-time construction code here

}

CEx10aDoc::~CEx10aDoc()
{
}

BOOL CEx10aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx10aDoc serialization

void CEx10aDoc::Serialize(CArchive& ar)
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
// CEx10aDoc diagnostics

#ifdef _DEBUG
void CEx10aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx10aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10aDoc commands
