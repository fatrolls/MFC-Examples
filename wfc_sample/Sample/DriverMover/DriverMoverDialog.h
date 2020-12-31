// DriverMoverDialog.h : header file
//

#if !defined(AFX_DRIVERMOVERDIALOG_H__8D5CEDF7_518E_11D3_B0CD_00600898269E__INCLUDED_)
#define AFX_DRIVERMOVERDIALOG_H__8D5CEDF7_518E_11D3_B0CD_00600898269E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDriverMoverDialog dialog

class CDriverMoverDialog : public CDialog
{
// Construction
public:
	CDriverMoverDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDriverMoverDialog)
	enum { IDD = IDD_DRIVERMOVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverMoverDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDriverMoverDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnCopyFileToDebugEE();
	afx_msg void OnRebootDebugEE();
	afx_msg void OnStartDriver();
	afx_msg void OnStopDriver();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERMOVERDIALOG_H__8D5CEDF7_518E_11D3_B0CD_00600898269E__INCLUDED_)
