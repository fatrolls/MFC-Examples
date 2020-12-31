// NewDoc.cpp : implementation file
//

#include "stdafx.h"
#include "Graph.h"
#include "NewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewDoc

IMPLEMENT_DYNCREATE(CNewDoc, CDocument)

CNewDoc::CNewDoc()
{
}

BOOL CNewDoc::OnNewDocument()
{
        if (!CDocument::OnNewDocument())
                return FALSE;
        return TRUE;
}

CNewDoc::~CNewDoc()
{
}


BEGIN_MESSAGE_MAP(CNewDoc, CDocument)
        //{{AFX_MSG_MAP(CNewDoc)
                // NOTE - the ClassWizard will add and remove mapping macros here.
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewDoc diagnostics

#ifdef _DEBUG
void CNewDoc::AssertValid() const
{
        CDocument::AssertValid();
}

void CNewDoc::Dump(CDumpContext& dc) const
{
        CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNewDoc serialization

void CNewDoc::Serialize(CArchive& ar)
{
        if (ar.IsStoring())
        {
                // TODO: add storing code here
        }
        else
        {
                // TODO: add loading code here
        }

        // CEditView contains an edit control which handles all serialization
        ((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CNewDoc commands
