// CommunicatorView.h : interface of the CCommunicatorView class
//

/////////////////////////////////////////////////////////////////////////////

class CCommunicatorView : public CFormView
{
protected: // create from serialization only
	CCommunicatorView();
	DECLARE_DYNCREATE(CCommunicatorView)

public:
	//{{AFX_DATA(CCommunicatorView)
	enum { IDD = IDD_COMMUNICATOR_FORM };
	CButton	m_wndCancel;
	CStatic	m_wndLocalPortLabel;
	CButton	m_wndServerGroup;
	CStatic	m_wndRemoteAddressLabel;
	CStatic	m_wndRemotePortLabel;
	CStatic	m_wndLocalAddressLabel;
	CButton	m_wndClientGroup;
	CStatic	m_wndClientAddressLabel;
	CButton	m_wndSendServer;
	CButton	m_wndDisconnectServer;
	CButton	m_wndConnectServer;
	CEdit	m_wndRemotePort;
	CEdit	m_wndRemoteAddress;
	CButton	m_wndDisconnectClient;
	CButton	m_wndSendClient;
	CButton	m_wndShutdown;
	CButton	m_wndListen;
	CEdit	m_wndLocalPort;
	CEdit	m_wndLocalAddress;
	CListBox	m_wndClientAddresses;
	CEdit	m_wndReceivedData;
	CString	m_sLocalAddress;
	int		m_nLocalPort;
	CString	m_sRemoteAddress;
	int		m_nRemotePort;
	//}}AFX_DATA

// Attributes
public:
	CCommunicatorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommunicatorView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCommunicatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void ShowData(CCommunicatorDoc::CHintData* pHintData);
	void AddText(LPCTSTR pszText);

// Generated message map functions
protected:
	//{{AFX_MSG(CCommunicatorView)
	afx_msg void OnConnectServer();
	afx_msg void OnDisconnectClient();
	afx_msg void OnDisconnectServer();
	afx_msg void OnListen();
	afx_msg void OnSendClient();
	afx_msg void OnSendServer();
	afx_msg void OnShutdown();
	afx_msg void OnIdleUpdateCmdUI();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CommunicatorView.cpp
inline CCommunicatorDoc* CCommunicatorView::GetDocument()
   { return (CCommunicatorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
