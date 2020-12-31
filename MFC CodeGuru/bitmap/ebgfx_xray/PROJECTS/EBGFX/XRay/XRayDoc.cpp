// XRayDoc.cpp : implementation of the CXRayDoc class
//

#include "stdafx.h"
#include "XRay.h"

#include "XRayDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXRayDoc

IMPLEMENT_DYNCREATE(CXRayDoc, CDocument)

BEGIN_MESSAGE_MAP(CXRayDoc, CDocument)
	//{{AFX_MSG_MAP(CXRayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXRayDoc construction/destruction

CXRayDoc::CXRayDoc()
{
	// TODO: add one-time construction code here

}

CXRayDoc::~CXRayDoc()
{
}

BOOL CXRayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXRayDoc serialization

void CXRayDoc::Serialize(CArchive& ar)
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
// CXRayDoc diagnostics

#ifdef _DEBUG
void CXRayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXRayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXRayDoc commands
