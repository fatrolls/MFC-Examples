// SyntaxColorDemoDoc.cpp : implementation of the CSyntaxColorDemoDoc class
//

#include "stdafx.h"
#include "SyntaxColorDemo.h"

#include "SyntaxColorDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoDoc

IMPLEMENT_DYNCREATE(CSyntaxColorDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSyntaxColorDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CSyntaxColorDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoDoc construction/destruction

CSyntaxColorDemoDoc::CSyntaxColorDemoDoc()
{
	// TODO: add one-time construction code here

}

CSyntaxColorDemoDoc::~CSyntaxColorDemoDoc()
{
}

BOOL CSyntaxColorDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoDoc serialization

void CSyntaxColorDemoDoc::Serialize(CArchive& ar)
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
// CSyntaxColorDemoDoc diagnostics

#ifdef _DEBUG
void CSyntaxColorDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSyntaxColorDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSyntaxColorDemoDoc commands
