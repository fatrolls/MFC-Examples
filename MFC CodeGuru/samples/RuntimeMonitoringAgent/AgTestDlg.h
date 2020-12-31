// AgTestDlg.h : header file
//

//////////////////////////////////////////////////////////////////////////////
// Test thread
//

class TTestThread : public CObject {
  private:
    // Thread management
    HANDLE EKillThread;
    HANDLE EThreadIsDead;
  private:
    CWinThread *Thread;
  public:
    static UINT __cdecl ThreadFunc(LPVOID);
  public:
    TTestThread(void);
    virtual ~TTestThread();
    virtual void Create(void);
    virtual void Destroy(void);
    virtual void Execute(void);
  #ifdef _DEBUG
	  virtual void AssertValid() const;
	  virtual void Dump(CDumpContext& dc) const;
  #endif
};

/////////////////////////////////////////////////////////////////////////////
// CAgTestDlg dialog

class CAgTestDlg : public CDialog
{
private:
  TTestThread Thread;
// Construction
public:
	CAgTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAgTestDlg)
	enum { IDD = IDD_AGTEST_DIALOG };
	CButton	StopT;
	CButton	StartT;
	CEdit	Edit;
	CButton	Check2;
	CButton	Check1;
  CButton Radio1;
  CButton Radio2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAgTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnKillFocusEdit1();
	afx_msg void OnSetFocusEdit1();
	afx_msg void OnStartThread();
	afx_msg void OnStopThread();
	afx_msg void OnThreadAction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

