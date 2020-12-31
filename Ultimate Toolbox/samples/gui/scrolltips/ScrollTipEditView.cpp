// ScrollTipEditView.cpp : implementation of the CScrollTipEditView class
//

#include "stdafx.h"
#include "ScrollTipDemo.h"

#include "ScrollTipDoc.h"
#include "CntrItem.h"
#include "ScrollTipEditView.h"
#include "ScrollSettingsDlg.h"
#include "ScrollDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScrollTipEditView

IMPLEMENT_DYNCREATE(CScrollTipEditView, CRichEditView)

BEGIN_MESSAGE_MAP(CScrollTipEditView, CRichEditView)
	//{{AFX_MSG_MAP(CScrollTipEditView)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollTipEditView construction/destruction

CScrollTipEditView::CScrollTipEditView()
{
	m_nWordWrap = WrapNone;
}

CScrollTipEditView::~CScrollTipEditView()
{
}

BOOL CScrollTipEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CScrollTipEditView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));

	// Insert sopme initial text in the view
	CString sInitialText;
	VERIFY(sInitialText.LoadString(IDS_VIEW_TEXT));
	GetRichEditCtrl().SetSel(0, -1);
	GetRichEditCtrl().ReplaceSel(sInitialText);

	// Add the scroll bar interceptors for scroll tips
	m_wndHScrollTipOwner.InterceptHorizontalScroll(this, TRUE);
	m_wndVScrollTipOwner.InterceptVerticalScroll(this, TRUE);

	// Set initial values
	m_wndHScrollTipOwner.SetMask(_T("Pos %a"));
	m_wndHScrollTipOwner.SetLeftTop(TRUE);
	m_wndHScrollTipOwner.SetPageAlign(FALSE);
	m_wndVScrollTipOwner.SetMask(_T("Page %p"));
	m_wndVScrollTipOwner.SetLeftTop(TRUE);
	m_wndVScrollTipOwner.SetPageAlign(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CScrollTipEditView printing

BOOL CScrollTipEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CScrollTipEditView diagnostics

#ifdef _DEBUG
void CScrollTipEditView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CScrollTipEditView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CScrollTipDoc* CScrollTipEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScrollTipDoc)));
	return (CScrollTipDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScrollTipEditView message handlers

void CScrollTipEditView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	AdjustSettings();

	CRichEditView::OnRButtonDown(nFlags, point);
}

void CScrollTipEditView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CScrollDlg dlg;
	dlg.DoModal();

	CRichEditView::OnLButtonDblClk(nFlags, point);
}

void CScrollTipEditView::AdjustSettings()
{
	CScrollSettingsDlg dlg;
	dlg.m_sHorizontalMask = m_wndHScrollTipOwner.GetMask();
	dlg.m_bHorizontalPageAlign = m_wndHScrollTipOwner.GetPageAlign();
	dlg.m_bHorizontalTop = m_wndHScrollTipOwner.GetLeftTop();

	dlg.m_sVerticalMask = m_wndVScrollTipOwner.GetMask();
	dlg.m_bVerticalPageAlign = m_wndVScrollTipOwner.GetPageAlign();
	dlg.m_bVerticalLeft = m_wndVScrollTipOwner.GetLeftTop();

	if (dlg.DoModal() == IDOK)
	{
		m_wndHScrollTipOwner.SetMask(dlg.m_sHorizontalMask);
		m_wndHScrollTipOwner.SetLeftTop(dlg.m_bHorizontalTop);
		m_wndHScrollTipOwner.SetPageAlign(dlg.m_bHorizontalPageAlign);

		m_wndVScrollTipOwner.SetMask(dlg.m_sVerticalMask);
		m_wndVScrollTipOwner.SetLeftTop(dlg.m_bVerticalLeft);
		m_wndVScrollTipOwner.SetPageAlign(dlg.m_bVerticalPageAlign);
	}
}


