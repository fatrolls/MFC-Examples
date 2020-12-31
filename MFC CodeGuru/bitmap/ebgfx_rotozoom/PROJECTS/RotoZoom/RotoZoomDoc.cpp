// RotoZoomDoc.cpp : implementation of the CRotoZoomDoc class
//

#include "stdafx.h"
#include "RotoZoom.h"

#include "RotoZoomDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomDoc

IMPLEMENT_DYNCREATE(CRotoZoomDoc, CDocument)

BEGIN_MESSAGE_MAP(CRotoZoomDoc, CDocument)
	//{{AFX_MSG_MAP(CRotoZoomDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomDoc construction/destruction

CRotoZoomDoc::CRotoZoomDoc()
{
	// TODO: add one-time construction code here

}

CRotoZoomDoc::~CRotoZoomDoc()
{
}

BOOL CRotoZoomDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRotoZoomDoc serialization

void CRotoZoomDoc::Serialize(CArchive& ar)
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
// CRotoZoomDoc diagnostics

#ifdef _DEBUG
void CRotoZoomDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRotoZoomDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomDoc commands
