// ToolbarMenuDemoMDIDoc.cpp : implementation of the CToolbarMenuDemoMDIDoc class
//

#include "stdafx.h"
#include "ToolbarMenuDemoMDI.h"

#include "ToolbarMenuDemoMDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIDoc

IMPLEMENT_DYNCREATE(CToolbarMenuDemoMDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolbarMenuDemoMDIDoc, CDocument)
	//{{AFX_MSG_MAP(CToolbarMenuDemoMDIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIDoc construction/destruction

CToolbarMenuDemoMDIDoc::CToolbarMenuDemoMDIDoc()
{
	// TODO: add one-time construction code here

}

CToolbarMenuDemoMDIDoc::~CToolbarMenuDemoMDIDoc()
{
}

BOOL CToolbarMenuDemoMDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIDoc serialization

void CToolbarMenuDemoMDIDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIDoc diagnostics

#ifdef _DEBUG
void CToolbarMenuDemoMDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolbarMenuDemoMDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIDoc commands
