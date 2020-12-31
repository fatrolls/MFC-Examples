// HyperbarDemoDoc.cpp : implementation of the CHyperbarDemoDoc class
//

#include "stdafx.h"
#include "HyperbarDemo.h"

#include "HyperbarDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoDoc

IMPLEMENT_DYNCREATE(CHyperbarDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CHyperbarDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CHyperbarDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoDoc construction/destruction

CHyperbarDemoDoc::CHyperbarDemoDoc()
{
	// TODO: add one-time construction code here

}

CHyperbarDemoDoc::~CHyperbarDemoDoc()
{
}

BOOL CHyperbarDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoDoc serialization

void CHyperbarDemoDoc::Serialize(CArchive& ar)
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
// CHyperbarDemoDoc diagnostics

#ifdef _DEBUG
void CHyperbarDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHyperbarDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoDoc commands
