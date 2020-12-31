// ex10dDoc.cpp : implementation of the CEx10dDoc class
//

#include "stdafx.h"
#include "ex10d.h"

#include "ex10dDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10dDoc

IMPLEMENT_DYNCREATE(CEx10dDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx10dDoc, CDocument)
	//{{AFX_MSG_MAP(CEx10dDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10dDoc construction/destruction

CEx10dDoc::CEx10dDoc()
{
	// TODO: add one-time construction code here

}

CEx10dDoc::~CEx10dDoc()
{
}

BOOL CEx10dDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx10dDoc serialization

void CEx10dDoc::Serialize(CArchive& ar)
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
// CEx10dDoc diagnostics

#ifdef _DEBUG
void CEx10dDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx10dDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10dDoc commands
