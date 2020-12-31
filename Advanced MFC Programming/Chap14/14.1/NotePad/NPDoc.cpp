#include "stdafx.h"
#include "NotePad.h"

#include "NPDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CNotePadDoc, CDocument)

BEGIN_MESSAGE_MAP(CNotePadDoc, CDocument)
	//{{AFX_MSG_MAP(CNotePadDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CNotePadDoc::CNotePadDoc()
{
}

CNotePadDoc::~CNotePadDoc()
{
}

BOOL CNotePadDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())return FALSE;
	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);
	return TRUE;
}

void CNotePadDoc::Serialize(CArchive& ar)
{
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

#ifdef _DEBUG
void CNotePadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNotePadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
