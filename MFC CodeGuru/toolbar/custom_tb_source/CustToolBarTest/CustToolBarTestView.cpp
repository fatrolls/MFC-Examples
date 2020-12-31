// CustToolBarTestView.cpp : implementation of the CCustToolBarTestView class
//

#include "stdafx.h"
#include "CustToolBarTest.h"

#include "CustToolBarTestDoc.h"
#include "CustToolBarTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestView

IMPLEMENT_DYNCREATE(CCustToolBarTestView, CView)

BEGIN_MESSAGE_MAP(CCustToolBarTestView, CView)
	//{{AFX_MSG_MAP(CCustToolBarTestView)
	ON_COMMAND(ID_USER_TOOL1, OnUserTool1)
	ON_COMMAND(ID_USER_TOOL2, OnUserTool2)
	ON_COMMAND(ID_USER_TOOL3, OnUserTool3)
	ON_UPDATE_COMMAND_UI(ID_USER_TOOL3, OnUpdateUserTool3)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestView construction/destruction

CCustToolBarTestView::CCustToolBarTestView()
{
	// TODO: add construction code here

}

CCustToolBarTestView::~CCustToolBarTestView()
{
}

BOOL CCustToolBarTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestView drawing

void CCustToolBarTestView::OnDraw(CDC* pDC)
{
	CCustToolBarTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestView printing

BOOL CCustToolBarTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCustToolBarTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCustToolBarTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestView diagnostics

#ifdef _DEBUG
void CCustToolBarTestView::AssertValid() const
{
	CView::AssertValid();
}

void CCustToolBarTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCustToolBarTestDoc* CCustToolBarTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustToolBarTestDoc)));
	return (CCustToolBarTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustToolBarTestView message handlers

void CCustToolBarTestView::OnUserTool1() 
{
	MessageBox ("User Tool 1");
}

void CCustToolBarTestView::OnUserTool2() 
{
	MessageBox ("User Tool 2");
}

// Check buttons demo!
static BOOL bOnOff = TRUE;

void CCustToolBarTestView::OnUserTool3() 
{
	bOnOff = !bOnOff;	
}

void CCustToolBarTestView::OnUpdateUserTool3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (bOnOff);
}
