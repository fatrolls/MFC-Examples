// RequestLog.h : header file
//

#ifndef REQUESTLOG_H
#define REQUESTLOG_H

#define COL_DEVICE		0	// column index for device name
#define COL_FUNC		1	// for function name
#define COL_SECTOR		2	// for starting sector
#define COL_NBYTES		3	// for # bytes
#define COL_STATUS		4	// for resulting status code

/////////////////////////////////////////////////////////////////////////////
// CRequestLog dialog

class CRequestLog : public CDialog
{
// Construction
public:
	CRequestLog(HANDLE reqmon); // used as a modeless dialog

// Dialog Data
	//{{AFX_DATA(CRequestLog)
	enum { IDD = REQLOG };
	CListCtrl	m_ctlList;
	CButton		m_ctlPause;
	CButton		m_ctlResume;
	//}}AFX_DATA

	CArray<PIOSDCB, PIOSDCB> m_devlist;	// devices to monitor
	
	HANDLE				m_thread;	// handle of monitor thread
	HANDLE				m_reqmon;	// reqmon.vxd device handle
	BOOL				m_paused;	// true if monitoring is currently paused
	CRITICAL_SECTION	m_cs;		// gate on access to m_devlist
	HANDLE				m_evkill;	// event used to kill monitor thread
	int					m_nlog;		// maximum number to record
	BOOL				m_all;		// true if monitoring all devices

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRequestLog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRequestLog)
	afx_msg void OnClose();
	afx_msg void OnPause();
	afx_msg void OnResume();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnRequest(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

#endif
