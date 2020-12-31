// ToolTipDoc.cpp : implementation of the CToolTipDoc class
//

#include "stdafx.h"
#include "ToolTip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipDoc

IMPLEMENT_DYNCREATE(CToolTipDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolTipDoc, CDocument)
	//{{AFX_MSG_MAP(CToolTipDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipDoc construction/destruction

CToolTipDoc::CToolTipDoc()
{
	// TODO: add one-time construction code here

}

CToolTipDoc::~CToolTipDoc()
{
}

BOOL CToolTipDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CToolTipDoc serialization

void CToolTipDoc::Serialize(CArchive& ar)
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
// CToolTipDoc diagnostics

#ifdef _DEBUG
void CToolTipDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolTipDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolTipDoc commands
