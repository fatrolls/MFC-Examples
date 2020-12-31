#if !defined(AFX_MAINFRM_H__D649DA97_3EFC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__D649DA97_3EFC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CMainFrame : public CFrameWnd
{
protected:
	BOOL m_bEnableMenu;
	BOOL m_bPlayAvailable;
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnHideGo();
	afx_msg void OnMacroPalyback();
	afx_msg void OnMacroRecord();
	afx_msg void OnUpdateMacroPalyback(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMacroRecord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHideGo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LONG OnFinishJournal(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__D649DA97_3EFC_11D1_9C9A_444553540000__INCLUDED_)
