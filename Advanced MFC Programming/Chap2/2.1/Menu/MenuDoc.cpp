#include "stdafx.h"
#include "Menu.h"
#include "MenuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMenuDoc, CDocument)

BEGIN_MESSAGE_MAP(CMenuDoc, CDocument)
	//{{AFX_MSG_MAP(CMenuDoc)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMenuDoc::CMenuDoc()
{
	m_bPasteAvailable=FALSE;
	m_bDataPasted=FALSE;
}

CMenuDoc::~CMenuDoc()
{
}

BOOL CMenuDoc::OnNewDocument()
{
	if(!CDocument::OnNewDocument())return FALSE;

	return TRUE;
}

void CMenuDoc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CMenuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMenuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

void CMenuDoc::OnEditCopy() 
{
	m_bPasteAvailable=TRUE;
	m_bDataPasted=FALSE;
}

void CMenuDoc::OnEditCut() 
{
	m_bPasteAvailable=TRUE;
	m_bDataPasted=FALSE;
}

void CMenuDoc::OnEditPaste() 
{
	m_bDataPasted=TRUE;	
}

void CMenuDoc::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bPasteAvailable);
	pCmdUI->SetCheck(m_bDataPasted);
	pCmdUI->SetText
	(
		m_bPasteAvailable ? 
		(m_bDataPasted ? "Data &pasted":"Please &paste"):
		"Do not &paste"
	);
}
