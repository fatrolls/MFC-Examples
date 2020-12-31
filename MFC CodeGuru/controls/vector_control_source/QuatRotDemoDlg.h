// QuatRotDemoDlg.h : header file
//

#if !defined(AFX_QUATROTDEMODLG_H__BE23BA67_C0D3_11D1_9738_F0693C6EEA7E__INCLUDED_)
#define AFX_QUATROTDEMODLG_H__BE23BA67_C0D3_11D1_9738_F0693C6EEA7E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CQuatRotDemoDlg dialog

class CQuatRotDemoDlg : public CDialog
{
// Construction
public:
	CQuatRotDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CQuatRotDemoDlg)
	enum { IDD = IDD_QUATROTDEMO_DIALOG };
	CButton	m_chkFront;
	CVectorCtl m_Vector;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuatRotDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQuatRotDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBoundFront();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUATROTDEMODLG_H__BE23BA67_C0D3_11D1_9738_F0693C6EEA7E__INCLUDED_)
