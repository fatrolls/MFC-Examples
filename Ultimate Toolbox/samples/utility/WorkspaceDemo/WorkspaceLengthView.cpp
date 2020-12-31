// WorkspaceLengthView.cpp : implementation file
//

#include "stdafx.h"
#include "WorkspaceDemo.h"

#include "WorkspaceTextDoc.h"
#include "WorkspaceLengthView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceLengthView

IMPLEMENT_DYNCREATE(CWorkspaceLengthView, CFormView)

CWorkspaceLengthView::CWorkspaceLengthView()
	: CFormView(CWorkspaceLengthView::IDD)
{
	//{{AFX_DATA_INIT(CWorkspaceLengthView)
	m_sLength = _T("");
	//}}AFX_DATA_INIT
}

CWorkspaceLengthView::~CWorkspaceLengthView()
{
}

void CWorkspaceLengthView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkspaceLengthView)
	DDX_Control(pDX, IDC_LENGTH_SPIN, m_wndLengthSpin);
	DDX_Text(pDX, IDC_LENGTH, m_sLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkspaceLengthView, CFormView)
	//{{AFX_MSG_MAP(CWorkspaceLengthView)
	ON_COMMAND(ID_WINDOW_NEWTEXTWINDOW, OnWindowNewtextwindow)
	ON_COMMAND(ID_WINDOW_NEWLENGTHWINDOW, OnWindowNewlengthwindow)
	ON_EN_CHANGE(IDC_LENGTH, OnChangeLength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceLengthView diagnostics

#ifdef _DEBUG
void CWorkspaceLengthView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWorkspaceLengthView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWorkspaceTextDoc* CWorkspaceLengthView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkspaceTextDoc)));
	return (CWorkspaceTextDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceLengthView message handlers

void CWorkspaceLengthView::OnChangeLength() 
	{
	// ... Check whether we have already passed OnInitialUpdate
	if (m_wndLengthSpin.m_hWnd == NULL)
		return;

	if (!UpdateData(TRUE))
		return;
	int nNewLength = _ttoi(m_sLength);

	CString sText = GetDocument()->GetText();
	int nLength = sText.GetLength();
	if (nLength < nNewLength)
		sText += CString(_T('.'), nNewLength - nLength);
	else
		sText = sText.Left(nNewLength);
	GetDocument()->SetText(sText);

	m_sLength.Format(_T("%i"), nNewLength);
	UpdateData(FALSE);

	GetDocument()->UpdateAllViews(this);
	}

void CWorkspaceLengthView::OnInitialUpdate() 
	{
	CFormView::OnInitialUpdate();

	m_wndLengthSpin.SetRange(0, UD_MAXVAL);

	// Fit frame around view
	ResizeParentToFit(FALSE);
	}

void CWorkspaceLengthView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
	{
	UNREFERENCED_PARAMETER(pSender);
	UNREFERENCED_PARAMETER(lHint);
	UNREFERENCED_PARAMETER(pHint);

	CString sText = GetDocument()->GetText();
	m_sLength.Format(_T("%i"), sText.GetLength());
	UpdateData(FALSE);
	}

void CWorkspaceLengthView::OnWindowNewtextwindow() 
	{
	CFrameWnd * pFrame =
         ((CWorkspaceDemoApp*)AfxGetApp())->m_pTextDocTemplate->CreateNewFrame(GetDocument(), GetParentFrame());
	((CWorkspaceDemoApp*)AfxGetApp())->m_pTextDocTemplate->InitialUpdateFrame(pFrame, GetDocument());
	}

void CWorkspaceLengthView::OnWindowNewlengthwindow() 
	{
	CFrameWnd * pFrame =
         ((CWorkspaceDemoApp*)AfxGetApp())->m_pLengthDocTemplate->CreateNewFrame(GetDocument(), GetParentFrame());
	((CWorkspaceDemoApp*)AfxGetApp())->m_pLengthDocTemplate->InitialUpdateFrame(pFrame, GetDocument());
	}
