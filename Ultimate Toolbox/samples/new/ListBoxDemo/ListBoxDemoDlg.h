// ListBoxDemoDlg.h : header file
//

#if !defined(AFX_LISTBOXDEMODLG_H__827DCE60_D0A0_42E2_8CE3_C119889FCE03__INCLUDED_)
#define AFX_LISTBOXDEMODLG_H__827DCE60_D0A0_42E2_8CE3_C119889FCE03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListBoxDemoDlg dialog

class CListBoxDemoDlg : public CDialog
{
// Construction
public:
	CListBoxDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListBoxDemoDlg)
	enum { IDD = IDD_LISTBOXDEMO_DIALOG };
	COXListBoxEx	m_ListBox;
	CEdit	m_TextToAdd;
	CButton	m_chkSort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListBoxDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChksort();
	afx_msg void OnBtnadd();
	afx_msg void OnBtnremove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXDEMODLG_H__827DCE60_D0A0_42E2_8CE3_C119889FCE03__INCLUDED_)
