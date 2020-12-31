// CompFileDlg.h : header file
//

#if !defined(AFX_COMPFILEDLG_H__4F168D5F_C210_11D2_9E60_00104B08CC22__INCLUDED_)
#define AFX_COMPFILEDLG_H__4F168D5F_C210_11D2_9E60_00104B08CC22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCompFileDlg dialog

class CCompFileDlg : public CDialog
{
// Construction
public:
	CCompFileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCompFileDlg)
	enum { IDD = IDD_COMPFILE_DIALOG };
	CString	m_DirPathString;
	CString	m_FilePathString;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCompFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFilebrowser();
	afx_msg void OnDirbrowser();
	afx_msg void OnReadfromfile();
	afx_msg void OnWritetofile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPFILEDLG_H__4F168D5F_C210_11D2_9E60_00104B08CC22__INCLUDED_)
