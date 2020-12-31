#if !defined(AFX_MAINFRM_H__C0A99CF5_ED67_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__C0A99CF5_ED67_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "MDlgBar.h"

class CMainFrame : public CFrameWnd
{
protected:
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
	CToolBar	m_wndColorButton;
	CDialogBar	m_wndDialogBar;	
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewColorBar();
	afx_msg void OnViewDialogBar();
	afx_msg void OnUpdateViewColorBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDialogBar(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__C0A99CF5_ED67_11D0_9C9A_444553540000__INCLUDED_)
