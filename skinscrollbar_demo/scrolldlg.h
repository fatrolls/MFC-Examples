// scrollDlg.h : header file
//

#if !defined(AFX_SCROLLDLG_H__EA4ACC0E_4EC1_4873_A756_A83BC3250F0D__INCLUDED_)
#define AFX_SCROLLDLG_H__EA4ACC0E_4EC1_4873_A756_A83BC3250F0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScrollDlg dialog
#include "SkinScrollWnd.h"
#include "SkinScrollBar.h"
#include "SkinComboBox.h"
#include "listctrlex.h"
class CScrollDlg : public CDialog
{
// Construction
public:
	CScrollDlg(CWnd* pParent = NULL);	// standard constructor
	HBITMAP	m_hBmpScrollBar	;
// Dialog Data
	//{{AFX_DATA(CScrollDlg)
	enum { IDD = IDD_SCROLL_DIALOG };
	CSkinComboBox	m_cbxTest2;
	CListCtrlEx	m_ctrlLC;
	CSkinComboBox	m_cbxTest;
	CScrollBar	m_ctrlScroll1;
	CSkinScrollBar	m_ctrlScroll;
	CRichEditCtrl	m_ctrlRichEdit;
	CEdit	m_ctrlEdit;
	CTreeCtrl	m_ctrlTree;
	CListBox	m_ctrlList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScrollDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	afx_msg void OnAbout();
	afx_msg void OnButton3();
	afx_msg void OnLcMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLDLG_H__EA4ACC0E_4EC1_4873_A756_A83BC3250F0D__INCLUDED_)
