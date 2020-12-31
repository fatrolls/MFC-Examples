/*******************************************************************************
File:        SysTrayIcon.h

Description: This file contains the module for creating and manipulating 
			 a system tray icon	 
             
Created: Dec 5, 2002
Author:  Prateek Kaul
e-mail:  kaulpr@yahoo.com

Compiler with version number : Visual C++ 6.0/7.0 (.NET)
********************************************************************************/

#ifndef SYSTRAYICON_H
#define SYSTRAYICON_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxwin.h>
#include <afxtempl.h>
#include <shellapi.h>

class CSysTrayIcon;

#define WM_SYSTRAYMSG  (WM_USER + 1)

#define NIIF_NONE       0x00000000
#define NIIF_INFO       0x00000001
#define NIIF_WARNING    0x00000002
#define NIIF_ERROR      0x00000003
#define NIIF_USER       0x00000004
#define NIIF_ICON_MASK  0x0000000F
#define NIIF_NOSOUND    0x00000010

#define NIM_ADD         0x00000000
#define NIM_MODIFY      0x00000001
#define NIM_DELETE      0x00000002
#define NIM_SETFOCUS    0x00000003
#define NIM_SETVERSION  0x00000004
#define NOTIFYICON_VERSION 3
#define NIF_MESSAGE     0x00000001
#define NIF_ICON        0x00000002
#define NIF_TIP         0x00000004
#define NIF_STATE       0x00000008
#define NIF_INFO        0x00000010
#define NIF_GUID        0x00000020

#define NIS_HIDDEN              0x00000001
#define NIS_SHAREDICON          0x00000002

// says this is the source of a shared icon


struct _MYNOTIFYICONDATAA : public _NOTIFYICONDATAA
{
	CHAR   szTip[128];
	DWORD dwState;
	DWORD dwStateMask;
	CHAR   szInfo[256];
	union {
		UINT  uTimeout;
		UINT  uVersion;
	} DUMMYUNIONNAME;
	CHAR   szInfoTitle[64];
	DWORD dwInfoFlags;
	GUID guidItem;
};

typedef  _MYNOTIFYICONDATAA MYNOTIFYICONDATAA;
typedef  _MYNOTIFYICONDATAA (*PMYNOTIFYICONDATAA);

typedef MYNOTIFYICONDATAA MYNOTIFYICONDATA;
typedef PMYNOTIFYICONDATAA PMYNOTIFYICONDATA;

/*---------------------------------------------------------------------------
 class CSysTrayIconWnd

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : Helper invisbile window to route messages to the CSysTrayIcon class

 Revisions :none.
----------------------------------------------------------------------------*/

class CSysTrayWnd : public CWnd  
{
    DECLARE_MESSAGE_MAP()
public:
	CSysTrayWnd();
	virtual ~CSysTrayWnd();
	
	BOOL CreateWnd(
	         CSysTrayIcon* pstiSysTrayIcon,
	         LPCTSTR lpszClassName,
             LPCTSTR lpszWindowName,
             DWORD dwStyle,
             int x,
             int y,
             int nWidth,
             int nHeight,
             HWND hWndParent,
             HMENU nIDorHMenu,
             LPVOID lpParam = NULL 
         );

protected:
    afx_msg LRESULT OnSysTrayMsg(WPARAM wParam, LPARAM lParam);
    CSysTrayIcon* m_pstiSysTrayIcon;
    CPoint GetMouseScreenPt(void);
};


/*---------------------------------------------------------------------------
 class CSysTrayIcon

 Created: Dec 5, 2002
 Author:  Prateek Kaul
 e-mail:  kaulpr@yahoo.com

 Abstract : For creating and manipluating a Sys tray icon

 Revisions :none.
----------------------------------------------------------------------------*/

typedef CTypedPtrList<CPtrList, NOTIFYICONDATA*> NOTIFYICONDATAList;

class CSysTrayIcon
{
    friend class CSysTrayWnd; // The CSysTrayWnd is a friend so that it call call the protected mouse
                              // overridable methods for message routing

public:
    BOOL CreateIcon(HICON hIcon, UINT nIconID, PCSTR szTip);
    BOOL ShowIcon(UINT nIconID); // Show an icon i     
    BOOL HideIcon(UINT nIconID);
	BOOL DeleteIcon(UINT nIconID); // Remove an icon from the Sys tray
	BOOL ChangeIconTip(UINT nIconID, CString strTip);

	BOOL ShowBalloon(
	         UINT  nIconID,        // nIconID
             PTSTR szBalloonTitle, // Balloon title
             PTSTR szBalloonMsg,   // Balloon message
             DWORD dwIcon = NIIF_NONE, // Type of icon in the message ICON_ERROR, ICON_INFO,ICON_WARNING
             UINT nTimeOut = 10        // Time(secs)for the balloon to be shown, shoudn't be less than 10 sec.
         );

            
protected:
    CSysTrayIcon();   
    virtual ~CSysTrayIcon();

    // Deals with the context menu
    BOOL OnContextMenu(CMenu* pContextMenu, CPoint ptMouse, CWnd* pWndMessageHandler);
    virtual void OnLButtonDown(UINT nIconID, CPoint ptMouse);
    virtual void OnRButtonDown(UINT nIconID, CPoint ptMouse);
    virtual void OnMButtonDown(UINT nIconID, CPoint ptMouse);
    virtual void OnLButtonUp(UINT nIconID, CPoint ptMouse);
    virtual void OnRButtonUp(UINT nIconID, CPoint ptMouse);
    virtual void OnMButtonUp(UINT nIconID, CPoint ptMouse);
    virtual void OnLButtonDblClk(UINT nIconID, CPoint ptMouse);
    virtual void OnRButtonDblClk(UINT nIconID, CPoint ptMouse);
    virtual void OnMButtonDblClk(UINT nIconID, CPoint ptMouse);
    virtual void OnMouseMove(UINT nIconID, CPoint ptMouse);
                                                 
private:
	BOOL CreateTheSysTrayMsgReceiverWnd();
    CSysTrayWnd m_wndTrayMsgReceiver;     // Helper invisible window, that will receive
                                          // the tray icon messages
    NOTIFYICONDATAList m_NotifyIconDataList;  // List of NOTIFIYICONDATA structs
    BOOL CheckIfIconIDExists(UINT nIconID);
    BOOL DeleteNotifyIconDataFromList(NOTIFYICONDATA* pnidIconInfoToBeDeleted);
    NOTIFYICONDATA* GetNotifyIconDataFromID(int nIconID);
};


#endif // SYSTRAYICON_H