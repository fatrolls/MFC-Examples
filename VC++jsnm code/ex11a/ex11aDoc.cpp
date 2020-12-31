// ex11aDoc.cpp : implementation of the CEx11aDoc class
//

#include "stdafx.h"
#include "ex11a.h"

#include "ex11aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11aDoc

IMPLEMENT_DYNCREATE(CEx11aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx11aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx11aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11aDoc construction/destruction

CEx11aDoc::CEx11aDoc()
{
	// TODO: add one-time construction code here

}

CEx11aDoc::~CEx11aDoc()
{
}

BOOL CEx11aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx11aDoc serialization

void CEx11aDoc::Serialize(CArchive& ar)
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
// CEx11aDoc diagnostics

#ifdef _DEBUG
void CEx11aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx11aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11aDoc commands
