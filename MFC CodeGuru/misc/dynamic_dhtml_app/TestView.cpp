// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "InstForm.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CBrowserView)

BEGIN_MESSAGE_MAP(CTestView, CBrowserView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(ID_INSTRUCTOR_FORM, OnInstructorForm)
	ON_COMMAND(ID_STUDENT_FORM, OnStudentForm)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TEST_MENU, OnTestCommand)
	ON_COMMAND(ID_NEXT, OnNext)
	ON_COMMAND(ID_FIRST, OnFirst)
	ON_COMMAND(ID_LAST, OnLast)
	ON_COMMAND(ID_PREV, OnPrev)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	m_pForm = NULL;
}

CTestView::~CTestView()
{
	delete m_pForm;
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBrowserView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CBrowserView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CBrowserView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::OnInstructorForm() 
{
	delete m_pForm;

	m_pForm  = new CInstForm();

	LoadForm(m_pForm);	
}


void CTestView::OnStudentForm() 
{
//The student form can also be implemented similarily
	
//	delete m_pForm;

//	m_pForm = new CStudentForm();

//	LoadForm(m_pForm);
	
}

void CTestView::OnAppAbout() 
{
	delete m_pForm;
	
	CString strURL = AfxGetApp()->GetProfileString("URLS", "AboutBox", NULL);
	if (strURL.IsEmpty())
	{
		strURL = "http://www.codeguru.com";
	}
	
	m_pForm = new CHTMLForm(strURL);
	LoadForm(m_pForm);
}

void CTestView::OnContextMenu(POINT pt)
{
	CMenu menu;

	menu.LoadMenu(IDR_TEST_MENU);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, AfxGetMainWnd());
}

void CTestView::OnTestCommand() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("This is just to show that/nIE4 context Menu can be replaced");

}

void CTestView::OnNext() 
{
	m_pForm->ExecuteCmd("Next/");	
}

void CTestView::OnFirst() 
{
	m_pForm->ExecuteCmd("MoveFirst/");	
}

void CTestView::OnLast() 
{
	m_pForm->ExecuteCmd("Last/");
	
}

void CTestView::OnPrev() 
{
		m_pForm->ExecuteCmd("Previous/");
	
}
