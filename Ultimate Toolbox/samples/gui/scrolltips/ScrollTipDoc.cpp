// ScrollTipDoc.cpp : implementation of the CScrollTipDoc class
//

#include "stdafx.h"
#include "ScrollTipDemo.h"

#include "ScrollTipDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollTipDoc

IMPLEMENT_DYNCREATE(CScrollTipDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CScrollTipDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CScrollTipDoc)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollTipDoc construction/destruction

CScrollTipDoc::CScrollTipDoc()
	{
	// TODO: add one-time construction code here
	
	}

CScrollTipDoc::~CScrollTipDoc()
	{
	}

BOOL CScrollTipDoc::OnNewDocument()
	{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;
	
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
	}

CRichEditCntrItem* CScrollTipDoc::CreateClientItem(REOBJECT* preo) const
	{
	// cast away constness of this
	return new CScrollTipDemoCntrItem(preo, (CScrollTipDoc*) this);
	}

/////////////////////////////////////////////////////////////////////////////
// CScrollTipDoc serialization

void CScrollTipDoc::Serialize(CArchive& ar)
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
// CScrollTipDoc diagnostics

#ifdef _DEBUG
void CScrollTipDoc::AssertValid() const
	{
	CRichEditDoc::AssertValid();
	}

void CScrollTipDoc::Dump(CDumpContext& dc) const
	{
	CRichEditDoc::Dump(dc);
	}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScrollTipDoc commands

BOOL CScrollTipDoc::SaveModified() 
	{
	// ... Never ask to save
	SetModifiedFlag(FALSE);
	
	return CRichEditDoc::SaveModified();
	}
