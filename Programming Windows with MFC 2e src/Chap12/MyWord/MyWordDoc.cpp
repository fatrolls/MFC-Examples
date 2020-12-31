// MyWordDoc.cpp : implementation of the CMyWordDoc class
//

#include "stdafx.h"
#include "MyWord.h"

#include "MyWordDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWordDoc

IMPLEMENT_DYNCREATE(CMyWordDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CMyWordDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CMyWordDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyWordDoc construction/destruction

CMyWordDoc::CMyWordDoc()
{
}

CMyWordDoc::~CMyWordDoc()
{
}

BOOL CMyWordDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;
	return TRUE;
}

CRichEditCntrItem* CMyWordDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CMyWordCntrItem(preo, (CMyWordDoc*) this);
}

/////////////////////////////////////////////////////////////////////////////
// CMyWordDoc serialization

void CMyWordDoc::Serialize(CArchive& ar)
{
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMyWordDoc diagnostics

#ifdef _DEBUG
void CMyWordDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CMyWordDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyWordDoc commands
