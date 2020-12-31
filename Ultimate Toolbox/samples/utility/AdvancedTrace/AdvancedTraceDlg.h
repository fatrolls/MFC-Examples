// AdvancedTraceDlg.h : header file
//

#if !defined(AFX_ADVANCEDTRACEDLG_H__3454410C_BC3C_11D2_A7BD_525400DAF3CE__INCLUDED_)
#define AFX_ADVANCEDTRACEDLG_H__3454410C_BC3C_11D2_A7BD_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "OXSeparator.h"
#include "OXStaticHyperLink.h"
#include "OXTrace.h"

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTraceDlg dialog

class CAdvancedTraceDlg : public CDialog
{
// Construction
public:
	CAdvancedTraceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAdvancedTraceDlg)
	enum { IDD = IDD_ADVANCEDTRACE_DIALOG };
	CListCtrl	m_listCtrl;
	CListBox	m_listBox;
	COXStaticHyperLink	m_linkOutputFile;
	COXStatic	m_staticOutputFile;
	COXSeparator	m_separator2;
	COXSeparator	m_separator1;
	BOOL	m_bChecked;
	int		m_nComboItem;
	CString	m_sListBoxItem;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedTraceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	COXTrace* pTrace;

	// Generated message map functions
	//{{AFX_MSG(CAdvancedTraceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton();
	afx_msg void OnCheck();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnChangeEdit();
	afx_msg void OnSelchangeListbox();
	afx_msg void OnItemchangedListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVANCEDTRACEDLG_H__3454410C_BC3C_11D2_A7BD_525400DAF3CE__INCLUDED_)
