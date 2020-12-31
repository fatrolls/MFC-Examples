#include "stdafx.h"
#include "Ini.h"
#include "IniDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CIniDoc, CDocument)

BEGIN_MESSAGE_MAP(CIniDoc, CDocument)
	//{{AFX_MSG_MAP(CIniDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CIniDoc::CIniDoc()
{
}

CIniDoc::~CIniDoc()
{
}

BOOL CIniDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CIniDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CIniDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIniDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

