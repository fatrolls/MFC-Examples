// ex12aDoc.cpp : implementation of the CEx12aDoc class
//

#include "stdafx.h"
#include "ex12a.h"

#include "ex12aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc

IMPLEMENT_DYNCREATE(CEx12aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx12aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx12aDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearDocument)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearDocument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc construction/destruction

CEx12aDoc::CEx12aDoc()
{
	// TODO: add one-time construction code here

}

CEx12aDoc::~CEx12aDoc()
{
}

BOOL CEx12aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_strText = "Hello (from CEx12aDoc::OnNewDocument)";
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc serialization

void CEx12aDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc diagnostics

#ifdef _DEBUG
void CEx12aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx12aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc commands

void CEx12aDoc::OnEditClearDocument() 
{
	m_strText.Empty();	
}

void CEx12aDoc::OnUpdateEditClearDocument(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_strText.IsEmpty());	
}
