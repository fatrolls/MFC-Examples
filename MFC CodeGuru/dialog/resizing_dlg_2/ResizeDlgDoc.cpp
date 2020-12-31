// ResizeDlgDoc.cpp : implementation of the CResizeDlgDoc class
//

#include "stdafx.h"
#include "ResizeDlg.h"

#include "ResizeDlgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgDoc

IMPLEMENT_DYNCREATE(CResizeDlgDoc, CDocument)

BEGIN_MESSAGE_MAP(CResizeDlgDoc, CDocument)
	//{{AFX_MSG_MAP(CResizeDlgDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgDoc construction/destruction

CResizeDlgDoc::CResizeDlgDoc()
{
	// TODO: add one-time construction code here

}

CResizeDlgDoc::~CResizeDlgDoc()
{
}

BOOL CResizeDlgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CResizeDlgDoc serialization

void CResizeDlgDoc::Serialize(CArchive& ar)
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
// CResizeDlgDoc diagnostics

#ifdef _DEBUG
void CResizeDlgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CResizeDlgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgDoc commands
