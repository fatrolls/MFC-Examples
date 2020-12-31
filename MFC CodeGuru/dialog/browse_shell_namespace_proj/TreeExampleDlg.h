// TreeExampleDlg.h : header file
//

#if !defined(AFX_TREEEXAMPLEDLG_H__F0B620A7_9D4F_11D1_B10E_B8F603C10000__INCLUDED_)
#define AFX_TREEEXAMPLEDLG_H__F0B620A7_9D4F_11D1_B10E_B8F603C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "ShellTree.h"

/////////////////////////////////////////////////////////////////////////////
// CTreeExampleDlg dialog
//
// This source is part of CShellTree - Selom Ofori
// 
// Version: 1.02 (any previously unversioned copies are older/inferior
//
// This code is free for all to use. Mutatilate it as much as you want
// See MFCENUM sample from microsoft

class CTreeExampleDlg : public CDialog
{
// Construction
public:
	CTreeExampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTreeExampleDlg)
	enum { IDD = IDD_TREEEXAMPLE_DIALOG };
	CComboBox	m_FileListCtl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeExampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CShellTree* m_TreeCtl;
	// Generated message map functions
	//{{AFX_MSG(CTreeExampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnItemexpandingBrowseTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickBrowseTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemBrowseTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSynchFolders();
	afx_msg void OnSelchangedBrowseTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEEXAMPLEDLG_H__F0B620A7_9D4F_11D1_B10E_B8F603C10000__INCLUDED_)
