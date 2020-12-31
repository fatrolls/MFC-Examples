// ZipTestDlg.h : header file
//

#if !defined(AFX_ZIPTESTDLG_H__05772FDF_959E_4A6A_8C22_212E5D1CDE25__INCLUDED_)
#define AFX_ZIPTESTDLG_H__05772FDF_959E_4A6A_8C22_212E5D1CDE25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZipTestDlg dialog

class CZipTestDlg : public CDialog
{
// Construction
public:
	CZipTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZipTestDlg)
	enum { IDD = IDD_ZIPTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZipTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZipTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnZip();
	afx_msg void OnUnzip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIPTESTDLG_H__05772FDF_959E_4A6A_8C22_212E5D1CDE25__INCLUDED_)
