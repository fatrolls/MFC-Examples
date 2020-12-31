// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "DlgDemo2.h"
#include "OptionsDialog.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	m_nWidth = 4;
	m_nHeight = 2;
	m_nUnits = 0;
	m_pDlg = NULL;
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_USER_APPLY, OnApply)
	ON_MESSAGE (WM_USER_DIALOG_DESTROYED, OnDialogDestroyed)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // Device context for painting
	
	CBrush brush (RGB (255, 0, 255));
	CBrush* pOldBrush = dc.SelectObject (&brush);

	switch (m_nUnits) {

	case 0: // Inches
		dc.SetMapMode (MM_LOENGLISH);
		dc.Rectangle (0, 0, m_nWidth * 100, -m_nHeight * 100);
		break;

	case 1: // Centimeters
		dc.SetMapMode (MM_LOMETRIC);
		dc.Rectangle (0, 0, m_nWidth * 100, -m_nHeight * 100);
		break;

	case 2: // Pixels
		dc.SetMapMode (MM_TEXT);
		dc.Rectangle (0, 0, m_nWidth, m_nHeight);
		break;
	}
	dc.SelectObject (pOldBrush);
}

void CChildView::OnFileOptions() 
{
	//
	// If the dialog box already exists, display it.
	//
	if (m_pDlg != NULL)
		m_pDlg->SetFocus ();

	//
	// If the dialog box doesn't already exist, create it.
	//
	else {
		m_pDlg = new COptionsDialog;
		m_pDlg->m_nWidth = m_nWidth;
		m_pDlg->m_nHeight = m_nHeight;
		m_pDlg->m_nUnits = m_nUnits;
		m_pDlg->Create (IDD_OPTIONS);
		m_pDlg->ShowWindow (SW_SHOW);
	}
}

LRESULT CChildView::OnApply (WPARAM wParam, LPARAM lParam)
{
    RECTPROP* prp = (RECTPROP*) lParam;
    m_nWidth = prp->nWidth;
    m_nHeight = prp->nHeight;
    m_nUnits = prp->nUnits;
    Invalidate ();
    return 0;
}

LRESULT CChildView::OnDialogDestroyed (WPARAM wParam, LPARAM lParam)
{
	m_pDlg = NULL;
	return 0;
}
