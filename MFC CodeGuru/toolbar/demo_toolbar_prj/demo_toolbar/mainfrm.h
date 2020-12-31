// MainFrm.h : interface of the CMainFrame class
//
// 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND, and the user
// holds the author blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__6F831B29_0710_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_MAINFRM_H__6F831B29_0710_11D2_AB9F_441100C10000__INCLUDED_

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

	// Note: to use any of these methods from another
	// class cast m_pMainWnd to a CMainFrame pointer, then
	// call the method ie: ((CMainFrame*)m_pMainWnd)->GetEditControl()...

	// return a reference to the edit control
	CEdit& GetEditControl() {
		return *m_edit;
	}

	// return a reference to the combo control
	CComboBox& GetComboControl() {
		return *m_combo;
	}

	// get the currently selected combo index
	int GetComboIndex() {
		return m_cbIndex;
	}

	// set the combo index
	void SetComboIndex( int nIndex ) {
		m_cbIndex = nIndex;
	}

	void DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf );

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
	CToolBar    m_winToolBar;
	CToolBar    m_hotToolBar;
	CImageList  m_pImageColor;
	CImageList  m_pImageNoColor;
	CEdit*		m_edit;
	CComboBox*  m_combo;
	int         m_cbIndex;
	CMenuMgr	m_menuManager;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBack();
	afx_msg void OnForward();
	afx_msg void OnStop();
	afx_msg void OnRefresh();
	afx_msg void OnHome();
	afx_msg void OnSelEndOk();
	afx_msg void OnToolbarDropDown(NMTOOLBAR* pnmh, LRESULT* plRes);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6F831B29_0710_11D2_AB9F_441100C10000__INCLUDED_)
