// NewControlDlg.h : header file
//

#if !defined(AFX_NEWCONTROLDLG_H__50484475_B6C3_4AA9_AF9F_9F5E1097B5F0__INCLUDED_)
#define AFX_NEWCONTROLDLG_H__50484475_B6C3_4AA9_AF9F_9F5E1097B5F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HTMLListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CNewControlDlg dialog

class CNewControlDlg : public CDialog
{
// Construction
public:
	void OnOK();
	CNewControlDlg(CWnd* pParent = NULL);	// standard constructor

	CImageList m_ImageList;
// Dialog Data
	//{{AFX_DATA(CNewControlDlg)
	enum { IDD = IDD_NEWCONTROL_DIALOG };
	BOOL	m_bCheckBoxes;
	BOOL	m_bGridLines;
	BOOL	m_bShowImages;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewControlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	CHTMLListCtrl m_list;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNewControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnCheckCheckboxes();
	afx_msg void OnCheckGridlines();
	afx_msg void OnCheckImages();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg void OnHTMLList_SelectionChanged(NMHDR* pNMHDR, LRESULT*);
	afx_msg void OnHTMLList_LButtonDown(NMHDR* pNMHDR, LRESULT*);
	afx_msg void OnHTMLList_LButtonDBLClick(NMHDR* pNMHDR, LRESULT*);
	afx_msg void OnHTMLList_RButtonDown(NMHDR* pNMHDR, LRESULT*);
	afx_msg void OnHTMLList_CheckStateChanged(NMHDR* pNMHDR, LRESULT*);
	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCONTROLDLG_H__50484475_B6C3_4AA9_AF9F_9F5E1097B5F0__INCLUDED_)
