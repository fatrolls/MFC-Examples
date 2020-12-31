// DIBManager.h : main header file for the DIBMANAGER application
//

#if !defined(AFX_DIBMANAGER_H__D2552D0E_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_DIBMANAGER_H__D2552D0E_7143_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXWinApp.h"
#include "OXSplashWnd.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerApp:
// See DIBManager.cpp for the implementation of this class
//

class CScaleRollupDlg;

class CDIBManagerApp : public COXWinApp
{
protected:
	// defines roll-up ZoomLevel Dialog
	CScaleRollupDlg* m_pScaleRollupDlg;

	void IniAppVars();
	void SaveAppVars();

public:
	CDIBManagerApp();

	CScaleRollupDlg* &GetScaleRollupDlg() { return m_pScaleRollupDlg; }

	virtual CFileDialog* NewFileDialog(BOOL bOpenFileDialog, DWORD lFlags);

	// load workspace on enter or not
	BOOL m_bLoadWSOnEnter;
	// save workspace on exit or not
	BOOL m_bSaveWSOnExit;
	// the number of bits in current system palette
	UINT m_nColors;
	// splash window that we use while loading
	COXSplashWnd* m_pSplash;

	void ShowSplashWindow(UINT nBitmapID, UINT nTime); 
	void HideSplashWindow(BOOL bRedrawMainFrame=FALSE);
	void ErrorNotify(UINT nMsgID);
	void ErrorNotify(CString sMsg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBManagerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDIBManagerApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnViewWorkspace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBMANAGER_H__D2552D0E_7143_11D1_A3D5_0080C83F712F__INCLUDED_)
