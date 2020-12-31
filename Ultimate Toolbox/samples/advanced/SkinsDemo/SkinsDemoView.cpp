// SkinsDemoView.cpp : implementation of the CSkinsDemoView class
//

#include "stdafx.h"
#include "SkinsDemo.h"

#include "SkinsDemoDoc.h"
#include "SkinsDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoView

IMPLEMENT_DYNCREATE(CSkinsDemoView, BASEVIEW)

BEGIN_MESSAGE_MAP(CSkinsDemoView, BASEVIEW)
	//{{AFX_MSG_MAP(CSkinsDemoView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ITEM1, OnItem1)
	ON_COMMAND(ID_ITEM2, OnItem2)
	ON_UPDATE_COMMAND_UI(ID_ITEM2, OnUpdateItem2)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoView construction/destruction

CSkinsDemoView::CSkinsDemoView()
{
	// TODO: add construction code here

}

CSkinsDemoView::~CSkinsDemoView()
{
}

BOOL CSkinsDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoView drawing

void CSkinsDemoView::OnDraw(CDC* pDC)
{
	CSkinsDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// TODO: add draw code for native data here
	CFont font;
	font.CreatePointFont(80, _T("MS Sans Serif"));
	CFont* pOldFont = pDC->SelectObject(&font);

	CRect rectClient;
	GetClientRect(rectClient);

	CSkinsDemoApp* pApp = (CSkinsDemoApp*) AfxGetApp();

	COLORREF clrOldColor = pDC->SetTextColor(pApp->GetCurrentSkin()->GetFrameSkin()->GetBorderColor());
	pDC->DrawText(_T("Right click to activate the context menu."), rectClient, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	pDC->SetTextColor(clrOldColor);
	pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoView printing

BOOL CSkinsDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSkinsDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSkinsDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoView diagnostics

#ifdef _DEBUG
void CSkinsDemoView::AssertValid() const
{
	BASEVIEW::AssertValid();
}

void CSkinsDemoView::Dump(CDumpContext& dc) const
{
	BASEVIEW::Dump(dc);
}

CSkinsDemoDoc* CSkinsDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSkinsDemoDoc)));
	return (CSkinsDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoView message handlers

void CSkinsDemoView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
	// TODO: Add your message handler code here
	COXBitmapMenu menu;
	menu.LoadMenu(IDR_POPUPS);
	CMenu* pMenuPopup = menu.GetSubMenu(0);

	pMenuPopup->SetDefaultItem(0, MF_BYPOSITION | MF_ENABLED);
	pMenuPopup->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);

	pMenuPopup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd());
}

void CSkinsDemoView::OnItem1() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("Item 1 clicked."), MB_ICONWARNING);
}

void CSkinsDemoView::OnItem2() 
{
	// TODO: Add your command handler code here
	
}

void CSkinsDemoView::OnUpdateItem2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	// Disable the item
	pCmdUI->Enable(FALSE);
}
