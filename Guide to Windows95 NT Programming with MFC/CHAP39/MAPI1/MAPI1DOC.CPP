// Mapi1Doc.cpp : implementation of the CMapi1Doc class
//

#include "stdafx.h"
#include "Mapi1.h"
#include "Mapi1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapi1Doc

IMPLEMENT_DYNCREATE(CMapi1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMapi1Doc, CDocument)
	//{{AFX_MSG_MAP(CMapi1Doc)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapi1Doc construction/destruction

CMapi1Doc::CMapi1Doc()
{
	// TODO: add one-time construction code here

}

CMapi1Doc::~CMapi1Doc()
{
}

BOOL CMapi1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMapi1Doc serialization

void CMapi1Doc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMapi1Doc diagnostics

#ifdef _DEBUG
void CMapi1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapi1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapi1Doc commands

void CMapi1Doc::OnFileSendMail() 
{
   // Perform your own tasks first, then...

   // Call inherited method
   CDocument::OnFileSendMail();
}

