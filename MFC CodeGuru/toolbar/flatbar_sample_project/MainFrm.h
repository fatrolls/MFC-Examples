// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1E0F37E7_4020_11D1_9FB1_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__1E0F37E7_4020_11D1_9FB1_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ToolBarEx.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
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
	CToolBarEx  m_wndToolBar;
	CToolBarEx	m_wndTextBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateViewFlatbar(CCmdUI* pCmdUI);
	afx_msg void OnViewFlatbar();
	afx_msg void OnUpdateToggleCase(CCmdUI* pCmdUI);
	afx_msg void OnToggleCase();
	//}}AFX_MSG

#if _MFC_VER >= 0x0420
		afx_msg void	OnCustomToolbarDraw( NMHDR *, LRESULT * );
#endif
		afx_msg void	OnQueryDelete( NMHDR *, LRESULT * );
		afx_msg void	OnQueryInsert( NMHDR *, LRESULT * );

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bCaseCheck;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1E0F37E7_4020_11D1_9FB1_444553540000__INCLUDED_)
