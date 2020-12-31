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

#include "OXCaptionPainter.h"

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

// special structure to define CaptionPainter properties
// used in Customize CaptionPainter dialog
struct CustomizeCaption
{
	LOGFONT		m_lf;
	COLORREF	m_clrBackground;
	COLORREF	m_clrText;
	BOOL		m_bGradient;
	int			m_nGradientAlgorithm;
	int			m_nGradientAlignment;
	int			m_nEllipsis;
	int			m_nHorizontalAlignment;
	int			m_nVerticalAlignment;
	int			m_nNumberShade;
};

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
protected:
	// caption painter
	COXCaptionPainter m_Caption;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CMainFrame : public CMDIFrameWnd
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

	// get properties of CaptionPainter to use in Customize CaptionPainter dialog
	CustomizeCaption GetCaptionProperties(BOOL bActive);
	// apply changed properties to CaptionPainter
	void SetCaptionProperties(BOOL bActive, CustomizeCaption ct);

protected:
	// caption painter
	COXCaptionPainter m_Caption;

	CStatusBar  m_wndStatusBar;

	// to show bitmaps in menu
	// just to make the framework look pretty
	COXBitmapMenuOrganizer Organizer;

	// three CoolToolBars
	COXCoolToolBar m_wndToolBarFile;
	COXCoolToolBar m_wndToolBarEdit;
	COXCoolToolBar m_wndToolBarWindow;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnViewCustomize();
	afx_msg void OnViewCustomizeCaption();
	//}}AFX_MSG
	afx_msg void OnUpdateViewToolbars(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbars(UINT nID);
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
