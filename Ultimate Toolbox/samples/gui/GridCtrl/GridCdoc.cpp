// GridCdoc.cpp : implementation of the CGridCtrlDoc class
//

#include "stdafx.h"
#include "GridCtrl.h"

#include "GridCdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDoc

IMPLEMENT_DYNCREATE(CGridCtrlDoc, CDocument)

BEGIN_MESSAGE_MAP(CGridCtrlDoc, CDocument)
	//{{AFX_MSG_MAP(CGridCtrlDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDoc construction/destruction

CGridCtrlDoc::CGridCtrlDoc()
{
	// TODO: add one-time construction code here

}

CGridCtrlDoc::~CGridCtrlDoc()
{
}

BOOL CGridCtrlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDoc serialization

void CGridCtrlDoc::Serialize(CArchive& ar)
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
// CGridCtrlDoc diagnostics

#ifdef _DEBUG
void CGridCtrlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGridCtrlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDoc commands
