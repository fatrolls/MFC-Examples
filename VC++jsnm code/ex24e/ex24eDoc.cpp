// ex24eDoc.cpp : implementation of the CEx24eDoc class
//

#include "stdafx.h"
#include "ex24e.h"

#include "ex24eDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24eDoc

IMPLEMENT_DYNCREATE(CEx24eDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx24eDoc, CDocument)
	//{{AFX_MSG_MAP(CEx24eDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24eDoc construction/destruction

CEx24eDoc::CEx24eDoc()
{
	// TODO: add one-time construction code here

}

CEx24eDoc::~CEx24eDoc()
{
}

BOOL CEx24eDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx24eDoc serialization

void CEx24eDoc::Serialize(CArchive& ar)
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
// CEx24eDoc diagnostics

#ifdef _DEBUG
void CEx24eDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx24eDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx24eDoc commands
