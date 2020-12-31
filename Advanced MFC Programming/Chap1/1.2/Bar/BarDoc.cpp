#include "stdafx.h"
#include "Bar.h"

#include "BarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CBarDoc, CDocument)
	//{{AFX_MSG_MAP(CBarDoc)
	ON_COMMAND(ID_BUTTON_BLUE, OnButtonBlue)
	ON_COMMAND(ID_BUTTON_GREEN, OnButtonGreen)
	ON_COMMAND(ID_BUTTON_RED, OnButtonRed)
	ON_COMMAND(ID_BUTTON_YELLOW, OnButtonYellow)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_BLUE, OnUpdateButtonBlue)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_GREEN, OnUpdateButtonGreen)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RED, OnUpdateButtonRed)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_YELLOW, OnUpdateButtonYellow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBarDoc::CBarDoc()
{
	m_uCurrentBtn=ID_BUTTON_RED;
}

CBarDoc::~CBarDoc()
{
}

BOOL CBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CBarDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

void CBarDoc::OnButtonBlue() 
{
	m_uCurrentBtn=ID_BUTTON_BLUE;
}

void CBarDoc::OnButtonGreen() 
{
	m_uCurrentBtn=ID_BUTTON_GREEN;
}

void CBarDoc::OnButtonRed() 
{
	m_uCurrentBtn=ID_BUTTON_RED;
}

void CBarDoc::OnButtonYellow() 
{
	m_uCurrentBtn=ID_BUTTON_YELLOW;
}

void CBarDoc::OnUpdateButtonBlue(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_uCurrentBtn);
}

void CBarDoc::OnUpdateButtonGreen(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(pCmdUI->m_nID == m_uCurrentBtn);
}

void CBarDoc::OnUpdateButtonRed(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(pCmdUI->m_nID == m_uCurrentBtn);
}

void CBarDoc::OnUpdateButtonYellow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(pCmdUI->m_nID == m_uCurrentBtn);
}
