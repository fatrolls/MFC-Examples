// CalcKey.cpp : implementation file
//

#include "stdafx.h"
#include "calckey.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalcKey

IMPLEMENT_SHAPECLASS(CCalcKey)

// Constructor
CCalcKey::CCalcKey()
{
	m_bHasFocus = FALSE;
	m_bIsPressed = FALSE;
	m_crText = GetSysColor(COLOR_WINDOWTEXT);
	m_crBk = GetSysColor(COLOR_WINDOW);
	m_crAnimText = m_crText;
	m_crAnimBk = m_crBk;
}

// Destructor
CCalcKey::~CCalcKey()
{
	// Destroy the associated window if necessary
	if(::IsWindow(GetSafeHwnd()))
		DestroyWindow();
}

// Sets the colors used for normal and pressed (animated) state
void CCalcKey::SetColors(COLORREF crText, COLORREF crBk, COLORREF crAnimText, 
									COLORREF crAnimBk)
{
	m_crText = (crText==-1?GetSysColor(COLOR_BTNTEXT):crText);
	m_crBk = (crBk==-1?GetSysColor(COLOR_BTNFACE):crBk);
	m_crAnimText = (crAnimText==-1?m_crText:m_crAnimText);
	m_crAnimBk = (m_crAnimBk==-1?m_crBk:crAnimBk);
}

BEGIN_MESSAGE_MAP(CCalcKey, CWnd)
	//{{AFX_MSG_MAP(CCalcKey)
	ON_WM_PAINT()
	ON_MESSAGE(WM_SETTEXT,OnSetText)
	ON_MESSAGE(WM_GETTEXT,OnGetText)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCalcKey message handlers

// Destroy CCalcKey class - MUST DO THIS for your custom controls
void CCalcKey::PostNcDestroy() 
{
	CWnd::PostNcDestroy();

	// Need to force the destructor the be called since MFC didn't
	// create and attach this class -- otherwise we have memory leaks
	delete this;
}

// Handles WM_SETTEXT Windows message
LONG CCalcKey::OnSetText(WPARAM, LPARAM lParam)
{
	// Save the text
	m_strTitle = (LPCTSTR) lParam;
	Invalidate();

	return(0L);
}

// Handles WM_GETTEXT Windows message
LONG CCalcKey::OnGetText(WPARAM wParam, LPARAM lParam)
{
	int nChars = __min((int)wParam,m_strTitle.GetLength());
	LPTSTR lpszOut = (LPTSTR) lParam;

	// Copy out the text
	UTBStr::tcsncpy(lpszOut, nChars + 1, (LPCTSTR) m_strTitle,nChars);

	// NULL terminate it
	*(lpszOut+nChars) = _T('\0');

	return(nChars);
}

// Handles button painting (normal or pressed state)
void CCalcKey::OnPaint() 
{
	CPaintDC dc(this);

	RECT rc;
	CBrush brNormal(m_crBk);
	CBrush brAnim(m_crAnimBk);

	// Fill the button with the specified color
	// Notice that we can use FillRect(), the visible region takes care of
	// only filling the selected shape
	GetClientRect(&rc);
	dc.FillRect(&rc,m_bIsPressed?&brAnim:&brNormal);

	// Draw the button's text
	TCHAR szTemp[500];
	COLORREF crOldText = dc.SetTextColor(m_bIsPressed?m_crAnimText:m_crText);
	int nOldMode = dc.SetBkMode(TRANSPARENT);
	GetWindowText(szTemp,sizeof(szTemp));
	dc.DrawText(szTemp,-1,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

	// Draw a focus rectangle if the button has focus
	if(m_bHasFocus)
	{
		InflateRect(&rc,-6,-6);
		dc.DrawFocusRect(&rc);
	}

	// Restore everything
	dc.SetTextColor(crOldText);
	dc.SetBkMode(nOldMode);
}

// Handle the button's creation
int CCalcKey::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Set the button's initial text from its CREATESTRUCT
	if(lpCreateStruct->lpszName)
		OnSetText(0,(LPARAM)(LPCTSTR)lpCreateStruct->lpszName);

	return 0;
}

// Handles WM_LBUTTONDOWN Windows message
void CCalcKey::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(point);

	// Set focus to the selected button
	SetFocus();

	// Let the parent know that we were clicked
//	FireClick();

	// Grab the mouse
	SetCapture();
	
	// Set the pressed flag for painting
	m_bIsPressed = TRUE;

	// Paint the button in a pressed state
	Invalidate();
}

// Handles WM_LBUTTONUP Windows message
void CCalcKey::OnLButtonUp(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(point);

	// Let go of the mouse
	ReleaseCapture();

		// Let the parent know that we were clicked
	FireClick();

	// Clear the pressed flag and paint again
	m_bIsPressed = FALSE;
	Invalidate();
}

// Handles WM_SETFOCUS Windows message
void CCalcKey::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);

	// Set the focus flag
	m_bHasFocus = TRUE;

	// Repaint to draw the focus rectangle
	Invalidate();
}

// Handles WM_KILLFOCUS Windows message
void CCalcKey::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);

	// Reset the focus flag
	m_bHasFocus = FALSE;

	// Repaint to remove the focus rectangle
	Invalidate();
}

// Handles WM_KEYDOWN Windows message
void CCalcKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(nRepCnt);

	// Simulate a keyboard button press
	switch(nChar)
	{
		// SPACE key works like mouse click on a button
		case VK_SPACE:
			// Click the button then delay for a short time
			OnLButtonDown(0,0);
			SetTimer(1000,50,NULL);
			break;
	}
}

// Handles WM_TIMER Windows message
void CCalcKey::OnTimer(UINT nIDEvent) 
{
	UNREFERENCED_PARAMETER(nIDEvent);

	// Release the button click now
	KillTimer(1000);
	OnLButtonUp(0,0);
}

