// FullScreenDoc.cpp : implementation of the CFullScreenDoc class
//

#include "stdafx.h"
#include "FullScreen.h"

#include "FullScreenDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDoc

IMPLEMENT_DYNCREATE(CFullScreenDoc, CDocument)

BEGIN_MESSAGE_MAP(CFullScreenDoc, CDocument)
	//{{AFX_MSG_MAP(CFullScreenDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDoc construction/destruction

CFullScreenDoc::CFullScreenDoc()
{
	// TODO: add one-time construction code here

}

CFullScreenDoc::~CFullScreenDoc()
{
}

BOOL CFullScreenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFullScreenDoc serialization

void CFullScreenDoc::Serialize(CArchive& ar)
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
// CFullScreenDoc diagnostics

#ifdef _DEBUG
void CFullScreenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFullScreenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDoc commands
