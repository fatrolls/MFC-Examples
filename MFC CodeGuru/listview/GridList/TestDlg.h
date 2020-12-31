#if !defined(AFX_TESTDLG_H__92CA5997_9434_11D1_88D5_444553540000__INCLUDED_)
#define AFX_TESTDLG_H__92CA5997_9434_11D1_88D5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestDlg.h : header file
//
#include "GridListCtrl.h"
#include "InPlaceEdit.h"

/////////////////////////////////////////////////////////////////////////////
// TestDlg dialog

class TestDlg : public CDialog
{
// Construction
public:
	TestDlg(CWnd* pParent = NULL);   // standard constructor
	~TestDlg();

// Dialog Data
	//{{AFX_DATA(TestDlg)
	enum { IDD = IDD_DIALOG1 };
	CGridListCtrl	m_GridListCtrl;
	//}}AFX_DATA
	CImageList *m_pImageList;
	CInPlaceEdit *m_pListEdit;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBeginlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__92CA5997_9434_11D1_88D5_444553540000__INCLUDED_)
