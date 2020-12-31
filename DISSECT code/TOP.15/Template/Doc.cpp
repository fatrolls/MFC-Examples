// $$doc_ifile$$.cpp : implementation of the $$DOC_CLASS$$ class
//

#include "stdafx.h"
#include "$$root$$.h"

$$IF(CRecordView || CDaoRecordView)
#include "$$recset_hfile$$.h"
$$ENDIF
#include "$$doc_hfile$$.h"
$$IF(CONTAINER || CONTAINER_SERVER)
#include "$$cntritem_hfile$$.h"
$$ENDIF
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
#include "$$srvritem_hfile$$.h"
$$ENDIF

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$DOC_CLASS$$

IMPLEMENT_DYNCREATE($$DOC_CLASS$$, $$DOC_BASE_CLASS$$)

BEGIN_MESSAGE_MAP($$DOC_CLASS$$, $$DOC_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$DOC_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
$$ENDIF
	//}}AFX_MSG_MAP
$$IF(CONTAINER || CONTAINER_SERVER)
	// Enable default OLE container implementation
$$IF(!CRichEditView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, $$DOC_BASE_CLASS$$::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, $$DOC_BASE_CLASS$$::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, $$DOC_BASE_CLASS$$::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, $$DOC_BASE_CLASS$$::OnEditConvert)
$$ENDIF //!CRichEditView
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, $$DOC_BASE_CLASS$$::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, $$DOC_BASE_CLASS$$::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, $$DOC_BASE_CLASS$$::OnUpdateObjectVerbMenu)
$$ENDIF
$$IF(MAPI)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
$$ENDIF //MAPI
END_MESSAGE_MAP()

$$IF(AUTOMATION)
BEGIN_DISPATCH_MAP($$DOC_CLASS$$, $$DOC_BASE_CLASS$$)
	//{{AFX_DISPATCH_MAP($$DOC_CLASS$$)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

$$IF(VERBOSE)
// Note: we add support for IID_I$$Safe_root$$ to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {$$DISPIID_CLSID_ODL$$}
$$ENDIF //VERBOSE
static const IID IID_I$$Safe_root$$ =
$$DISPIID_CLSID$$;

BEGIN_INTERFACE_MAP($$DOC_CLASS$$, $$DOC_BASE_CLASS$$)
	INTERFACE_PART($$DOC_CLASS$$, IID_I$$Safe_root$$, Dispatch)
END_INTERFACE_MAP()

$$ENDIF //AUTOMATION
/////////////////////////////////////////////////////////////////////////////
// $$DOC_CLASS$$ construction/destruction

$$DOC_CLASS$$::$$DOC_CLASS$$()
{
$$IF(COMPFILE)
$$IF(VERBOSE)
	// Use OLE compound files
$$ENDIF
	EnableCompoundFile();

$$ENDIF //COMPFILE
$$IF(VERBOSE)
	// TODO: add one-time construction code here

$$ENDIF
$$IF(AUTOMATION)
	EnableAutomation();

	AfxOleLockApp();
$$ENDIF
}

$$DOC_CLASS$$::~$$DOC_CLASS$$()
{
$$IF(AUTOMATION)
	AfxOleUnlockApp();
$$ENDIF
}

BOOL $$DOC_CLASS$$::OnNewDocument()
{
	if (!$$DOC_BASE_CLASS$$::OnNewDocument())
		return FALSE;
$$IF(PROJTYPE_SDI)
$$IF(CEditView)

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);
$$ENDIF //CEditView
$$ENDIF //PROJTYPE_SDI

$$IF(VERBOSE)
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

$$ENDIF
	return TRUE;
}
$$IF(CRichEditView)

$$CNTRITEM_BASE_CLASS$$* $$DOC_CLASS$$::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new $$CNTRITEM_CLASS$$(preo, ($$DOC_CLASS$$*) this);
}
$$ENDIF //CRichEditView
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)

/////////////////////////////////////////////////////////////////////////////
// $$DOC_CLASS$$ server implementation

COleServerItem* $$DOC_CLASS$$::OnGetEmbeddedItem()
{
$$IF(VERBOSE)
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

$$ENDIF
	$$SRVRITEM_CLASS$$* pItem = new $$SRVRITEM_CLASS$$(this);
	ASSERT_VALID(pItem);
	return pItem;
}
$$ENDIF
$$IF(ACTIVE_DOC_SERVER)

/////////////////////////////////////////////////////////////////////////////
// $$DOC_CLASS$$ ActiveX Document server implementation

CDocObjectServer *$$DOC_CLASS$$::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new CDocObjectServer(this, pDocSite);
}
$$ENDIF


$$IF(!DB_NO_FILE)

/////////////////////////////////////////////////////////////////////////////
// $$DOC_CLASS$$ serialization

void $$DOC_CLASS$$::Serialize(CArchive& ar)
{
$$IF(CEditView)
$$IF(VERBOSE)
	// CEditView contains an edit control which handles all serialization
$$ENDIF //VERBOSE
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
$$ELSE
	if (ar.IsStoring())
	{
$$IF(VERBOSE)
		// TODO: add storing code here
$$ENDIF
	}
	else
	{
$$IF(VERBOSE)
		// TODO: add loading code here
$$ENDIF
	}
$$IF(CONTAINER || CONTAINER_SERVER)
$$IF(VERBOSE)

	// Calling the base class $$DOC_BASE_CLASS$$ enables serialization
	//  of the container document's COleClientItem objects.
$$ENDIF
	$$DOC_BASE_CLASS$$::Serialize(ar);
$$ENDIF
$$ENDIF //CEditView
}
$$ENDIF //!DB_NO_FILE

/////////////////////////////////////////////////////////////////////////////
// $$DOC_CLASS$$ diagnostics

#ifdef _DEBUG
void $$DOC_CLASS$$::AssertValid() const
{
	$$DOC_BASE_CLASS$$::AssertValid();
}

void $$DOC_CLASS$$::Dump(CDumpContext& dc) const
{
	$$DOC_BASE_CLASS$$::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// $$DOC_CLASS$$ commands
