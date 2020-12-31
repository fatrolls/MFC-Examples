// AutoCompleteDlg.h : header file
//

#if !defined(AFX_AUTOCOMPLETEDLG_H__7945FE1C_25D3_11D4_AD2F_0050BAAB46B1__INCLUDED_)
#define AFX_AUTOCOMPLETEDLG_H__7945FE1C_25D3_11D4_AD2F_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXAutoComplete.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoCompleteDlg dialog
 
class CAutoCompleteDlg : public CDialog
{
// Construction
public:
	COXAutoComplete m_autoComplete;
	CAutoCompleteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAutoCompleteDlg)
	enum { IDD = IDD_AUTOCOMPLETE_DIALOG };
	CEdit	m_editUp;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoCompleteDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAutoCompleteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOCOMPLETEDLG_H__7945FE1C_25D3_11D4_AD2F_0050BAAB46B1__INCLUDED_)
