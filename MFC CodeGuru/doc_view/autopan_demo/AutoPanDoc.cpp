// AutoPanDoc.cpp : implementation of the CAutoPanDoc class
//

#include "stdafx.h"
#include "AutoPan.h"

#include "AutoPanDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoPanDoc

IMPLEMENT_DYNCREATE(CAutoPanDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoPanDoc, CDocument)
	//{{AFX_MSG_MAP(CAutoPanDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoPanDoc construction/destruction

CAutoPanDoc::CAutoPanDoc()
{
	// TODO: add one-time construction code here

}

CAutoPanDoc::~CAutoPanDoc()
{
}

BOOL CAutoPanDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAutoPanDoc serialization

void CAutoPanDoc::Serialize(CArchive& ar)
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
// CAutoPanDoc diagnostics

#ifdef _DEBUG
void CAutoPanDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoPanDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoPanDoc commands
