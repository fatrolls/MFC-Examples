#include "stdafx.h"
#include "DB.h"
#include "DBDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDBDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBDoc, CDocument)
	//{{AFX_MSG_MAP(CDBDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDBDoc::CDBDoc()
{
}

CDBDoc::~CDBDoc()
{
}

BOOL CDBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CDBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CDBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
