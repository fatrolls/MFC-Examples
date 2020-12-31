// mymenuDoc.cpp : implementation of the CMymenuDoc class
//

#include "stdafx.h"
#include "mymenu.h"
#include "mymenuDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CMymenuDoc

IMPLEMENT_DYNCREATE(CMymenuDoc, CDocument)

BEGIN_MESSAGE_MAP(CMymenuDoc, CDocument)
	//{{AFX_MSG_MAP(CMymenuDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMymenuDoc construction/destruction

CMymenuDoc::CMymenuDoc()
{
}

CMymenuDoc::~CMymenuDoc()
{
}

BOOL CMymenuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMymenuDoc serialization

void CMymenuDoc::Serialize(CArchive& ar)
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
// CMymenuDoc diagnostics

#ifdef _DEBUG
void CMymenuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMymenuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMymenuDoc commands
