#include "stdafx.h"
#include "Menu.h"
#include "MenuDoc.h"
#include "MenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMenuView, CView)

BEGIN_MESSAGE_MAP(CMenuView, CView)
	//{{AFX_MSG_MAP(CMenuView)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMenuView::CMenuView()
{
}

CMenuView::~CMenuView()
{
}

BOOL CMenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CMenuView::OnDraw(CDC* pDC)
{
	CMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

#ifdef _DEBUG
void CMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMenuDoc* CMenuView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMenuDoc)));
	return (CMenuDoc*)m_pDocument;
}
#endif

void CMenuView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menu;
	CMenu *ptrMenu;
		
	menu.LoadMenu(IDR_MENU_POPUP);
	ptrMenu=menu.GetSubMenu(0);
	ptrMenu->EnableMenuItem(ID__POPUPITEM1, MF_GRAYED);
	ptrMenu->EnableMenuItem(ID__POPUPITEM2, MF_ENABLED);
	ptrMenu->CheckMenuItem(ID__POPUPITEM3, MF_UNCHECKED);
	ptrMenu->CheckMenuItem(ID__POPUPITEM4, MF_CHECKED);
	ClientToScreen(&point);
	ptrMenu->TrackPopupMenu
	(
		TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		point.x,
		point.y,
		this,
		NULL
	);
	CView::OnRButtonDown(nFlags, point);
}
