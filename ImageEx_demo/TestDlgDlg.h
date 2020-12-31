// TestDlgDlg.h : header file
//

#if !defined(AFX_TESTDLGDLG_H__DCED1A3A_D92E_4173_835F_46CAF30E68C2__INCLUDED_)
#define AFX_TESTDLGDLG_H__DCED1A3A_D92E_4173_835F_46CAF30E68C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog

class CTestDlgDlg : public CDialog
{
// Construction
public:
	CTestDlgDlg(CWnd* pParent = NULL);	// standard constructor
	~CTestDlgDlg();

	// GDI+
	ImageEx*			m_image;

// Dialog Data
	//{{AFX_DATA(CTestDlgDlg)
	enum { IDD = IDD_TESTDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLGDLG_H__DCED1A3A_D92E_4173_835F_46CAF30E68C2__INCLUDED_)
