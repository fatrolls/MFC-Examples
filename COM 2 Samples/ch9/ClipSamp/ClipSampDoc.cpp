// ClipSampDoc.cpp : implementation of the CClipSampDoc class
//

#include "stdafx.h"
#include "ClipSamp.h"

#include "dib.h"
#include "ClipSampDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipSampDoc

IMPLEMENT_DYNCREATE(CClipSampDoc, CDocument)

BEGIN_MESSAGE_MAP(CClipSampDoc, CDocument)
	//{{AFX_MSG_MAP(CClipSampDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
    ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipSampDoc construction/destruction

CClipSampDoc::CClipSampDoc()
{
	// TODO: add one-time construction code here
    m_bDragHere = FALSE;
}

CClipSampDoc::~CClipSampDoc()
{
}

BOOL CClipSampDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CClipSampDoc serialization

void CClipSampDoc::Serialize(CArchive& ar)
{
    m_dib.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CClipSampDoc diagnostics

#ifdef _DEBUG
void CClipSampDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClipSampDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClipSampDoc commands

void CClipSampDoc::OnEditClearAll() 
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
}

void CClipSampDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_dib.GetSizeImage() > 0);   
}

void CClipSampDoc::DeleteContents() 
{
    m_dib.Empty();
}
