#if !defined(AFX_ADDREPEATERSDLG_H__1C6A7DD1_EC32_11D0_9AA6_000000000000__INCLUDED_)
#define AFX_ADDREPEATERSDLG_H__1C6A7DD1_EC32_11D0_9AA6_000000000000__INCLUDED_

#include "CompleteSet.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddRepeatersDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddRepeatersDlg dialog

class CAddRepeatersDlg : public CDialog
{
// Construction
public:
	CAddRepeatersDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddRepeatersDlg)
	enum { IDD = IDD_ADDREPEATERS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddRepeatersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddRepeatersDlg)
	afx_msg void OnAdd();
	afx_msg void OnReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeCallsign();
	afx_msg void OnChangeCity();
	afx_msg void OnChangeFrequency();
	afx_msg void OnSelchangeInput();
	afx_msg void OnSelchangeState();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL RecordsWereAdded () { return m_bRecordsWereAdded; }
protected:
private:
	BOOL m_bRecordsWereAdded;
	CCompleteSet m_setComplete;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDREPEATERSDLG_H__1C6A7DD1_EC32_11D0_9AA6_000000000000__INCLUDED_)
