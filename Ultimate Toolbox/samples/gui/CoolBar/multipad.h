// multipad.h : main header file for the Multipad application
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#include "resource.h"
#include "OXBitmapMenuOrganizer.h"
#include "OXCoolToolBar.h"
#include "OXCoolBar.h"

#define _MDI_INTERFACE

#ifdef _MDI_INTERFACE
#define CMainFrameWindow CMDIFrameWnd
#else
#define CMainFrameWindow CFrameWnd
#endif

class CMultiPadApp : public CWinApp
{
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedAssertApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMultiPadApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// special structure to define CoolToolBar and CoolBar band properties
// used in Customize Toolbars dialog
struct CustomizeBand
{
	BOOL	bCustomizable;
	BOOL	bFlat;
	BOOL	bList;
	BOOL	bSeparator;
	BOOL	bText;
	int		nTextType;
	UINT	nRows;
	UINT	nWidth;
	CString	sBandText;
	int		nImage;
};

class CMainFrame : public CMainFrameWindow
{
	DECLARE_DYNCREATE(CMainFrame)

public:
	//load and save bars placement in Framework and state of CoolBar and
	//all CoolToolBars within it
	void LoadWorkspace();
	void SaveWorkspace();

	// get properties of CoolBar's band to use in Customize Toolbars dialog
	CustomizeBand GetToolbarProperties(COXCoolToolBar* pBar);
	// apply changed properties to CoolToolBar
	void SetToolbarProperties(COXCoolToolBar* pBar, CustomizeBand ct);

protected:
	CStatusBar  m_wndStatusBar;
	CFont m_CoolbarFont;

	// to show bitmaps in menu
	// just to make the framework look pretty
	COXBitmapMenuOrganizer Organizer;

	//CoolBar - container for toolbars
	COXCoolBar m_wndCoolBar;

	// three CoolToolBars
	COXCoolToolBar m_wndToolBarFile;
	COXCoolToolBar m_wndToolBarEdit;
	COXCoolToolBar m_wndToolBarWindow;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnViewCustomize();
	afx_msg void OnCoolbar();
	afx_msg void OnUpdateCoolbar(CCmdUI* pCmdUI);
	//}}AFX_MSG
#if _MFC_VER>=0x0420
	afx_msg void OnCustomDraw(NMHDR* pNotifyStruct, LRESULT* result);
#endif
	DECLARE_MESSAGE_MAP()
};

class CPadDoc : public CDocument
{
	DECLARE_DYNCREATE(CPadDoc)
	void Serialize(CArchive& ar);
	//{{AFX_MSG(CPadDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
