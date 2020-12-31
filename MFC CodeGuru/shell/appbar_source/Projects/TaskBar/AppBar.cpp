// AppBar.cpp: implementation of the CAppBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppBar.h"
#include <windowsx.h>
#include "utility.h"
#include "defines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAppBar::CAppBar(HWND hWnd)
{
    m_hWnd = hWnd;

    m_bAppRegistered = FALSE;

    m_pOptions = new OPTIONS;
    ASSERT (m_pOptions);
}

CAppBar::~CAppBar()
{
    if (m_pOptions)
    {
        delete m_pOptions;
        m_pOptions = NULL;
    }
}

//
//  AppBar_Size -- Handles updating the appbar's size and position.
//
void CAppBar::Size()
{
	RECT rc;
	APPBARDATA abd;
	POPTIONS pOpt;

	if (m_bAppRegistered)
	{
		pOpt = GetAppbarData ();

		abd.cbSize = sizeof(APPBARDATA);
		abd.hWnd = m_hWnd;

		GetWindowRect (m_hWnd, &rc);
		QuerySetPos (pOpt->uSide, &rc, &abd, TRUE);
	}
}

//
//  QueryPos -- Asks the system if the AppBar can occupy the rectangle specified
//           -- in lprc.  The system will change the lprc rectangle to make
//           -- it a valid rectangle on the desktop.
//

void CAppBar::QueryPos(LPRECT lprc)
{
	POPTIONS pOpt;
    pOpt = GetAppbarData ();

	APPBARDATA abd;
	int iWidth = 0;
	int iHeight = 0;

    // Fill out the APPBARDATA struct and save the edge we're moving to
    // in the appbar OPTIONS struct.
	abd.hWnd = m_hWnd;
	abd.cbSize = sizeof(APPBARDATA);
	abd.rc = *lprc;
	abd.uEdge = pOpt->uSide;

    // Calculate the part we want to occupy.  We only figure out the top
    // and bottom coordinates if we're on the top or bottom of the screen.
    // Likewise for the left and right.  We will always try to occupy the
	// full height or width of the screen edge.
	if ((ABE_LEFT == abd.uEdge) || (ABE_RIGHT == abd.uEdge))
	{
		iWidth = pOpt->cxWidth;
		abd.rc.top = 0;
		abd.rc.bottom = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		iHeight = pOpt->cyHeight;
		abd.rc.left = 0;
		abd.rc.right = GetSystemMetrics(SM_CXSCREEN);
	}

    // Ask the system for the screen space
	SHAppBarMessage(ABM_QUERYPOS, &abd);

    // The system will return an approved position along the edge we're asking
	// for.  However, if we can't get the exact position requested, the system
	// only updates the edge that's incorrect.  For example, if we want to 
	// attach to the bottom of the screen and the taskbar is already there, 
	// we'll pass in a rect like 0, 964, 1280, 1024 and the system will return
	// 0, 964, 1280, 996.  Since the appbar has to be above the taskbar, the 
	// bottom of the rect was adjusted to 996.  We need to adjust the opposite
	// edge of the rectangle to preserve the height we want.

	switch (abd.uEdge)
	{
		case ABE_LEFT:
			abd.rc.right = abd.rc.left + iWidth;
			break;

		case ABE_RIGHT:
			abd.rc.left = abd.rc.right - iWidth;
			break;

		case ABE_TOP:
			abd.rc.bottom = abd.rc.top + iHeight;
			break;

		case ABE_BOTTOM:
			abd.rc.top = abd.rc.bottom - iHeight;
			break;
	}


	*lprc = abd.rc;	
}

//
//  QuerySetPos -- Asks the system if the appbar can move itself to a particular
//              -- side of the screen and then does move the appbar.
//
void CAppBar::QuerySetPos(UINT uEdge, LPRECT lprc, PAPPBARDATA pabd, BOOL bMove)
{
	int iHeight = 0;
	int iWidth = 0;
	POPTIONS pOpt = GetAppbarData();

    // Fill out the APPBARDATA struct and save the edge we're moving to
    // in the appbar OPTIONS struct.
	pabd->rc = *lprc;
	pabd->uEdge = uEdge;
	pOpt->uSide = uEdge;

	QueryPos(&(pabd->rc));

    // Tell the system we're moving to this new approved position.
	SHAppBarMessage(ABM_SETPOS, pabd);

	if (bMove)
	{
    	// Move the appbar window to the new position
		MoveWindow(m_hWnd, pabd->rc.left, pabd->rc.top, 
			   	   pabd->rc.right - pabd->rc.left,
			   	   pabd->rc.bottom - pabd->rc.top, TRUE);
	}

    // Save the appbar rect.  We use this later when we autohide.  If we're
	// currently hidden, then don't mess with this.
	if (!pOpt->fAutoHide)
    {
		m_rcAppBar = pabd->rc;
    }
}

//
//  PosChanged -- The system has changed our position for some reason.  We need
//			   -- to recalculate the position on the screen we want to occupy
//			   -- by determining how wide or thick we are and the update the
//			   -- screen position.
//              
void CAppBar::PosChanged (PAPPBARDATA pabd)
{
    RECT rc;
    RECT rcWindow;
    int iHeight;
    int iWidth;
	POPTIONS pOpt = GetAppbarData ();

    // Start by getting the size of the screen.
    rc.top = 0;
    rc.left = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);

	// Update the m_rcAppBar so when we slide (if hidden) we slide to the 
	// right place.
	if (pOpt->fAutoHide)
	{
		m_rcAppBar = rc;
		switch (pOpt->uSide)
		{
			case ABE_TOP:
				m_rcAppBar.bottom = m_rcAppBar.top + m_dwHeight;
				break;

		    case ABE_BOTTOM:
		        m_rcAppBar.top = m_rcAppBar.bottom - m_dwHeight;
		        break;

		    case ABE_LEFT:
		        m_rcAppBar.right = m_rcAppBar.left + m_dwWidth;
		        break;

		    case ABE_RIGHT:
		        m_rcAppBar.left = m_rcAppBar.right - m_dwWidth;
		        break;
		}	 		
	}		 

    // Now get the current window rectangle and find the height and width
    GetWindowRect(pabd->hWnd, &rcWindow);
    iHeight = rcWindow.bottom - rcWindow.top;
    iWidth = rcWindow.right - rcWindow.left;

    // Depending on which side we're on, try to preserve the thickness of
    // the window    
    switch (pOpt->uSide) 
    {
	    case ABE_TOP:
	        rc.bottom = rc.top + iHeight;
	        break;

	    case ABE_BOTTOM:
	        rc.top = rc.bottom - iHeight;
	        break;

	    case ABE_LEFT:
	        rc.right = rc.left + iWidth;
	        break;

	    case ABE_RIGHT:
	        rc.left = rc.right - iWidth;
	        break;
    }        

    // Move the appbar.
    QuerySetPos (pOpt->uSide, &rc, pabd, TRUE);
}

void CAppBar::AppBarCallback (UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    APPBARDATA abd;
 	static HWND hwndZOrder = NULL;
	POPTIONS pOpt = GetAppbarData ();
    
    abd.cbSize = sizeof(abd);
    abd.hWnd = m_hWnd;
    
    switch (wParam) 
    {
        // Notifies the appbar that the taskbar's autohide or always-on-top 
        // state has changed.  The appbar can use this to conform to the settings
        // of the system taskbar.
	    case ABN_STATECHANGE:
	        break;

        // Notifies the appbar when a full screen application is opening or 
        // closing.  When a full screen app is opening, the appbar must drop
        // to the bottom of the Z-Order.  When the app is closing, we should 
        // restore our Z-order position.
	    case ABN_FULLSCREENAPP:
	        if (lParam) 
	        {
                // A full screen app is opening.  Move us to the bottom of the 
                // Z-Order.  

				// First get the window that we're underneath so we can correctly
				// restore our position
				hwndZOrder = GetWindow (m_hWnd, GW_HWNDPREV);
				
				// Now move ourselves to the bottom of the Z-Order
	            SetWindowPos(m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, 
	            			 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);            
	        } 
	        else 
	        {
                // The app is closing.  Restore the Z-order			   
                SetWindowPos(m_hWnd, pOpt->fOnTop ? HWND_TOPMOST : hwndZOrder,
	                         0, 0, 0, 0, 
	                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
				
				hwndZOrder = NULL;
	        }
			break;
        
        // Notifies the appbar when an event has occured that may effect the 
        // appbar's size and position.  These events include changes in the 
        // taskbar's size, position, and visiblity as well as adding, removing,
        // or resizing another appbar on the same side of the screen.
    	case ABN_POSCHANGED:
            // Update our position in response to the system change
        	PosChanged (&abd);
        	break;
    }
}

//
//  Register -- Registers the appbar with the system.
//
BOOL CAppBar::Register()
{
	APPBARDATA abd;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	abd.uCallbackMessage = APPBAR_CALLBACK;

	m_bAppRegistered = SHAppBarMessage (ABM_NEW, &abd);

	return m_bAppRegistered;
}

BOOL CAppBar::UnRegister()
{
	APPBARDATA abd;
	
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;

	m_bAppRegistered = !SHAppBarMessage(ABM_REMOVE, &abd);
		
	return !m_bAppRegistered;
}

//
//  SetAutoHide -- Causes the appbar window to either auto hide or stop auto hiding.
//
BOOL CAppBar::SetAutoHide(BOOL bHide)
{
	if (bHide)
    {
		return AutoHide ();
    }
	else
    {
		return NoAutoHide ();
    }
}

//
//  AutoHide -- Does the work of changing the appbar to autohide.  We check
//           -- to see if we can autohide, and if so unregister and tell
//           -- the system we are autohiding.
//
BOOL CAppBar::AutoHide()
{
	HWND hwndAutoHide;
	APPBARDATA abd;
	POPTIONS pOpt = GetAppbarData();
	BOOL bSuccess;	
	RECT rc;
    CString strMsg;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	abd.uEdge = pOpt->uSide;
	
	// First figure out if someone already has this side for 
	// autohiding
	hwndAutoHide = (HWND) SHAppBarMessage(ABM_GETAUTOHIDEBAR, &abd);
	if (hwndAutoHide != NULL)
	{
		return FALSE;
	}

	// We can autohide on this edge.  Set the autohide style.
	abd.lParam = TRUE;			

	bSuccess = (BOOL) SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd);
	if (!bSuccess)
	{
#ifdef LOG
        strMsg.LoadString (IDS_ERROR_AUTOHIDE);
	    gLog.WriteError (strMsg);
#endif
        return FALSE;
	}
	else
	{
		// Since we're allowed to autohide, we need to adjust our screen 
		// rectangle to the autohidden position.  This will allow the system
		// to resize the desktop.
		pOpt->fAutoHide = TRUE;

		m_dwWidth = pOpt->cxWidth;
		m_dwHeight = pOpt->cyHeight;

		rc = m_rcAppBar;
		switch (pOpt->uSide)
		{
			case ABE_TOP:
				rc.bottom = rc.top + 2; 
				break;
			case ABE_BOTTOM:
				rc.top = rc.bottom - 2;
				break;
			case ABE_LEFT:
				rc.right = rc.left + 2;
				break;
			case ABE_RIGHT:
				rc.left = rc.right - 2;
				break;
		}

		QuerySetPos(pOpt->uSide, &rc, &abd, TRUE);
	}

	return TRUE;
}

BOOL CAppBar::NoAutoHide()
{
	HWND hwndAutoHide;
	APPBARDATA abd;
	POPTIONS pOpt = GetAppbarData();
	BOOL fSuccess;	
    CString strMsg;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;
	abd.uEdge = pOpt->uSide;
	
	// First let's check to see if we're the appbar attached to the
	// side of the screen
	abd.uEdge = pOpt->uSide;
	hwndAutoHide = (HWND) SHAppBarMessage(ABM_GETAUTOHIDEBAR, &abd);
	if (hwndAutoHide != m_hWnd)
	{
        strMsg.Format ("%s", STR_ERROR_NOT_HIDDEN);
		TRACE (strMsg);
		return FALSE;
	}

	// We can autohide or stop autohide on this edge.  Set the autohide style.
	abd.lParam = FALSE;			

	fSuccess = (BOOL) SHAppBarMessage(ABM_SETAUTOHIDEBAR, &abd);
	if (!fSuccess)
	{
        strMsg.Format ("%s", STR_ERROR_SET_AUTOHIDE);
		TRACE (strMsg);
        return FALSE;
	}
	else
	{
		// Need to change the appbar to get the screen desktop space
		// back.  Also need to reattach the appbar to that edge of the
		// screen.
    	pOpt->fAutoHide = FALSE;		
    	
		pOpt->cxWidth = m_dwWidth;
		pOpt->cyHeight = m_dwHeight;

        SetSide (pOpt->uSide);	 
	}

	return (TRUE);
}

BOOL CAppBar::SetSide(UINT uSide)
{
	APPBARDATA abd;
	RECT	   rc;
	POPTIONS   pOpt = GetAppbarData();
	BOOL	   fAutoHide = FALSE;

    // Calculate the size of the screen so we can occupy the full width or
    // height of the screen on the edge we request.
	rc.top = 0;
	rc.left = 0;
	rc.right = GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = GetSystemMetrics(SM_CYSCREEN);

    // Fill out the APPBARDATA struct with the basic information
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = m_hWnd;

	// If the appbar is autohidden, turn that off so we can move the bar
	if (pOpt->fAutoHide)
	{
		fAutoHide = pOpt->fAutoHide;

		// Turn off the redrawing of the desktop while we move things around.
		// If you put any breakpoints in this area you will lock up the desktop
		// Since turning off the desktop repaints turns it off for all the apps
		// in the system
		SetWindowRedraw (GetDesktopWindow(), FALSE);
  		SetAutoHide (FALSE);
	}

    // Adjust the rectangle to set our height or width depending on the
    // side we want.
	switch (uSide)
	{
		case ABE_TOP:
			rc.bottom = rc.top + pOpt->cyHeight;
			break;
		case ABE_BOTTOM:
			rc.top = rc.bottom - pOpt->cyHeight;
			break;
		case ABE_LEFT:
			rc.right = rc.left + pOpt->cxWidth;
			break;
		case ABE_RIGHT:
			rc.left = rc.right - pOpt->cxWidth;
			break;
	}

    // Move the appbar to the new screen space.
	QuerySetPos(uSide, &rc, &abd, TRUE);
	
	// If the appbar was hidden, rehide it now
	if (fAutoHide)
	{
		SetAutoHide (TRUE);

		SetWindowRedraw (GetDesktopWindow(), TRUE);
		RedrawWindow (GetDesktopWindow(), NULL, NULL, 
					 RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);			
	}

	return TRUE;
}

void CAppBar::SetAlwaysOnTop(BOOL bOnTop)
{
	POPTIONS pOpt = GetAppbarData();

	// Update the window position to HWND_TOPMOST if we're to be always
	// on top, or HWND_NOTOPMOST if we're not.
	SetWindowPos(m_hWnd, (bOnTop) ? HWND_TOPMOST : HWND_NOTOPMOST,
	             0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	// Store the setting in the appbar OPTIONS struct.
	pOpt->fOnTop = bOnTop;
}

void CAppBar::Hide()
{
	POPTIONS pOpt = GetAppbarData ();
	RECT rc;

	// Don't want to hide if AutoHide not set
	if (!pOpt->fAutoHide)
	{
		return;
	}

	// Calculate a hidden rectangle to use
	rc = m_rcAppBar;
	switch (pOpt->uSide)
	{
		case ABE_TOP:
			rc.bottom = rc.top + 2; 
			break;
		case ABE_BOTTOM:
			rc.top = rc.bottom - 2;
			break;
		case ABE_LEFT:
			rc.right = rc.left + 2;
			break;
		case ABE_RIGHT:
			rc.left = rc.right - 2;
			break;
	}

	pOpt->fHiding = TRUE;	
    CUtility Util;
    Util.SlideWindow (m_hWnd, &rc);
}

void CAppBar::UnHide()
{
	POPTIONS pOpt = GetAppbarData();

    CUtility Util;
    Util.SlideWindow (m_hWnd, &m_rcAppBar);

    pOpt->fHiding = FALSE;

	SetAutoHideTimer ();
}

void CAppBar::SetAutoHideTimer()
{
	POPTIONS pOpt = GetAppbarData();

	if (pOpt->fAutoHide)
    {
		SetTimer (m_hWnd, IDT_AUTOHIDE, 500, NULL);
    }
}

void CAppBar::SetAutoUnhideTimer()
{
	POPTIONS pOpt = GetAppbarData();

	if (pOpt->fAutoHide && pOpt->fHiding)
    {
		SetTimer(m_hWnd, IDT_AUTOUNHIDE, 50, NULL);
    }
}

POPTIONS CAppBar::GetAppbarData()
{
	return m_pOptions;
}

BOOL CAppBar::SetAppbarData (POPTIONS pOptions)
{
    if (!m_pOptions)
    {
        return FALSE;
    }

    m_pOptions->fAutoHide = pOptions->fAutoHide;
    m_pOptions->fOnTop = pOptions->fOnTop;
    m_pOptions->fHiding = pOptions->fHiding;
    m_pOptions->uSide = pOptions->uSide;
    m_pOptions->cxWidth = pOptions->cxWidth;
    m_pOptions->cyHeight = pOptions->cyHeight;
    for (int idx=0; idx<4; idx++)
    {
        m_pOptions->rcEdges[idx] = pOptions->rcEdges[idx];
    }

    return TRUE;
}
