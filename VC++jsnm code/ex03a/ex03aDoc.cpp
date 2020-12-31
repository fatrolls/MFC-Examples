// ex03aDoc.cpp : implementation of the CEx03aDoc class
//

#include "stdafx.h"
#include "ex03a.h"

#include "ex03aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx03aDoc

IMPLEMENT_DYNCREATE(CEx03aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx03aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx03aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx03aDoc construction/destruction

CEx03aDoc::CEx03aDoc()
{
	// TODO: add one-time construction code here

}

CEx03aDoc::~CEx03aDoc()
{
}

BOOL CEx03aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx03aDoc serialization

void CEx03aDoc::Serialize(CArchive& ar)
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
// CEx03aDoc diagnostics

#ifdef _DEBUG
void CEx03aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx03aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx03aDoc commands
