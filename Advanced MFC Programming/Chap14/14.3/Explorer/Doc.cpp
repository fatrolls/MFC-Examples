#include "stdafx.h"
#include "Explorer.h"
#include "Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CExplorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CExplorerDoc, CDocument)
	//{{AFX_MSG_MAP(CExplorerDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CExplorerDoc::CExplorerDoc()
{
}

CExplorerDoc::~CExplorerDoc()
{
}

BOOL CExplorerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CExplorerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CExplorerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExplorerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

