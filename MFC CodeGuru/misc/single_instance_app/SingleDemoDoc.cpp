// SingleDemoDoc.cpp : implementation of the CSingleDemoDoc class
//

#include "stdafx.h"
#include "SingleDemo.h"

#include "SingleDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoDoc

IMPLEMENT_DYNCREATE(CSingleDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSingleDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CSingleDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoDoc construction/destruction

CSingleDemoDoc::CSingleDemoDoc()
{
	// TODO: add one-time construction code here

}

CSingleDemoDoc::~CSingleDemoDoc()
{
}

BOOL CSingleDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoDoc serialization

void CSingleDemoDoc::Serialize(CArchive& ar)
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
// CSingleDemoDoc diagnostics

#ifdef _DEBUG
void CSingleDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSingleDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoDoc commands
