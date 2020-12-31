// MenuDoc.cpp : implementation of the CMenuDoc class
//

#include "stdafx.h"
#include "Menu.h"

#include "MenuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuDoc

IMPLEMENT_DYNCREATE(CMenuDoc, CDocument)

BEGIN_MESSAGE_MAP(CMenuDoc, CDocument)
	//{{AFX_MSG_MAP(CMenuDoc)
	ON_COMMAND(ID_EDIT_INSERTDYNAMICMENU, OnEditInsertDynamicMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERTDYNAMICMENU, OnUpdateEditInsertDynamicMenu)
	ON_COMMAND(ID_EDIT_DELETEDYNAMICMENU, OnEditDeleteDynamicMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETEDYNAMICMENU, OnUpdateEditDeleteDynamicMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuDoc construction/destruction

CMenuDoc::CMenuDoc()
{
	m_menuSub.LoadMenu(IDR_MENU_POPUP);
	m_bSubMenuOn=FALSE;
}

CMenuDoc::~CMenuDoc()
{
}

BOOL CMenuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMenuDoc serialization

void CMenuDoc::Serialize(CArchive& ar)
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
// CMenuDoc diagnostics

#ifdef _DEBUG
void CMenuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMenuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMenuDoc commands

void CMenuDoc::OnEditInsertDynamicMenu() 
{
	CMenu *pTopMenu=AfxGetMainWnd()->GetMenu();
	CMenu *ptrMenu=m_menuSub.GetSubMenu(0);
	pTopMenu->InsertMenu
	(
		1, MF_BYPOSITION | MF_POPUP, (UINT)ptrMenu->GetSafeHmenu(), "&Dynamic Menu"
	);
	AfxGetMainWnd()->DrawMenuBar();
	m_bSubMenuOn=TRUE;
}

void CMenuDoc::OnUpdateEditInsertDynamicMenu(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bSubMenuOn == FALSE);	
}

void CMenuDoc::OnEditDeleteDynamicMenu() 
{
	CMenu *pTopMenu=AfxGetMainWnd()->GetMenu();
	pTopMenu->RemoveMenu(1, MF_BYPOSITION);
	AfxGetMainWnd()->DrawMenuBar();
	m_bSubMenuOn=FALSE;
}

void CMenuDoc::OnUpdateEditDeleteDynamicMenu(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bSubMenuOn == TRUE);
}
