// ex06bDoc.cpp : implementation of the CEx06bDoc class
//

#include "stdafx.h"
#include "ex06b.h"

#include "ex06bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx06bDoc

IMPLEMENT_DYNCREATE(CEx06bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx06bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx06bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx06bDoc construction/destruction

CEx06bDoc::CEx06bDoc()
{
	// TODO: add one-time construction code here

}

CEx06bDoc::~CEx06bDoc()
{
}

BOOL CEx06bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx06bDoc serialization

void CEx06bDoc::Serialize(CArchive& ar)
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
// CEx06bDoc diagnostics

#ifdef _DEBUG
void CEx06bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx06bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx06bDoc commands
