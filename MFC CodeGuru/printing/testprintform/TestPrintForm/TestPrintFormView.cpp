// TestPrintFormView.cpp : implementation of the CTestPrintFormView class
//

#include "stdafx.h"
#include "TestPrintForm.h"

#include "TestPrintFormDoc.h"
#include "TestPrintFormView.h"

#include "TestPrintFormDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormView

IMPLEMENT_DYNCREATE(CTestPrintFormView, CFormView)

BEGIN_MESSAGE_MAP(CTestPrintFormView, CFormView)
	//{{AFX_MSG_MAP(CTestPrintFormView)
	ON_COMMAND(ID_TEST, OnTest)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormView construction/destruction

CTestPrintFormView::CTestPrintFormView()
	: CFormView(CTestPrintFormView::IDD)
{
	//{{AFX_DATA_INIT(CTestPrintFormView)
	bCheck = FALSE;
	csVal1 = _T("test value 1");
	csVal2 = _T("test value 2");
	csVal3 = _T("test value 3");
	csVal4 = _T("test value 4");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	cSingleJob.pView = this;
	cMultiJob.pView = this;
}

CTestPrintFormView::~CTestPrintFormView()
{
}

void CTestPrintFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPrintFormView)
	DDX_Control(pDX, IDC_LIST1, wndList);
	DDX_Check(pDX, IDC_CHECK1, bCheck);
	DDX_Text(pDX, IDC_EDIT1, csVal1);
	DDX_Text(pDX, IDC_EDIT2, csVal2);
	DDX_Text(pDX, IDC_EDIT3, csVal3);
	DDX_Text(pDX, IDC_EDIT4, csVal4);
	//}}AFX_DATA_MAP
}

BOOL CTestPrintFormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormView printing

BOOL CTestPrintFormView::OnPreparePrinting(CPrintInfo* pInfo)
{
	UpdateData();

	if (bCheck)
	{
		cMultiJob.Clear();
		cMultiJob.AddPage("testform2.prx", "testpage", 1, wndList.GetItemCount());
	}
	else
	{
		cSingleJob.Clear();
		cSingleJob.AddPage("testform1.prx", "testpage", 1);
	}

	if (pInfo->m_bPreview) return DoPreparePrinting(pInfo);

	if (bCheck) return cMultiJob.OnPreparePrinting(pInfo);
	return cSingleJob.OnPreparePrinting(pInfo);
}

void CTestPrintFormView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (bCheck) cMultiJob.OnBeginPrinting(pDC, pInfo);
	else cSingleJob.OnBeginPrinting(pDC, pInfo);
}

void CTestPrintFormView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (bCheck) cMultiJob.OnEndPrinting(pDC, pInfo);
	else cSingleJob.OnEndPrinting(pDC, pInfo);
}

void CTestPrintFormView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if (bCheck) cMultiJob.OnPrint(pDC, pInfo);
	else cSingleJob.OnPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormView diagnostics

#ifdef _DEBUG
void CTestPrintFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestPrintFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTestPrintFormDoc* CTestPrintFormView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestPrintFormDoc)));
	return (CTestPrintFormDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormView message handlers

void CTestPrintFormView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	wndList.InsertColumn(0, "Field 1", LVCFMT_LEFT, 80);
	wndList.InsertColumn(1, "Field 2", LVCFMT_LEFT, 300);
	
	CString cs;
	for (int t = 0; t < 200; t++)
	{
		cs.Format("%d", t);
		int idx = wndList.InsertItem(t, cs);
		cs.Format("Field 2 of item %d", t);
		wndList.SetItemText(idx, 1, cs);
	}
}

void CTestPrintFormView::OnTest() 
{
	CTestPrintFormDlg dlg;
	dlg.DoModal();
}
