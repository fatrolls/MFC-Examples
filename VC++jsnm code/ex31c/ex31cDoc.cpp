// ex31cDoc.cpp : implementation of the CEx31cDoc class
//

#include "stdafx.h"
#include "ex31c.h"

#include "ex31cDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31cDoc

IMPLEMENT_DYNCREATE(CEx31cDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CEx31cDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CEx31cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx31cDoc construction/destruction

CEx31cDoc::CEx31cDoc()
{
	// TODO: add one-time construction code here

}

CEx31cDoc::~CEx31cDoc()
{
}

BOOL CEx31cDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CEx31cDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CEx31cCntrItem(preo, (CEx31cDoc*) this);
}

/////////////////////////////////////////////////////////////////////////////
// CEx31cDoc serialization

void CEx31cDoc::Serialize(CArchive& ar)
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
// CEx31cDoc diagnostics

#ifdef _DEBUG
void CEx31cDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CEx31cDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx31cDoc commands

BOOL CEx31cDoc::SaveModified() 
{
	return TRUE;
}
