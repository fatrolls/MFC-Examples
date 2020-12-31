#if !defined(AFX_ZIPDLG_H__9D34EB20_98AA_4A62_89BB_679AA8D45F56__INCLUDED_)
#define AFX_ZIPDLG_H__9D34EB20_98AA_4A62_89BB_679AA8D45F56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZipDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZipDlg dialog

class CZipDlg : public CDialog
{
// Construction
public:
	CZipDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZipDlg)
	enum { IDD = IDD_ZIP_DIALOG };
	CString	m_sFilePath;
	CString	m_sFolderPath;
	int		m_nFileCount;
	int		m_nFolderCount;
	BOOL	m_bIgnorePath;
	DWORD	m_nTotalCompSize;
	DWORD	m_nTotalUncompSize;
	BOOL	m_bAddToZip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZipDlg)
	afx_msg void OnBrowsefile();
	afx_msg void OnBrowsefolder();
	afx_msg void OnZip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIPDLG_H__9D34EB20_98AA_4A62_89BB_679AA8D45F56__INCLUDED_)
