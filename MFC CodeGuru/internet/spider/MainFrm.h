// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__26AC1028_E049_11D1_8F58_B6D09489096E__INCLUDED_)
#define AFX_MAINFRM_H__26AC1028_E049_11D1_8F58_B6D09489096E__INCLUDED_

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
	CTypedPtrList<CObList,CSpiderThread*>     m_threadList;  
    long           m_lMaxThreads;
	long           m_lCurThreads;
    
// Operations
public:
	BOOL GetURL(LPCTSTR lpString,HWND lphwndNotifyView = NULL,
		int lptype= 0, BOOL lpRoot = FALSE);
	void GetConnected();
	BOOL RobotCheck(LPCTSTR pszURL);

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
	afx_msg void OnWindowsCloseall();
	afx_msg void OnClose();
	afx_msg void OnToolsGetURL();
	afx_msg void OnToolsKillthread();
	afx_msg void OnDestroy();
	afx_msg void OnToolCheckURLs();
	afx_msg void OnToolsGetServerHeader();
	afx_msg void OnToolsViewURLList();
	afx_msg void OnToolsURLsNotFound();
	afx_msg void OnToolsThreadsStop();
	afx_msg void OnUpdateToolsKillthread(CCmdUI* pCmdUI);
	afx_msg void OnUpdateToolsThreadsStop(CCmdUI* pCmdUI);
	//}}AFX_MSG
	LRESULT OnDocNew(WPARAM wParam,LPARAM lParam);
	LRESULT OnDocUpdate(WPARAM wParam,LPARAM lParam);
	LRESULT OnThreadDone(WPARAM wParam,LPARAM lParam);
	LRESULT OnThreadStatus(WPARAM wParam,LPARAM lParam);
	LRESULT OnNewThread(WPARAM wParam,LPARAM lParam);
	LRESULT OnGetNewFiles(WPARAM wParam,LPARAM lParam);
	LRESULT OnServerStatus(WPARAM wParam,LPARAM lParam);
	LRESULT OnURLStatus(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	CRITICAL_SECTION m_CritSect; 


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__26AC1028_E049_11D1_8F58_B6D09489096E__INCLUDED_)
