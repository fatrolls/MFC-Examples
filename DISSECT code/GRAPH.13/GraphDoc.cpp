// GraphDoc.cpp : implementation of the CGraphDoc class
//

#include "stdafx.h"
#include "Graph.h"

#include "GraphDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphDoc

IMPLEMENT_DYNCREATE(CGraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphDoc, CDocument)
        //{{AFX_MSG_MAP(CGraphDoc)
        ON_COMMAND(ID_GRAPH_DATA1, OnGraphData1)
        ON_COMMAND(ID_GRAPH_DATA2, OnGraphData2)
        ON_COMMAND(ID_GRAPH_DATA3, OnGraphData3)
        ON_UPDATE_COMMAND_UI(ID_GRAPH_DATA1, OnUpdateGraphData1)
        ON_UPDATE_COMMAND_UI(ID_GRAPH_DATA2, OnUpdateGraphData2)
        ON_UPDATE_COMMAND_UI(ID_GRAPH_DATA3, OnUpdateGraphData3)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphDoc construction/destruction

CGraphDoc::CGraphDoc()
{
        SetValue(5, 10, 15, 20, 25, 78, 64, 38, 29, 9);
}

CGraphDoc::~CGraphDoc()
{
}

BOOL CGraphDoc::OnNewDocument()
{
        if (!CDocument::OnNewDocument())
                return FALSE;

        // TODO: add reinitialization code here
        // (SDI documents will reuse this document)

        return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGraphDoc serialization

void CGraphDoc::Serialize(CArchive& ar)
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
// CGraphDoc diagnostics

#ifdef _DEBUG
void CGraphDoc::AssertValid() const
{
        CDocument::AssertValid();
}

void CGraphDoc::Dump(CDumpContext& dc) const
{
        CDocument::Dump(dc);
}
#endif //_DEBUG



void CGraphDoc::OnGraphData1()
{
        SetValue(5, 10, 15, 20, 25, 78, 64, 38, 29, 9);
        UpdateAllViews(NULL);
}

void CGraphDoc::OnGraphData2()
{
        SetValue(50, 60, 70, 80, 90, 23, 68, 39, 73, 58);
        UpdateAllViews(NULL);
}

void CGraphDoc::OnGraphData3()
{
        SetValue(12, 20, 8, 17, 28, 37, 93, 45, 78, 29);
        UpdateAllViews(NULL);
}

void CGraphDoc::OnUpdateGraphData1(CCmdUI* pCmdUI)
{
        pCmdUI->SetCheck(m_intArray[0] == 5);
}

void CGraphDoc::OnUpdateGraphData2(CCmdUI* pCmdUI)
{
        pCmdUI->SetCheck(m_intArray[0] == 50);
}

void CGraphDoc::OnUpdateGraphData3(CCmdUI* pCmdUI)
{
        pCmdUI->SetCheck(m_intArray[0] == 12);
}

void CGraphDoc::SetValue(int i0, int i1, int i2, int i3, int i4,
                         int i5, int i6, int i7, int i8, int i9)
{
        m_intArray.SetSize(DATANUM, 0);
        m_intArray[0] = i0;
        m_intArray[1] = i1;
        m_intArray[2] = i2;
        m_intArray[3] = i3;
        m_intArray[4] = i4;
        m_intArray[5] = i5;
        m_intArray[6] = i6;
        m_intArray[7] = i7;
        m_intArray[8] = i8;
        m_intArray[9] = i9;
}
