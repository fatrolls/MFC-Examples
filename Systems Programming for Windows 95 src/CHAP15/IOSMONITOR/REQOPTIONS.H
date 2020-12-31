// ReqOptions.h : header file
//

#ifndef REQOPTIONS_H
#define REQOPTIONS_H

/////////////////////////////////////////////////////////////////////////////
// CReqOptions dialog

class CRequestLog;

class CReqOptions : public CDialog
{
// Construction
public:
	CReqOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReqOptions)
	enum { IDD = REQOPTIONS };
	CListBox	m_ctlList;
	CButton	m_ctlNone;
	CButton	m_ctlAll;
	int		m_numlog;
	//}}AFX_DATA

	CArray<PIOSDCB, PIOSDCB> m_devlist;
	CRequestLog* m_log;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReqOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReqOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnAll();
	afx_msg void OnNone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
