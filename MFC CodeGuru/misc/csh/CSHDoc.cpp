// CSHDoc.cpp : implementation of the CCSHDoc class
//

#include "stdafx.h"
#include "CSH.h"

#include "CSHDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSHDoc

IMPLEMENT_DYNCREATE(CCSHDoc, CDocument)

BEGIN_MESSAGE_MAP(CCSHDoc, CDocument)
	//{{AFX_MSG_MAP(CCSHDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSHDoc construction/destruction

CCSHDoc::CCSHDoc()
{
	// TODO: add one-time construction code here

}

CCSHDoc::~CCSHDoc()
{
}

BOOL CCSHDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCSHDoc serialization

void CCSHDoc::Serialize(CArchive& ar)
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
// CCSHDoc diagnostics

#ifdef _DEBUG
void CCSHDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCSHDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCSHDoc commands
