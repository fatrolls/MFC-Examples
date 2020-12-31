// ApBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ApBarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppBarDlg dialog


CAppBarDlg::CAppBarDlg(int iResource, CWnd* pParent /*=NULL*/)
	: CDialog(iResource, pParent)
{
	//{{AFX_DATA_INIT(CAppBarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_bMoving = FALSE;
    m_bHidden = FALSE;
    m_bOnTop = FALSE;
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

	// Initialize the common control DLL
	InitCommonControls();

	// Allocate an OPTIONS struct and attach to the appbar
	pOptions = (POPTIONS) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(OPTIONS));
	if (pOptions)
    {
	    pOptions->fAutoHide = m_bHidden;
	    pOptions->fOnTop = m_bOnTop;
	    pOptions->uSide = ABE_TOP;

        // Calculate the Height and the width
        DWORD dwUnits;
        dwUnits = GetDialogBaseUnits ();
	    pOptions->cyHeight = (CY_DEFHEIGHT*HIWORD (dwUnits)) / 8;
        pOptions->cxWidth = (CX_DEFWIDTH*LOWORD (dwUnits)) / 4;

		if (!m_pAppBar->SetAppbarData (pOptions))
        {
            ASSERT (FALSE);
        }
    }
	else
    {
		return FALSE;
    }

	// Register the appbar and attach it to the top by default
	m_pAppBar->Register ();
	m_pAppBar->SetSide (ABE_TOP);

    return TRUE;
}

void CAppBarDlg::OnDestroy() 
{
    ASSERT (m_pAppBar);

    if (m_pAppBar)
    {
        POPTIONS pOptions = m_pAppBar->GetAppbarData();

	    // Make sure the appbar is unregistered
	    if (m_pAppBar->IsRegistered ())
	    {
            m_pAppBar->UnRegister ();
	    }

        delete m_pAppBar;
        m_pAppBar = NULL;
    }

    CDialog::OnDestroy ();
}

void CAppBarDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
    ASSERT (m_pAppBar);

    CWnd::OnActivate(nState, pWndOther, bMinimized);

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

}

void CAppBarDlg::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
    ASSERT (m_pAppBar);

	CWnd::OnWindowPosChanged(lpwndpos);

	APPBARDATA abd;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	abd.lParam = 0;

	SHAppBarMessage (ABM_WINDOWPOSCHANGED, &abd);

	CWnd::OnWindowPosChanged(lpwndpos);
}

void CAppBarDlg::OnSize(UINT nType, int cx, int cy) 
{
    ASSERT (m_pAppBar);

    CString strTemp;

	CDialog::OnSize(nType, cx, cy);

	POPTIONS pOpt = m_pAppBar->GetAppbarData();
	RECT rcWindow;

	if (m_bMoving || pOpt->fAutoHide)
    {
		return;
    }

	// Make sure that client area has dimension
	if (!pOpt->fHiding && ((cx == 0) || (cy == 0)))
    {
#ifdef LOG
        strTemp.LoadString (IDS_ZERO_DIMENSION);
		gLog.WriteError (strTemp);
#endif
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
 	}
}

void CAppBarDlg::OnMove(int x, int y) 
{
    ASSERT (m_pAppBar);

	CDialog::OnMove(x, y);

	POPTIONS pOpt = m_pAppBar->GetAppbarData();

	if (m_bMoving || pOpt->fAutoHide)
    {
		return;
    }

    m_pAppBar->Size();

}

void CAppBarDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Popup menu here.
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CAppBarDlg::OnTimer(UINT nIDEvent) 
{
    ASSERT (m_pAppBar);

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

    CDialog::OnTimer(nIDEvent);
}

UINT CAppBarDlg::OnNcHitTest(CPoint point) 
{
    ASSERT (m_pAppBar);

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
}

void CAppBarDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
    ASSERT (m_pAppBar);

	POPTIONS pOpt = m_pAppBar->GetAppbarData();

	m_bMoving = TRUE;
	SetCapture();	

    CDialog::OnLButtonDown(nFlags, point);
}

void CAppBarDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
    ASSERT (m_pAppBar);

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

	CDialog::OnMouseMove(nFlags, point);
}

void CAppBarDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
    ASSERT (m_pAppBar);

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

    CDialog::OnLButtonUp(nFlags, point);
}

/*
 *  ShowMenu -- Show the menu for the corresponding button
 *  
 *  iResourceID - Resource of the menu
 *  iBoldID - ID of the menu item that is the default (in bold)
 *          - if -1 then there is no default
 *  rect - Window position of the button who will contain this menu.
 */ 

BOOL CAppBarDlg::ShowMenu (const CRect& rect, int iResourceID, int iBoldID)
{
    ASSERT (m_pAppBar);

	CMenu Menu;
    CMenu *pSubMenu;

	MENUITEMINFO mii;
	POPTIONS pOptions = m_pAppBar->GetAppbarData();
	UINT uItem;
	TCHAR szMenu[64];

	// Bring up the context menu
    if (Menu.LoadMenu(iResourceID))
    {
	    pSubMenu = Menu.GetSubMenu(0);

	    // Set the default menu item
	    mii.cbSize = sizeof(MENUITEMINFO);
	    mii.fMask = MIIM_STATE;
	    mii.fState = MFS_DEFAULT;
	    
	    if (iBoldID >= 0)
        {
            SetMenuItemInfo(pSubMenu->m_hMenu, iBoldID, FALSE, &mii);
        }

	    mii.fMask = MIIM_TYPE | MIIM_STATE;
	    (LPTSTR) mii.dwTypeData = szMenu;
	    mii.cch = sizeof(szMenu);

	    GetMenuItemInfo(pSubMenu->m_hMenu, uItem, FALSE, &mii);

	    mii.fType |= MFT_RADIOCHECK;
	    mii.fState = MFS_CHECKED;

	    SetMenuItemInfo(pSubMenu->m_hMenu, uItem, FALSE, &mii);

        switch (pOptions->uSide)
        {
        case ABE_TOP:
	        TrackPopupMenu (pSubMenu->m_hMenu, 
                TPM_LEFTALIGN | TPM_TOPALIGN, 
                rect.left, 
                rect.bottom, 
                0, 
                m_hWnd, 
                NULL);	
            break;

        case ABE_LEFT:
	        TrackPopupMenu (pSubMenu->m_hMenu, 
                TPM_LEFTALIGN | TPM_TOPALIGN, 
                rect.left, 
                rect.bottom, 
                0, 
                m_hWnd, 
                NULL);	
            break;

        case ABE_RIGHT:
	        TrackPopupMenu (pSubMenu->m_hMenu, 
                TPM_RIGHTALIGN | TPM_TOPALIGN, 
                rect.right, 
                rect.bottom, 
                0, 
                m_hWnd, 
                NULL);	
            break;

        case ABE_BOTTOM:
	        TrackPopupMenu (pSubMenu->m_hMenu, 
                TPM_LEFTALIGN | TPM_BOTTOMALIGN, 
                rect.left, 
                rect.top, 
                0, 
                m_hWnd, 
                NULL);	
            break;
        }

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
