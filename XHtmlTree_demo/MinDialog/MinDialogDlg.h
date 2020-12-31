// MinDialogDlg.h : header file
//

#ifndef MINDIALOGDLG_H
#define MINDIALOGDLG_H

#include "..\src\XHtmlTree.h"

/////////////////////////////////////////////////////////////////////////////
// CMinDialogDlg dialog

class CMinDialogDlg : public CDialog
{
// Construction
public:
	CMinDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMinDialogDlg)
	enum { IDD = IDD_MINDIALOG_DIALOG };
	CXHtmlTree	m_Tree;
	//}}AFX_DATA
	CImageList	m_Images;
	int m_nCount;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMinDialogDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	void InitTree();
	void LoadTextFileFromResource(LPCTSTR lpszResource);

	// Generated message map functions
	//{{AFX_MSG(CMinDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //MINDIALOGDLG_H
