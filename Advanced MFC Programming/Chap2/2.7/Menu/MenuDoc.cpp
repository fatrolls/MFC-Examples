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
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMenuDoc::CMenuDoc()
{
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

void CMenuDoc::OnFileNew() 
{
	CMenu menu;

	menu.LoadMenu(IDR_MAINFRAME_ACTIVE);
	AfxGetMainWnd()->SetMenu(&menu);
	AfxGetMainWnd()->DrawMenuBar();
	menu.Detach();
}

void CMenuDoc::OnFileOpen() 
{
	CMenu menu;

	menu.LoadMenu(IDR_MAINFRAME_ACTIVE);
	AfxGetMainWnd()->SetMenu(&menu);
	AfxGetMainWnd()->DrawMenuBar();
	menu.Detach();
}

void CMenuDoc::OnFileClose() 
{
	CMenu menu;

	menu.LoadMenu(IDR_MAINFRAME);
	AfxGetMainWnd()->SetMenu(&menu);
	AfxGetMainWnd()->DrawMenuBar();
	menu.Detach();
}
