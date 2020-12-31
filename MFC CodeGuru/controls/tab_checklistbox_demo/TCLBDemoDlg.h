// TCLBDemoDlg.h : header file
//

#if !defined(AFX_TCLBDEMODLG_H__BC64B6E9_F097_11D1_A0F1_006097B18B90__INCLUDED_)
#define AFX_TCLBDEMODLG_H__BC64B6E9_F097_11D1_A0F1_006097B18B90__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TabCheckListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CTCLBDemoDlg dialog

class CTCLBDemoDlg : public CDialog
{
// Construction
public:
	CTCLBDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTCLBDemoDlg)
	enum { IDD = IDD_TCLBDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CTabCheckListBox m_ctrlCheckListBox;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCLBDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CFont* m_pFont;
	void AddStringToList();
	int GetDialogUnitNumber();

	// Generated message map functions
	//{{AFX_MSG(CTCLBDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDefaultRadio();
	afx_msg void OnEqualRadio();
	afx_msg void OnDiffRadio();
	afx_msg void OnDiffFontRadio();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCLBDEMODLG_H__BC64B6E9_F097_11D1_A0F1_006097B18B90__INCLUDED_)
