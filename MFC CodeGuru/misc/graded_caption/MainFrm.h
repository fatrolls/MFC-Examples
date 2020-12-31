// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "PaintCap.h"
#include "CoolMenu.h"
#include "ToolBarEx.h"

#if !defined(AFX_MAINFRM_H__A5362398_6034_11D1_B4DF_006097608B1F__INCLUDED_)
#define AFX_MAINFRM_H__A5362398_6034_11D1_B4DF_006097608B1F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
  void RedrawCaption(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
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
	CToolBarEx    m_wndToolBar;
  CCaptionPainter m_capp;
	CCoolMenuManager m_menuManager;
  virtual void OnUpdateFrameTitle(BOOL bAddToTitle);
  LRESULT OnPaintMyCaption(WPARAM wp,LPARAM lp);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A5362398_6034_11D1_B4DF_006097608B1F__INCLUDED_)
