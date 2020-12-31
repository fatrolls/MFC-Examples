// ex12aView.cpp : implementation of the CEx12aView class
//

#include "stdafx.h"
#include "ex12a.h"

#include "ex12aDoc.h"
#include "ex12aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12aView

IMPLEMENT_DYNCREATE(CEx12aView, CView)

BEGIN_MESSAGE_MAP(CEx12aView, CView)
	//{{AFX_MSG_MAP(CEx12aView)
	ON_COMMAND(ID_TRANSFER_GETDATA, OnTransferGetData)
	ON_COMMAND(ID_TRANSFER_STOREDATA, OnTransferStoreData)
	ON_UPDATE_COMMAND_UI(ID_TRANSFER_STOREDATA, OnUpdateTransferStoreData)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FORMAT_DEFAULT, OnFormatDefault)
	ON_COMMAND(ID_FORMAT_SELECTION, OnFormatSelection)
	ON_UPDATE_COMMAND_UI(ID_FORMAT_SELECTION, OnUpdateFormatSelection)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USERAPPLY, OnUserApply)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12aView construction/destruction

CEx12aView::CEx12aView() : m_sh("")
{
	m_sh.m_page1.m_nFont = 0;
	m_sh.m_page2.m_bBold = FALSE;
	m_sh.m_page2.m_bItalic = FALSE;
	m_sh.m_page2.m_bUnderline = FALSE;
	m_sh.m_page3.m_nColor = 0;
	m_sh.m_page4.m_nFontSize = 12;
	g_pView = this;
	m_bDefault = TRUE;
}

CEx12aView::~CEx12aView()
{
}

BOOL CEx12aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aView drawing

void CEx12aView::OnDraw(CDC* pDC)
{
	CEx12aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aView diagnostics

#ifdef _DEBUG
void CEx12aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx12aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx12aDoc* CEx12aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx12aDoc)));
	return (CEx12aDoc*)m_pDocument;
}
#endif //_DEBUG

void CEx12aView::Format(CHARFORMAT& cf)
{
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE |
	            CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;
	cf.dwEffects = (m_sh.m_page2.m_bBold ? CFE_BOLD : 0) |
	               (m_sh.m_page2.m_bItalic ? CFE_ITALIC : 0) |
	               (m_sh.m_page2.m_bUnderline ? CFE_UNDERLINE : 0);
	cf.yHeight = m_sh.m_page4.m_nFontSize * 20;
	switch(m_sh.m_page3.m_nColor) {
	case -1:
	case 0:
		cf.crTextColor = RGB(0, 0, 0);
		break;
	case 1:
		cf.crTextColor = RGB(255, 0, 0);
		break;
	case 2:
		cf.crTextColor = RGB(0, 255, 0);
		break;
	}
	switch(m_sh.m_page1.m_nFont) {
	case -1:
	case 0:
		strcpy(cf.szFaceName, "Times New Roman");
		break;
	case 1:
		strcpy(cf.szFaceName, "Arial");
		break;
	case 2:
		strcpy(cf.szFaceName, "Courier New");
		break;
	}
	cf.bCharSet = 0;
	cf.bPitchAndFamily = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aView message handlers

void CEx12aView::OnTransferGetData() 
{
	CEx12aDoc* pDoc = GetDocument();
	m_rich.SetWindowText(pDoc->m_strText);
	m_rich.SetModify(FALSE);
}

void CEx12aView::OnTransferStoreData() 
{
	CEx12aDoc* pDoc = GetDocument();
	m_rich.GetWindowText(pDoc->m_strText);
	m_rich.SetModify(FALSE);
}

void CEx12aView::OnUpdateTransferStoreData(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_rich.GetModify());
}

int CEx12aView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CRect rect(0, 0, 0, 0);
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_rich.Create(ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN |
	              WS_CHILD | WS_VISIBLE | WS_VSCROLL, rect, this, 1);
	CHARFORMAT cf;
	Format(cf);
	m_rich.SetDefaultCharFormat(cf);
	return 0;
}

void CEx12aView::OnSize(UINT nType, int cx, int cy) 
{
	CRect rect;
	CView::OnSize(nType, cx, cy);
	GetClientRect(rect);
	m_rich.SetWindowPos(&wndTop, 0, 0, rect.right - rect.left,
	                    rect.bottom - rect.top, SWP_SHOWWINDOW);
}

void CEx12aView::OnFormatDefault() 
{
	m_sh.SetTitle("Default Format");
	m_bDefault = TRUE;
	m_sh.DoModal();
}

void CEx12aView::OnFormatSelection() 
{
	m_sh.SetTitle("Selection Format");
	m_bDefault = FALSE;
	m_sh.DoModal();
}

void CEx12aView::OnUpdateFormatSelection(CCmdUI* pCmdUI) 
{
	long nStart, nEnd;
	m_rich.GetSel(nStart, nEnd);
	pCmdUI->Enable(nStart != nEnd);
}

LRESULT CEx12aView::OnUserApply(WPARAM wParam, LPARAM lParam)
{
	TRACE("CEx12aView::OnUserApply -- wParam = %x\n", wParam);
	CHARFORMAT cf;
	Format(cf);
	if (m_bDefault) {
		m_rich.SetDefaultCharFormat(cf);
	}
	else {
		m_rich.SetSelectionCharFormat(cf);
	}
	return 0;
}
