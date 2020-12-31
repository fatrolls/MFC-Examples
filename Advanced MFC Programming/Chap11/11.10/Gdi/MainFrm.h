#if !defined(AFX_MAINFRM_H__1010F3A8_28F5_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__1010F3A8_28F5_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "ColorBar.h"

class CMainFrame : public CFrameWnd
{
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	void UpdateColorBar(){m_wndColorBar.UpdateAllButtons();}
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
	CStatusBar m_wndStatusBar;
	CToolBar m_wndToolBar;
	CToolBar m_wndDrawToolBar;
	CColorBar m_wndColorBar;

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__1010F3A8_28F5_11D1_9C9A_444553540000__INCLUDED_)
