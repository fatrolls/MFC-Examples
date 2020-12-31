// SerialView.cpp : implementation of the CSerialView class
//

#include "stdafx.h"
#include "Serial.h"

#include "SerialDoc.h"
#include "SerialView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialView

IMPLEMENT_DYNCREATE(CSerialView, CEditView)

BEGIN_MESSAGE_MAP(CSerialView, CEditView)
	//{{AFX_MSG_MAP(CSerialView)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(IDM_OUTPUT, OnOutput)
	ON_MESSAGE(IDM_BACKSPACE, OnBackspace)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerialView construction/destruction

CSerialView::CSerialView()
{
	m_font.m_hObject = NULL;

	// Assign custom colours for the view
	m_clrText = RGB(255, 255, 255);		// while
	m_clrBkgnd = RGB(0, 0, 128);		// blue
	m_brBkgnd.CreateSolidBrush(m_clrBkgnd);
}

CSerialView::~CSerialView()
{
	if (m_font.m_hObject != NULL)
		m_font.DeleteObject();
}

BOOL CSerialView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL | WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CSerialView drawing

void CSerialView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	CSerialDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSerialView diagnostics

#ifdef _DEBUG
void CSerialView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSerialView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSerialDoc* CSerialView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSerialDoc)));
	return (CSerialDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSerialView message handlers

void CSerialView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	GetEditCtrl().SetReadOnly(TRUE);
	
	//
	// Create the font for this view
	//
	if (m_font.m_hObject == NULL)
	{
		if (m_font.CreatePointFont(95, _T("Fixedsys")))
			SetFont(&m_font);
	}

	// Output some text
	Output(_T("Serial - An Ultimate Toolbox Sample Application\r\n"));
	Output(_T("Copyright 1998 by The Code Project - http://www.theUltimateToolbox.com\r\n"));
	Output(_T("----------------------------------------------------------\r\n\r\n\r\n"));
}

HBRUSH CSerialView::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	UNREFERENCED_PARAMETER(nCtlColor);

	//
	// Use custom colours to paint the control
	//
	pDC->SetTextColor(m_clrText);
	pDC->SetBkColor(m_clrBkgnd);
	return m_brBkgnd;
}

void CSerialView::Output(LPCTSTR pszOutput, ...)
{
	//
	// void Output(LPCTSTR pszOutput, ...)
	//
	// Outputs a formatted string to the edit window
	//
	// IN
	//    pszOutput: A format-control string.
	//
	// OUT
	//    none
	//
	// RETURN
	//    none

	int nLength = GetEditCtrl().GetWindowTextLength();
	TCHAR szBuffer[1024];
	
	va_list argptr;

	va_start(argptr, pszOutput);
	_vstprintf(szBuffer, pszOutput, argptr);
	va_end(argptr);
	GetEditCtrl().SetSel(nLength, nLength);
	GetEditCtrl().ReplaceSel(szBuffer);
}

void CSerialView::Backspace()
{
	int nLength = GetEditCtrl().GetWindowTextLength();
	
	GetEditCtrl().SetReadOnly(FALSE);
	GetEditCtrl().SetSel(nLength - 1, nLength);
	GetEditCtrl().Clear();		
	GetEditCtrl().SetReadOnly(TRUE);
}

LONG CSerialView::OnOutput(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);

	//
	// This message is sent from the IncomingTextThread function
	// on receipt of an incoming character notification.  The
	// character (string) is pointed to by lParam
	Output((LPCTSTR) lParam);
	return 0;
}

LONG CSerialView::OnBackspace(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	//
	// This message is sent from the IncomingTextThread function
	// on receipt of an incoming character notification.  The
	// character is always the backspace character
	Backspace();
	return 0;
}
