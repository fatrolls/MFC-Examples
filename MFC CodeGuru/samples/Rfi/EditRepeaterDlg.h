#if !defined(AFX_EDITREPEATERDLG_H__1808F5C2_ECDD_11D0_9AAA_000000000000__INCLUDED_)
#define AFX_EDITREPEATERDLG_H__1808F5C2_ECDD_11D0_9AAA_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditRepeaterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditRepeaterDlg dialog

class CEditRepeaterDlg : public CDialog
{
// Construction
public:
	CEditRepeaterDlg(CString&, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
private:
	//{{AFX_DATA(CEditRepeaterDlg)
	enum { IDD = IDD_EDITREPEATER };
	CComboBox	m_cbState;
	CComboBox	m_cbInput;
	CString	m_strCallsign;
	CString	m_strCity;
	CString	m_strFrequency;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditRepeaterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditRepeaterDlg)
	afx_msg void OnReset();
	afx_msg void OnChangeEditCallsign();
	afx_msg void OnChangeEditCity();
	afx_msg void OnChangeEditFrequency();
	afx_msg void OnSelchangeEditInput();
	afx_msg void OnSelchangeEditState();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString& GetCallsign () { return m_strCallsign; }
	CString& GetCity () { return m_strCity; }
	CString& GetFrequency () { return m_strFrequency; }
	CString& GetState () { return m_strState; }
	CString& GetInput () { return m_strInput; }
	void SetCallsign ( CString& str ) { m_strCallsign = str; }
	void SetCity ( CString& str ) { m_strCity = str; }
	void SetFrequency ( CString& str ) { m_strFrequency = str; }
	void SetState ( CString& str ) { m_strState = str; }
	void SetInput ( CString& str ) { m_strInput = str; }
protected:
private:
	CString m_strSavedInput;
	CString m_strSavedState;
	CString m_strRecordId;
	CString m_strState;
	CString m_strInput;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITREPEATERDLG_H__1808F5C2_ECDD_11D0_9AAA_000000000000__INCLUDED_)
