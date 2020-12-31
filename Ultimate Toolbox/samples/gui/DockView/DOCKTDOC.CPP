// docktdoc.cpp : implementation of the CDocktestDoc class
//
// Docktest demo of Dockable Views functionality

#include "stdafx.h"
#include "docktest.h"

#include "docktdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocktestDoc

IMPLEMENT_DYNCREATE(CDocktestDoc, CDocument)

BEGIN_MESSAGE_MAP(CDocktestDoc, CDocument)
	//{{AFX_MSG_MAP(CDocktestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocktestDoc construction/destruction

CDocktestDoc::CDocktestDoc()
{
	// TODO: add one-time construction code here

}

CDocktestDoc::~CDocktestDoc()
{
}

BOOL CDocktestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDocktestDoc serialization

void CDocktestDoc::Serialize(CArchive& ar)
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
// CDocktestDoc diagnostics

#ifdef _DEBUG
void CDocktestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDocktestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDocktestDoc commands
