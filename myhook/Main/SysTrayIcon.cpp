/*******************************************************************************
File:        SysTrayIcon.cpp

Description: This file contains the module for creating and manipulating 
			 a Sys tray icon	 
             
Created: Dec 5, 2002
Author:  Prateek Kaul
e-mail:  kaulpr@yahoo.com

Compiler with version number : Visual C++ 6.0/7.0 (.NET)
********************************************************************************/

#include "StdAfx.h"

#include "SysTrayIcon.h"



//------------------------------------------------------------------------------
// Message map for CSysTrayWnd
//------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CSysTrayWnd, CWnd)
    ON_MESSAGE(WM_SYSTRAYMSG, OnSysTrayMsg)
END_MESSAGE_MAP()


/*-----------------------------------------------------------------------------
 Function : CSysTrayWnd::CSysTrayWnd()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Default constructor

 Parameters : none

 Return Value : none
----------------------------------------------------------------------------*/

CSysTrayWnd::CSysTrayWnd()
{
    m_pstiSysTrayIcon = NULL;
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayWnd::CSysTrayWnd()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Default destructor

 Parameters : none

 Return Value : none
----------------------------------------------------------------------------*/

CSysTrayWnd::~CSysTrayWnd()
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayWnd::OnSysTrayMsg()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : The icon in the system sends the WM_SYSTRAYMSG to this window.
            WM_SYSTRAYMSG is mapped to this function via the message map.
            
 Parameters : System calls and sends the wParam and lParam to this function
              1. wParam -> Icon ID
              2. lParam -> The message sent to the icon

 Return Value : LRESULT
----------------------------------------------------------------------------*/

LRESULT CSysTrayWnd::OnSysTrayMsg(WPARAM wParam, LPARAM lParam)
{
    // wParam gives the ICON ID on which the mouse had made some movement.
    // lParam is the mouse message
    
    CPoint ptMouse = GetMouseScreenPt();
            
    switch (lParam)
    {
        case WM_RBUTTONDOWN:
            m_pstiSysTrayIcon->OnRButtonDown(wParam, ptMouse);
        break;
        
        case WM_LBUTTONDOWN:
            m_pstiSysTrayIcon->OnLButtonDown(wParam, ptMouse);
        break;
        
        case WM_MBUTTONDOWN:
            m_pstiSysTrayIcon->OnMButtonDown(wParam, ptMouse);
        break;
        
        case WM_RBUTTONDBLCLK:
            m_pstiSysTrayIcon->OnRButtonDblClk(wParam, ptMouse);
        break;
        
        case WM_LBUTTONDBLCLK:
            m_pstiSysTrayIcon->OnLButtonDblClk(wParam, ptMouse);
        break;
        
        case WM_MBUTTONDBLCLK:
            m_pstiSysTrayIcon->OnMButtonDblClk(wParam, ptMouse);
        break;
        
        case WM_MBUTTONUP:
            m_pstiSysTrayIcon->OnMButtonUp(wParam, ptMouse);
        break;
        
        case WM_RBUTTONUP:
            m_pstiSysTrayIcon->OnRButtonUp(wParam, ptMouse);
        break;
            
        case WM_LBUTTONUP:
            m_pstiSysTrayIcon->OnLButtonUp(wParam, ptMouse);
        break;
            
        case WM_MOUSEMOVE:
            m_pstiSysTrayIcon->OnMouseMove(wParam, ptMouse);
        break;
        
        default:
        break;
    }
  
    return 0;
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayWnd::CreateWnd()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Creates the hidden helper window, which will receive messages for
            the tray icon
            
 Parameters : 

 Return Value : BOOL (TRUE, if the helper window is created, else FALSE)
----------------------------------------------------------------------------*/

BOOL CSysTrayWnd::CreateWnd(CSysTrayIcon* pstiSysTrayIcon,  LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
{
    ASSERT(pstiSysTrayIcon != NULL);
    BOOL bWndCreated = FALSE;
    
    if (pstiSysTrayIcon == NULL)
    {
        return bWndCreated;
    }
    
    PCSTR pstrOwnerClass = ::AfxRegisterWndClass(0);
    
    bWndCreated = CWnd::CreateEx(
                      0,
                      pstrOwnerClass, 
                      _T(""), 
                      WS_POPUP,
		              CW_USEDEFAULT,
                      CW_USEDEFAULT,
                      CW_USEDEFAULT, 
                      CW_USEDEFAULT,
		              NULL,
                      0
                  );
                  
    m_pstiSysTrayIcon = pstiSysTrayIcon;                       
    return bWndCreated;
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayWnd::GetMouseScreenPt()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Gets the screen co-ordinates where the mouse is on the icon.
            
 Parameters : void

 Return Value : CPoint -> Point where the mouse is on the icon
----------------------------------------------------------------------------*/

CPoint CSysTrayWnd::GetMouseScreenPt()
{
    CPoint ptMouse(0, 0);
    
    ::GetCursorPos(&ptMouse);
	
    return ptMouse;
}


/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::CSysTrayIcon()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Default constructor

 Parameters : none

 Return Value : none
----------------------------------------------------------------------------*/

CSysTrayIcon::CSysTrayIcon()
{
    CreateTheSysTrayMsgReceiverWnd();
}


/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::~CSysTrayIcon()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Destructor

 Parameters : none

 Return Value : none
----------------------------------------------------------------------------*/

CSysTrayIcon::~CSysTrayIcon(void)
{
    POSITION pos = m_NotifyIconDataList.GetHeadPosition();
    NOTIFYICONDATA* pnifInconInfo = NULL;
    
    while (m_NotifyIconDataList.IsEmpty() == FALSE)
    {
        pnifInconInfo = m_NotifyIconDataList.GetNext(pos);
        
        DeleteIcon(pnifInconInfo->uID);
    }
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::Create()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Same functionality as 2nd constructor, if you wish to construct blank
            object and intialize it later

 Parameters : 
	1. hIcon -> Handle to an icon

	2. nIconID -> An unique ID for the tray icon if you intend to use
	              more than one tray icon
	              
	3. szTip -> The tool tip that will be shown when mouse is over the icon
	            with the ID nIconID

 Return Value : BOOL (TRUE, if the icon could be created, else FALSE)
----------------------------------------------------------------------------*/

BOOL CSysTrayIcon::CreateIcon(HICON hIcon, UINT nIconID, PCSTR szTip)
{
    BOOL bIconCreated = FALSE;
    
    bIconCreated = CheckIfIconIDExists(nIconID);
    
    // Icon should not be created as an icon with this ID already exists!!
    ASSERT(bIconCreated == FALSE);
    
    if (bIconCreated == FALSE)
    {
        NOTIFYICONDATA* pnidIconInfo = new NOTIFYICONDATA;
        
        if (pnidIconInfo != NULL)
        {
            ::memset(pnidIconInfo, 0, sizeof(NOTIFYICONDATA));
            
            ASSERT(hIcon != NULL);
            ASSERT(::strcmp(szTip, _T("")) != 0); // Sure that icon tip == "" ??
            
            if (hIcon != NULL)
            {
                pnidIconInfo->hIcon            = hIcon;
                pnidIconInfo->hWnd             = m_wndTrayMsgReceiver.GetSafeHwnd();
                pnidIconInfo->uCallbackMessage = WM_SYSTRAYMSG;
                pnidIconInfo->uID              = nIconID;
                pnidIconInfo->cbSize           = sizeof(NOTIFYICONDATA);
     	        pnidIconInfo->uFlags           = 0;
                ::strcpy(pnidIconInfo->szTip, szTip); // Copy the string
                 
                // Add the icon information to the list
                m_NotifyIconDataList.AddTail(pnidIconInfo); 
                
                bIconCreated = TRUE;
                
                return bIconCreated;
            }
        }
    }
    else
    {
        return FALSE;
    }
	return TRUE;
}
    


/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::ShowBalloon()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Shows a ballon tip over the tray icon

 Parameters : 
	1. szBallonTitle -> Message title
    2. szBalloonMsg -> Balloon message
	3. nTimeOut -> Time to show the balloon, min 10 secs.
	4. dwIcon -> ICON_WARNING or ICON_ERROR or ICON_INFO
	
 Return Value : BOOL
----------------------------------------------------------------------------*/

BOOL CSysTrayIcon::ShowBalloon(UINT  nIconID, PTSTR szBalloonTitle, PTSTR szBalloonMsg, DWORD dwIcon, UINT nTimeOut)
{

    // First check if Icon exits
    ASSERT(szBalloonTitle != NULL); // Are you sure ballon message title == NULL??
    ASSERT(szBalloonMsg != NULL);   // Are you sure ballon message == NULL??

    VERIFY((nTimeOut *= 1000) >= 10000); // in Windows 2000 nTimeout is 10 seconds,
                                         // If even set less no point, so a check 
                                         // just in case.

    ASSERT(::strcmp(szBalloonTitle, _T("")) != 0); // Sure that balloon title == "" ??
    ASSERT(::strcmp(szBalloonMsg, _T("")) != 0); // Sure that balloon message == "" ?

    ASSERT (dwIcon == NIIF_WARNING || dwIcon == NIIF_ERROR || dwIcon == NIIF_INFO || dwIcon == NIIF_NONE);
    
    BOOL bBalloonShown = FALSE;
    MYNOTIFYICONDATA* pnidIconInfo = (MYNOTIFYICONDATA*)GetNotifyIconDataFromID(nIconID);
    
    if (pnidIconInfo != NULL)
    {
        pnidIconInfo->dwInfoFlags = dwIcon;
    }
    else
    {
        return bBalloonShown; // We could not get the NOTIFYICONDATA
    }
    
    // Set the flags for showing balloon, espcially NIF_INFO
	pnidIconInfo->uFlags |= NIF_INFO;
	
	// Set the time out for the balloon
	pnidIconInfo->uTimeout = nTimeOut;

	// Set the balloon title
	::strcpy(pnidIconInfo->szInfoTitle, szBalloonTitle);

	// Set balloon message
	::strcpy(pnidIconInfo->szInfo, szBalloonMsg);

    // Show balloon....
    bBalloonShown = ::Shell_NotifyIcon(NIM_MODIFY, pnidIconInfo);
		
	return bBalloonShown;  
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::ShowIcon()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Shows a tray icon

 Parameters : 
	1. hIcon -> Handle of icon
    2. szTip -> Tool tip of tray icon
	
 Return Value : BOOL
----------------------------------------------------------------------------*/

BOOL CSysTrayIcon::ShowIcon(UINT nIconID)
{
    BOOL bIconShown = FALSE;
    
	NOTIFYICONDATA* pnidIconInfo = GetNotifyIconDataFromID(nIconID);
	
	if (pnidIconInfo != NULL)
	{
	    // Use NIM_ADD if the icon has never been shown, else use the flag NIM_MODIFY   
	    // The NOTIFYICONDATA.uFlags signifies that the icon in the system tray is
	    // not visible.     
	    if (pnidIconInfo->uFlags == 0)
        {
	        pnidIconInfo->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		    bIconShown = ::Shell_NotifyIcon(NIM_ADD, pnidIconInfo);
	    }
	    else
	    {
	        pnidIconInfo->uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		    bIconShown = ::Shell_NotifyIcon(NIM_MODIFY, pnidIconInfo);
	    }
	}
	
    return bIconShown;
}

BOOL CSysTrayIcon::CreateTheSysTrayMsgReceiverWnd()
{
    PCSTR pstrOwnerClass = ::AfxRegisterWndClass(0);

    BOOL bHelperWndCreated = FALSE;
    
    bHelperWndCreated = m_wndTrayMsgReceiver.CreateWnd(
                            this,
                            pstrOwnerClass, 
                            _T(""), 
                            WS_POPUP,
		                    CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT, 
                            CW_USEDEFAULT,
		                    NULL,
                            0
                            );

    return bHelperWndCreated;
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::HideIcon()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Hides an icon from the system tray. Does not delete it from 
            memory

 Parameters : The icon ID
	
 Return Value : BOOL (TRUE if the icon is hidden, else FALSE)
----------------------------------------------------------------------------*/

BOOL CSysTrayIcon::HideIcon(UINT nIconID)
{
    BOOL bIconHidden = FALSE;
    
    NOTIFYICONDATA* pnidIconInfo = GetNotifyIconDataFromID(nIconID);
    
    if (pnidIconInfo != NULL)
    {
        // The NOTIFYICONDATA.uFlags signifies that the icon in the system tray is
	    // not visible.     
	    pnidIconInfo->uFlags = 0;
	    
	    bIconHidden = ::Shell_NotifyIcon(NIM_DELETE, pnidIconInfo);
    }
    	
	return bIconHidden;
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::DeleteIcon()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Hides an icon from the system tray. Also deletes it from 
            memory

 Parameters : The icon ID
	
 Return Value : BOOL (TRUE if the icon is hidden & deleted , else FALSE)
----------------------------------------------------------------------------*/

BOOL CSysTrayIcon::DeleteIcon(UINT nIconID)
{
    BOOL bIconHidden = FALSE;
    
    NOTIFYICONDATA* pnidIconInfo = GetNotifyIconDataFromID(nIconID);
    
    if (pnidIconInfo != NULL)
    {
        // The NOTIFYICONDATA.uFlags signifies that the icon in the system tray is
	    // not visible.     
	    pnidIconInfo->uFlags = 0;
	    
	    bIconHidden = ::Shell_NotifyIcon(NIM_DELETE, pnidIconInfo);
	    
	    DeleteNotifyIconDataFromList(pnidIconInfo);
    }
    	
	return bIconHidden;
}




/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::GetNotifyIconDataFromID()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Gets the associated NOTIFYICONDATA struct from the icon ID

 Parameters : The icon ID
	
 Return Value : NOTIFYICONDATA* (NOTIFYICONDATA pointer, if available, 
                else NULL)
----------------------------------------------------------------------------*/

NOTIFYICONDATA* CSysTrayIcon::GetNotifyIconDataFromID(int nIconID)
{
    POSITION pos = m_NotifyIconDataList.GetHeadPosition();
    NOTIFYICONDATA* pnidIconInfo = NULL;                
    
    while (pos != NULL)
    {
        pnidIconInfo = m_NotifyIconDataList.GetNext(pos);
        
        if (pnidIconInfo->uID == nIconID)
        {
            return pnidIconInfo; // We found the rqeuired NOTIFYICONDATA
        }
    }
    
    return NULL;
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::DeleteNotifyIconDataFromList()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Deletes the icon and it's NOTIFYICONDATA struct from linked list
            m_NotifyIconDataList

 Parameters : The icon ID
	
 Return Value : BOOL (TRUE if possible to delete the icon with the struct
                passed as the parameter, else FALSE)
----------------------------------------------------------------------------*/

BOOL CSysTrayIcon::DeleteNotifyIconDataFromList(NOTIFYICONDATA* pnidIconInfoToBeDeleted)
{
    BOOL bIconInfoDeleted = FALSE;
    
    POSITION pos = m_NotifyIconDataList.GetHeadPosition();
    NOTIFYICONDATA* pnidIconInfo = NULL;
        
    while (pos != NULL)
    {   
        // We did not use m_NotifyIconDataList.GetNext() because, in the case
        // we enter the 'if' case below, the RemoveAt() will point to the next 
        // element rather than the element we want to delete.
        pnidIconInfo = m_NotifyIconDataList.GetAt(pos);
        
        if (pnidIconInfo == pnidIconInfoToBeDeleted)
        {
            m_NotifyIconDataList.RemoveAt(pos);
            delete pnidIconInfo;
            
            bIconInfoDeleted = TRUE;
            
            break; // We found the NOTIFYICONDATA to be deleted
        }
        
        // Move to the next element
        m_NotifyIconDataList.GetNext(pos);
    }
    
    return bIconInfoDeleted; 
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::CheckIfIconIDExists()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Checks if an icon with the requested ID exists

 Parameters : The icon ID
	
 Return Value : BOOL (TRUE if icon with this ID exists in the linked list
                m_NotifyIconDataList, else FALSE)
----------------------------------------------------------------------------*/

BOOL CSysTrayIcon::CheckIfIconIDExists(UINT nIconID)
{   
    BOOL bIconIDExists = FALSE;
    
    POSITION pos = m_NotifyIconDataList.GetHeadPosition();
    
    while (pos != NULL)
    {
        NOTIFYICONDATA* pnidIconInfo = m_NotifyIconDataList.GetNext(pos);
        
        if (pnidIconInfo->uID == nIconID)
        {
            bIconIDExists = TRUE;
            
            break;
        }
    } 
    return bIconIDExists;
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnLButtonDown()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user clicks
            and icon with the left mouse button

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnLButtonDown(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnRButtonDown()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user clicks
            and icon with the right mouse button

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnRButtonDown(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnMButtonDown()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user clicks
            and icon with the right mouse button

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnMButtonDown(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnLButtonUp()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user releases
            the left mouse button over the icon

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnLButtonUp(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnRButtonUp()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user releases
            the right mouse button over the icon

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnRButtonUp(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnMButtonUp()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user releases
            the middle mouse button over the icon

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnMButtonUp(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnLButtonDblClk()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user double
            clicks the left mouse button over the icon

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnLButtonDblClk(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnRButtonDblClk()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user double
            clicks the right mouse button over the icon

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnRButtonDblClk(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnMButtonDblClk()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user double
            clicks the middle mouse button over the icon

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnMButtonDblClk(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnLButtonDblClk()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called by the window m_wndTrayMsgReceiver when the user moves the
            mouse over the icon.

 Parameters : 1. nIconID -> The icon ID
              2. ptMouse -> screen co-ordinates of the mouse
	
 Return Value : void
----------------------------------------------------------------------------*/

void CSysTrayIcon::OnMouseMove(UINT nIconID, CPoint ptMouse)
{
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::OnContextMenu()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Called to initialize a menu over the icon, and set the foreground
            window for proper message routing.

 Parameters : 1. CMenu* -> Pointer to the menu
              2. ptMouse -> screen co-ordinates of the mouse
              3. pWndMessageHandler -> Window that will handle the message
	
 Return Value : void
----------------------------------------------------------------------------*/

BOOL CSysTrayIcon::OnContextMenu(CMenu* pContextMenu, CPoint ptMouse, CWnd* pWndMessageHandler)
{
    // The window is brought forward, so that it starts 
    // receving messages, rather than currently active window.
    // If we don't do this the messages of the context menu will
    // go to the currently active window.
    pWndMessageHandler->SetForegroundWindow();
	
    BOOL bResult = pContextMenu->TrackPopupMenu(
                       TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
                       ptMouse.x, 
                       ptMouse.y, 
                       pWndMessageHandler
                   );
    
    return bResult;
}



/*-----------------------------------------------------------------------------
 Function : CSysTrayIcon::ChangeIconTip()

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Changes the tool tip of the icon

 Parameters : 1. nIconID -> ID of the icon whose tool tip to be changed
              2. strTip -> New tip of the icon
              	
 Return Value : void
----------------------------------------------------------------------------*/
BOOL CSysTrayIcon::ChangeIconTip(UINT nIconID, CString strTip)
{
    BOOL bIconTipChanged = FALSE;
    TCHAR* szTip = strTip.GetBuffer(0);
    
    ASSERT(::strcmp(szTip, _T("")) != 0); // Sure that icon tip == "" ??
    
    NOTIFYICONDATA* pnidIconInfo = GetNotifyIconDataFromID(nIconID);
    
    if (pnidIconInfo != NULL)
    {
        ::strcpy(pnidIconInfo->szTip, szTip); // Copy the new string containing the tip
    
        pnidIconInfo->cbSize  = sizeof(NOTIFYICONDATA);
        pnidIconInfo->uFlags |= NIF_TIP;

	    bIconTipChanged = ::Shell_NotifyIcon(NIM_MODIFY, pnidIconInfo);
    }
    	    
    return bIconTipChanged;
}
