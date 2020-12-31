// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__14C1632C_675D_11D2_A753_525400DAF3CE__INCLUDED_)
#define AFX_MAINFRM_H__14C1632C_675D_11D2_A753_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXBitmapMenuOrganizer.h"
#include "OXCoolToolBar.h"
#include "OXMenuBar.h"
#include "OX3DTabView.h"


class CMainFrame : public COXMenuBarFrame<CMainFrameWindow,CDockBar>
{
	DECLARE_DYNCREATE(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	DWORD m_dwOffsetExt;
	DWORD m_dwOffsetInt;
	DWORD m_dwStyle;
	BOOL m_bOpenCustomizeDlg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	COXCoolToolBar    m_wndToolBar;

	// to show bitmaps in menu
	// just to make the framework look pretty
	COXBitmapMenuOrganizer Organizer;

#ifndef _MDI_INTERFACE
	COX3DTabViewContainer m_TabViewContainer;
	CImageList m_ilContainer;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewShowCustomizeDlg();
	afx_msg void OnUpdateViewShowCustomizeDlg(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__14C1632C_675D_11D2_A753_525400DAF3CE__INCLUDED_)
