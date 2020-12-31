// demo_toolbarDoc.cpp : implementation of the CDemo_toolbarDoc class
//

#include "stdafx.h"
#include "demo_toolbar.h"

#include "demo_toolbarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarDoc

IMPLEMENT_DYNCREATE(CDemo_toolbarDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemo_toolbarDoc, CDocument)
	//{{AFX_MSG_MAP(CDemo_toolbarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarDoc construction/destruction

CDemo_toolbarDoc::CDemo_toolbarDoc()
{
	// TODO: add one-time construction code here

}

CDemo_toolbarDoc::~CDemo_toolbarDoc()
{
}

BOOL CDemo_toolbarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarDoc serialization

void CDemo_toolbarDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarDoc diagnostics

#ifdef _DEBUG
void CDemo_toolbarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemo_toolbarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarDoc commands
