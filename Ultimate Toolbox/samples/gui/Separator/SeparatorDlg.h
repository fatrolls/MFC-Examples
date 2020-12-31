// SeparatorDlg.h : header file
//

#if !defined(AFX_SEPARATORDLG_H__354BA847_6F3F_11D2_A75E_525400DAF3CE__INCLUDED_)
#define AFX_SEPARATORDLG_H__354BA847_6F3F_11D2_A75E_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXSeparator.h"

/////////////////////////////////////////////////////////////////////////////
// CSeparatorDlg dialog

class CSeparatorDlg : public CDialog
{
// Construction
public:
	CSeparatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSeparatorDlg)
	enum { IDD = IDD_SEPARATOR_DIALOG };
	COXSeparator	m_ctlSepVertRight;
	COXSeparator	m_ctlSepVertPlain;
	COXSeparator	m_ctlSepVertLeft;
	COXSeparator	m_ctlSepVertCenter;
	COXSeparator	m_ctlSepHorzRight;
	COXSeparator	m_ctlSepHorzPlain;
	COXSeparator	m_ctlSepHorzLeft;
	COXSeparator	m_ctlSepHorzCenter;
	COXSeparator	m_ctlSepCustomText;
	COXSeparator	m_ctlSepCusomLine;
	COXSeparator	m_ctlSeparatorHeader;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeparatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSeparatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEPARATORDLG_H__354BA847_6F3F_11D2_A75E_525400DAF3CE__INCLUDED_)
