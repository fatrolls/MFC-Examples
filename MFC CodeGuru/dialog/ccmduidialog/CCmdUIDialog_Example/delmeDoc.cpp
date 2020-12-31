// delmeDoc.cpp : implementation of the CDelmeDoc class
//

#include "stdafx.h"
#include "delme.h"

#include "delmeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelmeDoc

IMPLEMENT_DYNCREATE(CDelmeDoc, CDocument)

BEGIN_MESSAGE_MAP(CDelmeDoc, CDocument)
	//{{AFX_MSG_MAP(CDelmeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelmeDoc construction/destruction

CDelmeDoc::CDelmeDoc()
{
	// TODO: add one-time construction code here

}

CDelmeDoc::~CDelmeDoc()
{
}

BOOL CDelmeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDelmeDoc serialization

void CDelmeDoc::Serialize(CArchive& ar)
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
// CDelmeDoc diagnostics

#ifdef _DEBUG
void CDelmeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDelmeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDelmeDoc commands
