#include "stdafx.h"
#include "Hook.h"
#include "HookDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CHookDoc, CDocument)

BEGIN_MESSAGE_MAP(CHookDoc, CDocument)
	//{{AFX_MSG_MAP(CHookDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CHookDoc::CHookDoc()
{
}

CHookDoc::~CHookDoc()
{
}

BOOL CHookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CHookDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CHookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
