// ProgressBar.cpp : implementation file

/////////////////////////////////////////////////////////////////////////////
// CProgressBar -  status bar progress control
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au), 1997
// Please feel free to use and distribute.
	
#include "stdafx.h"
#include "ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CProgressBar, CProgressCtrl)

BEGIN_MESSAGE_MAP(CProgressBar, CProgressCtrl)
	//{{AFX_MSG_MAP(CProgressBar)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CProgressBar::CProgressBar()
{
	m_bSuccess = FALSE;
}

CProgressBar::CProgressBar(LPCTSTR strMessage, int nSize /* = 100 */, 
	                       int MaxValue /* = 100 */)
{
	Create(strMessage, nSize, MaxValue);
}

CProgressBar::~CProgressBar()
{
	Clear();
}	

CStatusBar* CProgressBar::GetStatusBar()
{
	CFrameWnd *pFrame = (CFrameWnd*)AfxGetMainWnd();
	if (!pFrame || !pFrame->IsKindOf(RUNTIME_CLASS(CFrameWnd))) 
	    return NULL;

	CStatusBar* pBar = (CStatusBar*) pFrame->GetMessageBar();
	if (!pBar || !pBar->IsKindOf(RUNTIME_CLASS(CStatusBar))) 
	    return NULL;

	return pBar;
}

// Create the CProgressCtrl as a child of the status bar positioned
// over the first pane, extending "nSize" percentage across pane.
// Sets the range to be 0 to MaxValue, with a step of 1.
BOOL CProgressBar::Create(LPCTSTR strMessage, int nSize, int MaxValue)
{
	m_bSuccess = FALSE;
	
	CStatusBar *pStatusBar = GetStatusBar();
	if (!pStatusBar) return FALSE;

	// Create the progress bar
	VERIFY(m_bSuccess = CProgressCtrl::Create(WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), 
	    pStatusBar, 1));
	if (!m_bSuccess) return FALSE;

	// Set range and step
	SetRange(0, MaxValue);
	SetStep(1);

	m_strMessage = strMessage;
	m_nSize	     = nSize;

	// Resize the control to its desired width
	Resize();

	return TRUE;
}

void CProgressBar::Clear()
{
	// Hide the window. This is necessary so that a cleared
	// window is not redrawn if "Resise" is called
	ModifyStyle(WS_VISIBLE, 0);

	// Get the IDLE_MESSAGE
	CString str;
	str.LoadString(AFX_IDS_IDLEMESSAGE);

	// Place the IDLE_MESSAGE in the status bar 
	CStatusBar *pStatusBar = GetStatusBar();
	if (pStatusBar) pStatusBar->SetWindowText(str);
}

void CProgressBar::SetRange(int nLower, int nUpper, int nStep /* = 1 */)	
{
	if (!m_bSuccess) return;
	CProgressCtrl::SetRange(nLower, nUpper);
	CProgressCtrl::SetStep(nStep);
}

int CProgressBar::SetPos(int nPos)	 
{
	ModifyStyle(0,WS_VISIBLE);
	return (m_bSuccess)? CProgressCtrl::SetPos(nPos) : 0;
}

int  CProgressBar::OffsetPos(int nPos) 
{ 
	ModifyStyle(0,WS_VISIBLE);
	return (m_bSuccess)? CProgressCtrl::OffsetPos(nPos) : 0;
}

int  CProgressBar::SetStep(int nStep)
{ 
	ModifyStyle(0,WS_VISIBLE);
	return (m_bSuccess)? CProgressCtrl::SetStep(nStep) : 0;	
}

int  CProgressBar::StepIt()			 
{ 
	ModifyStyle(0,WS_VISIBLE);
	return (m_bSuccess)? CProgressCtrl::StepIt() : 0;	
}

void CProgressBar::Resize() 
{	
	CStatusBar *pStatusBar = GetStatusBar();
	if (!pStatusBar) return;

	// Redraw the window text
	if (::IsWindow(m_hWnd) && IsWindowVisible()) {
	    pStatusBar->SetWindowText(m_strMessage);
	    pStatusBar->UpdateWindow();
	}

	// Calculate how much space the text takes up
	CClientDC dc(pStatusBar);
	CFont *pOldFont = dc.SelectObject(pStatusBar->GetFont());
	CSize size = dc.GetTextExtent(m_strMessage);		// Length of text
	int margin = dc.GetTextExtent(_T(" ")).cx * 2;		// left hand margin
	dc.SelectObject(pOldFont);

	// Now calculate the rectangle in which we will draw the progress bar
	CRect rc;
	pStatusBar->GetItemRect (0, rc);
	rc.left = size.cx + margin;
	rc.right = rc.left + (rc.right - rc.left) * m_nSize / 100;
	if (rc.right < rc.left) rc.right = rc.left;
	
	// Leave a litle vertical margin (10%) between the top and bottom of the bar
	int Height = rc.bottom - rc.top;
	rc.bottom -= Height/10;
	rc.top    += Height/10;

	// Resize the window
	if (::IsWindow(m_hWnd))
	    MoveWindow(&rc);
}

BOOL CProgressBar::OnEraseBkgnd(CDC* pDC) 
{
	Resize();
	return CProgressCtrl::OnEraseBkgnd(pDC);
}