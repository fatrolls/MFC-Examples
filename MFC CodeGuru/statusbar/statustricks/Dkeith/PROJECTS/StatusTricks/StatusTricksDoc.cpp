// StatusTricksDoc.cpp : implementation of the CStatusTricksDoc class
//

#include "stdafx.h"
#include "StatusTricks.h"

#include "StatusTricksDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksDoc

IMPLEMENT_DYNCREATE(CStatusTricksDoc, CDocument)

BEGIN_MESSAGE_MAP(CStatusTricksDoc, CDocument)
	//{{AFX_MSG_MAP(CStatusTricksDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksDoc construction/destruction

CStatusTricksDoc::CStatusTricksDoc()
{
	// TODO: add one-time construction code here

}

CStatusTricksDoc::~CStatusTricksDoc()
{
}

BOOL CStatusTricksDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStatusTricksDoc serialization

void CStatusTricksDoc::Serialize(CArchive& ar)
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
// CStatusTricksDoc diagnostics

#ifdef _DEBUG
void CStatusTricksDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStatusTricksDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusTricksDoc commands
