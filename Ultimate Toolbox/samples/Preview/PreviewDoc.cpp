// PreviewDoc.cpp : implementation of the CPreviewDoc class
//

#include "stdafx.h"
#include "Preview.h"

#include "PreviewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewDoc

IMPLEMENT_DYNCREATE(CPreviewDoc, CDocument)

BEGIN_MESSAGE_MAP(CPreviewDoc, CDocument)
	//{{AFX_MSG_MAP(CPreviewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewDoc construction/destruction

CPreviewDoc::CPreviewDoc()
{
	// TODO: add one-time construction code here

}

CPreviewDoc::~CPreviewDoc()
{
}

BOOL CPreviewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPreviewDoc serialization

void CPreviewDoc::Serialize(CArchive& ar)
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
// CPreviewDoc diagnostics

#ifdef _DEBUG
void CPreviewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPreviewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPreviewDoc commands
