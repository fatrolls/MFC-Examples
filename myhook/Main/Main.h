// Main.h : main header file for the MAIN application
//

#if !defined(AFX_MAIN_H__09ABD1EA_7346_45E5_943B_52D76081FD85__INCLUDED_)
#define AFX_MAIN_H__09ABD1EA_7346_45E5_943B_52D76081FD85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SysTrayIcon.h"

/////////////////////////////////////////////////////////////////////////////
// CMainApp:
// See Main.cpp for the implementation of this class
//
class CAppSysIcon;
class CMainApp : public CWinApp , public CBCGPWorkspace
{
	friend class CRemoteControlDlg;
public:
	CMainApp();
    BOOL ShowBalloonMsgInTray(CString strTitle, CString strMsgTxt);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMainApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CAppSysIcon* m_pTrayIcon;

	bool CreateAndShowTrayIcon();
};


/////////////////////////////////////////////////////////////////////////////
class CAppSysIcon : public CSysTrayIcon  
{
public:
	CAppSysIcon();
	virtual ~CAppSysIcon();

	virtual void OnRButtonDown(UINT nIconID, CPoint ptMouse);
    virtual void OnLButtonDblClk(UINT nIconID, CPoint ptMouse);
	bool m_bExitMenu;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAIN_H__09ABD1EA_7346_45E5_943B_52D76081FD85__INCLUDED_)
