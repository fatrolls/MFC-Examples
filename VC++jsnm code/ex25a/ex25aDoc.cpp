// ex25aDoc.cpp : implementation of the CEx25aDoc class
//

#include "stdafx.h"
#include "ex25a.h"

#include "cdib.h"
#include "ex25aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25aDoc

IMPLEMENT_DYNCREATE(CEx25aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx25aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx25aDoc)
   ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
   ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25aDoc construction/destruction

CEx25aDoc::CEx25aDoc()
{
	// TODO: add one-time construction code here

}

CEx25aDoc::~CEx25aDoc()
{
}

BOOL CEx25aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx25aDoc serialization

void CEx25aDoc::Serialize(CArchive& ar)
{
   m_dib.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx25aDoc diagnostics

#ifdef _DEBUG
void CEx25aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx25aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx25aDoc commands

void CEx25aDoc::OnEditClearAll() 
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
}

void CEx25aDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_dib.GetSizeImage() > 0);   
}

void CEx25aDoc::DeleteContents() 
{
   m_dib.Empty();
}
