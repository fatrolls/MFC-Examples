// OutLookStyleDoc.cpp : implementation of the COutLookStyleDoc class
//

#include "stdafx.h"
#include "OutLookStyle.h"

#include "OutLookStyleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleDoc

IMPLEMENT_DYNCREATE(COutLookStyleDoc, CDocument)

BEGIN_MESSAGE_MAP(COutLookStyleDoc, CDocument)
	//{{AFX_MSG_MAP(COutLookStyleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleDoc construction/destruction

COutLookStyleDoc::COutLookStyleDoc()
{
	// TODO: add one-time construction code here

}

COutLookStyleDoc::~COutLookStyleDoc()
{
}

BOOL COutLookStyleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COutLookStyleDoc serialization

void COutLookStyleDoc::Serialize(CArchive& ar)
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
// COutLookStyleDoc diagnostics

#ifdef _DEBUG
void COutLookStyleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COutLookStyleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleDoc commands
