// ex11Doc.cpp : implementation of the CEx11Doc class
//

#include "stdafx.h"
#include "ex11.h"

#include "ex11Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11Doc

IMPLEMENT_DYNCREATE(CEx11Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx11Doc, CDocument)
	//{{AFX_MSG_MAP(CEx11Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11Doc construction/destruction

CEx11Doc::CEx11Doc()
{
	// TODO: add one-time construction code here

}

CEx11Doc::~CEx11Doc()
{
}

BOOL CEx11Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx11Doc serialization

void CEx11Doc::Serialize(CArchive& ar)
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
// CEx11Doc diagnostics

#ifdef _DEBUG
void CEx11Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx11Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11Doc commands
