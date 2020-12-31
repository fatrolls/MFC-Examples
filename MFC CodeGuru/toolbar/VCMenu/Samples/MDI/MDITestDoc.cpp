// MDITestDoc.cpp : implementation of the CMDITestDoc class
//

#include "stdafx.h"
#include "MDITest.h"

#include "MDITestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDITestDoc

IMPLEMENT_DYNCREATE(CMDITestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDITestDoc, CDocument)
	//{{AFX_MSG_MAP(CMDITestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDITestDoc construction/destruction

CMDITestDoc::CMDITestDoc()
{
	// TODO: add one-time construction code here

}

CMDITestDoc::~CMDITestDoc()
{
}

BOOL CMDITestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMDITestDoc serialization

void CMDITestDoc::Serialize(CArchive& ar)
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
// CMDITestDoc diagnostics

#ifdef _DEBUG
void CMDITestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDITestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDITestDoc commands
