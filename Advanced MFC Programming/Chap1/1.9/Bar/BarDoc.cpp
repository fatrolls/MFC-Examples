#include "stdafx.h"
#include "Bar.h"
#include "BarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CBarDoc, CDocument)
	//{{AFX_MSG_MAP(CBarDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBarDoc::CBarDoc()
{
}

CBarDoc::~CBarDoc()
{
}

BOOL CBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CBarDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
