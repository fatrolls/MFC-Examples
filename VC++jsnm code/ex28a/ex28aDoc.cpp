// ex28aDoc.cpp : implementation of the CEx28aDoc class
//

#include "stdafx.h"
#include "ex28a.h"
#include "ex28aSet.h"
#include "ex28aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc

IMPLEMENT_DYNCREATE(CEx28aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx28aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx28aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc construction/destruction

CEx28aDoc::CEx28aDoc()
{
	// TODO: add one-time construction code here

}

CEx28aDoc::~CEx28aDoc()
{
}

BOOL CEx28aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc serialization

void CEx28aDoc::Serialize(CArchive& ar)
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
// CEx28aDoc diagnostics

#ifdef _DEBUG
void CEx28aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx28aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28aDoc commands
