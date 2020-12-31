#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDIDoc, CDocument)
	//{{AFX_MSG_MAP(CGDIDoc)
	ON_COMMAND(ID_FLOODFILL, OnFloodfill)
	ON_UPDATE_COMMAND_UI(ID_FLOODFILL, OnUpdateFloodfill)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGDIDoc::CGDIDoc()
{
	m_bFloodFill=FALSE;
}

CGDIDoc::~CGDIDoc()
{
	while(m_paLines.GetSize())
	{
		delete m_paLines.GetAt(0);
		m_paLines.RemoveAt(0);
	}
}

BOOL CGDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CGDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CGDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

void CGDIDoc::OnFloodfill() 
{
	m_bFloodFill=m_bFloodFill ? FALSE:TRUE;	
}

void CGDIDoc::OnUpdateFloodfill(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bFloodFill);	
}
