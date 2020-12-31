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
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_BUTTON_RED, ID_BUTTON_YELLOW, OnButtons)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BUTTON_RED, ID_BUTTON_YELLOW, OnUpdateButtons)
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

void CBarDoc::OnButtons(UINT uID) 
{
	m_uCurrentBtn=uID;
}

void CBarDoc::OnUpdateButtons(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(pCmdUI->m_nID == m_uCurrentBtn);
}
