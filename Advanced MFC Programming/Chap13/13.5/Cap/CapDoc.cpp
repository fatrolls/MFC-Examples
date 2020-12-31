#include "stdafx.h"
#include "Cap.h"
#include "CapDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CCapDoc, CDocument)

BEGIN_MESSAGE_MAP(CCapDoc, CDocument)
	//{{AFX_MSG_MAP(CCapDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCapDoc::CCapDoc()
{
}

CCapDoc::~CCapDoc()
{
}

BOOL CCapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CCapDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CCapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
