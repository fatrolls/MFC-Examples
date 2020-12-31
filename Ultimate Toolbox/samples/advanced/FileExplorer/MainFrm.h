// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__10814F8D_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_)
#define AFX_MAINFRM_H__10814F8D_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "OXCoolToolBar.h"
#include "OXMenuBar.h"

class CFileExplorerView;
class CLeftView;

class CMainFrame : public COXMenuBarFrame<CFrameWnd,CDockBar>
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	CFileExplorerView* GetRightPane();
	CLeftView* GetLeftPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	COXCoolToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	afx_msg void OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnViewType();
	afx_msg void OnViewUp();
	afx_msg void OnViewBackward();
	afx_msg void OnViewForward();
	afx_msg void OnUpdateViewUp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewBackward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewForward(CCmdUI* pCmdUI);
	afx_msg void OnBackwardItem(UINT nCommandID);
	afx_msg void OnForwardItem(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__10814F8D_EC24_11D2_A7FB_525400DAF3CE__INCLUDED_)
