#include "stdafx.h"
#include "MsgRcv.h"

#include "RcvDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMsgRcvDoc, CDocument)

BEGIN_MESSAGE_MAP(CMsgRcvDoc, CDocument)
	//{{AFX_MSG_MAP(CMsgRcvDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMsgRcvDoc::CMsgRcvDoc()
{
}

CMsgRcvDoc::~CMsgRcvDoc()
{
}

BOOL CMsgRcvDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())return FALSE;
	return TRUE;
}

void CMsgRcvDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CMsgRcvDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMsgRcvDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
