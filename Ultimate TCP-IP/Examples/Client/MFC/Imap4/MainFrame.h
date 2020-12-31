// MainFrame.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRAME_H__1FE0A7D8_27E9_11D3_B75D_00203596449E__INCLUDED_)
#define AFX_MAINFRAME_H__1FE0A7D8_27E9_11D3_B75D_00203596449E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IDN_UPDATE_MESSAGE_LIST 1

class CMessageFolderView;
class CMessageListView;

#pragma warning ( disable : 4511 4512 )


class CMyIMAP4Class : public CUT_IMAP4Client
{
public:
    CMyIMAP4Class() : m_ptrListView(NULL) {}

    CMessageListView    *m_ptrListView;


protected:
	virtual	void OnAlertMessage(LPCSTR lpszAlertMsg);
	virtual	void OnExpunge(long nMsgNumber);
	virtual	BOOL OnFetch(CUT_MsgData &data);
	virtual	void OnExists(long nMsgNumber);
	virtual	void OnRecent(long nMsgNumber);
};

class CMainFrame : public CFrameWnd
{
	friend class CMessageFolderView;
	friend class CMessageListView;

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	inline CMessageFolderView* GetMessageFolderView() const
		{ return (CMessageFolderView*)(m_wndSplitter.GetPane(0, 0)); }
	inline CMessageListView* GetMessageListView() const
		{ return (CMessageListView*)(m_wndSplitter.GetPane(0, 1)); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	CSplitterWnd m_wndSplitter;

	BOOL m_bConnected;
	CMyIMAP4Class m_imapClient;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileConnect();
	afx_msg void OnUpdateFileConnect(CCmdUI* pCmdUI);
	afx_msg void OnFileDisconnect();
	afx_msg void OnUpdateFileDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 )

inline CMainFrame* GetAppFrameWnd() 
{
	return static_cast<CMainFrame*>(AfxGetMainWnd());
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__1FE0A7D8_27E9_11D3_B75D_00203596449E__INCLUDED_)
