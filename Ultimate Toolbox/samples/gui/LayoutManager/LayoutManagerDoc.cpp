// LayoutManagerDoc.cpp : implementation of the CLayoutManagerDoc class
//

#include "stdafx.h"
#include "LayoutManager.h"

#include "LayoutManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerDoc

IMPLEMENT_DYNCREATE(CLayoutManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CLayoutManagerDoc, CDocument)
	//{{AFX_MSG_MAP(CLayoutManagerDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerDoc construction/destruction

CLayoutManagerDoc::CLayoutManagerDoc()
{
}

CLayoutManagerDoc::~CLayoutManagerDoc()
{
}

BOOL CLayoutManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerDoc serialization

void CLayoutManagerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerDoc diagnostics

#ifdef _DEBUG
void CLayoutManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLayoutManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerDoc commands
