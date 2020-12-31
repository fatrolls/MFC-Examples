// SketchDoc.cpp : implementation of the CSketchDoc class
//

#include "stdafx.h"
#include "Line.h"
#include "Sketch.h"
#include "SketchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSketchDoc

IMPLEMENT_DYNCREATE(CSketchDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketchDoc, CDocument)
	//{{AFX_MSG_MAP(CSketchDoc)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSketchDoc construction/destruction

CSketchDoc::CSketchDoc()
{
}

CSketchDoc::~CSketchDoc()
{
}

BOOL CSketchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_bShowGrid = TRUE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSketchDoc serialization

void CSketchDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_bShowGrid;
    }
    else
    {
        ar >> m_bShowGrid;
    }
    m_arrLines.Serialize (ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSketchDoc diagnostics

#ifdef _DEBUG
void CSketchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSketchDoc commands

BOOL CSketchDoc::IsGridVisible()
{
	return m_bShowGrid;
}

void CSketchDoc::OnViewGrid() 
{
    if (m_bShowGrid)
        m_bShowGrid = FALSE;
    else
        m_bShowGrid = TRUE;

    SetModifiedFlag (TRUE);
    UpdateAllViews (NULL);	
}

void CSketchDoc::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck (m_bShowGrid);
}

CLine* CSketchDoc::AddLine(POINT from, POINT to)
{
    CLine* pLine = NULL;

    try {
        pLine = new CLine (from, to);
        m_arrLines.Add (pLine);
        SetModifiedFlag (TRUE);
		UpdateAllViews (NULL, 0x7C, pLine);
    }
    catch (CMemoryException* e) {
        AfxMessageBox (_T ("Out of memory"));
        if (pLine != NULL) {
            delete pLine;
            pLine = NULL;
        }
        e->Delete ();   
    }       
    return pLine;
}

int CSketchDoc::GetLineCount()
{
    return m_arrLines.GetSize ();
}

CLine* CSketchDoc::GetLine(int nIndex)
{
	ASSERT (nIndex < GetLineCount ());
	return m_arrLines[nIndex];
}

void CSketchDoc::DeleteContents() 
{
    int nCount = GetLineCount ();

    if (nCount) {
        for (int i=0; i<nCount; i++)
            delete m_arrLines[i];
        m_arrLines.RemoveAll ();
    }
    CDocument::DeleteContents();
}
