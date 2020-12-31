// ex30aDoc.cpp : implementation of the CEx30aDoc class
//

#include "stdafx.h"
#include "ex30a.h"

#include "ex30aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx30aDoc

IMPLEMENT_DYNCREATE(CEx30aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx30aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx30aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx30aDoc construction/destruction

CEx30aDoc::CEx30aDoc()
{
	// TODO: add one-time construction code here

}

CEx30aDoc::~CEx30aDoc()
{
}

BOOL CEx30aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx30aDoc serialization

void CEx30aDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx30aDoc diagnostics

#ifdef _DEBUG
void CEx30aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx30aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx30aDoc commands

BOOL CEx30aDoc::SaveModified() 
{
	return TRUE; // eliminates "save doc" message on exit
}
