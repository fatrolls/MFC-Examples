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
	ON_COMMAND(ID_EDIT_INSERTDYNAMICMENU, OnEditInsertDynamicMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERTDYNAMICMENU, OnUpdateEditInsertDynamicMenu)
	ON_COMMAND(ID_EDIT_DELETEDYNAMICMENU, OnEditDeleteDynamicMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETEDYNAMICMENU, OnUpdateEditDeleteDynamicMenu)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID__POPUPITEM1, OnPopUpItem1)
	ON_COMMAND(ID__POPUPITEM2, OnPopUpItem2)
	ON_COMMAND(ID__POPUPITEM3, OnPopUpItem3)
	ON_COMMAND(ID__POPUPITEM4, OnPopUpItem4)
	ON_UPDATE_COMMAND_UI(ID__POPUPITEM1, OnUpdatePopUpItem1)
	ON_UPDATE_COMMAND_UI(ID__POPUPITEM2, OnUpdatePopUpItem2)
END_MESSAGE_MAP()

CMenuDoc::CMenuDoc()
{
	CMenu *ptrMenu;

	m_menuSub.LoadMenu(IDR_MENU_POPUP);
	m_bmpCheck.LoadBitmap(IDB_BITMAP_CHECK);
	m_bmpUnCheck.LoadBitmap(IDB_BITMAP_UNCHECK);
	ptrMenu=m_menuSub.GetSubMenu(0);
	ptrMenu->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_bmpUnCheck, &m_bmpCheck);
	ptrMenu->SetMenuItemBitmaps(1, MF_BYPOSITION, &m_bmpUnCheck, &m_bmpCheck);
	m_bSubMenuOn=FALSE;
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

void CMenuDoc::OnPopUpItem1()
{
	AfxMessageBox("Dynamic Pop up menu item 1");
}

void CMenuDoc::OnPopUpItem2()
{
	AfxMessageBox("Dynamic Pop up menu item 2");
}

void CMenuDoc::OnPopUpItem3()
{
	AfxMessageBox("Dynamic Pop up menu item 3");
}

void CMenuDoc::OnPopUpItem4()
{
	AfxMessageBox("Dynamic Pop up menu item 4");
}

void CMenuDoc::OnUpdatePopUpItem1(CCmdUI *pCmdUI)
{
	if(m_bSubMenuOn)pCmdUI->SetCheck(TRUE);
}

void CMenuDoc::OnUpdatePopUpItem2(CCmdUI *pCmdUI)
{
	if(m_bSubMenuOn)pCmdUI->SetCheck(FALSE);
}