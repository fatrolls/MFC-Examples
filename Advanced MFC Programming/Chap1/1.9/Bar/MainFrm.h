#if !defined(AFX_MAINFRM_H__BCBCDFC8_F3B1_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__BCBCDFC8_F3B1_11D0_9C9A_444553540000__INCLUDED_

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
	void GetClientRect(LPRECT);
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
	MCDialogBar m_wndDialogBar;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__BCBCDFC8_F3B1_11D0_9C9A_444553540000__INCLUDED_)
