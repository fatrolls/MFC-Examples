// ReportCtrlDemoView.cpp : implementation of the CReportCtrlDemoView class
//

#include "stdafx.h"
#include "ReportCtrlDemo.h"

#include "ReportCtrlDemoDoc.h"
#include "ReportCtrlDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString GenRandInt()
{
	int n = (rand() % 100000) + 200;
	CString str;
	str.Format(_T("%d"), n);
	return str;
}

CString GenRandDate()
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	COleDateTimeSpan span(rand() % 3650, rand() % 24, rand() % 60, rand() % 60);
	now -= span;
	return now.Format();
}

CString GenRandDbl()
{
	CString s = GenRandInt();
	s.Insert(s.GetLength() - 2, _T('.'));
	return s;
}

CString GenRandStr()
{
	const CString LETTERS = _T("abcdefghijklmnopqrstuvwxyz0123456789");
	const int LEN = 16;

	CString str;
	for (int i = 0; i < LEN; i++)
	{
		str += LETTERS[rand() % LETTERS.GetLength()];
	}

	return str;
}

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoView

IMPLEMENT_DYNCREATE(CReportCtrlDemoView, CFormView)

BEGIN_MESSAGE_MAP(CReportCtrlDemoView, CFormView)
	//{{AFX_MSG_MAP(CReportCtrlDemoView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoView construction/destruction

CReportCtrlDemoView::CReportCtrlDemoView()
	: CFormView(CReportCtrlDemoView::IDD)
{
	//{{AFX_DATA_INIT(CReportCtrlDemoView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CReportCtrlDemoView::~CReportCtrlDemoView()
{
}

void CReportCtrlDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportCtrlDemoView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CReportCtrlDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CReportCtrlDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	srand((unsigned)time(NULL));
	m_wndList.Create(this, 0, NULL, 0);
	m_wndList.SetImageList(IDB_BITMAP1);
	m_wndList.SetColumnHeader(_T("Member ID, 100; Register Date, 140; Salary, 90, 2; FooBar, 120"));

	for (int i = 0; i < 100; i++)
	{
		const int IDX = m_wndList.InsertItemEx(INT_MAX, GenRandInt(), GenRandDate(), GenRandDbl(), GenRandStr());
		for (int j = 0; j < 3; j++)
		{
			m_wndList.SetItemImage(IDX, j, rand() % 5);
		}
	}

	m_wndList.SetHeaderImageList(IDB_BITMAP2);
	m_wndList.SetHeaderImage(0, 0);
	m_wndList.SetHeaderImage(1, 1, FALSE);
	m_wndList.SetHeaderImage(2, 2);
	
	m_wndList.SetGridLines(TRUE); // SHow grid lines
	m_wndList.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes
	m_wndList.SetEditable(TRUE); // Allow sub-text edit
}

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoView printing

BOOL CReportCtrlDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReportCtrlDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CReportCtrlDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CReportCtrlDemoView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoView diagnostics

#ifdef _DEBUG
void CReportCtrlDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CReportCtrlDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CReportCtrlDemoDoc* CReportCtrlDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReportCtrlDemoDoc)));
	return (CReportCtrlDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlDemoView message handlers

void CReportCtrlDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_wndList.ResizeToFitParent();
}
