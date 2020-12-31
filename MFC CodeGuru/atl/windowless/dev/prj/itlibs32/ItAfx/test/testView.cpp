// testView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "test.h"
#include "OccEx.h"

#include "testDoc.h"
#include "testView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	m_pCtrl = new CWindowlessControl;
}

CTestView::~CTestView()
{
	delete m_pCtrl;
	m_pCtrl = NULL;
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_pCtrlCont)
		STATIC_DOWNCAST(COleControlContainerEx, m_pCtrlCont)->OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	if (m_pCtrl->m_hWnd == NULL)
	{
		CRect rect(40, 40, 200, 200);
//		VERIFY(m_pCtrl->CreateControl("{CE963B33-54D6-11D1-B3E4-0020AF905F9C}", 
		if(!m_pCtrl->CreateControl("Forms.CheckBox.1", 
			NULL, WS_CHILD | WS_VISIBLE,
			rect, this, 1))
		{
			TRACE("Could not create control\n");
		}
		else if (m_pCtrl->m_hWnd)
		{
			TRACE("Control created with window %X\n", m_pCtrl->m_hWnd);
		}
		else
		{
			TRACE("Control created windowless\n");
		}
	}
}
