// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__8FFAB4A6_B3F1_4893_A121_28D57BFA5B3F__INCLUDED_)
#define AFX_MAINFRM_H__8FFAB4A6_B3F1_4893_A121_28D57BFA5B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PPTooltip.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
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
	CToolBar m_wndToolBar;
	CToolBar m_wndToolBar2;
	CPPToolTip m_tooltip;

	BOOL m_bBalloonTooltip;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDemoDialog();
	afx_msg void OnUpdateDemoDialog(CCmdUI* pCmdUI);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSubMenu);
    afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditPaste();
	afx_msg void OnLeftMenutip();
	afx_msg void OnUpdateLeftMenutip(CCmdUI* pCmdUI);
	afx_msg void OnCenterMenutip();
	afx_msg void OnUpdateCenterMenutip(CCmdUI* pCmdUI);
	afx_msg void OnBottomMenutip();
	afx_msg void OnUpdateBottomMenutip(CCmdUI* pCmdUI);
	afx_msg void OnRightMenutip();
	afx_msg void OnUpdateRightMenutip(CCmdUI* pCmdUI);
	afx_msg void OnTopMenutip();
	afx_msg void OnUpdateTopMenutip(CCmdUI* pCmdUI);
	afx_msg void OnVcenterMenutip();
	afx_msg void OnUpdateVcenterMenutip(CCmdUI* pCmdUI);
	afx_msg void OnAnchorLeft();
	afx_msg void OnUpdateAnchorLeft(CCmdUI* pCmdUI);
	afx_msg void OnAnchorRight();
	afx_msg void OnUpdateAnchorRight(CCmdUI* pCmdUI);
	afx_msg void OnAnchorBottom();
	afx_msg void OnUpdateAnchorBottom(CCmdUI* pCmdUI);
	afx_msg void OnAnchorCenter();
	afx_msg void OnUpdateAnchorCenter(CCmdUI* pCmdUI);
	afx_msg void OnAnchorTop();
	afx_msg void OnUpdateAnchorTop(CCmdUI* pCmdUI);
	afx_msg void OnAnchorVcenter();
	afx_msg void OnUpdateAnchorVcenter(CCmdUI* pCmdUI);
	afx_msg void OnAnchorBottomedgeCenter();
	afx_msg void OnUpdateAnchorBottomedgeCenter(CCmdUI* pCmdUI);
	afx_msg void OnAnchorBottomedgeLeft();
	afx_msg void OnUpdateAnchorBottomedgeLeft(CCmdUI* pCmdUI);
	afx_msg void OnAnchorBottomedgeRight();
	afx_msg void OnUpdateAnchorBottomedgeRight(CCmdUI* pCmdUI);
	afx_msg void OnAnchorLeftedgeBottom();
	afx_msg void OnUpdateAnchorLeftedgeBottom(CCmdUI* pCmdUI);
	afx_msg void OnAnchorLeftedgeTop();
	afx_msg void OnUpdateAnchorLeftedgeTop(CCmdUI* pCmdUI);
	afx_msg void OnAnchorLeftedgeVcenter();
	afx_msg void OnUpdateAnchorLeftedgeVcenter(CCmdUI* pCmdUI);
	afx_msg void OnAnchorRightedgeBottom();
	afx_msg void OnUpdateAnchorRightedgeBottom(CCmdUI* pCmdUI);
	afx_msg void OnAnchorRightedgeTop();
	afx_msg void OnUpdateAnchorRightedgeTop(CCmdUI* pCmdUI);
	afx_msg void OnAnchorRightedgeVcenter();
	afx_msg void OnUpdateAnchorRightedgeVcenter(CCmdUI* pCmdUI);
	afx_msg void OnAnchorTopedgeCenter();
	afx_msg void OnUpdateAnchorTopedgeCenter(CCmdUI* pCmdUI);
	afx_msg void OnAnchorTopedgeLeft();
	afx_msg void OnUpdateAnchorTopedgeLeft(CCmdUI* pCmdUI);
	afx_msg void OnAnchorTopedgeRight();
	afx_msg void OnUpdateAnchorTopedgeRight(CCmdUI* pCmdUI);
	afx_msg void OnTooltipBalloon();
	afx_msg void OnUpdateTooltipBalloon(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8FFAB4A6_B3F1_4893_A121_28D57BFA5B3F__INCLUDED_)
