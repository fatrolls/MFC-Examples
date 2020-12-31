// TimeClockDlg.h : header file
//

class CPrintPropertiesDlg;

/////////////////////////////////////////////////////////////////////////////
// CTimeClockDlg dialog

class CTimeClockDlg : public CDialog
{
// Construction
public:
	CTimeClockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
private:

	//{{AFX_DATA(CTimeClockDlg)
	enum { IDD = IDD_TIMECLOCK_DIALOG };
	CListCtrl	m_listctlTimeCard;
	CString	m_strHours;
	CString	m_strMinutes;
	CString	m_strSeconds;
	CString	m_strDate;
	CString	m_strTimeCardFilename;
	CString	m_strName;
	CString	m_strWeek;
	CString	m_strVacation;
	CString	m_strSick;
	CString	m_strOther;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeClockDlg)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Interface
public:
	void SetCmdLine ( LPCSTR );

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeClockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPunchinout();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLoadtimecard();
	afx_msg void OnPrintreport();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDblclkTimecard(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static const UINT nAboutBoxCommandId;
	static const UINT nUpdateClockEvent;
	static const DWORD m_dwDocID;
	HICON m_hIcon;
	LPCSTR m_lpcstrCmdLine;
	DWORD m_dwNumTimeCardEntries;
	BOOL m_bHaveValidFile;
	BOOL m_bHaveTimer;
	time_t m_time_tLast;
	time_t m_time_tTotal;
	CImageList m_ilSmallImages;
	CImageList m_ilLargeImages;
	CList < time_t, time_t& > m_listTimes;
	void DoTimeListEntries ();
	int ItoD ( double );
	BOOL DoOutputToDC ( CDC&, CPrintPropertiesDlg& );
	BOOL LoadCard ( CString& );
	CString& GetTotalTimeFor ( CString& );
	void GetEndTimes ( time_t, CString&, CString& );
	void Reset ();
	void UpdateClock ();
};
