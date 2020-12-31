// FullScreenView.cpp : implementation of the CFullScreenView class
//

#include "stdafx.h"
#include "FullScreen.h"

#include "FullScreenDoc.h"
#include "FullScreenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullScreenView

IMPLEMENT_DYNCREATE(CFullScreenView, CEditView)

BEGIN_MESSAGE_MAP(CFullScreenView, CEditView)
	//{{AFX_MSG_MAP(CFullScreenView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFullScreenView construction/destruction

CFullScreenView::CFullScreenView()
{
	// TODO: add construction code here

}

CFullScreenView::~CFullScreenView()
{
}

BOOL CFullScreenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFullScreenView drawing

void CFullScreenView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	CFullScreenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFullScreenView printing

BOOL CFullScreenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFullScreenView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CEditView::OnBeginPrinting(pDC,pInfo);
}

void CFullScreenView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CEditView::OnEndPrinting(pDC,pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CFullScreenView diagnostics

#ifdef _DEBUG
void CFullScreenView::AssertValid() const
{
	CEditView::AssertValid();
}

void CFullScreenView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CFullScreenDoc* CFullScreenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFullScreenDoc)));
	return (CFullScreenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFullScreenView message handlers


void CFullScreenView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	
	CEditView::OnPrepareDC(pDC, pInfo);
}

int CFullScreenView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CString sDescription;
	sDescription.LoadString(IDS_STRING_DESCRIPTION);
	SetWindowText(sDescription);
	return 0;
}
