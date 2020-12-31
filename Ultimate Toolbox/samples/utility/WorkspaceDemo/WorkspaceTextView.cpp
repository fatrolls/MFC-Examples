// WorkspaceDemoView.cpp : implementation of the CWorkspaceTextView class
//
//====================================================================
//===============  Dundas Software ==================================
//===================================================================

#include "stdafx.h"
#include "WorkspaceDemo.h"

#include "WorkspaceTextDoc.h"
#include "WorkspaceTextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextView

IMPLEMENT_DYNCREATE(CWorkspaceTextView, CEditView)

BEGIN_MESSAGE_MAP(CWorkspaceTextView, CEditView)
	//{{AFX_MSG_MAP(CWorkspaceTextView)
	ON_COMMAND(ID_SQUARE, OnSquare)
	ON_COMMAND(ID_CIRCLE, OnCircle)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_COMMAND(ID_WINDOW_NEWLENGTHWINDOW, OnWindowNewlengthwindow)
	ON_COMMAND(ID_WINDOW_NEWTEXTWINDOW, OnWindowNewtextwindow)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextView construction/destruction

CWorkspaceTextView::CWorkspaceTextView()
{
	// TODO: add construction code here

}

CWorkspaceTextView::~CWorkspaceTextView()
{
}

BOOL CWorkspaceTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextView drawing

void CWorkspaceTextView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	CWorkspaceTextDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextView printing

BOOL CWorkspaceTextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CWorkspaceTextView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CWorkspaceTextView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextView diagnostics

#ifdef _DEBUG
void CWorkspaceTextView::AssertValid() const
{
	CEditView::AssertValid();
}

void CWorkspaceTextView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CWorkspaceTextDoc* CWorkspaceTextView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkspaceTextDoc)));
	return (CWorkspaceTextDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTextView message handlers

void CWorkspaceTextView::OnSquare() 
	{
	AfxMessageBox(_T("You clicked the square"));
	}

void CWorkspaceTextView::OnCircle() 
	{
	AfxMessageBox(_T("You clicked the circle"));
	}

void CWorkspaceTextView::OnChange() 
	{
	CString sText;
	GetEditCtrl().GetWindowText(sText);
	if (GetDocument()->SetText(sText))
		GetDocument()->UpdateAllViews(this);
	
	}

void CWorkspaceTextView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
	{
	UNREFERENCED_PARAMETER(pSender);
	UNREFERENCED_PARAMETER(lHint);
	UNREFERENCED_PARAMETER(pHint);

	CString sText = GetDocument()->GetText();
	GetEditCtrl().SetWindowText(sText);
	}

void CWorkspaceTextView::OnInitialUpdate() 
	{
	CEditView::OnInitialUpdate();
	}

void CWorkspaceTextView::OnWindowNewlengthwindow() 
	{
	CFrameWnd * pFrame =
         ((CWorkspaceDemoApp*)AfxGetApp())->m_pLengthDocTemplate->CreateNewFrame(GetDocument(), GetParentFrame());
	((CWorkspaceDemoApp*)AfxGetApp())->m_pLengthDocTemplate->InitialUpdateFrame(pFrame, GetDocument());
	}

void CWorkspaceTextView::OnWindowNewtextwindow() 
	{
	CFrameWnd * pFrame =
         ((CWorkspaceDemoApp*)AfxGetApp())->m_pTextDocTemplate->CreateNewFrame(GetDocument(), GetParentFrame());
	((CWorkspaceDemoApp*)AfxGetApp())->m_pTextDocTemplate->InitialUpdateFrame(pFrame, GetDocument());
	}
