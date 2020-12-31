// CtlDlg.h : header file
//

#if !defined(AFX_CTLDLG_H__F2267948_01AE_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CTLDLG_H__F2267948_01AE_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCtlDlg dialog

class CCtlDlg : public CDialog
{
// Construction
public:
	CCtlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCtlDlg)
	enum { IDD = IDD_CTL_DIALOG };
	CListBox	m_listDir;
	CListBox	m_listMCBox;
	CListBox	m_listBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCtlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTLDLG_H__F2267948_01AE_11D1_9C9A_444553540000__INCLUDED_)
