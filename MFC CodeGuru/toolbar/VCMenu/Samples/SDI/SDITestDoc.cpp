// SDITestDoc.cpp : implementation of the CSDITestDoc class
//

#include "stdafx.h"
#include "SDITest.h"

#include "SDITestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDITestDoc

IMPLEMENT_DYNCREATE(CSDITestDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDITestDoc, CDocument)
	//{{AFX_MSG_MAP(CSDITestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDITestDoc construction/destruction

CSDITestDoc::CSDITestDoc()
{
	// TODO: add one-time construction code here

}

CSDITestDoc::~CSDITestDoc()
{
}

BOOL CSDITestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSDITestDoc serialization

void CSDITestDoc::Serialize(CArchive& ar)
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
// CSDITestDoc diagnostics

#ifdef _DEBUG
void CSDITestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDITestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDITestDoc commands
