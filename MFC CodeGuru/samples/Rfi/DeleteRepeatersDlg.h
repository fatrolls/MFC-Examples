#if !defined(AFX_DELETEREPEATERSDLG_H__1808F5C1_ECDD_11D0_9AAA_000000000000__INCLUDED_)
#define AFX_DELETEREPEATERSDLG_H__1808F5C1_ECDD_11D0_9AAA_000000000000__INCLUDED_

#include "CompleteSet.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DeleteRepeatersDlg.h : header file
//

#ifndef _LBCTRL_H
#include "lbctrl.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteRepeatersDlg dialog

class CDeleteRepeatersDlg : public CDialog
{
// Construction
public:
	CDeleteRepeatersDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
private:
	//{{AFX_DATA(CDeleteRepeatersDlg)
	enum { IDD = IDD_DELETEREPEATERS };
	CListBoxCtrl	m_lcRepeaterList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteRepeatersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeleteRepeatersDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnColumnclickRepeaterList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnClickRepeaterList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL RecordsWereDeleted () { return m_bRecordsWereDeleted; }
protected:
private:
	void LoadSortList ( CString& );
	void LoadList ();
	BOOL m_bRecordsWereDeleted;
	CCompleteSet m_setComplete;
	CImageList m_smImageList;
	CImageList m_lgImageList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEREPEATERSDLG_H__1808F5C1_ECDD_11D0_9AAA_000000000000__INCLUDED_)
