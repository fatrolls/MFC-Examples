#include "stdafx.h"
#include "Spw.h"
#include "SpwDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSpwDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpwDoc, CDocument)
	//{{AFX_MSG_MAP(CSpwDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSpwDoc::CSpwDoc()
{
}

CSpwDoc::~CSpwDoc()
{
}

BOOL CSpwDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())return FALSE;

	return TRUE;
}

void CSpwDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CSpwDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpwDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
