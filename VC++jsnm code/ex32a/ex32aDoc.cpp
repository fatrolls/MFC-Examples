// ex32aDoc.cpp : implementation of the CEx32aDoc class
//

#include "stdafx.h"
#include "ex32a.h"

#include "ex32aDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc

IMPLEMENT_DYNCREATE(CEx32aDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CEx32aDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CEx32aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc construction/destruction

CEx32aDoc::CEx32aDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

}

CEx32aDoc::~CEx32aDoc()
{
}

BOOL CEx32aDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CEx32aDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CEx32aCntrItem(preo, (CEx32aDoc*) this);
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc server implementation

COleServerItem* CEx32aDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CEx32aSrvrItem* pItem = new CEx32aSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

CDocObjectServer* CEx32aDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pSite)
{
	return new CDocObjectServer(this, pSite);
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc serialization

void CEx32aDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc diagnostics

#ifdef _DEBUG
void CEx32aDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CEx32aDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx32aDoc commands
