// LBTabDemoDoc.cpp : implementation of the CLBTabDemoDoc class
//

#include "stdafx.h"
#include "LBTabDemo.h"

#include "LBTabDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoDoc

IMPLEMENT_DYNCREATE(CLBTabDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CLBTabDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CLBTabDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoDoc construction/destruction

CLBTabDemoDoc::CLBTabDemoDoc()
{
	// TODO: add one-time construction code here

}

CLBTabDemoDoc::~CLBTabDemoDoc()
{
}

BOOL CLBTabDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoDoc serialization

void CLBTabDemoDoc::Serialize(CArchive& ar)
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
// CLBTabDemoDoc diagnostics

#ifdef _DEBUG
void CLBTabDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLBTabDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoDoc commands
