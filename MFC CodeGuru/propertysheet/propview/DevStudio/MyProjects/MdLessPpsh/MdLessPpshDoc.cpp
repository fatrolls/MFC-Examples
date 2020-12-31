// MdLessPpshDoc.cpp : implementation of the CMdLessPpshDoc class
//

#include "stdafx.h"
#include "MdLessPpsh.h"

#include "MdLessPpshDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshDoc

IMPLEMENT_DYNCREATE(CMdLessPpshDoc, CDocument)

BEGIN_MESSAGE_MAP(CMdLessPpshDoc, CDocument)
	//{{AFX_MSG_MAP(CMdLessPpshDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshDoc construction/destruction

CMdLessPpshDoc::CMdLessPpshDoc()
{
	// TODO: add one-time construction code here

}

CMdLessPpshDoc::~CMdLessPpshDoc()
{
}

BOOL CMdLessPpshDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshDoc serialization

void CMdLessPpshDoc::Serialize(CArchive& ar)
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
// CMdLessPpshDoc diagnostics

#ifdef _DEBUG
void CMdLessPpshDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMdLessPpshDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshDoc commands
