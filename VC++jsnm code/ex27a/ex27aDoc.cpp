// ex27aDoc.cpp : implementation of the CEx27aDoc class
//

#include "stdafx.h"
#include "ex27a.h"

#include "ex27aDoc.h"
#include "SrvrItem.h"
#include "TextDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc

IMPLEMENT_DYNCREATE(CEx27aDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CEx27aDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CEx27aDoc)
	ON_COMMAND(ID_MODIFY, OnModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc construction/destruction

CEx27aDoc::CEx27aDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

}

CEx27aDoc::~CEx27aDoc()
{
}

BOOL CEx27aDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_strText="Initial default text";

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc server implementation

COleServerItem* CEx27aDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CEx27aSrvrItem* pItem = new CEx27aSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc serialization

void CEx27aDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
      ar << m_strText;
    }
    else
    {
      ar >> m_strText;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc diagnostics

#ifdef _DEBUG
void CEx27aDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CEx27aDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27aDoc commands

void CEx27aDoc::OnModify() 
{
    CTextDialog dlg;
    dlg.m_strText = m_strText;
    if (dlg.DoModal() == IDOK) {
      m_strText = dlg.m_strText;
      UpdateAllViews(NULL); // Trigger CEx27aView::OnDraw
      UpdateAllItems(NULL); // Trigger CEx27aSrvrItem::OnDraw
      SetModifiedFlag();
    }
}
