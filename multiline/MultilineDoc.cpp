// MultilineDoc.cpp : implementation of the CMultilineDoc class
//

#include "stdafx.h"
#include "Multiline.h"

#include "MultilineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultilineDoc

IMPLEMENT_DYNCREATE(CMultilineDoc, CDocument)

BEGIN_MESSAGE_MAP(CMultilineDoc, CDocument)
	//{{AFX_MSG_MAP(CMultilineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultilineDoc construction/destruction

CMultilineDoc::CMultilineDoc()
{
	// TODO: add one-time construction code here

}

CMultilineDoc::~CMultilineDoc()
{
}

BOOL CMultilineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMultilineDoc serialization

void CMultilineDoc::Serialize(CArchive& ar)
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
// CMultilineDoc diagnostics

#ifdef _DEBUG
void CMultilineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultilineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultilineDoc commands
