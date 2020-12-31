// GridViewDemoDoc.cpp : implementation of the CGridViewDemoDoc class
//

#include "stdafx.h"
#include "GridViewDemo.h"

#include "GridViewDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoDoc

IMPLEMENT_DYNCREATE(CGridViewDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CGridViewDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CGridViewDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoDoc construction/destruction

CGridViewDemoDoc::CGridViewDemoDoc()
{
	// TODO: add one-time construction code here

}

CGridViewDemoDoc::~CGridViewDemoDoc()
{
}

BOOL CGridViewDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoDoc serialization

void CGridViewDemoDoc::Serialize(CArchive& ar)
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
// CGridViewDemoDoc diagnostics

#ifdef _DEBUG
void CGridViewDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGridViewDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoDoc commands
