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
#include "OXTabClientWnd.h"
#include "OXMenuBar.h"
#include "oxskins.h"

#define _MDI_INTERFACE

#ifdef _MDI_INTERFACE
#define CMainFrameWindow CMDIFrameWnd
#else
#define CMainFrameWindow CFrameWnd
#endif

class CMultiPadApp : public COXSkinnedApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// load workspace on enter or not
	BOOL m_bLoadWSOnEnter;
	// save workspace on exit or not
	BOOL m_bSaveWSOnExit;

protected:
	void IniAppVars();
	void SaveAppVars();

public:
	//{{AFX_MSG(CMultiPadApp)
	afx_msg void OnAppAbout();
	afx_msg void OnViewWorkspace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// special structure to define CoolToolBar properties
// used in Customize Toolbars dialog
struct CustomizeToolbar
{
	BOOL	bCustomizable;
	BOOL	bFlat;
	BOOL	bGripper;
	BOOL	bList;
	BOOL	bSeparator;
	BOOL	bText;
	int		nTextType;
	UINT	nRows;
	UINT	nWidth;
	UINT	nIndent;
};

// Derive you mainframe window from COXMenuBarFrame template class
// and specify parent frame window and dock bar
class CMainFrame : public COXMenuBarFrame<CMainFrameWindow,CDockBar>
{
	DECLARE_DYNCREATE(CMainFrame)

public:
	//load and save bars placement in Framework and state of all CoolToolBars
	void LoadWorkspace();
	void SaveWorkspace();

	// get properties of CoolToolBar to use in Customize Toolbars dialog
	CustomizeToolbar GetToolbarProperties(COXCoolToolBar* pBar);
	// apply changed properties to CoolToolBar
	void SetToolbarProperties(COXCoolToolBar* pBar, CustomizeToolbar ct);

protected:
	CStatusBar  m_wndStatusBar;

	// to show bitmaps in menu
	// just to make the framework look pretty
	COXBitmapMenuOrganizer Organizer;

	// three CoolToolBars
	COXCoolToolBar m_wndToolBarFile;
	COXCoolToolBar m_wndToolBarEdit;
	COXCoolToolBar m_wndToolBarWindow;

	// MTI client window
	COXTabClientWnd m_MTIClientWnd;
	DWORD m_dwStyle;
	DWORD m_dwOffset;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnViewCustomize();
	afx_msg void OnViewMTI();
	afx_msg void OnUpdateViewMTI(CCmdUI* pCmdUI);
	afx_msg void OnViewMticustomize();
	afx_msg void OnUpdateViewMticustomize(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnUpdateViewToolbars(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbars(UINT nID);
	afx_msg void OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult);
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
