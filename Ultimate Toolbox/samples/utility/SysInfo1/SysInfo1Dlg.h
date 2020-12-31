// SysInfo1Dlg.h : header file
//

#if !defined(AFX_SYSINFO1DLG_H__1CD38C29_81E5_11D1_A4E0_0020359647BF__INCLUDED_)
#define AFX_SYSINFO1DLG_H__1CD38C29_81E5_11D1_A4E0_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXSysInfo.h"
// we will use this value to distinguish a folder from a resource item in the tree view
#define TVI_DATA_FOLDER	0xFFFFFFFF

/////////////////////////////////////////////////////////////////////////////
// CSysInfo1Dlg dialog

class CSysInfo1Dlg : public CDialog
{
// Construction
public:
	CSysInfo1Dlg(CWnd* pParent = NULL);	// standard constructor
	CImageList m_ilFolder;
	HTREEITEM  m_hRootItem;

// Dialog Data
	//{{AFX_DATA(CSysInfo1Dlg)
	enum { IDD = IDD_SYSINFO1_DIALOG };
	CTreeCtrl	m_InfoTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysInfo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	public:
	COXSysInfo	m_oxSysInfo ;
	void		GetSystemInformation() ;

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSysInfo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSINFO1DLG_H__1CD38C29_81E5_11D1_A4E0_0020359647BF__INCLUDED_)
