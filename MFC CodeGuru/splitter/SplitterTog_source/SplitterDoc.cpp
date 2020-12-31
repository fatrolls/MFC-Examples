// SplitterDoc.cpp : implementation of the CSplitterDoc class
//

#include "stdafx.h"
#include "Splitter.h"

#include "SplitterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitterDoc

IMPLEMENT_DYNCREATE(CSplitterDoc, CDocument)

BEGIN_MESSAGE_MAP(CSplitterDoc, CDocument)
	//{{AFX_MSG_MAP(CSplitterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitterDoc construction/destruction

CSplitterDoc::CSplitterDoc()
{
	// TODO: add one-time construction code here

}

CSplitterDoc::~CSplitterDoc()
{
}

BOOL CSplitterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSplitterDoc serialization

void CSplitterDoc::Serialize(CArchive& ar)
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
// CSplitterDoc diagnostics

#ifdef _DEBUG
void CSplitterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSplitterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplitterDoc commands
