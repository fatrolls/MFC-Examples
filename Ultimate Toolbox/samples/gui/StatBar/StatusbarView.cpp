// StatusbarView.cpp : implementation of the CStatusbarView class
//

#include "stdafx.h"
#include "Statusbar.h"

#include "StatusbarDoc.h"
#include "StatusbarView.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusbarView

IMPLEMENT_DYNCREATE(CStatusbarView, CFormView)

BEGIN_MESSAGE_MAP(CStatusbarView, CFormView)
	//{{AFX_MSG_MAP(CStatusbarView)
	ON_BN_CLICKED(IDC_APPLYBUTTON, OnApplybutton)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CURSORCHECK, OnCursorcheck)
	ON_BN_CLICKED(IDC_FONTCHECK, OnFontcheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusbarView construction/destruction

CStatusbarView::CStatusbarView()
	: CFormView(CStatusbarView::IDD)
{
	//{{AFX_DATA_INIT(CStatusbarView)
	m_bFont = FALSE;
	m_bCursor = FALSE;
	m_bProcent = TRUE;
	m_bGlasses = FALSE;
	m_bTooltips = FALSE;
	m_nLayout = 2;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CStatusbarView::~CStatusbarView()
{
}

void CStatusbarView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatusbarView)
	DDX_Check(pDX, IDC_FONTCHECK, m_bFont);
	DDX_Check(pDX, IDC_CURSORCHECK, m_bCursor);
	DDX_Check(pDX, IDC_CHECK1, m_bProcent);
	DDX_Check(pDX, IDC_CHECK3, m_bGlasses);
	DDX_Check(pDX, IDC_CHECK4, m_bTooltips);
	DDX_Radio(pDX, IDC_STRETCHRADIO, m_nLayout);
	//}}AFX_DATA_MAP
}

BOOL CStatusbarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusbarView diagnostics

#ifdef _DEBUG
void CStatusbarView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStatusbarView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CStatusbarDoc* CStatusbarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatusbarDoc)));
	return (CStatusbarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusbarView message handlers

void CStatusbarView::OnApplybutton() 
	{
	if (UpdateData(TRUE))
//		((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneBitmap(2, IDB_NEWMAIL, (EOrientation)(m_nLayout + 1), RGB(0,128,128));
		((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneBitmap(2, IDB_GREEN_LIGHT, (EOrientation)(m_nLayout + 1), RGB(0,128,128));

	}

void CStatusbarView::OnCheck1() 
{
	if (UpdateData(TRUE))
		((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetUpBar(1, TRUE, m_bProcent);
	
}

void CStatusbarView::OnCheck3() 
{
	if (UpdateData(TRUE))
		if (m_bGlasses)
			((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(40);
		else
			((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(0);

	
	((CMainFrame*)AfxGetMainWnd())->RecalcLayout();
	
}

void CStatusbarView::OnCheck4() 
{
	if (UpdateData(TRUE))
		((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.ActivatePaneTips(m_bTooltips);
	
}

void CStatusbarView::OnCursorcheck() 
{
	if (UpdateData(TRUE))
		{
		if (m_bCursor)
			((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneCursor(0, IDC_NODROP);
		else
			((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneCursor(0, 0);

		}
}

void CStatusbarView::OnFontcheck() 
{
	if (UpdateData(TRUE))
		{
		if (m_bFont)
			{
			CFont TestFont;
			TestFont.CreateStockObject(ANSI_FIXED_FONT);
			((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneFont(0, &TestFont);
			}
		else
			((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneFont(0, NULL);

		}
	
}

void CStatusbarView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneTip(0, _T("The Stretchy pane"));
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneTip(1, _T("The Progress pane"));
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneTip(2, _T("The Bitmap pane"));
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneTip(3, _T("The Numlock pane"));
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneTip(4, _T("The Scrolllock pane"));
	((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar.SetPaneTip(5, _T("The Time pane"));
	
	ResizeParentToFit(FALSE);
}
