// ButtonDoc.cpp : implementation of the CButtonDoc class
//

#include "stdafx.h"
#include "Button.h"

#include "ButtonDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonDoc

IMPLEMENT_DYNCREATE(CButtonDoc, CDocument)

BEGIN_MESSAGE_MAP(CButtonDoc, CDocument)
	//{{AFX_MSG_MAP(CButtonDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonDoc construction/destruction

CButtonDoc::CButtonDoc()
{
	// TODO: add one-time construction code here

}

CButtonDoc::~CButtonDoc()
{
}

BOOL CButtonDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CButtonDoc serialization

void CButtonDoc::Serialize(CArchive& ar)
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
// CButtonDoc diagnostics

#ifdef _DEBUG
void CButtonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CButtonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CButtonDoc commands
