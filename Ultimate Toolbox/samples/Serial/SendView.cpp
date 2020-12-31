// SendView.cpp : implementation file
//

#include "stdafx.h"
#include "serial.h"
#include "SendView.h"

#include "SerialDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendView

IMPLEMENT_DYNCREATE(CSendView, CEditView)

CSendView::CSendView()
{
	m_font.m_hObject = NULL;
}

CSendView::~CSendView()
{
	m_font.DeleteObject();
}

BOOL CSendView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL | WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

BEGIN_MESSAGE_MAP(CSendView, CEditView)
	//{{AFX_MSG_MAP(CSendView)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendView drawing

void CSendView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSendView diagnostics

#ifdef _DEBUG
void CSendView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSendView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSerialDoc* CSendView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSerialDoc)));
	return (CSerialDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSendView message handlers


void CSendView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	// Create a new font for this view
	if (m_font.m_hObject == NULL)
	{
		if (m_font.CreatePointFont(110, _T("Arial")))
			SetFont(&m_font);
	}
}

void CSendView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CSerialDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Route this message to the document class whereupon the keystroke will
	// be send through to the receiving end.
	if (pDoc != NULL)
	{
		for (UINT n = 0; n < nRepCnt; n++)
		{
			if (!pDoc->SendKeyDown(nChar))
				;
		}
	}
	
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}
