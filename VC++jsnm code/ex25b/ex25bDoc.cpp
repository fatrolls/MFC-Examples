// ex25bDoc.cpp : implementation of the CEx25bDoc class
//

#include "stdafx.h"
#include "ex25b.h"

#include "cdib.h"
#include "ex25bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25bDoc

IMPLEMENT_DYNCREATE(CEx25bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx25bDoc, CDocument)
    //{{AFX_MSG_MAP(CEx25bDoc)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25bDoc construction/destruction

CEx25bDoc::CEx25bDoc()
{
    m_bDragHere = FALSE;
}

CEx25bDoc::~CEx25bDoc()
{
}

BOOL CEx25bDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx25bDoc serialization

void CEx25bDoc::Serialize(CArchive& ar)
{
    m_dib.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx25bDoc diagnostics

#ifdef _DEBUG
void CEx25bDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEx25bDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx25bDoc commands

void CEx25bDoc::OnEditClearAll() 
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
}

void CEx25bDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_dib.GetSizeImage() > 0);   
}

void CEx25bDoc::DeleteContents() 
{
    m_dib.Empty();
}
