#include "stdafx.h"
#include "Once.h"
#include "OnceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(COnceDoc, CDocument)

BEGIN_MESSAGE_MAP(COnceDoc, CDocument)
	//{{AFX_MSG_MAP(COnceDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

COnceDoc::COnceDoc()
{
}

COnceDoc::~COnceDoc()
{
}

BOOL COnceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void COnceDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void COnceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COnceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
