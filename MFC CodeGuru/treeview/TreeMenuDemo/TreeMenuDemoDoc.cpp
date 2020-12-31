// TreeMenuDemoDoc.cpp : implementation of the CTreeMenuDemoDoc class
//

#include "stdafx.h"
#include "TreeMenuDemo.h"

#include "TreeMenuDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoDoc

IMPLEMENT_DYNCREATE(CTreeMenuDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CTreeMenuDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CTreeMenuDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoDoc construction/destruction

CTreeMenuDemoDoc::CTreeMenuDemoDoc()
{
	// TODO: add one-time construction code here

}

CTreeMenuDemoDoc::~CTreeMenuDemoDoc()
{
}

BOOL CTreeMenuDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoDoc serialization

void CTreeMenuDemoDoc::Serialize(CArchive& ar)
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
// CTreeMenuDemoDoc diagnostics

#ifdef _DEBUG
void CTreeMenuDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTreeMenuDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoDoc commands
