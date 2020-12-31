#include "stdafx.h"
#include "DDESrv.h"
#include "DDEDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDDESrvDoc, CDocument)

BEGIN_MESSAGE_MAP(CDDESrvDoc, CDocument)
	//{{AFX_MSG_MAP(CDDESrvDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDDESrvDoc::CDDESrvDoc()
{
}

CDDESrvDoc::~CDDESrvDoc()
{
}

BOOL CDDESrvDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	return TRUE;
}

void CDDESrvDoc::Serialize(CArchive& ar)
{
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

#ifdef _DEBUG
void CDDESrvDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDDESrvDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

