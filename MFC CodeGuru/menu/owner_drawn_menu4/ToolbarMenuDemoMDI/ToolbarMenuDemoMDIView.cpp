// ToolbarMenuDemoMDIView.cpp : implementation of the CToolbarMenuDemoMDIView class
//

#include "stdafx.h"
#include "ToolbarMenuDemoMDI.h"

#include "ToolbarMenuDemoMDIDoc.h"
#include "ToolbarMenuDemoMDIView.h"

// COOLMENU SUPPORT
#include "MenuSpawn.h"
// END COOLMENU SUPPORT


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIView

IMPLEMENT_DYNCREATE(CToolbarMenuDemoMDIView, CEditView)

BEGIN_MESSAGE_MAP(CToolbarMenuDemoMDIView, CEditView)
	//{{AFX_MSG_MAP(CToolbarMenuDemoMDIView)
	ON_WM_RBUTTONDOWN()
	ON_WM_MENUCHAR()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIView construction/destruction

CToolbarMenuDemoMDIView::CToolbarMenuDemoMDIView()
{
// COOLMENU SUPPORT
	pSpawn = NULL;
// END COOLMENU SUPPORT
}

CToolbarMenuDemoMDIView::~CToolbarMenuDemoMDIView()
{
// COOLMENU SUPPORT
	if (pSpawn) delete pSpawn;
// END COOLMENU SUPPORT
}

BOOL CToolbarMenuDemoMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIView drawing

void CToolbarMenuDemoMDIView::OnDraw(CDC* pDC)
{
	CToolbarMenuDemoMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIView printing

BOOL CToolbarMenuDemoMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CToolbarMenuDemoMDIView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CToolbarMenuDemoMDIView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIView diagnostics

#ifdef _DEBUG
void CToolbarMenuDemoMDIView::AssertValid() const
{
	CEditView::AssertValid();
}

void CToolbarMenuDemoMDIView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CToolbarMenuDemoMDIDoc* CToolbarMenuDemoMDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolbarMenuDemoMDIDoc)));
	return (CToolbarMenuDemoMDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolbarMenuDemoMDIView message handlers


// COOLMENU SUPPORT
void CToolbarMenuDemoMDIView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (!pSpawn || !pSpawn->DrawItem(lpDrawItemStruct))
		CEditView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CToolbarMenuDemoMDIView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if (!pSpawn || !pSpawn->MeasureItem(lpMeasureItemStruct))
		CEditView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
// END COOLMENU SUPPORT

void CToolbarMenuDemoMDIView::OnRButtonDown(UINT nFlags, CPoint point) 
{
// COOLMENU SUPPORT

	if (pSpawn) delete pSpawn;

	pSpawn = new CMenuSpawn(true);
	ASSERT(pSpawn);

	pSpawn->LoadToolBarResource(IDR_MAINFRAME);

	CMenu pPopupMenu;
	VERIFY(pPopupMenu.LoadMenu(IDR_TOOLBATYPE));
	CMenu * pPopup = pPopupMenu.GetSubMenu(1);	// Let's get the Modify menu
	ASSERT(pPopup != NULL);

	pSpawn->RemapMenu(pPopup);

	// This is a function which uses the standard MFC command enabling mechanism
	// to enable and disable the items of the popup menu
	pSpawn->EnableMenuItems(pPopup, this);

	
/*	CString csText;
	pSpawn->GetMenuItemText(csText, pPopup, 0, true);
	afxDump << csText << "\n";*/

	CPoint mpt;
	::GetCursorPos(&mpt);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, mpt.x, mpt.y, this);
	pPopupMenu.DestroyMenu();

	delete pSpawn;
	pSpawn = NULL;

// END COOLMENU SUPPORT
//	CEditView::OnRButtonDown(nFlags, point);
}

// COOLMENU SUPPORT
LRESULT CToolbarMenuDemoMDIView::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lRes = CEditView::OnMenuChar(nChar, nFlags, pMenu);
	if (HIWORD(lRes) != 2) pSpawn->FindKeyboardShortcut(nChar, nFlags, pMenu, lRes);
	return lRes;
}
// END COOLMENU SUPPORT


