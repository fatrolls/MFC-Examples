// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__7D955F2C_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
#define AFX_MAINFRM_H__7D955F2C_0A9F_11D2_88B8_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// _OX_MDI
// To have this example work as an MDI (Multiple document interface) application
// define _OX_MDI; otherwise, the application works as an SDI application

#define _OX_MDI


#ifdef _OX_MDI
#define CMyFrameWnd CMDIFrameWnd
#else
#define CMyFrameWnd CFrameWnd
#endif

class CMainFrame : public CMyFrameWnd
{
#ifdef _OX_MDI
	DECLARE_DYNAMIC(CMainFrame)
#else
	DECLARE_DYNCREATE(CMainFrame)
#endif
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

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
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowDialog();
	afx_msg void OnShowProppage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7D955F2C_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
