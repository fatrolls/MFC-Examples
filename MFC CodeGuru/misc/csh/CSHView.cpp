// CSHView.cpp : implementation of the CCSHView class
//

#include "stdafx.h"
#include "CSH.h"

#include "CSHDoc.h"
#include "CSHView.h"
#include "DlgSample.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "resource.hm"
const DWORD CCSHView::m_nHelpIDs[] = 
{
	IDC_BUTTON_HELP         ,HIDC_BUTTON_HELP,
	IDC_CHECK_WITH_INTERNET ,HIDC_CHECK_WITH_INTERNET,
	IDC_COMBO_SELECT_SHOP   ,HIDC_COMBO_SELECT_SHOP,        
	IDC_RADIO_RADIO         ,HIDC_RADIO_RADIO,         
	IDC_RADIO_TV            ,HIDC_RADIO_TV,
	0,0
};

/////////////////////////////////////////////////////////////////////////////
// CCSHView

IMPLEMENT_DYNCREATE(CCSHView, CFormView)

BEGIN_MESSAGE_MAP(CCSHView, CFormView)
	//{{AFX_MSG_MAP(CCSHView)
	ON_WM_CONTEXTMENU()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_BUTTON_SAMPLE_DLG, OnButtonSampleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSHView construction/destruction

CCSHView::CCSHView()
	: CFormView(CCSHView::IDD)
{
	//{{AFX_DATA_INIT(CCSHView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CCSHView::~CCSHView()
{
}

void CCSHView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSHView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CCSHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCSHView diagnostics

#ifdef _DEBUG
void CCSHView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCSHView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCSHDoc* CCSHView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCSHDoc)));
	return (CCSHDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCSHView message handlers

void CCSHView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	::WinHelp(pWnd->m_hWnd, AfxGetApp()->m_pszHelpFilePath, HELP_CONTEXTMENU, (DWORD)(LPVOID)m_nHelpIDs);
}

BOOL CCSHView::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	return ::WinHelp((HWND)pHelpInfo->hItemHandle, AfxGetApp()->m_pszHelpFilePath, HELP_WM_HELP, (DWORD)(LPVOID)m_nHelpIDs);	
}

void CCSHView::OnButtonSampleDlg() 
{
	CDlgSample DlgSample;
	DlgSample.DoModal();	
}
