// ApBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TaskBar.h"
#include "ApBarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MOREWORK    1

/////////////////////////////////////////////////////////////////////////////
// CAppBarDlg dialog


CAppBarDlg::CAppBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppBarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_bMoving = FALSE;
    m_bAppRegistered = FALSE;
}


void CAppBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppBarDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppBarDlg, CDialog)
	//{{AFX_MSG_MAP(CAppBarDlg)
	ON_WM_CREATE()
	ON_WM_DESTROY()
    ON_WM_ACTIVATE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppBarDlg message handlers


int CAppBarDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    m_pAppBar = new CAppBar (m_hWnd);
    ASSERT (m_pAppBar);

	POPTIONS pOptions;
	LOGFONT lf;

	// Initialize the common control DLL
	InitCommonControls();

	// Allocate an OPTIONS struct and attach to the appbar
	pOptions = (POPTIONS) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OPTIONS));
	if (pOptions)
    {
		SetWindowLong (m_hWnd, 0, (LONG) pOptions);
    }
	else
    {
		return FALSE;
    }

	pOptions->fAutoHide = FALSE;
	pOptions->fOnTop = FALSE;
	pOptions->uSide = ABE_TOP;
	pOptions->cxWidth = CX_DEFWIDTH;
	pOptions->cyHeight = CY_DEFHEIGHT;

	// Register the appbar and attach it to the top by default
	m_pAppBar->Register ();
	m_pAppBar->SetSide (ABE_TOP);

	// Create the fonts for drawing in the client area
	ZeroMemory (&lf, sizeof(LOGFONT));
	lf.lfHeight = 45;
	lf.lfEscapement = 2700;
	lf.lfOrientation = 0;
	lstrcpy (lf.lfFaceName, DEFAULT_FONT);
	m_hFontLeft = CreateFontIndirect(&lf);

	lf.lfEscapement = 0;
	m_hFontTop = CreateFontIndirect(&lf);
		
    return TRUE;
}

void CAppBarDlg::OnDestroy() 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK
    CDialog::OnDestroy();
#else
    POPTIONS pOptions = m_pAppBar->GetAppbarData();

	// Make sure the appbar is unregistered
	if (m_bAppRegistered)
	{
        // MOREWORK
		// SendMessage(WM_COMMAND, MAKEWPARAM(ID_APPBAR_UNREGISTER, 0), 0L);
	}

	// Free the OPTIONS struct associated with the appbar
	HeapFree(GetProcessHeap(), 0, pOptions);

	// Clean up the GDI objects we allocated
	DeleteObject(m_hFontTop);
	DeleteObject(m_hFontLeft);

    // Indicate that the message loop should exit since the main window
    // is being destroyed.

    // MOREWORK
    // PostQuitMessage(0);
#endif

    if (m_pAppBar)
    {
        delete m_pAppBar;
        m_pAppBar = NULL;
    }

}

void CAppBarDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK
	
    CWnd::OnActivate(nState, pWndOther, bMinimized);

#else
	
	APPBARDATA abd;
	
	// Always send the activate message to the system
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	abd.lParam = 0;                
	SHAppBarMessage(ABM_ACTIVATE, &abd);

	// Now determine if we're getting or losing activation
	switch (nState)
	{
		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			// If we're gaining activation, make sure we're visible
			m_pAppBar->UnHide();
			KillTimer(IDT_AUTOHIDE);
			break;

		case WA_INACTIVE:
			// If we're losing activation, check to see if we need to autohide.
			m_pAppBar->Hide();
			break;
	}

#endif
}

void CAppBarDlg::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK

	CWnd::OnWindowPosChanged(lpwndpos);

#else
	
	APPBARDATA abd;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	abd.lParam = 0;

	SHAppBarMessage (ABM_WINDOWPOSCHANGED, &abd);

    // DefWindowProc needs this to generate the WM_SIZE message.
	CWnd::OnWindowPosChanged(lpwndpos);

#endif
}

void CAppBarDlg::OnSize(UINT nType, int cx, int cy) 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK

	CDialog::OnSize(nType, cx, cy);

#else

	POPTIONS pOpt = m_pAppBar->GetAppbarData();
	RECT rcWindow;

	if (m_bMoving || pOpt->fAutoHide)
    {
		return;
    }

	// If the client width or height is zero, spew out a warning.
	if (!pOpt->fHiding && ((cx == 0) || (cy == 0)))
    {
		TRACE (TEXT("Client area has a zero dimension!\r\n"));
    }

	// Let the system know the appbar size has changed
	m_pAppBar->Size ();

	// Update the stored height and widths if the appbar is not hidden
	if (!pOpt->fHiding)
	{
		GetWindowRect(&rcWindow);

		if (pOpt->uSide == ABE_TOP || pOpt->uSide == ABE_BOTTOM)
        {
			pOpt->cyHeight = rcWindow.bottom - rcWindow.top;
        }
		else
        {
			pOpt->cxWidth = rcWindow.right - rcWindow.left;
        }

		TRACE (TEXT("Main_OnSize: cxWidth = %d, cyHeight = %d\r\n"),
				 pOpt->cxWidth, pOpt->cyHeight);
	}

#endif	
}

void CAppBarDlg::OnMove(int x, int y) 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK

	CDialog::OnMove(x, y);

#else
	
	POPTIONS pOpt = m_pAppBar->GetAppbarData();

	if (m_bMoving || pOpt->fAutoHide)
    {
		return;
    }

	m_pAppBar->Size();

#endif
}

void CAppBarDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CAppBarDlg::OnTimer(UINT nIDEvent) 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK

    CDialog::OnTimer(nIDEvent);

#else

	POPTIONS pOpt = m_pAppBar->GetAppbarData();
	POINT pt;
	RECT rc;
	HWND hwndActive;

	switch (nIDEvent)
	{
        // The AUTOHIDE timer has fired.  Check to see if the mouse is over our
        // window and if not hide the appbar.
		case IDT_AUTOHIDE:
			if ((pOpt->fAutoHide) && (!pOpt->fHiding))
			{
                // Get the mouse position, the window position, and active 
                // window
			 	GetCursorPos(&pt);
				GetWindowRect(&rc);
                hwndActive = (HWND) GetForegroundWindow();

                // If the mouse is outside of our window, or we are not active,
                // or at least one window is active, or we are not the parent
                // of an active window, the hide the appbar window.
				if ((!PtInRect(&rc, pt)) && (hwndActive != m_hWnd) && 
					(hwndActive != NULL) /*MOREWORK && (GetWindowOwner(hwndActive) != hwnd)*/)
				{
					KillTimer (nIDEvent);
					m_pAppBar->Hide ();
				}
			}
			break;

        // The period between the time the user has entered our window and the 
        // time we should show the window has expired.  
		case IDT_AUTOUNHIDE:
            // Kill the timer, we only need it to fire once.
			KillTimer (nIDEvent);

			GetWindowRect (&rc);
			if ((pOpt->fAutoHide) && (pOpt->fHiding))
			{
                // Check to see if the cursor is still in the appbar.  If so,
                // the unhide the window.
				GetCursorPos(&pt);
				if (PtInRect(&rc, pt))
                {
					m_pAppBar->UnHide ();
                }
			}
			break;
	}

#endif
}

UINT CAppBarDlg::OnNcHitTest(CPoint point) 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK

	return CWnd::OnNcHitTest(point);

#else

	POPTIONS pOpt = m_pAppBar->GetAppbarData ();
	LRESULT  lHitTest;

	// Take care of the autohide stuff if needed
	m_pAppBar->SetAutoUnhideTimer ();

	// Let DefWindowProc() tell us where the mouse is
	lHitTest = CWnd::OnNcHitTest(point);

	// We want to disable sizing in all directions except the inside edge.
	if ((pOpt->uSide == ABE_TOP) && (lHitTest == HTBOTTOM))
		return HTBOTTOM;
	
	if ((pOpt->uSide == ABE_BOTTOM) && (lHitTest == HTTOP))
		return HTTOP;

	if ((pOpt->uSide == ABE_LEFT) && (lHitTest == HTRIGHT))
		return HTRIGHT;

	if ((pOpt->uSide == ABE_RIGHT) && (lHitTest == HTLEFT))
		return HTLEFT;


	return HTCLIENT;							

#endif
}

void CAppBarDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK

	CDialog::OnLButtonDown(nFlags, point);

#else

	POPTIONS pOpt = m_pAppBar->GetAppbarData();

	m_bMoving = TRUE;
	SetCapture();	

#endif
}

void CAppBarDlg::OnMouseMove(UINT nFlags, CPoint point) 
{

    ASSERT (m_pAppBar);

#ifdef MOREWORK

	CDialog::OnMouseMove(nFlags, point);

#else

   	POINT ptCursor = {point.x, point.y};
	LONG cxScreen, cyScreen;
	DWORD dx, dy;
	WORD horiz, vert;
	POPTIONS pOpt = m_pAppBar->GetAppbarData();
	APPBARDATA abd;

	// If we're not currently in the middle of moving the appbar window,
	// there's nothing to do.
	if (!m_bMoving)
    {
		return;
    }

	// Convert the mouse position to screen coordinates
	ClientToScreen(&ptCursor);

	// Find out which edge of the screen we're closest to
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);

	if (ptCursor.x < (cxScreen / 2))
	{
		dx = ptCursor.x;
		horiz = ABE_LEFT;
	}
	else
	{
		dx = cxScreen - ptCursor.x;
		horiz = ABE_RIGHT;
	}

	if (ptCursor.y < (cyScreen / 2))
	{
		dy = ptCursor.y;
		vert = ABE_TOP;
	}
	else
	{
		dy = cyScreen - ptCursor.y;
		vert = ABE_BOTTOM;
	}

	// Build a drag rectangle based on the edge of the screen that we're 
	// closest to.
	if ((cxScreen * dy) > (cyScreen * dx))
	{
		m_rcDrag.top = 0;
		m_rcDrag.bottom = cyScreen;
		if (horiz == ABE_LEFT)
		{
			m_rcDrag.left = 0;
			m_rcDrag.right = m_rcDrag.left + pOpt->cxWidth;
			pOpt->uSide = ABE_LEFT;
		}
		else
		{
			m_rcDrag.right = cxScreen;
			m_rcDrag.left = m_rcDrag.right - pOpt->cxWidth;
			pOpt->uSide = ABE_RIGHT;
		}
	}
	else
	{
		m_rcDrag.left = 0;
		m_rcDrag.right = cxScreen;
		if (vert == ABE_TOP)
		{
			m_rcDrag.top = 0;
			m_rcDrag.bottom = m_rcDrag.top + pOpt->cyHeight;
			pOpt->uSide = ABE_TOP;
		}
		else
		{
			m_rcDrag.bottom = cyScreen;
			m_rcDrag.top = m_rcDrag.bottom - pOpt->cyHeight;
			pOpt->uSide = ABE_BOTTOM;
		}
	}			

	// Finally, make sure this is an OK position with the system and move
	// the window.
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;

	m_pAppBar->QueryPos (&m_rcDrag);
	MoveWindow(m_rcDrag.left, m_rcDrag.top, 
			   m_rcDrag.right - m_rcDrag.left, 
			   m_rcDrag.bottom - m_rcDrag.top, 
			   TRUE);

#endif
}

void CAppBarDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
    ASSERT (m_pAppBar);

#ifdef MOREWORK

    CDialog::OnLButtonUp(nFlags, point);

#else

	APPBARDATA abd;
	POPTIONS pOpt = m_pAppBar->GetAppbarData();

	if (!m_bMoving)
    {
		return;
    }

	// Update the global appbar rect used when we're autohiding.  This is
	// sloppy but it works for now.  It would be better to maintain two rects,
	// one for the hidden state and one for the unhidden state.
	m_pAppBar->m_rcAppBar = m_rcDrag;

	// Clean up the drag state info.
	ReleaseCapture();				

	// Calculate the hidden rect if we need to and then tell the system about
	// our new area.
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;

	if (pOpt->fAutoHide)
	{
		switch (pOpt->uSide)
		{
			case ABE_TOP:
				m_rcDrag.bottom = m_rcDrag.top + 2; 
				break;
			case ABE_BOTTOM:
				m_rcDrag.top = m_rcDrag.bottom - 2;
				break;
			case ABE_LEFT:
				m_rcDrag.right = m_rcDrag.left + 2;
				break;
			case ABE_RIGHT:
				m_rcDrag.left = m_rcDrag.right - 2;
				break;
		}
	}

	m_pAppBar->QuerySetPos(pOpt->uSide, &m_rcDrag, &abd, FALSE);

	m_bMoving = FALSE;

#endif
}
