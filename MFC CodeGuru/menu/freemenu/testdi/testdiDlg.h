// testdiDlg.h : header file
//

#if !defined(AFX_TESTDIDLG_H__6EA700CE_0AF3_11D2_9768_0080C858DB41__INCLUDED_)
#define AFX_TESTDIDLG_H__6EA700CE_0AF3_11D2_9768_0080C858DB41__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTestdiDlg dialog
class CFreeMenu;
class CTestdiDlg : public CDialog
{
// Construction
public:
	CFreeMenu  *m_menu;
	CTestdiDlg(CWnd* pParent = NULL);	// standard constructor
	CFont font;
// Dialog Data
	//{{AFX_DATA(CTestdiDlg)
	enum { IDD = IDD_TESTDI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestdiDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestdiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuitem32782();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDIDLG_H__6EA700CE_0AF3_11D2_9768_0080C858DB41__INCLUDED_)
